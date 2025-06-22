PalletTown_ProfessorOaksLab_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PalletTown_ProfessorOaksLab_OnFrame
	.byte 0

PalletTown_ProfessorOaksLab_OnFrame::
	map_script_2 VAR_STORYLINE_LAB_INVASION, 2, PalletTown_ProfessorOaksLab_BeginLabInvasion
	.2byte 0

PalletTown_ProfessorOaksLab_BeginLabInvasion::
	lock
	faceplayer
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	applymovement LOCALID_OAKS_LAB_BLACK, Common_Movement_WalkUp
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_GoAway
	closemessage
	applymovement LOCALID_OAKS_LAB_BLACK, PalletTown_ProfessorOaksLab_Movement_WalkIntimidatingly
	applymovement LOCALID_OAKS_LAB_WOMAN, PalletTown_ProfessorOaksLab_Movement_GetCorneredByAssailant
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_ShutYourMouth
	closemessage
	applymovement LOCALID_OAKS_LAB_BLACK, PalletTown_ProfessorOaksLab_Movement_TakePlayerAlong
	msgbox PalletTown_ProfessorOaksLab_Text_ComeOnNow
	closemessage
	applymovement LOCALID_OAKS_LAB_BLACK, PalletTown_ProfessorOaksLab_Movement_WalkTowardsOak
	waitmovement 0
	applymovement LOCALID_PLAYER, PalletTown_ProfessorOaksLab_Movement_WalkTowardsOak
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_GiveMeYourPokemon
	closemessage
	applymovement LOCALID_OAKS_LAB_BLACK, PalletTown_ProfessorOaksLab_Movement_IntimidateOak
	applymovement LOCALID_OAKS_LAB_PROF_OAK, PalletTown_ProfessorOaksLab_Movement_GetScaredFromGun
	waitmovement 0
	msgbox PalletTown_ProfessorOaksLab_Text_ChooseFromTable
	closemessage
	setvar VAR_STORYLINE_LAB_INVASION, 3
	releaseall
	end

PalletTown_ProfessorOaksLab_Computer::
	msgbox PalletTown_ProfessorOaksLab_Text_ElmsEmail, MSGBOX_SIGN
	end

PalletTown_ProfessorOaksLab_ProfessorOak::
	msgbox PalletTown_ProfessorOaksLab_Text_SomebodyHelpMe, MSGBOX_AUTOCLOSE
	end

PalletTown_ProfessorOaksLab_Black::
	msgbox PalletTown_ProfessorOaksLab_Text_SmallTask, MSGBOX_AUTOCLOSE
	end

PalletTown_ProfessorOaksLab_Woman::
	msgbox PalletTown_ProfessorOaksLab_Text_Scream, MSGBOX_NPC
	end

PalletTown_ProfessorOaksLab_PreventGoingToBasementSide::
	msgbox PalletTown_ProfessorOaksLab_Text_WhereAreYouGoing, MSGBOX_NPC
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	waitmovement 0
	end

PalletTown_ProfessorOaksLab_PickChikorita::
	goto_if_ge VAR_STORYLINE_GOT_FIRST_POKEMON, 1, PalletTown_ProfessorOaksLab_AlreadyPickedPokemon
	setvar VAR_TEMP_1, SPECIES_CHIKORITA
	setvar VAR_TEMP_2, FLAG_HIDE_CHIKORITA_BALL
	goto PalletTown_ProfessorOaksLab_ShowPokemonPicture

PalletTown_ProfessorOaksLab_PickTotodile::
	goto_if_ge VAR_STORYLINE_GOT_FIRST_POKEMON, 1, PalletTown_ProfessorOaksLab_AlreadyPickedPokemon
	setvar VAR_TEMP_1, SPECIES_TOTODILE
	setvar VAR_TEMP_2, FLAG_HIDE_TOTODILE_BALL
	goto PalletTown_ProfessorOaksLab_ShowPokemonPicture

