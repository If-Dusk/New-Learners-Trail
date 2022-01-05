#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<stdbool.h>

#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'

void welcome();                // ��ʼ����
void Finish();                 // ��������
void Choosing();               // ѡ����� 
void loading();                // ���ؽ���
void creatgraph();             // Χǽ��ӡ
void gotoxy(int x, int y);     // �����ת��xΪ������,yΪ������ 
void gotoprint(int x, int y);  // ��ת��ӡ
void gotodelete(int x, int y); // ��תɾ��
void creatfood();              // ʳ�����
int ClickControl();            // ��ȡ�����ź�
int Judge();                   // ��Ϸ�����ж�
void ExplanaTion();			   // ��Ϸ˵�� 
void RankList();			   // ���а� 
void Rankfile();			   // �������� 
void MovingBody(int n);        // �ߵ��ƶ�
void Eating(int n);            // �߳Ե��������쳤
void ChangeBody(int x, int y); // �ߵ�����任
int theSpeed(int score);	   // �ߵ��ٶȿ��� 
int GameCore(int m);		   // ��Ϸ���岿�� 
void NewChaning();			   // �������
 
/*ȫ�ֱ��� + Ԥ����*/
typedef struct Snakes {
	int x;
	int y;
	struct Snakes* next;
} snake;

snake* head;    // ������ͷָ��

// ����������ʳ��
struct Food {
	int x;
	int y;
} food;

typedef struct {
	char name[20];  // �����û���
	int score0;		// ������� 
}Info; 

Info User; 		// �û����� 
FILE *fp;		// �ļ����� 
int score = 0;  // ����
char click = 1; // ��¼���µļ��̰���
int speed;      // �ٶ� ��ʵ���ӳٵĺ�����
char m; 		// ѡ��

int main() {
	
	system("color 7d"); // ���ÿ���̨������ɫ
	welcome();          // ��ӭ����
	Choosing();			// ѡ����� 
	Rankfile();		    // ���а����ݱ��� 
	NewChaning();		// ���ݳ�ʼ�� 
	return main();		// ���¿�ʼ 
}

void NewChaning() {
	
	score = 0;
	click = 1;
	m = 0;
}

int GameCore(int n) {
	creatgraph();       // ������ͼ
	creatfood();        // �½�ʳ��
	// ������갴�� ClickControl
	if (ClickControl(n) == 0) {
		system("cls");
	}
	return 0;
}

void welcome() {
	gotoxy(15, 10);
	printf("|**********************************************|");
	gotoxy(15, 20);
	printf("|**********************************************|");
	gotoxy(15, 10);
	int i = 0;
	for(i = 0;i<11;i++) {
		printf("|");
		gotoxy(15,10+i);
	}
	gotoxy(62, 10);
	for(i = 0;i<11;i++) {
		printf("|");
		gotoxy(62,10+i);
	}
	gotoxy(20, 13);
	printf("WELCOME TO THE GAME OF RETRO SNAKE");
	gotoxy(20, 18);
	printf("PLEASE ENTER YOUR NAME:");
	scanf("%s",&User.name,20);
	system("cls");
}

void Choosing(){
	gotoxy(45,10); 
	printf("��ѡ����Ϸ�Ѷ�\n");	
	
	gotoxy(45,12);
	printf("1�������Ѷ�\n");
	gotoxy(45,13);
	printf("2�������Ѷ�\n");
	gotoxy(45,14);
	printf("3�����а�\n");
	gotoxy(45,15);
	printf("4����Ϸ˵��\n");
	gotoxy(45,16);
	printf("5���˳���Ϸ\n");
	
	m = getch();
	if(m > '0' && m < '6') {
		system("cls");

		switch(m){
			case '1': {
				int n = 1;
				loading();  // ���ؽ���
				GameCore(1);
				break;        
			}	
				break;
			case '2': {
				int n = 2;
				loading();
				GameCore(2);
				break;
			}
				break;
			case '3': RankList();
				break;
			case '4': ExplanaTion();
				break;
			default : exit(0);
				break;
		}
	}
	
	else {
		printf("����,������ѡ��");
		Choosing();
	}
}

void Rankfile() {
	User.score0 = score; 
	fp = fopen("Ranklist.txt","a");
	if(fp == NULL) {
		printf("���а��޷���");  
        exit(1);
	}
	fprintf(fp,"%s \t\t  %d\n",User.name,User.score0);
	fclose(fp); 
} 

