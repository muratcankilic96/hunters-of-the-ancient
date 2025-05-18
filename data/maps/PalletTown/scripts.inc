.set LOCALID_BLACK, 3

PalletTown_MapScripts::
	.byte 0

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
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

PalletTown_Movement_FollowTowardsOaksLab::
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
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
