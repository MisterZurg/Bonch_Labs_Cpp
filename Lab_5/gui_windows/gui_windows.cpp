#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string>

using namespace std;

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Windows Desktop");

HINSTANCE hInst;
int lastBmp = 0;
WORD xPosEx = 0, yPosEx = 0;

void MyFileDialog(int conf)
{
	OPENFILENAME OpenFileName = { 0 };
	TCHAR FilePath[MAX_PATH] = L"";
	ZeroMemory(&OpenFileName, sizeof(OpenFileName));
	OpenFileName.lStructSize = sizeof(OpenFileName);
	OpenFileName.lpstrFilter = L"All Files (*.*)\0*.*\0 Text Files (*.txt)\0*.txt";
	OpenFileName.lpstrFile = FilePath;
	OpenFileName.nMaxFile = MAX_PATH;
	OpenFileName.Flags = OFN_EXPLORER | OFN_FORCESHOWHIDDEN;

	switch (conf)
	{
	case 1:
		if (GetOpenFileName(&OpenFileName))
		{
			return;
		}
		break;
	case 2:
		if (GetSaveFileName(&OpenFileName))
		{
			return;
		}
		break;
	}
}

void DrawBitmap(HWND hWnd, int lastBmp, int x = 0, int y = 0)
{
	HDC hDC, hCompatibleDC;
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;
	RECT rect;
	LPWSTR name = (LPWSTR)L"";

	switch (lastBmp)
	{
	case 5:
		name = (LPWSTR)L"switch.bmp";
		break;
	case 6:
		name = (LPWSTR)L"hub.bmp";
		break;
	case 7:
		name = (LPWSTR)L"router.bmp";
		break;
	case 8:
		name = (LPWSTR)L"workstation.bmp";
		break;
	}

	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, 1);
	UpdateWindow(hWnd);

	hDC = GetDC(hWnd);

	hBitmap = LoadImage(hInst, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
	hCompatibleDC = CreateCompatibleDC(hDC);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	StretchBlt(hDC, x, y, 300, 300, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	SelectObject(hCompatibleDC, hOldBitmap);

	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);

	ReleaseDC(hWnd, hDC);
}

LRESULT CALLBACK WndProc(
	_In_ HWND hWnd,
	_In_ UINT message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	PAINTSTRUCT ps;
	HDC hdc;

	string position;
	WORD xPos = 0, yPos = 0;

	HANDLE FileHandle, FileHandle2;
	OFSTRUCT fileInfo;

	int size, flag;
	string result;
	wchar_t res[100];
	string pos, tmp = "";
	char Buf[10], Buf2[10];

	switch (message)
	{
	case WM_CREATE:
		HFILE initFile;

		initFile = OpenFile("info.txt", &fileInfo, OF_READ);
		ReadFile((HANDLE)initFile, Buf, sizeof(Buf), NULL, NULL);

		MultiByteToWideChar(CP_UTF8, 0, Buf, -1, res, sizeof(res) / 2);
		lastBmp = (int)Buf[0] - (int)'0';
		CloseHandle((HANDLE)initFile);

		initFile = OpenFile("info1.txt", &fileInfo, OF_READ);
		ReadFile((HANDLE)initFile, Buf2, sizeof(Buf2), NULL, NULL);
		CloseHandle((HANDLE)initFile);

		tmp = "";
		flag = 0;
		for (int i = 0; i < sizeof(Buf2); i++)
		{
			if (Buf2[i] == ' ')
			{
				xPos = stoi(tmp);
				tmp = "";
				flag = 1;
				continue;
			}
			else if ((int)Buf2[i] < 0 && flag)
			{
				yPos = stoi(tmp);
				break;
			}
			size = (int)Buf2[i];
			tmp += Buf2[i];
		}

		DrawBitmap(hWnd, lastBmp, xPos, yPos);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		HMENU hMenu1;
		HMENU hSubMenu1;
		HMENU hSubMenu2;

		hMenu1 = CreateMenu();
		hSubMenu1 = CreateMenu();
		hSubMenu2 = CreateMenu();

		AppendMenuW(hSubMenu1, MF_STRING, 1, L"&Open");
		AppendMenuW(hSubMenu1, MF_STRING, 2, L"&Save as");
		AppendMenuW(hSubMenu1, MF_SEPARATOR, 3, NULL);
		AppendMenuW(hSubMenu1, MF_STRING, 4, L"&Exit");
		AppendMenuW(hMenu1, MF_POPUP, (UINT_PTR)hSubMenu1, L"&File");

		AppendMenuW(hSubMenu2, MF_STRING, 5, L"&Switch");
		AppendMenuW(hSubMenu2, MF_STRING, 6, L"&Hub");
		AppendMenuW(hSubMenu2, MF_STRING, 7, L"&Router");
		AppendMenuW(hSubMenu2, MF_STRING, 8, L"&PC");
		AppendMenuW(hMenu1, MF_POPUP, (UINT_PTR)hSubMenu2, L"&Element");

		SetMenu(hWnd, hMenu1);

		EndPaint(hWnd, &ps);

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1:
			MyFileDialog(1);
			break;
		case 2:
			MyFileDialog(2);
			break;
		case 4:

			FileHandle = CreateFile(L"info.txt", GENERIC_READ | GENERIC_WRITE, 0,
				NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			result = to_string(lastBmp);
			WriteFile(FileHandle, result.c_str(), strlen(result.c_str()), NULL, NULL);

			FileHandle2 = CreateFile(L"info1.txt", GENERIC_READ | GENERIC_WRITE, 0,
				NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			pos = to_string(xPosEx) + " " + to_string(yPosEx);
			WriteFile(FileHandle2, pos.c_str(), strlen(pos.c_str()), NULL, NULL);


			CloseHandle(FileHandle);
			CloseHandle(FileHandle2);
			PostQuitMessage(0);

			break;
		case 5:
			lastBmp = 5;
			DrawBitmap(hWnd, lastBmp);
			break;
		case 6:
			lastBmp = 6;
			DrawBitmap(hWnd, lastBmp);
			break;
		case 7:
			lastBmp = 7;
			DrawBitmap(hWnd, lastBmp);
			break;
		case 8:
			lastBmp = 8;
			DrawBitmap(hWnd, lastBmp);
			break;
		}
		break;

	case WM_MOUSEMOVE:
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		position = "X: " + to_string(xPos) + ", " + "Y: " + to_string(yPos);

		SetWindowTextA(hWnd, position.c_str());
		break;

	case WM_LBUTTONDOWN:
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		xPosEx = xPos;
		yPosEx = yPos;

		DrawBitmap(hWnd, lastBmp, xPos - 150, yPos - 150);
		break;

	case WM_DESTROY:
		FileHandle = CreateFile(L"info.txt", GENERIC_READ | GENERIC_WRITE, 0,
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		result = to_string(lastBmp);
		WriteFile(FileHandle, result.c_str(), strlen(result.c_str()), NULL, NULL);

		FileHandle2 = CreateFile(L"info1.txt", GENERIC_READ | GENERIC_WRITE, 0,
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		pos = to_string(xPosEx) + " " + to_string(yPosEx);
		WriteFile(FileHandle2, pos.c_str(), strlen(pos.c_str()), NULL, NULL);


		CloseHandle(FileHandle);
		CloseHandle(FileHandle2);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Windows Desktop"), NULL);

		return 1;
	}
	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1500, 1000, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop"),
			NULL);

		return 1;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
