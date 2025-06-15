.set LOCALID_POLICE, 12

ViridianCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_OnTransition
	.byte 0

ViridianCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VIRIDIAN_CITY
	end

ViridianCity_Boy::
	msgbox ViridianCity_Text_ThesePokeballsInYourWaist, MSGBOX_NPC
	end

ViridianCity_Kid::
	lock
	faceplayer
	msgbox ViridianCity_Text_YouFromTeamRocket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_Kid_AnsweredNo
	msgbox ViridianCity_Text_YouIsCool, MSGBOX_NPC
	release
	end

ViridianCity_Kid_AnsweredNo::
	msgbox ViridianCity_Text_OkayYouNoCool, MSGBOX_NPC
	release 
	end

ViridianCity_OldMan::
	msgbox ViridianCity_Text_DoNotBotherUs, MSGBOX_NPC
	end

ViridianCity_OldWoman::
	msgbox ViridianCity_Text_PassingThroughViridianForest, MSGBOX_AUTOCLOSE
	end

ViridianCity_Scientist::
	msgbox ViridianCity_Text_ThisPeakLooksSoStrange, MSGBOX_NPC
	end

ViridianCity_RocketGrunt1::
	msgbox ViridianCity_Text_ThisPathLeads, MSGBOX_NPC
	end

ViridianCity_RocketGrunt2::
	msgbox ViridianCity_Text_ThisBaseHas, MSGBOX_NPC
	end

ViridianCity_Police::
	lockall
	faceplayer
	playbgm MUS_ENCOUNTER_POLICE, 0
	msgbox ViridianCity_Text_YouAreTeamRocketMember, MSGBOX_NPC
	trainerbattle_no_intro TRAINER_VIRIDIAN_EXIT_POLICE, ViridianCity_Text_YouAreTough
	msgbox ViridianCity_Text_IHaveBeenDefeated
	closemessage
	applymovement LOCALID_POLICE, ViridianCity_Movement_RunAway
	waitmovement 0
	removeobject LOCALID_POLICE
	checkflag FLAG_HIDE_VIRIDIAN_EXIT_POLICE
	releaseall
	end

ViridianCity_CitySign::
	msgbox ViridianCity_Text_CitySign, MSGBOX_SIGN
	end

ViridianCity_RecruitHelp1::
	msgbox ViridianCity_Text_CatchMonsForEasierBattles, MSGBOX_SIGN
	end

ViridianCity_RecruitHelp2::
	msgbox ViridianCity_Text_MovesLimitedByPP, MSGBOX_SIGN
	end

ViridianCity_DreamEaterTutor::
	goto EventScript_DreamEaterTutor
	end

ViridianCity_Movement_RunAway::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
