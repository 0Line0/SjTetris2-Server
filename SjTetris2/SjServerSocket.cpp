// SjServerSocket.cpp: 구현 파일
//

#include "pch.h"
#include "SjTetris2.h"
#include "SjServerSocket.h"


// CSjServerSocket

CSjServerSocket::CSjServerSocket()
{
}

CSjServerSocket::~CSjServerSocket()
{
}


// CSjServerSocket 멤버 함수


void CSjServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pWnd->SendMessage(UM_ACCEPT);

	CSocket::OnAccept(nErrorCode);
}


bool CSjServerSocket::ServerStart(CWnd* pWnd, int nPortNo)
{
	// TODO: 여기에 구현 코드 추가.
	m_pWnd = pWnd;
	if (!Create(nPortNo))
		return false;
	if (!Listen())
		return false;
	return true;
}
