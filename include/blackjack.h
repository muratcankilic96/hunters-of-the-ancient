#ifndef GUARD_BLACKJACK_H
#define GUARD_BLACKJACK_H

#include "global.h"
#include "main.h"

// Opens the Blackjack table and returns to savedCallback when the player exits.
void PlayBlackjack(MainCallback savedCallback);

// Safely closes an open Blackjack table. This is also used by the in-game Exit option.
void ExitBlackjack(void);

#endif // GUARD_BLACKJACK_H
