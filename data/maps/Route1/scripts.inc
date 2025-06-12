Route1_MapScripts::
	.byte 0

Route1_MartClerk::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POTION_ON_ROUTE_1, Route1_MartClerk_AfterGettingPotion
	msgbox Route1_Text_WorkAtPokeMartTakeSample
	textcolor NPC_TEXT_COLOR_NEUTRAL
	checkitemspace ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	bufferitemname STR_VAR_2, ITEM_POTION
	playfanfare MUS_LEVEL_UP
	message Text_ObtainedTheX
	waitmessage
	waitfanfare
	additem ITEM_POTION
	msgbox Route1_Text_PutPotionAway
	call EventScript_RestorePrevTextColor
	setflag FLAG_GOT_POTION_ON_ROUTE_1
	release
	end

Route1_MartClerk_AfterGettingPotion::
	msgbox Route1_Text_ComeSeeUsIfYouNeedPokeBalls
	release
	end

Route1_Boy::
	msgbox Route1_Text_SomebodySuitedLikeYou, MSGBOX_NPC
	end

Route1_RouteSign::
	msgbox Route1_Text_RouteSign, MSGBOX_SIGN
	end
