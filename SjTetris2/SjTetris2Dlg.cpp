
// SjTetris2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SjTetris2.h"
#include "SjTetris2Dlg.h"
#include "afxdialogex.h"
#include "afxcoll.h"
#define DATA_SIZE 200



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

POINT Pattern[7][16] =
{
	{{0,0}, {0,-1}, {-1,0}, {-1,-1}, {0,0}, {0,-1}, {-1,0}, {-1,-1}, //1
	{0,0}, {0,-1}, {-1,0}, {-1,-1}, {0,0}, {0,-1}, {-1,0}, {-1,-1}},

	{{0,0}, {1,0}, {-1,0}, {-2,0}, {0,0}, {0,1}, {0,2}, {0,-1},	//2
	{0,0}, {1,0}, {-1,0}, {-2,0}, {0,0}, {0,1}, {0,2}, {0,-1}},

	{{0,0}, {-1,0}, {0,-1}, {1,-1}, {0,0}, {0,1}, {-1,0}, {-1,-1}, //3
	{0,0}, {-1,0}, {0,-1}, {1,-1}, {0,0}, {0,1}, {-1,0}, {-1,-1}},

	{{0,0}, {-1,-1}, {0,-1}, {1,0}, {0,0}, {-1,0}, {-1,1}, {0,-1},	//4
	{0,0}, {-1,-1}, {0,-1}, {1,0}, {0,0}, {-1,0}, {-1,1}, {0,-1}},////여기까지 완벽

	{{-1,0}, {-1,1}, {0,1}, {1,1}, {0,1}, {1,1}, {1,0}, {1,-1},	//5
	{-1,-1}, {0,-1}, {1,-1}, {1,0}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}},

	{{-1,1}, {0,1}, {1,1}, {1,0}, {0,-1}, {1,-1}, {1,0}, {1,1},	//6
	{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {-1,1}, {-1,0}, {-1,-1}, {0,1}},

	{{0,0}, {-1,0}, {1,0}, {0,1}, {0,0}, {0,-1}, {0,1}, {1,0},	//7
	{0,0}, {-1,0}, {1,0}, {0,-1}, {0,0}, {-1,0}, {0,-1}, {0,1}},




};


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSjTetris2Dlg 대화 상자



CSjTetris2Dlg::CSjTetris2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SJTETRIS2_DIALOG, pParent)
	, m_nPortNo(1234)
	, m_strReceiveData(_T(""))
	, m_strSendData(_T(""))
	, m_strName(_T("관리자"))
	, m_strUserList(_T(""))
	, m_strIpAddress(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nX = COL_CNT / 2;
	m_nY = 0;
	m_nPattern = 0;
	m_nBitType = 1;
	m_nRot = 0;
	m_bStart = FALSE;
	m_mainRect.left = START_X;
	m_mainRect.top = START_Y;
	m_mainRect.right = START_X + BLOCK_SIZE * COL_CNT + 4;
	m_mainRect.bottom = START_Y + BLOCK_SIZE * ROW_CNT + 4;

	
	//왼쪽화면
	
	
	m_nPattern2 = 0;
	m_nBitType2 = 1;
	m_nRot2 = 0;
	m_bStart2 = FALSE;
	m_mainRect2.left = START_X2;
	m_mainRect2.top = START_Y2;
	m_mainRect2.right = START_X2 + BLOCK_SIZE * COL_CNT + 4;
	m_mainRect2.bottom = START_Y2 + BLOCK_SIZE * ROW_CNT + 4;

	m_nextRect.left = START_X + BLOCK_SIZE * COL_CNT + 15;
	m_nextRect.top = START_Y + 10;
	m_nextRect.right = m_nextRect.left + 150;
	m_nextRect.bottom = m_nextRect.top + 120;

	m_nNextPattern = 0;

	
}

