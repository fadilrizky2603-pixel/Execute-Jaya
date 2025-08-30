#include <YSI_Coding\y_hooks>

new pTimerCrafting[MAX_PLAYERS] = {-1, ...};

enum e_stuffcrafting
{
    STREAMER_TAG_AREA: CraftingArea,
    STREAMER_TAG_AREA: ClipArea,
    STREAMER_TAG_AREA: BombArea,
    STREAMER_TAG_3D_TEXT_LABEL:ClipLabel,
    STREAMER_TAG_3D_TEXT_LABEL:CraftingLabel
};
new Stuff_Craft[e_stuffcrafting];

hook OnScriptInit()
{
    Stuff_Craft[ClipArea] = CreateDynamicSphere(-1302.7467,2555.1570,87.1255, 2.0, 0, 0, -1);
    Stuff_Craft[BombArea] = CreateDynamicSphere(-1667.4523,2486.4460,87.1731, 2.0, 0, 0, -1);
    Stuff_Craft[CraftingArea] = CreateDynamicSphere(-2140.4128, -244.7229, 36.5156, 2.0, 0, 0, -1);
    Stuff_Craft[CraftingLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Buy Bomb", -1, -1667.4523,2486.4460,87.1731, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
    Stuff_Craft[CraftingLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Clip Crafting", -1, -1302.7467,2555.1570,87.1255, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
    Stuff_Craft[CraftingLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Crafting", -1, -2140.4128, -244.7229, 36.5156, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
}

hook OnPlayerConnect(playerid)
{
    pTimerCrafting[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerCrafting[playerid]);
    pTimerCrafting[playerid] = -1;
    return 1;
}
forward ClipSlc(playerid);
public ClipSlc(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 80)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 80!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 25)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 25!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 80);
        Inventory_Remove(playerid, "Baja", 25);

        Inventory_Add(playerid, "Clip SLC", 2969, 1);
		ShowItemBox(playerid, "Received 1x", "Clip SLC", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward ClipDe(playerid);
public ClipDe(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }
    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 50);
        Inventory_Remove(playerid, "Besi", 100);

        Inventory_Add(playerid, "Clip DE", 2969, 1);
        ShowItemBox(playerid, "Received 1x", "Clip DE", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward ClipColt(playerid);
public ClipColt(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 60)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kaca") < 10)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 10!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 20)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 20!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Baja", 60);
        Inventory_Remove(playerid, "Kaca", 10);
        Inventory_Remove(playerid, "Kayu Kemas", 20);

        Inventory_Add(playerid, "Clip COLT", 2969, 1);
		ShowItemBox(playerid, "Received 1x", "Clip COLT", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward ClipSG(playerid);
public ClipSG(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 50);
        Inventory_Remove(playerid, "Besi", 100);
        Inventory_Remove(playerid, "Kayu Kemas", 100);

        Inventory_Add(playerid, "Clip SG", 2969, 1);
        ShowItemBox(playerid, "Received 1x", "Clip SG", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward ClipAK(playerid);
public ClipAK(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 50);
        Inventory_Remove(playerid, "Besi", 100);
        Inventory_Remove(playerid, "Kayu Kemas", 100);

        Inventory_Add(playerid, "Clip AK-47", 2969, 1);
        ShowItemBox(playerid, "Received 1x", "Clip AK-47", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward ClipSOS(playerid);
public ClipSOS(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 50);
        Inventory_Remove(playerid, "Besi", 100);
        Inventory_Remove(playerid, "Kayu Kemas", 100);

        Inventory_Add(playerid, "Clip SOS", 2969, 1);
        ShowItemBox(playerid, "Received 1x", "Clip SOS", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward ClipUzi(playerid);
public ClipUzi(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 250)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 250!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 60)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kaca") < 10)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 10!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 20)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 20!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Material", 250);
        Inventory_Remove(playerid, "Baja", 60);
        Inventory_Remove(playerid, "Kaca", 10);
        Inventory_Remove(playerid, "Kayu Kemas", 20);

        Inventory_Add(playerid, "Clip Uzi", 2969, 1);
		ShowItemBox(playerid, "Received 1x", "Clip Uzi", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward ClipTec(playerid);
public ClipTec(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 250)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 250!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 60)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kaca") < 10)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 10!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 20)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 20!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Material", 250);
        Inventory_Remove(playerid, "Baja", 60);
        Inventory_Remove(playerid, "Kaca", 10);
        Inventory_Remove(playerid, "Kayu Kemas", 20);

        Inventory_Add(playerid, "Clip TEC-9", 2969, 1);
		ShowItemBox(playerid, "Received 1x", "Clip TEC-9", 2969);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward Kevlar(playerid);
public Kevlar(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Pakaian") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Pakaian tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 50);
        Inventory_Remove(playerid, "Besi", 100);
        Inventory_Remove(playerid, "Kayu Kemas", 100);
        Inventory_Remove(playerid, "Pakaian", 100);
        Inventory_Add(playerid, "Kevlar", 19515, 1);
        ShowItemBox(playerid, "Received 1x", "Kevlar", 19515);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward Colt(playerid);
public Colt(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 80)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 80!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Tembaga") < 120)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga tidak cukup, butuh 120!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 25)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 25!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 8)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 8!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 80);
        Inventory_Remove(playerid, "Tembaga", 120);
        Inventory_Remove(playerid, "Baja", 25);
        Inventory_Remove(playerid, "Kayu Kemas", 8);

        GivePlayerWeaponEx(playerid, 22, 1);
		ShowItemBox(playerid, "Received 1x", "Colt-45", 346);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}
forward DesertE(playerid);
public DesertE(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 250)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 250!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 60)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kaca") < 10)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 10!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 20)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 20!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Material", 250);
        Inventory_Remove(playerid, "Baja", 60);
        Inventory_Remove(playerid, "Kaca", 10);
        Inventory_Remove(playerid, "Kayu Kemas", 20);

        GivePlayerWeaponEx(playerid, 24, 1);
		ShowItemBox(playerid, "Received 1x", "Desert Eagle", 378);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}
