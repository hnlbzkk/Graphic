#pragma once
#include "data.h"
/*
* 类似java抽象类，存储操作方法
*/
//点和向量的互转
Vector pointToVector(Point p);
Point vectorToPoint(Vector v);
//向量长度
double mod(Vector v);
//单位向量
Vector unitization(Vector v);

//加减
Vector addVector(Vector v1, Vector v2);
Vector subVector(Vector v1, Vector v2);

//点积
double dotProduct(Vector v1, Vector v2);
//叉积
Vector crossProduct(Vector v1, Vector v2);

//矢量和矩阵的乘积
Vector matrixVectorProduct(Matrix m, Vector v);
//矩阵和矩阵的乘积，4维矩阵 
Matrix matrixMultiply(Matrix m1, Matrix m2);

//ZXY轴
Vector rotateZ(Vector v, double rad);
Vector rotateX(Vector v, double rad);
Vector rotateY(Vector v, double rad);