#include "setup.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight, const wchar_t* windowClassName, const wchar_t* windowTitle, const wchar_t* iconPath)
{
	WNDCLASSEX wc;

	// (Required)
	wc.cbSize = sizeof(WNDCLASSEX); // Size of the window class
	wc.style = CS_HREDRAW | CS_VREDRAW; // Redraw window when resized horizontally or vertically
	wc.hInstance = hInstance; // Instance handle to associate window
	wc.lpfnWndProc = (WNDPROC)WinProc;// The window procedure that handles messages
	wc.cbClsExtra = 0; // Extra bytes for class
	wc.cbWndExtra = 0; // Extra bytes for window
	wc.lpszClassName = windowClassName; // Identify the window class

	// (Optional)
	wc.hIcon = (HICON)LoadImage(hInstance, iconPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE); // Custom icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Custom cursor
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Background color (DEFAULT: transparency)
	wc.lpszMenuName = NULL; // Menu name
	wc.hIconSm = NULL; // Small icon

	// (Required)
	RegisterClassEx(&wc); //Register with the system
	HWND hWnd =
		CreateWindow(
			windowClassName,
			windowTitle,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL
		);

	// (Required) 
	if (!hWnd)
	{
		// (Optional) Log error message
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();

		return FALSE;
	}

	// (Required) 
	ShowWindow(hWnd, nCmdShow); // Show the window with the specified show state
	UpdateWindow(hWnd); // Force window to be redrawn immediately

	return hWnd;
}