void CSjTetris2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDB_START_BUTTON, m_ctrlStartBt);
	DDX_Control(pDX, IDC_STOP_BUTTON, m_ctrlStopBt);
	DDX_Control(pDX, IDC_SEND_BT, m_ctrlSendBt);
	DDX_Control(pDX, IDC_CONNECT_BT, m_ctrlConnectBt);
	DDX_Control(pDX, IDC_DISCONNECT_BT, m_ctrlDisconnectBt);
	DDX_Text(pDX, IDC_PORTNO, m_nPortNo);
	DDX_Control(pDX, IDC_RECEIVE_DATA, m_ctrlReceiveData);
	DDX_Text(pDX, IDC_RECEIVE_DATA, m_strReceiveData);
	DDX_Control(pDX, IDC_SEND_DATA, m_ctrlSendData);
	DDX_Text(pDX, IDC_SEND_DATA, m_strSendData);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Control(pDX, IDC_USER_LIST, m_ctrlUserList);
	DDX_LBString(pDX, IDC_USER_LIST, m_strUserList);
	DDX_Control(pDX, IDC_FORCED_EXIT_BT, m_ctrlForcedBt);
	DDX_Text(pDX, IDC_IP_ADDRESS, m_strIpAddress);
	DDX_Control(pDX, IDC_IP_ADDRESS, m_ctrlIpAddress);
}

BEGIN_MESSAGE_MAP(CSjTetris2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_START_BUTTON, &CSjTetris2Dlg::OnClickedStartButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CSjTetris2Dlg::OnClickedStopButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CSjTetris2Dlg::OnClickedExitButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONNECT_BT, &CSjTetris2Dlg::OnClickedConnectBt)
	ON_BN_CLICKED(IDC_DISCONNECT_BT, &CSjTetris2Dlg::OnClickedDisconnectBt)
	ON_BN_CLICKED(IDC_SEND_BT, &CSjTetris2Dlg::OnClickedSendBt)
	ON_MESSAGE(UM_ACCEPT, &CSjTetris2Dlg::OnAcceptMsg)
	ON_MESSAGE(UM_RECEIVE,&CSjTetris2Dlg::OnReceiveMsg)
	ON_MESSAGE(UM_SOCKET_CLOSE, &CSjTetris2Dlg::OnCloseMsg)
	ON_BN_CLICKED(IDC_FORCED_EXIT_BT, &CSjTetris2Dlg::OnClickedForcedExitBt)
END_MESSAGE_MAP()


// CSjTetris2Dlg 메시지 처리기

BOOL CSjTetris2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(100, 100, m_mainRect.right + 600, m_mainRect.bottom + 200); //
	m_pDC = GetDC();
	m_pDC2 = GetDC();
	m_bmBlock.LoadBitmap(IDB_BLOCK);
	m_BlockDC.CreateCompatibleDC(m_pDC);
	m_BlockDC.SelectObject(&m_bmBlock);

	m_bmBack.LoadBitmap(IDB_BACK2);
	m_BackDC.CreateCompatibleDC(m_pDC);
	m_BackDC.SelectObject(&m_bmBack);


	
	m_bmBlock2.LoadBitmap(IDB_BLOCK); //다음 화면
	m_BlockDC2.CreateCompatibleDC(m_pDC2);
	m_BlockDC2.SelectObject(&m_bmBlock2);

	m_bmBack2.LoadBitmap(IDB_BACK2);
	m_BackDC2.CreateCompatibleDC(m_pDC2);
	m_BackDC2.SelectObject(&m_bmBack2);

	m_NextBack.LoadBitmap(IDB_BACK1);
	m_NextDC.CreateCompatibleDC(m_pDC);
	m_NextDC.SelectObject(&m_NextBack);

	srand((unsigned)time(NULL));
	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);



	memset((void*)m_Table, -1, sizeof(m_Table));
	memset((void*)m_Table2, -1, sizeof(m_Table2));

	char hostName[32];
	struct in_addr myIpAddr;
	HOSTENT* pHostEnt = NULL;
	gethostname(hostName, sizeof(hostName));
	pHostEnt = gethostbyname(hostName);
	myIpAddr.S_un.S_addr = *((u_long*)(pHostEnt->h_addr_list[0]));
	m_strIpAddress = inet_ntoa(myIpAddr);
	UpdateData(FALSE);

	
	
	m_ctrlConnectBt.EnableWindow(TRUE);
	m_ctrlDisconnectBt.EnableWindow(FALSE);
	m_ctrlForcedBt.EnableWindow(FALSE);
	m_ctrlSendBt.EnableWindow(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSjTetris2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSjTetris2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawScr();
		DrawScr2();
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSjTetris2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSjTetris2Dlg::DrawScr()
{
	// TODO: 여기에 구현 코드 추가.
	int row, col;
	m_pDC->Rectangle(m_mainRect);
	m_pDC->Rectangle(m_nextRect);
	

	for (row = 0; row < ROW_CNT; row++)
	{


		for (col = 0; col < COL_CNT; col++)
		{

			if (m_Table[row][col] == -1)
			{
				m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE, &m_BackDC, col * BLOCK_SIZE, row * BLOCK_SIZE, SRCCOPY);

			}
			else
			{
				m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, m_Table[row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);

			}
		}
	}

}


