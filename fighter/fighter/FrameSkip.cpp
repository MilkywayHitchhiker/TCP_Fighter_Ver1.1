/////////////////////////////////////////////////////////////////////
// www.gamecodi.com						이주행 master@gamecodi.com
//
//
/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// FrameSkip 클래스.
//
// 별로 기능이 많은 클래스는 아니나, 게임에 자주 쓰이므로
// 클래스로 제작하였다.
// 
// WIN32 환경에서 사용되도록 제작되으므로 다른 OS 에서는 사용할 수 없다.
// WIN32 의 멀티미디어 타이머인 timeGetTime() 함수를 이용하여 
// 프레임 속도를 맞춘다.
///////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <Windows.h>
#include <timeapi.h>

#include "FrameSkip.h"


///////////////////////////////////////////////////////////////////////////
// 생성자, 파괴자.
//
// Parameters: (int) 죄대 프레임.
// Return: 없음.
///////////////////////////////////////////////////////////////////////////
CFrameSkip::CFrameSkip(int iMaxFPS)
{
	///////////////////////////////////////////////////////////////////////////
	// 프레임 저장...  한 프레임당 Tick 값 계산.
	///////////////////////////////////////////////////////////////////////////
	StartFrame = timeGetTime();
	FrameRate = 1000 / iMaxFPS;
}

CFrameSkip::~CFrameSkip()
{

}

///////////////////////////////////////////////////////////////////////////
// 프레임 스킵을 위한 함수.
// 게임의 메인 루프중 그리기 부분을 이 함수로 체크하여 TRUE 가 떨어질 경우에만
// 그리기를 실행하며, FALSE 가 나오게 되면 그리지 않고 그냥 넘어간다.
///////////////////////////////////////////////////////////////////////////
BYTE CFrameSkip::FrameSkip(void)
{
	//첫 시작.
	if ( StartFrame == 0 )
	{
		StartFrame = GetTickCount64 ();
		return true;
	}

	NowFrame = GetTickCount64 ();

	//프레임이 끝나야 되는 시간을 계산
	EndFrame = StartFrame + FrameRate;

	//한 프레임이 StartFrame + 20ms 보다 작다면 Sleep 으로 프레임을 20ms만큼 지연시킴
	if ( NowFrame <= EndFrame )
	{
		Sleep (EndFrame - NowFrame);
		StartFrame = EndFrame;
		return true;
	}
	else if ( NowFrame > EndFrame )
	{
		StartFrame = NowFrame;
		return false;
	}

}

