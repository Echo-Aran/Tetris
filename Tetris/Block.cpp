#include "Block.h"

#include<time.h>

//һ��4*2�Ķ�ά�����ʾ����˹�����ĳ����̬
//һ�ֶ���˹������Ҫ4��/2����ά���飬��Ϊ��4��/2����̬
int Block::size = 18;
IMAGE* Block::imgs[7] = { NULL };
int Blocks[7][4] = {
		1,3,5,7,//I
		2,4,5,7,//Z1
		3,4,5,6,//Z2
		3,4,5,7,//T
		2,3,5,7,//L
		3,5,6,7,//J
		2,3,4,5//��
};

//��Ա�ĳ�ʼ��
Block::Block()
{
	//�ز�ֻ��ʼ��һ��
	if (imgs[0]==NULL)
	{
		IMAGE BCMetrial;
		for (int i = 0; i < 7; i++) {

			loadimage(&BCMetrial,_T("D:\\Code\\Tetris\\images\\tiles.png"));
			//����image����Ϊ��ǰ�Ļ�ͼ�豸��֮�����еĻ�ͼ��䶼������ڸ�image����
			SetWorkingImage(&BCMetrial);
			for (int i = 0; i < 7; i++)
			{
				imgs[i] = new IMAGE;
				getimage(imgs[i],size * i, 0, size, size);
			}
		}

		SetWorkingImage();//��NULL�ָ�Ĭ��

		srand(time(NULL));
	}

	//��������ݣ�ÿ����һ���µķ��飬��Ҫִ��
	blockType = 1 + rand() % 7;//1-8,��Ϊ�����imgs[0~7]
	img = imgs[blockType - 1];

	for (int i = 0; i < 4; i++) {
		smallBlock[i].col = Blocks[blockType - 1][i] / 2;
		smallBlock[i].row = Blocks[blockType - 1][i] % 2;
	}
}

void Block::draw(int LeftMargin, int TopMargin)
{
	for (int i = 0; i < 4; i++)
	{
		putimage(smallBlock[i].col*size+LeftMargin, smallBlock[i].row * size+TopMargin,img );
	}
}

void Block::drop()
{
	for (auto &block : smallBlock) {
		block.row++;
	}
}

IMAGE** Block::getImages()
{
	return imgs;
}

int Block::getblockType() const
{
	return blockType;
}

bool Block::BlockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();

	for (auto& block : smallBlock) {
		if (block.col < 0 || block.col >= cols || block.row < 0 || block.row >= rows || map[block.row][block.col] != 0)
		{
			return false;
		}
	}
	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for (auto& block : smallBlock) {
		map[block.row][block.col] = blockType;
	}
}

Block& Block::operator=(const Block& other)
{

	//printf("%p", &other);

	if (this == &other) {
		return *this;
	}
	int other_blockType = 0;//ΪʲôҪ����Ϊstatic
	//printf("%p\n", &other);
	other_blockType = other.blockType;
	this->blockType = other_blockType;
	for (int i = 0; i < 4; i++) {
		this->smallBlock[i] = other.smallBlock[i];
	}
	return *this;
}



void Block::rotate()
{
	Point p = smallBlock[1];
	for (int i = 0; i < 4; i++)
	{
		Point tmp = smallBlock[i];
		smallBlock[i].col = p.col - tmp.row + p.row;
		smallBlock[i].row = p.row + tmp.col - p.col;

	}
}

void Block::moveLeftRight(int offset)
{
	for (int i = 0; i < 4; i++) {
		smallBlock[i].col += offset;
	}
}