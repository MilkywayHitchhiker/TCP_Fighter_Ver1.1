/////////////////////////////////////////////////////////////////////
// www.gamecodi.com						������ master@gamecodi.com
//
//
/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// FrameSkip Ŭ����.
//
// ���� ����� ���� Ŭ������ �ƴϳ�, ���ӿ� ���� ���̹Ƿ�
// Ŭ������ �����Ͽ���.
// 
// WIN32 ȯ�濡�� ���ǵ��� ���۵����Ƿ� �ٸ� OS ������ ����� �� ����.
// WIN32 �� ��Ƽ�̵�� Ÿ�̸��� timeGetTime() �Լ��� �̿��Ͽ� 
// ������ �ӵ��� �����.
///////////////////////////////////////////////////////////////////////////
#include<Windows.h>
#ifndef _FRAME_SKIPING_
#define _FRAME_SKIPING_

class CFrameSkip
{
protected:

	DWORD StartFrame;
	DWORD EndFrame;
	DWORD NowFrame;


	DWORD FrameRate;


public:

	///////////////////////////////////////////////////////////////////////////
	// ������, �ı���.
	//
	// Parameters: (int) �˴� ������.
	// Return: ����.
	///////////////////////////////////////////////////////////////////////////
	CFrameSkip(int iMaxFPS);
	~CFrameSkip();

	///////////////////////////////////////////////////////////////////////////
	// ������ ��ŵ�� ���� �Լ�.
	// ������ ���� ������ �׸��� �κ��� �� �Լ��� üũ�Ͽ� TRUE �� ������ ��쿡��
	// �׸��⸦ �����ϸ�, FALSE �� ������ �Ǹ� �׸��� �ʰ� �׳� �Ѿ��.
	///////////////////////////////////////////////////////////////////////////
	BYTE			FrameSkip(void);

};

#endif