void ExplanaTion() {
	system("cls");
	
	gotoxy(20,10);
	printf("���ŷ�������,�ߵ��ٶȻᷢ���仯");
	gotoxy(20,11);
	printf("��Ҫ��������ֲ���Ŷ");
	gotoxy(20,12);
	printf("?��(??��?)\n");
	gotoxy(20,13);
	printf("w,a,s,d�������������ƶ�");
	gotoxy(20,14);
	printf("�������ͣ,�س���������Ϸ");
	gotoxy(20,15);
	printf("�����ƶ����ڳ��Լ�Ŷ");
	gotoxy(20,16);
	printf("�ǵñ𿪴�д����Ŷ"); 
	gotoxy(20,18);
	printf("��������˳�");
	if(getch()) {
		system("cls");
		Choosing();
	}
}

void RankList(){
	system("cls");
	Info tmp[10];
	Info temp;
	gotoxy(40,40);
	int n = 10,i = 0,j = 0,k = 0;
	fp = fopen("RankList.txt", "rb");
	if(fp == NULL)
	{
		printf("���޼�¼\n");
	}
	
	n = 10;
	for(i=0;i<n-1;i++)//����ð�ݷ��������� 
    {  
		k = i;
		for(j=i+1;j<n;j++) 
	    if(tmp[j].score0>tmp[k].score0)//����Ƚϴ�С  
		k = j;
		temp=tmp[k];
		tmp[k]=tmp[i];
		tmp[i]=temp;//����������ʱ�������ݽ���
	} 
	i = 0;
	gotoxy(23,20);
	printf("���а�\n");
	gotoxy(23,21);
	printf("rank\t\t    name\tscore\n"); 
	while(i <= 5&&fscanf(fp,"%s%d",tmp[i].name,&tmp[i].score0)!=EOF)
	{
	gotoxy(23,22+i);
	printf("%3d%20s  %10d\n",i+1,tmp[i].name,tmp[i].score0);
	i++;
	}
	fclose(fp);
	gotoxy(23,30);
	printf("��������˳�");
	fclose(fp);
	
	if(getch()) {
		system("cls");	
		Choosing();
	}
	
}

void loading() {
	printf("��                              \n");
	printf("��                               \n");
    printf("��                                 * *     \n");
	printf("��                               *     *\n");
	printf("��*                             *         * \n");
    printf("�� *                           *            *  \n");
	printf("��  *                         *               *  \n");
	printf("��   *                       *                  * \n");
	printf("��    *                     *                     * \n");
	printf("��      *                 *                         *\n");
	printf("��        *             *        \n");
	printf("��          *         *          \n");
	printf("��             *   *             \n");
	printf("��                              \n");
	printf("��       ��            ������ \n");
	printf("��      ��  ��        ��     �� \n");
	printf("��    ��     ��      ������o�ѡ� \n");
	printf("��   ��        ��   ����     �� \n");
	printf("��  ��           �� ��      ��   \n");
	printf("�� ������ \n");
	printf("��  \n");
	gotoxy(46,23);
	int i;
	printf("��Ϸ������");
	gotoxy(45,20);
	printf("|");
	gotoxy(56,20);
	printf("|");
	for(i = 1; i<11; i++) {
		gotoxy(45+i,20);
		printf("*");
		gotoxy(50,20);
		printf("%d%%",i*10);
		Sleep(70);
	}
	gotoxy(46,23);
	printf("\n\t\t\t\t\t\t�������");
	printf("\n");
	
	if(getch()) {
		system("cls");
	}
}

void gotoxy(int x, int y) {
	// ���¹��λ��
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
	// ���ع��
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hOutput, &cursor);
}

void gotoprint(int x, int y) {
	gotoxy(x, y);
	printf("��");
}

void gotodelete(int x, int y) {
	gotoxy(x, y);
	printf("  ");
}

