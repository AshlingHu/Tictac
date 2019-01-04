
// JingDlg.cpp : 实现文件
//

//#include "afxwin.h"
#include "stdafx.h"
#include "JingDlg.h"
#include"a_b.h"
//#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

vector<vector<int> > initMatrix(3, vector<int>(3, 0));
int next_State = 1;
int n_pos = 0;
int depth = 3;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int t_cur_row;
int t_cur_col;
int choose = 1;
JingZiQi J;
Computer C;

//MIN_MAX process;
//ticTac* nextshow;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJingDlg 对话框



CJingDlg::CJingDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CJingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_MIN_MAX, &CJingDlg::OnBnClickedMinMax)
	ON_BN_CLICKED(IDC_AB, &CJingDlg::OnBnClickedAb)
END_MESSAGE_MAP()


// CJingDlg 消息处理程序
const CRect m_rcSquares[9] = {
	CRect(21, 21, 99, 99),
	CRect(101, 21, 179, 99),
	CRect(181, 21, 259, 99),
	CRect(21, 101, 99, 179),
	CRect(101, 101, 179, 179),
	CRect(181, 101, 259, 179),
	CRect(21, 181, 101, 259),
	CRect(101, 181, 179, 259),
	CRect(181, 181, 259, 259)
};

BOOL CJingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	AllocConsole();
	LPCWSTR lpStr = L"输出中间结果";
	SetConsoleTitle(lpStr);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void reset(CDC* pDC) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			initMatrix[i][j] = 0;
		}
	}
	CBrush brush(RGB(240, 240, 240));
	CRect rect = CRect(10, 10, 270, 270);
	pDC->FillRect(rect, &brush);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(pen);
	pDC->MoveTo(20, 20);
	pDC->LineTo(260, 20);
	pDC->MoveTo(20, 100);
	pDC->LineTo(260, 100);
	pDC->MoveTo(20, 180);
	pDC->LineTo(260, 180);
	pDC->MoveTo(20, 260);
	pDC->LineTo(260, 260);

	pDC->MoveTo(20, 20);
	pDC->LineTo(20, 260);
	pDC->MoveTo(100, 20);
	pDC->LineTo(100, 260);
	pDC->MoveTo(180, 20);
	pDC->LineTo(180, 260);
	pDC->MoveTo(260, 20);
	pDC->LineTo(260, 260);
	choose = 1;
	J.clear();
}
void CJingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CDC *pDC = GetDC();
	pDC->SelectObject(pen);
	pDC->MoveTo(20, 20);
	pDC->LineTo(260, 20);
	pDC->MoveTo(20, 100);
	pDC->LineTo(260, 100);
	pDC->MoveTo(20, 180);
	pDC->LineTo(260, 180);
	pDC->MoveTo(20, 260);
	pDC->LineTo(260, 260);

	pDC->MoveTo(20, 20);
	pDC->LineTo(20, 260);
	pDC->MoveTo(100, 20);
	pDC->LineTo(100, 260);
	pDC->MoveTo(180, 20);
	pDC->LineTo(180, 260);
	pDC->MoveTo(260, 20);
	pDC->LineTo(260, 260);
	int a;
	a = 0;
	MessageBox(L"请先选择算法！");
	//_cprintf("hh\n");

}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//判定鼠标是否点进矩形某一区域，点进返回区域编号，没有返回-1
//此处用了一个rect.PtInRect(Point point)函数帮助判定
int GetRectID(CPoint point)
{
	for (int i = 0; i<9; i++) {
		if (m_rcSquares[i].PtInRect(point))
			return i;
	}
	return -1;
}

int checkWin(vector<vector<int> > b) {
	//检查横
	for (int i = 0; i < 3; i++) {
		if (b[i][0] == b[i][1] && b[i][1]  == b[i][2]) {
			return b[i][0];
		}
	}
	//检查竖
	for (int i = 0; i < 3; i++) {
		if (b[0][i] == b[1][i] && b[1][i] == b[2][i]) {
			return b[0][i];
		}
	}
	//检查对角
	if ((b[0][0] == b[1][1] && b[1][1] == b[2][2]) || (b[0][2] == b[1][1] && b[1][1] == b[2][0])) {
		return b[1][1];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b[i][j] == 0) return 0;
		}
	}
	//平局
	return 2;
}
void ReDraw(CDC *pDC) {
	//RedrawWindow();

}
void CpDraw(CDC* pDC){
	if (choose == 1) {
		n_pos = t_cur_row * 3 + t_cur_col;
		CRect rect = m_rcSquares[n_pos], t_rect;
		t_rect = CRect(rect.left + 20, rect.top + 20, rect.right - 20, rect.bottom - 20);
		CPen pen(PS_SOLID, 5, RGB(0, 0, 0));//宽为16像素的红笔
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->SelectStockObject(NULL_BRUSH);
		int row = n_pos / 3;
		int col = n_pos % 3;
		initMatrix[row][col] = next_State;
		pDC->Ellipse(t_rect);
		next_State = 1;
		pDC->SelectObject(pOldPen);
		int win = checkWin(initMatrix);
		if (win == -1) {
			MessageBox(NULL, L"电脑赢", L"谁赢", MB_OK);
			reset(pDC);
			return;
		}
		else if (win == 1) {
			MessageBox(NULL, L"玩家赢", L"谁赢", MB_OK); 
			reset(pDC);
				return;
		}
		else if (win == 2){
			MessageBox(NULL, L"平局", L"谁赢", MB_OK);
			reset(pDC);
			return;
		}
	}
	else if (choose == 2) {
		pair<int, int> pa;
		pa = C.put(J.get_board(), depth);//depth
		J.put(pa);
		int u;
		int a, b;
		a = (pa.first);
		b = pa.second;
		u = (a * 3 + b);

		//标记已下并改变下一个点击状态
	//	m_nGameGrid[u] = OH; // 2
		//m_nNextChar = EX;//1

		//画上图
		//DrawO(pDC, u);//在u的矩形中下入
		n_pos = u;
		CRect rect = m_rcSquares[n_pos], t_rect;
		t_rect = CRect(rect.left + 20, rect.top + 20, rect.right - 20, rect.bottom - 20);
		CPen pen(PS_SOLID, 5, RGB(0, 0, 0));//宽为16像素的红笔
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->SelectStockObject(NULL_BRUSH);
		int row = n_pos / 3;
		int col = n_pos % 3;
		initMatrix[row][col] = next_State;
		pDC->Ellipse(t_rect);
		next_State = 1;
		pDC->SelectObject(pOldPen);
		int win = checkWin(initMatrix);
		if (win == -1) {
			MessageBox(NULL, L"电脑赢", L"谁赢", MB_OK);
			reset(pDC);
			return;
		}
		else if (win == 1) {
			MessageBox(NULL, L"玩家赢", L"谁赢", MB_OK);
			reset(pDC);
			return;
		}
		else if (win == 2){
			MessageBox(NULL, L"平局", L"谁赢", MB_OK);
			reset(pDC);
			return;
		}
	}
}
void InitGame()
{

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			initMatrix[i][j] = 0;
		}
	}

	next_State = 1;
}
//重新开始初始化