void CSjTetris2Dlg::InitialGame()
{
	// TODO: 여기에 구현 코드 추가.
	memset((void*)m_Table, -1, sizeof(m_Table));
	memset((void*)m_Table2, -1, sizeof(m_Table2));
	DrawScr();
	DrawScr2();
	m_nPattern = rand() % 7;
	m_nNextPattern = rand() % 7;
	m_nRot = 0;

	m_nY = 1;
	m_nX = COL_CNT / 2;
	m_bStart = TRUE;
	DrawBlock(TRUE);
	
	

	DrawNextBlock(TRUE);
	SetTimer(1, 500, NULL);
}


void CSjTetris2Dlg::DrawBlock(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < 4; i++)
	{

		if (bFlag)
		{
			m_pDC->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, m_nPattern * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
		else
		{
			m_pDC->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BackDC, (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE, (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE, SRCCOPY);
		}
	}
}


bool CSjTetris2Dlg::BlockDown()
{
	// TODO: 여기에 구현 코드 추가.
	if (!IsAround(m_nX, m_nY + 1))
	{

		SetTable();
		return FALSE;
	}
	DrawBlock(FALSE);
	m_nY++;
	DrawBlock(TRUE);
	return TRUE;
}


bool CSjTetris2Dlg::IsAround(int nX, int nY)
{
	// TODO: 여기에 구현 코드 추가.
	int i, row, col;
	for (i = 0; i < 4; i++)
	{
		col = nX + Pattern[m_nPattern][i + m_nRot * 4].x;
		row = nY + Pattern[m_nPattern][i + m_nRot * 4].y;
		if (col<0 || col>COL_CNT - 1 || row<1 || row>ROW_CNT - 1)
		{
			return FALSE;
		}
		if (m_Table[row][col] != -1)
		{
			return FALSE;
		}
	}
	return TRUE;
}


void CSjTetris2Dlg::SetTable()
{
	// TODO: 여기에 구현 코드 추가.
	int i, row, col, sw;
	for (i = 0; i < 4; i++)
	{
		m_Table[m_nY + Pattern[m_nPattern][i + m_nRot * 4].y][m_nX + Pattern[m_nPattern][i + m_nRot * 4].x] = m_nPattern;
	}
	for (row = ROW_CNT - 1; row >= 0; row--)
	{
		sw = 0;
		for (col = 0; col < COL_CNT; col++)
		{
			if (m_Table[row][col] == -1)
				sw = -1;
		}
		if (sw == 0)
		{
			for (i = row; i > 0; i--)
			{
				for (col = 0; col < COL_CNT; col++)
				{
					m_Table[i][col] = m_Table[i - 1][col];
					
				}
			}
			for (col = 0; col < COL_CNT; col++)
			{
				m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, &m_BackDC, 0, 0, SRCCOPY);

				Sleep(20);
			}
			DrawScr();
			Sleep(100);
			row++;
		}
	}

	/*(row = 0; row < ROW_CNT; row++)
	{
		for (col = 0; col < COL_CNT; col++)
		{
			m_Table2[row][col] = m_Table[row][col];
		}
	}*/
	memcpy((void*)m_Table2, (void*)m_Table, sizeof(m_Table));
	
	DrawScr2();
	m_nX = COL_CNT / 2;
	m_nY = 1;
	DrawNextBlock(FALSE);
	m_nPattern = m_nNextPattern;

	m_nRot = 1;
	m_nNextPattern = rand() % 7;
	DrawNextBlock(TRUE);






	if (!IsAround(m_nX, m_nY + 1))
	{
		KillTimer(1);
		MessageBox(_T("으악"));
		m_ctrlStartBt.EnableWindow(TRUE);
		m_ctrlStopBt.EnableWindow(FALSE);
		return;
	}
}


