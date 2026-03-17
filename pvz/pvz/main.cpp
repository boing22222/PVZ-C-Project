#include "main.h"
Scene* gameSence=nullptr ;
Scene* menuSence = nullptr;
Scene* selectSence = nullptr;
Scene* endScene = nullptr;
Scene* failScene = nullptr;
void init() {//初始化
    initgraph(WIN_WIDTH, WIN_HEIGHT);
    LOGFONT f;
    gettextstyle(&f);
    strcpy(f.lfFaceName, "Segoe UI Black");
    f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿
    f.lfHeight = 25;
    f.lfWidth = 10;
    settextstyle(&f);
    setbkmode(TRANSPARENT);
    setcolor(BLACK);
    loadAllImage();
    gameSence = Singleton<GameScene>::instance();
    menuSence = Singleton<MenuScene>::instance();
    selectSence = Singleton<SelectScene>::instance();
    endScene = Singleton<EndScene>::instance();
    failScene = Singleton<FailScene>::instance();
}
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    init();

    SceneManager* sceneManager = Singleton<SceneManager>::instance();
    ExMessage msg;
    sceneManager->SetCurrentState(menuSence);

    BeginBatchDraw();//双缓冲

    while (true) {
        DWORD frame_start_time = GetTickCount();//控制帧率
        //输入
        while (peekmessage(&msg)) {
            sceneManager->Input(msg);
        }

        static DWORD last_tick_time = GetTickCount();//根据帧间隔更新
        DWORD current_tick_time = GetTickCount();
        DWORD delta_tick = current_tick_time - last_tick_time;
        sceneManager->Update(delta_tick);
        last_tick_time = current_tick_time;
        //画图
        cleardevice();
        sceneManager->Draw();
        FlushBatchDraw();

        DWORD frame_end_time = GetTickCount();//控制帧率
        DWORD frame_delta_time = frame_end_time - frame_start_time;

        if (frame_delta_time < 1000 / FPS) {
            Sleep(1000 / FPS - frame_delta_time);
        }
    }
    EndBatchDraw();
}