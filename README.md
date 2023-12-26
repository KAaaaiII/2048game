[toc]

# C++课程设计项目报告：2048小游戏

> 使用集成开发环境为Visual Studio 2022社区版，C++编写

## 一、小组分工

## 二、游戏规则

2048作为一个经久不衰的小游戏，游戏规则较为基础

1. 初始地图为一个**4\*4**的网格，每一个网格均为空
2. 开始游戏后，每轮随机在一个空网格内生成一个数字**2**
3. 玩家有四种操作，分别为上移、下移、左移、右移
4. 每次操作，地图中所有数字都会向所选方向移动，补足该方向一侧的空格
5. 当该方向相邻两格中数字相同，两数字合成为原数字数值的两倍，每个数字每轮仅合并一次
6. 每次合并，玩家获得合并后数值的分数
7. 胜利条件：成功合成出2048($2^{11}$)，玩家获胜
8. 游戏结束条件：玩家成功合成2048，或所有网格被数字填满，无法再移动，游戏结束，玩家失败

## 三、游戏界面设计

由于时间比较紧张，并未使用easyx等图形库，主要通过控制台输出

1. 标题“2048 game”
2. 玩家得分、用户名
3. 游戏主界面，包含一个**4\*4**的网格，通过for循环输出‘|’与‘-’构建。数据结构是一个二维数组``Map[i][j]``，储存每格中的数值

```c++
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
```

4. 为了更好的游戏体验，我们采用了windows.h库内部的光标操作，隐藏了控制台的光标，hideCursor函数如下：

``` c++
void hideCursor() {//隐藏光标操作，这里参考了一些网上的做法
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = 0;
	cursor.dwSize = 1;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hOut, &cursor);
}
```

## 四、程序设计

### （一）数据结构设计

