#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define H 20
#define L 80  //H high�߶� L long����
#define UP 0
#define DOWN 1
#define LEft 2
#define RIGHT 3
#define mmlong 3  //�����߳�
#define HEIGHT   12
#define Wi    13 


//��1 
int map[H][L] ={0};            //��ͼ��H�У�L��
int snake[1000][2] = {0};      //��,0�д���x���꣬1�д���y���� 
int snake_long = mmlong;            //��1��ʼ����
int direction = UP;            //��ͷ���򣬳�ʼ���� 
int tail[2]={0};               //�Ĵ���β
int speed = 300,game_in = 3;   //�������ٶ�
int score = 0; 
int hittime=0;                //��1���� 

//��2
int snake_2[1000][2] = {0};      //��,0�д���x���꣬1�д���y���� 
int snake_long_2 = mmlong;            //��2��ʼ����
int direction2 = UP;            //��ͷ���򣬳�ʼ���� 
int tail_2[2]={0};               //�Ĵ���β
int speed_2 = 300;               //�������ٶ�
int score_2 = 0;                 //��2����
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


//ͨ��
int target = 0,time_game = 0,time_game0 = 0;    //time_game ��Ϸ����ģʽ 

void gotoxy(int i,int j)       //�ƶ����
{
    COORD position={i,j};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}

void color(int x0)	                       //�ı������ɫ 
{
	if( x0>= 0 && x0<= 15)                   //������0-15�ķ�Χ��ɫ
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x0);	//ֻ��һ������x���ı�������ɫ
	}
	else//Ĭ�ϵ���ɫ��ɫ
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}	
}

