#include <YSI_Coding\y_hooks>

CreateTDShortKey(playerid)
{
    PlayerTextdraws[playerid][textdraw_interaksi][0] = CreatePlayerTextDraw(playerid, 11.000, 195.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 96.000, 20.000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], -1);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 4);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][1] = CreatePlayerTextDraw(playerid, 11.000, 195.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 6.000, 20.000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 4);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][2] = CreatePlayerTextDraw(playerid, 21.000, 201.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 9.000, 8.000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 255);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 4);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][3] = CreatePlayerTextDraw(playerid, 32.000, 199.000, "[Y] Akses Garasi Umum");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 0.170, 1.098);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 255);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 150);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 1);
}

hook OnPlayerConnect(playerid)
{
    CreateTDShortKey(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    for(new x = 0; x < 4; x++)
    {
        PlayerTextDrawDestroy(playerid, PlayerTextdraws[playerid][textdraw_interaksi][x]);
    }
}

ShowKey(playerid, const text[])
{
    PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], text);
    for(new x = 0; x < 4; x++)
    {
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][x]);
    }
    PlayerPlaySound(playerid, 1058, 0, 0, 0);
    return 1;
}

HideShortKey(playerid)
{
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3]);
    return 1;
}