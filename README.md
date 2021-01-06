# Cpp
图形学自学任务

百度：图形学自学任务：https://wenku.baidu.com/view/ec42d707bceb19e8b9f6ba13.html

本人C/C++不熟悉，一直使用Java，所以在这个程序中，将.h文件理解为Java的接口类，纯定义方法名，具体实现就是对应的.cpp文件

无BUG可以全部实现

下面开始解释各个步骤，能更快理解：（全部只针对.h文件，对应的cpp都是实现）

一、二：data.h 定义 点、矩阵、向量、三角形、正方形、正方体 以及 固定的常量如：图片大小，窗口大小、裁剪大小、步长、π 等
三：vectorOperate 向量加减、点积、叉积和其他算法
四：transform  坐标变换算法
五：Line 画线算法，使用的是 DDA 算法。这里写了裁剪窗口的drawWindow() 
六：Blinn-phong光照算法
七：Cube 在gouraud算法基础上（已删）使用phong着色算法 画点/线/三角面/四边形/立方体  有model、flagt、flagl、flagc对应着之后的线框模式、纹理、光照、裁剪（裁剪在线框模式下）
八：Texture 纹理算法，使用z-buffer算法
九：cut  使用最基础的直线裁剪算法
十：main函数的keyboard方法，改变步长发生移动

所以成品可以支持：绘制线框模式（“o”“O”键） 是否使用纹理（“t”“T”键） 是否使用光照（“l”“L”）  在线框模式下是否使用裁剪（“c”“C”）非线框模式下，是将超出窗口直接涂黑，也不算具体算法