void product_map() //��ͼ���ݳ�ʼ�� 
{
	int i,j,c=0;
	snake_long = snake_long_2 = mmlong; //�߳�ʼ����
	speed = speed_2 = 300;    //���ٶȳ�ʼ300
	score = score_2 = 0;      //��ʼ������ʼ��0 
	emd:
	c++;
	srand(time(NULL)+c*100);
	direction = rand()%4;  //����1һ���������,���������� 
	if(direction == 1)
	goto emd; 
	hmd:
	c++;
	srand(time(NULL)+c*100);
	direction2 = rand()%4;  //����2һ���������,���������� 
	if(direction2 == 1)
	goto hmd;
	for(i = 0;i<H;i++)
	{
		for(j = 0;j<L;j++)
		{
			map[i][j] = 0;  //ÿ�ο�ʼ����Ϸ����Ҫ���¸���ά���鸳ֵ0 
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
	snake[0][1] = H/4;  //��ͷ��ʼ����������
	snake_2[0][0] = L*3/4;
	snake_2[0][1] = H*3/4;  //��ͷ��ʼ����������
	for(i = 1;i<mmlong;i++)
	{
		snake[i][0] = snake[0][0];
		snake[i][1] = snake[0][1] + i;  //��1�����꣬��ֱ����3��
		snake_2[i][0] = snake_2[0][0];
		snake_2[i][1] = snake_2[0][1] + i;  //��2�����꣬��ֱ����3�� 
	 }
	 tail[0] = snake[3][0];
	 tail[1] = snake[3][1];
	 tail_2[0] = snake_2[3][0];
	 tail_2[1] = snake_2[3][1]; 
 }
 
 void money_product() //������Ǯ
 {
 	int i,j,k,x0,y0;  //x,y�ǽ�ҵ������±�Ĵ��� 
	 for(i = 0,k = 1;;)
	 {
		cmd:
		k++;
		srand(time(NULL)+k*20+(j-2)*30);
		x0 = rand()%(L-2) + 1;
		y0 = rand()%(H-2) + 1;
		for(j = 0;j<snake_long;j++) //��ֹ��������1���� 
		{
			if(x0 == snake[j][0] && y0 == snake[j][1])
			goto cmd;  //���²��� 
		}
		for(j = 0;j<snake_long_2;j++) //��ֹ��������2���� 
		{
			if(x0 == snake_2[j][0] && y0 == snake_2[j][1])
			goto cmd;  //���²��� 
		}
		if((map[y0][x0] != 2)&&(i<=7))  //�Ѿ��ǽ�Ǯ�����ۼ� 
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
 
 void draw_map() //����ͼ 
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
   
void draw_snake() //����1 
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

void draw_snake2() //����2 
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

void move_snake()  //��1���ƶ�
{
	int i;
	tail[0] = snake[snake_long-1][0];
	tail[1] = snake[snake_long-1][1]; //�Ĵ���β 
	gotoxy(snake[snake_long-1][0],snake[snake_long-1][1]);
	printf(" ");     //����β���ո�
	for(i = snake_long-1;i>0;i--)  //���Ƹ�ֵ �Ѻ�һ������ǰһ��������,ʵ���ƶ� 
	{
		snake[i][0] = snake[i-1][0];
		snake[i][1] = snake[i-1][1];
	}	
}

void move_snake2()  //��2���ƶ�
{
	int i;
	tail_2[0] = snake_2[snake_long-1][0];
	tail_2[1] = snake_2[snake_long-1][1];  //�Ĵ���β 
	gotoxy(snake_2[snake_long_2-1][0],snake_2[snake_long_2-1][1]);
	printf(" ");       //����β���ո�
	for(i = snake_long_2-1;i>0;i--)  //���Ƹ�ֵ �Ѻ�һ������ǰһ��������,ʵ���ƶ� 
	{
		snake_2[i][0] = snake_2[i-1][0];
		snake_2[i][1] = snake_2[i-1][1];
	}	
}

void move_snake_head() //��1ͷ�ƶ�
{
	switch(direction)
	{
		case 0:snake[0][1]--;break;//���� 
		case 1:snake[0][1]++;break;//���� 
		case 2:snake[0][0]--;break;//���� 
		case 3:snake[0][0]++;break;//���� 
	}
 }
 
 void move_snake_head2() //��2ͷ�ƶ�
{
	switch(direction2)
	{
		case 0:snake_2[0][1]--;break;//���� 
		case 1:snake_2[0][1]++;break;//���� 
		case 2:snake_2[0][0]--;break;//���� 
		case 3:snake_2[0][0]++;break;//���� 
	}
 } 

void direction_snake() //�߷�����ͷ��
{
	switch(getch())
	{
		case 0xE0:switch(getch())
				 {
				 	   case 72:if(direction2 != 1) //��ǰ���������߾Ϳ��������� 
									direction2 = 0;break;
					   case 80:if(direction2 != 0) //��ǰ���������߾Ϳ��������� 
									direction2 = 1;break;
					   case 75:if(direction2 != 3) //��ǰ���������߾Ϳ��������� 
									direction2 = 2;break;
					   case 77:if(direction2 != 2) //��ǰ���������߾Ϳ��������� 
									direction2 = 3;break;
				 }break; 
		case 'w':
		case 'W':if(direction != 1) //��ǰ���������߾Ϳ��������� 
					direction = 0;break; 
		
		case 's':
		case 'S':if(direction != 0) //��ǰ���������߾Ϳ��������� 
					direction = 1;break;
		case 'a':
		case 'A':if(direction != 3) //��ǰ���������߾Ϳ��������� 
					direction = 2;break;
		case 'd':
		case 'D':if(direction != 2) //��ǰ���������߾Ϳ��������� 
					direction = 3;break;
		default :break;
	}
}

void check_snake()  //�����1״̬ 
{
	void message_snake();   //��ӡ��1��Ϣ
	int i,j;
	color(8); 
	if(map[snake[0][1]][snake[0][0]] == 2) //��ͷ�ĺ��������б꣬���������б�,�Ե�ʳ��߱߳�1��,�Ե���Ǯ�� 
	{                                      //�������²�����Ǯ 
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
				map[i][j] = 0;    //ԭ���Ľ�Ǯȫ����ʧ 
			}
		}
		money_product();          //���²�����Ǯ
		draw_snake();
		draw_map();    //����ͼ
		draw_snake();
	}
	message_snake();   //��ӡ��1��Ϣ
	
	if((map[snake[0][1]][snake[0][0]] == 1)||(map[snake[0][1]][snake[0][0]] == 3)) //ײ���߽�����ϰ���
	{
	     hittime++;
		 switch(direction)//������ 
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
				map[i][j] = 0;    //ԭ���Ľ�Ǯȫ����ʧ 
			}
		}
		 money_product(); 
		 draw_snake();
		 draw_map();    //����ͼ
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
			  printf("��1���ȴﵽĿ����������ʤ��\n");
			if(snake_long<2)
			  printf("��1��С��0����2���ʤ��\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("����һ�Σ�(Y/y)   �˳�(N/n)  ��0���ع��ܲ˵�");
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

void check_snake2()  //�����2״̬ 
{
	int i,j;
	void message_snake2();   //��ӡ��2��Ϣ
	color(8);
	if(map[snake_2[0][1]][snake_2[0][0]] == 2) //��ͷ�ĺ��������б꣬���������б�,�Ե�ʳ��߱߳�1��,�Ե���Ǯ�� 
	{                                      //�������²�����Ǯ 
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
				map[i][j] = 0;    //ԭ���Ľ�Ǯȫ����ʧ 
			}
		}
		money_product();          //���²�����Ǯ
		draw_snake2();
		draw_map();    //����ͼ
		draw_snake2(); 
	}
	message_snake2();   //��ӡ��2��Ϣ
	
	if((map[snake_2[0][1]][snake_2[0][0]] == 1)||(map[snake_2[0][1]][snake_2[0][0]] == 3)) //ײ���߽�����ϰ���
	{
	     hittime2++;
		 switch(direction2)//������ 
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
				map[i][j] = 0;    //ԭ���Ľ�Ǯȫ����ʧ 
			}
		}
		 money_product(); 
		 draw_snake2();
		 draw_map();    //����ͼ
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
			  printf("��2���ȴﵽĿ����������ʤ��\n");
			if(snake_long_2<2)
			  printf("��2��С��0����1���ʤ��\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("����һ�Σ�(Y/y)   �˳�(N/n)   ��0���ع��ܲ˵�");
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

void check_snake_0()  //������ģʽ�������״̬ 
{
	void message_snake();   //��ӡ����Ϣ
	int i,j;
	color(8); 
	if(map[snake[0][1]][snake[0][0]] == 2) //��ͷ�ĺ��������б꣬���������б�,�Ե�ʳ��߱߳�1��,�Ե���Ǯ�� 
	{                                      //�������²�����Ǯ 
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
				map[i][j] = 0;    //ԭ���Ľ�Ǯȫ����ʧ 
			}
		}
		money_product();          //���²�����Ǯ
		draw_snake();
		draw_map();    //����ͼ
		draw_snake();
	}
	message_snake();   //��ӡ��1��Ϣ
	
	if(score >= target)
	{
			Sleep(1500);
			system("cls");
			gotoxy(L/2,H/2);
			printf("�ﵽĿ����������ʤ��\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("����һ�Σ�(Y/y)   �˳�(N/n)  ��0���ع��ܲ˵�");
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
	
	if((map[snake[0][1]][snake[0][0]] == 1)||(map[snake[0][1]][snake[0][0]] == 3)) //ײ���߽�����ϰ������ 
	{
			Sleep(1500);
			system("cls");
			gotoxy(L/2,H/2);
			printf("ײ���ϰ��ʧ��\n");
			Sleep(1500);
			gotoxy(L/2-4,H/2+1);
			printf("����һ�Σ�(Y/y)   �˳�(N/n)   ��0���ع��ܲ˵�");
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

int menu0()  //���˵�
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);   
    //���ع��
	int i,m,c = 0;
	if(time_game0 == 1)
	goto moshi10;
	else if(time_game0 == 2)
	goto moshi20;
	else if(time_game0 == 3)
	goto kaishi0;
	 
	color(12); 
	gotoxy(L/2-2,2);
	printf("������Ϸ");
	gotoxy(15,5);
	color(8);
	printf("1.СС̰����");
	gotoxy(L/4+15,5);
	printf("2.������");
	gotoxy(L/2+15,5);
	printf("3.������Ϸ");
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
			printf("��");	
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
		printf("������Ϸ");
		gotoxy(15,5);
		color(8);
		printf("1.СС̰����");
		gotoxy(L/4+15,5);
		printf("2.������");
		gotoxy(L/2+15,5);
		printf("3.������Ϸ");
		color(3);		
		gotoxy(1,14);
		for(i = 0;i<79;i++)
		{
			printf(" ");	
		}
		gotoxy(1,13);
		printf("                 ");
		gotoxy(L/2-6,8);
		printf("�밴��Ӧ��Ž���ѡ��");
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
   
int menu()  //�Ӳ˵�
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);   
    //���ع��
	int i,m,c = 0;
	if(time_game == 1)
	goto moshi1;
	else if(time_game == 2)
	goto moshi2;
	else if(time_game == 3)
	goto kaishi;
	 
	color(12); 
	gotoxy(L/2-2,2);
	printf("СС̰����");
	gotoxy(15,5);
	color(8);
	printf("1.������Ϸ");
	gotoxy(L/4+15,5);
	printf("2.˫����Ϸ");
	gotoxy(L/2+15,5);
	printf("3.������Ϸ");
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
			printf("��");	
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
		printf("СС̰����");
		gotoxy(15,5);
		color(8);
		printf("1.������Ϸ");
		gotoxy(L/4+15,5);
		printf("2.˫����Ϸ");
		gotoxy(L/2+15,5);
		printf("3.������Ϸ");
		color(3);		
		gotoxy(1,14);
		for(i = 0;i<79;i++)
		{
			printf(" ");	
		}
		gotoxy(1,13);
		printf("                 ");
		gotoxy(L/2-6,8);
		printf("�밴��Ӧ��Ž���ѡ��");
		switch(getch())
		{
			case '1':moshi1:;
					 system("cls");
					 gotoxy(L/2-4,H/2-3);printf("��Ϸ˵��");
					 gotoxy(L/2-8,H/2-2);printf("����ģʽ���趨һ��Ŀ��֣��ﵽ����ʤ��");
					 gotoxy(L/2-8,H/2-1);printf("ÿ�Ե�һ����ң���������100��");
					 gotoxy(L/2-8,H/2);printf("ײ���߽���ϰ����Ϸʧ��");
					 gotoxy(L/2-8,H/2+1);printf("������Ŀ�������");color(8);fflush(stdin);scanf("%d",&target);
					 return 1; 
			case '2':moshi2:;
					 system("cls");
					 gotoxy(L/2-6,H/2-3);printf("��Ϸ˵��");
					 gotoxy(L/2-30,H/2-2);printf("˫�˶�ս�����ȴﵽĿ�������һ�����ʤ��������С��0�Է���ʤ");
					 gotoxy(L/2-30,H/2-1);printf("ÿ�Ե�һ����ң���������100�֣�ײ���߽���ϰ����������100*ײ������");
					 gotoxy(L/2-30,H/2);printf("ײ���߽���ϰ���߷������ƶ�");
					 gotoxy(L/2-12,H/2+1);printf("������Ŀ�������");color(8);fflush(stdin);scanf("%d",&target);
					 return 2; 
			case '3':return 3;
			default :break; 
			
		 } 
   }
   
void message_snake()  //��ӡ��1��Ϣ
{
	gotoxy(L/2-35,H+1);
	color(11); 
	printf("���1--��1");
	gotoxy(L/2-35,H+2);
	printf("�÷֣�%d",score);
	gotoxy(L/2-35,H+3);
	printf("��  ��  ��  ��");
	gotoxy(L/2-35,H+4);
	printf("W/w S/s A/a D/d");
	gotoxy(L/2-13,H+1);
	printf("Ŀ�������%d",target);	
}

void message_snake2()  //��ӡ��2��Ϣ
{
	gotoxy(L/2+10,H+1);
	color(11); 
	printf("���2--��2");
	gotoxy(L/2+10,H+2);
	printf("�÷֣�%d",score_2);
	gotoxy(L/2+10,H+3);
	printf("��  ��  ��  ��");
	gotoxy(L/2+10,H+4);
	printf(" ��  �� ��   ��");	
}   

void drawMap(){
	int i, j;
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<Wi; j++){
			switch(map2[i][j]){
				case 0:  printf("  ");break;  
				case 1:  printf("��");break;   
				case 2:  printf("��");break;  
				case 3:  printf("��");break;   
				case 4:  printf("��");break;  
				case 5:  printf("��");break;  
				case 6:  printf("��");break; 
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
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //���ع��
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
	i = menu();     //̰���߹��ܲ˵�
	if(i == 2)
		goto play2;
	else if(i == 1)
		goto play1;
	else if(i == 3)
		goto over_game; 
	play2: 
    game_in = 3;
	product_map(); //��ͼ����
	money_product();//������Ǯ 
	draw_map();    //����ͼ
	draw_snake();  //����
	draw_snake2();
	message_snake();  //��ӡ��1��Ϣ
	message_snake2();  //��ӡ��2��Ϣ
	color(8);
	gotoxy(L/2-10,H/2);
	system("pause");
	gotoxy(L/2-10,H/2);
	printf("                                       "); 
	do //˫��̰���� 
	{
		CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //���ع��
		move_snake();  //��1���ƶ�
		move_snake_head(); //��1ͷ�ƶ�
		check_snake();     //�����1״̬
		move_snake2();  //��2���ƶ�
		move_snake_head2(); //��2ͷ�ƶ�
		check_snake2();     //�����2״̬
		draw_snake();
		draw_snake2();
		if(game_in == 0)    // game_in 0 ������Ϸ��1���ģʽ�ؿ���2���ع��ܲ˵� 
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
		Sleep(speed<speed_2?speed:speed_2);  //�ٶ���� 
		if(kbhit() != 0) //��kbhit�������ж��Ƿ��а��� 
		{
			direction_snake(); //�ƶ��� 
		}
		
	 }while(1);
	
	//����̰���� 
	play1:
    game_in = 3;
	product_map(); //��ͼ����
	money_product();//������Ǯ 
	draw_map();    //����ͼ
	draw_snake();  //����1
	message_snake();  //��ӡ��1��Ϣ
	color(8); 
	gotoxy(L/2-10,H/2);
	system("pause");
	gotoxy(L/2-10,H/2);
	printf("                                       "); 
	do //����̰���� 
	{
		CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //���عر�
		move_snake();      //��1���ƶ�
		move_snake_head(); //��1ͷ�ƶ�
		check_snake_0();     //�����1״̬
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
		Sleep(speed-50);  //�ٶȼӿ� 
		if(kbhit() != 0) //��kbhit�������ж��Ƿ��а��� 
		{
			direction_snake(); //�ƶ��� 
		}
		
	 }while(1);  
	 tuixiangzi:
	 initData();
	 while(1){
		system("cls");	
		printf("������:%d\n",boxs);
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

