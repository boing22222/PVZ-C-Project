#include "Resource.h"

IMAGE imgbg[3];// 0  «∞◊ÃÏ»˝––  1  «∞◊ÃÏŒÂ––  2  «“πÕÌŒÂ––
IMAGE imbar;
IMAGE car;
IMAGE imgCardMask;
IMAGE imgCardSmallMask;
IMAGE imageBulletNormal;
IMAGE imageBulletBlast;
IMAGE imgPuffNormal;
IMAGE imgPuffBlast;
IMAGE Shovel_state;
IMAGE menu_scene, button1, button2;
IMAGE fightButton1, fightButton2;
IMAGE selecting_card_bar;
IMAGE card_cao;
IMAGE chuansongdai;
IMAGE trophy;
IMAGE end_of_level;
IMAGE next_level_button;
IMAGE game_card_bar;
IMAGE cards[16];
IMAGE selectCards[16];
IMAGE imgCoolBullet;
IMAGE imgCoolBlast;
IMAGE imgIceTrap;
IMAGE gameFail;
#pragma region ÷≤ŒÔ
std::vector<Atlas>atlas_plant(number_plant);
Atlas nutInjured;
Atlas nutNearDie;
Atlas potatoInit;
Atlas potatoExplode;
Atlas cherryBombBoom;
Atlas chomperAttack;
Atlas chomperDigest;
Atlas puffShroomSleep;
Atlas sunShroomSleep;
Atlas sunShroomBig;
Atlas scaredyShroomSleep;
Atlas scaredyShroomCry;
Atlas iceShroomSleep;
Atlas iceShroomExplode;
Atlas squashAim;
Atlas squashAttack;
Atlas jalapenoBoom;
#pragma endregion

#pragma region Ω© ¨
std::vector<std::vector<Atlas>>atlas_zombie(numberof_zm_type);
#pragma endregion

#pragma region ‘”œÓ
Atlas CoolMask;
Atlas atlasSunShine;
Atlas atlasSunShineSmall;
Atlas atlasSunShineBig;
#pragma endregion


