#pragma once
#include <vector>
#include <graphics.h>
#include <memory>

class Atlas {
public:
    using SP = std::shared_ptr<Atlas>;
    Atlas() = default;
    ~Atlas();
public:
    void LoadFromFile(LPCTSTR path, int num);
    void LoadFromFile2(LPCTSTR path, int num);
    void LoadFromFile3(LPCTSTR path, int num, int x, int y);
    void Clear();
    int GetSize();
    IMAGE* GetImage(int idx);
    void AddImage(const IMAGE& img);
private:
    std::vector<IMAGE>imgList;
};

