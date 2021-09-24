#pragma once
#ifndef TOOLS
#define TOOLS
#include"MEntityManager.h"
#define self (*this)
enum class MMouseType {
	DRAW_LINE, DRAW_RECTANGLE, DRAW_ELLIPSE, DRAW_TEXT, SELECT
};

enum class MMouseStatus {
	PRESSED, RELEASED
};
MEntityType mouseType2EntityType(MMouseType type);
#endif