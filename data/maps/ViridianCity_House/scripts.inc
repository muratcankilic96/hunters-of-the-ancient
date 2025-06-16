.set LOCALID_MAN, 1
.set LOCALID_GIRL, 2
.set LOCALID_SPEAROW, 3

ViridianCity_House_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_House_OnTransition
	.byte 0

ViridianCity_House_OnTransition::
    goto_if_set FLAG_HIDE_VIRIDIAN_CITY_SPEAROW, ViridianCity_House_RepositionObjects
    end

ViridianCity_House_RepositionObjects::
    setobjectxyperm LOCALID_MAN, 9, 3
    setobjectmovementtype LOCALID_MAN, MOVEMENT_TYPE_WANDER_UP_AND_DOWN 
    setobjectxyperm LOCALID_GIRL, 7, 2
    setobjectmovementtype LOCALID_GIRL, MOVEMENT_TYPE_FACE_UP 
	end

ViridianCity_House_Man::
	goto_if_set FLAG_HIDE_VIRIDIAN_CITY_SPEAROW, ViridianCity_House_Man_AfterBurglary
	msgbox ViridianCity_House_Text_GoAway, MSGBOX_NPC
	end

ViridianCity_House_Man_AfterBurglary::
	msgbox ViridianCity_House_Text_IHateYouAll, MSGBOX_NPC
	end


ViridianCity_House_LittleGirl::
	goto_if_set FLAG_HIDE_VIRIDIAN_CITY_SPEAROW, ViridianCity_House_LittleGirl_AfterBurglary
	msgbox ViridianCity_House_Text_DaddyAreTheyBad, MSGBOX_NPC
	end

ViridianCity_House_LittleGirl_AfterBurglary::
	msgbox ViridianCity_House_Text_Crying, MSGBOX_AUTOCLOSE
	end

ViridianCity_House_Speary::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_SPEAROW, CRY_MODE_NORMAL
	msgbox ViridianCity_House_Text_Speary
	waitmoncry
	msgbox ViridianCity_House_Text_WouldYouLikeToSteal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ViridianCity_House_Speary_StealAttempt
	closemessage
	releaseall
	end

ViridianCity_House_Speary_StealAttempt::
	lockall
	msgbox ViridianCity_House_Text_TriedToStealSpearow, MSGBOX_NPC
	delay 100
	message ViridianCity_House_Text_DoNotTouchHim
	applymovement LOCALID_MAN, ViridianCity_House_Movement_Exclamation
	waitmessage
	trainerbattle_no_intro TRAINER_VIRIDIAN_BIRD_KEEPER, ViridianCity_House_Text_SpearyNo
	delay 50
	givemon SPECIES_SPEAROW, 8
	playfanfare MUS_OBTAIN_KEY_ITEM
	message ViridianCity_House_Text_StoleTheSpearow
	closemessage
	setflag FLAG_HIDE_VIRIDIAN_CITY_SPEAROW
	removeobject LOCALID_SPEAROW
	message ViridianCity_House_Text_DecidedToRunAway
	closemessage
	setflag FLAG_HIDE_VIRIDIAN_CITY_SPEAROW
	warp MAP_VIRIDIAN_CITY, 1
	releaseall
	end

ViridianCity_House_NicknameSign::
	msgbox ViridianCity_House_Text_SpearowNameSpeary, MSGBOX_SIGN
	end

ViridianCity_House_Movement_Exclamation::
	emote_exclamation_mark
	face_down
	walk_in_place_down
	step_end
