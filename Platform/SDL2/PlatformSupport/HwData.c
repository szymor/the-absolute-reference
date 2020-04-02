#include "Game/HwData.h"

ROMDATA uint8_t ROM[0x100000];
RAMDATA uint8_t WORKRAM[0x100000];
RAMDATA uint8_t INPUTS[NUMINPUTS];
RAMDATA uint8_t EEPROM[4];
RAMDATA uint8_t SOUNDCTRL[8];
RAMDATA uint8_t GRAPHICSRAM[0x10000];
RAMDATA uint8_t PALRAM[NUMPALS * NUMPALCOLORS_4BPP * sizeof(Color)];
RAMDATA uint8_t SCALERAM[0x200];
RAMDATA uint8_t VIDEOCTRL;
volatile uint8_t IRQCTRL[4];
RAMDATA uint8_t VIDEOREGS[0x20];
