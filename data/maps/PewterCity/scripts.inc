PewterCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_OnTransition
	.byte 0

PewterCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_PEWTER_CITY
	end

PewterCity_Rocket_1::
	msgbox PewterCity_Text_WeHaveSecretBases, MSGBOX_NPC
	end

PewterCity_Rocket_2::
	msgbox PewterCity_Text_ThereAreBothersome, MSGBOX_NPC
	end

PewterCity_CitySign::
	msgbox PewterCity_Text_CitySign, MSGBOX_SIGN
	end

PewterCity_GymSign::
	msgbox PewterCity_Text_GymSign, MSGBOX_SIGN
	end

PewterCity_RecruitHelpSign::
	msgbox PewterCity_Text_RecruitHelpEarningExp, MSGBOX_SIGN
	end

PewterCity_MuseumOfScienceSign::
	msgbox PewterCity_Text_MuseumOfScienceSign, MSGBOX_SIGN
	end

PewterCity_TriggerEventFromLeft::
	clearflag FLAG_HIDE_GIOVANNI_IN_REGISTRATION_ROOM
	addobject LOCALID_PEWTER_BLACK
	setobjectxy LOCALID_PEWTER_BLACK, 20, 58
	setvar VAR_TEMP_0, 0
	goto PewterCity_TellPlayerAboutBrock

PewterCity_TriggerEventFromMiddleLeft::
	clearflag FLAG_HIDE_GIOVANNI_IN_REGISTRATION_ROOM
	addobject LOCALID_PEWTER_BLACK
	setobjectxy LOCALID_PEWTER_BLACK, 21, 58
	setvar VAR_TEMP_0, 1
	goto PewterCity_TellPlayerAboutBrock

PewterCity_TriggerEventFromMiddleRight::
	clearflag FLAG_HIDE_GIOVANNI_IN_REGISTRATION_ROOM
	addobject LOCALID_PEWTER_BLACK
	setobjectxy LOCALID_PEWTER_BLACK, 22, 58
	setvar VAR_TEMP_0, 2
	goto PewterCity_TellPlayerAboutBrock

PewterCity_TriggerEventFromRight::
	clearflag FLAG_HIDE_GIOVANNI_IN_REGISTRATION_ROOM
	addobject LOCALID_PEWTER_BLACK
	setobjectxy LOCALID_PEWTER_BLACK, 23, 58
	setvar VAR_TEMP_0, 3
	goto PewterCity_TellPlayerAboutBrock

PewterCity_TellPlayerAboutBrock::
	playbgm MUS_ENCOUNTER_RIVAL, 0
	applymovement LOCALID_PEWTER_BLACK, PewterCity_Movement_GetCloseToPlayer
	waitmovement 0
	msgbox PewterCity_Text_AfterTheRobbery, MSGBOX_NPC
	switch VAR_TEMP_0
	case 0, PewterCity_MoveBlackFromLeft
	case 1, PewterCity_MoveBlackFromMiddleLeft
	case 2, PewterCity_MoveBlackFromMiddleRight
	case 3, PewterCity_MoveBlackFromRight
	end

PewterCity_MoveBlackFromLeft::
	applymovement LOCALID_PEWTER_BLACK, PewterCity_Movement_WalkTowardsPewterBaseFromLeft
	waitmovement 0
	goto PewterCity_FinalizeEvent

PewterCity_MoveBlackFromMiddleLeft::
	applymovement LOCALID_PEWTER_BLACK, PewterCity_Movement_WalkTowardsPewterBaseFromMiddleLeft
	waitmovement 0
	goto PewterCity_FinalizeEvent

PewterCity_MoveBlackFromMiddleRight::
	applymovement LOCALID_PEWTER_BLACK, PewterCity_Movement_WalkTowardsPewterBaseFromMiddleRight
	waitmovement 0
	goto PewterCity_FinalizeEvent

PewterCity_MoveBlackFromRight::
	applymovement LOCALID_PEWTER_BLACK, PewterCity_Movement_WalkTowardsPewterBaseFromRight
	waitmovement 0
	goto PewterCity_FinalizeEvent

PewterCity_FinalizeEvent::
	fadedefaultbgm
	removeobject LOCALID_PEWTER_BLACK
	setvar VAR_STORYLINE_IPA_WARNING, 3
	setflag FLAG_HIDE_GIOVANNI_IN_REGISTRATION_ROOM
	clearflag FLAG_HIDE_BLACK_IN_PEWTER_CITY_BASE
	end

PewterCity_Movement_GetCloseToPlayer::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PewterCity_Movement_WalkTowardsPewterBaseFromLeft::
	walk_right
	walk_down
	walk_down
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	set_invisible
	walk_down
	step_end

PewterCity_Movement_WalkTowardsPewterBaseFromMiddleLeft::
	walk_left
	walk_down
	walk_down
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	set_invisible
	walk_down
	step_end

PewterCity_Movement_WalkTowardsPewterBaseFromMiddleRight::
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	set_invisible
	walk_down
	step_end

PewterCity_Movement_WalkTowardsPewterBaseFromRight::
	walk_left
	walk_down
	walk_down
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	set_invisible
	walk_down
	step_end
