#include "setup.h"
#include "config.h"
#include "gameLoop.h"
#include "GameKeyHandler.h"
#include "KeyMap.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT,
		WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE, WINDOW_ICON_PATH);

	CGame::GetInstance()->Init(hWnd, hInstance);
	// Init keyboard
	CGame::GetInstance()->InitKeyboard();
	// Load game resources
	CGame::GetInstance()->Load(L"mario-sample.txt");


	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	Run();

	return 0;
}