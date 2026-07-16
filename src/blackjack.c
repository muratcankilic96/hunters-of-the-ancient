#include "global.h"
#include "gflib.h"
#include "blackjack.h"
#include "coins.h"
#include "menu.h"
#include "random.h"
#include "task.h"
#include "text_window.h"

#define BLACKJACK_NUM_SUITS             4
#define BLACKJACK_NUM_RANKS             13
#define BLACKJACK_DECK_SIZE             (BLACKJACK_NUM_SUITS * BLACKJACK_NUM_RANKS)
#define BLACKJACK_MAX_HANDS             2
#define BLACKJACK_MAX_CARDS_PER_HAND    12
#define BLACKJACK_MAX_CARD_SPRITES      16
#define BLACKJACK_CARD_WIDTH            24
#define BLACKJACK_CARD_HEIGHT           32
#define BLACKJACK_CARD_TILE_BYTES       (BLACKJACK_CARD_WIDTH * BLACKJACK_CARD_HEIGHT / 2)
#define BLACKJACK_CARD_LEFT_TILE_BYTES  (16 * BLACKJACK_CARD_HEIGHT / 2)
#define BLACKJACK_CARD_RIGHT_TILE_BYTES (8 * BLACKJACK_CARD_HEIGHT / 2)
#define BLACKJACK_MAX_CARD_LABEL_CHARS  3
#define BLACKJACK_MAX_CARD_SPRITE_IDS   (BLACKJACK_MAX_CARD_SPRITES * 2)

#define BLACKJACK_CARD_LEFT_TAG_BASE    0x1A00
#define BLACKJACK_CARD_RIGHT_TAG_BASE   0x1A20
#define BLACKJACK_CARD_PALETTE_TAG      0x1A40

enum {
    BLACKJACK_BG_UI,
    BLACKJACK_BG_TABLE = 3,
};

enum {
    BLACKJACK_WIN_HEADER,
    BLACKJACK_WIN_FOOTER,
    BLACKJACK_WIN_COUNT,
};

enum {
    BLACKJACK_RANK_ACE,
    BLACKJACK_RANK_2,
    BLACKJACK_RANK_3,
    BLACKJACK_RANK_4,
    BLACKJACK_RANK_5,
    BLACKJACK_RANK_6,
    BLACKJACK_RANK_7,
    BLACKJACK_RANK_8,
    BLACKJACK_RANK_9,
    BLACKJACK_RANK_10,
    BLACKJACK_RANK_JACK,
    BLACKJACK_RANK_QUEEN,
    BLACKJACK_RANK_KING,
};

enum {
    BLACKJACK_PHASE_BETTING,
    BLACKJACK_PHASE_PLAYING,
    BLACKJACK_PHASE_RESULTS,
    BLACKJACK_PHASE_EXITING,
};

enum {
    BLACKJACK_ACTION_HIT,
    BLACKJACK_ACTION_STAND,
    BLACKJACK_ACTION_DOUBLE,
    BLACKJACK_ACTION_SPLIT,
    BLACKJACK_ACTION_COUNT,
};

enum {
    BLACKJACK_OUTCOME_NONE,
    BLACKJACK_OUTCOME_LOSE,
    BLACKJACK_OUTCOME_PUSH,
    BLACKJACK_OUTCOME_WIN,
    BLACKJACK_OUTCOME_BLACKJACK,
};

struct BlackjackHand
{
    u8 cards[BLACKJACK_MAX_CARDS_PER_HAND];
    u8 cardCount;
    u16 bet;
    u16 payout;
    u8 outcome;
    bool8 finished;
    bool8 doubled;
};

struct BlackjackState
{
    MainCallback savedCallback;
    struct BlackjackHand dealer;
    struct BlackjackHand playerHands[BLACKJACK_MAX_HANDS];
    u8 deck[BLACKJACK_DECK_SIZE];
    u8 deckPosition;
    u8 phase;
    u8 playerHandCount;
    u8 currentHand;
    u8 actionCursor;
    u8 cardSpriteIds[BLACKJACK_MAX_CARD_SPRITE_IDS];
    u8 cardSpriteCount;
    u16 bet;
    u16 tableTilemap[BG_SCREEN_SIZE];
    u16 uiTilemap[BG_SCREEN_SIZE];
    u8 cardTileBuffer[BLACKJACK_CARD_TILE_BYTES];
    u8 glyphTileBuffer[BLACKJACK_MAX_CARD_LABEL_CHARS * 64];
    u8 cardLeftTiles[BLACKJACK_MAX_CARD_SPRITES][BLACKJACK_CARD_LEFT_TILE_BYTES];
    u8 cardRightTiles[BLACKJACK_MAX_CARD_SPRITES][BLACKJACK_CARD_RIGHT_TILE_BYTES];
    struct SpriteTemplate cardLeftTemplates[BLACKJACK_MAX_CARD_SPRITES];
    struct SpriteTemplate cardRightTemplates[BLACKJACK_MAX_CARD_SPRITES];
};

static EWRAM_DATA struct BlackjackState *sBlackjack = NULL;

