.equ LOCALID_ROCKET_SCIENTIST, 1
.equ LOCALID_BLACK, 2
.equ LOCALID_POKEDEX_BELOW, 4
.equ LOCALID_POKEDEX_ABOVE, 5
.equ LOCALID_ROCKET_NURSE, 6

RecruitBase_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RecruitBase_Entrance_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, RecruitBase_Entrance_OnFrame
    .byte 0

RecruitBase_Entrance_OnTransition::
    goto_if_ge VAR_STORYLINE_LAB_INVASION, 6, RecruitBase_Entrance_RepositionScientist
    end

RecruitBase_Entrance_OnFrame::
	map_script_2 VAR_STORYLINE_LAB_INVASION, 5, RecruitBase_Entrance_GetPokedexFromBlack
	.2byte 0

RecruitBase_Entrance_RepositionScientist::
    setobjectxyperm LOCALID_ROCKET_SCIENTIST, 10, 7
    setobjectmovementtype LOCALID_ROCKET_SCIENTIST, MOVEMENT_TYPE_WANDER_AROUND 
    end

RecruitBase_Entrance_RecruitHelpSign::
    msgbox RecruitBase_Entrance_Text_RecruitHelp, MSGBOX_SIGN
    end

RecruitBase_Entrance_RocketNurse::
    msgbox RecruitBase_Entrance_Text_Medic, MSGBOX_NPC
    end

RecruitBase_Entrance_Scientist::
    goto_if_ge VAR_STORYLINE_LAB_INVASION, 6, RecruitBase_Entrance_Scientist_AfterGettingPokedex
    msgbox RecruitBase_Entrance_BoxesContainSuits, MSGBOX_NPC
    end

RecruitBase_Entrance_Scientist_AfterGettingPokedex::
    msgbox RecruitBase_Entrance_WeGotPokedex, MSGBOX_NPC
    end

RecruitBase_Entrance_Grunt::
    msgbox RecruitBase_Entrance_ThereIsLabNearby, MSGBOX_NPC
    end

RecruitBase_Entrance_GetPokedexFromBlack::
    lockall
    faceplayer
    setflag FLAG_HIDE_POKEDEX_IN_RECRUIT_BASE
    setflag FLAG_SYS_POKEDEX_GET
    playbgm MUS_OAK, 0
    msgbox RecruitBase_Entrance_Text_IToldEverything, MSGBOX_AUTOCLOSE
    applymovement LOCALID_ROCKET_SCIENTIST, RecruitBase_Entrance_Movement_WalkToPokedex
    msgbox RecruitBase_Entrance_Text_HeardYouGotPokemon, MSGBOX_AUTOCLOSE
    applymovement OBJ_EVENT_ID_PLAYER, RecruitBase_Entrance_Movement_AlignFromRight
    applymovement LOCALID_BLACK, Common_Movement_FaceLeft
    waitmovement 0
    msgbox RecruitBase_Entrance_Text_WhatAreThey, MSGBOX_AUTOCLOSE
    msgbox RecruitBase_Entrance_Text_TheyArePokedex, MSGBOX_AUTOCLOSE
    playfanfare MUS_OBTAIN_KEY_ITEM
    removeobject LOCALID_POKEDEX_BELOW
    message RecruitBase_Entrance_Text_PlayerGetsPokedex
    waitmessage
    waitfanfare
    msgbox RecruitBase_Entrance_Text_TheOtherOne, MSGBOX_AUTOCLOSE
    applymovement LOCALID_BLACK, RecruitBase_Entrance_Movement_GetOtherPokedex
    waitmovement 0
    removeobject LOCALID_POKEDEX_ABOVE
    setvar VAR_STORYLINE_ALLOW_LEAVING_SECRET_PATH, 1
    setvar VAR_STORYLINE_LAB_INVASION, 6
    msgbox RecruitBase_Entrance_Text_ThankYou, MSGBOX_AUTOCLOSE
    applymovement LOCALID_BLACK, RecruitBase_Entrance_Movement_LeaveRecruitBase
    applymovement OBJ_EVENT_ID_PLAYER RecruitBase_Entrance_Movement_LetHimPass
    waitmovement 0
    applymovement LOCALID_ROCKET_SCIENTIST, RecruitBase_Entrance_Movement_WalkToPlayer
    waitmovement 0
    delay 80
    msgbox RecruitBase_Entrance_Text_IHopeYouComplete, MSGBOX_AUTOCLOSE
    applymovement LOCALID_ROCKET_SCIENTIST, RecruitBase_Entrance_Movement_GoBackToInitialPlace
    waitmovement 0
    fadedefaultbgm
    releaseall
    end

RecruitBase_Entrance_Movement_AlignFromLeft::
	walk_right
    face_up
	step_end

RecruitBase_Entrance_Movement_AlignFromRight::
	walk_left
    face_up
	step_end

RecruitBase_Entrance_Movement_WalkToPokedex::
    walk_left
    walk_left
    walk_left
    walk_left
    step_end

RecruitBase_Entrance_Movement_GetOtherPokedex::
    walk_right
    walk_up
    walk_up
    walk_left
    walk_left
    face_down
    step_end

RecruitBase_Entrance_Movement_LeaveRecruitBase::
    walk_right
    walk_right
    walk_down
    walk_down
    walk_down
    walk_left
    face_down
    set_invisible
    walk_down
    step_end

RecruitBase_Entrance_Movement_LetHimPass::
    walk_left
    face_right
    step_end

RecruitBase_Entrance_Movement_WalkToPlayer::
    walk_down
    walk_down
    walk_left
    step_end

RecruitBase_Entrance_Movement_GoBackToInitialPlace::
    walk_right
    walk_right
    walk_right
    walk_up
    walk_up
    walk_right
    walk_right
    step_end
