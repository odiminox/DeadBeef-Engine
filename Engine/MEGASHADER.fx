
//--------------------------------------------------------------------------------------
// MEGASHADER.fx
//
//Simon 'dxCUDA' Jordan
//
//This shader is highly radioactive, the geiger counter is off the charts.
//I advise you to find one better.
//
//--------------------------------------------------------------------------------------

//TRANSFORMATION MATRICES
//--------------------------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;
//float4x4 WVP;
//--------------------------------------------------------------------------------------

//TEXTURE VARIABLES
//--------------------------------------------------------------------------------------
//color map texture
Texture2D tex2D;
//bump map texture
Texture2D bump2D;
//Specular map texture
Texture2D spec2D;
//--------------------------------------------------------------------------------------

//TEXTURE SAMPLER STATE
//--------------------------------------------------------------------------------------
SamplerState linearSampler
{
    Filter = min_mag_mip_linear;
    AddressU = Wrap;
    AddressV = Wrap;
};
//--------------------------------------------------------------------------------------

//LIGHTING STRUCTURES
//--------------------------------------------------------------------------------------
struct DirectionalLight
{
	float4 color;
	float3 dir;
};

struct spotLight
{
	float  spotPower;
	float3 dir;
	float3 att;
	float range;
	float4 color;
	float3 pos;
};

struct pointLight
{
	float3 att;
	float range;
	float4 color;
	float3 pos;
};

//struct light
//{
//	float4 color;
//	float  spotPower;
//	float3 dir;
//	float3 att;
//	float range;
//	float3 pos;
//};

struct Material
{
	float Ka, Kd, Ks, A;
};
//--------------------------------------------------------------------------------------

//LIGHTING VARIABLES
//--------------------------------------------------------------------------------------
DirectionalLight light;
spotLight  sLight;
pointLight pLight;
//light myLight;
Material material;
float4 ambientLight;
float3 eye;
float4x4 gTexMtx;
float4 specularColor;
float specularPower;
int pLightType; 
//--------------------------------------------------------------------------------------


//RASTERIZER STATES
//--------------------------------------------------------------------------------------
RasterizerState rsSolid
{
	  FillMode = Solid;
	  CullMode = NONE;
	  FrontCounterClockwise = false;
};
//--------------------------------------------------------------------------------------

//VERTEX AND PIXEL SHADER INPUTS
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 p 	: POSITION;
	float2 t 	: TEXCOORD; 
	float3 n 	: NORMAL;
    float3 tangent  : TANGENT;
};


struct PS_INPUT_PP_BLINNPHONG
{
	float4 p 	: SV_POSITION;
	float4 pW   : POSITION;
	float2 t 	: TEXCOORD;	
	float3 n 	: TEXCOORD1;
	float3 h 	: TEXCOORD2;
    float3 tangent  : TANGENT;
};
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Blinn-Phong Lighting Reflection Model
//--------------------------------------------------------------------------------------
float4 calcBlinnPhongLighting( Material M, float4 LColor, float3 N, float3 L, float3 H )
{	
	float4 Ia = M.Ka * ambientLight;
	float4 Id = M.Kd * saturate( dot(N,L) );
	float4 Is = M.Ks * pow( saturate(dot(N,H)), M.A );
	
	return Ia + (Id + Is) * LColor;
}


//--------------------------------------------------------------------------------------
// PER PIXEL LIGHTING 
//--------------------------------------------------------------------------------------
PS_INPUT_PP_BLINNPHONG VS_PIXEL_LIGHTING_BLINNPHONG( VS_INPUT input )
{

	PS_INPUT_PP_BLINNPHONG output;

	//set texture coords
	output.t = input.t;

	output.pW = mul( input.p, World );
	//output.pW = mul( input.p, View );    
	//output.pW = mul( output.p, Projection );	

	//set position into clip space
	//output.p = mul( input.p, World );
	input.p = mul( input.p, World );
	output.p = mul( input.p, View );    
	output.p = mul( output.p, Projection );	

	
	//Calculate the normal vector against the world matrix only and then normalize it
	output.n = normalize(mul(input.n, (float3x3)World));
	
	//Transform to homogeneous clip space
	//output.p = mul(input.p, WVP);
	
	//Calculate the tangent vector against the world matrix only and then normalize the final value
	output.tangent = mul(input.tangent, (float3x3)World);
    output.tangent = normalize(output.tangent);		

	//set required lighting vectors for interpolation
	float3 V = normalize( eye - (float3) input.p );

	if(pLightType == 0)
	{
		output.h = normalize( -light.dir + V );
	} else if(pLightType == 1)
	{
		output.h = normalize( -pLight.pos + V );
	} else if (pLightType == 2)
	{
		output.h = normalize( -pLight.pos + V );
	}


	return output;  
}

float4 PS_PIXEL_LIGHTING_BLINNPHONG( PS_INPUT_PP_BLINNPHONG input ) : SV_Target
{
		
	//renormalize interpolated vectors
	input.n = normalize( input.n );		
	input.h = normalize( input.h );
	
	//calculate lighting	
	float4 I = calcBlinnPhongLighting( material, light.color, input.n, -light.dir, input.h );
	
	//with texturing
	return I * tex2D.Sample(linearSampler, input.t);
}


