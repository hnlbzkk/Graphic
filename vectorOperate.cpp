#include "vectorOperate.h"
#include <math.h>

//点和向量的互转
Vector pointToVector(Point p) {
    return { p.x,p.y,p.z };
}

Point vectorToPoint(Vector v) {
    return { v.x,v.y,v.z };
}

//向量长度
double mod(Vector v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//单位向量
Vector unitization(Vector v) {
    double m = mod(v);

    Vector result = { v.x / m,v.y / m,v.z / m };

    return result;
}

//加
Vector addVector(Vector v1, Vector v2) {
    Vector v;

    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;

    return v;
}

//减
Vector subVector(Vector v1, Vector v2) {
    Vector v;

    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;

    return v;
}

//点积
double dotProduct(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//叉积
Vector crossProduct(Vector v1, Vector v2) {
    Vector v;

    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;

    return v;
}

/**
    *矢量和矩阵的乘积
    *也就是点和向量的坐标变换
    *此方法进行的是矢量和矩阵的运算，要先把矢量映射到4维，进行运算后齐次化，还原到三维。
*/
Vector matrixVectorProduct(Matrix m, Vector v) {
    Vector result;

    result.x = m.matrix[0][0] * v.x + m.matrix[0][1] * v.y + m.matrix[0][2] * v.z + m.matrix[0][3];
    result.y = m.matrix[1][0] * v.x + m.matrix[1][1] * v.y + m.matrix[1][2] * v.z + m.matrix[1][3];
    result.z = m.matrix[2][0] * v.x + m.matrix[2][1] * v.y + m.matrix[2][2] * v.z + m.matrix[2][3];
    double n = m.matrix[3][0] * v.x + m.matrix[3][1] * v.y + m.matrix[3][2] * v.z + m.matrix[3][3];
    result.x /= n;
    result.y /= n;
    result.z /= n;

    return result;
}

//矩阵和矩阵的乘积，4维矩阵
Matrix matrixMultiply(Matrix m1, Matrix m2) {
    Matrix result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double temp = 0;
            for (int k = 0; k < 4; k++) {
                temp += m1.matrix[i][k] * m2.matrix[k][j];
            }
            result.matrix[i][j] = temp;
        }
    }
    return result;
}
//左手坐标系
//绕x轴旋转
Vector rotateX(Vector v, double rad) {
    Vector result;

    double cosValue = cos(rad);
    double sinValue = sin(rad);

    result.x = v.x;
    result.y = cosValue * v.y + sinValue * v.z;
    result.z = -sinValue * v.y + cosValue * v.z;

    return result;
}

//绕y轴旋转
Vector rotateY(Vector v, double rad) {
    Vector result;

    double cosValue = cos(rad);
    double sinValue = sin(rad);

    result.x = cosValue * v.x - sinValue * v.z;
    result.y = v.y;
    result.z = sinValue * v.x + cosValue * v.z;

    return result;
}

//绕z轴旋转
Vector rotateZ(Vector v, double rad) {
    Vector result;

    double cosValue = cos(rad);
    double sinValue = sin(rad);

    result.x = cosValue * v.x + sinValue * v.y;
    result.y = -sinValue * v.x + cosValue * v.y;
    result.z = v.z;

    return result;
}

