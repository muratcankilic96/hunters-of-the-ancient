.set LOCALID_WOMAN, 2
.set LOCALID_OAK, 4
.set LOCALID_BLACK, 8

PalletTown_ProfessorOaksLab_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PalletTown_ProfessorOaksLab_OnFrame
	.byte 0

PalletTown_ProfessorOaksLab_OnFrame::
	map_script_2 VAR_STORYLINE_LAB_INVASION, 2, PalletTown_ProfessorOaksLab_BeginLabInvasion
	.2byte 0

PalletTown_ProfessorOaksLab_BeginLabInvasion::
	lock
	faceplayer
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	applymovement LOCALID_BLACK, Common_Movement_WalkUp
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_GoAway
	closemessage
	applymovement LOCALID_BLACK, PalletTown_ProfessorOaksLab_Movement_WalkIntimidatingly
	applymovement LOCALID_WOMAN, PalletTown_ProfessorOaksLab_Movement_GetCorneredByAssailant
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_ShutYourMouth
	closemessage
	applymovement LOCALID_BLACK, PalletTown_ProfessorOaksLab_Movement_TakePlayerAlong
	msgbox PalletTown_ProfessorOaksLab_Text_ComeOnNow
	closemessage
	applymovement LOCALID_BLACK, PalletTown_ProfessorOaksLab_Movement_WalkTowardsOak
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, PalletTown_ProfessorOaksLab_Movement_WalkTowardsOak
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_GiveMeYourPokemon
	closemessage
applymovement LOCALID_BLACK, PalletTown_ProfessorOaksLab_Movement_IntimidateOak
	applymovement LOCALID_OAK, PalletTown_ProfessorOaksLab_Movement_GetScaredFromGun
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_ChooseFromTable
	closemessage
	setvar VAR_STORYLINE_LAB_INVASION, 3
	releaseall
	end

PalletTown_ProfessorOaksLab_Computer::
	msgbox PalletTown_ProfessorOaksLab_Text_ComputerShutDown, MSGBOX_SIGN
	end

PalletTown_ProfessorOaksLab_ProfessorOak::
	msgbox PalletTown_ProfessorOaksLab_Text_SomebodyHelpMe, MSGBOX_AUTOCLOSE
	end

PalletTown_ProfessorOaksLab_Black::
	msgbox PalletTown_ProfessorOaksLab_Text_SmallTask, MSGBOX_AUTOCLOSE
	end

PalletTown_ProfessorOaksLab_Movement_WalkIntimidatingly::
	walk_up
	walk_up
	face_right
	step_end

PalletTown_ProfessorOaksLab_Movement_GetCorneredByAssailant::
	walk_up
	walk_right
	face_left
	step_end

PalletTown_ProfessorOaksLab_Movement_TakePlayerAlong::
	walk_down
	walk_down
	step_end

PalletTown_ProfessorOaksLab_Movement_WalkTowardsOak::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PalletTown_ProfessorOaksLab_Movement_IntimidateOak::
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

PalletTown_ProfessorOaksLab_Movement_GetScaredFromGun::
	walk_left
	walk_left
	walk_left
	walk_left
	face_right
	step_end
