#pragma once
#include "data.h"
#include "Line.h"

#define LEFT 1 //编码 0001
#define RIGHT 2//编码 0010
#define BOTTOM 4//编码 0100
#define TOP 8//编码 1000
//直线裁剪算法，对坐标转二进制
int encode(int x, int y);
//直线裁剪算法
void C_S_Line_CLip(int x1, int y1, int x2, int y2, int XL, int XR, int YB, int YT, int dashline = 1);

//判断一个屏幕上的点是否在窗口内
bool isInWindow(int x, int y);

//判断一个点是否在正方体内部
bool isInCube(Cube cube, Point p);

/*
	判断一个立方体表面一个点对于参考点是否可见
	逻辑：取一个距离该表面点很近的一个点，并且该点朝着参考点。如果该点在立方体里面，那么该点不可见，否则，可见
*/
bool isVisiblePoint(Cube cube, Point prp, Point p);

//判断正方体的边是否可见
bool isVisibleSide(Cube cube, Point prp, Line edge);

//判断正方体的面是否可见
bool isVisibleSurface(Cube cube, Point prp, Surface surface);