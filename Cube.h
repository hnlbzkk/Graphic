#pragma once

#include "data.h"
#include <easyx.h>

//根据两点之间颜色亮度的不同进行线性差值使得颜色渐变,
//坐标是屏幕坐标
//根据颜色差值，导致高光在中间区域的时候高光失效。需要注意
void gouraud_paintLine(int point1_x, int point1_y, double point1_light, int point2_x, int point2_y, double point2_light, int color);

//phong着色方法画出一条线
void phong_paintLine(int point1_x, int point1_y, Vector point1_v, Point p1, int point2_x, int point2_y, Vector point2_v, Point p2, int color, int flagl,
	double Ka, double Ia, double Ip, Point PLight, double Kd, double Ks, Point view, double n);

//涂一个三角形，三角形坐标是屏幕坐标
void gouraud_paintTriangle(int p1_x, int p1_y, double p1_light,
	int p2_x, int p2_y, double p2_light,
	int p3_x, int p3_y, double p3_light, int color);

//画三角形，采用phong着色方法
void phong_paintTriangle(int p1_x, int p1_y, Vector v1, Point p1,
	int p2_x, int p2_y, Vector v2, Point p2,
	int p3_x, int p3_y, Vector v3, Point p3, int color, int flagl,
	double Ka, double Ia, double Ip, Point Plight, double Kd, double Ks, Point view, double n);

//涂一个四边形,坐标屏幕坐标，并且点的顺序按照方向依次标注
void gouraud_paintQuadrangle(int p1_x, int p1_y, double p1_light,
	int p2_x, int p2_y, double p2_light,
	int p3_x, int p3_y, double p3_light,
	int p4_x, int p4_y, double p4_light, int color);

//涂一个四边形,坐标屏幕坐标，并且点的顺序按照方向依次标注
void phong_paintQuadrangle(int p1_x, int p1_y, Vector v1, Point p1,
	int p2_x, int p2_y, Vector v2, Point p2,
	int p3_x, int p3_y, Vector v3, Point p3,
	int p4_x, int p4_y, Vector v4, Point p4,
	int color, int flagl,
	double Ka, double Ia, double Ip, Point Plight, double Kd, double Ks, Point view, double n);

/*
屏幕上画一个立方体
需要知道：世界坐标变换矩阵，观察坐标变换矩阵，投影变换矩阵，立方体,投影参考点（用来确定哪些线可以看见）
采用gouraud着色方法(颜色差值)
*/
void gouraud_drawCube(Matrix worldTransform, Matrix viewTransform, Matrix projectionTransform, Cube cube, Point prp,
	double Ka, double Ia, double Ip, Point PLight, double Kd, double Ks, Point view, double n, int color, int model = 0/*0表示线框模式,1是光照模式*/);

/*
屏幕上画一个立方体
需要知道：世界坐标变换矩阵，观察坐标变换矩阵，投影变换矩阵，立方体,投影参考点（用来确定哪些线可以看见）
相比于上一个，采用的是phong方法(向量差值)
*/
void phong_drawCube(Matrix worldTransform, Matrix viewTransform, Matrix projectionTransform, Cube cube, Point prp,
	double Ka, double Ia, double Ip, Point PLight, double Kd, double Ks, Point view, double n, int color, IMAGE img,
	int model = 1, int flagt = 1, int flagl = 1/*0表示线框模式,1是光照模式*/, int flagc = 1);