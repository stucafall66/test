#include<stdio.h>
#pragma warning(disable:4996)
//#define ROW 11            
//#define COL 11
//#define DEFAULT 1
int minecount=0;
int ROW=10;
int COL=10;
int DEFAULT=10;
void menu();
void init_board(char mine[ROW][COL], char show[ROW][COL]);  //初始化棋盘
void display_board(char show[ROW][COL]);                    //打印棋盘
void set_mine(char mine[ROW][COL]);                         //布雷
int get_mine(char mine[ROW][COL], int x, int y);            //统计该位置周围雷的个数
void mine_sweep(char mine[ROW][COL], char show[ROW][COL]);   //扫雷
void game();                                                 //玩游戏
void check(char mine[ROW][COL], char show[ROW][COL],int x,int y);
char mine[10][10]={{'0','0','0','0','0','0','0','0','0','0'},
                   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'}};
char show[10][10]={{'0','0','0','0','0','0','0','0','0','0'},
                   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'},
				   {'0','0','0','0','0','0','0','0','0','0'}};  
char newmine1[5][5]=       {{'0','1','0','1','0'},
		                    {'0','0','1','0','0'},
							{'0','0','0','1','0'},
							{'1','0','1','0','0'},
							{'0','0','0','0','1'}
							};
char newmine2[7][7]=	   {{'0','0','0','0','1','0','1'},
		                    {'1','0','0','1','0','0','0'},
		                    {'0','1','0','0','0','1','0'},
		                    {'0','0','0','1','0','0','0'},
                            {'1','0','0','1','0','0','0'},
							{'1','0','0','0','0','0','0'},
							{'0','0','1','0','0','1','0'}
							};		
char newmine3[9][9]=       {{'0','0','0','0','1','0','1','0','1'},
		                    {'1','0','0','1','0','0','0','0','0'},
		                    {'0','1','0','0','0','1','0','1','0'},
		                    {'0','0','0','1','0','0','0','0','0'},
                            {'1','0','0','1','0','0','0','1','0'},
							{'1','0','0','0','0','0','1','0','0'},
							{'0','0','1','0','0','0','0','1','0'},
							{'0','0','0','1','0','0','1','0','0'},
							{'0','1','0','0','1','0','0','1','0'}
							};											
int level=0; 
int main()
{
    int input = 1;
    while (input)
    { 
	    menu();
        printf("请选择：\n");
        scanf("%d", &input);
        switch (input)
        {
        case 0:
            printf("退出程序\n");
            break;
        case 1:
        	while(level!=1&&level!=2&&level!=3) 
        	{
			printf("\n1为简单，2为中等，3为困难,请输入难度系数（1/2/3）：");
        	scanf("%d",&level);
        	if(level!=1&&level!=2&&level!=3)
        	    printf("\n请重新输入（1/2/3）"); 
            }
        	if(level==1)
			{
				ROW=COL=7;
				DEFAULT=7;
			} 
			if(level==2)
			{
				ROW=COL=9;
				DEFAULT=12;
			} 
			 	if(level==3)
			{
				ROW=COL=11;
				DEFAULT=21;
			} 
			 level=0;
            game();
            break;
        default:
            printf("错误指令请重新选择：\n");
            break;
        }
    }
    system("pause");
    return 0;
}
void menu()
{
    printf("###########扫雷#########\n");
    printf("####1：start||0:exit####\n");
    printf("########################\n");
}
void init_board(char mine[ROW][COL], char show[ROW][COL])
{
    int i = 0;
    int j = 0;
    for (i = 1; i < ROW - 1; i++)
    {
        for (j = 1; j < COL - 1; j++)
        {
            mine[i][j] = '0';
        }
    }
    for (i = 1; i < ROW - 1; i++)
    {
        for (j = 1; j < COL - 1; j++)
        {
            show [i][j] = '*';
        }
    }
}
void display_board(char show[ROW][COL])
{
    int i, j;
    printf("   ");
    for (i = 1; i < COL - 1; i++)
        printf("%d  ", i);
    printf("\n");
    printf("\n");
    for (i = 1; i < ROW - 1; i++)
    {
        printf("%d  ", i);
        for (j = 1; j < COL - 1; j++)
        {
            printf("%c  ", show[i][j]);
        }
        printf("\n");
    }
}
void set_mine(char mine[ROW][COL])
{
    int x = 0;
    int y = 0;
    int i1=0;
    int i2=0;
    int count = DEFAULT;
    if(count==7)
	{
		for(i1=1;i1<6;i1++){
			for(i2=1;i2<6;i2++){
			mine[i1][i2]=newmine1[i1-1][i2-1];
			}
			
		}
	}
	if(count==12)
	{									
		for(i1=1;i1<8;i1++){
			for(i2=1;i2<8;i2++){
			mine[i1][i2]=newmine2[i1-1][i2-1];
			}
			
		}
	}
	if(count==21)
	{										
		for(i1=1;i1<10;i1++){
			for(i2=1;i2<10;i2++){
			mine[i1][i2]=newmine3[i1-1][i2-1];
			}
			
		}
	} 
   // srand((unsigned)time(NULL));
   // while (count)
  //  { 
    //    x = rand() % (ROW-2) + 1;
    //    y = rand() % (COL-2) + 1;
    //    if (mine[x][y] == '0')
    //    {
    //        mine[x][y] = '1';
    //        count--;
   //     }
   // }
}
int get_mine(char mine[ROW][COL], int x, int y)
{
    int count = 0;
    if (mine[x - 1][y - 1] == '1')
        count++;
    if (mine[x - 1][y] == '1')
        count++;
    if (mine[x-1][y + 1] == '1')
        count++;
    if (mine[x][y - 1] == '1')
        count++;
    if (mine[x ][y + 1] == '1')
        count++;
    if (mine[x + 1][y - 1] == '1')
        count++;
    if (mine[x + 1][y] == '1')
        count++;
    if (mine[x + 1][y + 1] == '1')
        count++;
    return count;
}

void check(char mine[ROW][COL], char show[ROW][COL],int x,int y)
{
	if(x>=1&&x<=9&&y>=1&&y<=9&&show[x][y]=='*')
  {
	int ret = get_mine(mine,x,y);
	show[x][y]=ret+'0';
	minecount++;
	if(show[x][y]=='0')
	{
		check(mine,show,x-1,y-1);
		check(mine,show,x-1,y);
		check(mine,show,x-1,y+1);
		check(mine,show,x,y-1);
		check(mine,show,x,y+1);
		check(mine,show,x+1,y-1);
		check(mine,show,x+1,y);
		check(mine,show,x+1,y+1);
	}
  }	
  return;
}
void mine_sweep(char mine[ROW][COL], char show[ROW][COL])
{
    int x = 0;
    int y = 0;
    while (minecount != (ROW - 2)*(COL - 2) - DEFAULT)
    {
        printf("请输入坐标ROW（1-%d）COL（1-%d）：",ROW-2,ROW-2);
            scanf("%d%d", &x, &y);
        if (mine[x][y] == '1')
        {
            printf("踩到雷了：\n");
            printf("雷在棋盘的位置：\n");
            display_board(mine);
            printf("\n\n");
            return;
        }
        else
        {
          //  int ret = get_mine(mine, x, y);
          //  show[x][y] = ret + '0';
            check(mine,show,x,y);
            display_board(show);
        }
    }
    printf("扫雷成功\n");
}
void game()
{ 
    //char mine[ROW][COL];
    //char show[ROW][COL];

    init_board(mine, show);
    display_board(show);
    set_mine(mine);
    mine_sweep(mine, show);
}
