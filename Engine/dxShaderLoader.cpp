//#include "dxShaderLoader.h"
//
//void dxShaderLoader::InitializeShader(ID3D10Device* pD3DDevice, ID3D10Effect*	pBasicEffect, HWND hwnd, LPCSTR* filename)
//{
//	D3D10Blob* compilationErrors = 0;
//	HRESULT hr = 0;
//	if ( FAILED( D3DX10CreateEffectFromFile(*filename,
//		NULL, NULL,
//		"fx_4_0",
//		D3D10_SHADER_ENABLE_STRICTNESS,
//		0,
//		pD3DDevice,
//		NULL,
//		NULL,
//		&pBasicEffect,
//		&compilationErrors,
//		NULL	) ) ) {
//			if( compilationErrors )
//			{
//				MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
//				compilationErrors->Release();
//			}
//
//			pBasicTechnique = pBasicEffect->GetTechniqueByName("RENDER_PL_BLINNPHONG");
//			if ( pBasicTechnique == NULL ) return fatalError("Could not find specified technique!");
//
//			const D3D10_INPUT_ELEMENT_DESC layout[] =
//			{
//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 }
//			};
//
//			const int vertexInputLayoutNumElements = sizeof(layout)/sizeof(layout[0]);
//
//			D3D10_PASS_DESC PassDesc;
//			pBasicTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
//
//			if ( FAILED( pD3DDevice->CreateInputLayout(
//				layout,
//				vertexInputLayoutNumElements,
//				PassDesc.pIAInputSignature,
//				PassDesc.IAInputSignatureSize,
//				&pVertexLayout ) ) ) return fatalError("Could not create Input Layout!");
//
//			//create matrix effect pointers
//			pViewMatrixEffectVariable		= pBasicEffect->GetVariableByName( "View" )->AsMatrix();
//			pProjectionMatrixEffectVariable = pBasicEffect->GetVariableByName( "Projection" )->AsMatrix();
//			pWorldMatrixEffectVariable		= pBasicEffect->GetVariableByName( "World" )->AsMatrix();
//			pVar = pBasicEffect->GetVariableByName( "light" );
//			pVar->SetRawValue(&myLight.directionalLight, 0, sizeof(DirectionalLight));
//
//			pVar = pBasicEffect->GetVariableByName( "material" );
//			pVar->SetRawValue(&myLight.material, 0, sizeof(Material));
//
//			pVar = pBasicEffect->GetVariableByName( "ambientLight" );
//			pVar->SetRawValue( &myLight.ambientLight, 0, 16 );
//
//			myTexture.pTextureSR			= pBasicEffect->GetVariableByName( "tex2D" )->AsShaderResource();
//			myTexture.pBumSR                = pBasicEffect->GetVariableByName( "bump2D" )->AsShaderResource();
//}