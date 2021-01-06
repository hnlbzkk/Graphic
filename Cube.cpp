#include "Cube.h"
#include "Blinn-Phong.h"
#include "transform.h"
#include "Texture.h"
#include "Cut.h"

//phong着色方法画出一条线
void phong_paintLine(int point1_x, int point1_y, Vector point1_v, Point p1, int point2_x, int point2_y, Vector point2_v, Point p2, int color, int flagl,
	double Ka, double Ia, double Ip, Point PLight, double Kd, double Ks, Point view, double n) {
	if (point1_x == point2_x) {//斜率不存在时
		if (point1_y <= point2_y) {
			for (int y = point1_y; y <= point2_y; y++) {
				Vector v = { (double)(point2_y - y) / (point2_y - point1_y) * point1_v.x + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.x,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.y + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.y,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.z + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.z
				};
				Point P = { (double)(point2_y - y) / (point2_y - point1_y) * p1.x + (double)(y - point1_y) / (point2_y - point1_y) * p2.x,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.y + (double)(y - point1_y) / (point2_y - point1_y) * p2.y,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.z + (double)(y - point1_y) / (point2_y - point1_y) * p2.z
				};
				double light = Blinn_Phong(Ka, Ia, Ip, PLight, Kd, v, P, Ks, view, n);
				if (flagl == 0) {
					light = 0.5;
				}
				if(point1_x > 0)//左边界越界
					drawPoint(point1_x, y, colorBuffered[point1_x][y], light);
			}
		}
		else {
			for (int y = point2_y; y <= point1_y; y++) {
				Vector v = { (double)(point2_y - y) / (point2_y - point1_y) * point1_v.x + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.x,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.y + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.y,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.z + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.z
				};
				Point P = { (double)(point2_y - y) / (point2_y - point1_y) * p1.x + (double)(y - point1_y) / (point2_y - point1_y) * p2.x,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.y + (double)(y - point1_y) / (point2_y - point1_y) * p2.y,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.z + (double)(y - point1_y) / (point2_y - point1_y) * p2.z
				};
				double light = Blinn_Phong(Ka, Ia, Ip, PLight, Kd, v, P, Ks, view, n);
				if (flagl == 0) {
					light = 0.5;
				}
				drawPoint(point1_x, y, colorBuffered[point1_x][y], light);
			}
		}
	}//斜率不存在的情况完成
	int dx = point2_x - point1_x;
	int dy = point2_y - point1_y;
	double k = (float)dy / (float)dx;//斜率k

	if (k >= -1 && k <= 1) {//-1<=斜率<=1的
		if (point1_x <= point2_x) {//p1 x坐标小时
			double y = point1_y;
			for (int x = point1_x; x <= point2_x; x++) {
				Vector v = { (double)(point2_x - x) / (point2_x - point1_x) * point1_v.x + (double)(x - point1_x) / (point2_x - point1_x) * point2_v.x,
					(double)(point2_x - x) / (point2_x - point1_x) * point1_v.y + (double)(x - point1_x) / (point2_x - point1_x) * point2_v.y,
					(double)(point2_x - x) / (point2_x - point1_x) * point1_v.z + (double)(x - point1_x) / (point2_x - point1_x) * point2_v.z,
				};
				Point P = { (double)(point2_x - x) / (point2_x - point1_x) * p1.x + (double)(x - point1_x) / (point2_x - point1_x) * p1.x,
					(double)(point2_x - x) / (point2_x - point1_x) * p1.y + (double)(x - point1_x) / (point2_x - point1_x) * p1.y,
					(double)(point2_x - x) / (point2_x - point1_x) * p1.z + (double)(x - point1_x) / (point2_x - point1_x) * p1.z,
				};
				double light = Blinn_Phong(Ka, Ia, Ip, PLight, Kd, v, P, Ks, view, n);
				if (flagl == 0) {
					light = 0.5;
				}
				if(x > 0)//左边界越界
					drawPoint(x, (int)(y + 0.5), colorBuffered[x][(int)(y + 0.5)], light);
				y += k;
			}
		}
		else {
			double y = point2_y;
			for (int x = point2_x; x <= point1_x; x++) {
				Vector v = { (double)(point2_x - x) / (point2_x - point1_x) * point1_v.x + (double)(x - point1_x) / (point2_x - point1_x) * point2_v.x,
					(double)(point2_x - x) / (point2_x - point1_x) * point1_v.y + (double)(x - point1_x) / (point2_x - point1_x) * point2_v.y,
					(double)(point2_x - x) / (point2_x - point1_x) * point1_v.z + (double)(x - point1_x) / (point2_x - point1_x) * point2_v.z,
				};
				Point P = { (double)(point2_x - x) / (point2_x - point1_x) * p1.x + (double)(x - point1_x) / (point2_x - point1_x) * p2.x,
					(double)(point2_x - x) / (point2_x - point1_x) * p1.y + (double)(x - point1_x) / (point2_x - point1_x) * p2.y,
					(double)(point2_x - x) / (point2_x - point1_x) * p1.z + (double)(x - point1_x) / (point2_x - point1_x) * p2.z,
				};
				double light = Blinn_Phong(Ka, Ia, Ip, PLight, Kd, v, P, Ks, view, n);
				if (flagl == 0) {
					light = 0.5;
				}
				if(x > 0)//左边界越界
					drawPoint(x, (int)(y + 0.5), colorBuffered[x][(int)(y + 0.5)], light);
				y += k;
			}
		}
	}
	else {//斜率绝对值大于1的情况
		double k = (float)dx / (float)dy;//斜率
		if (point1_y <= point2_y) {
			double x = point1_x;
			for (int y = point1_y; y <= point2_y; y++) {
				Vector v = { (double)(point2_y - y) / (point2_y - point1_y) * point1_v.x + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.x,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.y + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.y,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.z + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.z,
				};
				Point P = { (double)(point2_y - y) / (point2_y - point1_y) * p1.x + (double)(y - point1_y) / (point2_y - point1_y) * p2.x,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.y + (double)(y - point1_y) / (point2_y - point1_y) * p2.y,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.z + (double)(y - point1_y) / (point2_y - point1_y) * p2.z,
				};
				double light = Blinn_Phong(Ka, Ia, Ip, PLight, Kd, v, P, Ks, view, n);
				if (flagl == 0) {
					light = 0.5;
				}
				if(x > 0)//左边界越界
					drawPoint((int)(x + 0.5), y, colorBuffered[(int)(x + 0.5)][y], light);
				x += k;
			}
		}
		else {
			double x = point2_x;
			for (int y = point2_y; y < point1_y; y++) {
				Vector v = { (double)(point2_y - y) / (point2_y - point1_y) * point1_v.x + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.x,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.y + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.y,
					(double)(point2_y - y) / (point2_y - point1_y) * point1_v.z + (double)(y - point1_y) / (point2_y - point1_y) * point2_v.z,
				};
				Point P = { (double)(point2_y - y) / (point2_y - point1_y) * p1.x + (double)(y - point1_y) / (point2_y - point1_y) * p2.x,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.y + (double)(y - point1_y) / (point2_y - point1_y) * p2.y,
					(double)(point2_y - y) / (point2_y - point1_y) * p1.z + (double)(y - point1_y) / (point2_y - point1_y) * p2.z,
				};
				double light = Blinn_Phong(Ka, Ia, Ip, PLight, Kd, v, P, Ks, view, n);
				if (flagl == 0) {
					light = 0.5;
				}
				if(x > 0)//左边界越界
					drawPoint((int)(x + 0.5), y, colorBuffered[(int)(x + 0.5)][y], light);
				x += k;
			}
		}
	}
}

