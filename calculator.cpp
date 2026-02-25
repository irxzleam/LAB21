#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define PLUS 1
#define MIN 2
#define MUL 3
#define DIV 4
HWND Textbox1,Textbox2,textfield;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	char szClassName[]="TextEntry";
	switch(Message) {
		case WM_CREATE:
		Textbox1 = CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,40,60,160,20,hwnd,NULL,NULL,NULL);
		Textbox2 = CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,40,85,160,20,hwnd,NULL,NULL,NULL);
		textfield = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE | WS_CHILD | WS_BORDER,20,20,200,30,hwnd,NULL,NULL,NULL);
		
		CreateWindow("BUTTON","+",WS_VISIBLE | WS_CHILD | WS_BORDER,40,120,30,30,hwnd,(HMENU)PLUS,NULL,NULL);
		CreateWindow("BUTTON","-",WS_VISIBLE | WS_CHILD | WS_BORDER,80,120,30,30,hwnd,(HMENU)MIN,NULL,NULL);
		CreateWindow("BUTTON","*",WS_VISIBLE | WS_CHILD | WS_BORDER,120,120,30,30,hwnd,(HMENU)MUL,NULL,NULL);
		CreateWindow("BUTTON","/",WS_VISIBLE | WS_CHILD | WS_BORDER,160,120,30,30,hwnd,(HMENU)DIV,NULL,NULL);
		break;
		
		case WM_COMMAND:
		{
		char t1[20],t2[20],t[100];
		double n1,n2,result=0;

		GetWindowText(Textbox1, t1, 20);
        GetWindowText(Textbox2, t2, 20);
		
		n1 = atof(t1);
        n2 = atof(t2);

			switch(LOWORD(wParam))
			{
				case PLUS:
				result=n1+n2;
				break;

				case MIN:
				result=n1-n2;
				break;

				case MUL:
				result=n1*n2;
				break;

				case DIV:
				//if(n2 != 0)
				result=n1/n2;
				break;

				default: return 0;
			}
			sprintf(t, "%f", result);
            MessageBox(hwnd, t, "Result", MB_OK);
		break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(50, 220, 150));;
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
