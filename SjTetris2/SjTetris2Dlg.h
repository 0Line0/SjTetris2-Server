
// SjTetris2Dlg.h: 헤더 파일
//

#pragma once
#define COL_CNT 10
#define ROW_CNT 20
#define START_X 10
#define START_Y 10
#define BLOCK_SIZE 32
#define START_X2 550
#define START_Y2 10

#define ZeroMemory RrlZeroMemory
#define RrlZeroMemory(destionation,Length) memset((Destination),0,(Length))

#include "SjServerSocket.h"
#include "SjClientSocket.h"


// CSjTetris2Dlg 대화 상자
class CSjTetris2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CSjTetris2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SJTETRIS2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	CBitmap m_bmBlock;
	CBitmap m_bmBack;
	CDC m_BackDC;
	CDC m_BlockDC;

	CDC* m_pDC;
	char m_Table[ROW_CNT][COL_CNT];
	CRect m_nextRect;
	CRect m_mainRect;
	int m_nPattern;
	int m_nBitType;
	int m_nX;
	int m_nY;
	int m_nRot;
	bool m_bStart;
	void DrawScr();
	void InitialGame();
	void DrawBlock(bool bFlag);
	bool BlockDown();
	bool IsAround(int nX, int nY);
	void SetTable();
	void RotateBlock(bool bFlag);
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	afx_msg void OnClickedStartButton();
	afx_msg void OnClickedStopButton();
	afx_msg void OnClickedExitButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_ctrlStartBt;
	CButton m_ctrlStopBt;
	
	void DrawNextBlock(bool bFlag);
	int m_nNextPattern;
	CBitmap m_NextBack;
	CDC m_NextDC;



	CBitmap m_bmBlock2;
	CBitmap m_bmBack2;
	CDC m_BackDC2;
	CDC m_BlockDC2;
	CDC* m_pDC2;
	char m_Table2[ROW_CNT][COL_CNT];
	CRect m_nextRect2;
	CRect m_mainRect2;
	bool m_bStart2;
	int m_nPattern2;
	int m_nBitType2;
	int m_nRot2;
	//int m_nX2;
	//int m_nY2;

	void DrawScr2();
	void DrawBlock2(bool bFlag);
	

	CButton m_ctrlSendBt;
	CButton m_ctrlConnectBt;
	CButton m_ctrlDisconnectBt;
	int m_nPortNo;
	CEdit m_ctrlReceiveData;
	CStringW m_strReceiveData;
	CEdit m_ctrlSendData;
	CStringW m_strSendData;

	afx_msg void OnClickedConnectBt();
	afx_msg void OnClickedDisconnectBt();
	afx_msg void OnClickedSendBt();
	afx_msg LRESULT OnAcceptMsg(WPARAM wParam, LPARAM IParam);
	afx_msg LRESULT OnReceiveMsg(WPARAM wParam, LPARAM IParam);
	CSjServerSocket m_Server;
	CSjClientSocket m_Client;
	CObList m_List;
	LRESULT OnCloseMsg(WPARAM wParam, LPARAM IParam);
	bool BroadCast(void* pStr);
	CStringW m_strName;
	CListBox m_ctrlUserList;
	CStringW m_strUserList;
	void UserList(CString strUser, char nFlag);
	CButton m_ctrlForcedBt;
	afx_msg void OnClickedForcedExitBt();
	CStringW m_strIpAddress;
	CEdit m_ctrlIpAddress;
};