//涂三角形，采用phong着色方法
void phong_paintTriangle(int p1_x, int p1_y, Vector v1, Point p1,
	int p2_x, int p2_y, Vector v2, Point p2,
	int p3_x, int p3_y, Vector v3, Point p3, int color, int flagl,
	double Ka, double Ia, double Ip, Point Plight, double Kd, double Ks, Point view, double n) {
	// 使得p1y<=p2y<=p3y
	if (p1_y <= p3_y && p3_y <= p2_y) {
		int temp = p3_y;
		p3_y = p2_y;
		p2_y = temp;

		temp = p3_x;
		p3_x = p2_x;
		p2_x = temp;

		Vector temp1 = v3;
		v3 = v2;
		v2 = temp1;

		Point tempp = p3;
		p3 = p2;
		p2 = tempp;
	}

	if (p2_y <= p1_y && p1_y <= p3_y) {
		int temp = p1_y;
		p1_y = p2_y;
		p2_y = temp;

		temp = p1_x;
		p1_x = p2_x;
		p2_x = temp;

		Vector temp1 = v1;
		v1 = v2;
		v2 = temp1;

		Point tempp = p1;
		p1 = p2;
		p2 = tempp;
	}

	if (p3_y <= p2_y && p2_y <= p1_y) {
		int temp = p3_y;
		p3_y = p1_y;
		p1_y = temp;

		temp = p3_x;
		p3_x = p1_x;
		p1_x = temp;

		Vector temp1 = v3;
		v3 = v1;
		v1 = temp1;

		Point tempp = p3;
		p3 = p1;
		p1 = tempp;
	}

	if (p2_y <= p3_y && p3_y <= p1_y) {
		int tempy = p1_y;
		p1_y = p2_y;
		p2_y = tempy;

		int tempx = p1_x;
		p1_x = p2_x;
		p2_x = tempx;

		Vector temp1 = v1;
		v1 = v2;
		v2 = temp1;

		Point tempp = p1;
		p1 = p2;
		p2 = tempp;

		int temp = p3_y;
		p3_y = p2_y;
		p2_y = temp;

		temp = p3_x;
		p3_x = p2_x;
		p2_x = temp;

		Vector templight = v3;
		v3 = v2;
		v2 = templight;

		Point temppp = p3;
		p3 = p2;
		p2 = temppp;
	}

	if (p3_y <= p1_y && p1_y <= p2_y) {
		int temp = p3_y;
		p3_y = p1_y;
		p1_y = temp;

		temp = p3_x;
		p3_x = p1_x;
		p1_x = temp;

		Vector temp1 = v3;
		v3 = v1;
		v1 = temp1;

		Point tempp = p3;
		p3 = p1;
		p1 = tempp;

		int temp2 = p3_y;
		p3_y = p2_y;
		p2_y = temp2;

		temp2 = p3_x;
		p3_x = p2_x;
		p2_x = temp2;

		Vector temp11 = v3;
		v3 = v2;
		v2 = temp11;

		Point temppp = p3;
		p3 = p2;
		p2 = temppp;
	}

	//平行于x轴的扫描线画法
	for (int y = p1_y; y < p2_y; y++) {
		double leftp_x = (double)(y - p1_y) / (p3_y - p1_y) * (p3_x - p1_x) + p1_x;
		Vector leftp_v = { (double)(y - p1_y) / (p3_y - p1_y) * (v3.x - v1.x) + v1.x,
			(double)(y - p1_y) / (p3_y - p1_y) * (v3.y - v1.y) + v1.y,
			(double)(y - p1_y) / (p3_y - p1_y) * (v3.z - v1.z) + v1.z,
		};
		Point leftp = { (double)(y - p1_y) / (p3_y - p1_y) * (p3.x - p1.x) + p1.x,
			(double)(y - p1_y) / (p3_y - p1_y) * (p3.y - p1.y) + p1.y,
			(double)(y - p1_y) / (p3_y - p1_y) * (p3.z - p1.z) + p1.z,
		};
		double rightp_x = (double)(y - p1_y) / (p2_y - p1_y) * (p2_x - p1_x) + p1_x;
		Vector rightp_v = { (double)(y - p1_y) / (p2_y - p1_y) * (v2.x - v1.x) + v1.x,
			(double)(y - p1_y) / (p2_y - p1_y) * (v2.y - v1.y) + v1.y,
			(double)(y - p1_y) / (p2_y - p1_y) * (v2.z - v1.z) + v1.z,
		};
		Point rightp = { (double)(y - p1_y) / (p2_y - p1_y) * (p2.x - p1.x) + p1.x,
			(double)(y - p1_y) / (p2_y - p1_y) * (p2.y - p1.y) + p1.y,
			(double)(y - p1_y) / (p2_y - p1_y) * (p2.z - p1.z) + p1.z,
		};
		phong_paintLine((int)(leftp_x + 0.5), y, leftp_v, leftp, (int)(rightp_x + 0.5), y, rightp_v, rightp, color, flagl, Ka, Ia, Ip, Plight, Kd, Ks, view, n);
	}

	for (int y = p2_y; y < p3_y; y++) {
		double leftp_x = (double)(y - p1_y) / (p3_y - p1_y) * (p3_x - p1_x) + p1_x;
		Vector leftp_v = { (double)(y - p1_y) / (p3_y - p1_y) * (v3.x - v1.x) + v1.x,
			(double)(y - p1_y) / (p3_y - p1_y) * (v3.y - v1.y) + v1.y,
			(double)(y - p1_y) / (p3_y - p1_y) * (v3.z - v1.z) + v1.z,
		};
		Point leftp = { (double)(y - p1_y) / (p3_y - p1_y) * (p3.x - p1.x) + p1.x,
			(double)(y - p1_y) / (p3_y - p1_y) * (p3.y - p1.y) + p1.y,
			(double)(y - p1_y) / (p3_y - p1_y) * (p3.z - p1.z) + p1.z,
		};
		double rightp_x = (double)(y - p3_y) / (p2_y - p3_y) * (p2_x - p3_x) + p3_x;
		Vector rightp_v = { (double)(y - p3_y) / (p2_y - p3_y) * (v2.x - v3.x) + v3.x,
			(double)(y - p3_y) / (p2_y - p3_y) * (v2.y - v3.y) + v3.y,
			(double)(y - p3_y) / (p2_y - p3_y) * (v2.z - v3.z) + v3.z,
		};
		Point rightp = { (double)(y - p3_y) / (p2_y - p3_y) * (p2.x - p3.x) + p3.x,
			(double)(y - p3_y) / (p2_y - p3_y) * (p2.y - p3.y) + p3.y,
			(double)(y - p3_y) / (p2_y - p3_y) * (p2.z - p3.z) + p3.z,
		};

		phong_paintLine((int)(leftp_x + 0.5), y, leftp_v, leftp, (int)(rightp_x + 0.5), y, rightp_v, rightp, color, flagl, Ka, Ia, Ip, Plight, Kd, Ks, view, n);

	}
}

