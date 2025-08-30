#include <YSI_Coding\y_hooks>

new SelectVeh[MAX_PLAYERS] = {0, ...};
new STREAMER_TAG_CP:ShowroomCheckpoint;
new PlayerText: ATRP_ShowroomTD[MAX_PLAYERS][15];

ATRPShowroomTD(playerid)
{
    ATRP_ShowroomTD[playerid][0] = CreatePlayerTextDraw(playerid, 220.000, 350.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][0], 42.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][0], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][0], 1);

    ATRP_ShowroomTD[playerid][1] = CreatePlayerTextDraw(playerid, 221.000, 352.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][1], 40.000, 21.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][1], 943210495);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][1], 1);

    ATRP_ShowroomTD[playerid][2] = CreatePlayerTextDraw(playerid, 378.000, 349.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][2], 42.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][2], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][2], 1);

    ATRP_ShowroomTD[playerid][3] = CreatePlayerTextDraw(playerid, 379.000, 351.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][3], 40.000, 21.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][3], 943210495);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][3], 1);

    ATRP_ShowroomTD[playerid][4] = CreatePlayerTextDraw(playerid, 282.000, 341.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][4], 76.000, 43.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][4], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][4], 1);

    ATRP_ShowroomTD[playerid][5] = CreatePlayerTextDraw(playerid, 283.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][5], 74.000, 39.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][5], 943210495);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][5], 1);

    ATRP_ShowroomTD[playerid][6] = CreatePlayerTextDraw(playerid, 336.000, 399.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][6], 53.000, 27.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][6], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][6], 1);

    ATRP_ShowroomTD[playerid][7] = CreatePlayerTextDraw(playerid, 337.000, 401.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][7], 51.000, 23.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][7], 1018393087);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][7], 1);

    ATRP_ShowroomTD[playerid][8] = CreatePlayerTextDraw(playerid, 258.000, 399.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][8], 53.000, 27.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][8], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][8], 1);

    ATRP_ShowroomTD[playerid][9] = CreatePlayerTextDraw(playerid, 259.000, 401.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][9], 51.000, 23.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][9], -16776961);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][9], 1);

    ATRP_ShowroomTD[playerid][10] = CreatePlayerTextDraw(playerid, 240.000, 352.000, "<<");
    PlayerTextDrawLetterSize(playerid, ATRP_ShowroomTD[playerid][10], 0.300, 2.199);
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][10], 12.000, 38.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][10], 2);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][10], 150);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_ShowroomTD[playerid][10], 1);

    ATRP_ShowroomTD[playerid][11] = CreatePlayerTextDraw(playerid, 399.000, 352.000, ">>");
    PlayerTextDrawLetterSize(playerid, ATRP_ShowroomTD[playerid][11], 0.300, 2.199);
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][11], 12.000, 38.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][11], 2);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][11], 150);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_ShowroomTD[playerid][11], 1);

    ATRP_ShowroomTD[playerid][12] = CreatePlayerTextDraw(playerid, 363.000, 405.000, "buy");
    PlayerTextDrawLetterSize(playerid, ATRP_ShowroomTD[playerid][12], 0.339, 1.599);
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][12], 13.000, 43.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][12], 2);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][12], 150);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][12], 3);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_ShowroomTD[playerid][12], 1);

    ATRP_ShowroomTD[playerid][13] = CreatePlayerTextDraw(playerid, 285.000, 405.000, "Cancel");
    PlayerTextDrawLetterSize(playerid, ATRP_ShowroomTD[playerid][13], 0.339, 1.599);
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][13], 13.000, 43.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][13], 2);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][13], 150);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][13], 3);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_ShowroomTD[playerid][13], 1);

    ATRP_ShowroomTD[playerid][14] = CreatePlayerTextDraw(playerid, 321.000, 347.000, "Sultan~n~~g~$5,000");
    PlayerTextDrawLetterSize(playerid, ATRP_ShowroomTD[playerid][14], 0.339, 1.599);
    PlayerTextDrawTextSize(playerid, ATRP_ShowroomTD[playerid][14], 13.000, 43.000);
    PlayerTextDrawAlignment(playerid, ATRP_ShowroomTD[playerid][14], 2);
    PlayerTextDrawColor(playerid, ATRP_ShowroomTD[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_ShowroomTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_ShowroomTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_ShowroomTD[playerid][14], 150);
    PlayerTextDrawFont(playerid, ATRP_ShowroomTD[playerid][14], 3);
    PlayerTextDrawSetProportional(playerid, ATRP_ShowroomTD[playerid][14], 1);
    return 1;
}