static void CB2_InitBlackjack(void);
static void CB2_Blackjack(void);
static void VBlankCB_Blackjack(void);
static void Task_Blackjack(u8 taskId);
static void InitBlackjackGraphics(void);
static void FreeBlackjackResources(void);
static void InitCardSpriteSheets(void);
static void RefreshBlackjackScreen(void);
static void DrawBlackjackHeader(void);
static void DrawBlackjackFooter(void);
static void DrawBlackjackCards(void);
static void DestroyCardSprites(void);
static void CreateCardSprites(u8 slot, u8 card, bool8 faceDown, s16 x, s16 y);
static void BuildCardTiles(u8 slot, u8 card, bool8 faceDown);
static void OverlayCardLabel(u8 *cardTiles, const u8 *label);
static void OverlayGlyphTile(u8 *dest, const u8 *src);
static void FormatCardLabel(u8 card, bool8 faceDown, u8 *dest);
static void PrintWindowLines(u8 windowId, const u8 *line0, const u8 *line1, const u8 *line2);
static u8 *AppendNumber(u8 *dest, u16 value);
static u8 *AppendHandValue(u8 *dest, const struct BlackjackHand *hand);
static u8 *AppendHandOutcome(u8 *dest, u8 handNumber, const struct BlackjackHand *hand);
static void StartBetting(void);
static void HandleBettingInput(void);
static void StartRound(void);
static void ResetRound(void);
static void ShuffleDeck(void);
static bool8 DealCard(struct BlackjackHand *hand);
static void HandlePlayerInput(void);
static void MoveActionCursor(s8 direction);
static bool8 IsActionAvailable(u8 action);
static void EnsureActionCursorIsValid(void);
static void PlayerHit(void);
static void PlayerStand(void);
static void PlayerDouble(void);
static void PlayerSplit(void);
static void FinishCurrentHand(void);
static void ResolveInitialBlackjacks(void);
static void ResolveRound(void);
static void SetHandOutcome(struct BlackjackHand *hand, u8 outcome, u16 payout);
static u16 GetHandTotal(const struct BlackjackHand *hand);
static bool8 IsBlackjack(const struct BlackjackHand *hand);
static bool8 IsDealerVisible(void);
static bool8 CanDouble(const struct BlackjackHand *hand);
static bool8 CanSplit(const struct BlackjackHand *hand);
static u16 GetBlackjackPayout(u16 bet);

static const u32 sCardGfx[BLACKJACK_CARD_TILE_BYTES / sizeof(u32)] = INCBIN_U32("graphics/blackjack/card.4bpp");
static const u16 sCardPalette[16] = INCBIN_U16("graphics/blackjack/card.gbapal");

static const u32 sTableTile[] = {
    0x11111111, 0x11111111, 0x11111111, 0x11111111,
    0x11111111, 0x11111111, 0x11111111, 0x11111111,
};

static const u16 sTablePalette[] = {
    RGB(0, 0, 0), RGB(2, 12, 4), RGB(3, 17, 6), RGB(8, 24, 9),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
};

