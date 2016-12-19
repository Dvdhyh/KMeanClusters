#include "HeaderMaster.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT iCmdShow){
	WNDCLASS wcex;
	//wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wcex);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HWND hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Playing around with K mean"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		0,            // initial y position
		CW_USEDEFAULT,            // initial x size
		0,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(9001));

	hInstance = hInstance;

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	static GdiplusStartupInput gdiplusStartupInput;
	static ULONG_PTR           gdiplusToken;
	static DrawScreen _DC;
	static RECT _windowRect;

	switch (message) {
	case WM_CREATE: {
		//Set Window Size
		MoveWindow(hWnd, 0, 0, 700, 700, false);

		//Initilize GDI+ library
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		//Get default window size
		GetClientRect(hWnd, &_windowRect);

		_DC.setWindowSize(_windowRect);

		//Select how many groups to sort data points into 
		_DC._CG.setK(3);

		//Select how many data points to randomly generate. Generate k number of random points to start K points
		_DC._CG.GenerateData(20);

		//Random sort into random groups
		_DC._CG.SortIntoClusters();

		break;
	}
	case WM_LBUTTONDOWN:{//When the left mouse button is clicked
		
		//Re sort the data points into different clusters
		_DC._CG.SortIntoClusters();

		//Generate new K points
		_DC._CG.setKPoints();

		//Display messageBox when K mean Points are the same as previous round
		/*
		if (_DC._CG.checkPreviousKPoints()) 
			MessageBox(NULL, "Optimum Cluster group set found", "Title", NULL);
		*/
		
		InvalidateRect(hWnd, NULL, true);
		break;
	}
	case WM_RBUTTONDOWN: {
		//Clear all data
		_DC._CG.clearAll();

		//Generate another set of random data points
		_DC._CG.GenerateData();

		//Sort into random clusters
		_DC._CG.SortIntoClusters();

		InvalidateRect(hWnd, NULL, true);
		break;
	}
	case WM_SIZE: {
		//If window is re sized, update values in classes
		GetClientRect(hWnd, &_windowRect);
		_DC.setWindowSize(_windowRect);
		break;
	}
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		// Parse the menu selections:

		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_PAINT:{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...

		//Draw on window screen
		_DC.PaintOnScreen(hdc);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		GdiplusShutdown(gdiplusToken);
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}