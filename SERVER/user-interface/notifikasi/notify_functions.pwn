    #include <YSI\y_hooks>
    enum e_notify
    {
        notifyIcon,
        notifyMessage[320],
        notifySize
    }
    new NotifInfo[MAX_PLAYERS][4][e_notify];
    new MaxPlayerNotify[MAX_PLAYERS];
    new PlayerText: notifyTextdraws[MAX_PLAYERS][4*8];
    new NotifIndex[MAX_PLAYERS];

    forward NotifyHide(playerid);
    public NotifyHide(playerid)
    {
        if(!NotifIndex[playerid]) return 1;
        -- NotifIndex[playerid];
        MaxPlayerNotify[playerid] --;
        for (new i = -1; ++ i < 8;) PlayerTextDrawDestroy(playerid, notifyTextdraws[playerid][(NotifIndex[playerid] * 8) + i]);
        return 1;
    }


ShowTDN(playerid, notifid, text[])
{
    if(AccountData[playerid][pStyleNotif] == 1) // TD
    {
        switch(notifid)
        {
            case NOTIFICATION_ERROR:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 1085, 0, 0, 0);
                ShowNotify(playerid, text, 2);
            }
            case NOTIFICATION_INFO:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 1139, 0, 0, 0);
                ShowNotify(playerid, text, 1);
            }
            case NOTIFICATION_SUKSES:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 5203, 0, 0, 0);
                ShowNotify(playerid, text, 3);
            }
            case NOTIFICATION_SYNTAX:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 5201, 0, 0, 0);
                ShowNotify(playerid, text, 4);
            }
            case NOTIFICATION_WARNING:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 4203, 0, 0, 0);
                ShowNotify(playerid, text, 5);
            }
        }
    }
    else if(AccountData[playerid][pStyleNotif] == 2)
    {
        switch(notifid)
        {
            case NOTIFICATION_ERROR:
            {
                Error(playerid, "%s", text);
            }
            case NOTIFICATION_INFO:
            {
                Info(playerid, "%s", text);
            }
            case NOTIFICATION_SUKSES:
            {
                Info(playerid, "%s", text);
            }
            case NOTIFICATION_SYNTAX:
            {
                Syntax(playerid, "%s", text);
            }
            case NOTIFICATION_WARNING:
            {
                Warning(playerid, "%s", text);
            }
        }
    }
    return 1;
}

/*stock ShowTDN(playerid, notifid, pesan[])
{
    switch(notifid)
    {
        case NOTIFICATION_ERROR:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 1085, 0, 0, 0);
			ShowNotify(playerid, pesan, 2);
		}
		case NOTIFICATION_INFO:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 1139, 0, 0, 0);
			ShowNotify(playerid, pesan, 1);
		}
		case NOTIFICATION_SUKSES:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 5203, 0, 0, 0);
			ShowNotify(playerid, pesan, 3);
		}
		case NOTIFICATION_SYNTAX:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 5201, 0, 0, 0);
			ShowNotify(playerid, pesan, 4);
		}
		case NOTIFICATION_WARNING:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 4203, 0, 0, 0);
			ShowNotify(playerid, pesan, 5);
		}
    }
    return 1;
}*/

stock ShowNotify(playerid, message[], icon)
{
    if(MaxPlayerNotify[playerid] >= 4) return 1;
    MaxPlayerNotify[playerid] ++;
    for (new x = -1; ++ x < NotifIndex[playerid] && x < 4;)
    {
        for (new i = -1; ++ i < 8;) PlayerTextDrawDestroy(playerid, notifyTextdraws[playerid][(x * 8) + i]);
        NotifInfo[playerid][NotifIndex[playerid] - x] = NotifInfo[playerid][(NotifIndex[playerid] - x) - 1];
    }
    format(NotifInfo[playerid][0][notifyMessage], 320, "%s", message);
    NotifInfo[playerid][0][notifyIcon] = icon;
    NotifInfo[playerid][0][notifySize] = 3;

    ++ NotifIndex[playerid];
    new Float: new_x = 0.0;
    for (new x = -1; ++ x < NotifIndex[playerid];)
    {
        CreateNotify(playerid, x, x * 8, new_x);
        new_x += (NotifInfo[playerid][x][notifySize] * 7.25) + 20.0;
    }
    SetTimerEx("NotifyHide", 6500, false, "d", playerid);
    return 1;
}

CreateNotify(playerid, index, i, Float:new_x)
{
    new lines = NotifInfo[playerid][index][notifySize];
    new Float:x = (lines * 8) + new_x;
    new Float:newpos = x - 20.0;
    if(NotifInfo[playerid][index][notifyIcon] == 1)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 500.000, 103.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 1097458175);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 500.000, 107.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 943210495);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 502.000, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 17.000, 17.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 503.000, 108.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 15.000, 15.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 1097458175);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 509.000, 109.000+newpos, "i");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.310, 1.299);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 518.000, 110.000+newpos, "INFO");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.200, 1.099);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 1097458175);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 610.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 2)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 500.000, 103.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1052226817);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 500.000, 107.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 943210495);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 109.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 20.000, 5.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1052226817);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 115.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 20.000, 5.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1052226817);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 525.000, 110.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], -5.000, 3.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 943210495);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 525.000, 116.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], -5.000, 3.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 943210495);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 528.000, 109.000+newpos, "ERROR");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.210, 1.099);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1052226817);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 610.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 3)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 500.000, 103.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 1018393087);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 500.000, 107.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 943210495);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 502.000, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 17.000, 17.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 510.000, 111.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.230, 0.699);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 16744447);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 512.000, 114.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], -0.260, 0.499);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 16744447);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 518.000, 110.000+newpos, "SUCCESS");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.200, 1.099);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 1018393087);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 610.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 4)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 500.000, 103.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -2139062017);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 500.000, 107.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 943210495);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 507.000, 108.000+newpos, "!");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.329, 1.399);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -2139062017);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 513.000, 110.000+newpos, "SYNTAX");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.159, 1.100);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -2139062017);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 610.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 5)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 500.000, 103.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -626712321);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 500.000, 107.000+newpos, "LD_BUM:blkdot");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 943210495);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 507.000, 108.000+newpos, "!");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.329, 1.399);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -626712321);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 513.000, 110.000+newpos, "WARNING");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.159, 1.100);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -626712321);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++ i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 610.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
}