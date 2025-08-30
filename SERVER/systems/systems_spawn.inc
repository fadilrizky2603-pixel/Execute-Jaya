#include <YSI_Coding\y_hooks>
new PlayerText: Spawntextdraws[MAX_PLAYERS][10];

CreateSpawnTextdraws(playerid)
{
    Spawntextdraws[playerid][0] = CreatePlayerTextDraw(playerid, 147.000, 181.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][0], 92.000, 21.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][0], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][0], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][0], 255);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][0], 1);

    Spawntextdraws[playerid][1] = CreatePlayerTextDraw(playerid, 147.000, 205.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][1], 92.000, 21.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][1], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][1], 200);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][1], 255);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][1], 1);

    Spawntextdraws[playerid][2] = CreatePlayerTextDraw(playerid, 147.000, 229.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][2], 92.000, 21.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][2], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][2], 200);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][2], 255);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][2], 1);

    Spawntextdraws[playerid][3] = CreatePlayerTextDraw(playerid, 147.000, 253.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][3], 92.000, 21.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][3], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][3], 200);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][3], 255);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][3], 1);

    Spawntextdraws[playerid][4] = CreatePlayerTextDraw(playerid, 147.000, 277.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][4], 92.000, 21.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][4], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][4], 200);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][4], 255);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][4], 1);

    Spawntextdraws[playerid][5] = CreatePlayerTextDraw(playerid, 159.000, 184.000, "> Tombol Spawn <");
    PlayerTextDrawLetterSize(playerid, Spawntextdraws[playerid][5], 0.219, 1.500);
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][5], 388.000, 10.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][5], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][5], 255);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][5], 150);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, Spawntextdraws[playerid][5], 1);

    Spawntextdraws[playerid][6] = CreatePlayerTextDraw(playerid, 154.000, 207.000, "Bandara Kota Happy");
    PlayerTextDrawLetterSize(playerid, Spawntextdraws[playerid][6], 0.219, 1.500);
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][6], 388.000, 10.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][6], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][6], 150);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, Spawntextdraws[playerid][6], 1);

    Spawntextdraws[playerid][7] = CreatePlayerTextDraw(playerid, 162.000, 231.000, "Pelabuhan Merak");
    PlayerTextDrawLetterSize(playerid, Spawntextdraws[playerid][7], 0.219, 1.500);
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][7], 388.000, 10.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][7], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][7], 150);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, Spawntextdraws[playerid][7], 1);

    Spawntextdraws[playerid][8] = CreatePlayerTextDraw(playerid, 168.000, 255.000, "Rusun Pribadi");
    PlayerTextDrawLetterSize(playerid, Spawntextdraws[playerid][8], 0.219, 1.500);
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][8], 388.000, 10.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][8], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][8], 150);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, Spawntextdraws[playerid][8], 1);

    Spawntextdraws[playerid][9] = CreatePlayerTextDraw(playerid, 167.000, 279.000, "Rumah Pribadi");
    PlayerTextDrawLetterSize(playerid, Spawntextdraws[playerid][9], 0.219, 1.500);
    PlayerTextDrawTextSize(playerid, Spawntextdraws[playerid][9], 388.000, 10.000);
    PlayerTextDrawAlignment(playerid, Spawntextdraws[playerid][9], 1);
    PlayerTextDrawColor(playerid, Spawntextdraws[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, Spawntextdraws[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, Spawntextdraws[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, Spawntextdraws[playerid][9], 150);
    PlayerTextDrawFont(playerid, Spawntextdraws[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, Spawntextdraws[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, Spawntextdraws[playerid][9], 1);
}

hook OnPlayerConnect(playerid)
{
    CreateSpawnTextdraws(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    for(new x = 0; x < 10; x++)
    {
        PlayerTextDrawDestroy(playerid, Spawntextdraws[playerid][x]);
    }
    return 1;
}

ShowSpawnTextdraws(playerid)
{
    for(new x = 0; x < 10; x++)
    {
        PlayerTextDrawShow(playerid, Spawntextdraws[playerid][x]);
    }
    SelectTextDraw(playerid, 0xFF9999FF);
    Info(playerid, "Gunakan "VERONA"'/cursor'"WHITE" jika cursor menghilang / textdraw tidak dapat ditekan");
    return 1;
}

HideSpawnTextdraws(playerid)
{
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][0]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][1]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][2]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][3]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][4]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][5]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][6]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][7]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][8]);
    PlayerTextDrawHide(playerid, Spawntextdraws[playerid][9]);
    CancelSelectTextDraw(playerid);
    return 1;
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
    if(textid == Spawntextdraws[playerid][6]) // Bandara
    {
        SetPVarInt(playerid, "SelectSpawn", 1); // Bandara
        SetPlayerCameraPos(playerid, 1665.321, -2295.758, 168.306);
        SetPlayerCameraLookAt(playerid, 1665.319, -2295.322, 163.325);
        InterpolateCameraPos(playerid, 1665.321, -2295.758, 168.306+150.0, 1665.321, -2295.758, 168.306, 2500, CAMERA_MOVE);
        PlayerPlaySound(playerid, 1054, 0, 0, 0);
    }
    if(textid == Spawntextdraws[playerid][7]) // pelabuhan
    {
        SetPVarInt(playerid, "SelectSpawn", 2); //pelabuhan
        SetPlayerCameraPos(playerid, 2736.289, -2453.198, 164.569);
        SetPlayerCameraLookAt(playerid, 2736.725, -2453.193, 159.588);
        InterpolateCameraPos(playerid, 2736.289, -2453.198, 164.569+150.0, 2736.289, -2453.198, 164.569, 2500, CAMERA_MOVE);
        PlayerPlaySound(playerid, 1054, 0, 0, 0);
    }
    if(textid == Spawntextdraws[playerid][8]) //rusun
    {
        if(AccountData[playerid][pOwnedRusun] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki rusun!");
        SetPVarInt(playerid, "SelectSpawn", 3); //rusun
        foreach(new id : Rusun)
        {
            if(RusunData[id][rusunOwnerID] == AccountData[playerid][pID])
            {
                SetPlayerCameraPos(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 120.0);
                SetPlayerCameraLookAt(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 90.0);
                InterpolateCameraPos(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 200.0, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 120.0, 2500, CAMERA_MOVE);
                PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
            }
        }
    }
    if(textid == Spawntextdraws[playerid][9]) // rumah pribadi
    {
        if(AccountData[playerid][pOwnedHouse] == -1 && AccountData[playerid][pFriendHouseID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rumah!");
        SetPVarInt(playerid, "SelectSpawn", 4); // Rumah
        foreach(new hid : House)
        {
            if(HouseData[hid][hsOwnerID] == AccountData[playerid][pID] || AccountData[playerid][pFriendHouseID] == hid)
            {
                SetPlayerCameraPos(playerid, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 120.0);
                SetPlayerCameraLookAt(playerid, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 90.0);
                InterpolateCameraPos(playerid, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 200.0, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 120.0, 2500, CAMERA_MOVE);
                PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
            }
        }
    }
    if(textid == Spawntextdraws[playerid][5]) // spawn
    {
        if(GetPVarInt(playerid, "SelectSpawn") == 1) // Bandara
        {
            new rand = random(sizeof(SpawnBandara));
            AccountData[playerid][pPosX] = SpawnBandara[rand][0];
            AccountData[playerid][pPosY] = SpawnBandara[rand][1];
            AccountData[playerid][pPosZ] = SpawnBandara[rand][2];
            AccountData[playerid][pPosA] = SpawnBandara[rand][3];
            SetPlayerInteriorEx(playerid, 0);
            SetPlayerVirtualWorldEx(playerid, 0);

            SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
            HideSpawnTextdraws(playerid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Bandara.");
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 2) // pelabuhan
        {
            new rand = random(sizeof(SpawnPelabuhan));
            AccountData[playerid][pPosX] = SpawnPelabuhan[rand][0];
            AccountData[playerid][pPosY] = SpawnPelabuhan[rand][1];
            AccountData[playerid][pPosZ] = SpawnPelabuhan[rand][2];
            AccountData[playerid][pPosA] = SpawnPelabuhan[rand][3];
            SetPlayerInteriorEx(playerid, 0);
            SetPlayerVirtualWorldEx(playerid, 0);

            SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
            HideSpawnTextdraws(playerid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Pelabuhan Merak.");
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 3) // Rusun Pribadi
        {
            if(AccountData[playerid][pOwnedRusun] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki rusun!");
            foreach(new rsid : Rusun)
            {
                if(RusunData[rsid][rusunOwnerID] == AccountData[playerid][pID])
                {
                    AccountData[playerid][pPosX] =  RusunData[rsid][rusunExtPos][0];
                    AccountData[playerid][pPosY] =  RusunData[rsid][rusunExtPos][1];
                    AccountData[playerid][pPosZ] =  RusunData[rsid][rusunExtPos][2];
                    AccountData[playerid][pPosA] =  RusunData[rsid][rusunExtPos][3];
                    SetPlayerInteriorEx(playerid, 0);
                    SetPlayerVirtualWorldEx(playerid, 0);

                    SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
                    HideSpawnTextdraws(playerid);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Rusun Pribadi.");
                }
            }
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 4) // Rumah Pribadi
        {
            if(AccountData[playerid][pOwnedHouse] == -1 && AccountData[playerid][pFriendHouseID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rumah!");
            foreach(new hid : House)
            {
                if(HouseData[hid][hsOwnerID] == AccountData[playerid][pID] || AccountData[playerid][pFriendHouseID] == hid)
                {
                    AccountData[playerid][pPosX] =  HouseData[hid][hsExtPos][0];
                    AccountData[playerid][pPosY] =  HouseData[hid][hsExtPos][1];
                    AccountData[playerid][pPosZ] =  HouseData[hid][hsExtPos][2];
                    AccountData[playerid][pPosA] =  HouseData[hid][hsExtPos][3];
                    SetPlayerInteriorEx(playerid, 0);
                    SetPlayerVirtualWorldEx(playerid, 0);

                    SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
                    HideSpawnTextdraws(playerid);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Rumah Pribadi.");
                }
            }
        }
        else 
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum menetapkan lokasi spawn!");
        }
        SetPVarInt(playerid, "SelectSpawn", 0);
        AccountData[playerid][playerClickSpawn] = 1;
        // SetPVarInt(playerid, "SpawnExpired", 1);
    }
    return 1;
}