static const struct BgTemplate sBgTemplates[] = {
    {
        .bg = BLACKJACK_BG_UI,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = BLACKJACK_BG_TABLE,
        .charBaseIndex = 3,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sWindowTemplates[] = {
    [BLACKJACK_WIN_HEADER] = {
        .bg = BLACKJACK_BG_UI,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 3,
        .paletteNum = 15,
        .baseBlock = 0x013,
    },
    [BLACKJACK_WIN_FOOTER] = {
        .bg = BLACKJACK_BG_UI,
        .tilemapLeft = 0,
        .tilemapTop = 16,
        .width = 30,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x080,
    },
    DUMMY_WIN_TEMPLATE,
};

static const struct OamData sOamDataCardLeft = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sOamDataCardRight = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sSpriteTemplateCardLeft = {
    .tileTag = TAG_NONE,
    .paletteTag = BLACKJACK_CARD_PALETTE_TAG,
    .oam = &sOamDataCardLeft,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplateCardRight = {
    .tileTag = TAG_NONE,
    .paletteTag = BLACKJACK_CARD_PALETTE_TAG,
    .oam = &sOamDataCardRight,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpritePalette sSpritePaletteCards = {
    .data = sCardPalette,
    .tag = BLACKJACK_CARD_PALETTE_TAG,
};

static const u8 sTextColors[] = {
    TEXT_COLOR_TRANSPARENT,
    TEXT_COLOR_WHITE,
    TEXT_COLOR_DARK_GRAY,
};

static const u8 sTextBust[] = _("BUST");
static const u8 sTextBlackjackCoins[] = _("BLACKJACK  COINS ");
static const u8 sTextBet[] = _("BET: ");
static const u8 sTextPlaceYourBet[] = _("PLACE YOUR BET.");
static const u8 sTextDealer[] = _("DEALER: ");
static const u8 sTextHidden[] = _("HIDDEN");
static const u8 sTextHand1[] = _("HAND 1: ");
static const u8 sTextBetSuffix[] = _("  BET ");
static const u8 sTextH1[] = _("H1 ");
static const u8 sTextH2[] = _("  H2 ");
static const u8 sTextDealExit[] = _("A: DEAL     B: EXIT");
static const u8 sTextBetControls[] = _("UP/DN: 1   L/R: 10");
static const u8 sTextActionControls[] = _("< >: CHOOSE   A: DO");
static const u8 sTextPlayAgainExit[] = _("A: PLAY AGAIN  B: EXIT");
static const u8 sTextLeavingTable[] = _("LEAVING TABLE...");
static const u8 sTextCardBack[] = _("??");
static const u8 sTextBlackjackWin[] = _("BLACKJACK +");
static const u8 sTextWin[] = _("WIN +");
static const u8 sTextPush[] = _("PUSH");
static const u8 sTextLose[] = _("LOSE");

static const u8 sSuitLabels[BLACKJACK_NUM_SUITS][2] = {
    _("C"),
    _("D"),
    _("H"),
    _("S"),
};

static const u8 sRankLabels[BLACKJACK_NUM_RANKS][3] = {
    _("A"),
    _("2"),
    _("3"),
    _("4"),
    _("5"),
    _("6"),
    _("7"),
    _("8"),
    _("9"),
    _("10"),
    _("J"),
    _("Q"),
    _("K"),
};

static const u8 sActionTexts[BLACKJACK_ACTION_COUNT][31] = {
    _(">HIT  STAND  DOUBLE  SPLIT"),
    _(" HIT >STAND  DOUBLE  SPLIT"),
    _(" HIT  STAND >DOUBLE  SPLIT"),
    _(" HIT  STAND  DOUBLE >SPLIT"),
};

void PlayBlackjack(MainCallback savedCallback)
{
    ResetTasks();
    sBlackjack = AllocZeroed(sizeof(*sBlackjack));
    if (sBlackjack == NULL)
    {
        SetMainCallback2(savedCallback);
        return;
    }

    sBlackjack->savedCallback = savedCallback;
    StartBetting();
    SetMainCallback2(CB2_InitBlackjack);
}

void ExitBlackjack(void)
{
    if (sBlackjack != NULL && sBlackjack->phase != BLACKJACK_PHASE_EXITING)
    {
        sBlackjack->phase = BLACKJACK_PHASE_EXITING;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    }
}

static void CB2_InitBlackjack(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();

    switch (gMain.state)
    {
    case 0:
        InitBlackjackGraphics();
        gMain.state++;
        break;
    case 1:
        sBlackjack->phase = BLACKJACK_PHASE_BETTING;
        RefreshBlackjackScreen();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 2:
        if (!gPaletteFade.active)
            SetMainCallback2(CB2_Blackjack);
        break;
    }
}

static void CB2_Blackjack(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_Blackjack(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_Blackjack(u8 taskId)
{
    switch (sBlackjack->phase)
    {
    case BLACKJACK_PHASE_BETTING:
        HandleBettingInput();
        break;
    case BLACKJACK_PHASE_PLAYING:
        HandlePlayerInput();
        break;
    case BLACKJACK_PHASE_RESULTS:
        if (JOY_NEW(A_BUTTON))
        {
            StartBetting();
            RefreshBlackjackScreen();
        }
        else if (JOY_NEW(B_BUTTON))
        {
            ExitBlackjack();
        }
        break;
    case BLACKJACK_PHASE_EXITING:
        if (!gPaletteFade.active)
        {
            FreeBlackjackResources();
            DestroyTask(taskId);
        }
        break;
    }
}

static void InitBlackjackGraphics(void)
{
    SetVBlankCallback(NULL);
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetBgsAndClearDma3BusyFlags(FALSE);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));

    SetBgTilemapBuffer(BLACKJACK_BG_TABLE, sBlackjack->tableTilemap);
    FillBgTilemapBufferRect_Palette0(BLACKJACK_BG_TABLE, 0, 0, 0, 32, 32);
    LoadBgTiles(BLACKJACK_BG_TABLE, sTableTile, sizeof(sTableTile), 0);
    LoadPalette(sTablePalette, BG_PLTT_ID(0), sizeof(sTablePalette));
    CopyBgTilemapBufferToVram(BLACKJACK_BG_TABLE);

    SetBgTilemapBuffer(BLACKJACK_BG_UI, sBlackjack->uiTilemap);
    FillBgTilemapBufferRect_Palette0(BLACKJACK_BG_UI, 0, 0, 0, 32, 32);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    LoadStdWindowGfxOnBg(BLACKJACK_BG_UI, 1, BG_PLTT_ID(15));

    LoadSpritePalette(&sSpritePaletteCards);
    InitCardSpriteSheets();

    ShowBg(BLACKJACK_BG_TABLE);
    ShowBg(BLACKJACK_BG_UI);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_BG3_ON);
    SetVBlankCallback(VBlankCB_Blackjack);
    CreateTask(Task_Blackjack, 0);
}

static void FreeBlackjackResources(void)
{
    MainCallback savedCallback = sBlackjack->savedCallback;

    SetVBlankCallback(NULL);
    ResetSpriteData();
    FreeAllSpritePalettes();
    FreeAllWindowBuffers();
    Free(sBlackjack);
    sBlackjack = NULL;
    SetMainCallback2(savedCallback);
}

static void InitCardSpriteSheets(void)
{
    struct SpriteSheet sheet;
    u8 i;

    for (i = 0; i < BLACKJACK_MAX_CARD_SPRITES; i++)
    {
        sBlackjack->cardLeftTemplates[i] = sSpriteTemplateCardLeft;
        sBlackjack->cardRightTemplates[i] = sSpriteTemplateCardRight;
        sBlackjack->cardLeftTemplates[i].tileTag = BLACKJACK_CARD_LEFT_TAG_BASE + i;
        sBlackjack->cardRightTemplates[i].tileTag = BLACKJACK_CARD_RIGHT_TAG_BASE + i;

        sheet.data = sBlackjack->cardLeftTiles[i];
        sheet.size = BLACKJACK_CARD_LEFT_TILE_BYTES;
        sheet.tag = BLACKJACK_CARD_LEFT_TAG_BASE + i;
        LoadSpriteSheet(&sheet);

        sheet.data = sBlackjack->cardRightTiles[i];
        sheet.size = BLACKJACK_CARD_RIGHT_TILE_BYTES;
        sheet.tag = BLACKJACK_CARD_RIGHT_TAG_BASE + i;
        LoadSpriteSheet(&sheet);
    }
}

static void RefreshBlackjackScreen(void)
{
    DrawBlackjackHeader();
    DrawBlackjackFooter();
    DrawBlackjackCards();
}

static u8 *AppendHandValue(u8 *dest, const struct BlackjackHand *hand)
{
    u16 total = GetHandTotal(hand);

    if (total > 21)
        return StringCopy(dest, sTextBust);
    return AppendNumber(dest, total);
}

static void DrawBlackjackHeader(void)
{
    u8 line0[32];
    u8 line1[32];
    u8 line2[32];
    u8 *ptr;

    ptr = StringCopy(line0, sTextBlackjackCoins);
    AppendNumber(ptr, GetCoins());

    if (sBlackjack->phase == BLACKJACK_PHASE_BETTING)
    {
        ptr = StringCopy(line1, sTextBet);
        AppendNumber(ptr, sBlackjack->bet);
        StringCopy(line2, sTextPlaceYourBet);
    }
    else
    {
        ptr = StringCopy(line1, sTextDealer);
        if (IsDealerVisible())
            AppendHandValue(ptr, &sBlackjack->dealer);
        else
            StringCopy(ptr, sTextHidden);

        if (sBlackjack->playerHandCount == 1)
        {
            ptr = StringCopy(line2, sTextHand1);
            ptr = AppendHandValue(ptr, &sBlackjack->playerHands[0]);
            StringCopy(ptr, sTextBetSuffix);
            AppendNumber(ptr, sBlackjack->playerHands[0].bet);
        }
        else
        {
            ptr = StringCopy(line2, sTextH1);
            ptr = AppendHandValue(ptr, &sBlackjack->playerHands[0]);
            StringCopy(ptr, sTextH2);
            AppendHandValue(ptr, &sBlackjack->playerHands[1]);
        }
    }

    PrintWindowLines(BLACKJACK_WIN_HEADER, line0, line1, line2);
}

static void DrawBlackjackFooter(void)
{
    u8 line0[32];
    u8 line1[32];
    u8 *ptr;

    switch (sBlackjack->phase)
    {
    case BLACKJACK_PHASE_BETTING:
        StringCopy(line0, sTextDealExit);
        StringCopy(line1, sTextBetControls);
        break;
    case BLACKJACK_PHASE_PLAYING:
        StringCopy(line0, sActionTexts[sBlackjack->actionCursor]);
        StringCopy(line1, sTextActionControls);
        break;
    case BLACKJACK_PHASE_RESULTS:
        ptr = AppendHandOutcome(line0, 1, &sBlackjack->playerHands[0]);
        if (sBlackjack->playerHandCount == 2)
            AppendHandOutcome(ptr, 2, &sBlackjack->playerHands[1]);
        StringCopy(line1, sTextPlayAgainExit);
        break;
    default:
        StringCopy(line0, sTextLeavingTable);
        line1[0] = EOS;
        break;
    }

    FillWindowPixelBuffer(BLACKJACK_WIN_FOOTER, PIXEL_FILL(1));
    PutWindowTilemap(BLACKJACK_WIN_FOOTER);
    DrawStdFrameWithCustomTileAndPalette(BLACKJACK_WIN_FOOTER, FALSE, 1, 15);
    AddTextPrinterParameterized4(BLACKJACK_WIN_FOOTER, FONT_SMALL, 8, 8, 0, 0, sTextColors, TEXT_SKIP_DRAW, line0);
    AddTextPrinterParameterized4(BLACKJACK_WIN_FOOTER, FONT_SMALL, 8, 16, 0, 0, sTextColors, TEXT_SKIP_DRAW, line1);
    CopyWindowToVram(BLACKJACK_WIN_FOOTER, COPYWIN_FULL);
}

static void DrawBlackjackCards(void)
{
    u8 i;
    u8 slot = 0;
    u8 cardsToDraw;

    DestroyCardSprites();

    if (sBlackjack->phase == BLACKJACK_PHASE_BETTING)
        return;

    cardsToDraw = sBlackjack->dealer.cardCount;
    if (cardsToDraw > 7)
        cardsToDraw = 7;
    for (i = 0; i < cardsToDraw; i++)
        CreateCardSprites(slot++, sBlackjack->dealer.cards[i], i == 0 && !IsDealerVisible(), 8 + i * 28, 32);

    if (sBlackjack->playerHandCount == 1)
    {
        cardsToDraw = sBlackjack->playerHands[0].cardCount;
        if (cardsToDraw > 8)
            cardsToDraw = 8;
        for (i = 0; i < cardsToDraw; i++)
            CreateCardSprites(slot++, sBlackjack->playerHands[0].cards[i], FALSE, 8 + i * 28, 82);
    }
    else
    {
        cardsToDraw = sBlackjack->playerHands[0].cardCount;
        if (cardsToDraw > 4)
            cardsToDraw = 4;
        for (i = 0; i < cardsToDraw; i++)
            CreateCardSprites(slot++, sBlackjack->playerHands[0].cards[i], FALSE, 4 + i * 15, 82);

        cardsToDraw = sBlackjack->playerHands[1].cardCount;
        if (cardsToDraw > 4)
            cardsToDraw = 4;
        for (i = 0; i < cardsToDraw; i++)
            CreateCardSprites(slot++, sBlackjack->playerHands[1].cards[i], FALSE, 124 + i * 15, 82);
    }
}

static void DestroyCardSprites(void)
{
    u8 i;

    for (i = 0; i < sBlackjack->cardSpriteCount; i++)
        DestroySprite(&gSprites[sBlackjack->cardSpriteIds[i]]);
    sBlackjack->cardSpriteCount = 0;
}

static void CreateCardSprites(u8 slot, u8 card, bool8 faceDown, s16 x, s16 y)
{
    u8 spriteId;
    u16 tileStart;

    if (slot >= BLACKJACK_MAX_CARD_SPRITES)
        return;

    BuildCardTiles(slot, card, faceDown);

    tileStart = GetSpriteTileStartByTag(BLACKJACK_CARD_LEFT_TAG_BASE + slot);
    if (tileStart != TAG_NONE)
        CpuCopy16(sBlackjack->cardLeftTiles[slot], (void *)(OBJ_VRAM0 + tileStart * TILE_SIZE_4BPP), BLACKJACK_CARD_LEFT_TILE_BYTES);
    tileStart = GetSpriteTileStartByTag(BLACKJACK_CARD_RIGHT_TAG_BASE + slot);
    if (tileStart != TAG_NONE)
        CpuCopy16(sBlackjack->cardRightTiles[slot], (void *)(OBJ_VRAM0 + tileStart * TILE_SIZE_4BPP), BLACKJACK_CARD_RIGHT_TILE_BYTES);

    spriteId = CreateSprite(&sBlackjack->cardLeftTemplates[slot], x + 8, y + 16, 0);
    if (spriteId != MAX_SPRITES)
        sBlackjack->cardSpriteIds[sBlackjack->cardSpriteCount++] = spriteId;

    spriteId = CreateSprite(&sBlackjack->cardRightTemplates[slot], x + 20, y + 16, 0);
    if (spriteId != MAX_SPRITES)
        sBlackjack->cardSpriteIds[sBlackjack->cardSpriteCount++] = spriteId;
}

static void BuildCardTiles(u8 slot, u8 card, bool8 faceDown)
{
    u8 label[4];
    u8 row;

    CpuCopy16(sCardGfx, sBlackjack->cardTileBuffer, BLACKJACK_CARD_TILE_BYTES);
    FormatCardLabel(card, faceDown, label);
    OverlayCardLabel(sBlackjack->cardTileBuffer, label);

    for (row = 0; row < 4; row++)
    {
        CpuCopy16(sBlackjack->cardTileBuffer + row * 3 * TILE_SIZE_4BPP,
                  sBlackjack->cardLeftTiles[slot] + row * 2 * TILE_SIZE_4BPP,
                  2 * TILE_SIZE_4BPP);
        CpuCopy16(sBlackjack->cardTileBuffer + (row * 3 + 2) * TILE_SIZE_4BPP,
                  sBlackjack->cardRightTiles[slot] + row * TILE_SIZE_4BPP,
                  TILE_SIZE_4BPP);
    }
}

static void OverlayCardLabel(u8 *cardTiles, const u8 *label)
{
    u8 text[9];
    u8 *ptr = text;
    u8 i;

    *ptr++ = EXT_CTRL_CODE_BEGIN;
    *ptr++ = EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW;
    *ptr++ = TEXT_COLOR_DARK_GRAY;
    *ptr++ = TEXT_COLOR_TRANSPARENT;
    *ptr++ = TEXT_COLOR_DARK_GRAY;
    StringCopy(ptr, label);

    memset(sBlackjack->glyphTileBuffer, 0, sizeof(sBlackjack->glyphTileBuffer));
    RenderTextHandleBold(sBlackjack->glyphTileBuffer, FONT_NORMAL, text, 0, 0, 0, 0, 0);

    for (i = 0; i < StringLength(label); i++)
    {
        OverlayGlyphTile(cardTiles + i * TILE_SIZE_4BPP,
                         sBlackjack->glyphTileBuffer + i * 2 * TILE_SIZE_4BPP);
        OverlayGlyphTile(cardTiles + (3 + i) * TILE_SIZE_4BPP,
                         sBlackjack->glyphTileBuffer + (i * 2 + 1) * TILE_SIZE_4BPP);
    }
}

static void OverlayGlyphTile(u8 *dest, const u8 *src)
{
    u8 i;

    for (i = 0; i < TILE_SIZE_4BPP; i++)
    {
        u8 source = src[i];
        u8 result = dest[i];

        if ((source & 0x0F) != 0)
            result = (result & 0xF0) | (source & 0x0F);
        if ((source & 0xF0) != 0)
            result = (result & 0x0F) | (source & 0xF0);
        dest[i] = result;
    }
}

static void FormatCardLabel(u8 card, bool8 faceDown, u8 *dest)
{
    u8 rank = card / BLACKJACK_NUM_SUITS;
    u8 suit = card % BLACKJACK_NUM_SUITS;
    u8 *ptr;

    if (faceDown)
    {
        StringCopy(dest, sTextCardBack);
    }
    else if (rank == BLACKJACK_RANK_ACE || rank >= BLACKJACK_RANK_JACK)
    {
        ptr = StringCopy(dest, sRankLabels[rank]);
        StringCopy(ptr, sSuitLabels[suit]);
    }
    else
    {
        ptr = StringCopy(dest, sSuitLabels[suit]);
        StringCopy(ptr, sRankLabels[rank]);
    }
}

static void PrintWindowLines(u8 windowId, const u8 *line0, const u8 *line1, const u8 *line2)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    PutWindowTilemap(windowId);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 0, 0, 0, 0, sTextColors, TEXT_SKIP_DRAW, line0);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 0, 8, 0, 0, sTextColors, TEXT_SKIP_DRAW, line1);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 0, 16, 0, 0, sTextColors, TEXT_SKIP_DRAW, line2);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static u8 *AppendNumber(u8 *dest, u16 value)
{
    return ConvertIntToDecimalStringN(dest, value, STR_CONV_MODE_LEFT_ALIGN, 5);
}

