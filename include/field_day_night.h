#ifndef GUARD_FIELD_DAY_NIGHT_H
#define GUARD_FIELD_DAY_NIGHT_H

#include "global.h"

#define TIME_OF_DAY_EARLY_MORNING       0
#define TIME_OF_DAY_MORNING             1
#define TIME_OF_DAY_DAY                 2
#define TIME_OF_DAY_EVENING             3
#define TIME_OF_DAY_NIGHT               4

void UpdateTimeOfDay(u8);

#endif // GUARD_FIELD_DAY_NIGHT_H