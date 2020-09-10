#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define H 20
#define L 80  //H high高度 L long长度
#define UP 0
#define DOWN 1
#define LEft 2
#define RIGHT 3
#define mmlong 3  //这是蛇长
#define HEIGHT   12
#define Wi    13 


//蛇1 
int map[H][L] ={0};            //地图，H行，L列
int snake[1000][2] = {0};      //蛇,0列代表x坐标，1列代表y坐标 
int snake_long = mmlong;            //蛇1初始长度
int direction = UP;            //蛇头方向，初始向上 
int tail[2]={0};               //寄存蛇尾
int speed = 300,game_in = 3;   //控制蛇速度
int score = 0; 
int hittime=0;                //蛇1分数 

//蛇2
int snake_2[1000][2] = {0};      //蛇,0列代表x坐标，1列代表y坐标 
int snake_long_2 = mmlong;            //蛇2初始长度
int direction2 = UP;            //蛇头方向，初始向上 
int tail_2[2]={0};               //寄存蛇尾
int speed_2 = 300;               //控制蛇速度
int score_2 = 0;                 //蛇2分数
int hittime2=0;


int x, y;				
int boxs;				

void drawMap();		
void game();			
void initData();	
int map2[HEIGHT][Wi] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,4,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,0,0,0,0},
    {0,0,1,1,1,1,3,1,1,1,1,0,0},
    {0,0,1,4,0,3,0,3,0,4,1,0,0},
    {0,0,1,1,1,1,0,1,1,1,1,0,0},
    {0,0,0,0,0,1,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0}
};


//通用
int target = 0,time_game = 0,time_game0 = 0;    //time_game 游戏对于模式 

void gotoxy(int i,int j)       //移动光标
{
    COORD position={i,j};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}

void color(int x0)	                       //改变输出颜色 
{
	if( x0>= 0 && x0<= 15)                   //参数在0-15的范围颜色
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x0);	//只有一个参数x，改变字体颜色
	}
	else//默认的颜色白色
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}	
}

void product_map() //地图数据初始化 
{
	int i,j,c=0;
	snake_long = snake_long_2 = mmlong; //蛇初始长度
	speed = speed_2 = 300;    //蛇速度初始300
	score = score_2 = 0;      //初始分数初始化0 
	emd:
	c++;
	srand(time(NULL)+c*100);
	direction = rand()%4;  //给蛇1一个随机方向,但不能向下 
	if(direction == 1)
	goto emd; 
	hmd:
	c++;
	srand(time(NULL)+c*100);
	direction2 = rand()%4;  //给蛇2一个随机方向,但不能向下 
	if(direction2 == 1)
	goto hmd;
	for(i = 0;i<H;i++)
	{
		for(j = 0;j<L;j++)
		{
			map[i][j] = 0;  //每次开始新游戏，需要重新给二维数组赋值0 
		}
	 } 
	for(i = 0;i<H;i++)
	{
		map[i][0] = map[i][L-1] = 1;
		
	}
	for(i = 0;i<L;i++)
	{
		map[0][i] = map[H-1][i] = 1;
	}
	snake[0][0] = L/4;
	snake[0][1] = H/4;  //蛇头初始坐标在中心
	snake_2[0][0] = L*3/4;
	snake_2[0][1] = H*3/4;  //蛇头初始坐标在中心
	for(i = 1;i<mmlong;i++)
	{
		snake[i][0] = snake[0][0];
		snake[i][1] = snake[0][1] + i;  //蛇1身坐标，竖直向下3个
		snake_2[i][0] = snake_2[0][0];
		snake_2[i][1] = snake_2[0][1] + i;  //蛇2身坐标，竖直向下3个 
	 }
	 tail[0] = snake[3][0];
	 tail[1] = snake[3][1];
	 tail_2[0] = snake_2[3][0];
	 tail_2[1] = snake_2[3][1]; 
 }
 
 void money_product() //产生金钱
 {
 	int i,j,k,x0,y0;  //x,y是金币的数组下标寄存器 
	 for(i = 0,k = 1;;)
	 {
		cmd:
		k++;
		srand(time(NULL)+k*20+(j-2)*30);
		x0 = rand()%(L-2) + 1;
		y0 = rand()%(H-2) + 1;
		for(j = 0;j<snake_long;j++) //防止产生在蛇1身上 
		{
			if(x0 == snake[j][0] && y0 == snake[j][1])
			goto cmd;  //重新产生 
		}
		for(j = 0;j<snake_long_2;j++) //防止产生在蛇2身上 
		{
			if(x0 == snake_2[j][0] && y0 == snake_2[j][1])
			goto cmd;  //重新产生 
		}
		if((map[y0][x0] != 2)&&(i<=7))  //已经是金钱不再累计 
		{
			map[y0][x0] = 2;
			i++;
		}
		else if((map[y0][x0]!=3)&&(i>7)&&(i<=12))
		{
			map[y0][x0]=3;
			i++;
		}
		if(i == 13)
		break; 
	 } 
 } 
 
 void draw_map() //画地图 
 {
 	int i,j;
 	gotoxy(0,0);
 	for(i = 0;i<H;i++)
 	{
 		for(j = 0;j<L;j++)
		 {
			 if(map[i][j] == 1)
		 	{
		 		color(7);
		 		printf("#");
			 }
		 	else if(map[i][j] == 0)
		 	{
		 		printf(" ");
			 }
		 	else if(map[i][j] == 2)
		 	{
		 		color(6);
		 		printf("*");
			 }
		 	else if(map[i][j] == 3)
		 	{
		 		color(7);
		 		printf("#");
			}
		  }
		 printf("\n"); 
	 }
  }
   