static u8 *AppendHandOutcome(u8 *dest, u8 handNumber, const struct BlackjackHand *hand)
{
    u16 profit;

    *dest++ = CHAR_H;
    *dest++ = CHAR_0 + handNumber;
    *dest++ = CHAR_SPACE;
    switch (hand->outcome)
    {
    case BLACKJACK_OUTCOME_BLACKJACK:
        dest = StringCopy(dest, sTextBlackjackWin);
        profit = hand->payout - hand->bet;
        dest = AppendNumber(dest, profit);
        break;
    case BLACKJACK_OUTCOME_WIN:
        dest = StringCopy(dest, sTextWin);
        profit = hand->payout - hand->bet;
        dest = AppendNumber(dest, profit);
        break;
    case BLACKJACK_OUTCOME_PUSH:
        dest = StringCopy(dest, sTextPush);
        break;
    default:
        dest = StringCopy(dest, sTextLose);
        break;
    }

    if (handNumber == 1 && sBlackjack->playerHandCount == 2)
        *dest++ = CHAR_SPACE;
    *dest = EOS;
    return dest;
}

static void StartBetting(void)
{
    ResetRound();
    sBlackjack->phase = BLACKJACK_PHASE_BETTING;
    if (GetCoins() == 0)
        sBlackjack->bet = 0;
    else if (sBlackjack->bet == 0 || sBlackjack->bet > GetCoins())
        sBlackjack->bet = 1;
}

