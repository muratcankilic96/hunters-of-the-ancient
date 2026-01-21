// This is an edited duplicate from Pokémon Emerald (pret/pokeemerald) source file.
// It is used to activate RTC in Fire Red.

#ifndef GUARD_CLOCK_H
#define GUARD_CLOCK_H

// TODO: time of day and seconds in a day defines

void UpdatePerDay(struct Time *);
void UpdatePerMinute(struct Time *);
void InitTimeBasedEvents(void);
void DoTimeBasedEvents(void);

#endif // GUARD_CLOCK_H