Toggle_ShowroomTD(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 15; i ++) PlayerTextDrawHide(playerid, ATRP_ShowroomTD[playerid][i]);
    }
    else
    {
        for(new i; i < 15; i ++) PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][i]);
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    ATRPShowroomTD(playerid);
    SetPVarInt(playerid, "SelectShowroomID", 0);
    SelectVeh[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(GetPVarInt(playerid, "SelectShowroomID") != 0)
    {
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
    }
    for(new x; x < 15; x ++) PlayerTextDrawDestroy(playerid, ATRP_ShowroomTD[playerid][x]);
    return 1;
}

hook OnScriptInit()
{
    ShowroomCheckpoint = CreateDynamicCP(1042.3744, 234.2350, 15.5392, 2.0, -1, 2, -1, 10.0);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == ShowroomCheckpoint)
    {
        ShowKey(playerid, "[Y] Menu Showroom");
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == ShowroomCheckpoint)
    {
        HideShortKey(playerid);
    }
    return 1;
}

new MotorShowroom[10] = 
{
    509, 481, 510, 462, 461, 581, 521, 463, 468, 586
};

new TrukShowroom[8] = 
{
    422, 482, 478, 554, 543, 440, 413, 418
};

new SuvShowroom[7] = 
{
    579, 400, 404, 589, 505, 479, 458
};

new ClassicShowroom[6] = 
{
    536, 575, 534, 567, 576, 412
};

new CompactShowroom[15] = 
{
    602, 496, 401, 518, 527, 589, 419, 587, 533, 526, 545, 474, 517, 419, 600
};

new LuxuryShowroom[18] = 
{
    445, 507, 585, 466, 492, 546, 551, 516, 426, 467, 547, 580, 550, 566, 540, 421, 529, 560
};

LuxuryCost(playerid)
{
    if(LuxuryShowroom[SelectVeh[playerid]] == 445) return 23450;
    if(LuxuryShowroom[SelectVeh[playerid]] == 507) return 23250;
    if(LuxuryShowroom[SelectVeh[playerid]] == 585) return 23400;
    if(LuxuryShowroom[SelectVeh[playerid]] == 466) return 23150;
    if(LuxuryShowroom[SelectVeh[playerid]] == 492) return 22650;
    if(LuxuryShowroom[SelectVeh[playerid]] == 546) return 22750;
    if(LuxuryShowroom[SelectVeh[playerid]] == 551) return 22900;
    if(LuxuryShowroom[SelectVeh[playerid]] == 516) return 23050;
    if(LuxuryShowroom[SelectVeh[playerid]] == 426) return 23500;
    if(LuxuryShowroom[SelectVeh[playerid]] == 467) return 22900;
    if(LuxuryShowroom[SelectVeh[playerid]] == 547) return 22700;
    if(LuxuryShowroom[SelectVeh[playerid]] == 580) return 23050;
    if(LuxuryShowroom[SelectVeh[playerid]] == 550) return 23850;
    if(LuxuryShowroom[SelectVeh[playerid]] == 566) return 23000;
    if(LuxuryShowroom[SelectVeh[playerid]] == 540) return 22900;
    if(LuxuryShowroom[SelectVeh[playerid]] == 421) return 23100;
    if(LuxuryShowroom[SelectVeh[playerid]] == 529) return 22500;
    if(LuxuryShowroom[SelectVeh[playerid]] == 560) return 27500;

    return -1;
}

CompactCost(playerid)
{
    if(CompactShowroom[SelectVeh[playerid]] == 602) return 23450;
    if(CompactShowroom[SelectVeh[playerid]] == 496) return 23250;
    if(CompactShowroom[SelectVeh[playerid]] == 401) return 23400;
    if(CompactShowroom[SelectVeh[playerid]] == 518) return 23150;
    if(CompactShowroom[SelectVeh[playerid]] == 527) return 22650;
    if(CompactShowroom[SelectVeh[playerid]] == 589) return 22750;
    if(CompactShowroom[SelectVeh[playerid]] == 419) return 22900;
    if(CompactShowroom[SelectVeh[playerid]] == 587) return 23050;
    if(CompactShowroom[SelectVeh[playerid]] == 533) return 23500;
    if(CompactShowroom[SelectVeh[playerid]] == 526) return 22900;
    if(CompactShowroom[SelectVeh[playerid]] == 545) return 22700;
    if(CompactShowroom[SelectVeh[playerid]] == 474) return 23050;
    if(CompactShowroom[SelectVeh[playerid]] == 517) return 23850;
    if(CompactShowroom[SelectVeh[playerid]] == 419) return 23000;
    if(CompactShowroom[SelectVeh[playerid]] == 600) return 22900;
    return -1;
}