static void HandleBettingInput(void)
{
    u16 coins = GetCoins();

    if (JOY_NEW(B_BUTTON))
    {
        ExitBlackjack();
    }
    else if (JOY_NEW(A_BUTTON) && sBlackjack->bet != 0)
    {
        StartRound();
    }
    else if (JOY_NEW(DPAD_UP) && sBlackjack->bet < coins)
    {
        sBlackjack->bet++;
        RefreshBlackjackScreen();
    }
    else if (JOY_NEW(DPAD_DOWN) && sBlackjack->bet > 1)
    {
        sBlackjack->bet--;
        RefreshBlackjackScreen();
    }
    else if (JOY_NEW(DPAD_RIGHT) && sBlackjack->bet < coins)
    {
        sBlackjack->bet += 10;
        if (sBlackjack->bet > coins)
            sBlackjack->bet = coins;
        RefreshBlackjackScreen();
    }
    else if (JOY_NEW(DPAD_LEFT) && sBlackjack->bet > 1)
    {
        if (sBlackjack->bet > 10)
            sBlackjack->bet -= 10;
        else
            sBlackjack->bet = 1;
        RefreshBlackjackScreen();
    }
}

static void StartRound(void)
{
    struct BlackjackHand *player = &sBlackjack->playerHands[0];

    if (!RemoveCoins(sBlackjack->bet))
    {
        sBlackjack->bet = GetCoins();
        RefreshBlackjackScreen();
        return;
    }

    ResetRound();
    ShuffleDeck();
    sBlackjack->playerHandCount = 1;
    player = &sBlackjack->playerHands[0];
    player->bet = sBlackjack->bet;
    DealCard(player);
    DealCard(&sBlackjack->dealer);
    DealCard(player);
    DealCard(&sBlackjack->dealer);
    sBlackjack->actionCursor = BLACKJACK_ACTION_HIT;

    if (IsBlackjack(player) || IsBlackjack(&sBlackjack->dealer))
        ResolveInitialBlackjacks();
    else
        sBlackjack->phase = BLACKJACK_PHASE_PLAYING;

    RefreshBlackjackScreen();
}

