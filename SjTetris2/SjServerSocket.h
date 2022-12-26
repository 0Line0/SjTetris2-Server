#pragma once

// CSjServerSocket 명령 대상
#define UM_ACCEPT (WM_USER + 2)
class CSjServerSocket : public CSocket
{
public:
	CSjServerSocket();
	virtual ~CSjServerSocket();
private:
	CWnd* m_pWnd;
public:
	virtual void OnAccept(int nErrorCode);
	bool ServerStart(CWnd* pWnd, int nPortNo);
};


