#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>

enum op {//��ö�ٺ���������ͷ��0Ϊ�˳���1Ϊ��ʼ
	EXIT,
	PLAY
};

void menu() {
	printf("1  play\n");
	printf("0  exit\n");//��ӡ�˵�
}

void init_board(char board[100][100], int x, int y) {//�����ά���������Ҫ�󣬽����������ʼ��Ϊ�ո�
	char c = ' ';
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			board[i][j] = c;
		}
	}
}

void init_mine(char mine[100][100], int x, int y) {//ͬ����һ������Ϊ������������ʼ��Ϊ�ո�
	char c = ' ';
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			mine[i][j] = c;
		}
	}
}

void get_mine(char mine[100][100], int x, int y, int num) {//������������в������������к�Ҫ���������
	int x1, y1;
	int mine_num = num;
	while (mine_num) {
	loop:
		x1 = rand() % x + 1;
		y1 = rand() % y + 1;
		if (mine[x1][y1] != '*') {//�������������һ��������������ף������������
			mine[x1][y1] = '*';
		}
		else
			goto loop;
		mine_num = mine_num - 1;//�ɹ�����һ���׺�num-1��ֱ��Ϊ0�˳�����
	}
}

void print_board(char board[100][100], int x, int y) {//�˺���������ӡ�û������İ�
	int i, j;
	printf("  ");
	for (i = 1; i <= y; i++)
		printf("  %d ", i);//��ӡ�ϱ߿�ĺ�����ż�����
	printf("\n");
	for (i = 1; i <= x; i++) {
		printf("  ");
		for (j = 1; j <= y; j++)
			printf("|---");//���к��ӡ�ϱ߿򼰵�һ��������߿�
		printf("|\n");
		printf("%2d", i);//��ӡ��һ�����һ���ұ߿򣬻��к��ӡ��ǰ�е����
		for (j = 1; j <= y; j++)
			printf("| %c ", board[i][j]);//��ӡ��ǰ�����е���߿���Ӧ����������
		printf("|\n");//��ӡ���һ������ұ߿���
	}
	printf("  ");
	for (j = 1; j <= y; j++)
		printf("|---");//��ӡ�±߿�
	printf("|\n");
}

char is_mine_num(char mine[100][100], char board[100][100], int x, int y) {//�˺�����������ѡ������Χ����
	int count = 0;
	if (mine[x - 1][y - 1] == '*')count++;
	if (mine[x - 1][y] == '*')count++;
	if (mine[x - 1][y + 1] == '*')count++;
	if (mine[x][y - 1] == '*')count++;
	if (mine[x][y + 1] == '*')count++;
	if (mine[x + 1][y - 1] == '*')count++;
	if (mine[x + 1][y] == '*')count++;
	if (mine[x + 1][y + 1] == '*')count++;//��Χ�˸�����ÿ��һ����count+1
	board[x][y] = (count + '0');//�����Χû���ף�����0
	return board[x][y];
}

void play_game(char mine[100][100], char board[100][100], int x, int y, int num) {//�˺���Ϊ�淨
	int count = x * y - num;//count����ȫ������
	int x2, y2;
	while (count) {
	loop:
		printf("��ң�\n���������ѡ������(�С���)>:");
		scanf_s("%d %d", &x2, &y2);
		if ((x2 < 1 || x2 > x) || (y2 > x || y2 < 1)) {//�����������Ϸ����������ս��棬��Ч������
			printf("����������Ч�����������롣\n");
			goto loop;
		}
		system("cls");
		if (mine[x2][y2] == '*') {
			int i, j;
			if (count == (x * y - num)) {//����ȵ��׵��ǵ�һ����Ϊʹ��Ϸ�������������²���
			rand:
				i = rand() % x + 1;
				j = rand() % y + 1;//���ѡ��һ������
				if (mine[i][j] == ' ') {//������������׾ͽ��ȵ���������������
					mine[i][j] = '*';
					mine[x2][y2] = ' ';
					count--;//��ȫ��-1
					if (count == 0) {//��������Ƶ�ģʽֻ��һ����ȫ������ôֱ��ʤ��
						printf("��ϲ��ɨ�����\n");
						return;
					}
					board[x2][y2] = is_mine_num(mine, board, x2, y2);//�Բ��������ѡ�������Χ�����������Ϸ
					print_board(board, x, y);
					goto loop;
				}
				else
					goto rand;//������ѡ�����������׾���ѡ
			}
			else {
				printf("�ȵ����ˣ�\n");//������׵Ĳ��ǵ�һ����˵�����˳�
				return;
			}
		}
		else {
			board[x2][y2] = is_mine_num(mine, board, x2, y2);
			print_board(board, x, y);
		}
		count--;
	}
	printf("��ϲ��ɨ�����\n");//count��Ϊ0ʱ���ʤ��
}

int main() {
	int input = 0;
	char board[100][100];
	char mine[100][100];
	srand((unsigned)time(NULL));//����rand()����������ӣ�ʹ�������������ͬ
	do {
		menu();//��ӡ�˵�
	loop:
		printf("��ѡ��>>��");
		scanf_s("%d", &input);
		if (input != 0 && input != 1) {
			printf("ѡ�����������ѡ��\n");//���ѡ��ʼ��Ϸ���˳�
			goto loop;
		}
		switch (input) {
		case PLAY:
			int x, y, num;
			printf("����������������������:");
			scanf_s("%d %d %d", &x, &y, &num);//��������Զ���Ҫ���ģʽ
			while (x * y < num) {
				printf("�����������࣬���������룺\n");
				printf("����������������������:");
				scanf_s("%d %d %d", &x, &y, &num);
			}
			system("cls");
			printf("��Ϸ��ʼ��\n");
			init_mine(mine, x, y);
			init_board(board, x, y);
			get_mine(mine, x, y, num);
			print_board(board, x, y);
			play_game(mine, board, x, y, num);
			print_board(mine, x, y);//���ε��������������Ϸ�������ӡȫ������
			break;
		case EXIT:
			printf("�˳���Ϸ��\n");
			break;
		}
	} while (input);//���ز˵�ѡ�����¿�ʼ���˳�
	return 0;
}