Route22_JohtoEntrance_MapScripts::
	.byte 0

Route22_JohtoEntrance_Police::
	msgbox Route22_JohtoEntrance_Text_PassingBeyondThisPoint, MSGBOX_NPC
	end

Route22_JohtoEntrance_Receptionist::
	msgbox Route22_JohtoEntrance_Text_HoldOnThere, MSGBOX_NPC
	end

Route22_JohtoEntrance_PreventPassing::
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_JOHTO_BORDER_RECEPTIONIST, Common_Movement_FaceLeft
	waitmovement 0
	msgbox Route22_JohtoEntrance_Text_HoldOnThere, MSGBOX_NPC
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	call EventScript_RestorePrevTextColor
	end