forward Shotgun(playerid);
public Shotgun(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 400)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 400!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 350)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 350!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Tembaga") < 250)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga tidak cukup, butuh 250!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Berlian") < 8)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Berlian tidak cukup, butuh 8!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 75)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 75!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Alumunium") < 150)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Alumunium tidak cukup, butuh 150!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kaca") < 30)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kaca tidak cukup, butuh 30!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 400);
        Inventory_Remove(playerid, "Besi", 350);
        Inventory_Remove(playerid, "Tembaga", 250);
        Inventory_Remove(playerid, "Berlian", 8);
        Inventory_Remove(playerid, "Baja", 75);
        Inventory_Remove(playerid, "Alumunium", 150);
        Inventory_Remove(playerid, "Kaca", 30);
        Inventory_Remove(playerid, "Kayu Kemas", 100);

        GivePlayerWeaponEx(playerid, 25, 1);
		ShowItemBox(playerid, "Received 1x", "SHOTGUN", 349);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 10;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}
forward Mp5(playerid);
public Mp5(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 250)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 250!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 160)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 160!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 70)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 70!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Alumunium") < 75)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Alumunium tidak cukup, butuh 75!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 250);
        Inventory_Remove(playerid, "Kayu Kemas", 160);
        Inventory_Remove(playerid, "Baja", 70);
        Inventory_Remove(playerid, "Alumunium", 75);

        GivePlayerWeaponEx(playerid, 29, 1);
		ShowItemBox(playerid, "Received 1x", "MP5", 353);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 10;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}
forward Ak47(playerid);
public Ak47(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 350)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 350!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Kemas") < 200)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 200!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 150)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 150!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 350);
        Inventory_Remove(playerid, "Kayu Kemas", 200);
        Inventory_Remove(playerid, "Baja", 150);

        GivePlayerWeaponEx(playerid, 30, 1);
		ShowItemBox(playerid, "Received 1x", "AK-47", 355);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}
