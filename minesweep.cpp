#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>

enum op {//用枚举函数做出开头，0为退出，1为开始
	EXIT,
	PLAY
};

void menu() {
	printf("1  play\n");
	printf("0  exit\n");//打印菜单
}

void init_board(char board[100][100], int x, int y) {//传入二维数组和行列要求，将整个数组初始化为空格
	char c = ' ';
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			board[i][j] = c;
		}
	}
}

void init_mine(char mine[100][100], int x, int y) {//同上另建一数组作为隐藏雷区，初始化为空格
	char c = ' ';
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			mine[i][j] = c;
		}
	}
}

void get_mine(char mine[100][100], int x, int y, int num) {//对雷区数组进行操作，传入行列和要填入的雷数
	int x1, y1;
	int mine_num = num;
	while (mine_num) {
	loop:
		x1 = rand() % x + 1;
		y1 = rand() % y + 1;
		if (mine[x1][y1] != '*') {//用随机函数产生一个随机坐标填入雷，如果有雷跳过
			mine[x1][y1] = '*';
		}
		else
			goto loop;
		mine_num = mine_num - 1;//成功填入一个雷后num-1，直到为0退出函数
	}
}

void print_board(char board[100][100], int x, int y) {//此函数用来打印用户操作的板
	int i, j;
	printf("  ");
	for (i = 1; i <= y; i++)
		printf("  %d ", i);//打印上边框的横向序号即列数
	printf("\n");
	for (i = 1; i <= x; i++) {
		printf("  ");
		for (j = 1; j <= y; j++)
			printf("|---");//换行后打印上边框及第一行所有左边框
		printf("|\n");
		printf("%2d", i);//打印上一行最后一个右边框，换行后打印当前行的序号
		for (j = 1; j <= y; j++)
			printf("| %c ", board[i][j]);//打印当前行所有的左边框及相应坐标中内容
		printf("|\n");//打印最后一个框的右边框换行
	}
	printf("  ");
	for (j = 1; j <= y; j++)
		printf("|---");//打印下边框
	printf("|\n");
}

char is_mine_num(char mine[100][100], char board[100][100], int x, int y) {//此函数用来查所选坐标周围雷数
	int count = 0;
	if (mine[x - 1][y - 1] == '*')count++;
	if (mine[x - 1][y] == '*')count++;
	if (mine[x - 1][y + 1] == '*')count++;
	if (mine[x][y - 1] == '*')count++;
	if (mine[x][y + 1] == '*')count++;
	if (mine[x + 1][y - 1] == '*')count++;
	if (mine[x + 1][y] == '*')count++;
	if (mine[x + 1][y + 1] == '*')count++;//周围八个方向每有一个雷count+1
	board[x][y] = (count + '0');//如果周围没有雷，返回0
	return board[x][y];
}

void play_game(char mine[100][100], char board[100][100], int x, int y, int num) {//此函数为玩法
	int count = x * y - num;//count代表安全区数量
	int x2, y2;
	while (count) {
	loop:
		printf("玩家：\n请输入你的选择坐标(行、列)>:");
		scanf_s("%d %d", &x2, &y2);
		if ((x2 < 1 || x2 > x) || (y2 > x || y2 < 1)) {//读入玩家输入合法的坐标后清空界面，无效便重输
			printf("输入坐标无效！请重新输入。\n");
			goto loop;
		}
		system("cls");
		if (mine[x2][y2] == '*') {
			int i, j;
			if (count == (x * y - num)) {//如果踩到雷的是第一步，为使游戏继续，进行如下操作
			rand:
				i = rand() % x + 1;
				j = rand() % y + 1;//随机选出一个坐标
				if (mine[i][j] == ' ') {//如果该坐标无雷就将踩到的雷移至该坐标
					mine[i][j] = '*';
					mine[x2][y2] = ' ';
					count--;//安全区-1
					if (count == 0) {//如果玩家设计的模式只有一个安全区，那么直接胜利
						printf("恭喜你扫雷完成\n");
						return;
					}
					board[x2][y2] = is_mine_num(mine, board, x2, y2);//对操作后的所选坐标查周围雷数后继续游戏
					print_board(board, x, y);
					goto loop;
				}
				else
					goto rand;//如果随机选出的坐标有雷就另选
			}
			else {
				printf("踩地雷了！\n");//如果踩雷的不是第一步，说明并退出
				return;
			}
		}
		else {
			board[x2][y2] = is_mine_num(mine, board, x2, y2);
			print_board(board, x, y);
		}
		count--;
	}
	printf("恭喜你扫雷完成\n");//count减为0时玩家胜出
}

int main() {
	int input = 0;
	char board[100][100];
	char mine[100][100];
	srand((unsigned)time(NULL));//设置rand()随机序列种子，使产生的随机数不同
	do {
		menu();//打印菜单
	loop:
		printf("请选择>>：");
		scanf_s("%d", &input);
		if (input != 0 && input != 1) {
			printf("选择错误，请重新选择。\n");//玩家选择开始游戏或退出
			goto loop;
		}
		switch (input) {
		case PLAY:
			int x, y, num;
			printf("请输入行数、列数及雷数:");
			scanf_s("%d %d %d", &x, &y, &num);//先请玩家自定义要玩的模式
			while (x * y < num) {
				printf("输入雷数过多，请重新输入：\n");
				printf("请输入行数、列数及雷数:");
				scanf_s("%d %d %d", &x, &y, &num);
			}
			system("cls");
			printf("游戏开始：\n");
			init_mine(mine, x, y);
			init_board(board, x, y);
			get_mine(mine, x, y, num);
			print_board(board, x, y);
			play_game(mine, board, x, y, num);
			print_board(mine, x, y);//依次调用以上诸函数，游戏结束后打印全部雷区
			break;
		case EXIT:
			printf("退出游戏！\n");
			break;
		}
	} while (input);//返回菜单选择重新开始或退出
	return 0;
}