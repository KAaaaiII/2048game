#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<time.h>
#include<string>
#include<windows.h>//��windows�Լ�������ص�ͷ�ļ�,�õ�system���cls��pause����������
#include<conio.h>//����̨���������_getch()����
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
	bool over() {//�ж��Ƿ��пɺϲ������
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (Map[i][j] == Map[i - 1][j] || Map[i][j] == Map[i + 1][j] || Map[i][j] == Map[i][j + 1] || Map[i][j] == Map[i][j - 1]) {
					return 0;//������ͬ�����ڣ��ɲ���
				}
			}
		}
		return 1;//�޷���������Ϸ����
	}
	void generate() {
		srand(time(0));
		int x = rand() % N + 1, y = rand() % N + 1;
		while (Map[x][y]) {
			x = rand() % N + 1;
			y = rand() % N + 1;
		}//���Ѱ��һ��λ�ã�֪����λ��Ϊ�գ�����2
		Map[x][y] = 2;
	}
	void print() {//��ӡ��ͼ,��'-'��'|'����
		cout << setw((5 * N + 4)/2+5) << "2048 game" << endl;
		cout << "score: " << score << " Player: " << player << endl;
		cout << "  ";
		for (int i = 1; i <= 5 * N + 1; i++)cout << '-';
		cout << endl;
		for (int i = 1; i <= N; i++) {
			cout << " ";
			cout << '|';
			for (int j = 1; j <= N; j++) {
				if (Map[i][j]) {
					cout << setw(4) << Map[i][j];
					cout << '|';
				}
				else cout << setw(5) << '|';
			}
			cout << endl;
			cout << "  ";
			for (int i = 1; i <= N * 5 + 1; i++) cout << '-';
			cout << endl;
		}
	}
	void up() {//up,down,right,left�������ƣ���upΪ����
		bool ismove = 0;
		int i = N;//�����·�����ɨ
		for (int j = 1; j <= N; j++) {
			int k = i + 1, flag = 0, y1 = 0, ismerge = 0, isag = 0;//flag��ʾ��ѭ�����Ƿ��ƶ���y1��ʾ�Ƿ��ҵ��˷���㣬ismerge�Ƿ��кϲ�������isag�Ƿ��Ѿ�ɨ���һ��
			while (1) {
				k--;//����Ѱ��
				if (k == 0) {//������
					if (flag)k = i, flag = 0, y1 = 0, isag = 1;//�ƶ�������ɨһ��
					else break;//�޷����ƶ�������
				}
				if (Map[k][j])y1 = 1;//�ҵ�һ�����㣬��ʼ����
				if (!Map[k][j] && y1 == 1) {//������Ϊ�㣬������һ������
					Map[k][j] = Map[k + 1][j];
					Map[k + 1][j] = 0;
					flag = 1;//�˴�ѭ�����ƶ�
					ismove = 1;//���������Ѿ��ƶ�
					continue;
				}
				if (Map[k][j] == Map[k + 1][j] && y1 == 1 && (!ismerge && !isag)) {//��������һ�кϲ����ǵ�һ��ѭ���������ѭ���ϲ����ֶ�κϲ����󣩣����һ��δ�ϲ������������ϲ���Σ�
					Map[k][j] *= 2;
					Map[k + 1][j] = 0;
					score += Map[k][j];
					maxsq = max(maxsq, Map[k][j]);
					sumsq--;
					flag = 1;
					ismove = 1;
					ismerge = 1;
					continue;
				}
				if (ismerge)ismerge++;
				if (ismerge >= 2)ismerge = 0;//δ�ϲ����´ο��Ժϲ�
			}
		}
		if (sumsq != N * N&&ismove) {//�Ѿ��ƶ�������û�����������������һ��2
			sumsq++;
			generate();
		}
	}
	void down() {
		bool ismove = 0;
		int i = 1;
		for (int j = 1; j <= N; j++) {
			int k = i - 1, flag = 0, y1 = 0, ismerge = 0, isag = 0;
			while (1) {
				k++;
				if (k == N + 1) {
					if (flag)k = i, flag = 0, y1 = 0, isag = 1;
					else break;
				}
				if (Map[k][j])y1 = 1;
				if (!Map[k][j] && y1 == 1) {
					Map[k][j] = Map[k - 1][j];
					Map[k - 1][j] = 0;
					flag = 1;
					ismove = 1;
					continue;
				}
				if (Map[k][j] == Map[k - 1][j] && y1 == 1 && (!ismerge && !isag)) {
					Map[k][j] *= 2;
					Map[k - 1][j] = 0;
					score += Map[k][j];
					maxsq = max(maxsq, Map[k][j]);
					sumsq--;
					flag = 1;
					ismove = 1;
					ismerge = 1;
					continue;
				}
				if (ismerge)ismerge++;
				if (ismerge >= 2)ismerge = 0;
			}
		}
		if (sumsq != N * N && ismove) {
			sumsq++;
			generate();
		}
	}
	void left() {
		bool ismove = 0;
		for (int i = 1; i <= N; i++) {
			int j = N;
			int k = j + 1, flag = 0, y1 = 0, ismerge = 0, isag = 0;
			while (1) {
				k--;
				if (k == 0) {
					if (flag)k = j, flag = 0, y1 = 0, isag = 1;
					else break;
				}
				if (Map[i][k])y1 = 1;
				if (!Map[i][k] && y1 == 1) {
					Map[i][k] = Map[i][k + 1];
					Map[i][k + 1] = 0;
					flag = 1;
					ismove = 1;
					continue;
				}
				if (Map[i][k] == Map[i][k + 1] && y1 == 1 && (ismerge == 0 && !isag)) {
					Map[i][k] *= 2;
					Map[i][k + 1] = 0;
					score += Map[i][k];
					maxsq = max(maxsq, Map[i][k]);
					sumsq--;
					flag = 1;
					ismove = 1;
					ismerge = 1;
					continue;
				}
				if (ismerge)ismerge++;
				if (ismerge >= 2)ismerge = 0;
			}
		}
		if (sumsq != N * N && ismove) {
			sumsq++;
			generate();
		}
	}
	void right() {
		bool ismove = 0;
		for (int i = 1; i <= N; i++) {
			int j = 1;
			int k = j - 1, flag = 0, y1 = 0, ismerge = 0, isag = 0;
			while (1) {
				k++;
				if (k == N + 1) {
					if (flag)k = j, flag = 0, y1 = 0, isag = 1;
					else break;
				}
				if (Map[i][k])y1 = 1;
				if (!Map[i][k] && y1 == 1) {
					Map[i][k] = Map[i][k - 1];
					Map[i][k - 1] = 0;
					flag = 1;
					ismove = 1;
					continue;
				}
				if (Map[i][k] == Map[i][k - 1] && y1 == 1 && (!ismerge && isag == 0)) {
					Map[i][k] *= 2;
					Map[i][k - 1] = 0;
					score += Map[i][k];
					maxsq = max(maxsq, Map[i][k]);
					sumsq--;
					flag = 1;
					ismove = 1;
					ismerge = 1;
					continue;
				}
				if (ismerge)ismerge++;
				if (ismerge >= 2)ismerge = 0;
			}
			
		}
		if (sumsq != N * N && ismove) {
			sumsq++;
			generate();
		}
	}
	void move() {
		int key = _getch();
		key = _getch();//��ȡ�������룬�޻���
		switch (key) {//����������ʲô�أ�72�ϼ�ͷ��80�¼�ͷ��75���ͷ��77�Ҽ�ͷ
		case 72: up(); break;
		case 80: down(); break;
		case 75: left(); break;
		case 77: right(); break;
		}
	}
	void run() {//��Ϸ���к���
		system("title 2048");//����system���ô�������
		hideCursor();//���ع�꣬����Ӱ��۸�
		generate();
		sumsq++;
		while (1) {//��ʼ��Ϸ
			hideCursor();
			if (sumsq == N * N && over()) {//���ˣ�����Ƿ�����ƶ�
				cout << "GAME OVER! You got " << score << " points" << endl;//�޷��ƶ�����Ϸ����
				system("pause");
				return;
			}
			if (maxsq == 2048) {//�ϲ���2048����Ϸʤ��
				cout << "You win!" << endl;
				system("pause");
				return;
			}
			print();//���µ�ͼ
			move();//�ƶ�����
			system("cls");
		}
	}
protected:
	int Map[N + 2][N + 2];//��ͼ��ά����
	int score;//����
	string player;
	int maxsq;//��󷽿���ֵ
	int sumsq; // ���Ϸ�������
};
int main() {
	srand(time(0));
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