Route23_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route23_OnTransition
	.byte 0

Route23_OnTransition::
	clearflag FLAG_HIDE_VICTORY_ROAD_3F_BOULDER
	setflag FLAG_HIDE_VICTORY_ROAD_2F_BOULDER
	setvar VAR_MAP_SCENE_VICTORY_ROAD_1F, 0
	setvar VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER1, 0
	setvar VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER2, 0
	setvar VAR_MAP_SCENE_VICTORY_ROAD_3F, 0
	end

Route23_EventScript_CascadeArtifactGuard::
	lock
	faceplayer
	setvar VAR_TEMP_1, 2
	bufferstdstring STR_VAR_1, STDSTRING_CASCADE_ARTIFACT
	goto Route23_EventScript_ArtifactGuard
	end

Route23_EventScript_ThunderArtifactGuard::
	lock
	faceplayer
	setvar VAR_TEMP_1, 3
	bufferstdstring STR_VAR_1, STDSTRING_THUNDER_ARTIFACT
	goto Route23_EventScript_ArtifactGuard
	end

Route23_EventScript_RainbowArtifactGuard::
	lock
	faceplayer
	setvar VAR_TEMP_1, 4
	bufferstdstring STR_VAR_1, STDSTRING_RAINBOW_ARTIFACT
	goto Route23_EventScript_ArtifactGuard
	end

Route23_EventScript_SoulArtifactGuard::
	lock
	faceplayer
	setvar VAR_TEMP_1, 5
	bufferstdstring STR_VAR_1, STDSTRING_SOUL_ARTIFACT
	goto Route23_EventScript_ArtifactGuard
	end

Route23_EventScript_MarshArtifactGuard::
	lock
	faceplayer
	setvar VAR_TEMP_1, 6
	bufferstdstring STR_VAR_1, STDSTRING_MARSH_ARTIFACT
	goto Route23_EventScript_ArtifactGuard
	end

Route23_EventScript_VolcanoArtifactGuard::
	lock
	faceplayer
	setvar VAR_TEMP_1, 7
	bufferstdstring STR_VAR_1, STDSTRING_VOLCANO_ARTIFACT
	goto Route23_EventScript_ArtifactGuard
	end

Route23_EventScript_EarthArtifactGuard::
	lock
	faceplayer
	setvar VAR_TEMP_1, 8
	bufferstdstring STR_VAR_1, STDSTRING_EARTH_ARTIFACT
	goto Route23_EventScript_ArtifactGuard
	end

Route23_EventScript_CascadeArtifactGuardTrigger::
	lockall
	setvar VAR_TEMP_1, 2
	setvar VAR_0x8009, LOCALID_CASCADE_ARTIFACT_GUARD
	bufferstdstring STR_VAR_1, STDSTRING_CASCADE_ARTIFACT
	goto Route23_EventScript_ArtifactGuardTrigger
	end

Route23_EventScript_ThunderArtifactGuardTrigger::
	lockall
	setvar VAR_TEMP_1, 3
	setvar VAR_0x8009, LOCALID_THUNDER_ARTIFACT_GUARD
	bufferstdstring STR_VAR_1, STDSTRING_THUNDER_ARTIFACT
	goto Route23_EventScript_ArtifactGuardTrigger
	end

Route23_EventScript_RainbowArtifactGuardTrigger::
	lockall
	setvar VAR_TEMP_1, 4
	setvar VAR_0x8009, LOCALID_RAINBOW_ARTIFACT_GUARD
	bufferstdstring STR_VAR_1, STDSTRING_RAINBOW_ARTIFACT
	goto Route23_EventScript_ArtifactGuardTrigger
	end

Route23_EventScript_SoulArtifactGuardTrigger::
	lockall
	setvar VAR_TEMP_1, 5
	setvar VAR_0x8009, LOCALID_SOUL_ARTIFACT_GUARD
	bufferstdstring STR_VAR_1, STDSTRING_SOUL_ARTIFACT
	goto Route23_EventScript_ArtifactGuardTrigger
	end

Route23_EventScript_MarshArtifactGuardTrigger::
	lockall
	setvar VAR_TEMP_1, 6
	setvar VAR_0x8009, LOCALID_MARSH_ARTIFACT_GUARD
	bufferstdstring STR_VAR_1, STDSTRING_MARSH_ARTIFACT
	goto Route23_EventScript_ArtifactGuardTrigger
	end

Route23_EventScript_VolcanoArtifactGuardTrigger::
	lockall
	setvar VAR_TEMP_1, 7
	setvar VAR_0x8009, LOCALID_VOLCANO_ARTIFACT_GUARD
	bufferstdstring STR_VAR_1, STDSTRING_VOLCANO_ARTIFACT
	goto Route23_EventScript_ArtifactGuardTrigger
	end

Route23_EventScript_EarthArtifactGuardTrigger::
	lockall
	setvar VAR_TEMP_1, 8
	setvar VAR_0x8009, LOCALID_EARTH_ARTIFACT_GUARD
	bufferstdstring STR_VAR_1, STDSTRING_EARTH_ARTIFACT
	goto Route23_EventScript_ArtifactGuardTrigger
	end

Route23_EventScript_VictoryRoadGateSign::
	msgbox Route23_Text_VictoryRoadGateSign, MSGBOX_SIGN
	end