void draw_snake() //画蛇1 
{
	int  i;
	color(12);
	gotoxy(snake[0][0],snake[0][1]);
	printf("@");
	color(14);
	for(i = 1;i<snake_long;i++)
	{
		gotoxy(snake[i][0],snake[i][1]);
		printf("@");
	}
}

void draw_snake2() //画蛇2 
{
	int i;
	color(1);
	gotoxy(snake_2[0][0],snake_2[0][1]);
	printf("@");
	color(9);
	for(i = 1;i<snake_long_2;i++)
	{
		gotoxy(snake_2[i][0],snake_2[i][1]);
		printf("@");
	}
} 

void move_snake()  //蛇1身移动
{
	int i;
	tail[0] = snake[snake_long-1][0];
	tail[1] = snake[snake_long-1][1]; //寄存蛇尾 
	gotoxy(snake[snake_long-1][0],snake[snake_long-1][1]);
	printf(" ");     //把蛇尾画空格
	for(i = snake_long-1;i>0;i--)  //后移赋值 把后一个等于前一个的坐标,实现移动 
	{
		snake[i][0] = snake[i-1][0];
		snake[i][1] = snake[i-1][1];
	}	
}

void move_snake2()  //蛇2身移动
{
	int i;
	tail_2[0] = snake_2[snake_long-1][0];
	tail_2[1] = snake_2[snake_long-1][1];  //寄存蛇尾 
	gotoxy(snake_2[snake_long_2-1][0],snake_2[snake_long_2-1][1]);
	printf(" ");       //把蛇尾画空格
	for(i = snake_long_2-1;i>0;i--)  //后移赋值 把后一个等于前一个的坐标,实现移动 
	{
		snake_2[i][0] = snake_2[i-1][0];
		snake_2[i][1] = snake_2[i-1][1];
	}	
}

void move_snake_head() //蛇1头移动
{
	switch(direction)
	{
		case 0:snake[0][1]--;break;//向上 
		case 1:snake[0][1]++;break;//向下 
		case 2:snake[0][0]--;break;//向左 
		case 3:snake[0][0]++;break;//向右 
	}
 }
 
 void move_snake_head2() //蛇2头移动
{
	switch(direction2)
	{
		case 0:snake_2[0][1]--;break;//向上 
		case 1:snake_2[0][1]++;break;//向下 
		case 2:snake_2[0][0]--;break;//向左 
		case 3:snake_2[0][0]++;break;//向右 
	}
 } 

