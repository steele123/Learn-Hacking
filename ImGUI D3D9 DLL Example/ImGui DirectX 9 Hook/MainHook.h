#pragma once
#include "Includes.h"

extern bool init_hook;
extern HWND window;
extern void* pDevice[119];
extern PTR EndSceneAddress;
extern EndScene oEndScene;
extern WNDPROC oWndProc;
extern bool bInit;
extern bool bRunning;

namespace MainHook
{
	void Init(HMODULE hModule);
	void Shutdown();
	long __stdcall hkEndScene(LPDIRECT3DDEVICE9 device);
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}