void CSjTetris2Dlg::RotateBlock(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int nRot = m_nRot;
	DrawBlock(FALSE);
	if (++m_nRot > 3)
	{
		m_nRot = 0;
	}
	if (!IsAround(m_nX, m_nY))
		m_nRot = nRot;
	DrawBlock(TRUE);
}


void CSjTetris2Dlg::MoveDown()
{
	// TODO: 여기에 구현 코드 추가.
	while (BlockDown())
	{
		Sleep(30);
	}
}


void CSjTetris2Dlg::MoveRight()
{
	// TODO: 여기에 구현 코드 추가.
	if (!IsAround(m_nX + 1, m_nY))
		return;
	DrawBlock(FALSE);
	m_nX++;
	DrawBlock(TRUE);
}


void CSjTetris2Dlg::MoveLeft()
{
	// TODO: 여기에 구현 코드 추가.
	if (!IsAround(m_nX - 1, m_nY))
		return;
	DrawBlock(FALSE);
	m_nX--;
	DrawBlock(TRUE);
}


void CSjTetris2Dlg::OnClickedStartButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InitialGame();
	m_ctrlStartBt.EnableWindow(FALSE);
	m_ctrlStopBt.EnableWindow(TRUE);
	m_ctrlStopBt.SetFocus();
}


void CSjTetris2Dlg::OnClickedStopButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bStart = FALSE;
	KillTimer(1);
	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);
}


