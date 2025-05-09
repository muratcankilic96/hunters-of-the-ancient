SecretWoods_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SecretWoods_OnTransition
	.byte 0

SecretWoods_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SECRET_WOODS
	end

SecretWoods_EventScript_Scientist::
	msgbox SecretWoods_Text_Scientist, MSGBOX_NPC
	end

SecretWoods_EventScript_FemaleRocket::
	msgbox SecretWoods_Text_FemaleRocket, MSGBOX_NPC
	end
	
SecretWoods_EventScript_MaleRocket::
	msgbox SecretWoods_Text_MaleRocket, MSGBOX_NPC
	goto_if_set FLAG_SYS_POKEMON_GET, SecretWoods_EventScript_MaleRocketAfterInvasion
	end

SecretWoods_EventScript_MaleRocketAfterInvasion::
	msgbox SecretWoods_Text_MaleRocketAfterLabInvasion, MSGBOX_NPC
	end

SecretWoods_EventScript_FlagUnsetBeforeRecruitBase::
	setvar VAR_STORYLINE_LAB_INVASION, 7
	end

SecretWoods_EventScript_BaseSign::
	msgbox SecretWoods_Text_RecruitBaseSign, MSGBOX_SIGN
	end

SecretWoods_EventScript_RecruitHelp::
	msgbox SecretWoods_Text_RecruitHelpSign, MSGBOX_SIGN
	end
