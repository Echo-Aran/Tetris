#include "Block.h"

#include<time.h>

//一个4*2的二维数组表示俄罗斯方块的某种形态
//一种俄罗斯方块需要4个/2个二维数组，因为有4种/2种形态
int Block::size = 18;
IMAGE* Block::imgs[7] = { NULL };
int Blocks[7][4] = {
		1,3,5,7,//I
		2,4,5,7,//Z1
		3,4,5,6,//Z2
		3,4,5,7,//T
		2,3,5,7,//L
		3,5,6,7,//J
		2,3,4,5//田
};

//成员的初始化
Block::Block()
{
	//素材只初始化一次
	if (imgs[0]==NULL)
	{
		IMAGE BCMetrial;
		for (int i = 0; i < 7; i++) {

			loadimage(&BCMetrial,_T("D:\\Code\\Tetris\\images\\tiles.png"));
			//将该image设置为当前的绘图设备，之后所有的绘图语句都会绘制在该image上面
			SetWorkingImage(&BCMetrial);
			for (int i = 0; i < 7; i++)
			{
				imgs[i] = new IMAGE;
				getimage(imgs[i],size * i, 0, size, size);
			}
		}

		SetWorkingImage();//传NULL恢复默认

		srand(time(NULL));
	}

	//下面的内容，每创建一种新的方块，都要执行
	blockType = 1 + rand() % 7;//1-8,因为下面的imgs[0~7]
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
	int other_blockType = 0;//为什么要声明为static
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