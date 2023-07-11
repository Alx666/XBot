
#include "XBot.h"
#include "FAKE_IDirect3D8.h"
#include "CrcTable.h"

#ifdef TEXTURE_LOGGER
	#include "XTextureLogger.h"
#endif

#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

extern FAKE_IDirect3D8 FAKE_D3D8;
extern FAKE_IDirect3D8 *pFAKE_D3D8;						
extern IDirect3D8 *pD3D8;						
extern FAKE_IDirect3DDevice8 FAKE_D3DDevice8;
extern FAKE_IDirect3DDevice8 *pFAKE_D3DDevice8;		
extern IDirect3DDevice8 *pD3DDevice8 ;

#ifdef TEXTURE_LOGGER
	extern XTextureLogger *texturelogger;
#endif



//*************************************** MODIFIED Direct3DDevice8 FUNCTIONS ***************************************

HRESULT __stdcall FAKE_IDirect3DDevice8::BeginScene()
{
	XBot::getXBot()->BeginScene();
	return pD3DDevice8->BeginScene();
}

HRESULT __stdcall FAKE_IDirect3DDevice8::EndScene()
{
	XBot::getXBot()->EndScene();

#ifdef TEXTURE_LOGGER
	texturelogger->draw();
#endif



	return pD3DDevice8->EndScene();
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	XBot::getXBot()->d3dAnalyzer->ProcessDrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);

	return pD3DDevice8->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);	
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{	
	if(!XBot::getXBot()->d3dAnalyzer->ProcessDrawIndexedPrimitive(Type, MinIndex, NumVertices, StartIndex, PrimitiveCount))
		return D3D_OK;

	return pD3DDevice8->DrawIndexedPrimitive(Type, MinIndex, NumVertices, StartIndex, PrimitiveCount);

}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture)
{

	//Create wrapped Texture
	FAKE_IDirect3DTexture8* pFAKE_D3DTexture8 = new FAKE_IDirect3DTexture8;
	
	//Set creation information
	pFAKE_D3DTexture8->Width = Width;
	pFAKE_D3DTexture8->Height = Height;
	pFAKE_D3DTexture8->Format = Format;
	pFAKE_D3DTexture8->bLocked = false;
	pFAKE_D3DTexture8->Crc32 = 0;
	//Create Texture
	
	HRESULT Result = pD3DDevice8->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture);
	
	//Set pointer to Texture
	pFAKE_D3DTexture8->pD3DTexture8 = *ppTexture;
	

	//Report back pointer to wrapped Texture
	*ppTexture = (IDirect3DTexture8*)pFAKE_D3DTexture8;


	//Add wrapped texture handler to our list
	XBot::getXBot()->texturesList.push_back(pFAKE_D3DTexture8);
		/*#ifdef TEST
			char str[256];
			sprintf(str,"\n-> New Texture Created, Number : %i , Format: %u , Height : %i , Width : %i ",
																								 xbot.TexturesList.size(),
																								 Format,
																								 Height,
																								 Width);
			fwrite(str,sizeof(char),strlen(str),logfile);
		#endif*/
	return Result;

}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetTexture(DWORD Stage, IDirect3DBaseTexture8* pTexture)
{
	XBot* xbot = XBot::getXBot();
	
	//Check if the texture to be set is one that was wrapped
	if (pTexture != NULL && xbot->d3dAnalyzer->IsInTextureList((FAKE_IDirect3DTexture8*)pTexture))
	{

		#ifdef TEXTURE_LOGGER
			texturelogger->logTexture((FAKE_IDirect3DTexture8*)pTexture);
		#endif

		FAKE_IDirect3DTexture8* pFAKE_D3DTexture8 = (FAKE_IDirect3DTexture8*)pTexture;

		if (Stage==0)
			xbot->currentTexture = (FAKE_IDirect3DTexture8*)pTexture;
		
		xbot->d3dAnalyzer->AnalyzeTexture((FAKE_IDirect3DTexture8*)pTexture);


		return pD3DDevice8->SetTexture(Stage, pFAKE_D3DTexture8->pD3DTexture8);
	}
	else
	{
		//xbot.currentTexture = NULL;  //FIX TEMPORANEO, IN CASO DI PROBLEMI GUARDARE QUI
		return pD3DDevice8->SetTexture(Stage, pTexture);
	}		
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer)
{

	return pD3DDevice8->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer)
{

	return pD3DDevice8->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetDirect3D(IDirect3D8** ppD3D8)
{
	//Return pointer to wrapped Direct3D8
	*ppD3D8 = pD3D8;
	return D3D_OK;
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride)
{
	if(StreamNumber==0) //NEW SHIT
		XBot::getXBot()->stride=Stride;//NEW SHIT
	


	return pD3DDevice8->SetStreamSource(StreamNumber, pStreamData, Stride);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return pD3DDevice8->SetTransform(State, pMatrix);
}

ULONG __stdcall FAKE_IDirect3DDevice8::Release()
{

	return pD3DDevice8->Release();
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	//if (State==D3DRS_FOGENABLE)
		//return D3D_OK;
	
	return pD3DDevice8->SetRenderState(State, Value);
}

void __stdcall FAKE_IDirect3DDevice8::SetGammaRamp(DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{

	pD3DDevice8->SetGammaRamp(Flags, pRamp);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetViewport(CONST D3DVIEWPORT8* pViewport)
{
	XBot* xbot = XBot::getXBot();
	if(xbot->currentViewport.Width != pViewport->Width || xbot->currentViewport.Height != pViewport->Height)
	{
		xbot->currentViewport = *pViewport;
		xbot->menu->setViewport(pViewport->Width, pViewport->Height);
		xbot->console->setViewport(pViewport->Width, pViewport->Height);
	}
	return pD3DDevice8->SetViewport(pViewport);
}

//****************************** FUNCTIONS BELOW ARE PASS-THROUGH ONLY ******************************

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture)
{
	return pD3DDevice8->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture)
{
	return pD3DDevice8->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	HRESULT result =  pD3DDevice8->Reset(pPresentationParameters);
	XBot* xbot = XBot::getXBot();
	
	xbot->drawer->OnResetDevice();
	xbot->menu->OnResetDevice();

	return result;
}

HRESULT __stdcall FAKE_IDirect3DDevice8::QueryInterface(REFIID iid, void **ppvObject)
{
	return pD3DDevice8->QueryInterface(iid, ppvObject);
}

ULONG __stdcall FAKE_IDirect3DDevice8::AddRef()
{
	return pD3DDevice8->AddRef();
}

HRESULT __stdcall FAKE_IDirect3DDevice8::TestCooperativeLevel()
{
	return pD3DDevice8->TestCooperativeLevel();
}

UINT __stdcall FAKE_IDirect3DDevice8::GetAvailableTextureMem()
{
	return pD3DDevice8->GetAvailableTextureMem();
}

HRESULT __stdcall FAKE_IDirect3DDevice8::ResourceManagerDiscardBytes(DWORD Bytes)
{
	return pD3DDevice8->ResourceManagerDiscardBytes(Bytes);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetDeviceCaps(D3DCAPS8* pCaps)
{
	return pD3DDevice8->GetDeviceCaps(pCaps);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetDisplayMode(D3DDISPLAYMODE* pMode)
{
	return pD3DDevice8->GetDisplayMode(pMode);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return pD3DDevice8->GetCreationParameters(pParameters);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap)
{
	return pD3DDevice8->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void __stdcall FAKE_IDirect3DDevice8::SetCursorPosition(UINT XScreenSpace, UINT YScreenSpace, DWORD Flags)
{
	pD3DDevice8->SetCursorPosition(XScreenSpace, YScreenSpace, Flags);
}

BOOL __stdcall FAKE_IDirect3DDevice8::ShowCursor(BOOL bShow)
{
	return pD3DDevice8->ShowCursor(bShow);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** ppSwapChain)
{
	return pD3DDevice8->CreateAdditionalSwapChain(pPresentationParameters, ppSwapChain);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return pD3DDevice8->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetBackBuffer(UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer)
{
	return pD3DDevice8->GetBackBuffer(BackBuffer, Type, ppBackBuffer);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus)
{
	return pD3DDevice8->GetRasterStatus(pRasterStatus);
}

void __stdcall FAKE_IDirect3DDevice8::GetGammaRamp(D3DGAMMARAMP* pRamp)
{
	pD3DDevice8->GetGammaRamp(pRamp);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8** ppSurface)
{
	return pD3DDevice8->CreateRenderTarget(Width, Height, Format, MultiSample, Lockable, ppSurface);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8** ppSurface)
{
	return pD3DDevice8->CreateDepthStencilSurface(Width, Height, Format, MultiSample, ppSurface);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateImageSurface(UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface)
{
	return pD3DDevice8->CreateImageSurface(Width, Height, Format, ppSurface);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CopyRects(IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray)
{
	return pD3DDevice8->CopyRects(pSourceSurface, pSourceRectsArray, cRects, pDestinationSurface, pDestPointsArray);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::UpdateTexture(IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture)
{
	return pD3DDevice8->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetFrontBuffer(IDirect3DSurface8* pDestSurface)
{
	return pD3DDevice8->GetFrontBuffer(pDestSurface);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetRenderTarget(IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pNewZStencil)
{
	return pD3DDevice8->SetRenderTarget(pRenderTarget, pNewZStencil);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetRenderTarget(IDirect3DSurface8** ppRenderTarget)
{
	return pD3DDevice8->GetRenderTarget(ppRenderTarget);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetDepthStencilSurface(IDirect3DSurface8** ppZStencilSurface)
{
	return pD3DDevice8->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return pD3DDevice8->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return pD3DDevice8->GetTransform(State, pMatrix);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return pD3DDevice8->MultiplyTransform(State, pMatrix);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetViewport(D3DVIEWPORT8* pViewport )
{
	return pD3DDevice8->GetViewport(pViewport);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetMaterial(CONST D3DMATERIAL8* pMaterial)
{
	return pD3DDevice8->SetMaterial(pMaterial);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetMaterial(D3DMATERIAL8* pMaterial)
{
	return pD3DDevice8->GetMaterial(pMaterial);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetLight(DWORD Index, CONST D3DLIGHT8* pLight)
{
	return pD3DDevice8->SetLight(Index, pLight);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetLight(DWORD Index, D3DLIGHT8* pLight)
{
	return pD3DDevice8->GetLight(Index, pLight);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::LightEnable(DWORD LightIndex, BOOL bEnable)
{
	return pD3DDevice8->LightEnable(LightIndex, bEnable);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return pD3DDevice8->GetLightEnable(Index, pEnable);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetClipPlane(DWORD Index, CONST float* pPlane )
{
	return pD3DDevice8->SetClipPlane(Index, pPlane);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetClipPlane(DWORD Index, float* pPlane)
{
	return pD3DDevice8->GetClipPlane(Index, pPlane);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return pD3DDevice8->GetRenderState(State, pValue);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::BeginStateBlock()
{
	return pD3DDevice8->BeginStateBlock();
}

HRESULT __stdcall FAKE_IDirect3DDevice8::EndStateBlock(DWORD* pToken)
{
	return pD3DDevice8->EndStateBlock(pToken);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::ApplyStateBlock(DWORD Token)
{
	return pD3DDevice8->ApplyStateBlock(Token);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CaptureStateBlock(DWORD Token)
{
	return pD3DDevice8->CaptureStateBlock(Token);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DeleteStateBlock(DWORD Token)
{
	return pD3DDevice8->DeleteStateBlock(Token);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateStateBlock(D3DSTATEBLOCKTYPE Type, DWORD* pToken)
{
	return pD3DDevice8->CreateStateBlock(Type, pToken);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetClipStatus(CONST D3DCLIPSTATUS8* pClipStatus)
{
	return pD3DDevice8->SetClipStatus(pClipStatus);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetClipStatus(D3DCLIPSTATUS8* pClipStatus)
{
	return pD3DDevice8->GetClipStatus(pClipStatus);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetTexture(DWORD Stage, IDirect3DBaseTexture8** ppTexture)
{
	return pD3DDevice8->GetTexture(Stage, ppTexture);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return pD3DDevice8->GetTextureStageState(Stage, Type, pValue);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
{
	return pD3DDevice8->SetTextureStageState(Stage, Type, Value);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::ValidateDevice(DWORD* pNumPasses)
{
	return pD3DDevice8->ValidateDevice(pNumPasses);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetInfo(DWORD DevInfoID, VOID* pDevInfoStruct, DWORD DevInfoStructSize)
{
	return pD3DDevice8->GetInfo(DevInfoID, pDevInfoStruct, DevInfoStructSize);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return pD3DDevice8->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return pD3DDevice8->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return pD3DDevice8->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetCurrentTexturePalette(UINT* pPaletteNumber)
{
	return pD3DDevice8->GetCurrentTexturePalette(pPaletteNumber);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pD3DDevice8->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pD3DDevice8->DrawIndexedPrimitiveUP(PrimitiveType, MinIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags)
{
	return pD3DDevice8->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, Flags);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreateVertexShader(CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* pHandle, DWORD Usage)
{
	return pD3DDevice8->CreateVertexShader(pDeclaration, pFunction, pHandle, Usage);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetVertexShader(DWORD Handle)
{
	return pD3DDevice8->SetVertexShader(Handle);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetVertexShader(DWORD* pHandle)
{
	return pD3DDevice8->GetVertexShader(pHandle);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DeleteVertexShader(DWORD Handle)
{
	return pD3DDevice8->DeleteVertexShader(Handle);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetVertexShaderConstant(DWORD Register, CONST void* pConstantData, DWORD  ConstantCount)
{
	return pD3DDevice8->SetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetVertexShaderConstant(DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return pD3DDevice8->GetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetVertexShaderDeclaration(DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return pD3DDevice8->GetVertexShaderDeclaration(Handle, pData, pSizeOfData);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetVertexShaderFunction(DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return pD3DDevice8->GetVertexShaderFunction(Handle, pData, pSizeOfData);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride)
{
	return pD3DDevice8->GetStreamSource(StreamNumber, ppStreamData, pStride);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetIndices(IDirect3DIndexBuffer8* pIndexData, UINT BaseVertexIndex)
{
	return pD3DDevice8->SetIndices(pIndexData, BaseVertexIndex);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetIndices(IDirect3DIndexBuffer8** ppIndexData, UINT* pBaseVertexIndex)
{
	return pD3DDevice8->GetIndices(ppIndexData, pBaseVertexIndex);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::CreatePixelShader(CONST DWORD* pFunction, DWORD* pHandle)
{
	return pD3DDevice8->CreatePixelShader(pFunction, pHandle);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetPixelShader(DWORD Handle)
{
	return pD3DDevice8->SetPixelShader(Handle);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetPixelShader(DWORD* pHandle)
{
	return pD3DDevice8->GetPixelShader(pHandle);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DeletePixelShader(DWORD Handle)
{
	return pD3DDevice8->DeletePixelShader(Handle);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::SetPixelShaderConstant(DWORD Register, CONST void* pConstantData, DWORD ConstantCount)
{
	return pD3DDevice8->SetPixelShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetPixelShaderConstant(DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return pD3DDevice8->GetPixelShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::GetPixelShaderFunction(DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return pD3DDevice8->GetPixelShaderFunction(Handle, pData, pSizeOfData);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return pD3DDevice8->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return pD3DDevice8->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT __stdcall FAKE_IDirect3DDevice8::DeletePatch(UINT Handle)
{
	return pD3DDevice8->DeletePatch(Handle);
}

void __stdcall FAKE_IDirect3DDevice8::SetCursorPosition(INT X, INT Y, DWORD Flags)
{
	pD3DDevice8->SetCursorPosition(X, Y, Flags);
}