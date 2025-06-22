RecruitBase_MainHall_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, RecruitBase_MainHall_OnFrame
	.byte 0

RecruitBase_MainHall_OnFrame::
	map_script_2 VAR_STORYLINE_DEFEATED_BROCK, 1, RecruitBase_MainHall_RunningShoes
	.2byte 0

RecruitBase_MainHall_Computer::
	msgbox RecruitBase_MainHall_Text_NeedsPassword, MSGBOX_SIGN
	end

RecruitBase_MainHall_RecruitBaseSign::
	msgbox RecruitBase_MainHall_Text_RecruitBaseSign, MSGBOX_SIGN
	end

RecruitBase_MainHall_Box_Empty::
	msgbox RecruitBase_MainHall_Text_Box_Empty, MSGBOX_SIGN
	end

RecruitBase_MainHall_Box_TeamRocketSuits::
	msgbox RecruitBase_MainHall_Text_Box_TeamRocketSuits, MSGBOX_SIGN
	end

RecruitBase_MainHall_Box_Pokeballs::
	msgbox RecruitBase_MainHall_Text_Box_Pokeballs, MSGBOX_SIGN
	end

RecruitBase_MainHall_Grunt1::
	msgbox RecruitBase_MainHall_Text_AccordingToLegend, MSGBOX_NPC
	end

RecruitBase_MainHall_Grunt2::
	msgbox RecruitBase_MainHall_Text_WeAreTheNewMembers, MSGBOX_NPC
	end

RecruitBase_MainHall_Grunt3::
	goto_if_ge VAR_STORYLINE_DEFEATED_BROCK, 2, RecruitBase_MainHall_Grunt3_AfterFirstArtifact
	msgbox RecruitBase_MainHall_Text_CollectingTreasures, MSGBOX_NPC
	end

RecruitBase_MainHall_Grunt3_AfterFirstArtifact::
	msgbox RecruitBase_MainHall_Text_TeamMagma, MSGBOX_NPC
	end

RecruitBase_MainHall_Grunt4::
	msgbox RecruitBase_MainHall_Text_WillOrderTheWorld, MSGBOX_NPC
	end

RecruitBase_MainHall_Grunt5::
	msgbox RecruitBase_MainHall_Text_ExceedsYourAuthority, MSGBOX_NPC
	end

RecruitBase_MainHall_RunningShoes::
	lock
	faceplayer
	msgbox RecruitBase_MainHall_Text_ComeHere
	waitmessage
	applymovement LOCALID_PLAYER, RecruitBase_MainHall_Movement_GetCloserToGiovanni
	msgbox RecruitBase_MainHall_Text_BossWantsToSpeak, MSGBOX_AUTOCLOSE
	playfanfare MUS_OBTAIN_KEY_ITEM
	message RecruitBase_MainHall_Text_PlayerGetsRunningShoes
	waitmessage
	waitfanfare
	msgbox RecruitBase_MainHall_Text_PlayerSwitchesRunningShoes
	setflag FLAG_SYS_B_DASH
	msgbox RecruitBase_MainHall_Text_GiovanniDismissesPlayer, MSGBOX_AUTOCLOSE
	applymovement LOCALID_RECRUIT_BASE_MAIN_HALL_GIOVANNI, RecruitBase_MainHall_Movement_GoRecruitBaseUnderground
	setvar VAR_STORYLINE_DEFEATED_BROCK, 2
	setvar VAR_STORYLINE_ALLOW_LEAVING_PEWTER, 1
	setflag FLAG_HIDE_PEWTER_CITY_EXIT_IPA_AGENT
	clearflag FLAG_HIDE_PEWTER_CITY_GYM_FRONT_IPA_AGENTS
	waitmovement 0
	msgbox RecruitBase_MainHall_Text_BlackGoesAhead, MSGBOX_AUTOCLOSE
	fadescreen FADE_FROM_BLACK
	warp MAP_CINEMATIC_BLACK_SCREEN, 9, 9
	releaseall
	end

RecruitBase_MainHall_Movement_GetCloserToGiovanni::
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

RecruitBase_MainHall_Movement_GoRecruitBaseUnderground::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