//涂一个四边形,坐标屏幕坐标，并且点的顺序按照方向依次标注
void phong_paintQuadrangle(int p1_x, int p1_y, Vector v1, Point p1,
	int p2_x, int p2_y, Vector v2, Point p2,
	int p3_x, int p3_y, Vector v3, Point p3,
	int p4_x, int p4_y, Vector v4, Point p4,
	int color, int flagl,
	double Ka, double Ia, double Ip, Point Plight, double Kd, double Ks, Point view, double n) {
	//为了让四边形的连续性更好，需要把p1_y赋最小
	if (p1_y <= p2_y && p1_y <= p4_y) {
		phong_paintTriangle(p2_x, p2_y, v2, p2,
			p1_x, p1_y, v1, p1,
			p3_x, p3_y, v3, p3, color, flagl,
			Ka, Ia, Ip, Plight, Kd, Ks, view, n);

		phong_paintTriangle(p1_x, p1_y, v1, p1,
			p4_x, p4_y, v4, p4,
			p3_x, p3_y, v3, p3, color, flagl,
			Ka, Ia, Ip, Plight, Kd, Ks, view, n);
	}
	else {
		phong_paintQuadrangle(p2_x, p2_y, v2, p2,
			p3_x, p3_y, v3, p3,
			p4_x, p4_y, v4, p4,
			p1_x, p1_y, v1, p1, color, flagl,
			Ka, Ia, Ip, Plight, Kd, Ks, view, n);
	}
}

