#include<iostream>
#include<vector>
#include<algorithm>
#include<conio.h>
using namespace std;
#define number 10
#define n number*2+1
int board[n][n];
int board2[number][number] = { 0 };
int visit[number][number] = { 0 };
vector<pair<int, int>>vv;
int sw = 1;
int o = 1, oo = 0;
void wall() {
	while (1) {
		int max = 0;
		int ii, jj;
		for (int i = 0; i < number; i++) {
			for (int j = 0; j < number; j++) {
				if (max < board2[i][j]) {
					max = board2[i][j];
					ii = i;
					jj = j;
				}
			}
		}
		int best = 0;
		int r = 0, c = 0;
		if (max == 0)return;
		if (ii + 1 < number && best < board2[ii + 1][jj]) {
			best = board2[ii + 1][jj];
			r = ii + 1;
			c = jj;
		}
		if (ii - 1 > -1 && best < board2[ii - 1][jj]) {
			best = board2[ii - 1][jj];
			r = ii - 1;
			c = jj;
		}
		if (jj + 1 < number && best < board2[ii][jj + 1]) {
			best = board2[ii][jj + 1];
			r = ii;
			c = jj + 1;
		}
		if (jj - 1 > -1 && best < board2[ii][jj - 1]) {
			best = board2[ii][jj - 1];
			r = ii;
			c = jj - 1;
		}
		board2[ii][jj] = 0;
		ii *= 2;
		jj *= 2;
		r *= 2;
		c *= 2;
		ii++, jj++, r++, c++;
		r = (r + ii) / 2;
		c = (c + jj) / 2;
		board[r][c] = 1;
	}
}
void dfs(int i, int j) {
	if (visit[i][j])return;
	vv.push_back(make_pair(i, j));
	visit[i][j]++;
	board2[i][j] = sw++;
	vector<pair<int, int>>v;
	if (i + 1 < number && !visit[i + 1][j])v.push_back(make_pair(i + 1, j));
	if (i - 1 > -1 && !visit[i - 1][j])v.push_back(make_pair(i - 1, j));
	if (j + 1 < number && !visit[i][j + 1])v.push_back(make_pair(i, j + 1));
	if (j - 1 > -1 && !visit[i][j - 1])v.push_back(make_pair(i, j - 1));
	random_shuffle(v.begin(), v.end());
	for (int ii = 0; ii < v.size(); ii++) {
		dfs(v[ii].first, v[ii].second);
	}
	return;
}
void print() {
	system("cls");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 0)cout << char(219) << char(219);
			else if (board[i][j] == 2)cout << "\x1B[36m" << char(219) << char(219) << "\033[0m";
			else cout << "  ";
		}
		cout << endl;
	}
}
bool win() {
	if (board[number * 2 - 1][number * 2] == 2)return 1;
	return 0;
}
void main() {
	srand(time(0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			board[i * 2 + 1][j * 2 + 1] = 1;
		}
	}
	board[o][oo] = 2;
	board[number * 2 - 1][number * 2] = 1;
	dfs(0, 0);
	wall();
	print();
	while (1) {
		if (win())break;
		if (_kbhit()) {
			char c = _getch();
			if (c == 'd') {
				oo++;
				if (board[o][oo] == 1) {
					board[o][oo] = 2;
					print();
				}
				else if (board[o][oo] == 2) {
					board[o][--oo] = 1;
					oo++;
					print();
				}
				else {
					oo--;
				}
			}
			else if (c == 'a') {
				oo--;
				if (board[o][oo] == 1) {
					board[o][oo] = 2;
					print();
				}
				else if (board[o][oo] == 2) {
					board[o][++oo] = 1;
					oo--;
					print();
				}
				else {
					oo++;
				}
			}
			else if (c == 's') {
				o++;
				if (board[o][oo] == 1) {
					board[o][oo] = 2;
					print();
				}
				else if (board[o][oo] == 2) {
					board[--o][oo] = 1;
					o++;
					print();
				}
				else {
					o--;
				}
			}
			else if (c == 'w') {
				o--;
				if (board[o][oo] == 1) {
					board[o][oo] = 2;
					print();
				}
				else if (board[o][oo] == 2) {
					board[++o][oo] = 1;
					o--;
					print();
				}
				else {
					o++;
				}
			}
		}
	}
	cout << "\x1B[36myou won\033[0m";

}