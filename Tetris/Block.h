#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
struct Point
{
	int row;
	int col;
};

//一种方块、一个方块
class Block
{
public:
	//完成新方块的初始化
	Block();
	//绘制
	void draw(int LeftMargin,int TopMargin);
	//旋转
	void rotate();
	//下降
	void drop();
	//左右移动
	void moveLeftRight(int offset);
	//为外界提供获取方块的素材的接口
	static IMAGE** getImages();
	//获取
	int getblockType()const;//const和operator=
	//判断方块是否在地图内
	bool BlockInMap(const vector<vector<int>>& map);
	//固定在地图上
	void solidify(vector<vector<int>>& map);
	Block& operator=(const Block& other);

public:
	int blockType;
	Point smallBlock[4];//组成block 的小方格的坐标

private:
	IMAGE* img;//小方块的素材
	
	static int size ;
	static IMAGE* imgs[7];//存储不同颜色小方块的的素材
	
};