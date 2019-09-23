# include "pch.h"
# include <iostream>
# include <fstream>
# include <string>
# include <math.h>
using namespace std;
int num_list[10][10] = { 0 };

int check(int h,int l,int m) {
	int num[10] = {0};
	for (int bh = 0; bh < m; bh++) {		//遍历行
		if (num_list[bh][l] != 0) {
			num[num_list[bh][l]]++;
			if (num[num_list[bh][l]] > 1)
				return 0;
		}
	}
	for (int i = 0; i < 10; i++) {
		num[i] = 0;
	}
	for (int bl = 0; bl < m; bl++) {		//遍历列
		if (num_list[h][bl] != 0) {
			num[num_list[h][bl]]++;
			if (num[num_list[h][bl]] > 1)
				return 0;
		}
	}
	for (int i = 0; i < 10; i++) {
		num[i] = 0;
	}
	if (m == 4 || m == 8 || m == 9) {
		int max_h, max_l;								//检验九宫格
		int gong_h, gong_l;
		gong_l = (int)sqrt(m);
		gong_h = (int)(m / gong_l);
		for (int i = 0; i < m; i++) {
			max_h = i * gong_h;
			if (max_h > h) {
				break;
			}
		}
		for (int i = 0; i < m; i++) {
			max_l = i * gong_l;
			if (max_l > l) {
				break;
			}
		}
		if (max_l > 9)
			max_l = 9;
		if (max_h > 9)
			max_h = 9;
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
	if (m == 6) {
		int max_h, max_l;								//检验九宫格
		int gong_h, gong_l;
		gong_h = (int)sqrt(m);
		gong_l = (int)(m / gong_h);
		for (int i = 0; i < m; i++) {
			max_h = i * gong_h;
			if (max_h > h) {
				break;
			}
		}
		for (int i = 0; i < m; i++) {
			max_l = i * gong_l;
			if (max_l > l) {
				break;
			}
		}
		int i,j;
		i = max_h - gong_h;
		j = max_l - gong_l;
		for (; i < max_h; i++) {
			for (; j < max_l; j++) {
				if (num_list[i][j] != 0 && i != h && j != l) {
					num[num_list[i][j]]++;
					if (num[num_list[i][j]] > 1)
						return 0;
				}
			}
		}
	}
	return 1;
}

int DFS(int n,int m)
{
	if (n > (m*m)) {
		return 1;
	}
	if (num_list[n / m][n % m] != 0)
	{
		if (DFS(n + 1, m) == 1)  // 继续搜索
			return 1;
	}
	else
	{
		//否则对当前位进行枚举测试 
		for (int i = 1; i <= m; i++)
		{
			num_list[n / m][n % m] = i;
			if (check(n / m, n % m, m) == 1)
			{
				if (DFS(n + 1, m) == 1)  // 继续搜索
					return 1;
					//返回时如果构造成功，则直接退出
				else
					num_list[n / m][n % m] = 0;
			}
			else
				num_list[n / m][n % m] = 0;
		}
	}
	return 0;
}

void count_157(int m) {
	cout << "使用唯余法"<<endl;
	int h, l;
	int may_count;
	int count = 0;
	for (h = 0; h < m; h++) {
		for (l = 0; l < m; l++) {
			if (num_list[h][l] == 0)
				count++;
		}
	}
	//printf("%d\n", count);
	for (h = 0; h < m; h++) {
		for (l = 0; l < m; l++) {
			if (num_list[h][l] == 0) {
				int may_num[10] = { 0 };
				may_count = m;
				for (int bh = 0; bh < m; bh++) {		//遍历行
					if (num_list[bh][l] != 0) {
						if (may_num[num_list[bh][l]] == 0)
							may_count--;
						//printf("%d,", may_count);
						may_num[num_list[bh][l]] = 1;
					}
					//printf("%d,", may_count);
				}
				for (int bl = 0; bl < m; bl++) {		//遍历列
					if (num_list[h][bl] != 0) {
						if (may_num[num_list[h][bl]] == 0)
							may_count--;
						may_num[num_list[h][bl]] = 1;
					}
					//printf("%d,", may_count);
				}
				if (may_count == 1) {					//填写数字
					for (int i = 1; i <= m; i++) {
						if (may_num[i] == 0) {
							num_list[h][l] = i;
							/*for (int j = 0; j < m; j++) {
								for (int k = 0; k < m; k++)
									cout << num_list[j][k];
								cout << endl;
							}*/
							h = 0;
							l = -1;
							count--;
							printf("%d\n", count);
							if (count == 0) {
								printf("成功\n");
								return;
							}
							break;
						}
					}
				}
			}
		}
	}
	if (count > 0)
	{
		cout << "使用DFS" << endl;
		DFS(0, m);
		cout << "成功" << endl;
	}
}

void count_489(int m) {
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
	//printf("%d\n", count);
	for (h = 0; h < m; h++) {
		for (l = 0; l < m; l++) {
			if (num_list[h][l] == 0) {
				int may_num[10] = { 0 };
				may_count = m;
				for (int bh = 0; bh < m; bh++) {		//遍历行
					if (num_list[bh][l] != 0) {
						if (may_num[num_list[bh][l]] == 0)
							may_count--;
						//printf("%d,", may_count);
						may_num[num_list[bh][l]] = 1;
					}
					//printf("%d,", may_count);
				}
				for (int bl = 0; bl < m; bl++) {		//遍历列
					if (num_list[h][bl] != 0) {
						if (may_num[num_list[h][bl]] == 0)
							may_count--;
						may_num[num_list[h][bl]] = 1;
					}
					//printf("%d,", may_count);
				}
				int max_h, max_l;								//遍历九宫格
				int gong_h, gong_l;
				gong_l = (int)sqrt(m);
				gong_h = (int)(m / gong_l);
				for (int i = 0; i < m; i++) {
					max_h = i * gong_h;
					if (max_h > h) {
						break;
					}
				}
				for (int i = 0; i < m; i++) {
					max_l = i * gong_l;
					if (max_l > l) {
						break;
					}
				}
				for (int i = max_h - gong_h; i < max_h; i++) {
					for (int j = max_l - gong_l; j < max_l; j++) {
						if (num_list[i][j] != 0) {
							if (may_num[num_list[i][j]] == 0)
								may_count--;
							may_num[num_list[i][j]] = 1;
						}
					}

				}

				if (may_count == 1) {					//填写数字
					for (int i = 1; i <= m; i++) {
						if (may_num[i] == 0) {
							num_list[h][l] = i;
							/*for (int j = 0; j < m; j++) {
								for (int k = 0; k < m; k++)
									cout << num_list[j][k];
								cout << endl;
							}*/
							h = 0;
							l = -1;
							count--;
							if (count == 0) {
								printf("成功\n");
								return;
							}
							break;
						}
					}
				}
			}
		}
	}
	if (count > 0)
	{
		cout << "使用DFS" << endl;
		DFS(0, m);
		cout << "成功" << endl;
	}
}

void count_6(int m) {
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
	//printf("%d\n", count);
	for (h = 0; h < m; h++) {
		for (l = 0; l < m; l++) {
			if (num_list[h][l] == 0) {
				int may_num[10] = { 0 };
				may_count = m;
				for (int bh = 0; bh < m; bh++) {		//遍历行
					if (num_list[bh][l] != 0) {
						if (may_num[num_list[bh][l]] == 0)
							may_count--;
						//printf("%d,", may_count);
						may_num[num_list[bh][l]] = 1;
					}
					//printf("%d,", may_count);
				}
				for (int bl = 0; bl < m; bl++) {		//遍历列
					if (num_list[h][bl] != 0) {
						if (may_num[num_list[h][bl]] == 0)
							may_count--;
						may_num[num_list[h][bl]] = 1;
					}
					//printf("%d,", may_count);
				}
				int max_h, max_l;								//遍历九宫格
				int gong_h, gong_l;
				gong_h = (int)sqrt(m);
				gong_l = (int)(m / gong_h);
				for (int i = 0; i < m; i++) {
					max_h = i * gong_h;
					if (max_h > h) {
						break;
					}
				}
				for (int i = 0; i < m; i++) {
					max_l = i * gong_l;
					if (max_l > l) {
						break;
					}
				}
				for (int i = max_h - gong_h; i < max_h; i++) {
					for (int j = max_l - gong_l; j < max_l; j++) {
						if (num_list[i][j] != 0) {
							if (may_num[num_list[i][j]] == 0)
								may_count--;
							may_num[num_list[i][j]] = 1;
						}
					}

				}

				if (may_count == 1) {					//填写数字
					for (int i = 1; i <= m; i++) {
						if (may_num[i] == 0) {
							num_list[h][l] = i;
							h = 0;
							l = -1;
							count--;
							printf("%d\n", count);
							if (count == 0) {
								printf("成功\n");
								return;
							}
							break;
						}
					}
				}
			}
		}
	}
	if (count > 0)
	{
		cout << "使用DFS"<<endl;
		DFS(0, m);
		cout << "成功" << endl;
	}
}

int main(int   argc, char*   argv[])
{
	char* i;
	char* o;
	int m, n,h,l;
	string list;

	m = (int)*argv[2] - 48;
	n = (int)*argv[4] - 48;
	i = argv[6];
	ifstream fin(i);
	o = argv[8];
	ofstream fout(o);

	h = 0;
	for (int c = 0; c < n; c++) {
		h = 0;
		while (!fin.eof()) {			//文件输入
			getline(fin, list);
			for (l = 0; l < m; l++)
				num_list[h][l] = list[l*2] - 48;
			h++;
			if (h == m) {
				getline(fin, list);
				break;
			}
		}
	if (m == 1 || m == 5 || m == 7) {
		count_157(m);
	}
	else if (m == 4 || m == 8 || m == 9) {
		count_489(m);
	}
	else if (m == 6) {
		count_6(m);
	}
	for (h = 0; h < m; h++) {			//文件输出
		for (l = 0; l < m; l++) {
			fout << num_list[h][l];
			if(l != m-1)
				fout << ' ';
			else
				fout << '\n';
		}
	}
	fout << '\n';
	}
	return 0;
}
