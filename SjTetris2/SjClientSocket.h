#pragma once

// CSjClientSocket 명령 대상
#define UM_RECEIVE (WM_USER + 1)
#define UM_SOCKET_CLOSE (WM_USER + 3)

class CSjClientSocket : public CSocket
{
public:
	CSjClientSocket();
	virtual ~CSjClientSocket();
private:
	CWnd* m_pWnd;
public:
	bool m_bFlag;
	bool m_bConnect;
	void SetMainWindow(CWnd* pWnd);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CString m_strName;
};


