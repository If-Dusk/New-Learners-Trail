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

void welcome();                // 开始界面
void Finish();                 // 结束界面
void Choosing();               // 选择界面 
void loading();                // 加载界面
void creatgraph();             // 围墙打印
void gotoxy(int x, int y);     // 光标跳转，x为横坐标,y为纵坐标 
void gotoprint(int x, int y);  // 跳转打印
void gotodelete(int x, int y); // 跳转删除
void creatfood();              // 食物产生
int ClickControl();            // 获取键盘信号
int Judge();                   // 游戏结束判断
void ExplanaTion();			   // 游戏说明 
void RankList();			   // 排行榜 
void Rankfile();			   // 分数保存 
void MovingBody(int n);        // 蛇的移动
void Eating(int n);            // 蛇吃到东西后伸长
void ChangeBody(int x, int y); // 蛇的坐标变换
int theSpeed(int score);	   // 蛇的速度控制 
int GameCore(int m);		   // 游戏主体部分 
void NewChaning();			   // 数据清除
 
/*全局变量 + 预处理：*/
typedef struct Snakes {
	int x;
	int y;
	struct Snakes* next;
} snake;

snake* head;    // 声明蛇头指针

// 申明并定义食物
struct Food {
	int x;
	int y;
} food;

typedef struct {
	char name[20];  // 保存用户名
	int score0;		// 保存分数 
}Info; 

Info User; 		// 用户数据 
FILE *fp;		// 文件开关 
int score = 0;  // 分数
char click = 1; // 记录敲下的键盘按键
int speed;      // 速度 其实是延迟的毫秒数
char m; 		// 选择

int main() {
	
	system("color 7d"); // 设置控制台字体颜色
	welcome();          // 欢迎界面
	Choosing();			// 选择界面 
	Rankfile();		    // 排行榜数据保存 
	NewChaning();		// 数据初始化 
	return main();		// 重新开始 
}

void NewChaning() {
	
	score = 0;
	click = 1;
	m = 0;
}

int GameCore(int n) {
	creatgraph();       // 创建地图
	creatfood();        // 新建食物
	// 捕获鼠标按键 ClickControl
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
	printf("请选择游戏难度\n");	
	
	gotoxy(45,12);
	printf("1、正常难度\n");
	gotoxy(45,13);
	printf("2、进阶难度\n");
	gotoxy(45,14);
	printf("3、排行榜\n");
	gotoxy(45,15);
	printf("4、游戏说明\n");
	gotoxy(45,16);
	printf("5、退出游戏\n");
	
	m = getch();
	if(m > '0' && m < '6') {
		system("cls");

		switch(m){
			case '1': {
				int n = 1;
				loading();  // 加载界面
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
		printf("错误,请重新选择");
		Choosing();
	}
}

void Rankfile() {
	User.score0 = score; 
	fp = fopen("Ranklist.txt","a");
	if(fp == NULL) {
		printf("排行榜无法打开");  
        exit(1);
	}
	fprintf(fp,"%s \t\t  %d\n",User.name,User.score0);
	fclose(fp); 
} 

void ExplanaTion() {
	system("cls");
	
	gotoxy(20,10);
	printf("随着分数增加,蛇的速度会发生变化");
	gotoxy(20,11);
	printf("不要被打个措手不及哦");
	gotoxy(20,12);
	printf("?”(??ω?)\n");
	gotoxy(20,13);
	printf("w,a,s,d控制上下左右移动");
	gotoxy(20,14);
	printf("鼠标点击暂停,回车键继续游戏");
	gotoxy(20,15);
	printf("反向移动等于吃自己哦");
	gotoxy(20,16);
	printf("记得别开大写锁定哦"); 
	gotoxy(20,18);
	printf("按任意键退出");
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
		printf("暂无记录\n");
	}
	
	n = 10;
	for(i=0;i<n-1;i++)//采用冒泡法进行排序 
    {  
		k = i;
		for(j=i+1;j<n;j++) 
	    if(tmp[j].score0>tmp[k].score0)//排序比较大小  
		k = j;
		temp=tmp[k];
		tmp[k]=tmp[i];
		tmp[i]=temp;//当符合条件时进行数据交换
	} 
	i = 0;
	gotoxy(23,20);
	printf("排行榜\n");
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
	printf("按任意键退出");
	fclose(fp);
	
	if(getch()) {
		system("cls");	
		Choosing();
	}
	
}

void loading() {
	printf("■                              \n");
	printf("■                               \n");
    printf("■                                 * *     \n");
	printf("■                               *     *\n");
	printf("■*                             *         * \n");
    printf("■ *                           *            *  \n");
	printf("■  *                         *               *  \n");
	printf("■   *                       *                  * \n");
	printf("■    *                     *                     * \n");
	printf("■      *                 *                         *\n");
	printf("■        *             *        \n");
	printf("■          *         *          \n");
	printf("■             *   *             \n");
	printf("■                              \n");
	printf("■       ■            ■■■ \n");
	printf("■      ■  ■        ■     ■ \n");
	printf("■    ■     ■      ■■⊙o⊙■ \n");
	printf("■   ■        ■   ■■     ■ \n");
	printf("■  ■           ■ ■      ■   \n");
	printf("■ ■■■ \n");
	printf("■  \n");
	gotoxy(46,23);
	int i;
	printf("游戏加载中");
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
	printf("\n\t\t\t\t\t\t加载完成");
	printf("\n");
	
	if(getch()) {
		system("cls");
	}
}

void gotoxy(int x, int y) {
	// 更新光标位置
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
	// 隐藏光标
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hOutput, &cursor);
}

void gotoprint(int x, int y) {
	gotoxy(x, y);
	printf("■");
}

void gotodelete(int x, int y) {
	gotoxy(x, y);
	printf("  ");
}

void creatgraph() {
	int i;// 因为控制台字符宽高比为1：2,每次i＋2 
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

// 随机产生一个食物
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
		while (1) {        //遍历排除蛇身重复
			if (judge->next == NULL) break;
			if (food.x == judge->x && food.y == judge->y) {
				flag = false;
			}
			judge = judge->next;
		}
	}
	gotoxy(food.x, food.y);
	printf("⊙");
}

// 捕获鼠标 游戏主循环
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

//蛇身移动 
void MovingBody(int n) {
	int x = head->x, y = head->y;
	snake* p = head;
	// 通过先清空后打印实现动画效果
	while (p->next != NULL) {
		p = p->next;
	}
	gotodelete(p->x, p->y); // 消除尾节点
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
	if (x != head->x || y != head->y) {	// 改变坐标时更新 暂停游戏停止更新蛇头 
		ChangeBody(x, y);
	}
	p = head;
	// 打印蛇头
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

// 吃到食物处理 添加一个尾巴
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

// 更新蛇体坐标 只需要消除尾结点 然后把新坐标结点置为头结点即可
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

// 判断是否游戏结束
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
	printf("GAME   OVER      o(*￣▽￣*)o");
	gotoxy(20, 16);
	printf("Your Score is %d", score);
	gotoxy(18, 18);
	printf("还不错哦，     继续努力O(∩_∩)O");
	gotoxy(0, 27);
	// 释放空间
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
