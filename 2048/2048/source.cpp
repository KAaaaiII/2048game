#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include<windows.h>//��windows�Լ�������ص�ͷ�ļ�
#include<conio.h>//����̨�������
using namespace std;
const int N = 4;//�߳�
class game2048 {//������Ϸ��ص���
public:


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