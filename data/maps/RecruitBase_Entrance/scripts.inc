RecruitBase_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RecruitBase_Entrance_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, RecruitBase_Entrance_OnFrame
    .byte 0

RecruitBase_Entrance_OnTransition::
    goto_if_ge VAR_STORYLINE_LAB_INVASION, 6, RecruitBase_Entrance_RepositionScientist
    end

RecruitBase_Entrance_OnFrame::
	map_script_2 VAR_STORYLINE_LAB_INVASION, 5, RecruitBase_Entrance_CheckWildBattleDefeat
	.2byte 0

RecruitBase_Entrance_RepositionScientist::
    setobjectxyperm LOCALID_RECRUIT_BASE_SCIENTIST, 10, 7
    setobjectmovementtype LOCALID_RECRUIT_BASE_SCIENTIST, MOVEMENT_TYPE_WANDER_AROUND 
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

RecruitBase_Entrance_CheckWildBattleDefeat::
    lockall
    faceplayer
    playbgm MUS_OAK, 0
    goto_if_set FLAG_FAINTED_BEFORE_POKEDEX, RecruitBase_Entrance_TriggerBlackCall
    goto RecruitBase_Entrance_GetPokedexFromBlack
    end

RecruitBase_Entrance_TriggerBlackCall::
    clearflag FLAG_FAINTED_BEFORE_POKEDEX
    applymovement LOCALID_RECRUIT_BASE_ENTRANCE_BLACK, Common_Movement_FaceRight
    waitmovement 0
    applymovement LOCALID_RECRUIT_BASE_ENTRANCE_BLACK, Common_Movement_ExclamationMark
    waitmovement 0
    msgbox RecruitBase_Entrance_Text_AreYouFeelingBetter, MSGBOX_AUTOCLOSE
    applymovement LOCALID_PLAYER, RecruitBase_Entrance_Movement_GoBackToInitialPlace
    waitmovement 0
    applymovement LOCALID_RECRUIT_BASE_ENTRANCE_BLACK, Common_Movement_FaceDown
    waitmovement 0
    goto RecruitBase_Entrance_GetPokedexFromBlack
    end

RecruitBase_Entrance_GetPokedexFromBlack::
    setflag FLAG_HIDE_POKEDEX_IN_RECRUIT_BASE
    setflag FLAG_SYS_POKEDEX_GET
    msgbox RecruitBase_Entrance_Text_IToldEverything, MSGBOX_AUTOCLOSE
    applymovement LOCALID_RECRUIT_BASE_SCIENTIST, RecruitBase_Entrance_Movement_WalkToPokedex
    waitmovement 0
    msgbox RecruitBase_Entrance_Text_HeardYouGotPokemon, MSGBOX_AUTOCLOSE
    applymovement LOCALID_PLAYER, RecruitBase_Entrance_Movement_AlignToRight
    applymovement LOCALID_RECRUIT_BASE_ENTRANCE_BLACK, Common_Movement_FaceLeft
    waitmovement 0
    msgbox RecruitBase_Entrance_Text_WhatAreThey, MSGBOX_AUTOCLOSE
    msgbox RecruitBase_Entrance_Text_TheyArePokedex, MSGBOX_AUTOCLOSE
    playfanfare MUS_OBTAIN_KEY_ITEM
    removeobject LOCALID_POKEDEX_BELOW
    message RecruitBase_Entrance_Text_PlayerGetsPokedex
    waitmessage
    waitfanfare
    msgbox RecruitBase_Entrance_Text_TheOtherOne, MSGBOX_AUTOCLOSE
    applymovement LOCALID_RECRUIT_BASE_ENTRANCE_BLACK, RecruitBase_Entrance_Movement_GetOtherPokedex
    waitmovement 0
    removeobject LOCALID_POKEDEX_ABOVE
    setvar VAR_STORYLINE_ALLOW_LEAVING_SECRET_PATH, 1
    setvar VAR_STORYLINE_LAB_INVASION, 6
    msgbox RecruitBase_Entrance_Text_ThankYou, MSGBOX_AUTOCLOSE
    applymovement LOCALID_RECRUIT_BASE_ENTRANCE_BLACK, RecruitBase_Entrance_Movement_LeaveRecruitBase
    applymovement LOCALID_PLAYER RecruitBase_Entrance_Movement_LetHimPass
    waitmovement 0
    removeobject LOCALID_RECRUIT_BASE_ENTRANCE_BLACK
    applymovement LOCALID_RECRUIT_BASE_SCIENTIST, RecruitBase_Entrance_Movement_WalkToPlayer
    waitmovement 0
    delay 80
    msgbox RecruitBase_Entrance_Text_IHopeYouComplete, MSGBOX_AUTOCLOSE
    applymovement LOCALID_RECRUIT_BASE_SCIENTIST, RecruitBase_Entrance_Movement_SitBackToTheChair
    waitmovement 0
    fadedefaultbgm
    releaseall
    end

RecruitBase_Entrance_Movement_WalkTowardsBlack::
	walk_right
    face_up
	step_end

RecruitBase_Entrance_Movement_AlignToRight::
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
    walk_down
    walk_down
    walk_down
    walk_left
    walk_left
    walk_left
    face_up
    step_end

RecruitBase_Entrance_Movement_SitBackToTheChair::
    walk_right
    walk_right
    walk_right
    walk_up
    walk_up
    walk_right
    walk_right
    step_end
