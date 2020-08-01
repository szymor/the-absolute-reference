#include "Game/HwData.h"

// TODO: Consider removing this.
ROMDATA void* ROM[0x100000 / sizeof(void*)];

RAMDATA void* WORKRAM[0x100000 / sizeof(void*)];
RAMDATA uint8_t INPUTS[NUMINPUTS];
RAMDATA uint8_t EEPROM[4];
RAMDATA uint8_t SOUNDCTRL[8];
RAMDATA uint32_t GRAPHICSRAM[0x10000 / sizeof(uint32_t)];
RAMDATA Color PALRAM[NUMPALS * NUMPALCOLORS_4BPP];
RAMDATA uint16_t SCALERAM[0x100];
RAMDATA uint8_t VIDEOCTRL;
RAMDATA uint8_t IRQCTRL[4];
RAMDATA uint8_t VIDEOREGS[0x20];
RAMDATA uint32_t GRAPHICSCHECK[0x20000 / sizeof(uint32_t)];

RAMDATA uint8_t _0xFFFFFE10;
RAMDATA uint8_t _0xFFFFFE11;
RAMDATA uint8_t _0xFFFFFE12;
RAMDATA uint8_t _0xFFFFFE12;
RAMDATA uint8_t _0xFFFFFE13;
RAMDATA uint8_t _0xFFFFFE14;
RAMDATA uint8_t _0xFFFFFE15;
RAMDATA uint8_t _0xFFFFFE16;

RAMDATA uint16_t _0xFFFFFE60;
RAMDATA uint16_t _0xFFFFFE66;

RAMDATA uint8_t _0xFFFFFE92;

RAMDATA uint32_t _0xFFFFFFE0;
RAMDATA uint32_t _0xFFFFFFE4;
RAMDATA uint32_t _0xFFFFFFE8;
RAMDATA uint32_t _0xFFFFFFEC;
RAMDATA uint32_t _0xFFFFFFF0;
RAMDATA uint32_t _0xFFFFFFF8;
