#pragma once
#include "Graphics.h"

using namespace Microsoft::WRL;

namespace graphics
{
	class CGraphicDevice_DX11
	{
	public:
		CGraphicDevice_DX11(ValidationMode validationMode = ValidationMode::Disabled);
		~CGraphicDevice_DX11();

		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc);
		bool CreateTextur(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D);

		bool CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT NumElements, const void* byteCode, SIZE_T bytecodeLength, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer);
		bool CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppVertexShader);
		bool CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);
		bool CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerdesc, ID3D11RasterizerState** ppRasterizerState);
		bool CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencildesc, ID3D11DepthStencilState** ppDepthStencilState);
		bool CreateBlendState(const D3D11_BLEND_DESC* pBlenddesc, ID3D11BlendState** ppBlendState);

		void BindPrivitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindVertexBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		void BindVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances);
		void BindPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances);
		void BindViewPorts(D3D11_VIEWPORT* viewPort);
		void BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void SetConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void SetShaderResource(eShaderStage stage, UINT slot, ID3D11ShaderResourceView* const* ppShaderResourceViews);
		void BindSamplers(eShaderStage stage, UINT slot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
		void BindsSamplers(UINT slot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
		void BindRasterizerState(ID3D11RasterizerState* pRasterizerState);
		void BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState);
		void BindBlendState(ID3D11BlendState* pBlendState);

		void Clear();
		void AdjustViewPorts();

		void Draw();
		void DrawIndexed(UINT indexCount, UINT StartIndexLocation, UINT BaseVertexLocation);

		void Present();

		ID3D11Device* GetID3D11Device() { return mDevice.Get(); }

	private:
		// GPU ???? ???? ???????????? ???????? ????????????
		ComPtr <ID3D11Device> mDevice;
		// GPU read write ?????????? ???? ???????? ???? ?? ?????? ???? GPU?? ?????? ??????
		ComPtr <ID3D11DeviceContext> mContext;

		// ?????????? ???????? ??????
		ComPtr <ID3D11Texture2D> mRenderTarget;
		// ???????? ?????? ???????????? ???? (????????X View?? ???? ????????)
		ComPtr <ID3D11RenderTargetView> mRenderTargetView; // ???? ???? ???? ???? - iter ???? ????

		ComPtr <ID3D11Texture2D> mDepthStencilBuffer;
		// ?????????? ?K ?????? ?????? ???????????? ????
		ComPtr <ID3D11DepthStencilView> mDepthStencilView;

		// ?????? ?????????? ????????
		// ??????(Frame Buffer)?? ????????, ?????? ?????? ?????? ????
		// ?????? ???????? ????
		ComPtr <IDXGISwapChain> mSwapChain;

		// ?????? ???????? ????????.
		// ???????????? (???????? ????)
		//ID3D11SamplerState* mSampler;

		D3D11_VIEWPORT mViewPort;
	};

	inline CGraphicDevice_DX11*& GetDevice()
	{
		static CGraphicDevice_DX11* device = nullptr;
		return device;
	}
}

