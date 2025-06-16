EventScript_RejectHealing::
	msgbox Text_RejectHealing, MSGBOX_NPC
	end

EventScript_PkmnCenterNurse::
	goto_if_questlog EventScript_ReleaseEnd
	message Text_WelcomeWantToHealPkmn
	waitmessage
	multichoice 19, 8, MULTICHOICE_YES_NO, FALSE | (TRUE << 1)
	switch VAR_RESULT
	case 0, EventScript_PkmnCenterNurse_HealPkmn
	case 1 EventScript_PkmnCenterNurse_Goodbye
	case SCR_MENU_CANCEL, EventScript_PkmnCenterNurse_Goodbye
	end

EventScript_PkmnCenterNurse_HealPkmn::
	incrementgamestat GAME_STAT_USED_POKECENTER
	message Text_TakeYourPkmnForFewSeconds
	waitmessage
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	special SetUsedPkmnCenterQuestLogEvent
	goto EventScript_PkmnCenterNurse_ReturnPkmn
	end

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	return

EventScript_PkmnCenterNurse_ReturnPkmn::
	message Text_RestoredPkmnToFullHealth
	waitmessage
	applymovement VAR_LAST_TALKED, Movement_Bow
	waitmovement 0
	msgbox Text_WeHopeToSeeYouAgain
	closemessage
	return

EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom::
	goto_if_set FLAG_SYS_INFORMED_OF_LOCAL_WIRELESS_PLAYER, EventScript_PkmnCenterNurse_ReturnPkmn
	msgbox Text_RestoredPkmnToFullHealth
	setflag FLAG_SYS_INFORMED_OF_LOCAL_WIRELESS_PLAYER
	message Text_PlayerIsPlayingRightNowGoForIt
	waitmessage
	applymovement VAR_LAST_TALKED, Movement_Bow
	waitmovement 0
	msgbox Text_WeHopeToSeeYouAgain
	closemessage
	return

EventScript_PkmnCenterNurse_Goodbye::
	msgbox Text_WeHopeToSeeYouAgain
	closemessage
	return

Movement_Bow::
	nurse_bow
	delay_4
	step_end
