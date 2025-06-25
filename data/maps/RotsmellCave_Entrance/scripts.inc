RotsmellCave_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RotsmellCave_Entrance_OnTransition
    .byte 0

RotsmellCave_Entrance_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_ROTSMELL_CAVE
	end
