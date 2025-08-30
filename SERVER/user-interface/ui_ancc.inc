#include <YSI_Coding\y_hooks>
new PlayerText: ANNOUNCEMENT[MAX_PLAYERS][5];

stock LoadAnnouncementTD(playerid)
{
    ANNOUNCEMENT[playerid][0] = CreatePlayerTextDraw(playerid, 21.000, 130.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ANNOUNCEMENT[playerid][0], 158.000, 73.000);
    PlayerTextDrawAlignment(playerid, ANNOUNCEMENT[playerid][0], 1);
    PlayerTextDrawColor(playerid, ANNOUNCEMENT[playerid][0], -2686721);
    PlayerTextDrawSetShadow(playerid, ANNOUNCEMENT[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ANNOUNCEMENT[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ANNOUNCEMENT[playerid][0], 255);
    PlayerTextDrawFont(playerid, ANNOUNCEMENT[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ANNOUNCEMENT[playerid][0], 1);

    ANNOUNCEMENT[playerid][1] = CreatePlayerTextDraw(playerid, 70.000, 132.000, "Anncouments");
    PlayerTextDrawLetterSize(playerid, ANNOUNCEMENT[playerid][1], 0.250, 1.099);
    PlayerTextDrawAlignment(playerid, ANNOUNCEMENT[playerid][1], 1);
    PlayerTextDrawColor(playerid, ANNOUNCEMENT[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, ANNOUNCEMENT[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ANNOUNCEMENT[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ANNOUNCEMENT[playerid][1], 150);
    PlayerTextDrawFont(playerid, ANNOUNCEMENT[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, ANNOUNCEMENT[playerid][1], 1);

    ANNOUNCEMENT[playerid][2] = CreatePlayerTextDraw(playerid, 35.000, 176.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ANNOUNCEMENT[playerid][2], 14.000, 16.000);
    PlayerTextDrawAlignment(playerid, ANNOUNCEMENT[playerid][2], 1);
    PlayerTextDrawColor(playerid, ANNOUNCEMENT[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, ANNOUNCEMENT[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ANNOUNCEMENT[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ANNOUNCEMENT[playerid][2], 255);
    PlayerTextDrawFont(playerid, ANNOUNCEMENT[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ANNOUNCEMENT[playerid][2], 1);

    ANNOUNCEMENT[playerid][3] = CreatePlayerTextDraw(playerid, 38.000, 138.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ANNOUNCEMENT[playerid][3], 8.000, 37.000);
    PlayerTextDrawAlignment(playerid, ANNOUNCEMENT[playerid][3], 1);
    PlayerTextDrawColor(playerid, ANNOUNCEMENT[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, ANNOUNCEMENT[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ANNOUNCEMENT[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ANNOUNCEMENT[playerid][3], 255);
    PlayerTextDrawFont(playerid, ANNOUNCEMENT[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ANNOUNCEMENT[playerid][3], 1);

    ANNOUNCEMENT[playerid][4] = CreatePlayerTextDraw(playerid, 59.000, 148.000, "di harap warga melakukan saveme server akan badai cukup lama ya guyssss");
    PlayerTextDrawLetterSize(playerid, ANNOUNCEMENT[playerid][4], 0.140, 0.799);
    PlayerTextDrawTextSize(playerid, ANNOUNCEMENT[playerid][4], 177.000, 0.000);
    PlayerTextDrawAlignment(playerid, ANNOUNCEMENT[playerid][4], 1);
    PlayerTextDrawColor(playerid, ANNOUNCEMENT[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, ANNOUNCEMENT[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ANNOUNCEMENT[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ANNOUNCEMENT[playerid][4], 150);
    PlayerTextDrawFont(playerid, ANNOUNCEMENT[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, ANNOUNCEMENT[playerid][4], 1);

}

hook OnPlayerConnect(playerid)
{
    LoadAnnouncementTD(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

function hideann()
{
	foreach(new i : Player)
	{
		for(new  ii = 0; ii < 5; ii ++)
		{
			PlayerTextDrawHide(i, ANNOUNCEMENT[i][ii]);
		}
	}
	return 1;
}

CMD:annc(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

    new teks[250], str[128];
    if(sscanf(params, "s[250]", teks))
    {
        ShowTDN(playerid, NOTIFICATION_WARNING, "/ann [teks]");
        return 1;
    }		
	format(str, 128, "%s", teks);
	for(new ii = 0; ii < 5; ii ++)
	{
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			PlayerTextDrawShow(i, ANNOUNCEMENT[i][ii]);
			PlayerTextDrawSetString(i, ANNOUNCEMENT[i][4], str);	
			SetTimer("hideann", 5000, 0);	
		}
	}	
    SendClientMessageToAll(COLOR_IVORY, "AdmCmd | %s telah memunculkan announcement kepada warga di kota", AccountData[playerid][pAdminname]);	
	return 1;
}
