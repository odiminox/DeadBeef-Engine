#ifndef DXD3D
#define DXD3D

#include <vector>
#include <d3d10.h>
#include <d3dx10.h>
#include <windows.h>
#include <sstream>
#include <string.h>

#include "dxGeometry.h"
//#include "dxTextureLoader.h"

using namespace std;
/**************************************************************************************
* dxD3D.h
* Simon GL Jordan 498992

* Description:
* DirectX10 core pipeline processes and functions.
*
* Use:
* Create pointer instance in engine body class to use.
***************************************************************************************/

static HWND wndHandle; // global variable to hold the window handlev

class dxD3D
{
protected:
	static ID3D10Device*				pD3DDevice;

	//effects and techniques
	static ID3D10Effect*				pBasicEffect;
	static ID3D10EffectTechnique*		pBasicTechnique;
	static ID3D10EffectVariable*		pVar;

	//effect variable pointers
	static ID3D10EffectMatrixVariable* pViewMatrixEffectVariable;
	static ID3D10EffectMatrixVariable* pProjectionMatrixEffectVariable;
	static ID3D10EffectMatrixVariable* pWorldMatrixEffectVariable;
	//static ID3D10EffectMatrixVariable* pWVPMatrixEffectVariable;

	//projection and view matrices
	static D3DXMATRIX				   worldMatrix;
	static D3DXMATRIX                  viewMatrix;
	static D3DXMATRIX                  projectionMatrix;
	//static D3DXMATRIX				   WVP;

	static ID3D10BlendState *pAlphaBlendState;
	//alpha blend state2 Multi sampled transparency
	static ID3D10BlendState *pAlphaBlendState2;

	static float AlphaBlendFactor[4];
	static UINT AlphaSampleMask;

	static float AlphaBlendFactor2[4];
	static UINT AlphaSampleMask2;

	static ID3D10BlendState *pBaseBlendState;
	static float BaseBlendFactor[4];
	static UINT BaseSampleMask;

	static ID3D10Buffer*				pVertexBuffer;
	static ID3D10Buffer*				pIndexBuffer;
	ID3D10DepthStencilState	*pDepthStencil_State;		//enable z buffer
	ID3D10DepthStencilState	*pDepthStencil_Dis_State;	//disable z buffer

	static LPCSTR							rootShaderFileName;
	static LPCSTR							rootTechniqueName;

	static bool									rootCustomShader;

	static bool                         Windowed;
public:
	//window handle shortcut

	HWND error_Handler;
	//device vars

	IDXGISwapChain*				pSwapChain;
	ID3D10RenderTargetView*		pRenderTargetView;
	ID3D10Texture2D*			pDepthStencil;
	ID3D10DepthStencilView*		pDepthStencilView;
	D3D10_VIEWPORT				viewPort;
	ID3D10RasterizerState*		pRS;
	ID3D10EffectScalarVariable* fogStartPtr;
	ID3D10EffectScalarVariable* fogEndPtr;

	//input layout and mesh
	ID3D10InputLayout*			pVertexLayout;
	ID3DX10Mesh*				pMesh;
	ID3DX10Mesh*				pMesh2;

	////get technique desc
	D3D10_TECHNIQUE_DESC		techniqueDescription;

	RECT						myRect;
	//dxTextureLoader             myTexture;

public:
	dxD3D();
	~dxD3D();

	void dxBeginScene();
	void dxEndScene();

	ID3D10Device* GetDevice();

	bool createSwapChainAndDevice(UINT width, UINT height );
	bool loadShadersAndCreateInputLayouts();
	void createViewports( UINT width, UINT height );
	bool dxInitialiseStencilStates();
	bool dxInitialiseBlendStates();
	inline void initRasterizerState();
	bool createRenderTargetsAndDepthBuffer( UINT width, UINT height );

	void Set_Zbuffer_On();
	void Set_Zbuffer_Off();

	bool dxInitialiseGraphics(UINT width, UINT height );

	void dxShutDown();
	ID3DX10Font* mFont;

private:
	//fatal error handler
	bool fatalError(const LPCSTR msg);
};

ID3D10Device*				dxD3D::pD3DDevice;