void CSjTetris2Dlg::OnClickedExitButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CSjTetris2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	BlockDown();
	
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CSjTetris2Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && m_bStart)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			MoveLeft();
			return TRUE;
		case VK_RIGHT:
			MoveRight();
			return TRUE;
		case VK_DOWN:
			MoveDown();
			return TRUE;
		case VK_UP:
			RotateBlock(FALSE);
			return TRUE;
		case VK_SPACE:
		case VK_RETURN:
			MoveDown();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSjTetris2Dlg::DrawNextBlock(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < 4; i++)
	{

		if (bFlag)
		{
			m_pDC->BitBlt(400 + (Pattern[m_nNextPattern][i].x) * BLOCK_SIZE,
				55 + (Pattern[m_nNextPattern][i].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, m_nNextPattern * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
		else
		{
			m_pDC->BitBlt(400 + (Pattern[m_nNextPattern][i].x) * BLOCK_SIZE,
				55 + (Pattern[m_nNextPattern][i].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_NextDC, 0, 0, SRCCOPY);
		}
	}
}


void CSjTetris2Dlg::DrawScr2() // 화면그리기 세팅 완료!
{
	// TODO: 여기에 구현 코드 추가.
	int row, col;
	//m_pDC2->Rectangle(m_mainRect2);



	for (row = 0; row < ROW_CNT; row++)
	{


		for (col = 0; col < COL_CNT; col++)
		{

			if (m_Table2[row][col] == -1)
			{
				m_pDC2->BitBlt(START_X2 + 2 + col * BLOCK_SIZE, START_Y2 + 2 + row * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE, &m_BackDC2, col * BLOCK_SIZE, row * BLOCK_SIZE, SRCCOPY);

			}
			else
			{
				m_pDC2->BitBlt(START_X2 + 2 + col * BLOCK_SIZE, START_Y2 + 2 + row * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC2, m_Table2[row][col] * BLOCK_SIZE, m_nBitType2 * BLOCK_SIZE, SRCCOPY);

			}
		}
	}

	
	

	
}



void CSjTetris2Dlg::DrawBlock2(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < 4; i++)
	{

		if (bFlag)
		{
			m_pDC2->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC2, m_nPattern * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
		else
		{
			m_pDC2->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BackDC2, (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE, (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE, SRCCOPY);
		}
	}
	
}


void CSjTetris2Dlg::OnClickedConnectBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_ctrlConnectBt.EnableWindow(FALSE);
	m_ctrlConnectBt.SetWindowText(_T("Server 실행중"));
	if (!m_Server.ServerStart(this,m_nPortNo))
	{
		MessageBox(_T("Server Socket 문제 발생"));
		m_ctrlConnectBt.EnableWindow(TRUE);
		m_ctrlConnectBt.SetWindowText(_T("Server Start"));
		return;
	}
	m_ctrlForcedBt.EnableWindow(TRUE);
	m_ctrlSendBt.EnableWindow(TRUE);
	m_ctrlDisconnectBt.EnableWindow(TRUE);
	
	m_strReceiveData += "Server 실행 후 대기 중입니다.\r\n";
	UpdateData(FALSE);
	m_ctrlSendData.SetFocus();
	
}





void CSjTetris2Dlg::OnClickedDisconnectBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (AfxMessageBox(_T("Server를 종료합니다!!"), MB_YESNO) != IDYES)
		return;

	CSjClientSocket* pNode;
	char szSendData[DATA_SIZE] = "QServer가 종료됩니다.";
	POSITION frontPos, pos = m_List.GetHeadPosition();

	while (pos != NULL)
	{
		frontPos = pos;
		pNode = (CSjClientSocket*)m_List.GetNext(pos);
		if (pNode->Send(szSendData, DATA_SIZE) == -1)
			MessageBox(_T("전송실패"));
		m_List.RemoveAt(frontPos);
		pNode->Close();
		delete pNode;
	}
	m_ctrlForcedBt.EnableWindow(false);
	m_ctrlSendBt.EnableWindow(false);
	m_ctrlDisconnectBt.EnableWindow(false);
	m_ctrlConnectBt.EnableWindow(true);
	m_ctrlConnectBt.SetWindowText(_T("Server Start"));
	m_Server.ShutDown();
	m_Server.Close();
	m_strReceiveData += "Server를 종료합니다.\r\n";
	UpdateData(FALSE);
}


void CSjTetris2Dlg::OnClickedSendBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다. 
	char szSendData[DATA_SIZE] = "";
	UpdateData(TRUE);
	if (!m_strSendData.IsEmpty())
	{
		sprintf_s((szSendData + 1), DATA_SIZE - 1, "관리자 : %s\r\n", CT2A(m_strSendData));
		szSendData[0] = 'D';
		BroadCast((void*)szSendData);
		m_strReceiveData += szSendData + 1;
		m_strSendData = "";
		UpdateData(FALSE);

	}
	m_ctrlSendData.SetFocus();
}


LRESULT CSjTetris2Dlg::OnAcceptMsg(WPARAM wParam, LPARAM IParam)
{
	// TODO: 여기에 구현 코드 추가.
	char szSendData[DATA_SIZE] = "", szReceiveData[DATA_SIZE] = "";
	CSjClientSocket* pSocket = new CSjClientSocket;
	if (!m_Server.Accept(*pSocket))
	{
		MessageBox(_T("Client 연결 실패"));
		return -1;
	}
	//szSendData[0]='I';
	sprintf_s(szSendData, DATA_SIZE, "ISejong Chatting Server입니다.\r\n");
	pSocket->Send((void*)szSendData, DATA_SIZE);
	pSocket->SetMainWindow(this);
	m_List.AddTail(pSocket);

	
	return LRESULT();
}


LRESULT CSjTetris2Dlg::OnReceiveMsg(WPARAM wParam, LPARAM IParam)
{
	// TODO: 여기에 구현 코드 추가.
	char szSendData[DATA_SIZE] = "", szReceiveData[DATA_SIZE] = "";
	CString strName;
	char szName[20];

	CSjClientSocket* pSocket = (CSjClientSocket*)IParam;
	pSocket->Receive((void*)szReceiveData, DATA_SIZE);

	switch (szReceiveData[0])
	{
	case'N':
		szSendData[DATA_SIZE] = 'U';
		for (int i = 0; i < m_ctrlUserList.GetCount(); i++)
		{
			m_ctrlUserList.GetText(i, strName);
			sprintf_s(szSendData, DATA_SIZE, "U%s", CT2A(strName));
			pSocket->Send((void*)szSendData, DATA_SIZE);
		}
		pSocket->m_strName = szReceiveData + 1;
		sprintf_s(szSendData, DATA_SIZE, "C%s", szReceiveData + 1);
		BroadCast((void*)szSendData);
		UserList(pSocket->m_strName, 'A');
		m_strReceiveData += szSendData + 1;
		m_strReceiveData += "님이 접속하셨습니다.\r\n";
		break;

	//case 'D':
	default:
		strcpy_s(szName, 20, CT2A(pSocket->m_strName));
		sprintf_s(szSendData, "D%s:%s\r\n",szName, szReceiveData + 1);
		BroadCast((void*)szSendData);
		m_strReceiveData += szSendData + 1;

	}
	UpdateData(FALSE);
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);
	return LRESULT();
}


