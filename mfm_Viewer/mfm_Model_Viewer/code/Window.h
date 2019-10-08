#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "DrawData.h"
#include "Grid.h"
#include "Draw_model.h"

class Window
{
public:
	Window();
	~Window();
	HWND Create(HWND hWnd, HINSTANCE hInstance, int nCmdShow);
	void Delete();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool ChangeDisplay(HINSTANCE hInstance, HWND hWnd);
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //ウィンドウプロシージャ
	static void KeyBoardDown(WPARAM, HWND);
	bool ChangeDevice(HINSTANCE hInstance, HWND hWnd, bool NewScreen);

	DirectX* Device;
	Grid main_grid;
	Draw_model Render_Draw;
	static DATA_TYPE::MFMMESHDATA model;
	static bool Model_Change;
	static bool DisplayMode;
	static bool Press;
	static bool Blur;

	const char* Class_Name = "  ";
	const char* Window_Name = "  ";
	const int Screen_Width_Size = 1280;
	const int Screen_Hiegth_Size = 720;
};

