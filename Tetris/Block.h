#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
struct Point
{
	int row;
	int col;
};

//һ�ַ��顢һ������
class Block
{
public:
	//����·���ĳ�ʼ��
	Block();
	//����
	void draw(int LeftMargin,int TopMargin);
	//��ת
	void rotate();
	//�½�
	void drop();
	//�����ƶ�
	void moveLeftRight(int offset);
	//Ϊ����ṩ��ȡ������زĵĽӿ�
	static IMAGE** getImages();
	//��ȡ
	int getblockType()const;//const��operator=
	//�жϷ����Ƿ��ڵ�ͼ��
	bool BlockInMap(const vector<vector<int>>& map);
	//�̶��ڵ�ͼ��
	void solidify(vector<vector<int>>& map);
	Block& operator=(const Block& other);

public:
	int blockType;
	Point smallBlock[4];//���block ��С���������

private:
	IMAGE* img;//С������ز�
	
	static int size ;
	static IMAGE* imgs[7];//�洢��ͬ��ɫС����ĵ��ز�
	
};