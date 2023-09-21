#include<iostream>
#include <conio.h>

using namespace std;
#include"Tetris.h"
#include"Block.h"
int main()
{
	//创建一个俄罗斯方块类型的游戏 game.
	Tetris game(20,10,28,30,18);

	game.play();

	system("pause");//_getch();
	closegraph();

	return 0;
}