static void ResetRound(void)
{
    memset(&sBlackjack->dealer, 0, sizeof(sBlackjack->dealer));
    memset(sBlackjack->playerHands, 0, sizeof(sBlackjack->playerHands));
    sBlackjack->deckPosition = 0;
    sBlackjack->playerHandCount = 0;
    sBlackjack->currentHand = 0;
    sBlackjack->actionCursor = BLACKJACK_ACTION_HIT;
}

static void ShuffleDeck(void)
{
    u8 i;

    for (i = 0; i < BLACKJACK_DECK_SIZE; i++)
        sBlackjack->deck[i] = i;

    for (i = BLACKJACK_DECK_SIZE - 1; i > 0; i--)
    {
        u8 j = Random() % (i + 1);
        u8 card = sBlackjack->deck[i];
        sBlackjack->deck[i] = sBlackjack->deck[j];
        sBlackjack->deck[j] = card;
    }
}

static bool8 DealCard(struct BlackjackHand *hand)
{
    if (hand->cardCount >= BLACKJACK_MAX_CARDS_PER_HAND || sBlackjack->deckPosition >= BLACKJACK_DECK_SIZE)
        return FALSE;

    hand->cards[hand->cardCount++] = sBlackjack->deck[sBlackjack->deckPosition++];
    return TRUE;
}

