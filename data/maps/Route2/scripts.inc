Route2_MapScripts::
	.byte 0

Route2_RouteSign::
	msgbox Route2_Text_RouteSign, MSGBOX_SIGN
	end

Route2_DiglettsCaveSign::
	msgbox Route2_Text_DiglettsCave, MSGBOX_SIGN
	end

Route2_Rocket::
	msgbox Route2_Text_YouCanRecognizeThem, MSGBOX_NPC
	end

Route2_WarnAboutIpa::
	applymovement LOCALID_ROUTE_2_ROCKET, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Route2_Text_ThereIsASecretOrganization
	closemessage
	setvar VAR_STORYLINE_IPA_WARNING, 1
	end
