#include "transform.h"
#include <iostream>



//把投影面上的点转换成屏幕的点
Point windowToScreen(Point p) {
    Point result;

    result.x = (p.x * SCREEN_LENGTH / WINDOW_LENGTH) + SCREEN_CENTER_X;
    result.y = (p.y * SCREEN_LENGTH / WINDOW_LENGTH) + SCREEN_CENTER_Y;
    result.z = p.z;

    return result;
}

//屏幕上点转换成投影面上的点
Point screenToWindow(Point p){
    Point result;

    result.x = (p.x - SCREEN_CENTER_X) * WINDOW_LENGTH / SCREEN_LENGTH;
    result.y = (p.y - SCREEN_CENTER_Y) * WINDOW_LENGTH / SCREEN_LENGTH;
    result.z = p.z;

    return result;
}

//把一个三角形转换到屏幕上
Triangle triangleToScreen(Triangle t) {
    Triangle result;

    result.v1 = windowToScreen(t.v1);
    result.v2 = windowToScreen(t.v2);
    result.v3 = windowToScreen(t.v3);

    return result;
}

/*
    世界坐标变换
    把模型坐标变换到世界空间
    @parameter m1 模型坐标在世界坐标中的位置location
    @parameter m2 模型坐标系的三个单位基向量在世界中的表示形式
    @return 一个变换矩阵
*/
Matrix worldTransform(ModelCoordinate mc) {
    Matrix m1, m2;

    double temp1[4][4] = { 
        {1,0,0,mc.location.x}, 
        {0,1,0,mc.location.y}, 
        {0,0,1,mc.location.z}, 
        {0,0,0,1} 
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m1.matrix[i][j] = temp1[i][j];//m1存储平移
        }
    }

    double temp2[4][4] = { 
        {mc.u.x,mc.v.x,mc.n.x,0}, 
        {mc.u.y,mc.v.y,mc.n.y,0}, 
        {mc.u.z,mc.v.z,mc.n.z,0}, 
        {0,     0,     0,     1}
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m2.matrix[i][j] = temp2[i][j];//m2存储坐标变换
        }
    }

    return matrixMultiply(m1, m2);
}


//根据camera把世界坐标转变成观察者坐标
Matrix viewTransform(Camera camera) {
    Matrix m1, m2;

    double temp1[4][4] = { 
        {1,0,0,-camera.location.x}, 
        {0,1,0,-camera.location.y}, 
        {0,0,1,-camera.location.z}, 
        {0,0,0,1} 
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m1.matrix[i][j] = temp1[i][j];//m1存储平移
        }
    }

    double temp2[4][4] = { 
        {camera.u.x,camera.u.y,camera.u.z,0}, 
        {camera.v.x,camera.v.y,camera.v.z,0}, 
        {camera.n.x,camera.n.y,camera.n.z,0}, 
        {0,         0,         0,         1}
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m2.matrix[i][j] = temp2[i][j];//m2存储坐标变换
        }
    }

    return matrixMultiply(m2, m1);
}

/*
    投影变换
    投影面是xy平面
    prp指的是投影参考点，利用它确定投影中心(透视投影)和投影方向（平行投影）
    type 参数指的是投影类型，（透视or平行）
    prp的坐标是（0，0，d）
*/

Matrix projectionTransform(Point prp, int type) {
    Matrix result = { 
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 1
    };

    switch (type) {
    case PARALLEL_PROJECTION:
        return result;
    case PERSPECTIVE_PROJECTION:
        result.matrix[3][2] = -1 / prp.z;
        return result;
    }
}

//一个点point经过三个变换后,得到点在屏幕的坐标
Point transform(Matrix worldTransform, Matrix viewTransform, Matrix projectionTransform, Point point) {
    Vector v = { point.x,point.y,point.z };

    v = matrixVectorProduct(worldTransform, v);
    v = matrixVectorProduct(viewTransform, v);
    v = matrixVectorProduct(projectionTransform, v);
    Point p = { v.x,v.y,v.z };
    p = windowToScreen(p);

    return p;
}
