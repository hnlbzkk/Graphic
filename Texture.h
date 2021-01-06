#pragma once
//实现与纹理相关的函数
#include <easyx.h>
#include "data.h"

//图片坐标转纹理坐标
Point picToTexture(int width, int height, int x, int y);

//纹理坐标转颜色缓冲区坐标
Point texttureToBuff(double x, double y, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

//实现把纹理的颜色加到一个四边形上去修改缓冲区
void addTexture(IMAGE img, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void addTexture(COLORREF color, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);


//缓冲区部分算法
extern int colorBuffered[GRAPHIC_LENGTH][GRAPHIC_WIDTH];//缓冲区存放颜色
extern int pictureColor[PICTURE_LENGTH][PICTURE_WIDTH];//照片数组
void showScreen();
void showScreen2();
void clearBuffer();