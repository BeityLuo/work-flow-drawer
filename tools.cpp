#include "tools.h"
MEntityType mouseType2EntityType(MMouseType type) {
	switch (type) {
	case(MMouseType::DRAW_LINE): return MEntityType::LINE;
	case(MMouseType::DRAW_RECTANGLE): return MEntityType::RECTANGLE;
	case(MMouseType::DRAW_ELLIPSE): return MEntityType::ELLIPSE;
	case(MMouseType::DRAW_TEXT): return MEntityType::TEXT;
	default: return MEntityType::LINE; //为了消除警告，暂时无用
	}
}