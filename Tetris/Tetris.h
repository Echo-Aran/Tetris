#pragma once
#include"Block.h"
#include<vector>
using namespace std;

class Tetris
{
public:
	//设置游戏相关属性，比如是n*n的俄罗斯方块？背景板的布置，区域的划分等
	Tetris(int rows, int cols, int left, int top, int blockSize);
	//游戏初始化
	void init();
	//游戏主体架构（逻辑）
	void play();
	//游戏结束
	void checkOver();

	int score;
	void drawScore();//绘制当前分数

	IMAGE background;//wcnm!!!!你个图片要个毛的权限啊
private:
	int delay;
	bool update;
	
	void drop();
	void updateWindow();
	void clearLine();//更新游戏的数据
	int getDelay();
	void keyEvent();
	void moveleftRight(int offset);


	Block* curBlock;
	Block* nextBlock;
	Block backBlock;

	//表示游戏状态的数据
	static unsigned int lastTime;
	int _rows;
	int _cols;
	int LeftMargin;
	int TopMargin;
	int blockSize;
	bool gameOver;//设置一个状态，而不是通过函数的返回值实现
	vector<vector<int>> map;//记录目前场上的信息 为0没有方块，有方块的地方的颜色 
};