/*
屏幕上画一个立方体
需要知道：世界坐标变换矩阵，观察坐标变换矩阵，投影变换矩阵，立方体,投影参考点（用来确定哪些线可以看见）
采用的是phong方法(向量差值)
*/
void phong_drawCube(Matrix worldTransform, Matrix viewTransform, Matrix projectionTransform, Cube cube, Point prp,
	double Ka, double Ia, double Ip, Point PLight, double Kd, double Ks, Point view, double n, int color, IMAGE img,
	int model , int flagt , int flagl , int flagc ) {

	//正方体各个顶点对应的屏幕坐标
	Point p1 = transform(worldTransform, viewTransform, projectionTransform, cube.p1);
	Point p2 = transform(worldTransform, viewTransform, projectionTransform, cube.p2);
	Point p3 = transform(worldTransform, viewTransform, projectionTransform, cube.p3);
	Point p4 = transform(worldTransform, viewTransform, projectionTransform, cube.p4);
	Point p5 = transform(worldTransform, viewTransform, projectionTransform, cube.p5);
	Point p6 = transform(worldTransform, viewTransform, projectionTransform, cube.p6);
	Point p7 = transform(worldTransform, viewTransform, projectionTransform, cube.p7);
	Point p8 = transform(worldTransform, viewTransform, projectionTransform, cube.p8);

	//由于prp是在观察坐标系中，cube是在物体坐标系中，因此要先把他们坐标转化到同一个坐标系中，
	//因为矩阵求逆比较复杂，这里把8个点变换到观察坐标系中
	Cube viewCube;//观察坐标系中的立方体
	viewCube.p1 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p1))));
	viewCube.p2 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p2))));
	viewCube.p3 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p3))));
	viewCube.p4 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p4))));
	viewCube.p5 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p5))));
	viewCube.p6 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p6))));
	viewCube.p7 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p7))));
	viewCube.p8 = vectorToPoint(matrixVectorProduct(viewTransform, matrixVectorProduct(worldTransform, pointToVector(cube.p8))));

	//求得各个顶点法向量(vc)
	Vector v8 = { viewCube.p8.x - viewCube.p1.x,viewCube.p8.y - viewCube.p1.y,viewCube.p8.z - viewCube.p1.z };
	Vector v7 = { viewCube.p7.x - viewCube.p3.x,viewCube.p7.y - viewCube.p3.y,viewCube.p7.z - viewCube.p3.z };
	Vector v6 = { viewCube.p6.x - viewCube.p2.x,viewCube.p6.y - viewCube.p2.y,viewCube.p6.z - viewCube.p2.z };
	Vector v5 = { viewCube.p5.x - viewCube.p4.x,viewCube.p5.y - viewCube.p4.y,viewCube.p5.z - viewCube.p4.z };
	Vector v4 = { viewCube.p4.x - viewCube.p5.x,viewCube.p4.y - viewCube.p5.y,viewCube.p4.z - viewCube.p5.z };
	Vector v3 = { viewCube.p3.x - viewCube.p7.x,viewCube.p3.y - viewCube.p7.y,viewCube.p3.z - viewCube.p7.z };
	Vector v2 = { viewCube.p2.x - viewCube.p6.x,viewCube.p2.y - viewCube.p6.y,viewCube.p2.z - viewCube.p6.z };
	Vector v1 = { viewCube.p1.x - viewCube.p8.x,viewCube.p1.y - viewCube.p8.y,viewCube.p1.z - viewCube.p8.z };

	if (model == 1) {
		if (isVisibleSurface(viewCube, prp, Surface{ viewCube.p1,viewCube.p2,viewCube.p5,viewCube.p3 })) {
			if (flagt == 1) {
				addTexture(img, p1.x, p1.y, p2.x, p2.y, p5.x, p5.y, p3.x, p3.y);
			}
			else {
				addTexture(color, p1.x, p1.y, p2.x, p2.y, p5.x, p5.y, p3.x, p3.y);
			}
			phong_paintQuadrangle(p1.x, p1.y, v1, cube.p1,
				p2.x, p2.y, v2, cube.p2,
				p5.x, p5.y, v5, cube.p5,
				p3.x, p3.y, v3, cube.p3, color, flagl,
				Ka, Ia, Ip, PLight, Kd, Ks, view, n);
		}

		if (isVisibleSurface(viewCube, prp, Surface{ viewCube.p4,viewCube.p6,viewCube.p8,viewCube.p7 })) {
			if (flagt == 1) {
				addTexture(img, p4.x, p4.y, p6.x, p6.y, p8.x, p8.y, p7.x, p7.y);
			}
			else {
				addTexture(color, p4.x, p4.y, p6.x, p6.y, p8.x, p8.y, p7.x, p7.y);
			}
			phong_paintQuadrangle(p4.x, p4.y, v4, cube.p4,
				p6.x, p6.y, v6, cube.p6,
				p8.x, p8.y, v8, cube.p8,
				p7.x, p7.y, v7, cube.p7, color, flagl,
				Ka, Ia, Ip, PLight, Kd, Ks, view, n);
		}

		if (isVisibleSurface(viewCube, prp, Surface{ viewCube.p3,viewCube.p5,viewCube.p8,viewCube.p6 })) {
			if (flagt == 1)
				addTexture(img, p3.x, p3.y, p5.x, p5.y, p8.x, p8.y, p6.x, p6.y);
			else {
				addTexture(color, p3.x, p3.y, p5.x, p5.y, p8.x, p8.y, p6.x, p6.y);
			}
			phong_paintQuadrangle(p3.x, p3.y, v3, cube.p3,
				p5.x, p5.y, v5, cube.p5,
				p8.x, p8.y, v8, cube.p8,
				p6.x, p6.y, v6, cube.p6, color, flagl,
				Ka, Ia, Ip, PLight, Kd, Ks, view, n);
		}

		if (isVisibleSurface(viewCube, prp, Surface{ viewCube.p5,viewCube.p8,viewCube.p7,viewCube.p2 })) {
			if (flagt == 1)
				addTexture(img, p5.x, p5.y, p8.x, p8.y, p7.x, p7.y, p2.x, p2.y);
			else {
				addTexture(color, p5.x, p5.y, p8.x, p8.y, p7.x, p7.y, p2.x, p2.y);
			}
			phong_paintQuadrangle(p5.x, p5.y, v5, cube.p5,
				p8.x, p8.y, v8, cube.p8,
				p7.x, p7.y, v7, cube.p7,
				p2.x, p2.y, v2, cube.p2, color, flagl,
				Ka, Ia, Ip, PLight, Kd, Ks, view, n);
		}

		if (isVisibleSurface(viewCube, prp, Surface{ viewCube.p1,viewCube.p4,viewCube.p7,viewCube.p2 })) {
			if (flagt == 1)
				addTexture(img, p1.x, p1.y, p4.x, p4.y, p7.x, p7.y, p2.x, p2.y);
			else {
				addTexture(color, p1.x, p1.y, p4.x, p4.y, p7.x, p7.y, p2.x, p2.y);
			}

			phong_paintQuadrangle(p1.x, p1.y, v1, cube.p1,
				p4.x, p4.y, v4, cube.p4,
				p7.x, p7.y, v7, cube.p7,
				p2.x, p2.y, v2, cube.p2, color, flagl,
				Ka, Ia, Ip, PLight, Kd, Ks, view, n);
		}

		if (isVisibleSurface(viewCube, prp, Surface{ viewCube.p1,viewCube.p4,viewCube.p6,viewCube.p3 })) {
			if (flagt == 1)
				addTexture(img, p1.x, p1.y, p4.x, p4.y, p6.x, p6.y, p3.x, p3.y);
			else {
				addTexture(color, p1.x, p1.y, p4.x, p4.y, p6.x, p6.y, p3.x, p3.y);
			}
			phong_paintQuadrangle(p1.x, p1.y, v1, cube.p1,
				p4.x, p4.y, v4, cube.p4,
				p6.x, p6.y, v6, cube.p6,
				p3.x, p3.y, v3, cube.p3, color, flagl,
				Ka, Ia, Ip, PLight, Kd, Ks, view, n);
		}
	}

	if (model == 0) {
		if (isVisibleSide(viewCube, prp, Line{ viewCube.p1 ,viewCube.p2 })) {
			if (flagc == 1)
			{
				drawLine(p1, p2, WHITE);
			}else
			{
				C_S_Line_CLip(p1.x, p1.y, p2.x, p2.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p1, p2, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p1.x, p1.y, p2.x, p2.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p1 ,viewCube.p3 })) {
			if (flagc == 1)
			{
				drawLine(p1, p3, WHITE);
			}else
			{
				C_S_Line_CLip(p1.x, p1.y, p3.x, p3.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p1, p3, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p1.x, p1.y, p3.x, p3.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p1 ,viewCube.p4 })) {
			if (flagc == 1)
			{
				drawLine(p1, p4, WHITE);
			}else
			{
				C_S_Line_CLip(p1.x, p1.y, p4.x, p4.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p1, p4, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p1.x, p1.y, p4.x, p4.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p2 ,viewCube.p5 })) {

			if (flagc == 1)
			{
				drawLine(p2, p5, WHITE);
			}else
			{
				C_S_Line_CLip(p2.x, p2.y, p5.x, p5.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {

			if (flagc == 1)
			{
				drawLine(p2, p5, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p2.x, p2.y, p5.x, p5.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p2 ,viewCube.p7 })) {

			if (flagc == 1)
			{
				drawLine(p2, p7, WHITE);
			}else
			{
				C_S_Line_CLip(p2.x, p2.y, p7.x, p7.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p2, p7, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p2.x, p2.y, p7.x, p7.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p3 ,viewCube.p5 })) {
			if (flagc == 1)
			{
				drawLine(p3, p5, WHITE);
			}else
			{
				C_S_Line_CLip(p3.x, p3.y, p5.x, p5.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p3, p5, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p3.x, p3.y, p5.x, p5.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p3 ,viewCube.p6 })) {
			if (flagc == 1)
			{
				drawLine(p3, p6, WHITE);
			}else
			{
				C_S_Line_CLip(p3.x, p3.y, p6.x, p6.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p3, p6, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p3.x, p3.y, p6.x, p6.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p4 ,viewCube.p6 })) {
			if (flagc == 1)
			{
				drawLine(p4, p6, WHITE);
			}else
			{
				C_S_Line_CLip(p4.x, p4.y, p6.x, p6.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p4, p6, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p4.x, p4.y, p6.x, p6.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p4 ,viewCube.p7 })) {

			if (flagc == 1)
			{
				drawLine(p4, p7, WHITE);
			}else
			{
				C_S_Line_CLip(p4.x, p4.y, p7.x, p7.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p4, p7, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p4.x, p4.y, p7.x, p7.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p5 ,viewCube.p8 })) {
			if (flagc == 1)
			{
				drawLine(p5, p8, WHITE);
			}else
			{
				C_S_Line_CLip(p5.x, p5.y, p8.x, p8.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p5, p8, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p5.x, p5.y, p8.x, p8.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p6 ,viewCube.p8 })) {
			if (flagc == 1)
			{
				drawLine(p6, p8, WHITE);
			}else
			{
				C_S_Line_CLip(p6.x, p6.y, p8.x, p8.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p6, p8, WHITE, DASH_LINE);

			}else
			{
				C_S_Line_CLip(p6.x, p6.y, p8.x, p8.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

		if (isVisibleSide(viewCube, prp, Line{ viewCube.p7 ,viewCube.p8 })) {
			if (flagc == 1)
			{
				drawLine(p7, p8, WHITE);
			}else
			{
				C_S_Line_CLip(p7.x, p7.y, p8.x, p8.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
			}
		}
		else {
			if (flagc == 1)
			{
				drawLine(p7, p8, WHITE, DASH_LINE);
			}else
			{
				C_S_Line_CLip(p7.x, p7.y, p8.x, p8.y, WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, DASH_LINE);
			}
		}

	}
	if (model == 1)
		showScreen();
	else
		showScreen2();
}
