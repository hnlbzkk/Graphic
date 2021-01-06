//#pragma once

#include <math.h>
#include <easyx.h>
#include "data.h"
#include "vectorOperate.h"
#include "Line.h"
#include "transform.h"

/*Blinn_Phong光照模型
	double Ka ;//环境光反射系数
	double Ia ;//环境光光强
	double Ip ;//点光源光强
	Point PLight ;//光源位置
	double Kd ;//漫反射系数
	Vector N ;//顶点法向量
	Point P//待绘制点
	double Ks //镜面反射系数
	Point view ;//视点
	double n ;//光泽度
*/
double Blinn_Phong(double Ka, double Ia, double Ip, Point PLight, double Kd, Vector N, Point P, double Ks, Point view, double n) {
	double I1 = Ia * Ka;//环境光亮度
	Vector L = { PLight.x - P.x,PLight.y - P.y,PLight.z - P.z };//点指向光源的向量
	L = unitization(L);
	N = unitization(N);//视野与光纤中间向量
	double I2 = Ip * Kd * dotProduct(L, N);//漫反射亮度
	Vector V = { view.x - P.x,view.y - P.y,view.z - P.z };//点指向视点的向量
	V = unitization(V);
	Vector H = addVector(L, V);//法线方向
	H = unitization(H);
	double I3 = Ks * Ip * pow(dotProduct(H, N), n);
	return I1 + I2 + I3;
}
