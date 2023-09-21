#include "Tetris.h"
#include<time.h>
#include<conio.h>
#include<iostream>
using namespace std;
const int Speed_Normal = 500;//ms
const int Speed_Quick = 50;

//基础属性的设置
Tetris::Tetris(int rows, int cols, int left, int top, int block_size)
	:_rows(rows)
	,_cols(cols)
	,LeftMargin(left)
	,TopMargin(top)
	,blockSize(block_size)
	,score(0)
	,gameOver(false)
{

	for (int i = 0; i <_rows ; i++)
	{
		vector<int> row;
		for (int j = 0; j <_cols ; j++)
		{
			row.push_back(0);
		}
		map.push_back(row);
	}

	delay = Speed_Normal;
	curBlock = nullptr;
	nextBlock = nullptr;
	update = false;
}

//初始化背景，地图
void Tetris::init()
{
	delay = Speed_Normal;
	//配置随机种子
	srand(time(NULL));
	//创建游戏窗口
	initgraph(320, 480, EX_SHOWCONSOLE);//初始化图形界面

	//加载背景图片
	loadimage(&background, _T("D:\\Code\\Tetris\\images\\background.png"));//这个函数用于从文件中读取图像。
	//putimage(0, 0, &background);

	//初始化游戏区中的数据
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			map[i][j] = 0;
		}
	}
}

void Tetris::play()
{
	init();

	//定义定时器
	int timer = 0;
	putimage(0, 0, &background);

	//初始化第一个方块和预告方块
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	while (1)
	{
		//接受用户输入
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			update = true;
		}
		//刷新游戏画面
		if (update) {
			update = false;
			updateWindow();
			clearLine();
		}

		checkOver();
		if (gameOver)
		{
			break;
		}
	}
}

void Tetris::drawScore()
{
	setcolor(RGB(255,0,0));
	settextstyle(60, 0, _T("楷体"));
	//string scoreTest;
	TCHAR scoreTest[32];
	_stprintf_s(scoreTest,_T("%d"), score);

	setbkmode(TRANSPARENT);
	outtextxy(254, 395, scoreTest);
}


//在地图上的固定
void Tetris::drop()
{
	backBlock = *curBlock;
	curBlock->drop();

	if (!curBlock->BlockInMap(map)) {
		//将这个方块固化
		backBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}

	//检查游戏是否已经结束

	delay = Speed_Normal;//加速下落后要能回到正常速度
}

//刷新绘制方块
void Tetris::updateWindow()
{
	BeginBatchDraw();//实现批量绘图，以消除闪烁

		putimage(0, 0, &background);//绘制背景图片

		IMAGE** imgs = Block::getImages();//获取方块素材信息
		//获取地图上的信息，在地图上绘制方块
		for (int i = 0; i < _rows; i++)	{
			for (int j = 0; j < _cols; j++) {
				if (map[i][j] == 0) {
					continue;//说明是空白位置
				}
				int x = j * blockSize + LeftMargin;
				int y = i * blockSize + TopMargin;
				putimage(x, y, imgs[map[i][j] - 1]);
			}
		}

		curBlock->draw(LeftMargin, TopMargin);
		nextBlock->draw(240, 65);//预告方块
		drawScore();

	EndBatchDraw();
}

void Tetris::clearLine()
{
	int k = _rows - 1;
	for (int i = _rows - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < _cols; j++)
		{
			if (map[i][j]) { count++; }
			//边存边找
			map[k][j] = map[i][j];
		}

		if (count != _cols)
		{
			k--;
		}
		else
		{
			score += 10;
			update = true;//随时刷新
		}
	}
}

//获取延时
int Tetris::getDelay()
{
	//第一次调用，返回0
	//返回距离上一次调用，间隔了多少ms

	static unsigned int lastTime=0;
	unsigned int currentTime=GetTickCount();
	/*cout << lastTime << endl;
	cout << currentTime << endl;*/

	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret=currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}

}

void Tetris::keyEvent()
{
	//char -128~127
	unsigned char ch;//0~255
	bool isRotate = false;
	int dx = 0;

	//这个按回车才表示真正的输入
	//getchar();

	while(_kbhit())//防止阻塞
	{
		ch=_getch();//按一个按键直接输入
		/*cout << ch << endl;*/
		//如果按下向下方向键，
		
		switch (ch)
		{
		case 'w':
			isRotate = true;
			break;
		case 's':
			delay = Speed_Quick;
			break;
		case 'a':
			dx = -1;
			break;
		case 'd':
			dx = 1;
			break;
		default:
			break;
		}

		/*if (ch == 244)
		{
			ch = _getch();
			switch (ch)
			{
			case 72:
				isRotate = true;
				break;
			case 80:
				delay = Speed_Quick;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}*/

	}
	if (isRotate)
	{
		if(curBlock->getblockType()==7)
		{
			return;
		}


		//实现旋转
		backBlock = *curBlock;
		curBlock->rotate();

		if (!curBlock->BlockInMap(map))
		{
			*curBlock = backBlock;
		}

	}

	if (dx != 0)
	{
		moveleftRight(dx);
		update = true;
	}

	
}

void Tetris::moveleftRight(int offset)
{
	//先备份
	backBlock = *curBlock;
	curBlock->moveLeftRight(offset);
	//判断移动后有没有越界,不对就还原
	if (!curBlock->BlockInMap(map))
	{
		*curBlock = backBlock;
	}
}
void Tetris::checkOver()
{
	/*gameOver = !curBlock->BlockInMap(map)*/
	for (int j = 0; j < _cols; j++)
	{
		if (map[1][j]!=0)
		{
			Sleep(1000);
			gameOver = true;
			return;
		}
	}
	gameOver = false;
	
}