static void HandlePlayerInput(void)
{
    if (JOY_NEW(DPAD_LEFT))
    {
        MoveActionCursor(-1);
        RefreshBlackjackScreen();
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        MoveActionCursor(1);
        RefreshBlackjackScreen();
    }
    else if (JOY_NEW(A_BUTTON))
    {
        switch (sBlackjack->actionCursor)
        {
        case BLACKJACK_ACTION_HIT:
            PlayerHit();
            break;
        case BLACKJACK_ACTION_STAND:
            PlayerStand();
            break;
        case BLACKJACK_ACTION_DOUBLE:
            PlayerDouble();
            break;
        case BLACKJACK_ACTION_SPLIT:
            PlayerSplit();
            break;
        }
        RefreshBlackjackScreen();
    }
}

static void MoveActionCursor(s8 direction)
{
    u8 attempts;

    for (attempts = 0; attempts < BLACKJACK_ACTION_COUNT; attempts++)
    {
        if (direction < 0)
        {
            if (sBlackjack->actionCursor == 0)
                sBlackjack->actionCursor = BLACKJACK_ACTION_COUNT - 1;
            else
                sBlackjack->actionCursor--;
        }
        else
        {
            sBlackjack->actionCursor++;
            if (sBlackjack->actionCursor >= BLACKJACK_ACTION_COUNT)
                sBlackjack->actionCursor = 0;
        }

        if (IsActionAvailable(sBlackjack->actionCursor))
            return;
    }
}

static bool8 IsActionAvailable(u8 action)
{
    const struct BlackjackHand *hand = &sBlackjack->playerHands[sBlackjack->currentHand];

    switch (action)
    {
    case BLACKJACK_ACTION_HIT:
    case BLACKJACK_ACTION_STAND:
        return TRUE;
    case BLACKJACK_ACTION_DOUBLE:
        return CanDouble(hand);
    case BLACKJACK_ACTION_SPLIT:
        return CanSplit(hand);
    default:
        return FALSE;
    }
}

static void EnsureActionCursorIsValid(void)
{
    if (!IsActionAvailable(sBlackjack->actionCursor))
        sBlackjack->actionCursor = BLACKJACK_ACTION_HIT;
}

static void PlayerHit(void)
{
    struct BlackjackHand *hand = &sBlackjack->playerHands[sBlackjack->currentHand];

    if (!DealCard(hand) || GetHandTotal(hand) > 21)
        FinishCurrentHand();
    else
        EnsureActionCursorIsValid();
}

static void PlayerStand(void)
{
    FinishCurrentHand();
}

static void PlayerDouble(void)
{
    struct BlackjackHand *hand = &sBlackjack->playerHands[sBlackjack->currentHand];
    u16 additionalBet;

    if (!CanDouble(hand))
        return;

    additionalBet = hand->bet;
    if (!RemoveCoins(additionalBet))
        return;

    hand->bet += additionalBet;
    hand->doubled = TRUE;
    DealCard(hand);
    FinishCurrentHand();
}

