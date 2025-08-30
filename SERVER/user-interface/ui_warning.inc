#include <YSI_Coding\y_hooks>

new PlayerText: ALERTTD[MAX_PLAYERS][16];

stock LoadAlertTD(playerid)
{
	ALERTTD[playerid][0] = CreatePlayerTextDraw(playerid, -11.000, -61.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][0], 710.000, 610.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][0], -1845493505);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][0], 1);

	ALERTTD[playerid][1] = CreatePlayerTextDraw(playerid, 211.000, 150.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][1], 218.000, 133.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][1], 1);

	ALERTTD[playerid][2] = CreatePlayerTextDraw(playerid, 212.000, 151.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][2], 216.000, 131.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][2], -1845493505);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][2], 1);

	ALERTTD[playerid][3] = CreatePlayerTextDraw(playerid, 250.000, 169.000, "/");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][3], 0.738, 4.398);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][3], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][3], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][3], 1);

	ALERTTD[playerid][4] = CreatePlayerTextDraw(playerid, 257.000, 169.000, "\\");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][4], 0.798, 4.298);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][4], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][4], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][4], 1);

	ALERTTD[playerid][5] = CreatePlayerTextDraw(playerid, 249.000, 195.000, "-");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][5], 1.889, 1.598);
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][5], 0.000, -62.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][5], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][5], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][5], 1);

	ALERTTD[playerid][6] = CreatePlayerTextDraw(playerid, 259.000, 185.000, "!");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][6], 0.230, 1.899);
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][6], 0.000, -62.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][6], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][6], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][6], 1);

	ALERTTD[playerid][7] = CreatePlayerTextDraw(playerid, 364.000, 167.000, "/");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][7], 0.738, 4.398);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][7], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][7], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][7], 1);

	ALERTTD[playerid][8] = CreatePlayerTextDraw(playerid, 371.000, 167.000, "\\");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][8], 0.798, 4.298);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][8], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][8], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][8], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][8], 1);

	ALERTTD[playerid][9] = CreatePlayerTextDraw(playerid, 363.000, 193.000, "-");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][9], 1.889, 1.598);
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][9], 0.000, -62.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][9], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][9], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][9], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][9], 1);

	ALERTTD[playerid][10] = CreatePlayerTextDraw(playerid, 373.000, 183.000, "!");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][10], 0.230, 1.899);
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][10], 0.000, -62.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][10], -596946177);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][10], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][10], 1);

	ALERTTD[playerid][11] = CreatePlayerTextDraw(playerid, 277.000, 182.000, "WARNING");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][11], 0.509, 2.499);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][11], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][11], 1);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][11], 1);

	ALERTTD[playerid][12] = CreatePlayerTextDraw(playerid, 248.000, 207.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][12], 139.000, 1.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][12], 255);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][12], 4);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][12], 1);

	ALERTTD[playerid][13] = CreatePlayerTextDraw(playerid, 320.000, 213.000, "Ganggu bucin aja anjg lu bgst");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][13], 0.290, 1.699);
	PlayerTextDrawTextSize(playerid, ALERTTD[playerid][13], 152.000, 212.000);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][13], 2);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][13], -1);
	PlayerTextDrawUseBox(playerid, ALERTTD[playerid][13], 1);
	PlayerTextDrawBoxColor(playerid, ALERTTD[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][13], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][13], 1);

	ALERTTD[playerid][14] = CreatePlayerTextDraw(playerid, 368.000, 264.000, "Warned by: eternals");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][14], 0.159, 1.099);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][14], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][14], 1);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][14], 1);

	ALERTTD[playerid][15] = CreatePlayerTextDraw(playerid, 320.000, 287.000, "Press [Y] to dismiss this message.");
	PlayerTextDrawLetterSize(playerid, ALERTTD[playerid][15], 0.189, 1.099);
	PlayerTextDrawAlignment(playerid, ALERTTD[playerid][15], 2);
	PlayerTextDrawColor(playerid, ALERTTD[playerid][15], -1);
	PlayerTextDrawSetShadow(playerid, ALERTTD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, ALERTTD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, ALERTTD[playerid][15], 150);
	PlayerTextDrawFont(playerid, ALERTTD[playerid][15], 1);
	PlayerTextDrawSetProportional(playerid, ALERTTD[playerid][15], 1);  
}

hook OnPlayerConnect(playerid)
{
    LoadAlertTD(playerid);    
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES)
    {
		if(IsValidDynamicPlayerTextDraw(playerid, ALERTTD[playerid][0]))
		{
			forex(i, 16)
			{
				PlayerTextDrawHide(playerid, ALERTTD[playerid][i]);
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:alert(playerid, const params[])
{
	new
	    userid, teks[100];

    if(AccountData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	if (sscanf(params, "us[100]", userid, teks))
	    return ShowTDN(playerid, NOTIFICATION_WARNING, "/alert [playerid/PartOfName] [teks]");

	forex(i, 16)
	{
		PlayerTextDrawShow(userid, ALERTTD[userid][i]);
		PlayerTextDrawSetString(userid, ALERTTD[userid][13], teks);
		PlayerTextDrawSetString(userid, ALERTTD[userid][14], sprintf("Warned by: %s", AccountData[playerid][pAdminname]));
	}
	SendClientMessageToAllEx(COLOR_IVORY, "AdmCmd | %s telah memunculkan alert kepada %s", AccountData[playerid][pAdminname], ReturnName(userid));
	return 1;
}