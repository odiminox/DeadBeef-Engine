//--------------------------------------------------------------------------------------
// Lighting
//--------------------------------------------------------------------------------------

//transformation matrices
matrix World;
matrix View;
matrix Projection;

//TEXTURE VARIABLES
//--------------------------------------------------------------------------------------

//color map texture
Texture2D tex2D;
//bump map texture
Texture2D bump2D;


//texture sampler state
SamplerState linearSampler
{
    Filter = min_mag_mip_linear;
    AddressU = Wrap;
    AddressV = Wrap;
};

//LIGHTING STRUCTURES AND VARIABLES
//--------------------------------------------------------------------------------------
struct DirectionalLight
{
	float4 color;
	float3 dir;
};

struct Material
{
	float Ka, Kd, Ks, A;
};

//lighting vars
DirectionalLight light;
Material material;
float4 ambientLight;
float3 eye;
float4x4 gTexMtx;

//RASTERIZER STATES
//--------------------------------------------------------------------------------------
RasterizerState rsSolid
{
	  FillMode = Solid;
	  CullMode = NONE;
	  FrontCounterClockwise = false;
};

//VERTEX AND PIXEL SHADER INPUTS
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 p 	: POSITION;
	float2 t 	: TEXCOORD; 
	float3 n 	: NORMAL;
    float3 tangent  : TANGENT;
	//float3 bitangent  : BINORMAL;
};


struct PS_INPUT_PP_BLINNPHONG
{
	float4 p 	: SV_POSITION;  
	float2 t 	: TEXCOORD;	
	float3 n 	: TEXCOORD1;
	float3 h 	: TEXCOORD2;
    float3 tangent  : TANGENT;
	//float3 bitangent  : BINORMAL;
};

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
	
	//set position into clip space
	input.p = mul( input.p, World );
	output.p = mul( input.p, View );    
	output.p = mul( output.p, Projection );	

	// Output vertex attributes for interpolation across triangle.
	output.t = mul(float4(input.t, 0.0f, 1.0f), gTexMtx);
	
	//set texture coords
	output.t = input.t;			
	
	//set required lighting vectors for interpolation
	float3 V = normalize( eye - (float3) input.p );
	output.n = normalize( mul(input.n, (float3x3)World) );	
	output.h = normalize( -light.dir + V );
	
	// Calculate the tangent vector against the world matrix only and then normalize the final value.
	output.tangent = mul(input.tangent, (float3x3)World);
	output.tangent = normalize(output.tangent);

	//output.bitangent = mul(input.bitangent, input.tangent);
	//output.bitangent = normalize(output.bitangent);
	
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

	textureColor = tex2D.Sample(linearSampler, input.t);
	bumpMap     = bump2D.Sample(linearSampler, input.t);
     	
	//renormalize interpolated vectors
	input.n = normalize( input.n );		
	input.h = normalize( input.h );

	// Expand the range of the normal value from (0, +1) to (-1, +1).
     bumpMap = (2.0f * bumpMap) - 1.0f;

	input.tangent = normalize(input.tangent - dot(input.tangent, input.n)*input.n);
	//input.bitangent = cross(input.n, input.tangent);
	bitangent = cross(input.n, input.tangent);

	//Tex space matrix
	//float3x3 texSpace = float3x3(input.tangent, input.bitangent, input.n);
	float3x3 texSpace = float3x3(input.tangent, bitangent, input.n);

	 // Calculate the normal from the data in the bump map.
    //bumpNormal = input.n + bumpMap.x * input.tangent + bumpMap.y * B;

	 //Convert normal from normal map to texture space and store in input.normal
	 //float3 bumpedNormal = normalize(mul(bumpMap, texSpace));
	 bumpNormal = normalize(mul(bumpMap, texSpace));

	 // Normalize the resulting bump normal.
     bumpNormal = normalize(bumpNormal);

	 input.n = normalize(mul(bumpMap, texSpace));

	 //lightIntensity = saturate(dot(bumpedNormal, -light.dir));
	 lightIntensity = saturate(dot(bumpNormal, -light.dir));

	 //calculate lighting	
	float4 I = calcBlinnPhongLighting( material, light.color, input.n, -light.dir, input.h );

	 //with texturing
	return lightIntensity * I *  textureColor;
	 //return I *  textureColor;
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
        SetPixelShader( CompileShader( ps_4_0, PS_PIXEL_LIGHTING_BLINNPHONG() ) );
	    //SetPixelShader( CompileShader( ps_4_0, PS_NORMAL_MAP() ) );
        SetRasterizerState( rsSolid );
    }
}
