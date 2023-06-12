#include <Windows.h>
#include "../imgui/imgui.h"
#include <vector>
#include <d3d9.h>
//#include "settings.h"
#include "../Gui/gui.h"
#include "../Font/byte_array.h"
#include <dwmapi.h>
#include "sdk.hpp"
#include <string>
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

IDirect3D9Ex* p_object = NULL;
IDirect3DDevice9Ex* p_device = NULL;
D3DPRESENT_PARAMETERS p_params = { NULL };
HWND game_wnd = NULL;
RECT game_rect = { NULL };

MSG messager = { NULL };
HWND win = NULL;

HRESULT directx_init()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_object)))
		exit(3);
	ZeroMemory(&p_params, sizeof(p_params));
	p_params.Windowed = TRUE;
	p_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_params.hDeviceWindow = win;
	p_params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_params.BackBufferWidth = Width;
	p_params.BackBufferHeight = Height;
	p_params.EnableAutoDepthStencil = TRUE;
	p_params.AutoDepthStencilFormat = D3DFMT_D16;
	p_params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	if (FAILED(p_object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, win, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_params, 0, &p_device)))
	{
		p_object->Release();
		exit(4);
	}

	gui::setup(p_device, win);

	p_object->Release();
	return S_OK;
}

#define VK_W		0x57
#define VK_A		0x41
#define VK_S		0x53
#define VK_D		0x44
#define VK_SPACE    0x20
#define VK_R			0x52

namespace Offsets
{
	uintptr_t PlayerState = 0x2A8; //APlayerState*
	uintptr_t PersistentLevel = 0x30; //ULevel*
}

float color_red = 1.;
float color_green = 0;
float color_blue = 0;
float color_random = 0.0;
float color_speed = -10.0;

struct player
{

	uint64_t Actor;
	uint64_t Mesh;
	uint64_t RootComp;
	bool valid;
	bool IsOnScreen;
	bool enemy;
	bool isbot;
};


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct item
{

	uint64_t Actor;
	uint64_t Mesh;
	uint64_t RootComp;
	bool IsOnScreen;

};

std::vector<player> player_pawns;
std::vector<item> item_pawns;

bool vsyncenable = true;

void cleanup_d3d()
{
	if (p_device != NULL)
	{
		p_device->EndScene();
		p_device->Release();
	}
	if (p_object != NULL)
	{
		p_object->Release();
	}
}
//
//RECT GameRect = { NULL };
//D3DPRESENT_PARAMETERS d3dpp;
//const MARGINS Margin = { -1 };
//
//void SetWindowToTarget()
//{
//	while (true)
//	{
//		if (game_wnd)
//		{
//			ZeroMemory(&GameRect, sizeof(GameRect));
//			GetWindowRect(game_wnd, &GameRect);
//			Width = GameRect.right - GameRect.left;
//			Height = GameRect.bottom - GameRect.top;
//			DWORD dwStyle = GetWindowLong(game_wnd, GWL_STYLE);
//
//			if (dwStyle & WS_BORDER)
//			{
//				GameRect.top += 32;
//				Height -= 39;
//			}
//
//			MoveWindow(win, GameRect.left, GameRect.top, Width, Height, true);
//		}
//		else
//		{
//			exit(0);
//		}
//	}
//}
//
//LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
//{
//	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
//		return true;
//
//	switch (Message)
//	{
//	case WM_DESTROY:
//		cleanup_d3d();
//		PostQuitMessage(0);
//		exit(4);
//		break;
//	case WM_SIZE:
//		if (p_device != NULL && wParam != SIZE_MINIMIZED)
//		{
//			ImGui_ImplDX9_InvalidateDeviceObjects();
//			d3dpp.BackBufferWidth = LOWORD(lParam);
//			d3dpp.BackBufferHeight = HIWORD(lParam);
//			HRESULT hr = p_device->Reset(&d3dpp);
//			if (hr == D3DERR_INVALIDCALL)
//				IM_ASSERT(0);
//			ImGui_ImplDX9_CreateDeviceObjects();
//		}
//		break;
//	default:
//		return DefWindowProc(hWnd, Message, wParam, lParam);
//		break;
//	}
//	return 0;
//}

