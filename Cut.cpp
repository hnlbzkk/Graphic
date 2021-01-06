#include "Cut.h"
#include "vectorOperate.h"
#include "transform.h"
#include "Cut.h"
#include <easyx.h>

int encode(int x, int y) {
	int c = 0;
	if (x < WINDOW_LEFT) c = c | LEFT;
	else if (x > WINDOW_RIGHT) c = c | RIGHT;
	if (y > WINDOW_BOTTOM) c = c | BOTTOM;//左上是原点，所以Y < Y(bottom) 就是 y > WINDOW_BOTTOM
	else if (y < WINDOW_TOP) c = c | TOP;
	return c;
}
//直线裁剪算法
void C_S_Line_CLip(int x1, int y1, int x2, int y2, int XL, int XR, int YB, int YT, int dashline /* = 1 */)
{
	int code1, code2, code;
	int x, y;
	code1 = encode(x1, y1);
	code2 = encode(x2, y2);
	//code1 0000 code2 0000  简取
	while (code1 != 0 || code2 != 0)
	{
		if ((code1 & code2) != 0) return;//简弃
		code = code1;
		if (code == 0) code = code2;
		if ((LEFT & code) != 0)//线段与左边界相交
		{
			x = XL;
			y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
		}
		else if ((RIGHT & code) != 0)//线段与右边界相交
		{
			x = XR;
			y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
		}
		else if ((BOTTOM & code) != 0)//线段与下边界相交
		{
			y = YB;
			x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
		}
		else if ((TOP & code) != 0)//线段与上边界相交
		{
			y = YT;
			x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
		}
		if (code == code1) {
			x1 = x;
			y1 = y;
			code1 = encode(x, y);
		}
		else {
			x2 = x;
			y2 = y;
			code2 = encode(x, y);
		}
	}
	drawLine(x1, y1, x2, y2, WHITE, dashline);
	return;
}

//判断一个屏幕上的点是否在窗口内
bool isInWindow(int x, int y) {
	if (x < WINDOW_LEFT || x > WINDOW_RIGHT) {
		return false;
	}
	else if (y < WINDOW_TOP || y > WINDOW_BOTTOM) {
		return false;
	}

	return true;
}

//判断一个点是否在正方体内部
bool isInCube(Cube cube, Point p) {
	Vector u = { cube.p2.x - cube.p1.x, cube.p2.y - cube.p1.y, cube.p2.z - cube.p1.z };
	Vector v = { cube.p3.x - cube.p1.x, cube.p3.y - cube.p1.y, cube.p3.z - cube.p1.z };
	Vector n = { cube.p4.x - cube.p1.x, cube.p4.y - cube.p1.y, cube.p4.z - cube.p1.z };
	double length = mod(u);
	double width = mod(v);
	double higth = mod(n);//求得立方体长宽高
	u = unitization(u);//单位向量
	v = unitization(v);
	n = unitization(n);
	//注意到变换的过程类似于viewTransform,采用类似的方法完成变换
	Camera ca = { cube.p1,u,v,n };
	Matrix viewMatrix = viewTransform(ca);//获得了变换矩阵

	Vector vp = { p.x,p.y,p.z };
	vp = matrixVectorProduct(viewMatrix, vp);//获得了变换后p的坐标

	if (vp.x < 0 || vp.x  >length) return false;
	if (vp.y < 0 || vp.y > width) return false;
	if (vp.z < 0 || vp.z  >higth) return false;
	return true;
}

/*
	判断一个立方体表面一个点对于参考点是否可见
	逻辑：取一个距离该表面点很近的一个点，并且该点朝着参考点。如果该点在立方体里面，那么该点不可见，否则，可见
*/
bool isVisiblePoint(Cube cube, Point prp, Point p) {
	Vector v = {
		prp.x - p.x,
		prp.y - p.y,
		prp.z - p.z
	};
	v = unitization(v);
	Point newp = { p.x + v.x / 10000,p.y + v.y / 10000,p.z + v.z / 10000 };//newp是一个与p很近的一个点
	if (isInCube(cube, newp)) {
		return false;
	}
	return true;
}

//判断正方体的边是否可见
bool isVisibleSide(Cube cube, Point prp, Line edge) {
	if (isVisiblePoint(cube, prp, edge.p1) && isVisiblePoint(cube, prp, edge.p2)) {//两点都可见，则边可见
		return true;
	}
	else {
		return false;
	}
}

//判断正方体的面是否可见
bool isVisibleSurface(Cube cube, Point prp, Surface surface) {
	if (isVisibleSide(cube, prp, Line{ surface.p1,surface.p2 }) &&
		isVisibleSide(cube, prp, Line{ surface.p2,surface.p3 }) &&
		isVisibleSide(cube, prp, Line{ surface.p3,surface.p4 }) &&
		isVisibleSide(cube, prp, Line{ surface.p4,surface.p1 })
		) {//四边都可见，则面可见
		return true;
	}
	else {
		return false;
	}
}