--- INTRODUCTION ---

Make a Blackjack game in Pokémon FireRed style. It will have its own UI, like the other Rocket Corner games.
Generate the code in blackjack.c and blackjack.h files.

There will be cards: The image file is in \graphics\blackjack\card.png. For each card write a number and suit on top of it.

Examples:
8 of Clubs = C8
3 of Hearts = H3
Ace of Spades = AS
Queen for Diamonds = QD

The menu should be accessible and exitable with the execution of a function.

--- GAME RULES ---

The Pack
52 cards, no jokers

In casinos, multiple decks are often shuffled together and dealt from a dealing shoe.

Object of the Game
To beat the dealer, getting as close to 21 without going over.

Card Values/scoring
Face Cards = 10

Ace = 1 or 11

Number Cards = Pip Value

Setup
Each player places an initial bet before cards are dealt.

Players receive two cards face-up.

The dealer receives one card face-up and one face-down (the “hole” card).

Players Turn
EVALUATE YOUR HAND

Add your two card values together

CHOOSE YOUR ACTION

Hit: Take another card to add to your total

Stand/Stay: Keep your current total. End your turn.

Double Down: Double your bet, take one final card, then stand.

Split: If you have a pair, split into two hands by placing a second bet equal to your first.

Dealer's Turn
Dealer reveals the hole card.

Dealer must hit until reaching 17 or higher.

If the dealer busts (goes over 21), all remaining players win.

PAYOUTS

Win: Paid 1:1.

Blackjack (Ace + 10-value card): Paid 3:2.

Push (tie): Your bet is returned.

Lose: Dealer collects your bet.