forward Tec9(playerid);
public Tec9(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured] != 0)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Material") < 450)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 450!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 100)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Baja") < 75)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 75!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Alumunium") < 60)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Alumunium tidak cukup, butuh 60!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Tembaga") < 500)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga tidak cukup, butuh 500!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }


    if(Inventory_Count(playerid, "Emas") < 30)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Emas tidak cukup, butuh 30!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Berlian") < 10)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Berlian tidak cukup, butuh 10!");
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerCrafting[playerid]);
        pTimerCrafting[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        StopLoopingAnim(playerid);
        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Material", 450);
        Inventory_Remove(playerid, "Besi", 100);
        Inventory_Remove(playerid, "Baja", 75);
        Inventory_Remove(playerid, "Alumunium", 60);
        Inventory_Remove(playerid, "Tembaga", 500);
        Inventory_Remove(playerid, "Emas", 30);
        Inventory_Remove(playerid, "Berlian", 10);

        GivePlayerWeaponEx(playerid, 32, 1);
		ShowItemBox(playerid, "Received 1x", "TEC-9", 372);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInDynamicArea(playerid, Stuff_Craft[CraftingArea]))
        {
            new countpd = 0, countems = 0;
            foreach(new pid : Player) {
                if(IsPlayerConnected(pid))
                {
                    if(AccountData[pid][pDutyPD]) countpd++;
                    if(AccountData[pid][pDutyEms]) countems++;
                }
            }
            if(countpd >= 4 && countems >= 2)
            {
                if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level Anda tidak cukup! (Min: 15)");
                if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dalam Family!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                ShowPlayerDialog(playerid, DIALOG_CRAFTING, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Crafting", 
                "Kevlar\
                \n"GRAY"Colt 45\
                \nDesert Eagle\
                \n"GRAY"Shotgun\
                \nAK-47\
                \n"GRAY"TEC-9", "Pilih", "Batal");
            }
            else return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty & 2 EMS Duty!");
        }
        if(IsPlayerInDynamicArea(playerid, Stuff_Craft[ClipArea]))
        {
            new countpd = 0, countems = 0;
            foreach(new pid : Player) {
                if(IsPlayerConnected(pid))
                {
                    if(AccountData[pid][pDutyPD]) countpd++;
                    if(AccountData[pid][pDutyEms]) countems++;
                }
            }
            if(countpd >= 4 && countems >= 2)
            {
                if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level Anda tidak cukup! (Min: 15)");
                if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dalam Family!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIP, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Crafting", 
                "Clip DE\
                \n"GRAY"Clip SLC\
                \nClip COLT-45\
                \n"GRAY"Clip SG\
                \nClip SOS\
                \n"GRAY"Clip ak-47\
                \nClip UZI\
                \n"GRAY"TEC-9", "Pilih", "Batal");
            }
            else return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty & 2 EMS Duty!");
        }
        if(IsPlayerInDynamicArea(playerid, Stuff_Craft[BombArea]))
        {
            new countpd = 0, countems = 0;
            foreach(new pid : Player) {
                if(IsPlayerConnected(pid))
                {
                    if(AccountData[pid][pDutyPD]) countpd++;
                    if(AccountData[pid][pDutyEms]) countems++;
                }
            }
            if(countpd >= 4 && countems >= 2)
            {
                if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level Anda tidak cukup! (Min: 15)");
                if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dalam Family!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                new mstr[128];
                Inventory_Add(playerid, "C4", 1252);
                ShowItemBox(playerid, "Recived 1x", "C4", 1252);
                GiveMoney(playerid, -BOM_PRICE);
                ShowItemBox(playerid, "Remove $20000", "Uang", 1212);

                format(mstr, sizeof(mstr), "{FFFF00}Kamu berhasil membeli bom seharga {33AA33}$%d", BOM_PRICE);
                ShowTDN(playerid, NOTIFICATION_SUKSES, mstr);
            }
            else return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty & 2 EMS Duty!");
        }
    }
    return 1;
}

