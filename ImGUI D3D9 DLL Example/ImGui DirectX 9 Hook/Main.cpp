#include "Includes.h"
#include "MainHook.h"
#include "Constants.h"
#include "msgsend.h"

HWND window;
void* pDevice[119];
PTR EndSceneAddress;
EndScene oEndScene;
WNDPROC oWndProc;

void InitImGui(IDirect3DDevice9* pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

bool bInit = false;
bool bShow = false;

long __stdcall MainHook::hkEndScene(LPDIRECT3DDEVICE9 device)
{
	if (!bInit)
	{
		bInit = true;
		InitImGui(device);
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		bShow = !bShow;
	}

	if (GetAsyncKeyState(VK_DELETE) & 1) {
		oEndScene(device);
		MainHook::Shutdown();
		bRunning = false;
		return 0;
	}

	if (bShow) {
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("DLL Example", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Hello World.");
		if (ImGui::CollapsingHeader(("Info"), ImGuiTreeNodeFlags_DefaultOpen)) {
			std::stringstream ss;

			__time64_t sysTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			struct tm pTime;
			localtime_s(&pTime, &sysTime);
			char timeInString[60] = { 0 };
			sprintf_s(timeInString, "%d-%02d-%02d %02d:%02d:%02d",
				(int)pTime.tm_year + 1900,
				(int)pTime.tm_mon + 1,
				(int)pTime.tm_mday,
				(int)pTime.tm_hour,
				(int)pTime.tm_min,
				(int)pTime.tm_sec);
			ss << "  Current Time : " << timeInString;
			ImGui::Text(ss.str().c_str());
			ss.str("");

			ss << "  Build Version : " << buildVersion;
			ImGui::Text(ss.str().c_str());
			ss.str("");

			ss << "  Author : " << "U";
			ImGui::Text(ss.str().c_str());
			ss.str("");

			ss << "  Discord : " << "https://discord.gg/discord";
			ImGui::Text(ss.str().c_str());
			ss.str("");

			ss << "  Website : " << "https://example.com";
			ImGui::Text(ss.str().c_str());
			ss.str("");
		}
		if (ImGui::CollapsingHeader("Test Help Markers")) {
			ImGui::Button("Test");
			ImGui::SameLine(); HelpMarker("This is a help marker.");
		}
		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	return oEndScene(device);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall MainHook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainHook::Init, hMod, 0, nullptr));
		break;
	case DLL_PROCESS_DETACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainHook::Shutdown, hMod, 0, nullptr);
		break;
	}
	return TRUE;
}