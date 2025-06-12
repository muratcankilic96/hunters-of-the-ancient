SecretPath_North_MapScripts::
    .byte 0

SecretPath_North_Grunt::
    lock
    faceplayer
    goto_if_set FLAG_GOT_POKEBALLS_ON_SECRET_PATH, SecretPath_North_Grunt_AfterGivingPokeball
    msgbox SecretPath_North_Text_NoNeedToStealEachTime
    textcolor NPC_TEXT_COLOR_NEUTRAL
	checkitemspace ITEM_POKE_BALL
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	bufferitemname STR_VAR_2, ITEM_POKE_BALL
	playfanfare MUS_LEVEL_UP
	message Text_ObtainedTheX
	waitmessage
	waitfanfare
	additem ITEM_POKE_BALL, 5
    msgbox SecretPath_North_PutPokeballAway
    call EventScript_RestorePrevTextColor
    setflag FLAG_GOT_POKEBALLS_ON_SECRET_PATH
    release
    end

SecretPath_North_Grunt_AfterGivingPokeball::
    msgbox SecretPath_North_Text_PokeballIsConvenient, MSGBOX_NPC
    release
    end
