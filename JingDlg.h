
// JingDlg.h : 头文件
//
#pragma once

#include<iostream>
#include<vector>
//#include<cstdlib>
//#include<cmath>
#include "conio.h"
#include "Jing.h"
#include <sstream>
//#include <string>
using namespace std;

// CJingDlg 对话框
//vector<vector<int> > t_cur(3, vector<int>(3, 0));
class CJingDlg : public CDialogEx
{
// 构造
public:
	CJingDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_JING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedMinMax();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedAb();
};

/*1表示O -1表示X 0表示没放*/
class ticTac {
public:
	vector<vector<int> > chessBoard;
	int value;
public:
	ticTac() {
		chessBoard.resize(3);
		for (int i = 0; i < 3; i++) {
			chessBoard[i].resize(3, 0);
		}
	}
	ticTac(vector<vector<int> > b) {
		chessBoard.resize(3);
		for (int i = 0; i < 3; i++) {
			chessBoard[i].resize(3, 0);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				chessBoard[i][j] = b[i][j];
			}
		}
	}
	void setChess(vector<vector<int> > b) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				chessBoard[i][j] = b[i][j];
			}
		}
	}
	void disp() {
		for (int i = 0; i < chessBoard.size(); i++) {
			for (int j = 0; j < chessBoard[i].size(); j++) {
				char str[4] = {};
				if (chessBoard[i][j] < 0) {
					str[0] = '-';
					str[1] = abs(chessBoard[i][j]) + '0'; str[2] = '  '; str[3] = '\0';
				}
				else
				{
					str[0] = chessBoard[i][j] + '0'; str[1] = ' '; str[2] = '\0';
				}
				
				_cprintf(str);
				//cout << chessBoard[i][j] << " ";
			}
			//cout << endl;
			_cprintf("\n");
		}
		_cprintf("\n");
		/*
		int win = checkWin(chessBoard);
		if (win == -1) {
			_cprintf("The computer wins!\n");
		}
		else if (win == 1) {
			_cprintf("Congratuations!You win!\n");
		}
		*/
	}
	void computeValue() {
		//全部空格放X后三字成一线的总数-全部空格放O后三字一线的总数
		//放X 用户
		vector<vector<int> > Xchess(3, vector<int>(3, 0));
		int countx = 0;
		for (int i = 0; i < chessBoard.size(); i++) {
			for (int j = 0; j < chessBoard[i].size(); j++) {
				if (chessBoard[i][j] == 0) Xchess[i][j] = 1;
				else Xchess[i][j] = chessBoard[i][j];
			}
		}
		/*cout << "输出X：\n";
		for (int i = 0; i < chessBoard.size(); i++) {
		for (int j = 0; j < chessBoard[i].size(); j++) {
		cout << Xchess[i][j] << " ";
		}
		cout << endl;
		}*/
		for (int i = 0; i < chessBoard.size(); i++) {
			int sum = 0;
			for (int j = 0; j < chessBoard[i].size(); j++) sum += Xchess[i][j];
			if (sum == 3) countx++;

			sum = 0;
			for (int j = 0; j < chessBoard[i].size(); j++) sum += Xchess[j][i];
			if (sum == 3) countx++;
		}
		int sum = 0;
		for (int i = 0; i < chessBoard.size(); i++) sum += Xchess[i][i];
		if (sum == 3) countx++;

		sum = 0;
		for (int i = 0; i < chessBoard.size(); i++) sum += Xchess[i][chessBoard.size() - 1 - i];
		if (sum == 3) countx++;

		//cout << "xcount: " << countx << endl;
		//放Y 机器占优
		vector<vector<int> > Ychess(3, vector<int>(3, 0));
		int county = 0;
		for (int i = 0; i < chessBoard.size(); i++) {
			for (int j = 0; j < chessBoard[i].size(); j++) {
				if (chessBoard[i][j] == 0) Ychess[i][j] = -1;
				else Ychess[i][j] = chessBoard[i][j];
			}
		}
		/*cout << "输出Y：\n";
		for (int i = 0; i < chessBoard.size(); i++) {
		for (int j = 0; j < chessBoard[i].size(); j++) {
		cout << Ychess[i][j] << " ";
		}
		cout << endl;
		}*/
		for (int i = 0; i < chessBoard.size(); i++) {
			int sum = 0;
			for (int j = 0; j < chessBoard[i].size(); j++) sum += Ychess[i][j];
			if (sum == -3) county++;

			sum = 0;
			for (int j = 0; j < chessBoard[i].size(); j++) sum += Ychess[j][i];
			if (sum == -3) county++;
		}
		sum = 0;
		for (int i = 0; i < chessBoard.size(); i++) sum += Ychess[i][i];
		if (sum == -3) county++;

		sum = 0;
		for (int i = 0; i < chessBoard.size(); i++) sum += Ychess[i][chessBoard.size() - 1 - i];
		if (sum == -3) county++;

		//cout << "ycount: " << county << endl;

		value = county - countx;
	}
};
typedef pair<ticTac*, pair<int, int> > chess;
class MIN_MAX {
public:
	ticTac* tic; //输入一个棋盘状态 
	//bool layer; //表示极大极小层
	int k; //搜索树深度 
	vector<vector<chess> > graph; // 搜索图 
	vector<vector<int> > t_cur;
	pair<int, int> cur_pos;
//	int i;
//	int j;
public:
	MIN_MAX(vector<vector<int> > b/*int isBlack*/) {
		//输入的b一定是用户先下完  所以棋盘中有1 机器下-1
		t_cur = b;
		tic = new ticTac();
		tic->setChess(b);
		tic->value = -9;
		//layer = 1;
		k = 3;
		graph.resize(k);
		graph[0].push_back(make_pair(tic, make_pair(0, 0)));

	}
	~MIN_MAX() {
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				delete graph[i][j].first;
			}
		}
	}
	//返回最优棋盘状态 
	ticTac* search() {
		//极大极小算法，先生成整个搜索树
		int preisum = 1;
		for (int i = 1; i < k; i++) {
			for (int j = 0; j < graph[i - 1].size(); j++) {
				ticTac* temp = graph[i - 1][j].first;
				//生成后继 
				int suanzi;
				if (i % 2) suanzi = -1; //X-机器
				else suanzi = 1; //O-用户
				//新的棋盘状态 
				vector<vector<int> > temp2(3, vector<int>(3, 0));
				for (int x = 0; x < temp->chessBoard.size(); x++) {
					for (int y = 0; y < temp->chessBoard[x].size(); y++) {
						temp2[x][y] = temp->chessBoard[x][y];
					}
				}
				for (int x = 0; x < temp->chessBoard.size(); x++) {
					for (int y = 0; y < temp->chessBoard[x].size(); y++) {
						if (temp2[x][y] == 0) {
							temp2[x][y] = suanzi;
							ticTac* new_status = new ticTac(temp2);
							new_status->computeValue();
							//new_status->disp(); 
							//cout << new_status->value << endl; 
							graph[i].push_back(make_pair(new_status, make_pair(i - 1, j)));
							temp2[x][y] = 0;
						}
					}
				}
			}
			preisum += graph[i].size();
		}

		//输出当前搜索树的结点评估值
		/*for (int i = 0; i < k; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
		cout << graph[i][j].first->value << " ";
		}
		cout << endl;
		}*/
		_cprintf("output:\n");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				int a = -10;
				//char str[10] = {};
				_cprintf("search on chessbroad:\n");
				graph[i][j].first->disp();
				stringstream ss;
				string s;
				ss << graph[i][j].first->value ;
				//_itoa(graph[i][j].first->value, str, 10);
				ss >> s;
				s += " ";
				//s.c_str();
				_cprintf("evaluation on chessbroad:\n");
				_cprintf(s.c_str());
				//cout << graph[i][j].first->value << " ";
				//free(str);
				_cprintf("\n");
				
			}
			_cprintf("\n");
			//cout << endl;
		}

		//倒推过程 
		pair<int, int> next_max = pair<int, int>(1, 1);
		//对i=1层取出最大值
		for (int i = graph.size() - 1; i >= 1; i--) {
			for (int j = 0; j < graph[i].size(); j++) {
				pair<int, int> parent = graph[i][j].second;
				if ((i - 1) % 2) {
					if (graph[i][j].first->value < graph[parent.first][parent.second].first->value) {
						graph[parent.first][parent.second].first->value = graph[i][j].first->value;
						if (!(i - 1)) next_max = make_pair(i, j);
					}
				}
				else {
					if (graph[i][j].first->value > graph[parent.first][parent.second].first->value) {
						graph[parent.first][parent.second].first->value = graph[i][j].first->value;
						if (!(i - 1)) next_max = make_pair(i, j);
					}
				}
			}
		}
		//cout << next_max.first << " " << next_max.second << endl; 
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (graph[next_max.first][next_max.second].first->chessBoard[i][j] != t_cur[i][j]) {
					cur_pos.first = i;
					cur_pos.second = j;
				}
			}
		}
		return graph[next_max.first][next_max.second].first;
	}
};

