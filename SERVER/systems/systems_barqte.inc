#define BAR_MIN 272 // Posisi minimum bar
#define BAR_MAX 375	// Posisi maksimum bar
#define BAR_SPEED 10 	// kecepatan bar
#define	MAX_CALLBACK 34
#define LebarTarget 5

new bool:BarDirection[MAX_PLAYERS];   // Arah pergerakan bar (true = maju, false = mundur)
new showBarGames[MAX_PLAYERS];
new Float:BarPosition[MAX_PLAYERS];   // Posisi bar saat ini untuk setiap pemain
new Float:BarMove[MAX_PLAYERS];   // Posisi wabar saat ini untuk setiap pemain
new BarTimer[MAX_PLAYERS];      // Timer untuk menggerakkan bar

new Float:targetlokasi[MAX_PLAYERS];
new PlayerText:PlayerTD[MAX_PLAYERS][9];

new LoadingCallback[MAX_PLAYERS][MAX_CALLBACK];

stock randomEx(minnum = cellmin, maxnum = cellmax) return random(maxnum - minnum + 1) + minnum;

function IsValidBarQTE(playerid)
	return showBarGames[playerid];

stock BarQTE(playerid, const HDevinteks[] = "_", const callback[] = "")
{
	if(showBarGames[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "your already minigames bars");
	BarPosition[playerid] = 0.0;
    BarDirection[playerid] = true;
    showBarGames[playerid] = 1;
    // Jika callback tidak kosong, maka lakukan sesuatu
    if(callback[0] != EOS)
	{
		format(LoadingCallback[playerid], MAX_CALLBACK, "%s", callback);
	}
	//for(new i = 0; i < 1; i++) PlayerTextDrawShow(playerid, PlayerTD[playerid][i]);

    CreateBar(playerid, HDevinteks);
    return 1;
}

function CreateBar(playerid, const HDevinteks[])
{    
    BarMove[playerid] = BAR_MIN, BarTimer[playerid] = SetTimerEx("MoveBar", 100, true, "i", playerid);   
	targetlokasi[playerid] = randomEx(BAR_MIN, BAR_MAX - LebarTarget); 

	PlayerTD[playerid][0] = CreatePlayerTextDraw(playerid, 268.000, 399.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][0], 110.000, 1.000);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][0], 1);

	PlayerTD[playerid][1] = CreatePlayerTextDraw(playerid, 268.000, 417.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][1], 110.000, 1.000);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][1], 1);

	PlayerTD[playerid][2] = CreatePlayerTextDraw(playerid, 268.000, 418.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][2], 1.000, -19.000);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][2], 1);

	PlayerTD[playerid][3] = CreatePlayerTextDraw(playerid, 378.000, 418.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][3], 1.000, -19.000);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][3], 1);

	PlayerTD[playerid][4] = CreatePlayerTextDraw(playerid, 269.000, 390.000, HDevinteks);
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][4], 0.148, 0.796);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][4], 150);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][4], 1);

	PlayerTD[playerid][5] = CreatePlayerTextDraw(playerid, 365.000, 390.000, "Press H");
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][5], 0.148, 0.796);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][5], 150);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][5], 1);

	PlayerTD[playerid][6] = CreatePlayerTextDraw(playerid, 271.000, 402.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][6], 105.000, 12.000);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][6], 606879231);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][6], 255);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][6], 1);

	PlayerTD[playerid][7] = CreatePlayerTextDraw(playerid, BAR_MIN, 404.000, "_");
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][7], 0.930, 0.997);
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][7], 375.000, 89.000);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, PlayerTD[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][7], COLOR_GOLD);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][7], 1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][7], -1);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][7], 1);

	PlayerTD[playerid][8] = CreatePlayerTextDraw(playerid, targetlokasi[playerid], 402.000, "_");
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][8], 0.536, 1.500);
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][8], targetlokasi[playerid] + LebarTarget, 70.000);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][8], -1);
	PlayerTextDrawUseBox(playerid, PlayerTD[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][8], 1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][8], -1);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][8], 1);

	for(new i = 0; i < 9; i++) PlayerTextDrawShow(playerid, PlayerTD[playerid][i]);

	return 1;
}

function MoveBar(playerid)
{
    if (!BarDirection[playerid])
    {
        BarMove[playerid] = BarMove[playerid] - BAR_SPEED;
        if (BarMove[playerid] <= BAR_MIN)
        {
            BarDirection[playerid] = true;
            BarMove[playerid] = BAR_MIN;
        }
    }
    else
    {
		BarMove[playerid] = BarMove[playerid] + BAR_SPEED;
		if (BarMove[playerid] >= BAR_MAX)
		{
		    BarDirection[playerid] = false;
		    BarMove[playerid] = BAR_MAX;
		}
	}
    
	if(IsValidDynamicPlayerTextDraw(playerid, PlayerTD[playerid][7]))
    // Mengatur posisi bar menggunakan TextDraw
    PlayerTextDrawTextSize(playerid, PlayerTD[playerid][7], BarMove[playerid], 89.000);
    PlayerTextDrawShow(playerid, PlayerTD[playerid][7]);
}

function StopBar(playerid)
{
    if (floatabs(BarMove[playerid] - targetlokasi[playerid]) <= LebarTarget)
    {
		if(LoadingCallback[playerid][0] != EOS)
		{
			CallLocalFunction(LoadingCallback[playerid], "d", playerid);
		}
   	}
    else
    {
    	ShowTDN(playerid, NOTIFICATION_ERROR, "Aktivity gagal, karna garis titik tidak tepat");
    }
	LoadingCallback[playerid][0] = EOS;
    KillTimer(BarTimer[playerid]);
    showBarGames[playerid] = 0;

	// Or
	for(new i = 0; i < 9; i++)
	{
		// i == 0  :: OK
		// i == 1  :: Error
		PlayerTextDrawDestroy(playerid, PlayerTD[playerid][i]);
	}
	RemovePlayerAttachedObject(playerid, 0);
	ClearAnimations(playerid, 0);
    return 1;
}

CMD:pesan(playerid, params[])
{
	//manggilanya BarQTE(playerid, "HDevinteks", "Callback");
    BarQTE(playerid, "pesan", "Pesan");
    return 1;
}

function Pesan(playerid)
{
	SendClientMessage(playerid, -1, "Test Pesan");
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys & KEY_CTRL_BACK) 
    {
    	if(showBarGames[playerid]) return StopBar(playerid);
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}