ClassicCost(playerid)
{
    if(ClassicShowroom[SelectVeh[playerid]] == 536) return 22150;
    if(ClassicShowroom[SelectVeh[playerid]] == 575) return 22700;
    if(ClassicShowroom[SelectVeh[playerid]] == 534) return 22350;
    if(ClassicShowroom[SelectVeh[playerid]] == 567) return 22000;
    if(ClassicShowroom[SelectVeh[playerid]] == 535) return 22300;
    if(ClassicShowroom[SelectVeh[playerid]] == 576) return 21950;
    if(ClassicShowroom[SelectVeh[playerid]] == 412) return 22100;

    return -1;
}

TrukCost(playerid)
{
    if(TrukShowroom[SelectVeh[playerid]] == 422) return 22250;
    if(TrukShowroom[SelectVeh[playerid]] == 482) return 22500;
    if(TrukShowroom[SelectVeh[playerid]] == 478) return 21900;
    if(TrukShowroom[SelectVeh[playerid]] == 554) return 22750;
    if(TrukShowroom[SelectVeh[playerid]] == 543) return 22100;
    if(TrukShowroom[SelectVeh[playerid]] == 440) return 21800;
    if(TrukShowroom[SelectVeh[playerid]] == 413) return 22000;
    if(TrukShowroom[SelectVeh[playerid]] == 418) return 22000;
    return -1;
}

SuvCost(playerid)
{
    if(SuvShowroom[SelectVeh[playerid]] == 579) return 22250;
    if(SuvShowroom[SelectVeh[playerid]] == 400) return 22500;
    if(SuvShowroom[SelectVeh[playerid]] == 404) return 21900;
    if(SuvShowroom[SelectVeh[playerid]] == 589) return 22750;
    if(SuvShowroom[SelectVeh[playerid]] == 505) return 22100;
    if(SuvShowroom[SelectVeh[playerid]] == 479) return 21800;
    if(SuvShowroom[SelectVeh[playerid]] == 458) return 22000;
    return -1;
}

MotorCost(playerid)
{
    if(MotorShowroom[SelectVeh[playerid]] == 509) return 200;
    if(MotorShowroom[SelectVeh[playerid]] == 481) return 250;
    if(MotorShowroom[SelectVeh[playerid]] == 510) return 500;
    if(MotorShowroom[SelectVeh[playerid]] == 462) return 700;
    if(MotorShowroom[SelectVeh[playerid]] == 461) return 11100;
    if(MotorShowroom[SelectVeh[playerid]] == 581) return 11200;
    if(MotorShowroom[SelectVeh[playerid]] == 521) return 11450;
    if(MotorShowroom[SelectVeh[playerid]] == 463) return 11700;
    if(MotorShowroom[SelectVeh[playerid]] == 468) return 4000;
    if(MotorShowroom[SelectVeh[playerid]] == 586) return 11000;
    return -1;
}

/* Other Func */
VehicleTruckSelect(playerid)
{
    if(IsValidVehicle(ShowroomVeh[playerid]))
    {
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
    }

    ShowroomVeh[playerid] = CreateVehicle(TrukShowroom[SelectVeh[playerid]], 1027.7688, 237.1656, 15.2641, 324.3192, random(255), random(255), 60000, 0);
    LinkVehicleToInterior(ShowroomVeh[playerid], GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(ShowroomVeh[playerid], GetPlayerVirtualWorld(playerid));
    SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0);
    
    PutPlayerInVehicle(playerid, ShowroomVeh[playerid], 0);
    SetPlayerCameraPos(playerid, 1036.682, 242.037, 16.233);
    SetPlayerCameraLookAt(playerid, 1032.315, 239.626, 15.901);
    return 1;
}

