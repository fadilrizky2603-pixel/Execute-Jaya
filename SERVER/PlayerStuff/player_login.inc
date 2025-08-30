//login screen by ahmazuqi

#define Login::    Login_

enum e_Login {
    STREAMER_TAG_OBJECT:objectLogin,
};
new Login::screen[MAX_PLAYERS][e_Login];

FUNC::Login_Screen_Show(playerid, value)
{
    switch(value)
    {
        //bandara
        case 1:
        {   
            ClearAllChat(playerid);
            new wid = 200+AccountData[playerid][pID];
            TogglePlayerControllable(playerid, false);
            if(IsValidDynamicObject(Login::screen[playerid][objectLogin]))
                DestroyDynamicObject(Login::screen[playerid][objectLogin]);
            Login::screen[playerid][objectLogin] = CreateDynamicObject(1681, 1161.48, -2490.2, 66.7269, 0, 0, -89.8, wid, -1, -1);
            Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
            SetPlayerPos(playerid, 1291.9954,-2382.0916,21.6245);
            SetPlayerVirtualWorld(playerid, wid);
            MoveDynamicObject(Login::screen[playerid][objectLogin], 1362.21, -2489.5, 66.7269, 18.0, 0, 0, -89.8);
            SetPlayerCameraPos(playerid,1287.4884,-2386.6216,21.6686);
            SetPlayerCameraLookAt(playerid, 1161.48, -2490.2, 66.7269, CAMERA_CUT);
            SetTimerEx("MoveSceneLogin", 12000, false, "id", playerid, 1);
            InterpolateCameraLookAt(playerid, 1161.48, -2490.2, 66.7269, 1362.21, -2489.5, 66.7269, 10000, CAMERA_MOVE);
            
        }
        //pelabuhan
        case 2:
        {

        }
    }
    return 1;
}

FUNC::MoveSceneLogin(playerid, value)
{
    switch(value)
    {
        case 1:
        {
            new wid = 200+AccountData[playerid][pID];
            TogglePlayerControllable(playerid, false);
            if(IsValidDynamicObject(Login::screen[playerid][objectLogin]))
                DestroyDynamicObject(Login::screen[playerid][objectLogin]);
            Login::screen[playerid][objectLogin] = CreateDynamicObject(1681, 1487.52, -2494.01, 14.7547, 0 , 0, -90.2, wid, -1, -1);
            Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
            SetPlayerPos(playerid, 1606.1193,-2458.1716,13.5547);
            SetPlayerVirtualWorld(playerid, wid);
            MoveDynamicObject(Login::screen[playerid][objectLogin], 1572.76, -2494.01, 14.7547, 18.0, 0, 0, -90.2);
            SetPlayerCameraPos(playerid,1604.5731,-2460.0952,20.4359);
            SetPlayerCameraLookAt(playerid, 1161.48, -2490.2, 66.7269, CAMERA_CUT);
            SetTimerEx("SpawnEndPlayer", 12000, false, "i", playerid);
            InterpolateCameraLookAt(playerid, 1487.52, -2494.01, 14.7547, 1572.76, -2494.01, 14.7547, 10000, CAMERA_MOVE);
        }
        case 2: 
        {

        }
    }
    return 1;
}

FUNC::SpawnEndPlayer(playerid)
{
    if(IsValidDynamicObject(Login::screen[playerid][objectLogin]))
        DestroyDynamicObject(Login::screen[playerid][objectLogin]);

    AccountData[playerid][pPosX] = 1692.3311;
    AccountData[playerid][pPosY] = -2331.0283;
    AccountData[playerid][pPosZ] = 13.5469;
    AccountData[playerid][pPosA] = 358.8479;
    TogglePlayerControllable(playerid, false);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
    AccountData[playerid][pDiPesawat] = true;
    //SetPlayerRaceCheckpoint(playerid, 1, 2.4156,33.1422,1199.5938, 0.0, 0.0, 0.0, 1.5);
    return 1;
}
CMD:testscreen(playerid, params[])
{
    Login::Screen_Show(playerid, 1);
    return 1;
}