#include <Windows.h>
#include <thread>
#include "resource.h"

bool ProgramRunning = true;

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

void BackGroundTask() {

	while (ProgramRunning) {



	}

}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(CLIENT), NULL, DlgProc, 0);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg = {};

	std::thread Background = std::thread(BackGroundTask);

	while (1) {
		GetMessage(&msg, hWnd, 0, 0);
		TranslateMessage(&msg);
		DispatchMessageA(&msg);

	}

	ProgramRunning = false;

	if (Background.joinable()) {

		Background.join();

	}

	return (int)msg.wParam;

}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	switch (Msg) {

	case WM_INITDIALOG:
		return 0;

	case WM_COMMAND:
		switch (wParam) {

		case DISPLAY_QR:
			//DisplayQR(std::string(USERID) + ".bmp");
			return 0;

		case CREDENTIALS:
			//DisplayCredentials();
			return 0;

		case ABOUT:
			//DisplayAuthors();
			return 0;

		case CLOSE:
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			return 0;

		default:
			return 0;
		}

		return 0;

	case WM_CLOSE:
		//Close();
		SendMessage(hWnd, WM_QUIT, wParam, lParam);
		return 0;

	case WM_QUIT:
		::exit(0);
		return 0;

	default:
		return 0;

	}


	return DefDlgProcA(hWnd, Msg, wParam, lParam);

}