float4 PS_NORMAL_MAP( PS_INPUT_PP_BLINNPHONG input) : SV_Target
{  
	float4 textureColor;
    float4 bumpMap;
    float3 bumpNormal;
	float3 bitangent;
	float lightIntensity;
    float4 color;
	float4 specularIntensity;
	float4 specularPower1;
	float3 reflection;
	float4 diffuse;
	float4 specular;
	float4 I;
	float s;
	float3 lightVec;

	textureColor	   = tex2D.Sample(linearSampler, input.t);
	bumpMap			   = bump2D.Sample(linearSampler, input.t);
	specularIntensity  = spec2D.Sample(linearSampler, input.t);

	//renormalize interpolated vectors
	input.h = normalize( input.h );

	// Expand the range of the normal value from (0, +1) to (-1, +1).
    bumpMap = (2.0f * bumpMap) - 1.0f;

	input.n = normalize( input.n );		
	input.tangent = normalize(input.tangent - dot(input.tangent, input.n)*input.n);//Gram-Schmidt orthogonalize
	bitangent = cross(input.n, input.tangent);//this is where the issue arises

	//Tex space matrix
	float3x3 texSpace = float3x3(input.tangent, bitangent, input.n);

	//Convert normal from normal map to texture space and store in input.normal
	bumpNormal = normalize(mul(bumpMap, texSpace));

	input.n = normalize(mul(bumpMap, texSpace));

	if(pLightType == 0)
	{
		lightIntensity = saturate(dot(bumpNormal, -light.dir));
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		color = saturate(material.Kd * lightIntensity);
		
		//color = color  * textureColor;

		specularPower1 = 5.0f;//Need to make this modifiable outside of the shader
		if(lightIntensity > 0.0f)
		{
			//Calculate the reflection vector based on the light intensity, normal vector and light direction
			reflection = normalize(2 * lightIntensity * bumpNormal +light.dir);
			// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
			specular = pow(saturate(dot(reflection, input.h)), specularPower1);
			// Use the specular map to determine the intensity of specular light at this pixel.
			 specular = specular * specularIntensity;
			// Add the specular component last to the output color.
			color = saturate(color + specular) * textureColor;

		}
		 //calculate lighting	
		I = calcBlinnPhongLighting( material, light.color, input.n, -light.dir, input.h );


	} else if (pLightType == 1)
	{
		lightIntensity = saturate(dot(bumpNormal, -sLight.dir));
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		color = saturate(material.Kd * lightIntensity);

		// The vector from the surface to the light.
		lightVec =normalize(sLight.pos - input.pW);
		
		// The distance from surface to light.
		float d = length(lightVec);

		
		// Normalize the light vector.
		lightVec /= d;
		
		if( d > pLight.range )
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

		s = pow(max(dot(-lightVec, sLight.dir), 0.0f), sLight.spotPower);

		//color = color  * textureColor;

		specularPower1 = 5.0f;//Need to make this modifiable outside of the shader
		if(lightIntensity > 0.0f)
		{		
			//Calculate the reflection vector based on the light intensity, normal vector and light direction
			reflection = normalize(2 * lightIntensity * bumpNormal +sLight.dir);
			// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
			specular = pow(saturate(dot(reflection, input.h)), specularPower1);
			 // Use the specular map to determine the intensity of specular light at this pixel.
			specular = specular * specularIntensity;

			
			  // Add the specular component last to the output color.
			color = saturate(color  + specular) * s;
			color = color  / dot(sLight.att, float3(0.5f, d, d*d)) * textureColor;

		}
		 //calculate lighting	
		I = calcBlinnPhongLighting( material, sLight.color, input.n, -sLight.dir, input.h );
     	
	} else if(pLightType == 2)
	{
		lightIntensity = saturate(dot(bumpNormal, -pLight.pos));
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		color = saturate(material.Kd * lightIntensity);

		// The vector from the surface to the light.
		lightVec = pLight.pos - input.pW;
		//lightVec =normalize(pLight.pos - input.pW);
		
		// The distance from surface to light.
		float d = length(lightVec);

		// Normalize the light vector.
		lightVec /= d;
		//lightVec = -normalize(d);
		
		if( d > pLight.range )
		return float4(0.0f, 0.0f, 0.0f, 0.0f);



		//color = color  * textureColor;

		specularPower1 = 5.0f;//Need to make this modifiable outside of the shader
		if(lightIntensity > 0.0f)
		{		
			//Calculate the reflection vector based on the light intensity, normal vector and light direction
			reflection = normalize(2 * lightIntensity * bumpNormal -pLight.pos);
			// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
			specular = pow(saturate(dot(reflection, input.h)), specularPower1);
			 // Use the specular map to determine the intensity of specular light at this pixel.
			specular = specular * specularIntensity;

			  // Add the specular component last to the output color.
			color = saturate(color  + specular);
			color = color / dot(pLight.att, float3(1.0f, d, d*d)) * textureColor;// / dot(pLight.att, float3(1.0f, d, d*d)) * textureColor;
		}

		I = calcBlinnPhongLighting( material, pLight.color, input.n, -pLight.pos, input.h);
		//I = calcBlinnPhongLighting( material, pLight.color, input.n, -sLight.dir, input.h );
	}
	
	 
	return I *  color;
	//return I *  color;

}
//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------

technique10 RENDER_PL_BLINNPHONG
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS_PIXEL_LIGHTING_BLINNPHONG() ) );
        SetGeometryShader( NULL );
       //SetPixelShader( CompileShader( ps_4_0, PS_PIXEL_LIGHTING_BLINNPHONG() ) );
	    SetPixelShader( CompileShader( ps_4_0, PS_NORMAL_MAP() ) );
        SetRasterizerState( rsSolid );
    }


}
