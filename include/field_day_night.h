#ifndef GUARD_FIELD_DAY_NIGHT_H
#define GUARD_FIELD_DAY_NIGHT_H

#include "global.h"

#define TIME_OF_DAY_EARLY_MORNING       0
#define TIME_OF_DAY_MORNING             1
#define TIME_OF_DAY_DAY                 2
#define TIME_OF_DAY_EVENING             3
#define TIME_OF_DAY_NIGHT               4

u8 GetTimeOfDay(void);
void SetTimeOfDay(u8);
void UpdateTimeOfDayByCurrentHour(u8);
void SetObjectEventLightingForTimeOfDay(u16 *);
void SetTilesetLightingForTimeOfDay(u16 *, u16);
void UpdateTilesetPalettesByLighting(u8, u16 *, u16);
void UpdateObjectEventPalettesByLighting(u8, u16 *);
void UpdateOverworldLighting(void);
void UpdateObjectEventLighting(void);
void UpdateTilesetLighting(void);
void UpdateTilesetLighting_ExitingFromQuestLog(void);
void UpdateObjectEventLighting_ExitingFromQuestLog(void);

#endif // GUARD_FIELD_DAY_NIGHT_H