VehicleSuvSelect(playerid)
{
    if(IsValidVehicle(ShowroomVeh[playerid]))
    {
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
    }

    ShowroomVeh[playerid] = CreateVehicle(SuvShowroom[SelectVeh[playerid]], 1027.7688, 237.1656, 15.2641, 324.3192, random(255), random(255), 60000, 0);
    LinkVehicleToInterior(ShowroomVeh[playerid], GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(ShowroomVeh[playerid], GetPlayerVirtualWorld(playerid));
    SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0);
    
    PutPlayerInVehicle(playerid, ShowroomVeh[playerid], 0);
    SetPlayerCameraPos(playerid, 1036.682, 242.037, 16.233);
    SetPlayerCameraLookAt(playerid, 1032.315, 239.626, 15.901);
}

VehicleMotorSelect(playerid)
{
    if(IsValidVehicle(ShowroomVeh[playerid]))
    {
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
    }

    ShowroomVeh[playerid] = CreateVehicle(MotorShowroom[SelectVeh[playerid]], 1027.7688, 237.1656, 15.2641, 324.3192, random(255), random(255), 60000, 0);
    LinkVehicleToInterior(ShowroomVeh[playerid], GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(ShowroomVeh[playerid], GetPlayerVirtualWorld(playerid));
    SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0);
    
    PutPlayerInVehicle(playerid, ShowroomVeh[playerid], 0);
    SetPlayerCameraPos(playerid, 1036.682, 242.037, 16.233);
    SetPlayerCameraLookAt(playerid, 1032.315, 239.626, 15.901);
}

VehicleLowriderSelect(playerid)
{
    if(IsValidVehicle(ShowroomVeh[playerid]))
    {
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
    }

    ShowroomVeh[playerid] = CreateVehicle(ClassicShowroom[SelectVeh[playerid]], 1027.7688, 237.1656, 15.2641, 324.3192, random(255), random(255), 60000, 0);
    LinkVehicleToInterior(ShowroomVeh[playerid], GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(ShowroomVeh[playerid], GetPlayerVirtualWorld(playerid));
    SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0);
    
    PutPlayerInVehicle(playerid, ShowroomVeh[playerid], 0);
    SetPlayerCameraPos(playerid, 1036.682, 242.037, 16.233);
    SetPlayerCameraLookAt(playerid, 1032.315, 239.626, 15.901);
}

VehicleCompactSelect(playerid)
{
    if(IsValidVehicle(ShowroomVeh[playerid]))
    {
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
    }

    ShowroomVeh[playerid] = CreateVehicle(CompactShowroom[SelectVeh[playerid]], 1027.7688, 237.1656, 15.2641, 324.3192, random(255), random(255), 60000, 0);
    LinkVehicleToInterior(ShowroomVeh[playerid], GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(ShowroomVeh[playerid], GetPlayerVirtualWorld(playerid));
    SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0);
    
    PutPlayerInVehicle(playerid, ShowroomVeh[playerid], 0);
    SetPlayerCameraPos(playerid, 1036.682, 242.037, 16.233);
    SetPlayerCameraLookAt(playerid, 1032.315, 239.626, 15.901);
}

