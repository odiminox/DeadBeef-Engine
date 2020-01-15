
//--------------------------------------------------------------------------------------
// MEGASHADER.fx
//
//Simon  Jordan
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
int setColour = 1;
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

struct pointLight
{
	float  spotPower;
	float3 dir;
	float3 att;
	float range;
	float4 color;
	float3 pos;
};

cbuffer cbFixed
{
	float gFogStart;
	float gFogRange;
	float3 gFogColor;
}

BlendState SrcAlphaBlendingAdd
{
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
	 RenderTargetWriteMask[0] = 0x0F;
};

float fogStart;
float fogEnd;

struct Material
{
	float Ka, Kd, Ks, A;
};
//--------------------------------------------------------------------------------------

//LIGHTING VARIABLES
//--------------------------------------------------------------------------------------
DirectionalLight light;
pointLight pLight;
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
	float  fogFactor :FOG;
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

	//set position into clip space
	output.p = mul( input.p, World );
	input.p = mul( input.p, World );
	output.p = mul( input.p, View );    
	output.p = mul( output.p, Projection );	

	output.fogFactor = saturate((fogEnd - input.p.z) / (fogEnd - fogStart));
	//Calculate the normal vector against the world matrix only and then normalize it
	output.n = normalize(mul(input.n, (float3x3)World));
	

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
	}


	return output;  
}



float4 PS_PIXEL_LIGHTING_BLINNPHONG( PS_INPUT_PP_BLINNPHONG input ) : SV_Target
{
	float4 textureColor;
	float4 color;
	bool inValue;

	textureColor	   = tex2D.Sample(linearSampler, input.t);
	//////////////////////////
		//renormalize interpolated vectors
	input.n = normalize( input.n );		
	input.h = normalize( input.h );

	//calculate lighting	
	float4 I = calcBlinnPhongLighting( material, light.color, input.n, -light.dir, input.h );

	if (setColour == 1){
		color = float4(1.0f, 0.0f, 0.0f, 1.0f);
		textureColor = textureColor + color;
		return I * textureColor; 
	}	
	//color = color  * textureColor;

	

	
	
	//with texturing
	return I * tex2D.Sample(linearSampler, input.t);
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
	    SetPixelShader( CompileShader( ps_4_0, PS_PIXEL_LIGHTING_BLINNPHONG() ) );
		//SetBlendState( SrcAlphaBlendingAdd, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetRasterizerState( rsSolid );
    }


}