void ResetGame(CDC *pDC)
{
	CView *pView;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			initMatrix[i][j] = 0;
		}
	}

	next_State = 1;
//	pDC->Invalidate();   //使控件的整个图面无效并导致重绘控件
}

void CJingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.x >= (long)260 || point.x <= (long)20 || point.y >= (long)260 || point.y <= (long)20) {
		return;
	}
		
	CDC *pDC = GetDC();
	//int n_pos;
	n_pos = GetRectID(point);
	/*	
	if (next_State == 1) {
		n_pos = GetRectID(point);
	}
	else {
		n_pos = t_cur_row * 3 + t_cur_col;
	}*/
	CRect rect = m_rcSquares[n_pos], t_rect;
	t_rect = CRect(rect.left + 20, rect.top + 20, rect.right - 20, rect.bottom - 20);
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));//宽为16像素的红笔
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);
	int row = n_pos / 3;
	int col = n_pos % 3;
	initMatrix[row][col] = next_State;
	pDC->MoveTo(t_rect.left, t_rect.top);
	pDC->LineTo(t_rect.right, t_rect.bottom);
	pDC->MoveTo(t_rect.left, t_rect.bottom);
	pDC->LineTo(t_rect.right, t_rect.top);
	
	int win = checkWin(initMatrix);
	if (win == -1) {
		MessageBox(L"电脑赢", L"谁赢");
		reset(pDC);
		return;
	}
	else if (win == 1) {
		MessageBox(L"玩家赢", L"谁赢");
		reset(pDC);
		return;
	}
	else if (win == 2){
		MessageBox(L"平局", L"谁赢");
		reset(pDC);
		return;
	}

	if (choose == 1) {
		MIN_MAX process(initMatrix);
		//	processt_cur = initMatrix;
		//	process.search();
		ticTac* nextshow = process.search();
		nextshow->disp();
		next_State = -1;
		t_cur_row = process.cur_pos.first;
		t_cur_col = process.cur_pos.second;
	}
	else if (choose == 2)
	{

		//获得点击矩形区域编号
		//如果没有点中或者已经被下棋了，返回
	//	int nPos = GetRectID(point); //n 已经下的矩形位置；
	//	if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
	//		return;


		//标记已下并改变下一个点击状态
		J.put(make_pair(row, col));
		//m_nGameGrid[nPos] = EX;
		next_State = -1;

		//画上图并判断游戏是否结束
	//	DrawX(&dc, nPos);
	//	if (CheckForGameOver())return;

	//	CpDraw(&dc);
		//电脑下棋
	//	if (CheckForGameOver())return;
	}
	
	CpDraw(pDC);
	/*
	if (next_State == 1) {
		pDC->MoveTo(t_rect.left, t_rect.top);
		pDC->LineTo(t_rect.right, t_rect.bottom);
		pDC->MoveTo(t_rect.left, t_rect.bottom);
		pDC->LineTo(t_rect.right, t_rect.top);
		next_State = -1;
		MIN_MAX process(initMatrix);
	//	processt_cur = initMatrix;
	//	process.search();
		ticTac* nextshow = process.search();
		nextshow->disp();
		t_cur_row = process.cur_pos.first;
		t_cur_col = process.cur_pos.second;
	}
	else {

		//pDC->SetBkMode(TRANSPARENT);
		pDC->Ellipse(t_rect);
		next_State = 1;
	}*/
	pDC->SelectObject(pOldPen);
	//	MIN_MAX process(initMatrix);
	//	ticTac* nextshow = process.search();
	//	nextshow->disp();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CJingDlg::OnBnClickedMinMax()
{
	// TODO:  在此添加控件通知处理程序代码
	choose = 1;

}




void CJingDlg::OnBnClickedAb()
{
	// TODO:  在此添加控件通知处理程序代码
	choose = 2;
}