游戏类``game2048``,包括数据成员整型二维数组``Map[N+2][N+2]``,用于存储网格中的数字，整型变量``score``、``maxsq``、``sumsq``，分别表示玩家得分、场上最大方块数值、场上方块数目总和，以及一个字符串``player``，存储玩家用户名。另外有相应的函数，见[五、系统实现](##五、系统实现)

```c++
class game2048{
public: 
    void initializing(){...}
    void hideCurdor(){...}
    bool over(){...}
    void generate(){...}
    void print(){...}
    void up(){...}
    void down(){...}
    void left(){...}
    void right(){...}
    void move(){...}
    void run(){...}
protected:
	int Map[N + 2][N + 2];//地图二维数组
	int score;//分数
	string player;
	int maxsq;//最大方块数值
	int sumsq; // 场上方块总数    
};
```

### （二）程序流程设计

<img src="https://i.miji.bid/2023/12/26/12704259eab0ee4df19e31dca67392dd.png" style="zoom:100%;" />

### （三）交互方式设计

1. 用户名输入

2. 通过\_getch()获取用户键盘按键，且\_getch()无回显，对应按键数值如下

   > 上: 72
   > 下: 80
   > 左: 75
   > 右: 77 

3. 游戏结束结算

   ```c++
   if (sumsq == N * N && over()) {//满了，检测是否可以移动
   	cout << "GAME OVER! You got " << score << " points" << endl;//无法移动，游戏结束
   	system("pause");
   	return;
   }
   if (maxsq == 2048) {//合并到2048，游戏胜利
   	cout << "You win!" << endl;
   	system("pause");
   	return;
   }
   ```

4. 光标隐藏（见上）

## 五、系统实现

### （一）初始化函数initializing

```c++
void initializing(string str) {//类的初始化
	memset(Map, 0, sizeof(Map));//初始化地图二维数组
	score = 0;
	maxsq = 0;
	sumsq = 0;
	player = str;
}
```

### （二）游戏运行函数run

```C++
void run() {//游戏运行函数
	system("title 2048");//利用system设置窗口名称
	hideCursor();//隐藏光标，否则影响观感
	generate();
	sumsq++;
	while (1) {//开始游戏
		hideCursor();
		if (sumsq == N * N && over()) {//满了，检测是否可以移动
			cout << "GAME OVER! You got " << score << " points" << endl;//无法移动，游戏结束
			system("pause");
			return;
		}
		if (maxsq == 2048) {//合并到2048，游戏胜利
			cout << "You win!" << endl;
			system("pause");
			return;
		}
		print();//更新地图
		move();//移动操作
		system("cls");
	}
}
```

### （三）操作函数move

```c++
void move() {
	int key = _getch();
	key = _getch();//读取键盘输入，无回显
	switch (key) {//键盘输入了什么呢，72上箭头，80下箭头，75左箭头，77右箭头
	case 72: up(); break;
	case 80: down(); break;
	case 75: left(); break;
	case 77: right(); break;
	}
}
```

### （四）检验函数over

```c++
bool over() {//判断是否有可合并项存在
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Map[i][j] == Map[i - 1][j] || Map[i][j] == Map[i + 1][j] || Map[i][j] == Map[i][j + 1] || Map[i][j] == Map[i][j - 1]) {
				return 0;//有两相同项相邻，可操作
			}
		}
	}
	return 1;//无法操作，游戏结束
}
```

## 六、完整源代码

``` c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<time.h>
#include<string>
#include<windows.h>//与windows以及窗口相关的头文件,用到system里的cls、pause、命名窗口
#include<conio.h>//控制台输入输出，_getch()函数
using namespace std;
const int N = 4;//边长
class game2048 {//创建游戏相关的类
public:
	void initializing(string str) {//类的初始化
		memset(Map, 0, sizeof(Map));//初始化地图二维数组
		score = 0;
		maxsq = 0;
		sumsq = 0;
		player = str;
	}
	void hideCursor() {//隐藏光标操作，这里参考了一些网上的做法，用到头文件windows.h中的函数
		CONSOLE_CURSOR_INFO cursor;
		cursor.bVisible = 0;
		cursor.dwSize = 1;
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorInfo(hOut, &cursor);
	}
	bool over() {//判断是否有可合并项存在
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (Map[i][j] == Map[i - 1][j] || Map[i][j] == Map[i + 1][j] || Map[i][j] == Map[i][j + 1] || Map[i][j] == Map[i][j - 1]) {
					return 0;//有两相同项相邻，可操作
				}
			}
		}
		return 1;//无法操作，游戏结束
	}
	void generate() {
		srand(time(0));
		int x = rand() % N + 1, y = rand() % N + 1;
		while (Map[x][y]) {
			x = rand() % N + 1;
			y = rand() % N + 1;
		}//随机寻找一个位置，知道该位置为空，填入2
		Map[x][y] = 2;
	}
	void print() {//打印地图,由'-'和'|'构成
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
	void up() {//up,down,right,left操作类似，以up为例子
		bool ismove = 0;
		int i = N;//从最下方向上扫
		for (int j = 1; j <= N; j++) {
			int k = i + 1, flag = 0, y1 = 0, ismerge = 0, isag = 0;//flag表示该循环下是否移动，y1表示是否找到了非零点，ismerge是否有合并操作，isag是否已经扫描过一遍
			while (1) {
				k--;//向上寻找
				if (k == 0) {//到顶端
					if (flag)k = i, flag = 0, y1 = 0, isag = 1;//移动过，再扫一次
					else break;//无法再移动，跳出
				}
				if (Map[k][j])y1 = 1;//找到一处非零，开始处理
				if (!Map[k][j] && y1 == 1) {//若此行为零，将下面一行上移
					Map[k][j] = Map[k + 1][j];
					Map[k + 1][j] = 0;
					flag = 1;//此次循环已移动
					ismove = 1;//整个过程已经移动
					continue;
				}
				if (Map[k][j] == Map[k + 1][j] && y1 == 1 && (!ismerge && !isag)) {//可与下面一行合并，是第一次循环（若多次循环合并出现多次合并现象），最近一次未合并（否则连续合并多次）
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
				if (ismerge >= 2)ismerge = 0;//未合并，下次可以合并
			}
		}
		if (sumsq != N * N&&ismove) {//已经移动过，且没有满，继续随机产生一个2
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
		key = _getch();//读取键盘输入，无回显
		switch (key) {//键盘输入了什么呢，72上箭头，80下箭头，75左箭头，77右箭头
		case 72: up(); break;
		case 80: down(); break;
		case 75: left(); break;
		case 77: right(); break;
		}
	}
	void run() {//游戏运行函数
		system("title 2048");//利用system设置窗口名称
		hideCursor();//隐藏光标，否则影响观感
		generate();
		sumsq++;
		while (1) {//开始游戏
			hideCursor();
			if (sumsq == N * N && over()) {//满了，检测是否可以移动
				cout << "GAME OVER! You got " << score << " points" << endl;//无法移动，游戏结束
				system("pause");
				return;
			}
			if (maxsq == 2048) {//合并到2048，游戏胜利
				cout << "You win!" << endl;
				system("pause");
				return;
			}
			print();//更新地图
			move();//移动操作
			system("cls");
		}
	}
protected:
	int Map[N + 2][N + 2];//地图二维数组
	int score;//分数
	string player;
	int maxsq;//最大方块数值
	int sumsq; // 场上方块总数
};
int main() {
	srand(time(0));
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
```

## 七、结果展示

见视频