PalletTown_ProfessorOaksLab_PickCyndaquil::
	goto_if_ge VAR_STORYLINE_GOT_FIRST_POKEMON, 1, PalletTown_ProfessorOaksLab_AlreadyPickedPokemon
	setvar VAR_TEMP_1, SPECIES_CYNDAQUIL
	setvar VAR_TEMP_2, FLAG_HIDE_CYNDAQUIL_BALL
	goto PalletTown_ProfessorOaksLab_ShowPokemonPicture

PalletTown_ProfessorOaksLab_ShowPokemonPicture::
	showmonpic VAR_TEMP_1, 10, 3
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	goto PalletTown_ProfessorOaksLab_MakeStealingDecision

PalletTown_ProfessorOaksLab_MakeStealingDecision::
	msgbox PalletTown_ProfessorOaksLab_Text_StealingDecision, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PalletTown_ProfessorOaksLab_StealPokemon
	hidemonpic
	release
	end

PalletTown_ProfessorOaksLab_StealPokemon::
	hidemonpic
	removeobject VAR_LAST_TALKED
	givemon VAR_TEMP_1, 5
	setflag VAR_TEMP_2
	message PalletTown_ProfessorOaksLab_Text_StolePokemon
	waitmessage
	playfanfare MUS_OBTAIN_KEY_ITEM
	waitfanfare
	msgbox PalletTown_ProfessorOaksLab_Text_Nickname, MSGBOX_YESNO
	call_if_eq VAR_RESULT, 1, PalletTown_ProfessorOaksLab_Nickname
	closemessage
	setvar VAR_STORYLINE_GOT_FIRST_POKEMON, 1
@ TODO: Find the purpose of these variables and flags:
@ setvar 0x5003 0x1
@ setvar 0x5000 0x1
@ setflag 0x100E
@ setflag 0x1065
	copyvar VAR_STARTER_MON, VAR_TEMP_1
	setflag FLAG_SYS_POKEMON_GET
	end

PalletTown_ProfessorOaksLab_Nickname::
	setvar VAR_0x8004, 0
	call EventScript_ChangePokemonNickname
	return

PalletTown_ProfessorOaksLab_AlreadyPickedPokemon::
	msgbox PalletTown_ProfessorOaksLab_Text_AlreadyGotOne, MSGBOX_AUTOCLOSE
	end

PalletTown_ProfessorOaksLab_TriggerOnLeavingLab::
	goto_if_ge VAR_STORYLINE_GOT_FIRST_POKEMON, 1, PalletTown_ProfessorOaksLab_PoliceBattleEvent
	msgbox PalletTown_ProfessorOaksLab_Text_FirstShouldStealPokemon, MSGBOX_AUTOCLOSE
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	end

PalletTown_ProfessorOaksLab_PoliceBattleEvent::
	setrespawn HEAL_LOCATION_GAME_OVER
	msgbox PalletTown_ProfessorOaksLab_Text_YouMadeAChoice
	closemessage
	clearflag FLAG_HIDE_BLACK_IN_PALLET_TOWN
	addobject LOCALID_OAKS_LAB_POLICE
	clearflag FLAG_HIDE_POKEDEX_IN_RECRUIT_BASE
	applymovement LOCALID_OAKS_LAB_POLICE, PalletTown_ProfessorOaksLab_Movement_DiveIntoLab
	applymovement LOCALID_OAKS_LAB_BLACK, PalletTown_ProfessorOaksLab_Movement_PrepareToEscape
	msgbox PalletTown_ProfessorOaksLab_Text_Police
	closemessage
	msgbox PalletTown_ProfessorOaksLab_UseYourPicked
	closemessage
	trainerbattle_no_intro TRAINER_OAK_LAB_SECURITY, PalletTown_ProfessorOaksLab_IFailedToStopYou
	setrespawn HEAL_LOCATION_RECRUIT_BASE
	msgbox PalletTown_ProfessorOaksLab_LetsRun
	closemessage
	setvar VAR_STORYLINE_LAB_INVASION, 4
@ TODO: Find the purpose of this flag: clearflag 0x107
	warp MAP_PALLET_TOWN, 16, 14
	waitstate
	releaseall
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

PalletTown_ProfessorOaksLab_Movement_DiveIntoLab::
	walk_up
	walk_up
	walk_up
	step_end

PalletTown_ProfessorOaksLab_Movement_PrepareToEscape::
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
