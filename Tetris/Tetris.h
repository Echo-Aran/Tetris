#pragma once
#include"Block.h"
#include<vector>
using namespace std;

class Tetris
{
public:
	//������Ϸ������ԣ�������n*n�Ķ���˹���飿������Ĳ��ã�����Ļ��ֵ�
	Tetris(int rows, int cols, int left, int top, int blockSize);
	//��Ϸ��ʼ��
	void init();
	//��Ϸ����ܹ����߼���
	void play();
	//��Ϸ����
	void checkOver();

	int score;
	void drawScore();//���Ƶ�ǰ����

	IMAGE background;//wcnm!!!!���ͼƬҪ��ë��Ȩ�ް�
private:
	int delay;
	bool update;
	
	void drop();
	void updateWindow();
	void clearLine();//������Ϸ������
	int getDelay();
	void keyEvent();
	void moveleftRight(int offset);


	Block* curBlock;
	Block* nextBlock;
	Block backBlock;

	//��ʾ��Ϸ״̬������
	static unsigned int lastTime;
	int _rows;
	int _cols;
	int LeftMargin;
	int TopMargin;
	int blockSize;
	bool gameOver;//����һ��״̬��������ͨ�������ķ���ֵʵ��
	vector<vector<int>> map;//��¼Ŀǰ���ϵ���Ϣ Ϊ0û�з��飬�з���ĵط�����ɫ 
};

