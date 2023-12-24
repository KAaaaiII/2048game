#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include<windows.h>//与windows以及窗口相关的头文件
#include<conio.h>//控制台输入输出
using namespace std;
const int N = 4;//边长
class game2048 {//创建游戏相关的类
public:


protected:
	int Map[N + 2][N + 2];//地图二维数组
	int score;//分数
	string player;
	int maxsq;//最大方块数值
	int sumsq; // 场上方块总数
};
int main() {
	game2048 g;
	string username;
	cout << "请输入你的用户名:" << endl;
	getline(cin, username);
	g.initializing(username);
	cout << "按下任意键开始游戏" << endl;
	system("pause");
	system("cls");
	g.run();
	return 0;
}