LRESULT CSjTetris2Dlg::OnCloseMsg(WPARAM wParam, LPARAM IParam)
{
	// TODO: 여기에 구현 코드 추가.
	char szName[20] = "";
	char szSendData[DATA_SIZE] = "";
	CSjClientSocket* pSocket = (CSjClientSocket*)IParam;
	strcpy_s(szName, 10, CT2A(pSocket->m_strName));
	sprintf_s(szSendData, DATA_SIZE, "E%s", szName);

	UserList(pSocket->m_strName, 'D');

	BroadCast((void*)szSendData);
	m_strReceiveData += szSendData + 1;
	m_strReceiveData += "님이 퇴장하셨습니다.\r\n";
	UpdateData(FALSE);
	
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);

	CSjClientSocket* pNode;
	POSITION frontPos, pos = m_List.GetHeadPosition();
	while (pos != NULL)
	{
		frontPos = pos;
		pNode = (CSjClientSocket*)m_List.GetNext(pos);
		if (pSocket == pNode)
		{
				m_List.RemoveAt(frontPos);
				pSocket->Close();
				delete pSocket;
				break;
			
		}
	}

	

	return LRESULT();
}


bool CSjTetris2Dlg::BroadCast(void* pStr)
{
	// TODO: 여기에 구현 코드 추가.
	CSjClientSocket* pNode;
	for (POSITION pos = m_List.GetHeadPosition(); pos != NULL;)
	{
		pNode = (CSjClientSocket*)m_List.GetNext(pos);
		if (pNode->Send(pStr, DATA_SIZE) == -1)
			MessageBox(_T("전송실패"));
	}
	return false;

}


void CSjTetris2Dlg::UserList(CString strUser, char nFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int n, loc;
	if (nFlag == 'D')
	{
		n = m_ctrlUserList.FindString(-1, strUser);
		m_ctrlUserList.DeleteString(n);

	}
	else if (nFlag == 'A')
	{
		m_ctrlUserList.AddString(strUser);
	}
	loc = m_ctrlUserList.GetCount();
	
	m_ctrlUserList.SetAnchorIndex(loc - 1);
	m_ctrlUserList.SetCurSel(loc - 1);
	
}


void CSjTetris2Dlg::OnClickedForcedExitBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szName[10] = "";
	char szSendData[DATA_SIZE] = "";
	CSjClientSocket* pNode;

	UpdateData(TRUE);
	strcpy_s(szName, 10, CT2A(m_strUserList));
	sprintf_s(szSendData, DATA_SIZE, "F%s", szName);
	UserList(m_strUserList, 'D');
	BroadCast((void*)szSendData);
	m_strReceiveData += szSendData + 1;
	m_strReceiveData += "님이 강제 퇴장 되었습니다.\r\n";
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);

	POSITION frontPos, pos = m_List.GetHeadPosition();
	while (pos != NULL)
	{
		frontPos = pos;
		pNode = (CSjClientSocket*)m_List.GetNext(pos);
		if (pNode->m_strName == m_strUserList);
		{
			m_List.RemoveAt(frontPos);
			pNode->Close();
			delete pNode;
			break;
		}
	}

}
