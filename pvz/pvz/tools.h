#pragma once
#include <graphics.h>
#include <stdio.h>
#include<iostream>

void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);//实现透明图片无黑边导入
int getDelay();
bool fileExist(const char* name);
void CoolImage(IMAGE* src, IMAGE* dst);//减速的蓝色效果，第一个参数为原图，第二个参数存放结果
int GetFileNum(const char* filePath);
int GetFileNum2(const char* filePath);
bool CheckHit(int x, int y, int objX, int objy, int objW, int objH);
bool CheckHitX(int x, int objX, int objW);
void flipimage(IMAGE* src,IMAGE* dst);
void SketchImage(IMAGE* src, IMAGE* dst);