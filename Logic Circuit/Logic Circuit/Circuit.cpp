#include "myHeader.h"
#include "Classes.h"
#include "Declaration.h"

const WCHAR* nameVar = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int spacing = 20;
const int spacHeight = 17;

int wWidth = 0, wHeight = 0;
int outNum;

std::vector<Cable> cables;
VarIn<Var> vars;
VarIn<Component> components;
std::vector<MapKarn> mapKarns;

void ResolveConnections() 
{
	for (size_t i = 0; i < vars.size(); i++)
	{
		for (Cable& cable : cables)
			if (vars[i].label == cable.label)
				cable.energized = &vars[i].energized;
		}
	for (Cable& cable : cables) {
		if (cable.label != 'z')
			continue;
		for (size_t i = 0; i < components.size(); i++) {
			int x = components[i].x;
			if (components[i].x == cable.x && components[i].yF == cable.y)
			{
				cable.energized = &components[i].energized;
				break;
			}
		}
	}
}

void DrawAll(Graphics& graphics)
{
	Pen pen(Color(0, 0, 0), 2.0F);
	Font font(L"Arial", 12, FontStyleBold);
	SolidBrush brush(Color(0, 0, 0));
	mapKarns[0].Draw(graphics, pen, font, brush);
	//DrawVariables(spacing, vars, wHeight, graphics);
	/*
	for (size_t i = 0; i < components.size(); i++)
		components[i].Draw(graphics);
	for (size_t i = 0; i < cables.size(); i++)
		cables[i].Draw(graphics);
	*/
}

void CreateVarCables()
{
	const int spacLine = spacing * 2;
	for (size_t i = 0; i < vars.size(); i++)
	{
		size_t iX = i + 1;
		bool* bPoint = &vars[i].energized;
		const wchar_t label = vars[i].label+L'\0';
		cables.push_back(Cable(bPoint, label, spacLine * iX, spacHeight, spacLine * iX, wHeight));
		cables.push_back(Cable(bPoint, label, spacLine * iX - spacing, spacHeight * 3, spacLine * iX, spacHeight * 3));
		cables.push_back(Cable(bPoint, label, spacLine * iX - spacing, spacHeight * 3, spacLine * iX - spacing, spacHeight * 5));


		for (size_t j = 0; j < cables.size(); j++)
		{
			if (cables[j].xF == spacLine * iX - spacing && cables[j].yF == spacHeight * 5)
			{
				std::vector<bool*> inEnerzed = { cables[j].energized };
				components.push_back(Component(spacLine * iX - spacing, spacHeight * 5, NOT, inEnerzed));
				break;
			}
		}


		for (size_t z = 0; z < components.size(); z++)
		{
			if (components[z].x == spacLine * iX - spacing && components[z].yF == spacHeight * 5 + szComponent.Height) {
				cables.push_back(Cable(&components[z].energized, wchar_t('z'), spacLine * iX - spacing,
					(spacHeight * 5 + szComponent.Height),
					spacLine * iX - spacing, wHeight));
				break;
			}
		}

	}
}

void Initialization(const HWND hWnd)
{
	RECT wRect;
	if (GetWindowRect(hWnd, &wRect))
	{
		wWidth = wRect.right - wRect.left;
		wHeight = wRect.bottom - wRect.top;
	}
	for (int i = 0; i < 4; i++)
		vars.push_back(Var(nameVar[i], true, Rect(Point(spacing*2 * (i+1)-15, 0), Size(30,18))));
	
	//testing resolver here is the binary expression
	std::vector<int> varsTest {1, 3, 0, 4, 8, 14, 15, 6,11,13};
	mapKarns.emplace_back(varsTest, 4, 20, 20);
	CreateVarCables();
	ResolveConnections();
}

VOID OnPaint(HDC hdc, HWND hWnd)
{
	Graphics graphics(hdc);
	DrawAll(graphics);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("CircuitLogicWin");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("CircuitLogicWin"),  // window class name
		TEXT("Circuit Logic"),    // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	HWND circuit = CreateWindow(
		TEXT("CircuitSimulatorWin"),  // window class name
		TEXT("Circuit Logic Simulator"),    // window caption
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                     // program instance handle
		NULL);                    // creation parameters

	Initialization(hWnd);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		
		//InvalidateRect(hWnd, NULL, NULL);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_PAINT:
		RECT wRect;
		if (GetWindowRect(hWnd, &wRect))
		{
			wWidth = wRect.right - wRect.left;
			wHeight = wRect.bottom - wRect.top;
		}
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc, hWnd);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONUP:
			POINT mPos;
			GetCursorPos(&mPos);
			if (ScreenToClient(hWnd, &mPos))
			{
				Point resolvedP(mPos.x, mPos.y);
				for (size_t i = 0; i < vars.size(); i++)
					if (vars[i].rect.Contains(resolvedP)) {
						vars[i].energized = !vars[i].energized;
					}
			}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc