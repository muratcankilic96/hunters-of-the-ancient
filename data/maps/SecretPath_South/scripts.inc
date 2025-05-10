SecretPath_South_MapScripts::
    .byte 0

SecretPath_South_PreventEnteringIntoWildGrass::
    msgbox SecretPath_South_Text_CannotWanderInGrass, MSGBOX_AUTOCLOSE
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkOppositeDirection
    waitmovement 0
    end