void direction_snake() //蛇方向（蛇头）
{
	switch(getch())
	{
		case 0xE0:switch(getch())
				 {
				 	   case 72:if(direction2 != 1) //当前不是向下走就可以向上走 
									direction2 = 0;break;
					   case 80:if(direction2 != 0) //当前不是向下走就可以向上走 
									direction2 = 1;break;
					   case 75:if(direction2 != 3) //当前不是向下走就可以向上走 
									direction2 = 2;break;
					   case 77:if(direction2 != 2) //当前不是向下走就可以向上走 
									direction2 = 3;break;
				 }break; 
		case 'w':
		case 'W':if(direction != 1) //当前不是向下走就可以向上走 
					direction = 0;break; 
		
		case 's':
		case 'S':if(direction != 0) //当前不是向上走就可以向下走 
					direction = 1;break;
		case 'a':
		case 'A':if(direction != 3) //当前不是向右走就可以向左走 
					direction = 2;break;
		case 'd':
		case 'D':if(direction != 2) //当前不是向左走就可以向右走 
					direction = 3;break;
		default :break;
	}
}

void check_snake()  //检查蛇1状态 
{
	void message_snake();   //打印蛇1信息
	int i,j;
	color(8); 
	if(map[snake[0][1]][snake[0][0]] == 2) //蛇头的横坐标是行标，纵坐标是列标,吃到食物，蛇边长1格,吃到金钱后 
	{                                      //立马重新产生金钱 
		snake_long++;
		score += 100;
		snake[snake_long-1][0] = tail[0];
		snake[snake_long-1][1] = tail[1];
		speed -= 35;
		if(speed<100)
		speed = 100;
		for(i = 0;i<H;i++)
		{
			for(j = 0;j<L;j++)
			{
				if((map[i][j] == 2)||(map[i][j] == 3))
				map[i][j] = 0;    //原来的金钱全部消失 
			}
		}
		money_product();          //重新产生金钱
		draw_snake();
		draw_map();    //画地图
		draw_snake();
	}
	message_snake();   //打印蛇1信息
	
	if((map[snake[0][1]][snake[0][0]] == 1)||(map[snake[0][1]][snake[0][0]] == 3)) //撞到边界或者障碍物
	{
	     hittime++;
		 switch(direction)//反方向 
		 {
	       case 0:direction=2;break;
		   case 1:direction=3;break;
		   case 2:direction=0;break;
		   case 3:direction=1;break;	
		 } 
		 snake_long=snake_long-hittime;
		 int a,b;
		 a=tail[0];
		 tail[0]=snake[0][0];
		 snake[0][0]=a;
		 b=tail[1];
		 tail[1]=snake[0][1];
		 snake[0][1]=b;
		 for(int k=1;k<=(snake_long-1)/2;k++)
		 {
		 	a=snake[snake_long+1-k][0];
		 	snake[snake_long+1-k][0]=snake[k][0];
		 	snake[k][0]=a;
		 	b=snake[snake_long+1-k][1];
		 	snake[snake_long+1-k][1]=snake[k][1];
		 	snake[k][1]=b;
		 }
		 for(i = 0;i<H;i++)
		{
			for(j = 0;j<L;j++)
			{
				if((map[i][j] == 2)||(map[i][j] == 3))
				map[i][j] = 0;    //原来的金钱全部消失 
			}
		}
		 money_product(); 
		 draw_snake();
		 draw_map();    //画地图
		 draw_snake();
		 score=score-hittime*100;
	}
	message_snake();
	
	if((score >= target)||(snake_long<2))
	{
			Sleep(1500);
			system("cls");
			gotoxy(L/2,H/2);
			if(score>=target)
			  printf("蛇1率先达到目标分数，获得胜利\n");
			if(snake_long<2)
			  printf("蛇1身长小于0，蛇2获得胜利\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("再来一次？(Y/y)   退出(N/n)  按0返回功能菜单");
			shuru2:
			switch(getch())
			{
				case '0':game_in = 2;goto eee;break;
				case 'y':
				case 'Y':game_in = 1;goto eee;break;
				case 'n':
				case 'N':game_in = 0;goto eee;break;
				default:goto shuru2; 
			}
	 }
	eee:;	
} 

void check_snake2()  //检查蛇2状态 
{
	int i,j;
	void message_snake2();   //打印蛇2信息
	color(8);
	if(map[snake_2[0][1]][snake_2[0][0]] == 2) //蛇头的横坐标是行标，纵坐标是列标,吃到食物，蛇边长1格,吃到金钱后 
	{                                      //立马重新产生金钱 
		snake_long_2++;
		score_2 += 100;
		snake_2[snake_long_2-1][0] = tail_2[0];
		snake_2[snake_long_2-1][1] = tail_2[1];
		speed_2 -= 35;
		if(speed_2<100)
		speed_2 = 100;
		for(i = 0;i<H;i++)
		{
			for(j = 0;j<L;j++)
			{
				if((map[i][j] == 2)||(map[i][j] == 3))
				map[i][j] = 0;    //原来的金钱全部消失 
			}
		}
		money_product();          //重新产生金钱
		draw_snake2();
		draw_map();    //画地图
		draw_snake2(); 
	}
	message_snake2();   //打印蛇2信息
	
	if((map[snake_2[0][1]][snake_2[0][0]] == 1)||(map[snake_2[0][1]][snake_2[0][0]] == 3)) //撞到边界或者障碍物
	{
	     hittime2++;
		 switch(direction2)//反方向 
		 {
	       case 0:direction2=2;break;
		   case 1:direction2=3;break;
		   case 2:direction2=0;break;
		   case 3:direction2=1;break;	
		 } 
		 snake_long_2=snake_long_2-hittime2;
		 int a,b;
		 a=tail_2[0];
		 tail_2[0]=snake_2[0][0];
		 snake_2[0][0]=a;
		 b=tail_2[1];
		 tail_2[1]=snake_2[0][1];
		 snake_2[0][1]=b;
		 for(int k=1;k<=(snake_long_2-1)/2;k++)
		 {
		 	a=snake_2[snake_long_2+1-k][0];
		 	snake_2[snake_long_2+1-k][0]=snake_2[k][0];
		 	snake_2[k][0]=a;
		 	b=snake_2[snake_long_2+1-k][1];
		 	snake_2[snake_long_2+1-k][1]=snake_2[k][1];
		 	snake_2[k][1]=b;
		 }
		 for(i = 0;i<H;i++)
		{
			for(j = 0;j<L;j++)
			{
				if((map[i][j] == 2)||(map[i][j] == 3))
				map[i][j] = 0;    //原来的金钱全部消失 
			}
		}
		 money_product(); 
		 draw_snake2();
		 draw_map();    //画地图
		 draw_snake2();
		 score_2=score_2-hittime2*100;
	}	
	message_snake2();
	
	if((score_2 >= target)||(snake_long_2<2))
	{
			Sleep(1500);
			system("cls");
			gotoxy(L/2,H/2);
			if(score_2>=target)
			  printf("蛇2率先达到目标分数，获得胜利\n");
			if(snake_long_2<2)
			  printf("蛇2身长小于0，蛇1获得胜利\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("再来一次？(Y/y)   退出(N/n)   按0返回功能菜单");
			shuru:
			switch(getch())
			{
				case '0':game_in = 2;goto eee1;break;
				case 'y':
				case 'Y':game_in = 1;goto eee1;break;
				case 'n':
				case 'N':game_in = 0;goto eee1;break;
				default:goto shuru; 
			}
	 }
	 eee1:;
}

void check_snake_0()  //（单人模式）检查蛇状态 
{
	void message_snake();   //打印蛇信息
	int i,j;
	color(8); 
	if(map[snake[0][1]][snake[0][0]] == 2) //蛇头的横坐标是行标，纵坐标是列标,吃到食物，蛇边长1格,吃到金钱后 
	{                                      //立马重新产生金钱 
		snake_long++;
		score += 100;
		snake[snake_long-1][0] = tail[0];
		snake[snake_long-1][1] = tail[1];
		speed -= 35;
		if(speed<100)
		speed = 100;
		for(i = 0;i<H;i++)
		{
			for(j = 0;j<L;j++)
			{
				if((map[i][j] == 2)||(map[i][j] == 3))
				map[i][j] = 0;    //原来的金钱全部消失 
			}
		}
		money_product();          //重新产生金钱
		draw_snake();
		draw_map();    //画地图
		draw_snake();
	}
	message_snake();   //打印蛇1信息
	
	if(score >= target)
	{
			Sleep(1500);
			system("cls");
			gotoxy(L/2,H/2);
			printf("达到目标分数，获得胜利\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("再来一次？(Y/y)   退出(N/n)  按0返回功能菜单");
			shuru0:
			switch(getch())
			{
				case '0':game_in = 2;goto eee;break;
				case 'y':
				case 'Y':game_in = 1;goto eee;break;
				case 'n':
				case 'N':game_in = 0;goto eee;break;
				default:goto shuru0; 
			}
	 }
	
	if((map[snake[0][1]][snake[0][0]] == 1)||(map[snake[0][1]][snake[0][0]] == 3)) //撞到边界或者障碍物，输了 
	{
			Sleep(1500);
			system("cls");
			gotoxy(L/2,H/2);
			printf("撞到障碍物，失败\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("再来一次？(Y/y)   退出(N/n)   按0返回功能菜单");
			shuru00:
			switch(getch())
			{
				case '0':game_in = 2;break;
				case 'y':
				case 'Y':game_in = 1;break;
				case 'n':
				case 'N':game_in = 0;break;
				default:goto shuru00; 
			}
	}
	eee:;	
} 

int menu0()  //主菜单
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);   
    //隐藏光标
	int i,m,c = 0;
	if(time_game0 == 1)
	goto moshi10;
	else if(time_game0 == 2)
	goto moshi20;
	else if(time_game0 == 3)
	goto kaishi0;
	 
	color(12); 
	gotoxy(L/2-2,2);
	printf("益智游戏");
	gotoxy(15,5);
	color(8);
	printf("1.小小贪吃蛇");
	gotoxy(L/4+15,5);
	printf("2.推箱子");
	gotoxy(L/2+15,5);
	printf("3.结束游戏");
	gotoxy(1,13);
	printf("  Loading......\n");
	
	do
	{
		
		for(i = 10,m = 1;i<60;i++,m+=2)
		{
			color(8);
			gotoxy(75,13);
			printf("    ");
			gotoxy(75,13);
			printf("%-2d%%",m);
			gotoxy(75,13);
			printf("    ");
			gotoxy(75,13);
			printf("%-2d%%",m+1);
			gotoxy(i+5,14);
			color(3);
			printf("》");	
			Sleep(i+m);
			c++;
			if(c == 50)
			goto end0;
			
		}
		gotoxy(1,14);
		for(i = 0;i<79;i++)
		{
			printf(" ");	
		}
		
	}while(1);
	end0:
		kaishi0:;
		color(12); 
		gotoxy(L/2-2,2);
		printf("益智游戏");
		gotoxy(15,5);
		color(8);
		printf("1.小小贪吃蛇");
		gotoxy(L/4+15,5);
		printf("2.推箱子");
		gotoxy(L/2+15,5);
		printf("3.结束游戏");
		color(3);		
		gotoxy(1,14);
		for(i = 0;i<79;i++)
		{
			printf(" ");	
		}
		gotoxy(1,13);
		printf("                 ");
		gotoxy(L/2-6,8);
		printf("请按相应序号进行选择");
		switch(getch())
		{
			case '1':moshi10:;
			         system("cls");
					 return 1; 
			case '2':moshi20:;
					 system("cls");
					 return 2; 
			case '3':system("cls");
			         return 3;
			default :break; 
			
		 } 
   }
   
int menu()  //子菜单
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);   
    //隐藏光标
	int i,m,c = 0;
	if(time_game == 1)
	goto moshi1;
	else if(time_game == 2)
	goto moshi2;
	else if(time_game == 3)
	goto kaishi;
	 
	color(12); 
	gotoxy(L/2-2,2);
	printf("小小贪吃蛇");
	gotoxy(15,5);
	color(8);
	printf("1.单人游戏");
	gotoxy(L/4+15,5);
	printf("2.双人游戏");
	gotoxy(L/2+15,5);
	printf("3.结束游戏");
	gotoxy(1,13);
	printf("  Loading......\n");
	
	do
	{
		
		for(i = 10,m = 1;i<60;i++,m+=2)
		{
			color(8);
			gotoxy(75,13);
			printf("    ");
			gotoxy(75,13);
			printf("%-2d%%",m);
			gotoxy(75,13);
			printf("    ");
			gotoxy(75,13);
			printf("%-2d%%",m+1);
			gotoxy(i+5,14);
			color(3);
			printf("》");	
			Sleep(i+m);
			c++;
			if(c == 50)
			goto end;
			
		}
		gotoxy(1,14);
		for(i = 0;i<79;i++)
		{
			printf(" ");	
		}
		
	}while(1);
	end:
		kaishi:;
		color(12); 
		gotoxy(L/2-2,2);
		printf("小小贪吃蛇");
		gotoxy(15,5);
		color(8);
		printf("1.单人游戏");
		gotoxy(L/4+15,5);
		printf("2.双人游戏");
		gotoxy(L/2+15,5);
		printf("3.结束游戏");
		color(3);		
		gotoxy(1,14);
		for(i = 0;i<79;i++)
		{
			printf(" ");	
		}
		gotoxy(1,13);
		printf("                 ");
		gotoxy(L/2-6,8);
		printf("请按相应序号进行选择");
		switch(getch())
		{
			case '1':moshi1:;
					 system("cls");
					 gotoxy(L/2-4,H/2-3);printf("游戏说明");
					 gotoxy(L/2-8,H/2-2);printf("单人模式，设定一个目标分，达到即可胜利");
					 gotoxy(L/2-8,H/2-1);printf("每吃到一个金币，分数增加100分");
					 gotoxy(L/2-8,H/2);printf("撞到边界或障碍物，游戏失败");
					 gotoxy(L/2-8,H/2+1);printf("请输入目标分数：");color(8);fflush(stdin);scanf("%d",&target);
					 return 1; 
			case '2':moshi2:;
					 system("cls");
					 gotoxy(L/2-6,H/2-3);printf("游戏说明");
					 gotoxy(L/2-30,H/2-2);printf("双人对战，率先达到目标分数的一方获得胜利，蛇身长小于0对方获胜");
					 gotoxy(L/2-30,H/2-1);printf("每吃到一个金币，分数增加100分；撞到边界或障碍物分数减少100*撞击次数");
					 gotoxy(L/2-30,H/2);printf("撞到边界或障碍物，蛇反方向移动");
					 gotoxy(L/2-12,H/2+1);printf("请输入目标分数：");color(8);fflush(stdin);scanf("%d",&target);
					 return 2; 
			case '3':return 3;
			default :break; 
			
		 } 
   }
   
