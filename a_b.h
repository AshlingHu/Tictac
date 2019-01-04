#include<iostream>
#include<vector>
#include<stack>
#include <sstream>
#include <string>
#include <cstring>
#include "conio.h"
using namespace std;

#define BOARD_SIZE 3
#define WIN_SIZE 3 
typedef pair<int, int> pos;
pair<int, int> p;
class JingZiQi{
public:
	JingZiQi();
	bool put(pos);
	bool redraw();
	bool isWin();
	int who_win();
	void clear();
	vector<vector<int> > get_board();
	bool get_turn();
private:
	vector<vector<int> > board;
	stack<pos> history;
	bool P1_turn;
};

JingZiQi::JingZiQi(){

	for (int i = 0; i < BOARD_SIZE; i++){
		vector<int> tem(BOARD_SIZE);
		board.push_back(tem);
	}

	P1_turn = true;
}

bool JingZiQi::put(pos p){
	if (p.first<0 || p.second<0 || p.first >= BOARD_SIZE || p.second >= BOARD_SIZE) return false;
	if (board[p.first][p.second] != 0) return false;
	if (P1_turn){
		board[p.first][p.second] = 1;
		P1_turn = false;
	}

	else{
		board[p.first][p.second] = 2;
		P1_turn = true;
	}
	history.push(p);
	return true;
}

bool JingZiQi::redraw(){
	if (history.empty()) return false;
	pos tem = history.top();
	history.pop();
	board[tem.first][tem.second] = 0;
	P1_turn = !P1_turn;
	return true;
}

bool JingZiQi::isWin(){

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j< BOARD_SIZE; j++){
			int now = board[i][j];
			if (now == 0) continue;
			int k = 0;
			//¼ì²éºá 
			if (j <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i][j + k] != now) break;
			if (k == WIN_SIZE) return true;

			//¼ì²éÊú
			if (i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j] != now) break;
			if (k == WIN_SIZE) return true;

			//¼ì²é×óÐ±
			if (j >= WIN_SIZE - 1 && i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j - k] != now) break;
			if (k == WIN_SIZE) return true;

			//¼ì²éÓÒÐ±
			if (j <= BOARD_SIZE - WIN_SIZE&&i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j + k] != now) break;
			if (k == WIN_SIZE) return true;
		}
	}

	return false;

}
void print(vector<vector<int> > board);
int JingZiQi::who_win(){
	if (isWin()){
		if (P1_turn) return 2;
		else return 1;
	}
	return 0;
}

vector<vector<int> > JingZiQi::get_board(){
	return board;
}

bool JingZiQi::get_turn(){
	return P1_turn;
}
void JingZiQi::clear()
{
	board.resize(3);
	for (int i = 0; i < BOARD_SIZE; i++) {
		vector<int> tem(BOARD_SIZE, 0);
		board[i] = (tem);
	}

	P1_turn = true;
}

class Computer{
public:
	Computer();
	bool is_valid(vector<vector<int> >, pos);
	bool is_full(vector<vector<int> >);
	pos put(vector<vector<int> >, int);
	int a_cut(vector<vector<int> >, int, int);
	int b_cut(vector<vector<int> >, int, int);
	int eliminate(vector<vector<int> >);
	int eliminate_part(vector<vector<int> >, int);
	bool is_win(vector<vector<int> >, int);

};

Computer::Computer(){
}

bool Computer::is_valid(vector<vector<int> > board, pos p){
	if (p.first<0 || p.second<0 || p.first >= BOARD_SIZE || p.second >= BOARD_SIZE) return false;
	if (board[p.first][p.second] != 0) return false;
	return true;
}

bool Computer::is_full(vector<vector<int> > board){
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++)
		if (board[i][j] == 0) return false;
	}
	return true;
}

bool Computer::is_win(vector<vector<int> >board, int now){

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j< BOARD_SIZE; j++){
			int now = board[i][j];
			if (now == 0) continue;
			int k = 0;
			//¼ì²éºá 
			if (j <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i][j + k] != now) break;
			if (k == WIN_SIZE) return true;

			//¼ì²éÊú
			if (i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j] != now) break;
			if (k == WIN_SIZE) return true;

			//¼ì²é×óÐ±
			if (j >= WIN_SIZE - 1 && i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j - k] != now) break;
			if (k == WIN_SIZE) return true;

			//¼ì²éÓÒÐ±
			if (j <= BOARD_SIZE - WIN_SIZE&&i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j + k] != now) break;
			if (k == WIN_SIZE) return true;
		}
	}

	return false;

}

pos Computer::put(vector<vector<int> > board, int depth){

	int max = -100000;
	pos result;
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (is_valid(board, make_pair(i, j))){
				board[i][j] = 2;
				int score = b_cut(board, depth - 1, max);
				if (is_win(board, 2)) score = 1000;
				//cout<<score<<endl;
				if (max<score){
					max = score;
					result = make_pair(i, j);
				}
				board[i][j] = 0;
			}
		}
	}
	return result;
}

int Computer::a_cut(vector<vector<int> > board, int depth, int b){


	if (is_full(board) || depth<0) //ÂúÁË»òÕßËÑË÷µ½Ò¶×Ó 
		return eliminate(board);

	int max = -100000;
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (max >= b){
				print(board);
				_cprintf("depth:");
				stringstream ss;
				ss << depth;
				string s;
				ss >> s;
				s += " ";
				_cprintf(s.c_str());
				_cprintf("score:");
				ss << max;
				ss >> s;
				s += " ";
				_cprintf(s.c_str());
				_cprintf("Alpha cuting...\n");
				return max;
			}
			else if (is_valid(board, make_pair(i, j))){
				board[i][j] = 2;
				int tem = b_cut(board, depth - 1, max);
				if (is_win(board, 2)) tem = 1000 - depth;
				max = max > tem ? max : tem;
				board[i][j] = 0;
			}
		}
	}
	return max;
}


int Computer::b_cut(vector<vector<int> > board, int depth, int a){
	if (is_full(board) || depth<0) //ÂúÁË»òÕßËÑË÷µ½Ò¶×Ó 
		return eliminate(board);

	int min = 100000;
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (min <= a) {
				print(board);
				_cprintf("depth:");
				stringstream ss;
				ss << depth;
				string s;
				ss >> s;
				s += " ";
				_cprintf(s.c_str());
				_cprintf("score:");
				ss << min;
				ss >> s;
				s += " ";
				_cprintf(s.c_str());
				_cprintf("beta cuting...\n");
				return min;
			}
			else if (is_valid(board, make_pair(i, j))){

				board[i][j] = 1;

				int tem = a_cut(board, depth - 1, min);
				if (is_win(board, 1))  tem = -1000 + depth;
				min = min > tem ? tem : min;
				board[i][j] = 0;
			}
		}
	}
	return min;
}

int Computer::eliminate(vector<vector<int> >board){
	return eliminate_part(board, 2) - eliminate_part(board, 1);
}

int Computer::eliminate_part(vector<vector<int> >board, int now){

	int count = 0;
	if (is_win(board, now)) count += 1000;
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++)
		if (board[i][j] == 0) board[i][j] = now;
	}

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j< BOARD_SIZE; j++){
			int now = board[i][j];
			if (now == 0) continue;
			int k = 0;
			//¼ì²éºá 
			if (j <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i][j + k] != now) break;
			if (k == WIN_SIZE) count++;

			//¼ì²éÊú
			if (i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j] != now) break;
			if (k == WIN_SIZE) count++;

			//¼ì²é×óÐ±
			if (j >= WIN_SIZE - 1 && i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j - k] != now) break;
			if (k == WIN_SIZE) count++;

			//¼ì²éÓÒÐ±
			if (j <= BOARD_SIZE - WIN_SIZE&&i <= BOARD_SIZE - WIN_SIZE)
			for (k = 0; k < WIN_SIZE; k++)
			if (board[i + k][j + k] != now) break;
			if (k == WIN_SIZE) count++;
		}
	}
	return count;

}


void print(vector<vector<int> > board){
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++)
		if (board[i][j] == 1) {
			string s = "|X|";
			_cprintf(s.c_str());
			//cout << "|X|";
		}
		else if (board[i][j] == 2){
			string s = "|O|";
			_cprintf(s.c_str());
			//cout << "|O|";
		}
		else {
			string s = "| |";
			_cprintf(s.c_str());
		//	cout << "| |";
		}
		_cprintf("\n");
	}


	cout << endl << endl;
}