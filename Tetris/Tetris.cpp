#include "Tetris.h"
#include<time.h>
#include<conio.h>
#include<iostream>
using namespace std;
const int Speed_Normal = 500;//ms
const int Speed_Quick = 50;

//�������Ե�����
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

//��ʼ����������ͼ
void Tetris::init()
{
	delay = Speed_Normal;
	//�����������
	srand(time(NULL));
	//������Ϸ����
	initgraph(320, 480, EX_SHOWCONSOLE);//��ʼ��ͼ�ν���

	//���ر���ͼƬ
	loadimage(&background, _T("D:\\Code\\Tetris\\images\\background.png"));//����������ڴ��ļ��ж�ȡͼ��
	//putimage(0, 0, &background);

	//��ʼ����Ϸ���е�����
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			map[i][j] = 0;
		}
	}
}

void Tetris::play()
{
	init();

	//���嶨ʱ��
	int timer = 0;
	putimage(0, 0, &background);

	//��ʼ����һ�������Ԥ�淽��
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	while (1)
	{
		//�����û�����
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			update = true;
		}
		//ˢ����Ϸ����
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
	settextstyle(60, 0, _T("����"));
	//string scoreTest;
	TCHAR scoreTest[32];
	_stprintf_s(scoreTest,_T("%d"), score);

	setbkmode(TRANSPARENT);
	outtextxy(254, 395, scoreTest);
}


//�ڵ�ͼ�ϵĹ̶�
void Tetris::drop()
{
	backBlock = *curBlock;
	curBlock->drop();

	if (!curBlock->BlockInMap(map)) {
		//���������̻�
		backBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}

	//�����Ϸ�Ƿ��Ѿ�����

	delay = Speed_Normal;//���������Ҫ�ܻص������ٶ�
}

//ˢ�»��Ʒ���
void Tetris::updateWindow()
{
	BeginBatchDraw();//ʵ��������ͼ����������˸

		putimage(0, 0, &background);//���Ʊ���ͼƬ

		IMAGE** imgs = Block::getImages();//��ȡ�����ز���Ϣ
		//��ȡ��ͼ�ϵ���Ϣ���ڵ�ͼ�ϻ��Ʒ���
		for (int i = 0; i < _rows; i++)	{
			for (int j = 0; j < _cols; j++) {
				if (map[i][j] == 0) {
					continue;//˵���ǿհ�λ��
				}
				int x = j * blockSize + LeftMargin;
				int y = i * blockSize + TopMargin;
				putimage(x, y, imgs[map[i][j] - 1]);
			}
		}

		curBlock->draw(LeftMargin, TopMargin);
		nextBlock->draw(240, 65);//Ԥ�淽��
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
			//�ߴ����
			map[k][j] = map[i][j];
		}

		if (count != _cols)
		{
			k--;
		}
		else
		{
			score += 10;
			update = true;//��ʱˢ��
		}
	}
}

//��ȡ��ʱ
int Tetris::getDelay()
{
	//��һ�ε��ã�����0
	//���ؾ�����һ�ε��ã�����˶���ms

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

	//������س��ű�ʾ����������
	//getchar();

	while(_kbhit())//��ֹ����
	{
		ch=_getch();//��һ������ֱ������
		/*cout << ch << endl;*/
		//����������·������
		
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


		//ʵ����ת
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
	//�ȱ���
	backBlock = *curBlock;
	curBlock->moveLeftRight(offset);
	//�ж��ƶ�����û��Խ��,���Ծͻ�ԭ
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