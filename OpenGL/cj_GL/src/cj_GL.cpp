#include "..\glad\glad.c"

bool running = true;

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam);
HWND setupWindow(HINSTANCE instance);


int WINAPI WinMain(HINSTANCE Instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
	HWND hwnd = setupWindow(Instance);

	HDC dc = GetDC(hwnd);
	MSG msg = {};

	unsigned int *pixels = 0;
	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize 		= sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth 		= 800;
	bmi.bmiHeader.biHeight 		= 600;
	bmi.bmiHeader.biPlanes 		=   1;
	bmi.bmiHeader.biBitCount 	=  32;
	bmi.bmiHeader.biCompression 	= BI_RGB;



	pixels = (unsigned int*)VirtualAlloc(0, sizeof(unsigned int) * 800 * 600, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);


	glViewport(0, 0, 800, 600);
	

	while(running)
	{
		while(PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		unsigned int *pixel = pixels;
		for (int y = 0; y < 600; y++)
		{
			for (int x = 0; x < 800; x++)
			{
				*pixel++ = 0xff4400;	
			}
		}


		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		StretchDIBits(dc, 0, 0, 800, 600,
			      0, 0, 800, 600, 
			      pixels, &bmi, DIB_RGB_COLORS, SRCCOPY);  
	}

	return msg.wParam;
}



LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam)
{
	switch(msg)
	{
		case WM_DESTROY:
		{
			running = false;
		}
	}

	return DefWindowProc(hwnd, msg, WParam, LParam);
}

HWND setupWindow(HINSTANCE instance)
{
	WNDCLASSEX wc = {};

	wc.cbSize	 =	sizeof(WNDCLASSEX);
	wc.style	 = 	CS_OWNDC;
  	wc.lpfnWndProc	 = 	&wndProc;
  	wc.cbClsExtra	 = 	0;
  	wc.cbWndExtra	 = 	0;
  	wc.hInstance	 = 	instance;
  	wc.hIcon	 = 	0;
  	wc.hCursor	 = 	0;
  	wc.hbrBackground = 	HBRUSH(GetStockObject(BLACK_BRUSH));
  	wc.lpszMenuName	 = 	"cj_GL";
  	wc.lpszClassName = 	"cj_GL_Class";

	if(!RegisterClassEx(&wc))
	{
		MessageBox(0, "Register Window Fail", "Failed to Register Window",  MB_OK);
	}

	RECT rc = {0, 0, 800, 600};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, 0);

	HWND hwnd = CreateWindowEx(0, "cj_GL_Class", "cj_GL", WS_OVERLAPPEDWINDOW, 
				   0, 0, rc.right - rc.left, rc.bottom - rc.top,
				   0, 0, instance, 0);
	if(!hwnd)
	{
		MessageBox(0, "Create Window Fail", "Failed to Create Window",  MB_OK);
	}

	ShowWindow(hwnd, SW_SHOW);

	return hwnd;
}
