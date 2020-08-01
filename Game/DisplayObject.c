#include "DisplayObject.h"
#include "Video.h"
#include "PalNum.h"
#include "HwData.h"
#include "Macros.h"
#include <stdbool.h>

static void AddObjectSprite(const ObjectData* object, int16_t y, int16_t x, uint8_t palNum, uint16_t layer, uint8_t scaleY, uint8_t scaleX, uint8_t etc) {
	OBJECT_SETY(&_0x6061932.tempSprite, y + OBJECT_GETY(object));
	OBJECT_SETX(&_0x6061932.tempSprite, x + OBJECT_GETX(object));

	// flipY, sprPri, h.
	_0x6061932.tempSprite[2] = (_0x6061932.tempSprite[2] & 0x00FF) | ((*object)[2] & 0xFF00);

	// flipX, bgPri = 3u, w.
	_0x6061932.tempSprite[3] = (_0x6061932.tempSprite[3] & 0x00FF) | (((*object)[3] & 0xCF00) | 0x3000);

	OBJECT_SETSCALEY(&_0x6061932.tempSprite, scaleY);
	OBJECT_SETSCALEX(&_0x6061932.tempSprite, scaleX);

	OBJECT_SETPALNUM(&_0x6061932.tempSprite, palNum);

	// bpp, alpha, top three bits of tile.
	_0x6061932.tempSprite[4] = (_0x6061932.tempSprite[4] & 0xFF00) | etc;
	// Bottom 16 bits of tile.
	_0x6061932.tempSprite[5] = (*object)[5];

	for (size_t i = 0; i < lengthof(_0x6061932.tempSprite); i++) {
		Sprites[NumSprites][i] = _0x6061932.tempSprite[i];
	}
	NumSprites++;
}

#define ALPHA_TRANSPARENT 0x40
#define ALPHA_GRAYSCALE 0x10

void DisplayObject(const ObjectData* object, int16_t y, int16_t x, uint8_t palNum, uint16_t layer) {
	uint8_t etc;
	if (palNum == PALNUM_ALPHA) {
		// Field or item bar background; use alpha.
		etc = ALPHA_TRANSPARENT | ((*object)[4] & ~OBJECT_ALPHA);
	}
	else {
		// Opaque; no alpha.
		etc = (*object)[4] & ~OBJECT_ALPHA;
	}

	AllocSpriteLayerNames(layer, OBJECT_GETNUMSPRITES(object));;

	int16_t numSprites = OBJECT_GETNUMSPRITES(object);
	const ObjectData* curData = object;
	if (palNum != 0u) {
		while (numSprites-- != 0) {
			AddObjectSprite(curData++, y, x, palNum, layer, 0x3F, 0x3F, etc);
		}
	}
	else {
		while (numSprites-- != 0) {
			AddObjectSprite(curData++, y, x, OBJECT_GETPALNUM(object), layer, 0x3F, 0x3F, etc);
		}
	}
}

void DisplayObjectEx(const ObjectData* object, int16_t y, int16_t x, uint8_t palNum, uint16_t layer, SpriteScale scaleY, SpriteScale scaleX, bool alpha) {
	if (palNum == 0) {
		palNum = OBJECT_GETPALNUM(object);
	}

	uint8_t etc;
	if (alpha || palNum == PALNUM_ALPHA) {
		// Alpha requested, field background, or item bar background; use alpha.
		etc = ALPHA_TRANSPARENT | ((*object)[4] & ~OBJECT_ALPHA);
	}
	else {
		// Some other type of object. Default to opaque, if the object isn't a next block background.
		etc = (*object)[4] & ~OBJECT_ALPHA;
	}

	if (object == OBJECT_SINGLENEXTBLOCKBG || object == OBJECT_DOUBLESNEXTBLOCKBG) {
		// Use grayscale alpha.
		etc = ALPHA_GRAYSCALE | ((*object)[4] & ~OBJECT_ALPHA);
	}

	AllocSpriteLayerNames(layer, OBJECT_GETNUMSPRITES(object));

	const ObjectData* curData = object;
	for (int16_t numSprites = OBJECT_GETNUMSPRITES(object); numSprites != 0; numSprites--, curData++) {
		AddObjectSprite(curData, y, x, palNum, layer, scaleY, scaleX, etc);
	}
}
