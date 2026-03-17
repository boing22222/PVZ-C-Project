#include "GameScene.h"
#include "AllPlant.h"
#include "AllZombie.h"
#include "Singleton.h"
#include "SelectScene.h"
#include "Trophy.h"
GameScene::GameScene()
{
	sunNumber = 0;
	cur = nullptr;
}

void GameScene::OnEnter() {


	srand(time(nullptr));
	sunNumber = 50;
	hasCreated = 0;
	cardList.clear();

	Atlas::SP atlas = std::make_shared<Atlas>(CoolMask);

	if (!Singleton<SceneManager>::instance()->currentLevel->hasTransmission) {
		cardList.resize(selectNum.size());
		for (int i = 0; i < selectNum.size(); i++) {
			if (selectNum[i] == -1) {
				cardList.resize(i); break;
			}
		}
		for (int i = 0; i < cardList.size(); i++) {
			cardList[i] = new Card();
			cardList[i]->id = selectNum[i];
			cardList[i]->coolTime = coolTimeList[selectNum[i]];
			cardList[i]->isCool = true;
			cardList[i]->cost = costList[selectNum[i]];
			cardList[i]->x = 339 - 112 + i * (cards[selectNum[i]].getwidth() + 5);
			cardList[i]->y = 8;
		}
	}
	else {
		cardList.reserve(8);
	}

	cars.clear();
	cars.resize(5);
	for (int i = 0; i < cars.size(); i++) {
		cars[i] = new Car();
		cars[i]->y = 120 + i * 97;
		cars[i]->x = 70;
		cars[i]->row = i;
		cars[i]->SetImage(&car);
	}
	leftZombie = Singleton<SceneManager>::instance()->currentLevel->zombieNumber;
	sunshines.clear();
	sunshines.reserve(5);
	bullets.clear();
	bullets.reserve(20);
	plants.clear();
	plants = std::vector<std::vector<Object*>>(5, std::vector<Object*>(10, nullptr));
	zombies.clear();
	zombies = std::vector<std::vector<Object*>>(5);
	for (auto& v : zombies) {
		v.reserve(10);
	}
	mciSendString("stop res/music/bg.mp3", 0, 0, 0);
	mciSendString("play res/music/UraniwaNi.mp3 repeat", 0, 0, 0);
	trophy.InitTrophy();
}

void GameScene::Draw() {
	putimage(-112, 0, Singleton<SceneManager>::instance()->currentLevel->background);
	if (Singleton<SceneManager>::instance()->currentLevel->hasTransmission) {
		putimagePNG(250, 0, &chuansongdai);
	}
	else {
		putimage(250 - 112, 0, &game_card_bar);
		char sun[8];
		sprintf_s(sun, sizeof(sun), "%d", sunNumber);
		outtextxy(278 - 112, 69, sun);
	}
	putimagePNG(750, 0, &Shovel_state);



	for (auto& a : cardList) {
		if (a == nullptr)continue;
		a->Draw(a->x, a->y);
	}
	for (auto& a : plants) {
		if (a.empty())continue;
		for (auto& b : a) {
			if (b == nullptr)continue;
			b->Draw();
		}
	}
	for (auto& a : zombies) {
		if (a.empty())continue;
		for (auto& b : a) {
			if (b == nullptr)continue;
			b->Draw();
		}
	}
	if (cur) {
		cur->Draw();
	}
	if (!sunshines.empty()) {
		for (auto& b : sunshines) {
			if (b == nullptr)continue;
			b->Draw();
		}
	}
	if (!bullets.empty()) {
		for (auto& b : bullets) {
			if (b == nullptr)continue;
			b->Draw();
		}
	}
	if (!cars.empty()) {
		for (auto& b : cars) {
			if (b == nullptr)continue;
			b->Draw();
		}
	}
	trophy.drawTrophy();
}

