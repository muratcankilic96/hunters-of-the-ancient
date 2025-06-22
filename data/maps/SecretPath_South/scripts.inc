SecretPath_South_MapScripts::
    .byte 0

SecretPath_South_PreventEnteringIntoWildGrass::
    msgbox SecretPath_South_Text_CannotWanderInGrass, MSGBOX_AUTOCLOSE
    applymovement LOCALID_PLAYER, Common_Movement_WalkOppositeDirection
    waitmovement 0
    end

SecretPath_South_PreventLeavingSecretPath::
    msgbox SecretPath_South_Text_CannotLeave, MSGBOX_AUTOCLOSE
    applymovement LOCALID_PLAYER, Common_Movement_WalkOppositeDirection
    waitmovement 0
    end

SecretPath_South_PreventLeavingPalletTown::
    msgbox SecretPath_South_Text_ThePoliceIsHere, MSGBOX_AUTOCLOSE
    applymovement LOCALID_PLAYER, Common_Movement_WalkOppositeDirection
    waitmovement 0
    end

SecretPath_South_TriggerEventFromLeft::
    applymovement LOCALID_SECRET_PATH_BLACK, SecretPath_South_Movement_MoveCloseToPlayerAtLeft
    waitmovement 0
    goto SecretPath_South_InvitePlayerForStealing

SecretPath_South_TriggerEventFromRight::
    applymovement LOCALID_SECRET_PATH_BLACK, SecretPath_South_Movement_MoveCloseToPlayerAtRight
    waitmovement 0
    goto SecretPath_South_InvitePlayerForStealing

SecretPath_South_InvitePlayerForStealing::
    setflag FLAG_HIDE_BLACK_IN_SECRET_PATH
@ TODO: Find the purpose of this flag: setflag 0x10A
    lockall
    faceplayer
    playbgm MUS_ENCOUNTER_RIVAL, 0
    applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
    waitmovement 0
    msgbox SecretPath_South_Text_RivalIntroduction
    closemessage
    applymovement LOCALID_SECRET_PATH_BLACK, SecretPath_South_Movement_LeaveToPalletTown
    waitmovement 0
    setvar VAR_STORYLINE_LAB_INVASION, 1
    fadedefaultbgm
    releaseall
    end

SecretPath_South_Movement_MoveCloseToPlayerAtLeft::
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_left
    face_down
    step_end

SecretPath_South_Movement_MoveCloseToPlayerAtRight::
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    step_end

SecretPath_South_Movement_LeaveToPalletTown::
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    set_invisible
    step_end
