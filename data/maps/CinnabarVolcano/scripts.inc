CinnabarVolcano_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarVolcano_OnTransition
	.byte 0

CinnabarVolcano_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CINNABAR_VOLCANO
	end
