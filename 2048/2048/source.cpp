#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include<windows.h>//��windows�Լ�������ص�ͷ�ļ�
#include<conio.h>//����̨�������
using namespace std;
const int N = 4;//�߳�
class game2048 {//������Ϸ��ص���
public:
	void initializing(string str) {//��ĳ�ʼ��
		memset(Map, 0, sizeof(Map));//��ʼ����ͼ��ά����
		score = 0;
		maxsq = 0;
		sumsq = 0;
		player = str;
	}
	void hideCursor() {//���ع�����������ο���һЩ���ϵ��������õ�ͷ�ļ�windows.h�еĺ���
		CONSOLE_CURSOR_INFO cursor;
		cursor.bVisible = 0;
		cursor.dwSize = 1;
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorInfo(hOut, &cursor);
	}
protected:
	int Map[N + 2][N + 2];//��ͼ��ά����
	int score;//����
	string player;
	int maxsq;//��󷽿���ֵ
	int sumsq; // ���Ϸ�������
};
int main() {
	game2048 g;
	string username;
	cout << "����������û���:" << endl;
	getline(cin, username);
	g.initializing(username);
	cout << "�����������ʼ��Ϸ" << endl;
	system("pause");
	system("cls");
	g.run();
	return 0;
}