static void PlayerSplit(void)
{
    struct BlackjackHand *firstHand = &sBlackjack->playerHands[0];
    struct BlackjackHand *secondHand = &sBlackjack->playerHands[1];

    if (!CanSplit(firstHand) || !RemoveCoins(firstHand->bet))
        return;

    memset(secondHand, 0, sizeof(*secondHand));
    secondHand->cards[0] = firstHand->cards[1];
    secondHand->cardCount = 1;
    secondHand->bet = firstHand->bet;
    firstHand->cardCount = 1;
    sBlackjack->playerHandCount = 2;
    sBlackjack->currentHand = 0;
    DealCard(firstHand);
    DealCard(secondHand);
    EnsureActionCursorIsValid();
}

static void FinishCurrentHand(void)
{
    sBlackjack->playerHands[sBlackjack->currentHand].finished = TRUE;

    while (sBlackjack->currentHand < sBlackjack->playerHandCount
        && sBlackjack->playerHands[sBlackjack->currentHand].finished)
    {
        sBlackjack->currentHand++;
    }

    if (sBlackjack->currentHand >= sBlackjack->playerHandCount)
        ResolveRound();
    else
        EnsureActionCursorIsValid();
}

static void ResolveInitialBlackjacks(void)
{
    struct BlackjackHand *player = &sBlackjack->playerHands[0];
    bool8 playerBlackjack = IsBlackjack(player);
    bool8 dealerBlackjack = IsBlackjack(&sBlackjack->dealer);

    if (playerBlackjack && dealerBlackjack)
        SetHandOutcome(player, BLACKJACK_OUTCOME_PUSH, player->bet);
    else if (playerBlackjack)
        SetHandOutcome(player, BLACKJACK_OUTCOME_BLACKJACK, GetBlackjackPayout(player->bet));
    else
        SetHandOutcome(player, BLACKJACK_OUTCOME_LOSE, 0);

    sBlackjack->phase = BLACKJACK_PHASE_RESULTS;
}

static void ResolveRound(void)
{
    bool8 dealerMustPlay = FALSE;
    u8 i;
    u16 dealerTotal;

    for (i = 0; i < sBlackjack->playerHandCount; i++)
    {
        if (GetHandTotal(&sBlackjack->playerHands[i]) <= 21)
        {
            dealerMustPlay = TRUE;
            break;
        }
    }

    if (dealerMustPlay)
    {
        while (GetHandTotal(&sBlackjack->dealer) < 17)
        {
            if (!DealCard(&sBlackjack->dealer))
                break;
        }
    }

    dealerTotal = GetHandTotal(&sBlackjack->dealer);
    for (i = 0; i < sBlackjack->playerHandCount; i++)
    {
        struct BlackjackHand *hand = &sBlackjack->playerHands[i];
        u16 handTotal = GetHandTotal(hand);

        if (handTotal > 21)
            SetHandOutcome(hand, BLACKJACK_OUTCOME_LOSE, 0);
        else if (dealerTotal > 21 || handTotal > dealerTotal)
            SetHandOutcome(hand, BLACKJACK_OUTCOME_WIN, hand->bet * 2);
        else if (handTotal == dealerTotal)
            SetHandOutcome(hand, BLACKJACK_OUTCOME_PUSH, hand->bet);
        else
            SetHandOutcome(hand, BLACKJACK_OUTCOME_LOSE, 0);
    }

    sBlackjack->phase = BLACKJACK_PHASE_RESULTS;
}

static void SetHandOutcome(struct BlackjackHand *hand, u8 outcome, u16 payout)
{
    hand->outcome = outcome;
    hand->payout = payout;
    if (payout != 0)
        AddCoins(payout);
}

static u16 GetHandTotal(const struct BlackjackHand *hand)
{
    u16 total = 0;
    u8 aces = 0;
    u8 i;

    for (i = 0; i < hand->cardCount; i++)
    {
        u8 rank = hand->cards[i] / BLACKJACK_NUM_SUITS;

        if (rank == BLACKJACK_RANK_ACE)
        {
            total++;
            aces++;
        }
        else if (rank >= BLACKJACK_RANK_10)
        {
            total += 10;
        }
        else
        {
            total += rank + 1;
        }
    }

    if (aces != 0 && total + 10 <= 21)
        total += 10;
    return total;
}

static bool8 IsBlackjack(const struct BlackjackHand *hand)
{
    return hand->cardCount == 2 && GetHandTotal(hand) == 21;
}

static bool8 IsDealerVisible(void)
{
    return sBlackjack->phase == BLACKJACK_PHASE_RESULTS || sBlackjack->phase == BLACKJACK_PHASE_EXITING;
}

static bool8 CanDouble(const struct BlackjackHand *hand)
{
    return hand->cardCount == 2 && !hand->doubled && GetCoins() >= hand->bet;
}

static bool8 CanSplit(const struct BlackjackHand *hand)
{
    if (sBlackjack->playerHandCount != 1 || hand->cardCount != 2 || GetCoins() < hand->bet)
        return FALSE;

    return hand->cards[0] / BLACKJACK_NUM_SUITS == hand->cards[1] / BLACKJACK_NUM_SUITS;
}

static u16 GetBlackjackPayout(u16 bet)
{
    // The returned value includes the original stake plus the 3:2 Blackjack profit.
    return bet + (bet * 3) / 2;
}
