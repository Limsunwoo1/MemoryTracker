// GameFramework.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GameFramework.h"
#include "MainGame.h"
#include "MemoryAllocator.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND Hwnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;
    msg.message = NULL;

#ifdef USE_MEMORY_TRACE
    CMemoryTracer::GetInstance()->GetInstance()->Init();
    SetCustomMemoryAllocator();
#endif

    CMainGame::GetInstance()->Init(Hwnd, hInstance);

    HDC hdc = GetDC(Hwnd);

    while (msg.message != WM_QUIT)
    {
        // GetMessage 를 사용하면 메시지 큐에서 매번 메시지를 가져와서
        // 해당 메시지를 분석하는 과정이 필요한데
        // PeekMessage는 메시지큐를 관찰만한다
        // 그래서 메시지 분석에 걸리는 시간이 훨씬 적고
        // 무엇보다 겟 메시지를 쓰면 메시지가 없을땐 동작하지 않음
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        CMainGame::GetInstance()->Logic();
    }

    CMainGame::GetInstance()->Clear();
    CMainGame::GetInstance()->DestroyInstance();

#ifdef USE_MEMORY_TRACE
    DestoryMemoryAllocator();
    CMemoryTracer::GetInstance()->DestroyInstance();
#endif

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEFRAMEWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = L"Test";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(L"Test", L"Test", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 980, 680, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   Hwnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

#ifdef USE_MEMORY_TRACE

extern IMemoryAllocator* GMemoryAllocator;
extern IMemoryAllocator* GPrevMemoryAllocator;

void* operator new(size_t InSize)
{
    if (!GMemoryAllocator)
        return malloc(InSize);

    return GMemoryAllocator->New(InSize);
}

void operator delete(void* InAddress)
{
    if (!GMemoryAllocator)
        return free(InAddress);

    return GMemoryAllocator->Delete(InAddress);
}
#endif