#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include"Object.h"
#include"StaticObj.h"
#include"Card.h"
#include"Trophy.h"
class GameScene :public Scene {//游戏场景
public:
    GameScene();
    ~GameScene() ;
public:
    void OnEnter() override;
    void Update(int delta) override;
    void Draw() override;
    void Input(const ExMessage& msg) override;
    void OnExit() override;
    std::vector<Object*>& getSunShineVec();//获取阳光池
    std::vector<Object*>& getBulletVec();//获取子弹池
    std::vector<Object*>& getZombies(int row);//获取某行僵尸池
public:
    void processLeftButton(const ExMessage& msg);//处理左键按下
    void processShovel(const ExMessage& msg);
    void checkSunShine(const ExMessage& msg);//收集阳光
    void updateMemory();//内存回收
    void creatObject(int delta);//创建对象
    void creatSunShine(int delta);//创建阳光
    void creatZombie(int delta);//创建僵尸
    void creatCard(int delta);
    Object* creatPlant(int idx);//根据id获取新建的植物
    void processCollide();//碰撞处理
    void collideVec(std::vector<Object*>& v1, std::vector<Object*>& v2);//多次碰撞
    bool checkWin();//是否胜利
    void winSwitch(const ExMessage& msg);//胜利跳转
    void winMusic();
private:
    std::vector<std::vector<Object*>>plants;//植物池
    std::vector<std::vector<Object*>>zombies;//僵尸池
    std::vector<Object*>sunshines;//阳光池
    std::vector<Object*>bullets;//子弹池
    StaticObj* cur;//鼠标
    int sunNumber;//阳光数
    int leftZombie;//剩余未死亡的僵尸数
    int hasCreated;//已经生成的僵尸数
    std::vector<StaticObj*>cars;//推车
    Trophy trophy;//奖杯
};
