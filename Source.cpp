#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include "resource.h"

TCHAR szClassName[] = TEXT("nostr_client");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit1;
	static HWND hEdit2;
	static HWND hEdit3;
	static HWND hButton1;
	switch (msg)
	{
	case WM_CREATE:
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", 0, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 10, 512, 32, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", 0, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 50, 512, 32, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit3 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", 0, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_AUTOHSCROLL | ES_AUTOHSCROLL | ES_MULTILINE, 10, 90, 512, 256, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton1 = CreateWindowEx(0, L"BUTTON", L"submit", WS_CHILD | WS_VISIBLE, 10, 50, 256, 32, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_SIZE:
		MoveWindow(hEdit1, 10, 10, 512, 32, FALSE);
		MoveWindow(hEdit2, 10, 50, 512, 32, FALSE);
		MoveWindow(hEdit3, 10, 90, 512, 256, FALSE);
		MoveWindow(hButton1, 10, 90 + 256 + 10, 128, 32, FALSE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			WCHAR szPublicKey[256];
			GetWindowText(hEdit1, szPublicKey, _countof(szPublicKey));
			WCHAR szPrivateKey[256];
			GetWindowText(hEdit2, szPrivateKey, _countof(szPrivateKey));
			DWORD dwSize = GetWindowTextLength(hEdit3);
			LPWSTR lpszMessage = (LPWSTR)GlobalAlloc(0, sizeof(WCHAR) * (dwSize + 1));
			GetWindowText(hEdit3, lpszMessage, dwSize + 1);
			// ここに投稿用の処理を記述

			GlobalFree(lpszMessage);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)),
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Nostr Client"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
