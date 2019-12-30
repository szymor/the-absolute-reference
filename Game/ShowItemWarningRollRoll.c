#include "ShowItemWarningRollRoll.h"
#include "Graphics.h"
#include "Object.h"
#include "Frame.h"

#define warningFrames values[0]

static void UpdateEntityItemWarningRollRoll(Entity* entity);

void ShowItemWarningRollRoll(Player* player) {
	Entity* entity;
	if ((entity = AllocEntity()) != NULL) {
		entity->update = UpdateEntityItemWarningRollRoll;
		ENTITY_INSTANCE_DATA_PTR(BasicEntityInstanceData, data, entity);
		ENTITY_DATA(entity).player = player;
		entity->warningFrames = 0;
		data->x = 4;
		data->x = player->fieldPos[0] + player->fieldShift[0] - (player->matrixWidth / 2) * 8 + (data->x + 2) * 8;
		data->y = player->fieldPos[1] + player->fieldShift[1] - 96;
		data->objectTable = OBJECTTABLE_ITEMWARNINGROLLROLL;
		data->palNum = 182u;
	}
}

static void UpdateEntityItemWarningRollRoll(Entity* entity) {
	ENTITY_INSTANCE_DATA_PTR(BasicEntityInstanceData, data, entity);
	DisplayObject(&data->objectTable[entity->warningFrames], data->y, data->x, data->palNum, 124u);
	if (CurrentPauseMode < PAUSEMODE_GAME && ++entity->warningFrames >= 64) {
		FreeEntity(entity);
	}
}