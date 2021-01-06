#pragma once
#include "data.h"

//画点
void drawPoint(int x, int y, int color);

//根据亮度修改对应的颜色
int changeColorByLight(int color, float light);

//增加了Light亮度参数
void drawPoint(int x, int y, int color, double light);

//画线段函数
void drawLine(int x1, int y1, int x2, int y2, int color, int type = SOLID_LINE);
void drawLine(Point p1, Point p2, int color, int type = SOLID_LINE);

//在屏幕上划分出一部分作为显示窗口
void drawWindow();
