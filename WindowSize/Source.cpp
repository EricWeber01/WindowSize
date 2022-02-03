#include<Windows.h>
#include<tchar.h>
namespace glb 
{
	int margin = 10;
	TCHAR str[128], inf[128], winInfo[128];
	INT x, y, width, height;
}
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassWindow[] = TEXT("Framework Application");
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(
		0,
		szClassWindow,
		TEXT("My second window"),
		WS_OVERLAPPEDWINDOW,
		800,
		200,
		500,
		300,
		NULL,
		NULL,
		hInst,
		NULL
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:

		glb::x = LOWORD(lParam);
		glb::y = HIWORD(lParam);

		if (glb::x > glb::margin && glb::x < clientRect.right - glb::margin && glb::y > glb::margin && glb::y < clientRect.bottom - glb::margin)
			wcscpy_s(glb::inf, TEXT("IN"));

		else if (glb::x < glb::margin || glb::x > clientRect.right - glb::margin || glb::y < glb::margin || glb::y > clientRect.bottom - glb::margin)
			wcscpy_s(glb::inf, TEXT("OUT"));

		else if (glb::x == glb::margin && glb::y > glb::margin && glb::y < clientRect.bottom - glb::margin
			|| glb::x == clientRect.right - glb::margin && glb::y > glb::margin && glb::y < clientRect.bottom - glb::margin
			|| glb::y == glb::margin && glb::x > glb::margin && glb::x < clientRect.right - glb::margin
			|| glb::y == clientRect.bottom - glb::margin && glb::x > glb::margin && glb::x < clientRect.right - glb::margin)
			wcscpy_s(glb::inf, TEXT("BORDER"));

		wsprintf(glb::str, TEXT("%s"), glb::inf);
		SetWindowText(hWnd, glb::str);
		break;

	case WM_RBUTTONDOWN:
		glb::width = clientRect.right;
		glb::height = clientRect.bottom;
		wsprintf(glb::winInfo, TEXT("width: %d        height: %d"), glb::width, glb::height);
		SetWindowText(hWnd, glb::winInfo);
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}