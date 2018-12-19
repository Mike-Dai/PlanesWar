#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#pragma comment(lib,"Winmm.lib")		//ý���

#define Width 580//���
#define High 700//�߶�

IMAGE img_bk;
IMAGE img_planeNormal1, img_planeNormal2;	// ��ҷɻ�ͼƬ
IMAGE img_planeExplode1, img_planeExplode2; // ��ըͼƬ
IMAGE img_bullet1, img_bullet2;							// �ӵ�ͼƬ
IMAGE img_enemyPlane1, img_enemyPlane2;		//�л�ͼƬ
float position_x, position_y;		//���λ��
float bullet_x, bullet_y;				//�ӵ�λ��
float enemy_x, enemy_y;			//�л�λ��
int isExplode = 0;						//�ж��Ƿ�ը
int score = 0;							//����

void startup();						//��ʼ��
void show();							//��ʾͼƬ���÷�
void updateWithoutInput();	//�ж���ײ
void updateWithInput();		//������
void gameover();					//��Ϸ����

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
	//ѭ�����ű�������
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
		//��������ͼ��ʾͼƬ
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
	//��ʾ�÷�
	outtextxy(Width*0.48, High*0.95, L"�÷�");
	char s[5];
	sprintf(s, "%d", score);
	//outtextxy(Width*0.55, High*0.95, s);

	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	if (isExplode == 0)		//�����һ�����û�б�ը��
	{
		if (bullet_y > -25)
		{
			bullet_y -= 2;		//�ӵ�����2
		}
		if (enemy_y < High - 25)
		{
			enemy_y += 0.5;	//�л��½�0.5
		}
		else
		{
			enemy_y = 10;//����л����磬������Ļ��������

		}
		if (fabs(bullet_x - enemy_x) + fabs(bullet_y - enemy_y) < 80)//�ӵ����ел�
		{
			enemy_x = rand() % Width;//��������л�������
			enemy_y = -40;
			bullet_y = -85;
			//���Ż�ɱ��Ч
			mciSendString(L"close  gemusic ", NULL, 0, NULL);
			mciSendString(L"open D:\\planewar_source\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL);
			mciSendString(L"play gemusic", NULL, 0, NULL);
			score++;
		}
		if (fabs(position_x - enemy_x) + fabs(position_y - enemy_y) < 150)//��Һ͵л���ײ
		{
			isExplode = 1;
			//���ű�ը��Ч
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
		while (MouseHit())		//�����Ϣ
		{
			m = GetMouseMsg();
			//����ƶ�
			if (m.uMsg == WM_MOUSEMOVE)
			{
				position_x = m.x;
				position_y = m.y;
			}
			//�������
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
