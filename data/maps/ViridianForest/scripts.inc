.set LOCALID_ROCKET, 14

ViridianForest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianForest_OnTransition
	.byte 0

ViridianForest_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VIRIDIAN_FOREST
	goto_if_eq VAR_STORYLINE_IPA_WARNING, 1, ViridianForest_SetPewterBaseFlag
	end

ViridianForest_SetPewterBaseFlag::
	setflag FLAG_HIDE_BLACK_IN_PEWTER_CITY
	setvar VAR_STORYLINE_IPA_WARNING, 2
	end

ViridianForest_WarnAboutIpa::
	lock
	faceplayer
	msgbox ViridianForest_Text_IpaAgentsAreEverywhere
	closemessage
	trainerbattle_no_intro TRAINER_VIRIDIAN_FOREST_IPA_1, ViridianForest_Text_IpaAgentsAreEverywhere
	setvar VAR_STORYLINE_IPA_WARNING, 3
	setflag FLAG_HIDE_VIRIDIAN_FOREST_ROCKET_GRUNT
	fadescreen 0
	removeobject LOCALID_ROCKET
	release
	end

ViridianForest_Youngster::
	msgbox ViridianForest_Text_FriendsItchingToBattle, MSGBOX_NPC
	end

ViridianForest_Boy::
	msgbox ViridianForest_Text_RanOutOfPokeBalls, MSGBOX_NPC
	end

ViridianForest_TrainerTips1::
	msgbox ViridianForest_Text_AvoidGrassyAreasWhenWeak, MSGBOX_SIGN
	end

ViridianForest_TrainerTips2::
	msgbox ViridianForest_Text_UseAntidoteForPoison, MSGBOX_SIGN
	end

ViridianForest_TrainerTips3::
	msgbox ViridianForest_Text_CantCatchOwnedMons, MSGBOX_SIGN
	msgbox ViridianCity_Text_LikeICare
	closemessage
	end

ViridianForest_TrainerTips4::
	msgbox ViridianForest_Text_WeakenMonsBeforeCapture, MSGBOX_SIGN
	end

ViridianForest_ExitSign::
	msgbox ViridianForest_Text_LeavingViridianForest, MSGBOX_SIGN
	end

ViridianForest_Peter::
	trainerbattle_single TRAINER_BUG_CATCHER_PETER, ViridianForest_Text_RickIntro, ViridianForest_Text_RickDefeat
	msgbox ViridianForest_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_Murphy::
	trainerbattle_single TRAINER_BUG_CATCHER_MURPHY, ViridianForest_Text_DougIntro, ViridianForest_Text_DougDefeat
	msgbox ViridianForest_Text_DougPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_Walter::
	trainerbattle_single TRAINER_BUG_CATCHER_WALTER, ViridianForest_Text_SammyIntro, ViridianForest_Text_SammyDefeat
	msgbox ViridianForest_Text_SammyPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_Morgan::
	trainerbattle_single TRAINER_BUG_CATCHER_MORGAN, ViridianForest_Text_AnthonyIntro, ViridianForest_Text_AnthonyDefeat
	msgbox ViridianForest_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_Derrick::
	trainerbattle_single TRAINER_BUG_CATCHER_DERRICK, ViridianForest_Text_CharlieIntro, ViridianForest_Text_CharlieDefeat
	msgbox ViridianForest_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end
