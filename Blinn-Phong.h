#pragma once

//存放一些与算法有关的函数

/*Blinn_Phong光照模型
	double Ka ;//环境光反射系数
	double Ia ;//环境光亮度
	double Ip ;//点光源亮度
	Point PLight ;//光源位置
	double Kd ;//漫反射系数
	Vector N ;//顶点法向量
	Point P//待绘制点
	double Ks //镜面反射系数
	Point view ;//视点
	double n ;//镜面反射指数
*/
double Blinn_Phong(double Ka, double Ia, double Ip, Point PLight, double Kd, Vector N, Point P, double Ks, Point view, double n);
