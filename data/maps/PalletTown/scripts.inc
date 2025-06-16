.set LOCALID_BLACK, 3
.set LOCALID_POLICE, 4

PalletTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PalletTown_OnFrame
	.byte 0

PalletTown_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_PALLET_TOWN
    goto_if_eq VAR_STORYLINE_LAB_INVASION, 4, PalletTown_RepositionBlackAndPolice
    end

PalletTown_OnFrame::
	map_script_2 VAR_STORYLINE_LAB_INVASION, 4, PalletTown_RunFromPalletTown
	.2byte 0

PalletTown_RepositionBlackAndPolice::
	setobjectxyperm LOCALID_POLICE, 1, 1
    setobjectxyperm LOCALID_BLACK, 17, 14
    setobjectmovementtype LOCALID_BLACK, MOVEMENT_TYPE_FACE_RIGHT
    end

PalletTown_MeetWithBlackForLabInvasion::
	setflag FLAG_HIDE_BLACK_IN_PALLET_TOWN
@ TODO: Find the purpose of this flag: setflag 0x105
	lockall
	faceplayer
	playbgm MUS_ENCOUNTER_RIVAL, 0
	applymovement LOCALID_BLACK, PalletTown_Movement_GetCloseToPlayer
	waitmovement 0
	msgbox PalletTown_Text_YouCameAsExpected
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PalletTown_Movement_FollowTowardsOaksLab
	applymovement LOCALID_BLACK, PalletTown_Movement_MoveTowardsOaksLab
	waitmovement 0
	msgbox PalletTown_Text_PoliceIsHere
	closemessage
	setdooropen 16, 13
	waitdooranim
	applymovement LOCALID_BLACK, PalletTown_Movement_EnterOaksLab
	applymovement OBJ_EVENT_ID_PLAYER, PalletTown_Movement_FollowThroughOaksLab
	waitmovement 0
	setdoorclosed 16, 13
	waitdooranim
	setvar VAR_STORYLINE_LAB_INVASION, 2
	fadedefaultbgm
	warp MAP_PALLET_TOWN_PROFESSOR_OAKS_LAB, 6, 12
	waitstate
	releaseall
    end

PalletTown_RunFromPalletTown::
	lock
	faceplayer
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	applymovement LOCALID_BLACK, Common_Movement_FaceRight
	waitmovement 0
	msgbox PalletTown_Text_LetsGetBack
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PalletTown_Movement_FollowThroughSecretPath
	applymovement LOCALID_BLACK, PalletTown_Movement_LeaveTowardsSecretPath
	waitmovement 0
	removeobject LOCALID_BLACK
	setvar VAR_STORYLINE_LAB_INVASION, 5
	waitmovement 0
	release
	end

PalletTown_Woman::
	msgbox PalletTown_Text_WhoAreYou, MSGBOX_NPC
	end

PalletTown_FatMan::
	msgbox PalletTown_Text_YouCanSwim, MSGBOX_NPC
	end

PalletTown_ForSaleSign::
	msgbox PalletTown_Text_ForSaleSign, MSGBOX_SIGN
	end

PalletTown_OaksHouseSign::
	msgbox PalletTown_Text_OaksHouseSign, MSGBOX_SIGN
	end

PalletTown_OaksLabSign::
	msgbox PalletTown_Text_OaksLabSign, MSGBOX_SIGN
	end

PalletTown_TownSign::
	msgbox PalletTown_Text_TownSign, MSGBOX_SIGN
	end

PalletTown_LabDoor::
	msgbox PalletTown_Text_LabDoor, MSGBOX_SIGN
	end

PalletTown_EmptyHouseDoor::
	msgbox PalletTown_Text_EmptyHouseDoor
	closemessage
	end

PalletTown_Movement_GetCloseToPlayer::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	face_right
	step_end

PalletTown_Movement_MoveTowardsOaksLab::
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PalletTown_Movement_FollowTowardsOaksLab::
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

PalletTown_Movement_EnterOaksLab::
	walk_up
	set_invisible
	step_end

PalletTown_Movement_FollowThroughOaksLab::
	walk_left
	walk_up
	set_invisible
	step_end

PalletTown_Movement_FollowThroughSecretPath::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

PalletTown_Movement_LeaveTowardsSecretPath::
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	set_invisible
	step_end
