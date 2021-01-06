#pragma once

#define PI 3.14159265358979323846
#define RAD (PI / 180) * 10 //10度

#define WINDOW_LENGTH 4//世界坐标系中要显示的平面，默认是[-2,2][-2,2]
#define WINDOW_WIDTH 4

#define SCREEN_LENGTH 400
#define SCREEN_WIDTH 400//把世界坐标系转换到屏幕时的大小

#define SCREEN_CENTER_X 320
#define SCREEN_CENTER_Y 240//世界坐标系原点对应的屏幕坐标

#define GRAPHIC_LENGTH 640
#define GRAPHIC_WIDTH 480//整个图形的大小，事实上，这个值不能小于上述屏幕的大小，但此处不做检查

#define PARALLEL_PROJECTION 1//代表平行投影
#define PERSPECTIVE_PROJECTION 2//代表透视投影

#define STEP 0.1//wsad,上下左右移动camera(物体)的步长

#define SOLID_LINE 1 //实线
#define DASH_LINE 2//虚线

#define PICTURE_LENGTH 1920//图片长
#define PICTURE_WIDTH 1200//图片宽

//窗口大小,也是裁剪的边
#define WINDOW_LEFT SCREEN_CENTER_X - SCREEN_LENGTH / 2
#define WINDOW_RIGHT SCREEN_CENTER_X + SCREEN_LENGTH / 2
#define WINDOW_TOP SCREEN_CENTER_Y - SCREEN_LENGTH / 2
#define WINDOW_BOTTOM SCREEN_CENTER_Y + SCREEN_LENGTH / 2

/**
	*点的定义，3维
	*本质上讲，点和向量在空间中是一一对应的
*/
struct Point
{
	double x;
	double y;
	double z;
};
/**
	*向量的定义,3维
*/
struct Vector
{
	double x;
	double y;
	double z;
};

/**
	*矩阵的定义
	*三维空间的变换矩阵采用4*4的齐次坐标
*/
struct Matrix {
	double matrix[4][4];
};

/*
	定义一个物体坐标系
*/
struct ModelCoordinate {
	Point location;
	Vector u;
	Vector v;
	Vector n;
};
/*
	camera的定义
	包括他处于世界坐标系中的位置和他的每个单位基向量
*/
struct Camera {
	Point location;
	Vector u;
	Vector v;
	Vector n;
};

//直线的定义
struct Line {
	Point p1;
	Point p2;
};

//三角形的定义
struct Triangle {
	Point v1;
	Point v2;
	Point v3;
};

//正方体表面的定义
typedef struct {
	Point p1;
	Point p2;
	Point p3;
	Point p4;
}Surface;

//立方体的定义
//八个点是 (0,0,0) (1,0,0) (0,1,0) (0,0,1) (1,1,0) (0,1,1) (1,0,1) (1,1,1)
struct Cube {
	Point p1;//作为立方体原点
	Point p2;//立方体u轴方向
	Point p3;//立方体v轴方向
	Point p4;//立方体n轴方向
	Point p5;//uOv平面另外一点
	Point p6;//vOn平面另外一点
	Point p7;//nOu平面另外一点
	Point p8;//余下最后一个点
};