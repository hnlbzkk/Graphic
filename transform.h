#pragma once

#include "data.h"
#include "vectorOperate.h"

/*
 * 类似java抽象类，存储变换函数
*/

//把投影面上的点转换成屏幕的点
Point windowToScreen(Point p);

//屏幕上点转换成投影面上的点
Point screenToWindow(Point p);

//把一个三角形转换到屏幕上
Triangle triangleToScreen(Triangle t);

/*
    世界坐标变换
    把模型坐标变换到世界空间
    @parameter模型坐标在世界坐标中的位置location
    @parameter模型坐标系的三个单位基向量在世界中的表示形式
    @return一个变换矩阵
*/
Matrix worldTransform(ModelCoordinate mc);


//根据camera把世界坐标转变成观察者坐标
Matrix viewTransform(Camera camera);

/*
    投影变换
    投影面是xy平面
    prp指的是投影参考点，利用它确定投影中心(透视投影)和投影方向（平行投影）
    type 参数指的是投影类型，（透视or平行）

    prp的坐标是（0，0，d）
*/
Matrix projectionTransform(Point prp, int type = PARALLEL_PROJECTION);

//一个点point经过三个变换后,得到点在屏幕的坐标
Point transform(Matrix worldTransform, Matrix viewTransform, Matrix projectionTransform, Point point);
