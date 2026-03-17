#include "tools.h"
void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture) 
{
	DWORD* dst = GetImageBuffer();    
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); 
	int picture_width = picture->getwidth(); 
	int picture_height = picture->getheight(); 
	int graphWidth = getwidth();      
	int graphHeight = getheight();     
	int dstX = 0;   

	
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //image的像素点是按一维数组存的，id=列+行*宽
			int sa = ((src[srcX] & 0xff000000) >> 24); 
			int sr = ((src[srcX] & 0xff0000) >> 16); 
			int sg = ((src[srcX] & 0xff00) >> 8);   
			int sb = src[srcX] & 0xff;              
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; 
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
					| (sb * sa / 255 + db * (255 - sa) / 255);
			}
		}
	}
}

void putimagePNG(int x, int y, IMAGE* picture) {

	IMAGE imgTmp, imgTmp2, imgTmp3;
	int winWidth = getwidth();
	int winHeight = getheight();
	if (y < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp, 0, -y,
			picture->getwidth(), picture->getheight() + y);
		SetWorkingImage();
		y = 0;
		picture = &imgTmp;
	}
	else if (y >= getheight() || x >= getwidth()) {
		return;
	}
	else if (y + picture->getheight() > winHeight) {
		SetWorkingImage(picture);
		getimage(&imgTmp, x, y, picture->getwidth(), winHeight - y);
		SetWorkingImage();
		picture = &imgTmp;
	}

	if (x < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp2, -x, 0, picture->getwidth() + x, picture->getheight());
		SetWorkingImage();
		x = 0;
		picture = &imgTmp2;
	}

	if (x > winWidth - picture->getwidth()) {
		SetWorkingImage(picture);
		getimage(&imgTmp3, 0, 0, winWidth - x, picture->getheight());
		SetWorkingImage();
		picture = &imgTmp3;
	}


	_putimagePNG(x, y, picture);
}

int getDelay() {//返回时间差
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}
bool fileExist(const char* name) {//文件是否存在
	FILE* fp = fopen(name, "r");
	if (fp == NULL) {
		return false;
	}
	else {
		fclose(fp);
		return true;
	}
}
void CoolImage(IMAGE* src, IMAGE* dst) {//图片变蓝
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* srcBuffer = GetImageBuffer(src);
	DWORD* dstBuffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			static const float coefficient = 0.55f;
			//蓝色：5 50 255  RGB
			BYTE r = (BYTE)(GetBValue(srcBuffer[idx])) * coefficient + 5 * (1 - coefficient);//加权平均，变蓝
			BYTE g = (BYTE)(GetGValue(srcBuffer[idx])) * coefficient + 50 * (1 - coefficient);
			BYTE b = (BYTE)(GetRValue(srcBuffer[idx])) * coefficient + 255 * (1 - coefficient);
			if ((srcBuffer[idx] & 0xFF000000) >> 24) {//如果不透明 >>24是alpha通道
				dstBuffer[idx] = BGR(RGB(r, g, b) | ((DWORD)(BYTE)(255)) << 24);//设置颜色和透明度
			}
		}
	}
}
//返回对应文件夹下 命名规则为1,2,3...的文件总数
int GetFileNum(const char* filePath) {
	int num = 0;
	char name[256];
	while (true) {
		sprintf_s(name, "%s/%d.png", filePath, num + 1);
		if (fileExist(name)) {
			num++;
		}
		else { break; }
	}
	return num;
}
//返回对应文件夹下 命名规则为0,1,2,3...的文件总数
int GetFileNum2(const char* filePath) {
	int num = 0;
	char name[256];
	while (true) {
		sprintf_s(name, "%s/%d.png", filePath, num );
		if (fileExist(name)) {
			num++;
		}
		else { break; }
	}
	return num;
}
//碰撞检测
bool CheckHit(int x, int y, int objX, int objy, int objW, int objH) {
	return x > objX && x<objX + objW && y>objy && y < objy + objH;
}
bool CheckHitX(int x, int objX, int objW) {
	return x > objX && x < objX + objW;
}
//受击动画
void SketchImage(IMAGE* src, IMAGE* dst) {
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* srcBuffer = GetImageBuffer(src);
	DWORD* dstBuffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			if ((srcBuffer[idx] & 0xFF000000) >> 24) {//变白
				dstBuffer[idx] = BGR(RGB(255, 255, 255) | ((DWORD)(BYTE)(255)) << 24);
			}
		}
	}
}