#pragma once
#include "PlayScene.h"
#include "config.h"
#include "debug.h"
#include "stringUtil.h"
#include "FileConfig.h"

#include <fstream>
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <dinput.h>
#include <unordered_map>
#include <string>
#include <vector>

//#define DIRECTINPUT_VERSION 0x0800

using namespace std;
class CTexture; typedef CTexture* LPTEXTURE;
class CGameKeyHandler; typedef CGameKeyHandler* LPGAMEKEYHANDLER;

class CGame
{
	// for moving object from bonus
	bool isReturnToExisting = false;
	int px = 0, py = 0;

	static CGame* __instance;
	HWND hWnd = nullptr;
	HINSTANCE hInstance = nullptr;

	// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferWidth = 0;
	int backBufferHeight = 0;

	// Direct3D graphics objects
	ID3D10Device* pD3DDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D10RenderTargetView* pRenderTargetView = nullptr;
	ID3D10BlendState* pBlendStateAlpha = nullptr;
	ID3D10SamplerState* pPointSamplerState = nullptr;
	LPD3DX10SPRITE spriteObject = nullptr;

	// DirectInput related objects (DirectInput object, keyboard, keyboard state buffer, keyboard data)
	LPDIRECTINPUT8 di = nullptr;
	LPDIRECTINPUTDEVICE8 didv = nullptr;
	BYTE keyStates[KEYBOARD_STATE_SIZE]{ 0 };
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE]{ 0 };
	LPGAMEKEYHANDLER keyHandler = nullptr; // Our keyboard event handler

	// Camera position
	float cam_x = 0.0f;
	float cam_y = 0.0f;

	// Scene management
	unordered_map<int, LPSCENE> scenes;
	int currentScene;
	int nextScene = -1;

	// Parse data from file
	void _ParseSection_SETTINGS(SettingConfig setting);
	void _ParseSection_SCENES(vector<SceneConfig> scenes);
	void _ParseSection_TEXTURES(vector<TextureConfig> textures);

	CGame() {};

public:
	void Init(HWND hWnd, HINSTANCE hInstance);
	static CGame* GetInstance();
	~CGame();

	LPTEXTURE LoadTexture(LPCWSTR texturePath);
	void SetPointSamplerState();

	// Draw a portion or ALL the texture at position (x,y) on the screen. (x,y) is at the CENTER of the image
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = nullptr, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0);
	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0);

	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode) const;
	void ProcessKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler);

	// Scene management
	void SwitchScene();
	LPSCENE GetCurrentScene() const;
	void InitiateSwitchScene(int sceneId);
	void InitiateSwitchSceneFromBonus(int sceneId, int px, int py);
	void Load(LPCWSTR gameFile);

	// Camera management
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) const { x = cam_x; y = cam_y; }

	// Direct3D getters and setters
	int GetBackBufferWidth() const { return backBufferWidth; }
	int GetBackBufferHeight() const { return backBufferHeight; }
	ID3D10Device* GetDirect3DDevice() const { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() const { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() const { return this->pRenderTargetView; }
	ID3DX10Sprite* GetSpriteHandler() const { return this->spriteObject; }
	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };
};