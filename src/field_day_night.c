#include "field_day_night.h"
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "overworld.h"
#include "blend_palette.h"
#include "palette.h"

#include "event_data.h" //DEBUG

EWRAM_DATA u8 gTimeOfDay = 0;

static u16 const sLightingPaletteBlends[] = {
    RGB(30, 10, 2),
    RGB(30, 30, 0),
    RGB(0, 0, 0),
    RGB(0, 0, 0),
    RGB(0, 0, -8)
};

static u8 const sLightingTilesetPaletteCoeffs[] = { 4, 2, 0, 8, 8 };
static u8 const sLightingObjEventPaletteCoeffs[] = { 2, 1, 0, 4, 4 };

static const u8 primaryTilesetId = BG_PLTT_ID(0) + 1;
static const u8 secondaryTilesetId = BG_PLTT_ID(NUM_PALS_IN_PRIMARY) + 1;
static const u8 primaryTilesetSize = (NUM_PALS_IN_PRIMARY * PLTT_SIZE_4BPP - 2) >> 1;
static const u8 secondaryTilesetSize = ((NUM_PALS_TOTAL - NUM_PALS_IN_PRIMARY) * PLTT_SIZE_4BPP - 2) >> 1;

u8 GetTimeOfDay(void) {
    return gTimeOfDay;
}

void SetTimeOfDay(u8 timeOfDay) {
    gTimeOfDay = timeOfDay;
}

void UpdateTimeOfDayByCurrentHour(u8 hours) {
    if (hours < 6) {
        SetTimeOfDay(TIME_OF_DAY_NIGHT);
    } else if (hours >= 6 && hours < 8) {
        SetTimeOfDay(TIME_OF_DAY_EARLY_MORNING);
    } else if (hours >= 8 && hours < 12) {
        SetTimeOfDay(TIME_OF_DAY_MORNING);
    } else if (hours >= 12 && hours < 18) {
        SetTimeOfDay(TIME_OF_DAY_DAY);
    } else {
        SetTimeOfDay(TIME_OF_DAY_EVENING);
    }
}

void UpdateTilesetPalettesByLighting(u8 timeOfDay, u16 *palette, u16 count)
{
    BlendPalettesAt(palette, sLightingPaletteBlends[timeOfDay], sLightingTilesetPaletteCoeffs[timeOfDay], count);
}

void UpdateObjectEventPalettesByLighting(u8 timeOfDay, u16 *buffer)
{
    BlendPalettesAt(&(buffer[OBJ_PLTT_ID(0)]), sLightingPaletteBlends[timeOfDay], sLightingObjEventPaletteCoeffs[timeOfDay], 1 * 16);
    BlendPalettesAt(&(buffer[OBJ_PLTT_ID(2)]), sLightingPaletteBlends[timeOfDay], sLightingObjEventPaletteCoeffs[timeOfDay], 4 * 16);
    BlendPalettesAt(&(buffer[OBJ_PLTT_ID(10)]), sLightingPaletteBlends[timeOfDay], sLightingObjEventPaletteCoeffs[timeOfDay], 1 * 16);
}

void SetTilesetLightingForTimeOfDay(u16 *palette, u16 count)
{
    u8 timeOfDay = GetTimeOfDay();
    bool8 isOutdoors = IsMapTypeOutdoors(gMapHeader.mapType);

    if (isOutdoors) UpdateTilesetPalettesByLighting(timeOfDay, palette, count);
}

void SetObjectEventLightingForTimeOfDay(u16 *buffer) {
    u8 timeOfDay = GetTimeOfDay();
    bool8 isOutdoors = IsMapTypeOutdoors(gMapHeader.mapType);

    if (isOutdoors) UpdateObjectEventPalettesByLighting(timeOfDay, buffer);
}

void UpdateOverworldLighting(void) {
    LoadMapTilesetPalettes(gMapHeader.mapLayout);
    InitObjectEventPalettes(0);
    UpdateObjectEventLighting();
    UpdateTilesetLighting();
    CopyPrimaryTilesetToVram(gMapHeader.mapLayout);
    CopySecondaryTilesetToVram(gMapHeader.mapLayout);
}

void UpdateObjectEventLighting(void) {
    SetObjectEventLightingForTimeOfDay(gPlttBufferFaded);
    SetObjectEventLightingForTimeOfDay(gPlttBufferUnfaded);
}

void UpdateTilesetLighting(void) {
    SetTilesetLightingForTimeOfDay(&gPlttBufferFaded[primaryTilesetId], primaryTilesetSize);
    SetTilesetLightingForTimeOfDay(&gPlttBufferFaded[secondaryTilesetId], secondaryTilesetSize);
}

void UpdateTilesetLighting_ExitingFromQuestLog(void) {
    SetTilesetLightingForTimeOfDay(&gPlttBufferUnfaded[primaryTilesetId], primaryTilesetSize);
    SetTilesetLightingForTimeOfDay(&gPlttBufferUnfaded[secondaryTilesetId], secondaryTilesetSize);
}

void UpdateObjectEventLighting_ExitingFromQuestLog(void) {
    SetObjectEventLightingForTimeOfDay(gPlttBufferUnfaded);
}
