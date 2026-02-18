SecretWoods_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SecretWoods_OnTransition
	.byte 0

SecretWoods_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SECRET_WOODS
	end

SecretWoods_Scientist::
	msgbox SecretWoods_Text_WithNewTechnology, MSGBOX_NPC
	msgbox Promote, MSGBOX_NPC
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_SYS_POKEDEX_GET
	givemon SPECIES_SKARMORY, 80
	givemon SPECIES_ALAKAZAM, 80
	end

Promote::
	.string "You have FAIRY types now!$"

SecretWoods_FemaleRocket::
	msgbox SecretWoods_Text_GreatPlaceToHide, MSGBOX_NPC
	end
	
SecretWoods_MaleRocket::
	msgbox SecretWoods_Text_WithoutPokemonYouCannotWander, MSGBOX_NPC
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_43, MtEmber_Exterior_Text_Grunt1Defeat
	goto_if_set FLAG_SYS_POKEMON_GET, SecretWoods_MaleRocketAfterInvasion
	end

SecretWoods_MaleRocketAfterInvasion::
	msgbox SecretWoods_Text_YouGotYourPokemon, MSGBOX_NPC
	end

SecretWoods_BaseSign::
	msgbox SecretWoods_Text_RecruitBaseSign, MSGBOX_SIGN
	end

SecretWoods_RecruitHelp::
	msgbox SecretWoods_Text_RecruitHelpSign, MSGBOX_SIGN
	end
