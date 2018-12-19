#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#pragma comment(lib,"Winmm.lib")		//媒体库

#define Width 580//宽度
#define High 700//高度

IMAGE img_bk;
IMAGE img_planeNormal1, img_planeNormal2;	// 玩家飞机图片
IMAGE img_planeExplode1, img_planeExplode2; // 爆炸图片
IMAGE img_bullet1, img_bullet2;							// 子弹图片
IMAGE img_enemyPlane1, img_enemyPlane2;		//敌机图片
float position_x, position_y;		//玩家位置
float bullet_x, bullet_y;				//子弹位置
float enemy_x, enemy_y;			//敌机位置
int isExplode = 0;						//判断是否爆炸
int score = 0;							//分数

void startup();						//初始化
void show();							//显示图片，得分
void updateWithoutInput();	//判断碰撞
void updateWithInput();		//鼠标操作
void gameover();					//游戏结束

int main()
{
	startup();
	while (1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	gameover();
    return 0;
}

void startup()
{
	initgraph(Width, High);
	loadimage(&img_bk,L"D:\\planewar_source\\background.jpg");
	loadimage(&img_bullet1, L"D:\\planewar_source\\bullet1.jpg");
	loadimage(&img_bullet2, L"D:\\planewar_source\\bullet2.jpg");
	loadimage(&img_enemyPlane1, L"D:\\planewar_source\\enemyPlane1.jpg");
	loadimage(&img_enemyPlane2, L"D:\\planewar_source\\enemyPlane2.jpg");
	loadimage(&img_planeExplode1, L"D:\\planewar_source\\planeExplode_1.jpg");
	loadimage(&img_planeExplode2, L"D:\\planewar_source\\planeExplode_2.jpg");
	loadimage(&img_planeNormal1, L"D:\\planewar_source\\planeNormal_1.jpg");
	loadimage(&img_planeNormal2, L"D:\\planewar_source\\planeNormal_2.jpg");
	//循环播放背景音乐
	mciSendString(L"open D:\\planewar_source\\game_music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
	position_x = Width * 0.5;
	position_y = High * 0.7;
	bullet_x = position_x;
	bullet_y = -85;
	enemy_x = Width * 0.5;
	enemy_y = 10;
	BeginBatchDraw();
}

void show()
{
	putimage(0, 0, &img_bk);
	if ( isExplode == 0 )
	{
		//利用遮罩图显示图片
		putimage(position_x-50, position_y-60, &img_planeNormal1, NOTSRCERASE);
		putimage(position_x - 50, position_y - 60, &img_planeNormal2, SRCINVERT);
		putimage(bullet_x - 7, bullet_y, &img_bullet1, NOTSRCERASE);
		putimage(bullet_x - 7, bullet_y, &img_bullet2, SRCINVERT);
		putimage(enemy_x - 50, enemy_y - 70, &img_enemyPlane1, NOTSRCERASE);
		putimage(enemy_x - 50, enemy_y - 70, &img_enemyPlane2, SRCINVERT);
	}
	else {
		putimage(position_x - 50, position_y - 60, &img_planeExplode1, NOTSRCERASE);
		putimage(position_x - 50, position_y - 60, &img_planeExplode2, SRCINVERT);
	}
	//显示得分
	outtextxy(Width*0.48, High*0.95, L"得分");
	char s[5];
	sprintf(s, "%d", score);
	//outtextxy(Width*0.55, High*0.95, s);

	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	if (isExplode == 0)		//如果玩家还存活（即没有爆炸）
	{
		if (bullet_y > -25)
		{
			bullet_y -= 2;		//子弹上移2
		}
		if (enemy_y < High - 25)
		{
			enemy_y += 0.5;	//敌机下降0.5
		}
		else
		{
			enemy_y = 10;//如果敌机出界，则在屏幕顶端重生

		}
		if (fabs(bullet_x - enemy_x) + fabs(bullet_y - enemy_y) < 80)//子弹击中敌机
		{
			enemy_x = rand() % Width;//随机产生敌机横坐标
			enemy_y = -40;
			bullet_y = -85;
			//播放击杀音效
			mciSendString(L"close  gemusic ", NULL, 0, NULL);
			mciSendString(L"open D:\\planewar_source\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
			mciSendString(L"play gemusic", NULL, 0, NULL);
			score++;
		}
		if (fabs(position_x - enemy_x) + fabs(position_y - enemy_y) < 150)//玩家和敌机相撞
		{
			isExplode = 1;
			//播放爆炸音效
			mciSendString(L"close exmusic", NULL, 0, NULL);
			mciSendString(L"open D:\\planewar_source\\explode.mp3 alias exmusic", NULL, 0, NULL);
			mciSendString(L"play exmusic", NULL, 0, NULL);
		}
	}
}

void updateWithInput()
{
	if (isExplode == 0)
	{
		MOUSEMSG m;
		while (MouseHit())		//鼠标消息
		{
			m = GetMouseMsg();
			//鼠标移动
			if (m.uMsg == WM_MOUSEMOVE)
			{
				position_x = m.x;
				position_y = m.y;
			}
			//单击左键
			else if (m.uMsg == WM_LBUTTONDOWN)
			{
				bullet_x = position_x;
				bullet_y = position_y - 85;
				mciSendString(L"close fgmusic", NULL, 0, NULL);
				mciSendString(L"open D:\\planewar_source\\f_gun.mp3 alias fgmusic", NULL, 0, NULL);
				mciSendString(L"play fgmusic", NULL, 0, NULL);
			}
		}
	}
}

void gameover()
{
	EndBatchDraw();
	getchar();
	closegraph();
}