void create_overlay()
{
	//while (true) {
	//	game_wnd = FindWindowA("UnrealWindow", "Fortnite  ");
	//	if (game_wnd)
	//		break;
	//}

	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);
	//ShowWindow(win, SW_SHOW);

	//WNDCLASSEX wc;
	//ZeroMemory(&wc, sizeof(wc));
	//wc.cbSize = sizeof(wc);
	//wc.lpszClassName = "Overlay";
	//wc.lpfnWndProc = WinProc;
	//RegisterClassEx(&wc);

	//GetClientRect(game_wnd, &GameRect);
	//POINT xy;
	//ClientToScreen(game_wnd, &xy);
	//GameRect.left = xy.x;
	//GameRect.top = xy.y;

	//Width = GameRect.right;
	//Height = GameRect.bottom;

	//win = CreateWindowEx(NULL, "Overlay", "Overlay Util", WS_POPUP | WS_VISIBLE, 0, 0, Width, Height, 0, 0, 0, 0);

	//DwmExtendFrameIntoClientArea(win, &Margin);
	//SetWindowLong(win, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	//ShowWindow(win, SW_SHOW);
	//UpdateWindow(win);

	//NOTIFYICONDATA nid = {};
	//nid.cbSize = sizeof(NOTIFYICONDATA);
	//nid.hWnd = NULL;
	//nid.uID = 1;
	//nid.uFlags = NIF_INFO;
	//nid.dwInfoFlags = NIIF_INFO;
	//strcpy_s(nid.szInfoTitle, "External Notification");
	//strcpy_s(nid.szInfo, "Created Overlay Window");
	//Shell_NotifyIcon(NIM_ADD, &nid);
	//Sleep(5000);
	//Shell_NotifyIcon(NIM_DELETE, &nid);

	win = FindWindowA(("CEF-OSC-WIDGET"), ("NVIDIA GeForce Overlay"));
	if (!win)
	{
		Sleep(5000);
		exit(1);
	}

	ShowWindow(win, SW_SHOW);

	SetWindowLongA(win, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	SetWindowLongA(
		win,
		-20,
		static_cast<LONG_PTR>(
			static_cast<int>(GetWindowLongA(win, -20)) | 0x20
			)
	);

	//transparency
	MARGINS margin = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea(
		win,
		&margin
	);

	SetLayeredWindowAttributes(
		win,
		NULL,
		0xFF,
		0x02
	);

	// top most
	SetWindowPos(
		win,
		HWND_TOPMOST,
		0, 0, 0, 0,
		0x0002 | 0x0001
	);



	UpdateWindow(win);


}


void DrawFilledRect(int x, int y, int w, int h, ImU32 color)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

static auto DrawNormalBox(int x, int y, int w, int h, int borderPx, ImU32 color) -> void
{
	DrawFilledRect(x + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x + w - w + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h, color); //left 
	DrawFilledRect(x, y + h - h + borderPx * 2, borderPx, h, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w - w + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);//right 
}

void draw_cornered_box(int X, int Y, int W, int H, const ImU32& color, int thickness, int borderPx) {
	float lineW = (W / 3);
	float lineH = (H / 3);
	DrawFilledRect(X + borderPx, Y, W, borderPx, ImColor(10, 10, 10, 180));

	//black outlines
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

ImFont* infoF;

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

void DrawNewTextCustom2(int x, int y, int R, int G, int B, int A, const char* str)
{
	//ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	//ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
	ImGui::GetForegroundDrawList()->AddText(infoF, 18.0f, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(R / 255.0, G / 255.0, B / 255.0, A / 255.0)), utf_8_2.c_str());
}

std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}


typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

void DrawString(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 2;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), color, text.c_str());
}

class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA redlol = { 255,0,0,200 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA cyan = { 0,255,255,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 100,0,0,0 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 100,000, 000, 000 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 221,160,221,160 };

	RGBA VisibleColor = { 255 / 255, 0, 0 };
	RGBA InvisibleColor = { 0, 255 / 255, 0 };
	RGBA FilledFov = { 0,0,0,160 };

	RGBA rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}

		float rainbow_speed = 0.25f;

		x += rainbow_speed; //increase this value to switch colors faster
		if (x >= 255.0f)
			x = 0.0f;

		y += rainbow_speed; //increase this value to switch colors faster
		if (y > 1530.0f)
			y = 0.0f;


		return RGBA{ (DWORD)r, (DWORD)g, (DWORD)b, 255 };
	}


};
static Color Col;


namespace fn {
	enum bones
	{
		crown = 106,
		head = 68,
		neck = 67,
		chest = 7,
		leftshoulder = 38,
		leftbicep = 65,
		leftelbow = 39,
		leftwrist = 62,
		lefthand = 53,
		rightshoulder = 9,
		rightbicep = 35,
		rightelbow = 10,
		rightwrist = 34,
		righthand = 16,
		pelvis = 2,
		lefthip = 78,
		leftthigh = 84,
		leftcalf = 79,
		leftjoint = 87,
		leftfoot = 83,
		righthip = 71,
		rightthigh = 74,
		rightcalf = 86,
		rightjoint = 75,
		rightfoot = 76,
		root = 0,
	};

}

