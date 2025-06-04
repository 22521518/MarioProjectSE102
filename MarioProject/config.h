#pragma once

constexpr const wchar_t* WINDOW_CLASS_NAME = L"MarioWindow"; 
constexpr const wchar_t* MAIN_WINDOW_TITLE = L"Mario Project";
constexpr const wchar_t* WINDOW_ICON_PATH = L"mario.ico"; 

constexpr int SCREEN_WIDTH = 16 * 17;// 320;              
constexpr int SCREEN_HEIGHT = 16 * 15 - 5; // 240;             

constexpr int MAX_FRAME_RATE = 60;           
constexpr int KEYBOARD_BUFFER_SIZE = 1024;     
constexpr int KEYBOARD_STATE_SIZE = 256;