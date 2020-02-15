#include "ShowEffect.h"
#include "Graphics.h"
#include "Loop.h"
#include "DisplayObject.h"
#include "Pause.h"
#include "Block.h"
#include "Object.h"
#include "ShowBlockField.h"
#include "Frame.h"
#include "HwSprite.h"
#include "Math.h"

typedef struct BlockExplosionData {
	ObjectData* objectTable;
	uint16_t palNum;
	int16_t y;
	int16_t x;
} BlockExplosionData;

static const ObjectData* ObjectTablesBlockExplosions[NUMBLOCKEXPLOSIONTYPES] = {
	// TODO: Give these names based on their colors. They don't actually
	// correspond to block colors, because they're randomly selected.
	&OBJECTTABLES_BLOCKEXPLOSIONS[0 * NUMBLOCKEXPLOSIONS],
	&OBJECTTABLES_BLOCKEXPLOSIONS[1 * NUMBLOCKEXPLOSIONS],
	&OBJECTTABLES_BLOCKEXPLOSIONS[2 * NUMBLOCKEXPLOSIONS],
	&OBJECTTABLES_BLOCKEXPLOSIONS[3 * NUMBLOCKEXPLOSIONS],
	&OBJECTTABLES_BLOCKEXPLOSIONS[4 * NUMBLOCKEXPLOSIONS],
	&OBJECTTABLES_BLOCKEXPLOSIONS[5 * NUMBLOCKEXPLOSIONS],
	&OBJECTTABLES_BLOCKEXPLOSIONS[6 * NUMBLOCKEXPLOSIONS],
	&OBJECTTABLES_BLOCKEXPLOSIONS[7 * NUMBLOCKEXPLOSIONS]
};

static void UpdateEntityFieldBlockExplosion(Entity* entity);

#define frames values[0]

void ShowFieldBlockExplosion(Player* player, int16_t row, int16_t col) {
	Entity* entity;
	if (entity = AllocEntity()) {
		entity->update = UpdateEntityFieldBlockExplosion;
		entity->frames = 0;

		ENTITY_DATA(entity).player = player;

		ENTITY_INST_DATA_PTR(BlockExplosionData, data, entity);
		data->x = player->screenPos[0] + 8 * col - 8 * (player->matrixWidth / 2);
		data->y = player->screenPos[1] - 8 * row - 6;
		data->objectTable = ObjectTablesBlockExplosions[Rand(8u) % 8];
		data->palNum = PalNumTableNormalBlocks[TOBLOCKNUM(MATRIX(player, row, col).block & BLOCK_TYPE)];
	}
}

static void UpdateEntityFieldBlockExplosion(Entity* entity) {
	ENTITY_INST_DATA_PTR(BlockExplosionData, data, entity);
	DisplayObject(&data->objectTable[entity->frames], data->y, data->x, data->palNum + 9u, 115u);

	if (CurrentPauseMode < PAUSEMODE_GAME && ++entity->frames >= 32) {
		FreeEntity(entity);
	}
}

#undef frames

void ShowFireworks(Player* player, int16_t row, int16_t col, uint32_t seed) {
		// TODO
}

void ShowAllClear(Player* player, int16_t row, int16_t col) {
		// TODO
}

typedef struct {
	const ObjectData* objectTables[2];
	uint16_t palNum;
	int16_t screenPositions[2][2];
} struct_0x60174F8;

#define frames values[0]

void _0x60173B4(Player* player, int16_t row, int16_t col) {
	Entity* entity;
	if ((entity = AllocEntity()) != NULL) {
		entity->update = _0x60174F8;
		ENTITY_DATA(entity).player = player;
		entity->frames = 0;

		ENTITY_INST_DATA_PTR(struct_0x60174F8, data, entity);

		data->screenPositions[1][0] = player->screenPos[0] + 8 * (col + 2) - 8 * (player->matrixWidth / 2);
		data->screenPositions[0][0] = player->screenPos[1] - 8 * row + 10;

		data->screenPositions[1][1] = data->screenPositions[1][0] + Rand(10u) - 5;
		data->screenPositions[0][1] = data->screenPositions[0][0] + Rand(10u) - 5;

		const ObjectData** objectTable = data->objectTables;
		for (size_t i = 0; i < 2; i++) {
			*objectTable = ObjectTablesBlockExplosions[Rand(8) % 8];
			data->palNum = PalNumTableNormalBlocks[TOBLOCKNUM(player->activeBlock & BLOCK_TYPE)];
		}
	}
}

void _0x60174F8(Entity* entity) {
	ENTITY_INST_DATA_PTR(struct_0x60174F8, data, entity);

	const ObjectData** objectTable = data->objectTables;
	for (size_t i = 0; i < 2; i++, objectTable++) {
		DisplayObject(objectTable[entity->frames], data->screenPositions[0][i], data->screenPositions[1][i], data->palNum + 9, 115u);
	}

	if (CurrentPauseMode < PAUSEMODE_GAME && ++entity->frames >= 32) {
		FreeEntity(entity);
	}
}

#undef frames

void ShowClear(Player* player, int16_t row) {
		// TODO
}