VOID SkeletonESP(uintptr_t mesh, ImColor SkeletonColor, bool fingers)
{
	Vector3 crown, head, neck, chest, leftshoulder, leftbicep, leftelbow, leftwrist, lefthand, rightshoulder, rightbicep, rightelbow, rightwrist, righthand, penis, leftthigh, lefthip, leftcalf, leftjoint, leftfoot, righthip, rightthigh, rightcalf, rightjoint, rightfoot;
	crown = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::crown));
	head = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::head));
	neck = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::neck));
	chest = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::chest));
	leftshoulder = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftshoulder));
	leftbicep = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftbicep));
	leftelbow = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftelbow));
	leftwrist = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftwrist));
	lefthand = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::lefthand));
	rightshoulder = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightshoulder));
	rightbicep = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightbicep));
	rightelbow = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightelbow));
	rightwrist = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightwrist));
	righthand = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::righthand));
	penis = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::pelvis));
	lefthip = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::lefthip));
	leftthigh = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftthigh));
	leftcalf = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftcalf));
	leftjoint = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftjoint));
	leftfoot = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::leftfoot));
	righthip = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::righthip));
	rightthigh = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightthigh));
	rightcalf = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightcalf));
	rightjoint = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightjoint));
	rightfoot = ProjectWorldToScreen(GetBoneWithRotation(mesh, fn::bones::rightfoot));

	if (fingers)
	{
		//right hand in lobby
		Vector3 RHandWrist, rti, rbi, rbbi, rmt, rmb, rmbb, rrb, rrm, rrt, rpb, rpm, rpt, rtb, rtm, rtt;

		//left hand in lobby
		Vector3 LHandWrist, lti, lbi, lbbi, lmb, lmm, lmt, lrb, lrm, lrt, lpb, lpm, lpt, ltb, ltm, ltt;

		RHandWrist = ProjectWorldToScreen(GetBoneWithRotation(mesh, 33));
		rti = ProjectWorldToScreen(GetBoneWithRotation(mesh, 13));
		rbi = ProjectWorldToScreen(GetBoneWithRotation(mesh, 14));
		rbbi = ProjectWorldToScreen(GetBoneWithRotation(mesh, 15));
		rmt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 17));
		rmb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 18));
		rmbb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 19));
		rrb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 25));
		rrm = ProjectWorldToScreen(GetBoneWithRotation(mesh, 26));
		rrt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 27));
		rpb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 21));
		rpm = ProjectWorldToScreen(GetBoneWithRotation(mesh, 22));
		rpt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 23));
		rtb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 28));
		rtm = ProjectWorldToScreen(GetBoneWithRotation(mesh, 29));
		rtt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 30));

		LHandWrist = ProjectWorldToScreen(GetBoneWithRotation(mesh, 62));
		lti = ProjectWorldToScreen(GetBoneWithRotation(mesh, 42));
		lbi = ProjectWorldToScreen(GetBoneWithRotation(mesh, 43));
		lbbi = ProjectWorldToScreen(GetBoneWithRotation(mesh, 44));
		lmb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 46));
		lmm = ProjectWorldToScreen(GetBoneWithRotation(mesh, 47));
		lmt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 48));
		lrb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 54));
		lrm = ProjectWorldToScreen(GetBoneWithRotation(mesh, 55));
		lrt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 56));
		lpb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 49));
		lpm = ProjectWorldToScreen(GetBoneWithRotation(mesh, 50));
		lpt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 51));
		ltb = ProjectWorldToScreen(GetBoneWithRotation(mesh, 57));
		ltm = ProjectWorldToScreen(GetBoneWithRotation(mesh, 58));
		ltt = ProjectWorldToScreen(GetBoneWithRotation(mesh, 59));


		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightwrist.x, rightwrist.y), ImVec2(RHandWrist.x, RHandWrist.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RHandWrist.x, RHandWrist.y), ImVec2(righthand.x, righthand.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(righthand.x, righthand.y), ImVec2(rti.x, rti.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rti.x, rti.y), ImVec2(rbi.x, rbi.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rbi.x, rbi.y), ImVec2(rbbi.x, rbbi.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(righthand.x, righthand.y), ImVec2(rmt.x, rmt.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rmt.x, rmt.y), ImVec2(rmb.x, rmb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rmb.x, rmb.y), ImVec2(rmbb.x, rmbb.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(righthand.x, righthand.y), ImVec2(rrb.x, rrb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rrb.x, rrb.y), ImVec2(rrm.x, rrm.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rrm.x, rrm.y), ImVec2(rrt.x, rrt.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(righthand.x, righthand.y), ImVec2(rpb.x, rpb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rpb.x, rpb.y), ImVec2(rpm.x, rpm.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rpm.x, rpm.y), ImVec2(rpt.x, rpt.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(righthand.x, righthand.y), ImVec2(rtb.x, rtb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rtb.x, rtb.y), ImVec2(rtm.x, rtm.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rtm.x, rtm.y), ImVec2(rtt.x, rtt.y), SkeletonColor, 2.f);


		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftwrist.x, leftwrist.y), ImVec2(LHandWrist.x, LHandWrist.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LHandWrist.x, LHandWrist.y), ImVec2(lefthand.x, lefthand.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lefthand.x, lefthand.y), ImVec2(lti.x, lti.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lti.x, lbi.y), ImVec2(lbi.x, lbi.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lbi.x, lbi.y), ImVec2(lbbi.x, lbbi.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lefthand.x, lefthand.y), ImVec2(lmb.x, lmb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lmb.x, lmb.y), ImVec2(lmm.x, lmm.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lmm.x, lmm.y), ImVec2(lmt.x, lmt.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lefthand.x, lefthand.y), ImVec2(lrb.x, lrb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lrb.x, lrb.y), ImVec2(lrm.x, lrm.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lrm.x, lrm.y), ImVec2(lrt.x, lrt.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lefthand.x, lefthand.y), ImVec2(lpb.x, lpb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lpb.x, lpb.y), ImVec2(lpm.x, lpm.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lpm.x, lpm.y), ImVec2(lpt.x, lpt.y), SkeletonColor, 2.f);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lefthand.x, lefthand.y), ImVec2(ltb.x, ltb.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ltb.x, ltb.y), ImVec2(ltm.x, ltm.y), SkeletonColor, 2.f);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ltm.x, ltm.y), ImVec2(ltt.x, ltt.y), SkeletonColor, 2.f);
	}

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(crown.x, crown.y), ImVec2(head.x, head.y), SkeletonColor, 2.f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head.x, head.y), ImVec2(neck.x, neck.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(neck.x, neck.y), ImVec2(chest.x, chest.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(leftshoulder.x, leftshoulder.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftshoulder.x, leftshoulder.y), ImVec2(leftbicep.x, leftbicep.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftbicep.x, leftbicep.y), ImVec2(leftelbow.x, leftelbow.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftelbow.x, leftelbow.y), ImVec2(leftwrist.x, leftwrist.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftwrist.x, leftwrist.y), ImVec2(lefthand.x, lefthand.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(rightshoulder.x, rightshoulder.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightshoulder.x, rightshoulder.y), ImVec2(rightbicep.x, rightbicep.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightbicep.x, rightbicep.y), ImVec2(rightelbow.x, rightelbow.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightelbow.x, rightelbow.y), ImVec2(rightwrist.x, rightwrist.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightwrist.x, rightwrist.y), ImVec2(righthand.x, righthand.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(penis.x, penis.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(penis.x, penis.y), ImVec2(lefthip.x, lefthip.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lefthip.x, lefthip.y), ImVec2(leftthigh.x, leftthigh.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftthigh.x, leftthigh.y), ImVec2(leftcalf.x, leftcalf.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftcalf.x, leftcalf.y), ImVec2(leftjoint.x, leftjoint.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftjoint.x, leftjoint.y), ImVec2(leftfoot.x, leftfoot.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(penis.x, penis.y), ImVec2(righthip.x, righthip.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(righthip.x, righthip.y), ImVec2(rightthigh.x, rightthigh.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightthigh.x, rightthigh.y), ImVec2(rightcalf.x, rightcalf.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightcalf.x, rightcalf.y), ImVec2(rightjoint.x, rightjoint.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightjoint.x, rightjoint.y), ImVec2(rightfoot.x, rightfoot.y), SkeletonColor, 2.0f);
} 



bool IsInScreen(Vector3 pos, int over = 30) {
	if (pos.x > -over && pos.x < Width + over && pos.y > -over && pos.y < Height + over) {
		return true;
	}
	else {
		return false;
	}
}

void gui::setup(LPDIRECT3DDEVICE9 device, HWND window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui 

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	bold_segu = io.Fonts->AddFontFromMemoryTTF(&bold_segue, sizeof bold_segue, 30, NULL, io.Fonts->GetGlyphRangesCyrillic());
	io.Fonts->AddFontFromFileTTF("C:\\Arial.ttf", 15.0f);
	FN = io.Fonts->AddFontFromFileTTF("C:\\Arial.ttf", 15.0f);
	io.FontDefault = FN;

	is_setup = true;
}
