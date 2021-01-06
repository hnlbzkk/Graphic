#include <iostream>
#include <conio.h>
#include "Cube.h"
#include "Texture.h"
#include "transform.h"
#include "Cut.h"

using namespace std;


int keyboard(int key, Camera& camera, ModelCoordinate& mc, int& model, int& flagt, int& flagl, int& flagc) {
	switch (key) {
		//相机移动
	case 'w':
	case 'W':
		camera.location.y -= STEP;
		break;
	case 'a':
	case 'A':
		camera.location.x -= STEP;
		break;
	case 's':
	case 'S':
		camera.location.y += STEP;
		break;
	case 'd':
	case 'D':
		camera.location.x += STEP;
		break;
		//上下左右旋转物体，物体绕着世界坐标轴转动
	case 77:mc.u = rotateZ(mc.u, -RAD);
		mc.v = rotateZ(mc.v, -RAD);
		mc.n = rotateZ(mc.n, -RAD);//右对应的ascii
		break;
	case 80:mc.u = rotateX(mc.u, -RAD);
		mc.v = rotateX(mc.v, -RAD);
		mc.n = rotateX(mc.n, -RAD);//下对应的ascii
		break;
	case 72:mc.u = rotateX(mc.u, RAD);
		mc.v = rotateX(mc.v, RAD);
		mc.n = rotateX(mc.n, RAD);//上对应的ascii
		break;
	case 75:mc.u = rotateZ(mc.u, RAD);//左对应的ascii
		mc.v = rotateZ(mc.v, RAD);
		mc.n = rotateZ(mc.n, RAD);
		break;
	case 'O':
	case 'o':
	{
		model = !model;
		if (model)
		{
			flagc = 1;
		}
		break;
	}
	case 't':
	case'T':flagt = !flagt;
		break;
	case'l':
	case'L':flagl = !flagl;
		break;
	case 'c':
	case 'C':
	{
		flagc = !flagc;
		break;
	}
	case 27:
		return 5;
	}

}

int main()
{
	initgraph(GRAPHIC_LENGTH, GRAPHIC_WIDTH);
	IMAGE img;
	loadimage(&img, L"./1.jpg");
	HDC hdc = GetImageHDC(&img);
	for (int j = 0; j < PICTURE_WIDTH; j++) {
		for (int i = 0; i < PICTURE_LENGTH; i++) {
			pictureColor[i][j] = GetPixel(hdc, i, j);
		}
	}

	drawWindow();

	Cube cube = {
		{-0.5,-0.5,-0.5},
		{ 0.5,-0.5,-0.5},
		{-0.5, 0.5,-0.5},
		{-0.5,-0.5, 0.5},
		{ 0.5, 0.5,-0.5},
		{-0.5, 0.5, 0.5},
		{ 0.5,-0.5, 0.5},
		{ 0.5, 0.5, 0.5},
	};

	ModelCoordinate mc = { { 0,0,0 } ,{ 1,0,0 },{ 0,1,0 } ,{ 0,0,1 } };
	Matrix worldMatrix = worldTransform(mc);//获得世界矩阵

	Camera camera = { { 0,0,0 } ,{ 1,0,0 },{ 0,1,0 } ,{ 0,0,1 } };
	Matrix viewMatrix = viewTransform(camera);//根据camera获得观察矩阵

	Point prp = { 0,0,5 };//投影参考点,其坐标是观察空间系坐标
	Matrix projectionMatrix = projectionTransform(prp, PERSPECTIVE_PROJECTION);//根据prp获得投影矩阵

	double Ka = 0.6;//环境光反射系数
	double Ia = 0.5;//环境光亮度
	double Ip = 0.4;//点光源亮度
	Point PLight = { 0,0,5 };//光源位置
	double Kd = 0.7;//漫反射系数
	double Ks = 0.5;//镜面反射系数
	Point view = { 1,2,3 };//视点
	double n = 40;

	int model = 1;//模式，表示是以线框模式还是光照模式显示物体。
	int flagt = 1;//开关纹理
	int flagl = 1;//开关灯光
	int flagc = 1;//线框模式下裁剪


	phong_drawCube(worldMatrix, viewMatrix, projectionMatrix, cube, prp,
		Ka, Ia, Ip, PLight, Kd, Ks, view, n, WHITE, img, model, flagt, flagl, flagc);//画出立方体
	clearBuffer();//画完之后把缓冲区清空
	while (true) {
		drawWindow();
		input:int input = _getch();
		int flag = keyboard(input, camera, mc, model, flagt, flagl, flagc);
		if (flag == 5) return false;

		worldMatrix = worldTransform(mc);
		viewMatrix = viewTransform(camera);
		
		phong_drawCube(worldMatrix, viewMatrix, projectionMatrix, cube, prp,
			Ka, Ia, Ip, PLight, Kd, Ks, view, n, WHITE, img, model, flagt, flagl, flagc);//画出立方体
		clearBuffer();//画完之后把缓冲区清空
	}

	closegraph();
}
