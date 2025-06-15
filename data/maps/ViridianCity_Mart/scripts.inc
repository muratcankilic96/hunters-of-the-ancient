.set LOCALID_CLERK, 1

ViridianCity_Mart_MapScripts::
	.byte 0

ViridianCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message Text_HowMayIServeYou
	waitmessage
	pokemart ViridianCity_Mart_Items
	msgbox Text_SeeYouLater
	release
	end

ViridianCity_Mart_EventScript_Woman::
	msgbox ViridianCity_Mart_Text_DoYouHaveAnAntidote, MSGBOX_AUTOCLOSE
	end

ViridianCity_Mart_EventScript_Man::
	msgbox ViridianCity_Mart_Text_HeyMia, MSGBOX_AUTOCLOSE
	end

	.align 2
ViridianCity_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_NONE
	release
	end
