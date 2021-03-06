#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;
void search_all_path(int s, double **a, int *c, int *min_c, int &sum, int &min_sum, int prev, int first, int step) {
	for (int i = 0; i < s; i++) {
		if (c[i] == 0 && a[prev][i] != 0) {
			c[i] = step;
			int new_sum = sum + a[prev][i];
			search_all_path(s, a, c, min_c, new_sum, min_sum, i, first, step + 1);
			bool is_all = true;
			for (int j = 0; j < s; j++) {
				if (c[j] == 0) {
					is_all = false;
					break;
				}
			}
			if (is_all && a[i][first] != 0) {
				new_sum = sum + a[i][first] + a[prev][i];
				if (new_sum < min_sum || min_sum == -1) {
					min_sum = new_sum;
					for (int i = 0; i < s; i++) {
						min_c[i] = c[i];
					}
				}
			}
			c[i] = 0;
		}
	}
}
void СML(int s, double **a, int *min, int &e) {
	int sum = 0;
	int min_sum = -1;
	int *c = new int[s];
	int *min_c = new int[s];
	for (int j = 0; j < s; j++)
		c[j] = 0;
	c[0] = 1;
	search_all_path(s, a, c, min_c, sum, min_sum, 0, 0, 2);
	for (int i = 0; i < s; i++) {
		min[min_c[i] - 1] = i + 1;
	}
	e = min_sum;
}
int main() {
	setlocale(0, "");
	int SIZE = 7;
	int d[7]; // минимальное расстояние
	int v[7]; // посещенные вершины
	int l = 1;
	double **x;
	x = new double*[SIZE];
	for (int i = 0; i < SIZE; i++)
		x[i] = new double[SIZE];
	ofstream fout("result1.txt");
	ifstream in("matrix1.txt");
	if (in.is_open()) {
		int count = 0;
		int temp;
		while (!in.eof()) {
			in >> temp;
			count++;
		}
		in.seekg(0, ios::beg);
		in.clear();
		int count_space = 0;
		char symbol;
		while (!in.eof()) {
			in.get(symbol);
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;
		}
		in.seekg(0, ios::beg);
		in.clear();
		int n = count / (count_space + 1);
		int m = count_space + 1;
		for (int i = 0; i < n; i++) x[i] = new double[m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> x[i][j];
		in.close();
	}
	else {
		cout << "Файл не найден.";
	}
	int w = 0;
	СML(SIZE, x, d, w);
	for (int i = 0; i < SIZE; i++) {
		printf("%d", d[i]);
		printf(" ");
		fout << d[i] << " ";
	}
	printf("\nКонтур минимальной длины: %d", w);
	fout << "\n" << w;
	printf("\n");
	fout.close();
	system("pause");
	getchar(); getchar();
	return 0;
}


