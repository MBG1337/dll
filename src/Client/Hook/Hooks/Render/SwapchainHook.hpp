#pragma once

#include "../Hook.hpp"
#include <dxgi1_6.h>

#include <d2d1_3.h>
#include <d3d12.h>
#include <d3d11.h>
#include <d3d11on12.h>

#include "kiero.h"
#include "../../../../SDK/Client/Render/FrameTransform.hpp"

struct FrameContext {
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12Resource* main_render_target_resource = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;
};

class SwapchainHook : public Hook {
private:
    static HRESULT swapchainCallback(IDXGISwapChain3 *pSwapChain, UINT syncInterval, UINT flags);



public:

    static void DX12Blur();

    static void DX11Blur();
    typedef HRESULT(__thiscall *SwapchainOriginal)(IDXGISwapChain3 *, UINT, UINT);

    static inline SwapchainOriginal funcOriginal = nullptr;
    static bool init;

    SwapchainHook();

    void enableHook() override;

    static ID3D12CommandQueue *queue;
    static inline std::vector<IDXGISurface1 *> DXGISurfaces;
    static inline std::vector<ID2D1Bitmap1 *> D2D1Bitmaps;
    static inline std::vector<ID3D11Resource *> D3D11Resources;
    static inline IDXGISwapChain3 *swapchain;
    static inline ID3D12DescriptorHeap *D3D12DescriptorHeap;
    static inline ID3D11On12Device *d3d11On12Device;
    static inline ID2D1Bitmap1 *D2D1Bitmap;
    static inline ID3D11DeviceContext *context;
    static inline ID3D11Device* d3d11Device;
    static inline uintptr_t bufferCount;
    static inline ID3D12GraphicsCommandList* DX12CommandLists;
    static bool hasResized;
    static int currentBitmap;

    static inline ID3D12Device5* d3d12Device5 = nullptr;


    static inline ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiIMAGE = nullptr;
    static inline ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiRender = nullptr;
    static inline ID3D12DescriptorHeap* d3d12DescriptorHeapBackBuffers = nullptr;
    static inline ID3D12GraphicsCommandList* d3d12CommandList = nullptr;
    static inline ID3D12CommandQueue* d3d12CommandQueue = nullptr;
    static inline ID3D12CommandAllocator* allocator = nullptr;

    static inline uint64_t buffersCounts = 0;
    static inline std::vector<FrameContext> frameContexts = {};

    static inline std::queue<FrameTransform> FrameTransforms;
    static inline int transformDelay = 3;

    static inline UINT flagsreal;
};