LPCSTR dxD3D::rootShaderFileName;
LPCSTR dxD3D::rootTechniqueName;

bool        dxD3D::rootCustomShader;

//effects and techniques
ID3D10Effect*				dxD3D::pBasicEffect;
ID3D10EffectTechnique*		dxD3D::pBasicTechnique;
ID3D10EffectVariable*		dxD3D::pVar;

float dxD3D::AlphaBlendFactor[4];
UINT dxD3D::AlphaSampleMask;

float dxD3D::AlphaBlendFactor2[4];
UINT dxD3D::AlphaSampleMask2;

ID3D10BlendState * dxD3D::pBaseBlendState;
FLOAT dxD3D::BaseBlendFactor[4];
UINT dxD3D::BaseSampleMask;

ID3D10BlendState * dxD3D::pAlphaBlendState;
//alpha blend state2 Multi sampled transparency
ID3D10BlendState * dxD3D::pAlphaBlendState2;

//effect variable pointers
ID3D10EffectMatrixVariable* dxD3D::pViewMatrixEffectVariable;
ID3D10EffectMatrixVariable* dxD3D::pProjectionMatrixEffectVariable;
ID3D10EffectMatrixVariable* dxD3D::pWorldMatrixEffectVariable;
//ID3D10EffectMatrixVariable* dxD3D::pWVPMatrixEffectVariable;

//projection and view matrices
D3DXMATRIX				    dxD3D::worldMatrix;
D3DXMATRIX                  dxD3D::viewMatrix;
D3DXMATRIX                  dxD3D::projectionMatrix;
//D3DXMATRIX					dxD3D::WVP;

bool						dxD3D::Windowed;

ID3D10Buffer*				dxD3D::pVertexBuffer;
ID3D10Buffer*				dxD3D::pIndexBuffer;

dxD3D::dxD3D():pSwapChain(NULL),
			   pRenderTargetView(NULL),
			   pVertexLayout(0),
			   pRS(0)
{
	//free textures
	/*for ( unsigned int i=0; i < textureSRV.size(); i++ )
	{
		textureSRV[i]->Release();
	}	*/
	D3DXMatrixIdentity(&worldMatrix);

	pAlphaBlendState = NULL;
	pAlphaBlendState2 = NULL;
	pBaseBlendState = NULL;

	AlphaSampleMask = 0xffffffff;
	AlphaBlendFactor[0]	= NULL;
	AlphaBlendFactor[1]	= NULL;
	AlphaBlendFactor[2]	= NULL;
	AlphaBlendFactor[3]	= NULL;

	AlphaSampleMask2 = 0xffffffff;	//white
	AlphaBlendFactor2[0]	= NULL;
	AlphaBlendFactor2[1]	= NULL;
	AlphaBlendFactor2[2]	= NULL;
	AlphaBlendFactor2[3]	= NULL;
}
dxD3D::~dxD3D()
{
}

ID3D10Device* dxD3D::GetDevice()
{
	return pD3DDevice;
}
bool dxD3D::dxInitialiseGraphics(UINT width, UINT height )
{
	if ( !createSwapChainAndDevice(width, height) )
	{
		MessageBox(NULL, "Could not create swap chain and device.", "Error", MB_OK);
		return false;
	}

	// INPUT ASSEMBLY STAGE
	//*****************************************************************************
	if ( !loadShadersAndCreateInputLayouts() )
	{
		MessageBox(NULL, "Could not load shaders and create input layouts.", "Error", MB_OK);
		return false;
	}

	// RASTERIZER STAGE SETUP
	//*****************************************************************************
	createViewports(width, height);
	initRasterizerState();

	// OUTPUT-MERGER STAGE
	//*****************************************************************************
	if ( !createRenderTargetsAndDepthBuffer(width, height) )
	{
		MessageBox(NULL, "Out put merger stage failed", "Error", MB_OK);
		return false;
	}

	return true;
}
void dxD3D::dxBeginScene()
{
	pD3DDevice->ClearRenderTargetView( pRenderTargetView, D3DXCOLOR(0.4,0.4,0.6,1) );
	pD3DDevice->ClearDepthStencilView( pDepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0f, 0 );
	// Restore default states, input layout and primitive topology
	// because mFont->DrawText changes them.  Note that we can
	// restore the default states by passing null.
	//Set_Zbuffer_On();
 	pD3DDevice->OMSetDepthStencilState(0, 0);
 	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};
	pD3DDevice->OMSetBlendState(0, blendFactors, 0xffffffff);
	pD3DDevice->OMSetBlendState(pAlphaBlendState2, AlphaBlendFactor2, AlphaSampleMask2);

	pD3DDevice->IASetInputLayout(pVertexLayout);
	pD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	pWorldMatrixEffectVariable->SetMatrix(worldMatrix);
}
void dxD3D::dxEndScene()
{
	//pD3DDevice->OMSetBlendState(pBaseBlendState, BaseBlendFactor, BaseSampleMask);
	pSwapChain->Present(1, 0);
}

