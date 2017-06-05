// fighter.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "fighter.h"

/////////////////////////////////////////////////////////////////////
// WinMain.cpp
//
// Windows 의 기본 함수들.............
// 
/////////////////////////////////////////////////////////////////////
#include "CommonInclude.h"
#include <windowsx.h>
#include <TimeAPI.h>
#include "DefineEnum.h"
#include "Main.h"
#include "Network.h"

#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Imm32.lib")

/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
// WinMain 사용 전역 변수.
/////////////////////////////////////////////////////////////////////
HWND		g_hWnd = NULL;
HINSTANCE	g_hInstance = NULL;
BOOL		g_bActiveApp = TRUE; //비 활성화 게임 키 입력 무시WM_ACTIVATE

WCHAR		g_szIP[16];


/////////////////////////////////////////////////////////////////////
// 윈도우 초기화. 
/////////////////////////////////////////////////////////////////////
BOOL InitialWindow (HINSTANCE hInstance, WNDPROC WndProc, WCHAR* pAppName)
{
	WNDCLASSEX WndClassEx;
	HWND hWnd;

	WndClassEx.cbSize = sizeof (WNDCLASSEX);
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor (NULL, IDC_ARROW);
	WndClassEx.hbrBackground = ( HBRUSH )GetStockObject (BLACK_BRUSH);
	WndClassEx.lpszMenuName = NULL;
	WndClassEx.lpszClassName = pAppName;
	WndClassEx.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

	RegisterClassEx (&WndClassEx);


	hWnd = CreateWindowEx (0,
		pAppName,
		pAppName,
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL);


	if ( hWnd == NULL ) return FALSE;

	g_hWnd = hWnd;
	g_hInstance = hInstance;

	ShowWindow (hWnd, SW_SHOW);
	UpdateWindow (hWnd);
	SetFocus (hWnd);


	RECT WindowRect;


	SetRect (&WindowRect, 0, 0, dfSCREEN_WIDTH, dfSCREEN_HEIGHT); //현재 윈도우 스타일에서 실제 윈도우 싸이즈

	AdjustWindowRectEx (&WindowRect,
		GetWindowStyle (g_hWnd),
		GetMenu (g_hWnd) != NULL,
		GetWindowExStyle (g_hWnd)); //MSDN에 없음.


	int iX = (GetSystemMetrics (SM_CXSCREEN) - dfSCREEN_WIDTH) >> 1; //화면의 크기를 얻어서 정 중앙으로
	int iY = (GetSystemMetrics (SM_CYSCREEN) - dfSCREEN_HEIGHT) >> 1;

	MoveWindow (g_hWnd, iX, iY,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top, TRUE);


	return TRUE;

}




/////////////////////////////////////////////////////////////////////
// 윈도우 프로시져.
/////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( iMsg )
	{
	case dfNETWORK_UM:
		//---------------------------------------------------------------
		// 네트워크 메시지
		//---------------------------------------------------------------
		if ( !netNetworkProc (wParam, lParam) )
		{
			MessageBox (hWnd, L"접속이 종료되었습니다.",L"", MB_OK);
			PostQuitMessage (0);
		}
		break;

	case WM_ACTIVATEAPP:
		g_bActiveApp = ( BOOL )wParam; //wParam에 TRUE가 들어오면 활성화.
		break;

	case WM_IME_KEYDOWN:
		//------------------------------------------------------------
		// IME 셋팅 관련.
		//------------------------------------------------------------
		//------------------------------------------------------------
		// 한글입력 창을 없에기 위해서.. 무조건 영문모드로 만든다.
		//------------------------------------------------------------
		HIMC hIMC;
		//------------------------------------------------------------
		// IME 의 핸들을 얻고서..
		//------------------------------------------------------------
		hIMC = ImmGetContext (hWnd);
		//------------------------------------------------------------
		// IME_CMODE_ALPHANUMERIC 으로 셋딩.
		//------------------------------------------------------------
		ImmSetConversionStatus (hIMC, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);
		ImmReleaseContext (hWnd, hIMC);
		//------------------------------------------------------------
		break;

	case WM_DESTROY:
		//------------------------------------------------------------
		// 게임 리소스 정리
		//------------------------------------------------------------
		GameRelease ();

		//------------------------------------------------------------
		// 윈속 정리
		//------------------------------------------------------------
		netCleanUp ();

		timeEndPeriod (1);

		PostQuitMessage (0);
		break;

	}

	return DefWindowProc (hWnd, iMsg, wParam, lParam);
}





//////////////////////////////////////////////////////////////////
// Dialog 프로시져.
//////////////////////////////////////////////////////////////////
INT_PTR CALLBACK DialogProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEditBox;

	switch ( iMsg )
	{
	case WM_INITDIALOG:
		memset (g_szIP, 0, 16);

		//---------------------------------------------------------------
		// 기본 윈도우 IP 주소 입력  127.0.0.1
		//---------------------------------------------------------------
		hEditBox = GetDlgItem (hWnd, IDC_EDIT1);
		SetWindowText (hEditBox, L"127.0.0.1");
		return TRUE;


	case WM_COMMAND:

		switch ( wParam )
		{
		case IDOK:
			//---------------------------------------------------------------
			// 전송 버튼 눌릴때 에디트 창의 내용 전송.
			//---------------------------------------------------------------
			GetDlgItemText (hWnd, IDC_EDIT1, g_szIP, 16);
			EndDialog (hWnd, TRUE);
			return TRUE;
			break;
		}
		break;
	}
	return FALSE;
}






/////////////////////////////////////////////////////////////////////
// 메인 
/////////////////////////////////////////////////////////////////////
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MSG				msg;

	//------------------------------------------------------------
	// timeGetTime() 함수의 정교한 체크를 위한 설정.
	//------------------------------------------------------------
	timeBeginPeriod (1);

	//------------------------------------------------------------
	// 스프라이트 로드
	//------------------------------------------------------------
	if ( !GameInit () )
	{
		DestroyWindow (g_hWnd);
		return 1;
	}

	//------------------------------------------------------------
	// 아이피 입력을 위한 다이알로그를 생성한다.
	//------------------------------------------------------------
	DialogBox (hInstance, MAKEINTRESOURCE (IDD_DIALOG1), NULL, DialogProc);

	//------------------------------------------------------------
	// 윈도우를 생성한다.
	//------------------------------------------------------------
	if ( !InitialWindow (hInstance, WndProc, L"TCP_FIGHTER") )
	{
		DestroyWindow (g_hWnd);
	}




	//------------------------------------------------------------
	// 윈속 초기화.
	//------------------------------------------------------------
	if ( !netStartUp () )
	{
		DestroyWindow (g_hWnd);
	}

	//------------------------------------------------------------
	// WSAAsyncSelect 등록.
	//------------------------------------------------------------
	if ( !netSetAsyncSelect (g_hWnd) )
	{
		DestroyWindow (g_hWnd);
	}

	//------------------------------------------------------------
	// 서버로 접속 시도.
	//------------------------------------------------------------
	if ( !netConnect (g_szIP) )
	{
		DestroyWindow (g_hWnd);
	}


	while ( 1 )
	{
		if ( PeekMessage (&msg, NULL, 0, 0, PM_REMOVE) )
		{
			if ( msg.message == WM_QUIT )
				break;

			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
		else
		{
			//------------------------------------------------------------
			// 접속 처리가 되어야만 게임을 진행하자
			//------------------------------------------------------------
			if ( g_netConnect )
				Main ();
		}
	}
	return 1;
}