void loadAllImage() {
#pragma region º”‘ÿimage
	loadimage(&imgbg[0], "res/res/bg.jpg");
	loadimage(&imgbg[2], "res/resources/graphics/Items/Background/Background_0.jpg");
	loadimage(&imgbg[1], "res/resources/graphics/Items/Background/Background_1.jpg");
	loadimage(&imbar, "res/res/bar5.png");
	loadimage(&imbar, "res/res/bar5.png");
	loadimage(&gameFail, "res/res/gameFail.png");
	loadimage(&Shovel_state, "res/res/Shovel.png");
	loadimage(&car, "res/resources/graphics/Screen/car.png");
	loadimage(&imgIceTrap, "res/resources/graphics/icetrap.png");
	loadimage(&imgCardMask, "res/resources/graphics/Cards/cardMask.png");
	loadimage(&imgCardSmallMask, "res/resources/graphics/Cards/cardMask.png",50,72);
	//º”‘ÿ◊”µØÕº∆¨
	loadimage(&imageBulletNormal, "res/res/bullets/bullet_normal.png");
	loadimage(&imageBulletBlast, "res/res/bullets/bullet_blast.png");
	loadimage(&imgCoolBullet, "res/res/bullets/Cool.png");
	loadimage(&imgCoolBlast, "res/res/bullets/bullet_blast_bing.png");
	loadimage(&imgPuffNormal, "res/resources/graphics/Bullets/BulletMushRoom/PuffShroom_puff1.png");
	loadimage(&imgPuffBlast, "res/resources/graphics/Bullets/BulletMushRoomExplode/BulletMushRoomExplode_0.png");
	//º”‘ÿ≤Àµ•±≥æ∞
	loadimage(&menu_scene, "res/res/menu.png");
	//º”‘ÿ≤Àµ•∞¥≈•
	loadimage(&button1, "res/res/menu1.png");
	loadimage(&button2, "res/res/menu2.png");
	loadimage(&fightButton1, "res/res/fight_idle.png");
	loadimage(&fightButton1, "res/res/fight_pushed.png");
	//º”‘ÿ—°ø®ø®≤€Õº∆¨
	loadimage(&selecting_card_bar, "res/resources/graphics/Screen/PanelBackground.png");
	//º”‘ÿø®≤€Õº∆¨
	loadimage(&card_cao, "res/res/selectBar.png");
	loadimage(&chuansongdai, "res/resources/graphics/Screen/MoveBackground.png");
	loadimage(&game_card_bar, "res/res/gameBar.png");
	//º”‘ÿΩ±±≠Õº∆¨
	loadimage(&trophy, "res/res/trophy.png");
	//º”‘ÿ §¿˚Õº∆¨
	loadimage(&end_of_level, "res/res/gameWin.png");
	//º”‘ÿ∞¥≈•Õº∆¨
	loadimage(&next_level_button, "res/res/button.png ");
#pragma endregion
	TCHAR path[80];
	int num;
#pragma region Ω© ¨

	for (int i = 0; i < numberof_zm_type; i++) {
		atlas_zombie[i].resize(4);
		sprintf_s(path, "res/res/Zombie/%d/0", i);
		num = GetFileNum(path);
		atlas_zombie[i][0].LoadFromFile(path, num);
		sprintf_s(path, "res/res/Zombie/%d/1", i);
		num = GetFileNum(path);
		atlas_zombie[i][1].LoadFromFile(path, num);
		sprintf_s(path, "res/res/Zombie/%d/2", i);
		num = GetFileNum(path);
		atlas_zombie[i][2].LoadFromFile(path, num);
		sprintf_s(path, "res/resources/graphics/Zombies/%d/3", i);
		num = GetFileNum(path);
		atlas_zombie[i][3].LoadFromFile(path, num);
	}
#pragma endregion

#pragma region ÷≤ŒÔ

	for (int i = 0; i < number_plant; i++) {
		sprintf_s(path, "res/res/zhiwu/%d", i);
		num = GetFileNum(path);
		atlas_plant[i].LoadFromFile(path, num);
	}
	//º·π˚
	sprintf_s(path, "res/resources/graphics/Plants/WallNut/WallNut_cracked1");
	num = GetFileNum2(path);
	nutInjured.LoadFromFile2(path, num);
	sprintf_s(path, "res/resources/graphics/Plants/WallNut/WallNut_cracked2");
	num = GetFileNum2(path);
	nutNearDie.LoadFromFile2(path, num);
	//Õ¡∂π¿◊
	sprintf_s(path, "res/resources/graphics/Plants/PotatoMine/PotatoMineInit");
	num = GetFileNum2(path);
	potatoInit.LoadFromFile2(path, num);
	sprintf_s(path, "res/resources/graphics/Plants/PotatoMine/PotatoMineExplode");
	num = GetFileNum2(path);
	potatoExplode.LoadFromFile2(path, num);
	//”£Ã“’®µØ
	sprintf_s(path, "res/resources/graphics/Plants/CherryBomb/CherryBombBoom");
	num = GetFileNum(path);
	cherryBombBoom.LoadFromFile(path, num);
	//¥Û◊Ïª®
	sprintf_s(path, "res/resources/graphics/Plants/Chomper/ChomperAttack");
	num = GetFileNum2(path);
	chomperAttack.LoadFromFile2(path, num);
	sprintf_s(path, "res/resources/graphics/Plants/Chomper/ChomperDigest");
	num = GetFileNum2(path);
	chomperDigest.LoadFromFile2(path, num);
	//–°≈ÁπΩ
	sprintf_s(path, "res/resources/graphics/Plants/PuffShroom/PuffShroomSleep");
	num = GetFileNum2(path);
	puffShroomSleep.LoadFromFile2(path, num);
	//—Ùπ‚πΩ
	sprintf_s(path, "res/resources/graphics/Plants/SunShroom/SunShroomSleep");
	num = GetFileNum2(path);
	sunShroomSleep.LoadFromFile2(path, num);
	sprintf_s(path, "res/resources/graphics/Plants/SunShroom/SunShroomBig");
	num = GetFileNum2(path);
	sunShroomBig.LoadFromFile2(path, num);
	//µ®–°πΩ
	sprintf_s(path, "res/resources/graphics/Plants/ScaredyShroom/ScaredyShroomSleep");
	num = GetFileNum2(path);
	scaredyShroomSleep.LoadFromFile2(path, num);
	sprintf_s(path, "res/resources/graphics/Plants/ScaredyShroom/ScaredyShroomCry");
	num = GetFileNum2(path);
	scaredyShroomCry.LoadFromFile2(path, num);
	//∫Æ±˘πΩ
	sprintf_s(path, "res/resources/graphics/Plants/IceShroom/IceShroomSleep");
	num = GetFileNum2(path);
	iceShroomSleep.LoadFromFile2(path, num);
	sprintf_s(path, "res/resources/graphics/Plants/IceShroom/IceShroomExplode");
	num = GetFileNum2(path);
	iceShroomExplode.LoadFromFile2(path, num);
	//Ÿ¡πœ
	sprintf_s(path, "res/resources/graphics/Plants/Squash/SquashAim");
	num = GetFileNum2(path);
	squashAim.LoadFromFile2(path, num);
	sprintf_s(path, "res/resources/graphics/Plants/Squash/SquashAttack");
	num = GetFileNum2(path);
	squashAttack.LoadFromFile2(path, num);
	//¿±Ω∑
	sprintf_s(path, "res/resources/graphics/Plants/Jalapeno/JalapenoExplode");
	num = GetFileNum2(path);
	jalapenoBoom.LoadFromFile2(path, num);
#pragma endregion

#pragma region —Ùπ‚
	sprintf_s(path, sizeof(path), "res/res/sunshine");
	num = GetFileNum(path);
	atlasSunShine.LoadFromFile(path, num);

	atlasSunShineSmall.LoadFromFile3(path, num,50,50);
	atlasSunShineBig.LoadFromFile3(path, num, 110, 110);
#pragma endregion

#pragma region ¿‰»¥≤„
	sprintf_s(path, sizeof(path), "res/resources/graphics/cardCoolTime");
	num = GetFileNum2(path);
	CoolMask.LoadFromFile2(path, num);
#pragma endregion

#pragma region ø®∆¨
	for (int i = 0; i < number_plant; i++) {
		TCHAR path[64];
		sprintf_s(path, "res/res/Cards/%d.png", i);
		loadimage(&selectCards[i], path, 50, 72);
		loadimage(&cards[i], path, 60, 85);
	}
#pragma endregion
}