void dxD3D::Set_Zbuffer_On()
{
	pD3DDevice->OMSetDepthStencilState(pDepthStencil_State, 1);
}

void dxD3D::Set_Zbuffer_Off()
{
	pD3DDevice->OMSetDepthStencilState(pDepthStencil_Dis_State, 1);
}

bool dxD3D::dxInitialiseBlendStates()
{
	//get the current blend state ie the base state of blending
	pD3DDevice->OMGetBlendState(&pBaseBlendState, BaseBlendFactor, &BaseSampleMask);

	//blend state description
	D3D10_BLEND_DESC State_Desc;

	//set up the alpha blend state
	ZeroMemory(&State_Desc, sizeof(D3D10_BLEND_DESC));
	State_Desc.AlphaToCoverageEnable = FALSE;
	State_Desc.BlendEnable[0] = TRUE;
	State_Desc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	State_Desc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	State_Desc.BlendOp = D3D10_BLEND_OP_ADD;
	State_Desc.SrcBlendAlpha = D3D10_BLEND_ZERO;
	State_Desc.DestBlendAlpha = D3D10_BLEND_ZERO;
	State_Desc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	State_Desc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

	//Create the alpha state
	pD3DDevice->CreateBlendState(&State_Desc, &pAlphaBlendState);

	//blend state description
	D3D10_BLEND_DESC State_Desc2;

	//set up the alpha blend state
	ZeroMemory(&State_Desc2, sizeof(D3D10_BLEND_DESC));
	State_Desc2.AlphaToCoverageEnable = TRUE;
	State_Desc2.BlendEnable[0] = TRUE;
	State_Desc2.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	State_Desc2.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	State_Desc2.BlendOp = D3D10_BLEND_OP_ADD;
	State_Desc2.SrcBlendAlpha = D3D10_BLEND_ZERO;
	State_Desc2.DestBlendAlpha = D3D10_BLEND_ZERO;
	State_Desc2.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	State_Desc2.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

	//Create the alpha state
	pD3DDevice->CreateBlendState(&State_Desc2, &pAlphaBlendState2);

	return true;
}