#pragma region Update
void GameScene::Update(int delta) {
	creatObject(delta);

	for (auto& a : plants) {
		for (auto& b : a) {
			if (b == nullptr)continue;
			b->Update(delta);
		}
	}
	for (auto& a : zombies) {
		for (auto& b : a) {
			if (b == nullptr)continue;
			b->Update(delta);
		}
	}
	for (auto& b : bullets) {
		if (b == nullptr)continue;
		b->Update(delta);
	}
	for (auto& b : cars) {
		if (b == nullptr)continue;
		b->Update(delta);
	}
	for (auto& b : sunshines) {
		if (b == nullptr)continue;
		b->Update(delta);
	}
	for (int i = 0; i < cardList.size(); i++) {
		if (cardList[i] == nullptr) {continue; }
		cardList[i]->Update(delta);
		if (Singleton<SceneManager>::instance()->currentLevel->hasTransmission)
		{
			if (cardList[i]->x > 248 + 64 * i)
				cardList[i]->x -= 1;
		}
	}
	processCollide();
	updateMemory();
	if (checkWin()) {
		if(!trophy.isActive)
		trophy.put_trophy();
	}
	trophy.updateTrophy(delta);

}
void GameScene::winMusic() {
	mciSendString("stop res/music/UraniwaNi.mp3 repeat", 0, 0, 0);
	mciSendString("stop res/music/UraniwaNi.mp3", 0, 0, 0);
	mciSendString("play res/music/win.mp3", 0, 0, 0);
}

void GameScene::updateMemory() {//删除不用的物体
	for (Object*& a : sunshines) {
		if (a && !a->used) {
			delete a;
			a = nullptr;
			std::swap(a, sunshines.back());
			sunshines.pop_back();
		}
	}
	for (Object*& a : bullets) {
		if (a && !a->used) {
			delete a;
			a = nullptr;
			std::swap(a, bullets.back());
			bullets.pop_back();
		}
	}
	for (auto& b : zombies) {
		for (Object*& a : b) {
			if (a && !a->used) {
				delete a;
				a = nullptr;
				std::swap(a, b.back());
				b.pop_back();
				leftZombie--;
			}
		}
	}
	for (auto& a : plants) {
		for (Object*& b : a) {
			if (b && !b->used) {
				delete b;
				b = nullptr;
			}
		}
	}
	for (StaticObj*& a : cars) {
		if (a && !a->used) {
			delete a;
			a = nullptr;
		}
	}
}
void GameScene::creatObject(int delta) {
	creatSunShine(delta);
	creatZombie(delta);
	if (Singleton<SceneManager>::instance()->currentLevel->hasTransmission)creatCard(delta);
}
void GameScene::creatSunShine(int delta) {
	static int count = 0;
	count += delta;
	static int fre = 5000;
	if (Singleton<SceneManager>::instance()->currentLevel->isDay
		&& !Singleton<SceneManager>::instance()->currentLevel->hasTransmission)
	{
		if (count <= fre) { return; }
		count = 0;
		fre = Singleton<SceneManager>::instance()->currentLevel->isDay ? 6000 + rand() % 2000 : 10000 + rand() % 2000;
		SunShine* a = new SunShine(SunShine::SunType::Normal);
		sunshines.push_back(a);
	}

}
void GameScene::creatZombie(int delta) {
	if (hasCreated >= Singleton<SceneManager>::instance()->currentLevel->zombieNumber)return;
	static int count = 0;
	count += delta;
	static int fre = 10;
	if (count <= fre) { return; }
	count = 0;
	fre = 8000 + rand() % 5000;
	hasCreated++;
	switch (rand() % numberof_zm_type)
	{
	case 0: {
		auto a = new NormalZombie();
		zombies[a->row].push_back(a);
		break;
	}
	case 1: {
		auto a = new RoadBlockZombie();
		zombies[a->row].push_back(a);
		break;
	}
	case 2: {
		auto a = new BucketZombie();
		zombies[a->row].push_back(a);
		break;
	}
	default:
		break;
	}
}
void GameScene::processCollide() {//处理所有碰撞
	for (auto& a : bullets) {//子弹与僵尸碰撞
		int row = a->row;
		std::vector<Object*>& vec = zombies[row];
		if (vec.empty()) { continue; }
		for (auto& b : vec) {
			a->Collide(b);
		}
	}
	for (int i = 0; i < 5; i++) {//僵尸与植物、植物与僵尸碰撞
		auto& a = zombies[i];
		auto& b = plants[i];
		collideVec(a, b);
		collideVec(b, a);
		for (auto& c : a) {//车与僵尸碰撞
			if (cars[i]) {
				cars[i]->Collide(c);
			}
		}
	}
}
void GameScene::creatCard(int delta) {
	static int count = 0;
	count += delta;
	if (count <= 5000)return;
	count = 0;
	if (cardList.size() == 8)return;
	int max = 0;
	for (int i = 0; i < selectNum.size(); i++) {
		if (selectNum[i] >= 0)max++;
		else break;
	}
	Card* card = new Card();
	card->id = selectNum[rand() % max];
	card->x = 715;
	card->y = 0;
	cardList.push_back(card);
}
bool GameScene::checkWin() {
	return leftZombie == 0;
}
#pragma endregion

