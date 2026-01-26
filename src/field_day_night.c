#include "field_day_night.h"
#include "global.h"
#include "event_data.h"

EWRAM_DATA u8 gTimeOfDay = 0;

void UpdateTimeOfDay(u8 hours) {
    if (hours < 4 || hours >= 20) {
        gTimeOfDay = TIME_OF_DAY_NIGHT;
    } else if (hours >= 4 && hours < 8) {
        gTimeOfDay = TIME_OF_DAY_EARLY_MORNING;
    } else if (hours >= 8 && hours < 12) {
        gTimeOfDay = TIME_OF_DAY_MORNING;
    } else if (hours >= 12 && hours < 16) {
        gTimeOfDay = TIME_OF_DAY_DAY;
    } else {
        gTimeOfDay = TIME_OF_DAY_EVENING;
    }
}