bool dxD3D::dxInitialiseStencilStates()
{
	D3D10_DEPTH_STENCIL_DESC DepthStencil_State_Desc;
	ZeroMemory(&DepthStencil_State_Desc, sizeof(pDepthStencil_State));

	//Z Buffer Enabled
	DepthStencil_State_Desc.DepthEnable = true;
	DepthStencil_State_Desc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	DepthStencil_State_Desc.DepthFunc = D3D10_COMPARISON_LESS;
	DepthStencil_State_Desc.StencilEnable = true;
	DepthStencil_State_Desc.StencilReadMask = 0xFF;
	DepthStencil_State_Desc.StencilWriteMask = 0xFF;
	DepthStencil_State_Desc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_State_Desc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	DepthStencil_State_Desc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_State_Desc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	DepthStencil_State_Desc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_State_Desc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	DepthStencil_State_Desc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_State_Desc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	//create the state
	pD3DDevice->CreateDepthStencilState(&DepthStencil_State_Desc, &pDepthStencil_State);

	//set the state
	pD3DDevice->OMSetDepthStencilState(pDepthStencil_State, 1);

	D3D10_DEPTH_STENCIL_DESC DepthStencil_Dis_Desc;
	ZeroMemory(&DepthStencil_Dis_Desc, sizeof(DepthStencil_Dis_Desc));

	//Z Buffer Disabled
	DepthStencil_Dis_Desc.DepthEnable = false;
	DepthStencil_Dis_Desc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	DepthStencil_Dis_Desc.DepthFunc = D3D10_COMPARISON_LESS;
	DepthStencil_Dis_Desc.StencilEnable = true;
	DepthStencil_Dis_Desc.StencilReadMask = 0xFF;
	DepthStencil_Dis_Desc.StencilWriteMask = 0xFF;
	DepthStencil_Dis_Desc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_Dis_Desc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	DepthStencil_Dis_Desc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_Dis_Desc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	DepthStencil_Dis_Desc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_Dis_Desc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	DepthStencil_Dis_Desc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	DepthStencil_Dis_Desc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	//create the state
	pD3DDevice->CreateDepthStencilState(&DepthStencil_Dis_Desc, &pDepthStencil_Dis_State);

	return true;
}
bool dxD3D::createSwapChainAndDevice(UINT width, UINT height )
{
	HRESULT result;

	//Set up DX swap chain
	//--------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//set buffer dimensions and format
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//set refresh rate
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	//sampling settings
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;

	//output window handle
	swapChainDesc.OutputWindow = wndHandle;
	swapChainDesc.Windowed = true;

	//Create the D3D device
	//--------------------------------------------------------------
	result = ( D3D10CreateDeviceAndSwapChain(		NULL,
		D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		D3D10_SDK_VERSION,
		&swapChainDesc,
		&pSwapChain,
		&pD3DDevice ));

	if(FAILED(result))
	{
		return false;
	}

	D3DX10_FONT_DESC fontDesc;
	fontDesc.Height          = 24;
	fontDesc.Width           = 0;
	fontDesc.Weight          = 0;
	fontDesc.MipLevels       = 1;
	fontDesc.Italic          = false;
	fontDesc.CharSet         = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality         = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	strcpy_s(fontDesc.FaceName, "verdana");

	D3DX10CreateFontIndirect(pD3DDevice, &fontDesc, &mFont);

	return true;
}
/*******************************************************************
* Set up Viewports
*******************************************************************/
void dxD3D::createViewports( UINT width, UINT height )
{
	//create viewport structure
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	pD3DDevice->RSSetViewports(1, &viewPort);
}
/*******************************************************************
* Initialize Rasterizer State
*******************************************************************/
void dxD3D::initRasterizerState()
{
	//set rasterizer
	D3D10_RASTERIZER_DESC rasterizerState;
	rasterizerState.CullMode = D3D10_CULL_NONE;
	rasterizerState.FillMode = D3D10_FILL_SOLID;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = true;
	rasterizerState.AntialiasedLineEnable = true;

	ID3D10RasterizerState* pRS;
	pD3DDevice->CreateRasterizerState( &rasterizerState, &pRS);

	pD3DDevice->RSSetState(pRS);
}
/*******************************************************************
* Create Rendering Targets
*******************************************************************/
bool dxD3D::createRenderTargetsAndDepthBuffer( UINT width, UINT height )
{
	//try to get the back buffer
	ID3D10Texture2D* pBackBuffer;
	if ( FAILED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer) ) ) return fatalError("Could not get back buffer");

	//try to create render target view
	if ( FAILED( pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView) ) ) return fatalError("Could not create render target view");

	pBackBuffer->Release();

	//create depth stencil texture
	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	if( FAILED( pD3DDevice->CreateTexture2D( &descDepth, NULL, &pDepthStencil ) ) )  return fatalError("Could not create depth stencil texture");

	// Create the depth stencil view
	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	if( FAILED( pD3DDevice->CreateDepthStencilView( pDepthStencil, &descDSV, &pDepthStencilView ) ) ) return fatalError("Could not create depth stencil view");

	//set render targets
	pD3DDevice->OMSetRenderTargets( 1, &pRenderTargetView, pDepthStencilView );

	return true;
}
/*******************************************************************
* Shader Loader
*******************************************************************/
bool dxD3D::loadShadersAndCreateInputLayouts()
{
	if(rootCustomShader == true)
	{
		ID3D10Blob* compilationErrors = 0;
		HRESULT hr = 0;
		if ( FAILED( D3DX10CreateEffectFromFile(rootShaderFileName,
			NULL, NULL,
			"fx_4_0",
			D3D10_SHADER_ENABLE_STRICTNESS,
			0,
			pD3DDevice,
			NULL,
			NULL,
			&pBasicEffect,
			&compilationErrors,
			NULL	) ) ) {
				if( compilationErrors )
				{
					MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
					compilationErrors->Release();
				}
				//DXTrace(__FILE__, (DWORD)__LINE__, hr, "D3DX10CreateEffectFromFile", true);
		}

		pBasicTechnique = pBasicEffect->GetTechniqueByName(rootTechniqueName);
		if ( pBasicTechnique == NULL ) return fatalError("Could not find specified technique!");

		//create matrix effect pointers
		pViewMatrixEffectVariable		= pBasicEffect->GetVariableByName( "View" )->AsMatrix();
		pProjectionMatrixEffectVariable = pBasicEffect->GetVariableByName( "Projection" )->AsMatrix();
		pWorldMatrixEffectVariable		= pBasicEffect->GetVariableByName( "World" )->AsMatrix();
		//pWVPMatrixEffectVariable        = pBasicEffect->GetVariableByName( "WVP" )->AsMatrix();
	} else if (rootCustomShader == false)
	{
		ID3D10Blob* compilationErrors = 0;
		HRESULT hr = 0;
		if ( FAILED( D3DX10CreateEffectFromFile("fixedFunction.fx",
			NULL, NULL,
			"fx_4_0",
			D3D10_SHADER_ENABLE_STRICTNESS,
			0,
			pD3DDevice,
			NULL,
			NULL,
			&pBasicEffect,
			&compilationErrors,
			NULL	) ) ) {
				if( compilationErrors )
				{
					MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
					compilationErrors->Release();
				}
				//DXTrace(__FILE__, (DWORD)__LINE__, hr, "D3DX10CreateEffectFromFile", true);
		}
	}

	//Create Input Layout
	//--------------------------------------------------------------

	D3D10_PASS_DESC PassDesc;
	pBasicTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
	if ( FAILED( pD3DDevice->CreateInputLayout(
		layout,
		vertexInputLayoutNumElements,
		PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize,
		&pVertexLayout ) ) ) return fatalError("Could not create Input Layout!");

	// Set the input layout
	pD3DDevice->IASetInputLayout( pVertexLayout );

	pBasicTechnique->GetDesc( &techniqueDescription );

	//create vertex buffer (space for 100 vertices)
	//---------------------------------------------------------------------------------
	UINT numVertices = 100;

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( VERTEX ) * numVertices;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	if ( FAILED( pD3DDevice->CreateBuffer( &bd, NULL, &pVertexBuffer ) ) ) return fatalError("Could not create vertex buffer!");;

	// Set vertex buffer
	UINT stride = sizeof( VERTEX );
	UINT offset = 0;
	pD3DDevice->IASetVertexBuffers( 0, 1, &pVertexBuffer, &stride, &offset );

	//---------------------------------------------------------------------------------

	return true;
}

void dxD3D::dxShutDown()
{
	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	if(pSwapChain)
	{
		pSwapChain->SetFullscreenState(false, NULL);
	}

	if(pDepthStencilView)
	{
		pDepthStencilView->Release();
		pDepthStencilView = 0;
	}

	if(pDepthStencil)
	{
		pDepthStencil->Release();
		pDepthStencil = 0;
	}

	if(pRenderTargetView)
	{
		pRenderTargetView->Release();
		pRenderTargetView = 0;
	}

	if(pSwapChain)
	{
		pSwapChain->Release();
		pSwapChain = 0;
	}

	if(pD3DDevice)
	{
		pD3DDevice->Release();
		pD3DDevice = 0;
	}
}

/*******************************************************************
* Fatal Error Handler
*******************************************************************/
bool dxD3D::fatalError(const LPCSTR msg)
{
	MessageBox(error_Handler, msg, "Fatal Error!", MB_ICONERROR);
	return false;
}

#endif