TransferRequest_EventScript_Describe::
	setvar VAR_0x8004, HELPCONTEXT_PC_MISC
	special BackupHelpContext
	special Script_SetHelpContext
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetRequestedPokemonForTransfer
	bufferspeciesname STR_VAR_1, VAR_RESULT
	msgbox TransferRequest_Text_BossRequestsThis
	goto TransferRequest_EventScript_EndAnnouncement
	end

TransferRequest_EventScript_EndAnnouncement::
	special RestoreHelpContext
	return