#pragma region Input
void GameScene::Input(const ExMessage& msg) {
	switch (msg.message) {
	case WM_KEYDOWN://esc 退出
		if (msg.vkcode == VK_ESCAPE)
			exit(0);
		break;
	case WM_LBUTTONDOWN://左键单独判定
		processLeftButton(msg);
		break;
	case WM_MOUSEMOVE://鼠标移动，改变cur坐标
	{
		if (cur) {
			cur->x = msg.x - 20;
			cur->y = msg.y - 20;
		}
		int x = msg.x;
		int y = msg.y;
		if (x > 144 && y > 77 && y < 591) {
			int row = (y - 77) / 102;
			int col = (x - 144) / 81;
		}
	}
	break;
	case WM_RBUTTONDOWN://右键更新鼠标
		if (cur) {
			delete cur;
			cur = nullptr;
		}
		break;
	case WM_LBUTTONUP:
		break;
	default:
		break;
	}
}
void GameScene::processLeftButton(const ExMessage& msg) {
	static int idx = -1;
	if (trophy.pass_end_signal()) {//点击奖杯，跳转关卡
		if (trophy.isActive &&
			msg.x >= trophy.x && msg.x <= trophy.x + 134 &&
			msg.y >= trophy.y && msg.y <= trophy.y + 166) {//已经到达目标位置
			winSwitch(msg);
			return;
		}
	}

	if (!cur && msg.x > 227 && msg.x < 227 + 64 * selectNum.size() && msg.y < 96 && msg.y>8) {//如果在卡槽

		if (Singleton<SceneManager>::instance()->currentLevel->hasTransmission) {//传送带，idx=第几张卡
			for (int i = 0; i < cardList.size(); i++) {
				if (cardList[i] == nullptr)continue;
				if (msg.x > cardList[i]->x && msg.x < cardList[i]->x + cards[selectNum[i]].getwidth()) {
					idx = i;
					break;
				}
			}
			if ( cardList[idx]->id==-1||idx == -1) {
				return;
			}
			cur = new StaticObj();
			cur->x = msg.x;
			cur->id = cardList[idx]->id;
			cur->y = cur->id == 12 ? msg.y - 150 : msg.y;//倭瓜的贴图有问题，只能特殊对待
			cur->dy = cur->id == 12 ? -150 : 0;
			cur->SetImage(atlas_plant[cur->id].GetImage(0));//给鼠标位置附上图片
		}
		else {//idx=图鉴列表第几个
			idx = (msg.x - (227)) / 64;
			if (selectNum[idx] == -1) {
				return;
			}
			if (sunNumber < costList[selectNum[idx]] || cardList[idx]->isCool) { return; }
			cur = new StaticObj();
			cur->x = msg.x;
			cur->id = selectNum[idx];
			cur->y = cur->id == 12 ? msg.y - 150 : msg.y;//倭瓜的贴图有问题，只能特殊对待
			cur->dy = cur->id == 12 ? -150 : 0;
			cur->SetImage(atlas_plant[selectNum[idx]].GetImage(0));//给鼠标位置附上图片
		}


	}

	else if (msg.x > 750 && msg.x < 750 + 70 && msg.y < 70 && msg.y>10) {//如果在铲子上
		processShovel(msg);
		idx = -1;
	}
	else if (cur) {//cur已经存在
		int x = msg.x;
		int y = msg.y;
		if (x > 144 && y > 77 && y < 591) {
			int row = (y - 77) / 102;
			int col = (x - 144) / 81;
			if ((row == 0 || row == 4) && Singleton<SceneManager>::instance()->currentLevel->rows == 3)return;
			if (cur && (!plants[row][col]) && idx != -1) {//如果不是铲子，植物种下
				if (Singleton<SceneManager>::instance()->currentLevel->hasTransmission) {
					Object* a = creatPlant(cardList[idx]->id);//得到对应植物
					a->y = 77 + row * 102 + a->dy;
					a->x = 144 + col * 81 + a->dx;
					a->row = row;
					a->col = col;
					plants[row][col] = a;
					delete cardList[idx];
					cardList[idx] = nullptr;
					cardList.erase(cardList.begin() + idx);
				}
				else {
					Object* a = creatPlant(cardList[idx]->id);//得到对应植物
					a->y = 77 + row * 102 + a->dy;
					a->x = 144 + col * 81 + a->dx;
					a->row = row;
					a->col = col;
					plants[row][col] = a;
					sunNumber -= costList[cardList[idx]->id];
					cardList[idx]->isCool = true;
				}
				delete cur;
				cur = nullptr;
				idx = -1;
				PlaySound(TEXT("res/music/plant1.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (cur && plants[row][col] && cur->GetName() == "shovel") {//铲子按下
				plants[row][col]->used = false;
				cur = nullptr;
				PlaySound(TEXT("res/music/plant2.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
	}
	else {
		checkSunShine(msg);//收集阳光
	};
}
void GameScene::processShovel(const ExMessage& msg) 
{
	if (cur)delete cur;
	cur = new StaticObj();
	cur->SetImage(&Shovel_state);
	cur->className = "shovel";
	cur->x = msg.x;
	cur->y = msg.y;
}
void GameScene::checkSunShine(const ExMessage& msg) {//检测阳光
	for (auto& a : sunshines) {
		if (!a) { continue; }
		if (CheckHit(msg.x, msg.y, a->x + 5, a->y + 5, 60, 60)) {
			a->Collect();
			sunNumber += a->value;
			PlaySound(TEXT("res/music/sunshine.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
	}
}
void GameScene::winSwitch(const ExMessage& msg) {
	{
		Singleton<SceneManager>::instance()->levelid++;
		if (Singleton<SceneManager>::instance()->levelid < levelList.size()){
			Singleton<SceneManager>::instance()->currentLevel = levelList[Singleton<SceneManager>::instance()->levelid];
			Singleton<SceneManager>::instance()->SwitchTo(SceneManager::SceneType::Select);
			trophy.isActive = false;
		}
		else {
			Singleton<SceneManager>::instance()->SwitchTo(SceneManager::SceneType::End);
			trophy.isActive = false;
		}
	}
}
Object* GameScene::creatPlant(int id) {
	Object* a = nullptr;
	switch (id) {
	case 0:
		a = new PeaShooter();
		break;
	case 1:
		a = new SunFlower();
		break;
	case 2:
		a = new WallNut();
		break;
	case 3:
		a = new PotatoMine();
		break;
	case 4:
		a = new CherryBomb();
		break;
	case 5:
		a = new SnowPea();
		break;
	case 6:
		a = new Chomper();
		break;
	case 7:
		a = new Repeater();
		break;
	case 8:
		a = new PuffShroom();
		break;
	case 9:
		a = new SunShroom();
		break;
	case 10:
		a = new ScaredyShroom();
		break;
	case 11:
		a = new IceShroom();
		break;
	case 12:
		a = new Squash();
		break;
	case 13:
		a = new Spikeweed();
		break;
	case 14:
		a = new ThreePeater();
		break;
	case 15:
		a = new Jalapeno();
		break;
	default:
		break;
	}
	return a;
}
#pragma endregion

void GameScene::OnExit() {
	mciSendString("stop res/music/UraniwaNi.mp3 repeat", 0, 0, 0);
	mciSendString("stop res/music/UraniwaNi.mp3", 0, 0, 0);
	mciSendString("stop res/music/win.mp3", 0, 0, 0);
}

#pragma region tool function
std::vector<Object*>& GameScene::getSunShineVec() {
	return sunshines;
}
std::vector<Object*>& GameScene::getBulletVec() {
	return bullets;
}
std::vector<Object*>& GameScene::getZombies(int row) {
	return zombies[row];
}
void GameScene::collideVec(std::vector<Object*>& v1, std::vector<Object*>& v2) {
	for (auto& a : v1) {
		if (!a) { continue; }
		for (auto& b : v2) {
			if (!b) { continue; }
			a->Collide(b);
		}
	}
}
#pragma endregion

GameScene::~GameScene() {

}