Dialog:DIALOG_CRAFTPASS(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level Anda tidak cukup! (Min: 15)");
    if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dalam Family!");
    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!, tidak dapat crafting!");

    if(isnull(inputtext)) return Dialog_Show(playerid, DIALOG_CRAFTPASS, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Crafting Password",
    "Error: Tidak dapat diisi kosong!\nMohon masukkan kata kunci / sandi jika ingin Crafting senjata tersebut dengan benar:", "Input", "Batal");

    if(IsNumeric(inputtext)) if(isnull(inputtext)) return Dialog_Show(playerid, DIALOG_CRAFTPASS, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Crafting Password",
    "Error: Tidak dapat diisi angka!\nMohon masukkan kata kunci / sandi jika ingin Crafting senjata tersebut dengan benar:", "Input", "Batal");
    
    new jskc[600];
    if(!strcmp(inputtext, "abogoboga", true))
    {
        switch(AccountData[playerid][pTempValue])
        {
            case 3: // Shotgun
            {
                format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Shotgun"WHITE" dengan bahan sebagai berikut\
                \n\nMaterial: "ORANGE"%d/400\
                \n"WHITE"Besi: "ORANGE"%d/350\
                \n"WHITE"Tembaga: "ORANGE"%d/250\
                \n"WHITE"Berlian: "ORANGE"%d/8\
                \n"WHITE"Baja: "ORANGE"%d/75\
                \n"WHITE"Alumunium: "ORANGE"%d/150\
                \n"WHITE"Kaca: "ORANGE"%d/30\
                \n"WHITE"Kayu Kemas: "ORANGE"%d/100\
                \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Besi"),
                Inventory_Count(playerid, "Tembaga"), Inventory_Count(playerid, "Berlian"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), 
                Inventory_Count(playerid, "Kayu Kemas"));
                ShowPlayerDialog(playerid, DIALOG_CRAFTINGCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
            }
            case 4: // AK
            {
                format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"AK47"WHITE" dengan bahan sebagai berikut\
                \n\nMaterial: "ORANGE"%d/350\
                \n"WHITE"Kayu Kemas: "ORANGE"%d/200\
                \n"WHITE"Baja: "ORANGE"%d/150\
                \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ?)", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kayu Kemas"), 
                Inventory_Count(playerid, "Baja"));
                ShowPlayerDialog(playerid, DIALOG_CRAFTINGCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
            }
            case 5: // TEC
            {
                format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Tec-9"WHITE" dengan bahan sebagai berikut\
                \n\nMaterial: "ORANGE"%d/450\
                \n"WHITE"Besi: "ORANGE"%d/100\
                \n"WHITE"Baja: "ORANGE"%d/75\
                \n"WHITE"Alumunium: "ORANGE"%d/60\
                \n"WHITE"Tembaga: "ORANGE"%d/500\
                \n"WHITE"Emas: "ORANGE"%d/30\n\
                \n"WHITE"Berlian: "ORANGE"%d/10\
                \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ?)",
                Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Besi"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Tembaga"),
                Inventory_Count(playerid, "Emas"), Inventory_Count(playerid, "Berlian"));
                ShowPlayerDialog(playerid, DIALOG_CRAFTINGCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
            }
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kata sandi yang anda masukkan salah!");
        AccountData[playerid][pTempValue] = -1;
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_CRAFTING:
        {
            if(!response) return 1;
            if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level Anda tidak cukup! (Min: 15)");
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dalam Family!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!, tidak dapat crafting!");
            
            static jskc[1056];
            switch(listitem)
            {
                case 0:// Kevlar
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Kevlar"WHITE" dengan bahan sebagai berikut:\
                    \n\nMaterial: "ORANGE"%d/50\
                    \n"WHITE"Besi: "ORANGE"%d/100\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/100\
                    \n"WHITE"Pakaian: "ORANGE"%d/100\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Besi"),
                    Inventory_Count(playerid, "Kayu Kemas"), Inventory_Count(playerid, "Pakaian"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 1:// Colt
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Colt 45"WHITE" dengan bahan sebagai berikut:\
                    \n\nMaterial: "ORANGE"%d/80\
                    \n"WHITE"Tembaga: "ORANGE"%d/120\
                    \n"WHITE"Baja: "ORANGE"%d/25\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/8\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ?)", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Tembaga"),
                    Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 2:// Desert Eagle
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Desert Eagle"WHITE" dengan bahan sebagai berikut\
                    \n\nMaterial: "ORANGE"%d/250\
                    \n"WHITE"Baja: "ORANGE"%d/60\
                    \n"WHITE"Kaca: "ORANGE"%d/10\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/20\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Baja"),
                    Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 3:// Shotgun
                {
                    Dialog_Show(playerid, DIALOG_CRAFTPASS, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Crafting Password",
                    "Mohon masukkan kata kunci / sandi jika ingin Crafting senjata tersebut dengan benar:", "Input", "Batal");
                }
                case 4:// AK47
                {
                    Dialog_Show(playerid, DIALOG_CRAFTPASS, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Crafting Password",
                    "Mohon masukkan kata kunci / sandi jika ingin Crafting senjata tersebut dengan benar:", "Input", "Batal");
                }
                case 5:// TEC-9
                {
                    Dialog_Show(playerid, DIALOG_CRAFTPASS, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Crafting Password",
                    "Mohon masukkan kata kunci / sandi jika ingin Crafting senjata tersebut dengan benar:", "Input", "Batal");
                }
            }
            AccountData[playerid][pTempValue] = listitem;
        }
        case DIALOG_CRAFTINGCLIP:
        {
            if(!response) return 1;
            if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level Anda tidak cukup! (Min: 15)");
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dalam Family!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!, tidak dapat crafting!");
            
            static jskc[1056];
            switch(listitem)
            {
                case 0:// Clip de
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip DE"WHITE" dengan bahan sebagai berikut:\
                    \n\nMaterial: "ORANGE"%d/50\
                    \n"WHITE"Besi: "ORANGE"%d/100\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Besi"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 1:// cLIP SLC
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip SLC"WHITE" dengan bahan sebagai berikut:\
                    \n\nMaterial: "ORANGE"%d/80\
                    \n"WHITE"Baja: "ORANGE"%d/25\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ?)", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Baja"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 2:// Clip Colt
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip Colt"WHITE" dengan bahan sebagai berikut\
                    \n"WHITE"Baja: "ORANGE"%d/60\
                    \n"WHITE"Kaca: "ORANGE"%d/10\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/20\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Baja"),
                    Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 3:// Clip SG
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip SG"WHITE" dengan bahan sebagai berikut:\
                    \n\nMaterial: "ORANGE"%d/50\
                    \n"WHITE"Besi: "ORANGE"%d/100\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/100\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Besi"),
                    Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 4:// Clip SOS
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip SOS"WHITE" dengan bahan sebagai berikut:\
                    \n\nMaterial: "ORANGE"%d/50\
                    \n"WHITE"Besi: "ORANGE"%d/100\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/100\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Besi"),
                    Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 5:// Clip AK
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip AK-47"WHITE" dengan bahan sebagai berikut:\
                    \n\nMaterial: "ORANGE"%d/50\
                    \n"WHITE"Besi: "ORANGE"%d/100\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/100\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Besi"),
                    Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 6:// Clip Uzi
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip UZi"WHITE" dengan bahan sebagai berikut\
                    \n\nMaterial: "ORANGE"%d/250\
                    \n"WHITE"Baja: "ORANGE"%d/60\
                    \n"WHITE"Kaca: "ORANGE"%d/10\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/20\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Baja"),
                    Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
                case 7:// Clip Tec
                {
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Clip UZi"WHITE" dengan bahan sebagai berikut\
                    \n\nMaterial: "ORANGE"%d/250\
                    \n"WHITE"Baja: "ORANGE"%d/60\
                    \n"WHITE"Kaca: "ORANGE"%d/10\
                    \n"WHITE"Kayu Kemas: "ORANGE"%d/20\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Baja"),
                    Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Kayu Kemas"));
                    ShowPlayerDialog(playerid, DIALOG_CRAFTINGCLIPCONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Crafting", jskc, "Iya", "Tidak");
                }
            }
            AccountData[playerid][pTempValue] = listitem;
        }
        case DIALOG_CRAFTINGCLIPCONF:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan");
            switch(AccountData[playerid][pTempValue])
            {
                case 0: //Clip De
				{
					if(Inventory_Count(playerid, "Material") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!.");
					if(Inventory_Count(playerid, "Besi") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!.");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerCrafting[playerid] = SetTimerEx("ClipDe", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 1: // cLIP SLC
				{
                    if(Inventory_Count(playerid, "Material") < 80) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 80!");
                    if(Inventory_Count(playerid, "Baja") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 25!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("ClipSlc", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 2: // Clip Colt
				{
                    if(Inventory_Count(playerid, "Baja") < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
                    if(Inventory_Count(playerid, "Kaca") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kaca tidak cukup, butuh 10!");
                    if(Inventory_Count(playerid, "Kayu Kemas") < 20) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 20!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("ClipColt", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 3: // Clip SG
				{
					if(Inventory_Count(playerid, "Material") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!.");
					if(Inventory_Count(playerid, "Besi") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!.");
					if(Inventory_Count(playerid, "Kayu Kemas") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!.");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerCrafting[playerid] = SetTimerEx("ClipSG", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
                case 4: // Clip SOS
				{
					if(Inventory_Count(playerid, "Material") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!.");
					if(Inventory_Count(playerid, "Besi") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!.");
					if(Inventory_Count(playerid, "Kayu Kemas") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!.");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerCrafting[playerid] = SetTimerEx("ClipSOS", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
                case 5: // Clip AK-47
				{
					if(Inventory_Count(playerid, "Material") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!.");
					if(Inventory_Count(playerid, "Besi") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!.");
					if(Inventory_Count(playerid, "Kayu Kemas") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!.");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerCrafting[playerid] = SetTimerEx("ClipAK", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
                case 6: // Clip Uzi
				{
                    if(Inventory_Count(playerid, "Material") < 250) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 250!");
                    if(Inventory_Count(playerid, "Baja") < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
                    if(Inventory_Count(playerid, "Kaca") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kaca tidak cukup, butuh 10!");
                    if(Inventory_Count(playerid, "Kayu Kemas") < 20) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 20!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("ClipUzi", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
                case 7: // Clip Tec
				{
                    if(Inventory_Count(playerid, "Material") < 250) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 250!");
                    if(Inventory_Count(playerid, "Baja") < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
                    if(Inventory_Count(playerid, "Kaca") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kaca tidak cukup, butuh 10!");
                    if(Inventory_Count(playerid, "Kayu Kemas") < 20) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 20!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("ClipTec", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
            }
        }
        case DIALOG_CRAFTINGCONF:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan");
            switch(AccountData[playerid][pTempValue])
            {
                case 0: //kevlar
				{
					if(Inventory_Count(playerid, "Material") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 50!.");
					if(Inventory_Count(playerid, "Besi") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!.");
					if(Inventory_Count(playerid, "Kayu Kemas") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!.");
                    if(Inventory_Count(playerid, "Pakaian") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pakaian tidak cukup, butuh 100!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerCrafting[playerid] = SetTimerEx("Kevlar", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 1: // Colt-45
				{
                    if(Inventory_Count(playerid, "Material") < 80) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 80!");
                    if(Inventory_Count(playerid, "Tembaga") < 120) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga tidak cukup, butuh 120!");
                    if(Inventory_Count(playerid, "Baja") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 25!");
                    if(Inventory_Count(playerid, "Kayu Kemas") < 8) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 8!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("Colt", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 2: // Desert Eagle
				{
                    if(Inventory_Count(playerid, "Material") < 250) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 250!");
                    if(Inventory_Count(playerid, "Baja") < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 60!");
                    if(Inventory_Count(playerid, "Kaca") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kaca tidak cukup, butuh 10!");
                    if(Inventory_Count(playerid, "Kayu Kemas") < 20) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 20!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("DesertE", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 3: // Shotgun
				{
                    if(Inventory_Count(playerid, "Material") < 400) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 400!");
                    if(Inventory_Count(playerid, "Besi") < 350) return ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 350!");
                    if(Inventory_Count(playerid, "Tembaga") < 250) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga tidak cukup, butuh 250!");
                    if(Inventory_Count(playerid, "Berlian") < 8) return ShowTDN(playerid, NOTIFICATION_ERROR, "Berlian tidak cukup, butuh 8!");
                    if(Inventory_Count(playerid, "Baja") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 75!");
                    if(Inventory_Count(playerid, "Alumunium") < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Alumunium tidak cukup, butuh 150!");
                    if(Inventory_Count(playerid, "Kaca") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kaca tidak cukup, butuh 30!");
                    if(Inventory_Count(playerid, "Kayu Kemas") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 100!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("Shotgun", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 4: // Ak-47
				{
                    if(Inventory_Count(playerid, "Material") < 350) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 350!");
                    if(Inventory_Count(playerid, "Kayu Kemas") < 200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Kemas tidak cukup, butuh 200!");
                    if(Inventory_Count(playerid, "Baja") < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 150!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("Ak47", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
				case 5: // TEC-9
				{
                    if(Inventory_Count(playerid, "Material") < 450) return ShowTDN(playerid, NOTIFICATION_ERROR, "Material tidak cukup, butuh 450!");
                    if(Inventory_Count(playerid, "Besi") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Besi tidak cukup, butuh 100!");
                    if(Inventory_Count(playerid, "Baja") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Baja tidak cukup, butuh 75!");
                    if(Inventory_Count(playerid, "Alumunium") < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Alumunium tidak cukup, butuh 60!");
                    if(Inventory_Count(playerid, "Tembaga") < 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga tidak cukup, butuh 500!");
                    if(Inventory_Count(playerid, "Emas") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Emas tidak cukup, butuh 30!");
                    if(Inventory_Count(playerid, "Berlian") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Berlian tidak cukup, butuh 10!");

                    AccountData[playerid][ActivityTime] = 1;
					pTimerCrafting[playerid] = SetTimerEx("Tec9", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "CRAFTING");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
				}
            }
        }
    }
    return 0;
}