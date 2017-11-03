/*
PROJECT NAME : SETTrek
FILE NAME	: Graphics.cpp
DESCRIPTION : The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible
for managing the rendertarget.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/
#include "Graphics.h"

/*
Meathod		: Graphics()
DESCRIPTION : the purpose of this method is to act as the constructor of the Graphics class
and the initialize the required variables.
PARAMETERS  : none
RETURNS     : nothing
*/
Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
}

/*
Meathod		: ~Graphics()
DESCRIPTION : the purpose of this method is to act as the destructor for the graphics class.
PARAMETERS  : none
RETURNS     : nothing
*/
Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();

	// Direct2D 1.1
	if (Direct2DBackBuffer) Direct2DBackBuffer->Release();
	if (DXGISwapChain) DXGISwapChain->Release();
	//rendertarget->Release();           // Direct2D 1.0 also (this line only)
	if (Direct2DDevice) Direct2DDevice->Release();
	if (Direct3DContext) Direct3DContext->Release();
	if (Direct3DDevice) Direct3DDevice->Release();
}

/*
Meathod		: Init()
DESCRIPTION : the purose of this method is to setup the rendertarget/factory for our game.
PARAMETERS  : HWND windowHandle
RETURNS     : bool - return status.
*/
bool Graphics::Init(HWND windowHandle)
{

	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, reinterpret_cast<void **>(&factory));

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pDWriteFactory),
		reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
	);

	RECT rect;
	GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size

	// Set feature levels supported by our application
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// Create Direct3D device and context
	ID3D11Device *device;
	ID3D11DeviceContext *context;
	D3D_FEATURE_LEVEL returnedFeatureLevel;

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION,
		&device, &returnedFeatureLevel, &context);

	device->QueryInterface(__uuidof(ID3D11Device1), (void **)&Direct3DDevice);
	context->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&Direct3DContext);

	IDXGIDevice *dxgiDevice;

	Direct3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);

	factory->CreateDevice(dxgiDevice, &Direct2DDevice);

	Direct2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &rendertarget);

	// Get the GPU we are using
	IDXGIAdapter *dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// Get the DXGI factory instance
	IDXGIFactory2 *dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	// Describe Windows 7-compatible Windowed swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	// Create DXGI swap chain targeting a window handle (the only Windows 7-compatible option)
	dxgiFactory->CreateSwapChainForHwnd(Direct3DDevice, windowHandle, &swapChainDesc, nullptr, nullptr, &DXGISwapChain);

	

		// Get the back buffer as an IDXGISurface (Direct2D doesn't accept an ID3D11Texture2D directly as a render target)
		IDXGISurface *dxgiBackBuffer;
	DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));

	FLOAT dpiX, dpiY;
	factory->GetDesktopDpi(&dpiX, &dpiY);

	// Create a Direct2D surface (bitmap) linked to the Direct3D texture back buffer via the DXGI back buffer
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), dpiX, dpiY);

	rendertarget->CreateBitmapFromDxgiSurface(dxgiBackBuffer, &bitmapProperties, &Direct2DBackBuffer);

	// Set surface as render target in Direct2D device context
	rendertarget->SetTarget(Direct2DBackBuffer);

	if (dxgiBackBuffer) dxgiBackBuffer->Release();
	if (dxgiFactory) dxgiFactory->Release();
	if (dxgiAdapter) dxgiAdapter->Release();
	if (dxgiDevice) dxgiDevice->Release();
	if (context) context->Release();
	if (device) device->Release();

	return true;
}

/*
Meathod		: ClearScreen()
DESCRIPTION : the purose of this method is to setup the background color, given the red blue green values.
PARAMETERS  : float r, float g, float b
RETURNS     : nothing
*/
void Graphics::ClearScreen(float r, float g, float b)
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}

/*
Meathod		: GetSwapChain()
DESCRIPTION : the purose of this method is to return the IDXGI swapchain object.
PARAMETERS  : none
RETURNS     : IDXGISwapChain1* swapchain object.
*/
IDXGISwapChain1*  Graphics::GetSwapChain() {

	return DXGISwapChain;
}