void ShowSingleRowClear(Player* player, int16_t row) {
	// TODO
}

typedef struct ThrownOutActiveBlockData {
	int16_t y;
	int16_t x;
	Block activeBlock;
	int16_t spread;
	Rotation rotation;
} ThrownOutActiveBlockData;

static void UpdateEntityThrownOutActiveBlock(Entity* entity);
static void DisplayThrownOutActiveBlock(Player* player, int16_t x, int16_t y, int16_t spread, Block block, Rotation rotation);

#define frames values[0]
#define blockVerticalV values[1]

void ShowThrownOutActiveBlock(Player* player) {
	Entity* entity;
	if ((entity = AllocEntity()) != NULL) {
		entity->update = UpdateEntityThrownOutActiveBlock;
		ENTITY_DATA(entity).player = player;
		entity->frames = 1;
		entity->blockVerticalV = -4;
		ENTITY_INST_DATA_PTR(ThrownOutActiveBlockData, data, entity);
		data->x =
			player->screenPos[0] + player->screenOffset[0] +
			player->activePos[0] * 8 - (player->matrixWidth / 2) * 8;
		data->y =
			player->screenPos[1] + player->screenOffset[1] +
			(player->matrixHeight - player->activePos[1] - 2) * 8 - (player->matrixHeight - 2) * 8 -
			6;
		data->activeBlock = player->activeBlock;
		data->rotation = player->activeRotation;
		data->spread = 8;
	}
}

static void UpdateEntityThrownOutActiveBlock(Entity* entity) {
	Player* player = ENTITY_DATA(entity).player;
	ENTITY_INST_DATA_PTR(ThrownOutActiveBlockData, data, entity);

	data->y += entity->blockVerticalV;

	int16_t x;
	if (player->num == PLAYER1) {
		x = data->x - entity->frames;
	}
	else {
		x = data->x + entity->frames;
	}

	if (entity->frames % 5 == 0) {
		data->spread++;
	}

	DisplayThrownOutActiveBlock(player, x, data->y, data->spread, data->activeBlock, data->rotation);

	if (CurrentPauseMode < PAUSEMODE_GAME) {
		if (++entity->frames % 2 != 0) {
			entity->blockVerticalV++;
		}

		if (data->y > VIDEO_WIDTH || entity->frames > TIME(0, 2, 0)) {
			FreeEntity(entity);
		}
	}
}

#undef frames
#undef blockVerticalV

static void DisplayThrownOutActiveBlock(Player* player, int16_t x, int16_t y, int16_t spread, Block activeBlock, Rotation rotation) {
	int16_t squareY = y, squareX = x;
	if (activeBlock & BLOCK_BIG) {
		squareY++;
		squareX -= 2;
	}

	// Select the brightness of blocks first.
	int16_t palNum = player->lockFrames % 6;
	if (player->lockFrames % 6 > 0) {
		palNum++;
	}
	if (palNum > 0) {
		if (palNum >= 4) {
			palNum = 4;
		}
	}
	else {
		palNum = 0;
	}
	palNum += 4;

	ObjectData* blockObject;
	if (activeBlock & BLOCK_HARD) {
		blockObject = OBJECT_HARDBLOCK;
	}
	else if (activeBlock & BLOCK_ITEM) {
		blockObject = &OBJECTTABLE_ITEMBLOCKS[player->activeBlockItemType - 1];
	}
	else {
		blockObject = &OBJECTTABLE_NORMALBLOCKS[0];
	}

	// Select the starting palette number, adding it to the brightness selected
	// earlier.
	uint16_t startPalNum;
	if (activeBlock & BLOCK_ITEM) {
		startPalNum = PalNumTableNormalBlocks[player->activeBlockItemType - 1];
	}
	else if (activeBlock & BLOCK_ROLLROLL) {
		startPalNum = 48u;
	}
	else if (activeBlock & BLOCK_HARD) {
		startPalNum = 128u;
	}
	else if (activeBlock & BLOCK_TRANSFORM) {
		startPalNum = PalNumTableNormalBlocks[Rand(7u)];
	}
	else {
		startPalNum = PalNumTableNormalBlocks[(activeBlock & BLOCK_TYPE) - BLOCKTYPE_I];
	}
	palNum += startPalNum;

	int16_t size;
	SpriteScale scale;
	if (activeBlock & BLOCK_BIG) {
		size = 2;
		scale = SPRITESCALE(0x40);
	}
	else {
		size = 1;
		scale = UNSCALED;
	}

	BlockDefSquare* blockDef = BLOCKDEF(activeBlock & BLOCK_TYPE);
	for (int16_t row = 0, pixelSpread = spread * size; row < 4; row++, squareY += pixelSpread, blockDef += 16u) {
		BlockDefSquare* blockDefSquare = BLOCKDEFROW(blockDef, rotation, row);
		for (int16_t col = 0; col < 4; col++, squareX += pixelSpread, blockDefSquare++) {
			if (*blockDefSquare != BLOCKDEFSQUARE_EMPTY) {
				DisplayObjectEx(blockObject, squareY, squareX, palNum, 100u, scale, scale, false);
			}
		}
	}
}