void message_snake()  //打印蛇1信息
{
	gotoxy(L/2-35,H+1);
	color(11); 
	printf("玩家1--蛇1");
	gotoxy(L/2-35,H+2);
	printf("得分：%d",score);
	gotoxy(L/2-35,H+3);
	printf("上  下  左  右");
	gotoxy(L/2-35,H+4);
	printf("W/w S/s A/a D/d");
	gotoxy(L/2-13,H+1);
	printf("目标分数：%d",target);	
}

void message_snake2()  //打印蛇2信息
{
	gotoxy(L/2+10,H+1);
	color(11); 
	printf("玩家2--蛇2");
	gotoxy(L/2+10,H+2);
	printf("得分：%d",score_2);
	gotoxy(L/2+10,H+3);
	printf("上  下  左  右");
	gotoxy(L/2+10,H+4);
	printf(" ↑  ↓ ←   →");	
}   

void drawMap(){
	int i, j;
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<Wi; j++){
			switch(map2[i][j]){
				case 0:  printf("  ");break;  
				case 1:  printf("〇");break;   
				case 2:  printf("了");break;  
				case 3:  printf("■");break;   
				case 4:  printf("☆");break;  
				case 5:  printf("★");break;  
				case 6:  printf("了");break; 
			}
		}
		printf("\n");
	}
}