void creatgraph() {
	int i;// ��Ϊ����̨�ַ���߱�Ϊ1��2,ÿ��i��2 
	for (i = 0; i < 58; i += 2) {
		Sleep(50);
		gotoprint(i, 0);
		gotoprint(i, 26);
	}
	for (i = 1; i < 26; i++) {
		Sleep(50);
		gotoprint(0, i);
		gotoprint(56, i);
	}
	gotoxy(63, 10);
	printf("Hello %s,Welcome to the Snake", User.name);
	Sleep(50);
	gotoxy(63, 15);
	printf("Your Score Is:%d    ", score);
	Sleep(50);
	head = (snake*)malloc(sizeof(snake));
	snake* p = (snake*)malloc(sizeof(snake));
	snake* q = (snake*)malloc(sizeof(snake));
	head->x = 16;
	head->y = 15;
	p->x = 16;
	p->y = 16;
	q->x = 16;
	q->y = 17;
	head->next = p;
	p->next = q;
	q->next = NULL;
}

// �������һ��ʳ��
void creatfood() {
	bool flag = false;
	while (!flag) {
		flag = true;
		srand((int)time(NULL));
		food.y = rand() % (25 - 1 + 1) + 1;
		food.x = rand() % (54 - 2 + 1) + 2;
		if (food.x % 2 != 0) {
			food.x = food.x + 1;
		}
		snake* judge = head;
		while (1) {        //�����ų������ظ�
			if (judge->next == NULL) break;
			if (food.x == judge->x && food.y == judge->y) {
				flag = false;
			}
			judge = judge->next;
		}
	}
	gotoxy(food.x, food.y);
	printf("��");
}

// ������� ��Ϸ��ѭ��
int ClickControl(int n) {
	char c;
	while (1) {
		if (Judge() == 0) return 0;
		if (kbhit()) {
			click = getch();
		}
		MovingBody(n);
		Eating(n);
	}
	return 1;
}

//�����ƶ� 
void MovingBody(int n) {
	int x = head->x, y = head->y;
	snake* p = head;
	// ͨ������պ��ӡʵ�ֶ���Ч��
	while (p->next != NULL) {
		p = p->next;
	}
	gotodelete(p->x, p->y); // ����β�ڵ�
	switch (click) {
		case up :
			y -= 1;
			break;
		case down :
			y += 1;
			break;
		case left :
			x -= 2;
			break;
		case right :
			x += 2;
			break;
		default:
			break;
	}
	if (x != head->x || y != head->y) {	// �ı�����ʱ���� ��ͣ��Ϸֹͣ������ͷ 
		ChangeBody(x, y);
	}
	p = head;
	// ��ӡ��ͷ
	gotoprint(p->x, p->y);
	
	
	speed = theSpeed(n*score);
	Sleep(speed);
}

int theSpeed(int score) {
	int count = score / 10;
		if (count <= 10) return 150;
		else if (count > 10 && count <= 20) return (100 - count);
		else if (count > 20 && count <= 40) return (80 - count);
		else return 30;
}

// �Ե�ʳ�ﴦ�� ���һ��β��
void Eating(int n) {
	if (head->x == food.x && head->y == food.y) {
		creatfood();
		snake* _new = (snake*)malloc(sizeof(snake));
		snake* p;
		p = head;
		while (1) {
			if (p->next == NULL) break;
			p = p->next;
		}
		p->next = _new;
		_new->next = NULL;
		score += n*10;
		gotoxy(77, 15);
		printf("%d", score);
	}
}

// ������������ ֻ��Ҫ����β��� Ȼ�������������Ϊͷ��㼴��
void ChangeBody(int x, int y) {
	snake* p = head;
	while (p->next->next != NULL) {
		p = p->next;
	}
	free(p->next);
	p->next = NULL;
	snake* new_head = (snake*)malloc(sizeof(snake));
	new_head->x = x;
	new_head->y = y;
	new_head->next = head;
	head = new_head;
}

// �ж��Ƿ���Ϸ����
int Judge() {
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26) {
		Finish();
		return 0;
	}
	snake* p = head->next;
	while (1) {
		if (p == NULL) break;
		if (head->x == p->x && head->y == p->y) {
			Finish();
			return 0;
		}
		p = p->next;
	}
	return 1;
}

void Finish() {
	system("cls");
	gotoxy(15, 10);
	printf("/**********************************************/");
	gotoxy(15, 20);
	printf("/**********************************************/");
	gotoxy(18, 14);
	printf("GAME   OVER      o(*������*)o");
	gotoxy(20, 16);
	printf("Your Score is %d", score);
	gotoxy(18, 18);
	printf("������Ŷ��     ����Ŭ��O(��_��)O");
	gotoxy(0, 27);
	// �ͷſռ�
	snake *p = head, *q;
	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
	if(getch()) {
		system("cls");
	}
}
