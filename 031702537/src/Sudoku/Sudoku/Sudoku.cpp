﻿# include "pch.h"
# include <iostream>
# include <fstream>
# include <string>
# include <math.h>
using namespace std;
int num_list[10][10] = { 0 };

int check(int h, int l, int m) {
	int num[10] = { 0 };
	for (int bh = 0; bh < m; bh++) {		//遍历行，寻找重复的数字
		if (num_list[bh][l] != 0) {
			num[num_list[bh][l]]++;
			if (num[num_list[bh][l]] > 1)
				return 0;
		}
	}
	for (int i = 0; i < 10; i++) {
		num[i] = 0;
	}
	for (int bl = 0; bl < m; bl++) {		//遍历列，寻找重复的数字
		if (num_list[h][bl] != 0) {
			num[num_list[h][bl]]++;
			if (num[num_list[h][bl]] > 1)
				return 0;
		}
	}
	for (int i = 0; i < 10; i++) {
		num[i] = 0;
	}
	if (m == 4 || m == 8 || m == 9 || m == 6) {
		int max_h = 0, max_l = 0;					//检验九宫格，寻找重复的数字
		int gong_h = 0, gong_l = 0;
		if (m == 4 || m == 8 || m == 9) {
			gong_l = (int)sqrt(m);
			gong_h = (int)(m / gong_l);
		}
		else if (m == 6) {
			gong_h = (int)sqrt(m);
			gong_l = (int)(m / gong_h);
		}
		for (int i = 1; i < m; i++) {
			max_h = i * gong_h;
			if (max_h > h) {
				break;
			}
		}
		for (int i = 1; i < m; i++) {
			max_l = i * gong_l;
			if (max_l > l) {
				break;
			}
		}
		for (int i = max_h - gong_h; i < max_h; i++) {
			for (int j = max_l - gong_l; j < max_l; j++) {
				if (num_list[i][j] != 0) {
					num[num_list[i][j]]++;
					if (num[num_list[i][j]] > 1)
						return 0;
				}
			}
		}
	}

	return 1;
}

int DFS(int n, int m)
{
	if (n > (m*m)) {
		return 1;
	}
	if (num_list[n / m][n % m] != 0)		// 不需要填数字，则跳过
	{
		if (DFS(n + 1, m) == 1)  
			return 1;
	}
	else
	{
		for (int i = 1; i <= m; i++)		//试填1-m的数字 
		{
			num_list[n / m][n % m] = i;
			if (check(n / m, n % m, m) == 1)
			{
				if (DFS(n + 1, m) == 1)
					return 1;				//返回时如果构造成功，则返回1
				else
					num_list[n / m][n % m] = 0;
			}
			else
				num_list[n / m][n % m] = 0;
		}
	}
	return 0;
}

int weiyu(int m) {
	cout << "使用唯余法" << endl;
	int h, l;
	int may_count;
	int count = 0;
	for (h = 0; h < m; h++) {
		for (l = 0; l < m; l++) {
			if (num_list[h][l] == 0)
				count++;
		}
	}
	for (h = 0; h < m; h++) {
		for (l = 0; l < m; l++) {
			if (num_list[h][l] == 0) {
				int may_num[10] = { 0 };
				may_count = m;
				for (int bh = 0; bh < m; bh++) {		//遍历行
					if (num_list[bh][l] != 0) {
						if (may_num[num_list[bh][l]] == 0)
							may_count--;
						may_num[num_list[bh][l]] = 1;
					}
				}
				for (int bl = 0; bl < m; bl++) {		//遍历列
					if (num_list[h][bl] != 0) {
						if (may_num[num_list[h][bl]] == 0)
							may_count--;
						may_num[num_list[h][bl]] = 1;
					}
				}
				if (m == 4 || m == 6 || m == 8 || m == 9) {				//遍历宫格
					int max_h = 0, max_l = 0;								
					int gong_h = 0, gong_l = 0;

					//定位当前格在属于第几宫格
					if (m == 4 || m == 8 || m == 9) {			
						gong_l = (int)sqrt(m);
						gong_h = (int)(m / gong_l);
					}
					else if (m == 6) {
						gong_h = (int)sqrt(m);
						gong_l = (int)(m / gong_h);
					}
					for (int i = 1; i < m; i++) {
						max_h = i * gong_h;
						if (max_h > h) {
							break;
						}
					}
					for (int i = 1; i < m; i++) {
						max_l = i * gong_l;
						if (max_l > l) {
							break;
						}
					}

					//开始遍历
					for (int i = max_h - gong_h; i < max_h; i++) {
						for (int j = max_l - gong_l; j < max_l; j++) {
							if (i > 9)		//消除警告
								i = 9;
							if (i < 0)
								i = 0;
							if (j > 9)
								j = 9;
							if (j < 0)
								j = 0;
							if (num_list[i][j] != 0) {
								if (may_num[num_list[i][j]] == 0)
									may_count--;
								may_num[num_list[i][j]] = 1;
							}
						}

					}
				}
				if (may_count == 1) {					//填写数字
					for (int i = 1; i <= m; i++) {
						if (may_num[i] == 0) {
							num_list[h][l] = i;
							h = 0;
							l = -1;
							count--;				//填写成功，未填数减一
							if (count == 0) {
								printf("成功\n");
								return 0;		//完成数独，返回0
							}
							break;
						}
					}
				}
			}
		}
	}
	return 1;		//未完成数独，返回1
}


int main(int   argc, char*   argv[])
{
	char* i;
	char* o;
	int m, n, h, l;
	string list;

	m = atoi(argv[2]);
	n = atoi(argv[4]);
	i = argv[6];
	ifstream fin(i);
	if (!fin.is_open())
	{
		cout << "输入文件不存在";
		return 0;
	}
	o = argv[8];
	ofstream fout(o);

	h = 0;
	for (int c = 0; c < n; c++) {
		h = 0;
		while (!fin.eof()) {			//文件输入
			getline(fin, list);
			if (list.length() != 2 * m && list.length() != 2 * m - 1) {		//表格输入不规范，与阶数m不相符则退出
				cout << "表格大小不符合";
				return 0;
			}
			for (l = 0; l < m; l++) {
				num_list[h][l] = list[l * 2] - 48;
				if (num_list[h][l] < 0 || num_list[h][l]>9) {		//表格输入不规范，出现非数字字符则退出
					cout << "九宫格中出现不是0-9的数字";
					return 0;
				}
			}
			h++;
			if (h == m) {
				getline(fin, list);
				break;
			}
		}

		if (weiyu(m) == 1)		//先使用唯余法，如果不行，则用DFS
		{
			cout << "使用DFS" << endl;
			DFS(0, m);
			cout << "成功" << endl;
		}
		for (h = 0; h < m; h++) {			//文件输出
			for (l = 0; l < m; l++) {
				fout << num_list[h][l];
				if (l != m - 1)
					fout << ' ';
				else
					fout << '\n';
			}
		}
		fout << '\n';
	}
	return 0;
}
