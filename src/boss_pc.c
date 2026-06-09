#include "global.h"
#include "event_data.h"
#include "pokedex.h"
#include "random.h"
#include "boss_pc.h"
#include "field_message_box.h"

static const u16 sForbiddenPokemon[] =
{
    SPECIES_BULBASAUR,
    SPECIES_IVYSAUR,
    SPECIES_VENUSAUR,
    SPECIES_CHARMANDER,
    SPECIES_CHARMELEON,
    SPECIES_CHARIZARD,
    SPECIES_SQUIRTLE,
    SPECIES_WARTORTLE,
    SPECIES_BLASTOISE,
    SPECIES_CHIKORITA,
    SPECIES_BAYLEEF,
    SPECIES_MEGANIUM,
    SPECIES_CYNDAQUIL,
    SPECIES_QUILAVA,
    SPECIES_TYPHLOSION,
    SPECIES_TOTODILE,
    SPECIES_CROCONAW,
    SPECIES_FERALIGATR,
    SPECIES_TREECKO,
    SPECIES_GROVYLE,
    SPECIES_SCEPTILE,
    SPECIES_TORCHIC,
    SPECIES_COMBUSKEN,
    SPECIES_BLAZIKEN,
    SPECIES_MUDKIP,
    SPECIES_MARSHTOMP,
    SPECIES_SWAMPERT,
    SPECIES_ARTICUNO,
    SPECIES_ZAPDOS,
    SPECIES_MOLTRES,
    SPECIES_MEWTWO,
    SPECIES_MEW,
    SPECIES_LUGIA,
    SPECIES_HO_OH,
    SPECIES_RAIKOU,
    SPECIES_ENTEI,
    SPECIES_SUICUNE,
    SPECIES_CELEBI,
    SPECIES_REGIROCK,
    SPECIES_REGICE,
    SPECIES_REGISTEEL,
    SPECIES_LATIAS,
    SPECIES_LATIOS,
    SPECIES_KYOGRE,
    SPECIES_GROUDON,
    SPECIES_RAYQUAZA,
    SPECIES_JIRACHI,
    SPECIES_DEOXYS,
};

static bool8 IsForbiddenPokemon(u16 species)
{
    int i;
    for (i = 0; i < ARRAY_COUNT(sForbiddenPokemon); i++)
    {
        if (species == sForbiddenPokemon[i])
            return TRUE;
    }
    return FALSE;
}

static bool8 IsInvalidPokemon(u16 species)
{
    return (species >= SPECIES_OLD_UNOWN_B && species <= SPECIES_OLD_UNOWN_Z) || species == SPECIES_EGG;
}

static u16 ShuffleNewPokemon(void)
{
    u16 randomSpeciesId;
    do 
    {
        if (!IsNationalPokedexEnabled())
        {
            randomSpeciesId = (Random() % KANTO_SPECIES_END) + 1;
        }
        else
        {
            randomSpeciesId = (Random() % NUM_SPECIES) + 1;
        }
    }
    while (IsForbiddenPokemon(randomSpeciesId) || IsInvalidPokemon(randomSpeciesId));
    return randomSpeciesId;
}

void ResetTransferRequest(void)
{
    gSaveBlock1Ptr->bossTransferRequestPokemon = ShuffleNewPokemon();
}

u16 GetRequestedPokemonForTransfer(void)
{
    return gSaveBlock1Ptr->bossTransferRequestPokemon;
}

u16 GetPokedexCount(void)
{
    if (gSpecialVar_0x8004 == 0)
    {
        gSpecialVar_0x8005 = GetKantoPokedexCount(0);
        gSpecialVar_0x8006 = GetKantoPokedexCount(1);
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(0);
        gSpecialVar_0x8006 = GetNationalPokedexCount(1);
    }
    return IsNationalPokedexEnabled();
}