void initData(){
	int i, j;
	boxs = 0;
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<Wi; j++){
			if(map2[i][j]==2){		 
				y = i;
				x = j;	
			}
			if(map2[i][j]==3){
				boxs++;
			}
		}
	}
}

void game(){
	char direction;
	direction = getch();
	
		switch(direction){
			
			case 'w':
			case 'W':
				int wx,wy;
				wx = x;
				wy = y-1;
				
				  
				if(y==0){
					break;
				}
				
					if(map2[wy][wx]==1){
						break;
					}
					 
					if(map2[wy][wx]==3||map2[wy][wx]==5){
						 
						if(map2[wy-1][wx]==1||map2[wy-1][wx]==3||map2[wy-1][wx]==5){
							break;
						}	
						
						if(map2[wy-1][wx]==4){
							map2[wy-1][wx] = 5;
						}else{ 	
							map2[wy-1][wx] = 3; 
						}
					} 
					
					if(map2[y][x]!=6){ 
						map2[y][x] = 0;
					}
					
					if(map2[y][x]==6){
						map2[y][x] = 4;
					}
				
					if(map2[wy][wx]==4||map2[wy][wx]==5){
						map2[wy][wx] = 6; 
					}
					else{
						map2[wy][wx]	= 2;
					} 
					y = wy;
			break;
			
			
			case 's':
			case 'S':
				int sx,sy;
				sx = x;
				sy = y+1;

				if(y==HEIGHT-1){
					break;
				}
					if(map2[sy][sx]==1){
						break;
					}
					if(map2[sy][sx]==3||map2[sy][sx]==5)
					{
						if(map2[sy+1][sx]==1||map2[sy+1][sx]==3||map2[sy+1][sx]==5){
							break;
						}	
						if(map2[sy+1][sx]==4)
						{
							map2[sy+1][sx] = 5;
						}
						else{ 	
							map2[sy+1][sx] = 3; 
						}
					} 
					if(map2[y][x]!=6)
					{ 
						map2[y][x] = 0;	
					}
					
					if(map2[y][x]==6)
					{
						map2[y][x] = 4;
					}	
					if(map2[sy][sx]==4||map2[sy][sx]==5)
					{
						map2[sy][sx] = 6; 
					}
					else{
						map2[sy][sx]	= 2;
					}
					y = sy;
			break;
			
			
			case 'a':
			case 'A':
				int ax,ay;
				ax = x-1;
				ay = y;
				
			 
				if(x==0){
					break;
				}

					if(map2[ay][ax]==1){
						break;
					}
	
					if(map2[ay][ax]==3||map2[ay][ax]==5)
					{
						if(map2[ay][ax-1]==1||map2[ay][ax-1]==3||map2[ay][ax-1]==5){
							break;
						}	

						if(map2[ay][ax-1]==4)
						{
							map2[ay][ax-1] = 5;
						}
						else{ 
							map2[ay][ax-1] = 3; 
						}
					} 
					if(map2[y][x]!=6)
					{ 
						map2[y][x] = 0;	
					}
					
					if(map2[y][x]==6)
					{
						map2[y][x] = 4;
					}	
					if(map2[ay][ax]==4||map2[ay][ax]==5)
					{
						map2[ay][ax] = 6; 
					}
					else{
						map2[ay][ax]	= 2;
					}
					x = ax;
			
			break;
			
				
			
			case 'd':
			case 'D':
				int dx,dy;
				dx = x+1;
				dy = y;
				

				if(x==Wi-1){
					break;
				}

					if(map2[dy][dx]==1){
						break;
					}

					if(map2[dy][dx]==3||map2[dy][dx]==5)
					{

						if(map2[dy][dx+1]==1||map2[dy][dx+1]==3||map2[dy][dx+1]==5){
							break;
						}	

						if(map2[dy][dx+1]==4)
						{
							map2[dy][dx+1] = 5;
						}
						else{ 
							map2[dy][dx+1] = 3; 
						}
					} 
					
					if(map2[y][x]!=6)
					{ 
						map2[y][x] = 0;	
					}
					if(map2[y][x]==6)
					{
						map2[y][x] = 4;
					}	
					if(map2[dy][dx]==4||map2[dy][dx]==5)
					{
						map2[dy][dx] = 6; 
					}
					else{
						map2[dy][dx]= 2;
					}
					x = dx;
			break;
		}
}

