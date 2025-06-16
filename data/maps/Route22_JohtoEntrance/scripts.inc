Route22_JohtoEntrance_MapScripts::
	.byte 0

Route22_JohtoEntrance_Police::
	msgbox Route22_JohtoEntrance_Text_PassingBeyondThisPoint, MSGBOX_NPC
	end

Route22_JohtoEntrance_Receptionist::
	msgbox Route22_JohtoEntrance_Text_HoldOnThere, MSGBOX_NPC
	end

Route22_JohtoEntrance_PreventPassing::
	msgbox Route22_JohtoEntrance_Text_HoldOnThere, MSGBOX_NPC
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	end
