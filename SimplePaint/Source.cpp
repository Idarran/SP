//SimplePaint//

//Wybór koloru?
//Tryb prostej linii?
//Czyszczenie okna

#include <windows.h>
#include <cmath>

//#define KOLOR RGB(255,0,0)

void onMove(HWND, LPARAM);

bool isDown = false;

POINT pozycja; //struktura na punkt, zawieraj¹ca zmienne x i y

HWND window;
HDC hdc;

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
		
		case WM_RBUTTONDOWN:
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
			break;

		case WM_LBUTTONDOWN:
			isDown = true;
			pozycja.x = LOWORD(lp);
			pozycja.y = HIWORD(lp);
			return 0;

		case WM_LBUTTONUP:
			if (isDown)
			{
				hdc = GetDC(hwnd);
				MoveToEx(hdc, pozycja.x, pozycja.y, NULL);
				LineTo(hdc, LOWORD(lp), HIWORD(lp));
				ReleaseDC(hwnd, hdc);
			}
			isDown = false;
			return 0;

		case WM_MOUSEMOVE:
			if (isDown & MK_LBUTTON)
			{
				hdc = GetDC(hwnd);
				MoveToEx(hdc, pozycja.x, pozycja.y, NULL);
				LineTo(hdc, pozycja.x = LOWORD(lp),
					pozycja.y = HIWORD(lp));
				ReleaseDC(hwnd, hdc);
			}
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, message, wp, lp);
		}
		return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = wnd_proc;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_SHIELD); //IDI_SHIELD
	wc.hIconSm = LoadIcon(NULL, IDI_SHIELD);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "SimplePaint";

	RegisterClassEx(&wc);

	window = CreateWindowEx(0, "SimplePaint", "PA - SimplePaint",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 10, 10, 750, 750, NULL, NULL, hInstance, NULL);

	if (!window) return -1;

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

/*void on_paint(HWND hwnd, LPARAM lp)
{
	static PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0)); 
	SelectObject(ps.hdc, hpen);
	hdc = GetDC(hwnd);
	MoveToEx(hdc, pozycja.x, pozycja.y, NULL);
	LineTo(hdc, pozycja.x = LOWORD(lp), pozycja.y = HIWORD(lp));
	ReleaseDC(hwnd, hdc);
	SelectObject(ps.hdc, GetStockObject(NULL_PEN));
	DeleteObject(hpen);
	EndPaint(hwnd, &ps);
}
*/

/*void pisakOn(HWND hwnd, LPARAM lp)
{
	static PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);
	HPEN hpen = CreatePen(PS_SOLID, 3, KOLOR);
	SelectObject(ps.hdc, hpen);
	hdc = GetDC(hwnd);
	MoveToEx(hdc, pozycja.x, pozycja.y, NULL);
	LineTo(hdc, pozycja.x = LOWORD(lp),	pozycja.y = HIWORD(lp));
	ReleaseDC(hwnd, hdc);
	SelectObject(ps.hdc, GetStockObject(NULL_PEN));
	DeleteObject(hpen);
	EndPaint(hwnd, &ps);
}*/