int main()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //隐藏光标
    int i,j;
    mainmenu:
    system("cls");
    j = menu0();
    if(j == 1)
        goto menu1;
    else if(j == 2)
        goto tuixiangzi;
    else if(j == 3)
        goto over_game;
	menu1:
	system("cls");
	i = menu();     //贪吃蛇功能菜单
	if(i == 2)
		goto play2;
	else if(i == 1)
		goto play1;
	else if(i == 3)
		goto over_game; 
	play2: 
    game_in = 3;
	product_map(); //地图产生
	money_product();//产生金钱 
	draw_map();    //画地图
	draw_snake();  //画蛇
	draw_snake2();
	message_snake();  //打印蛇1信息
	message_snake2();  //打印蛇2信息
	color(8);
	gotoxy(L/2-10,H/2);
	system("pause");
	gotoxy(L/2-10,H/2);
	printf("                                       "); 
	do //双人贪吃蛇 
	{
		CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //隐藏光标
		move_snake();  //蛇1身移动
		move_snake_head(); //蛇1头移动
		check_snake();     //检查蛇1状态
		move_snake2();  //蛇2身移动
		move_snake_head2(); //蛇2头移动
		check_snake2();     //检查蛇2状态
		draw_snake();
		draw_snake2();
		if(game_in == 0)    // game_in 0 结束游戏，1这个模式重开，2返回功能菜单 
		goto over_game;
		else if(game_in == 1)
		{
			time_game = 2;
			goto menu1;
		}
		else if(game_in == 2)
		{
			time_game = 3;
			goto menu1;
		}
		draw_snake();
		draw_snake2();
		Sleep(speed<speed_2?speed:speed_2);  //速度最快 
		if(kbhit() != 0) //用kbhit函数来判断是否有按键 
		{
			direction_snake(); //移动蛇 
		}
		
	 }while(1);
	
	//单人贪吃蛇 
	play1:
    game_in = 3;
	product_map(); //地图产生
	money_product();//产生金钱 
	draw_map();    //画地图
	draw_snake();  //画蛇1
	message_snake();  //打印蛇1信息
	color(8); 
	gotoxy(L/2-10,H/2);
	system("pause");
	gotoxy(L/2-10,H/2);
	printf("                                       "); 
	do //单人贪吃蛇 
	{
		CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //隐藏关标
		move_snake();      //蛇1身移动
		move_snake_head(); //蛇1头移动
		check_snake_0();     //检查蛇1状态
		if(game_in == 0)
		goto over_game;
		else if(game_in == 1)
		{
			time_game = 1;
			goto menu1;
		}
		else if(game_in == 2)
		{
			time_game = 3;
			goto menu1;
		}
		draw_snake();
		Sleep(speed-50);  //速度加快 
		if(kbhit() != 0) //用kbhit函数来判断是否有按键 
		{
			direction_snake(); //移动蛇 
		}
		
	 }while(1);  
	 tuixiangzi:
	 initData();
	 while(1){
		system("cls");	
		printf("箱子数:%d\n",boxs);
		drawMap();
		if(boxs==0){
			break;		
		}
		
		game();
		initData();	
	}
	Sleep(1500);
	
	 over_game:;
}

