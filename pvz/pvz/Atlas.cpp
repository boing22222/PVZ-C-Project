#include "Atlas.h"
#include <cstdio>
//加载文件夹下1,2,3...
void Atlas::LoadFromFile(LPCTSTR path, int num) {
    imgList.clear();
    imgList.resize(num);

    TCHAR path_file[256];
    for (int i = 0; i < num; i++) {
        sprintf_s(path_file, "%s/%d.png", path, i + 1);
        loadimage(&imgList[i], path_file);
    }
}
//加载文件夹下0，1,2,3...
void Atlas::LoadFromFile2(LPCTSTR path, int num) {
    imgList.clear();
    imgList.resize(num);

    TCHAR path_file[256];
    for (int i = 0; i < num; i++) {
        sprintf_s(path_file, "%s/%d.png", path, i);
        loadimage(&imgList[i], path_file);
    }
}
//按指定大小加载文件夹下1,2,3...
void Atlas::LoadFromFile3(LPCTSTR path, int num,int x, int y) {
    imgList.clear();
    imgList.resize(num);

    TCHAR path_file[64];
    for (int i = 0; i < num; i++) {
        sprintf_s(path_file, "%s/%d.png", path, i+1);
        loadimage(&imgList[i], path_file,x,y);
    }
}

void Atlas::Clear() {
    imgList.clear();
}

int Atlas::GetSize() {
    return imgList.size();
}

IMAGE* Atlas::GetImage(int idx) {
    if (idx < 0 || idx >= imgList.size()) {
        throw 0;
    }
    return &imgList[idx];
}

void Atlas::AddImage(const IMAGE& img) {
    imgList.push_back(img);
}

Atlas::~Atlas() {

}
