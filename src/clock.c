// This is an edited duplicate from Pokémon Emerald (pret/pokeemerald) source file.
// It is used to activate RTC in Fire Red.

#include "global.h"
#include "battle_util.h"
#include "clock.h"
#include "event_data.h"
#include "field_specials.h"
#include "field_day_night.h"
#include "main.h"
#include "rtc.h"

void InitTimeBasedEvents(void)
{
    FlagSet(FLAG_SYS_CLOCK_SET);
    RtcCalcLocalTime();
    gSaveBlock2Ptr->lastBerryTreeUpdate = gLocalTime;
    VarSet(VAR_DAYS, gLocalTime.days);
}

void DoTimeBasedEvents(void)
{
    if (FlagGet(FLAG_SYS_CLOCK_SET) && !UsedPokemonCenterWarp())
    {
        RtcCalcLocalTime();
        UpdatePerDay(&gLocalTime);
        UpdatePerMinute(&gLocalTime);
    }
}

void UpdatePerDay(struct Time *localTime)
{
    u16 *days = GetVarPointer(VAR_DAYS);
    u16 daysSince;

    if (*days != localTime->days && *days <= localTime->days)
    {
        daysSince = localTime->days - *days;
        *days = localTime->days;
        ResetDailyStolenPokemonCount();
    }
}

void UpdatePerMinute(struct Time *localTime)
{
    u8 hours;

    hours = localTime->hours;

    UpdateTimeOfDayByCurrentHour(hours);
    gSaveBlock2Ptr->lastBerryTreeUpdate = *localTime;
}