VehicleLuxurySelect(playerid)
{
    if(IsValidVehicle(ShowroomVeh[playerid]))
    {
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
    }

    ShowroomVeh[playerid] = CreateVehicle(LuxuryShowroom[SelectVeh[playerid]], 1027.7688, 237.1656, 15.2641, 324.3192, random(255), random(255), 60000, 0);
    LinkVehicleToInterior(ShowroomVeh[playerid], GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(ShowroomVeh[playerid], GetPlayerVirtualWorld(playerid));
    SetValidVehicleHealth(ShowroomVeh[playerid], 1000.0);
    
    PutPlayerInVehicle(playerid, ShowroomVeh[playerid], 0);
    SetPlayerCameraPos(playerid, 1036.682, 242.037, 16.233);
    SetPlayerCameraLookAt(playerid, 1032.315, 239.626, 15.901);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInDynamicCP(playerid, ShowroomCheckpoint))
        {
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            EnableAntiCheatForPlayer(playerid, 4, false);
            
            ShowPlayerDialog(playerid, DIALOG_SHOWROOM_MENU, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Showroom",
            "Truk Ringan & Vans\
            \n"GRAY"SUV & Wagon\
            \nMotor & Sepeda\
            \n"GRAY"Classic & Lowrider\
            \n2 Pintu & Compact\
            \n"GRAY"4 Pintu & Luxury\
            \n"RED"(Jual Kendaraan Ke Negara)", "Pilih", "Batal");
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_SHOWROOM_MENU:
        {
            if(!response)
            {
                SetPVarInt(playerid, "SelectShowroomID", 0);
                EnableAntiCheatForPlayer(playerid, 4, true);
                return 1;
            }
            
            if(AccountData[playerid][pInjured])
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                return 1;
            }

            switch(listitem)
            {
                case 0: 
                {
                    SetPVarInt(playerid, "SelectShowroomID", 1); // truk
                    SetPlayerVirtualWorld(playerid, (playerid+1));
                    TogglePlayerControllable(playerid, 0);
                    VehicleTruckSelect(playerid);

                    PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(TrukShowroom[SelectVeh[playerid]]), FormatMoney(TrukCost(playerid))));
                    Toggle_ShowroomTD(playerid, true);
                    SelectTextDraw(playerid, 0xFF9999FF);
                }
                case 1: 
                {
                    SetPVarInt(playerid, "SelectShowroomID", 2); // SUV
                    SetPlayerVirtualWorld(playerid, (playerid+1));
                    TogglePlayerControllable(playerid, 0);
                    VehicleSuvSelect(playerid);

                    PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(SuvShowroom[SelectVeh[playerid]]), FormatMoney(SuvCost(playerid))));
                    Toggle_ShowroomTD(playerid, true);
                    SelectTextDraw(playerid, 0xFF9999FF);
                }
                case 2: 
                {
                    SetPVarInt(playerid, "SelectShowroomID", 3); // Motor
                    SetPlayerVirtualWorld(playerid, (playerid+1));
                    TogglePlayerControllable(playerid, 0);
                    VehicleMotorSelect(playerid);

                    PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(MotorShowroom[SelectVeh[playerid]]), FormatMoney(MotorCost(playerid))));
                    Toggle_ShowroomTD(playerid, true);
                    SelectTextDraw(playerid, 0xFF9999FF);
                }
                case 3: //
                {
                    SetPVarInt(playerid, "SelectShowroomID", 4); // Low ride
                    SetPlayerVirtualWorld(playerid, (playerid+1));
                    TogglePlayerControllable(playerid, 0);
                    VehicleLowriderSelect(playerid);

                    PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(ClassicShowroom[SelectVeh[playerid]]), FormatMoney(ClassicCost(playerid))));
                    Toggle_ShowroomTD(playerid, true);
                    SelectTextDraw(playerid, 0xFF9999FF);
                }
                case 4:
                {
                    SetPVarInt(playerid, "SelectShowroomID", 5); // Two Door
                    SetPlayerVirtualWorld(playerid, (playerid+1));
                    TogglePlayerControllable(playerid, 0);
                    VehicleCompactSelect(playerid);

                    PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(CompactShowroom[SelectVeh[playerid]]), FormatMoney(CompactCost(playerid))));
                    Toggle_ShowroomTD(playerid, true);
                    SelectTextDraw(playerid, 0xFF9999FF);
                }
                case 5:
                {
                    SetPVarInt(playerid, "SelectShowroomID", 6); // Luxury
                    SetPlayerVirtualWorld(playerid, (playerid+1));
                    TogglePlayerControllable(playerid, 0);
                    VehicleLuxurySelect(playerid);

                    PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(LuxuryShowroom[SelectVeh[playerid]]), FormatMoney(LuxuryCost(playerid))));
                    Toggle_ShowroomTD(playerid, true);
                    SelectTextDraw(playerid, 0xFF9999FF);
                }
                case 6: 
                {
                    ShowPlayerDialog(playerid, DIALOG_SHOWROOM_SELL, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Jual Kendaraan",
                    "Hai, kamu ingin menjual kendaraan?\n(Mohon masukkan VID Kendaraan anda yang ingin dijual di kolom bawah ini):", "Submit", "Batal");
                }
            }
        }
        case DIALOG_SHOWROOM_SELL:
        {
            if(!response)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
                EnableAntiCheatForPlayer(playerid, 4, true);
                return 1;
            }

            foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehExists])
            {
                if(strval(inputtext) == PlayerVehicle[i][pVehPhysic])
                {
                    if(!IsValidVehicle(PlayerVehicle[i][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak spawn!");
                    if(PlayerVehicle[i][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menjual kendaraan rental!");
                    if(PlayerVehicle[i][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                    if(PlayerVehicle[i][pVehFaction] > FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan milik instansi tidak dapat dijual di Showroom!");
                    if(!IsABicycle(PlayerVehicle[i][pVehPhysic]) && PlayerVehicle[i][pVehPlateOwn] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini belum memiliki plat!");
                    
                    new value = (PlayerVehicle[i][pVehPrice]/100)*50;
                    PlayerVehicle[i][pVehExists] = false;
                    DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
                    GiveMoney(playerid, value);
                    ShowItemBox(playerid, sprintf("Received %s", FormatMoney((PlayerVehicle[i][pVehPrice]/2))), "Uang", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Penjualan berhasil dilakukan.");

                    PlayerVehicle[i][pVehOwnerID] = -1;
                    PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;

                    new query[255];
                    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `player_vehicles` WHERE `id`=%d", PlayerVehicle[i][pVehID]);
                    mysql_tquery(g_SQL, query);
                    Iter_Remove(PvtVehicles, i); 
                }
            }
        }
    }
    return 1;
}


ShowroomVehicle_Create(ownerid, modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, cost)
{
    static vehicleid;
    if ((vehicleid = Iter_Free(PvtVehicles)) != cellmin)
    {
        Iter_Add(PvtVehicles, vehicleid);

        PlayerVehicle[vehicleid][pVehExists] = true;
        PlayerVehicle[vehicleid][pVehModelID] = modelid;
        PlayerVehicle[vehicleid][pVehOwnerID] = AccountData[ownerid][pID];
        format(PlayerVehicle[vehicleid][pVehPlate], 64, "-");

        PlayerVehicle[vehicleid][pVehPos][0] = x;
        PlayerVehicle[vehicleid][pVehPos][1] = y;
        PlayerVehicle[vehicleid][pVehPos][2] = z;
        PlayerVehicle[vehicleid][pVehPos][3] = angle;

        PlayerVehicle[vehicleid][pVehInsuranced] = false;
        PlayerVehicle[vehicleid][pVehImpounded] = false;

        PlayerVehicle[vehicleid][pVehColor1] = color1;
        PlayerVehicle[vehicleid][pVehColor2] = color2;
        PlayerVehicle[vehicleid][pVehPaintjob] = -1;

        PlayerVehicle[vehicleid][pVehLocked] = false;
        PlayerVehicle[vehicleid][pVehFuel] = MAX_FUEL_FULL;
        PlayerVehicle[vehicleid][pVehHealth] = 1000.0;
        PlayerVehicle[vehicleid][pVehRental] = -1;
        PlayerVehicle[vehicleid][pVehRentTime] = 0;
        PlayerVehicle[vehicleid][pVehParked] = -1;
        PlayerVehicle[vehicleid][pVehHouseGarage] = -1;
        PlayerVehicle[vehicleid][pVehHelipadGarage] = -1;
        PlayerVehicle[vehicleid][pVehFamiliesGarage] = -1;
        PlayerVehicle[vehicleid][pVehFactStored] = -1;
        PlayerVehicle[vehicleid][pVehFaction] = FACTION_NONE;

        PlayerVehicle[vehicleid][pVehPrice] = cost;
        PlayerVehicle[vehicleid][pVehNeon] = 0;
        PlayerVehicle[vehicleid][cTogNeon] = 0;
        
        PlayerVehicle[vehicleid][pVehDamage][0] = 0;
        PlayerVehicle[vehicleid][pVehDamage][1] = 0;
        PlayerVehicle[vehicleid][pVehDamage][2] = 0;
        PlayerVehicle[vehicleid][pVehDamage][3] = 0;

        PlayerVehicle[vehicleid][pVehPlateTime] = 0;
        PlayerVehicle[vehicleid][pVehPlateOwn] = 0;
        PlayerVehicle[vehicleid][pVehInterior] = 0;
        PlayerVehicle[vehicleid][pVehWorld] = 0;

        PlayerVehicle[vehicleid][pVehEngineUpgrade] = 0;
        PlayerVehicle[vehicleid][pVehBodyUpgrade] = 0;
        PlayerVehicle[vehicleid][pVehBodyRepair] = 0;
        
        PlayerVehicle[vehicleid][pVehBroken] = 0;

        PlayerVehicle[vehicleid][vehDonation] = 0;
        PlayerVehicle[vehicleid][pVehCapacity] = 0;
        
        PlayerVehicle[vehicleid][pVehWeapon][0] = 0;
        PlayerVehicle[vehicleid][pVehWeapon][1] = 0;
        PlayerVehicle[vehicleid][pVehWeapon][2] = 0;
        PlayerVehicle[vehicleid][pVehAmmo][0] = 0;
        PlayerVehicle[vehicleid][pVehAmmo][1] = 0;
        PlayerVehicle[vehicleid][pVehAmmo][2] = 0;
        PlayerVehicle[vehicleid][pVehDCTime] = 0;

        for(new j = 0; j < 17; j ++) {
            PlayerVehicle[vehicleid][pVehMod][j] = 0;
        }

        PlayerVehicle[vehicleid][pVehPhysic] = CreateVehicle(PlayerVehicle[vehicleid][pVehModelID], PlayerVehicle[vehicleid][pVehPos][0], PlayerVehicle[vehicleid][pVehPos][1], PlayerVehicle[vehicleid][pVehPos][2], PlayerVehicle[vehicleid][pVehPos][3], PlayerVehicle[vehicleid][pVehColor1], PlayerVehicle[vehicleid][pVehColor2], 600000);
        VehicleCore[PlayerVehicle[vehicleid][pVehPhysic]][vCoreFuel] = PlayerVehicle[vehicleid][pVehFuel];
        SetVehicleNumberPlate(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehPlate]);
        SetVehicleVirtualWorld(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehWorld]);
        LinkVehicleToInterior(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehInterior]);

        SetPlayerPositionEx(ownerid, 520.7665, -1287.1577, 17.9932, 199.5307, 1000);
        SetPlayerInteriorEx(ownerid, 0);
        SetPlayerVirtualWorldEx(ownerid, 0);
        AccountData[ownerid][pInDoor] = -1;
        AccountData[ownerid][pInHouse] = -1;
        AccountData[ownerid][pInRusun] = -1;
        AccountData[ownerid][pInFamily] = -1;
        AccountData[ownerid][pInBiz] = -1;
        SetCameraBehindPlayer(ownerid);
        CancelSelectTextDraw(ownerid);
        EnableAntiCheatForPlayer(ownerid, 4, true);

        mysql_tquery(g_SQL, "INSERT INTO `player_vehicles` (`PVeh_Faction`) VALUES('0')", "OnVehBuyCreated", "dd", ownerid, vehicleid);
        return vehicleid;
    }
    return -1;
}

/*ShowroomVehicle_Create(ownerid, modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, cost)
{
    new i = Iter_Free(PvtVehicles);
    if(i == INVALID_ITERATOR_SLOT) return printf("Tidak ada Iterator Free pada PvtVehicles");

    PlayerVehicle[i][pVehExists] = true;
    PlayerVehicle[i][pVehModelID] = modelid;
    PlayerVehicle[i][pVehOwnerID] = AccountData[ownerid][pID];
    format(PlayerVehicle[i][pVehPlate], 64, "-");

	PlayerVehicle[i][pVehPos][0] = x;
	PlayerVehicle[i][pVehPos][1] = y;
	PlayerVehicle[i][pVehPos][2] = z;
	PlayerVehicle[i][pVehPos][3] = angle;

	PlayerVehicle[i][pVehInsuranced] = false;
	PlayerVehicle[i][pVehImpounded] = false;

	PlayerVehicle[i][pVehColor1] = color1;
	PlayerVehicle[i][pVehColor2] = color2;
	PlayerVehicle[i][pVehPaintjob] = -1;

	PlayerVehicle[i][pVehLocked] = false;
	PlayerVehicle[i][pVehFuel] = MAX_FUEL_FULL;
	PlayerVehicle[i][pVehHealth] = 1000.0;
	PlayerVehicle[i][pVehRental] = -1;
	PlayerVehicle[i][pVehRentTime] = 0;
	PlayerVehicle[i][pVehParked] = -1;
	PlayerVehicle[i][pVehHouseGarage] = -1;
    PlayerVehicle[i][pVehHelipadGarage] = -1;
	PlayerVehicle[i][pVehFamiliesGarage] = -1;
	PlayerVehicle[i][pVehFactStored] = -1;
	PlayerVehicle[i][pVehFaction] = FACTION_NONE;

    PlayerVehicle[i][pVehPrice] = cost;
	PlayerVehicle[i][pVehNeon] = 0;
	PlayerVehicle[i][cTogNeon] = 0;
	
	PlayerVehicle[i][pVehDamage][0] = 0;
	PlayerVehicle[i][pVehDamage][1] = 0;
	PlayerVehicle[i][pVehDamage][2] = 0;
	PlayerVehicle[i][pVehDamage][3] = 0;

	PlayerVehicle[i][pVehPlateTime] = 0;
	PlayerVehicle[i][pVehPlateOwn] = 0;
	PlayerVehicle[i][pVehInterior] = 0;
	PlayerVehicle[i][pVehWorld] = 0;

    PlayerVehicle[i][pVehEngineUpgrade] = 0;
	PlayerVehicle[i][pVehBodyUpgrade] = 0;
	PlayerVehicle[i][pVehBodyRepair] = 0;
	
	PlayerVehicle[i][pVehBroken] = 0;

	PlayerVehicle[i][vehDonation] = 0;
	PlayerVehicle[i][pVehCapacity] = 0;
	
	PlayerVehicle[i][pVehWeapon][0] = 0;
	PlayerVehicle[i][pVehWeapon][1] = 0;
	PlayerVehicle[i][pVehWeapon][2] = 0;
	PlayerVehicle[i][pVehAmmo][0] = 0;
	PlayerVehicle[i][pVehAmmo][1] = 0;
	PlayerVehicle[i][pVehAmmo][2] = 0;
    PlayerVehicle[i][pVehDCTime] = 0;

    for(new j = 0; j < 17; j ++) {
        PlayerVehicle[i][pVehMod][j] = 0;
    }

    PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 600000, 0);
    VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
    SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
    SetVehicleVirtualWorld(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
    LinkVehicleToInterior(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);

    SetPlayerPositionEx(ownerid, 520.7665, -1287.1577, 17.9932, 199.5307, 1000);
    SetPlayerInteriorEx(ownerid, 0);
    SetPlayerVirtualWorldEx(ownerid, 0);
    AccountData[ownerid][pInDoor] = -1;
    AccountData[ownerid][pInHouse] = -1;
    AccountData[ownerid][pInRusun] = -1;
    AccountData[ownerid][pInFamily] = -1;
    AccountData[ownerid][pInBiz] = -1;
    SetCameraBehindPlayer(ownerid);
    CancelSelectTextDraw(ownerid);
    EnableAntiCheatForPlayer(ownerid, 4, true);

    Iter_Add(PvtVehicles, i);
    
    new cQuery[1048];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `player_vehicles` (`PVeh_OwnerID`, `PVeh_ModelID`, `PVeh_Price`, `PVeh_Fuel`, `PVeh_Health`, `PVeh_Plate`, `PVeh_Parked`, `PVeh_Housed`, `PVeh_Families`, `PVeh_FactionGarage`, `PVeh_Rental`, `PVeh_RentTime`, \
    `PVeh_PosX`, `PVeh_PosY`, `PVeh_PosZ`, `PVeh_PosA`, `PVeh_Color1`, `PVeh_Color2`, `PVeh_Paintjob`, `PVeh_World`, `PVeh_Interior`) VALUES ('%d', '%d', '%d', '%d', '%f', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d')",
    PlayerVehicle[i][pVehOwnerID], PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPrice], PlayerVehicle[i][pVehFuel], PlayerVehicle[i][pVehHealth], PlayerVehicle[i][pVehPlate], PlayerVehicle[i][pVehParked], PlayerVehicle[i][pVehHouseGarage], PlayerVehicle[i][pVehFamiliesGarage], PlayerVehicle[i][pVehFactStored],
    PlayerVehicle[i][pVehRental], PlayerVehicle[i][pVehRentTime], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], PlayerVehicle[i][pVehPaintjob], PlayerVehicle[i][pVehWorld], PlayerVehicle[i][pVehInterior]);
    mysql_tquery(g_SQL, cQuery, "OnVehBuyCreated", "ii", ownerid, i);
    return 1;
}*/