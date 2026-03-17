#include "Level.h"
Level::Level(bool day,bool trans,IMAGE* bg,int row,int z) {
	isDay = day;
	hasTransmission = trans;
	background = bg;
	rows = row;
	zombieNumber = z;
}