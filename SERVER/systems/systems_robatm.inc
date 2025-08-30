#include <YSI_Coding\y_hooks>
#define MAX_REMEMBERS	20
#define KEIZI:%0(%1) forward %0(%1); public %0(%1)
enum Remember_Data
{
	bool:remindersMustClicked,
	bool:remindersClicked,
}
new RememberData[MAX_PLAYERS][MAX_REMEMBERS][Remember_Data];
new PlayerText: RememberTD[MAX_PLAYERS][3];
new PlayerText: RobTD[MAX_PLAYERS][20];
new RobWave[MAX_PLAYERS],Float:RobValue[MAX_PLAYERS], RobTimers[MAX_PLAYERS], bool:IsPlayerRobbing[MAX_PLAYERS];
new Float:RobTimersDecrease[MAX_PLAYERS], RobCount[MAX_PLAYERS];

RobWarung_CreateTextDraw(playerid)
{
	RememberTD[playerid][0] = CreatePlayerTextDraw(playerid, 214.000, 118.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RememberTD[playerid][0], 215.000, 239.000);
    PlayerTextDrawAlignment(playerid, RememberTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, RememberTD[playerid][0], 1330007807);
    PlayerTextDrawSetShadow(playerid, RememberTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, RememberTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, RememberTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, RememberTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, RememberTD[playerid][0], 1);

    RememberTD[playerid][1] = CreatePlayerTextDraw(playerid, 222.000, 331.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RememberTD[playerid][1], 198.000, 10.000);
    PlayerTextDrawAlignment(playerid, RememberTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, RememberTD[playerid][1], 2129619967);
    PlayerTextDrawSetShadow(playerid, RememberTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, RememberTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, RememberTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, RememberTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, RememberTD[playerid][1], 1);

    RememberTD[playerid][2] = CreatePlayerTextDraw(playerid, 305.000, 123.000, "Rob Atm");
    PlayerTextDrawLetterSize(playerid, RememberTD[playerid][2], 0.250, 1.299);
    PlayerTextDrawAlignment(playerid, RememberTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, RememberTD[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, RememberTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, RememberTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, RememberTD[playerid][2], 150);
    PlayerTextDrawFont(playerid, RememberTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, RememberTD[playerid][2], 1);

	RobTD[playerid][0] = CreatePlayerTextDraw(playerid, 222.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][0], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][0], 1);

    RobTD[playerid][1] = CreatePlayerTextDraw(playerid, 263.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][1], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][1], 1);

    RobTD[playerid][2] = CreatePlayerTextDraw(playerid, 304.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][2], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][2], 1);

    RobTD[playerid][3] = CreatePlayerTextDraw(playerid, 345.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][3], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][3], 1);

    RobTD[playerid][4] = CreatePlayerTextDraw(playerid, 386.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][4], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][4], 1);

    RobTD[playerid][5] = CreatePlayerTextDraw(playerid, 222.000, 190.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][5], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][5], 1);

    RobTD[playerid][6] = CreatePlayerTextDraw(playerid, 263.000, 190.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][6], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][6], 1);

    RobTD[playerid][7] = CreatePlayerTextDraw(playerid, 304.000, 190.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][7], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][7], 1);

    RobTD[playerid][8] = CreatePlayerTextDraw(playerid, 345.000, 190.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][8], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][8], 1);

    RobTD[playerid][9] = CreatePlayerTextDraw(playerid, 386.000, 190.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][9], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][9], 1);

    RobTD[playerid][10] = CreatePlayerTextDraw(playerid, 222.000, 236.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][10], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][10], 1);

    RobTD[playerid][11] = CreatePlayerTextDraw(playerid, 263.000, 236.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][11], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][11], 1);

    RobTD[playerid][12] = CreatePlayerTextDraw(playerid, 304.000, 236.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][12], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][12], 1);

    RobTD[playerid][13] = CreatePlayerTextDraw(playerid, 345.000, 236.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][13], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][13], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][13], 1);

    RobTD[playerid][14] = CreatePlayerTextDraw(playerid, 386.000, 236.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][14], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][14], 1);

    RobTD[playerid][15] = CreatePlayerTextDraw(playerid, 222.000, 282.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][15], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][15], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][15], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][15], 1);

    RobTD[playerid][16] = CreatePlayerTextDraw(playerid, 263.000, 282.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][16], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][16], 1);

    RobTD[playerid][17] = CreatePlayerTextDraw(playerid, 304.000, 282.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][17], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][17], 1);

    RobTD[playerid][18] = CreatePlayerTextDraw(playerid, 345.000, 282.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][18], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][18], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][18], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][18], 1);

    RobTD[playerid][19] = CreatePlayerTextDraw(playerid, 386.000, 282.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, RobTD[playerid][19], 34.000, 39.000);
    PlayerTextDrawAlignment(playerid, RobTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, RobTD[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, RobTD[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, RobTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, RobTD[playerid][19], 255);
    PlayerTextDrawFont(playerid, RobTD[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, RobTD[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, RobTD[playerid][19], 1);
	return 1;
}

hook OnPlayerConnect(playerid) 
{
    RobWarung_CreateTextDraw(playerid);
    return 1;
}

RobWarung_TextDrawReset(playerid)
{
	//Loop TextDraw
	for(new i = 0; i<MAX_REMEMBERS; i++)
	{
		RememberData[playerid][i][remindersMustClicked] = false;
		RememberData[playerid][i][remindersClicked] = false;
		PlayerTextDrawColor(playerid, RobTD[playerid][i], -1);
	}
	//Reset Player Data

	IsPlayerRobbing[playerid] = false;
	RobWave[playerid] = 0;
	RobValue[playerid] = 100.0;
	RobTimersDecrease[playerid] = 1.0;
	RobCount[playerid] = 0;
	KillTimer(RobTimers[playerid]);
	return 1;
}
RobWarung_RandomTextDraw(playerid)
{
	//SUBSCIBE KEIIZI
	new counts = 0, rand;
	//Loop textdraw
	for(new i = 0; i<MAX_REMEMBERS; i++)
	{
		//random textdraw yang harus di ingat
		rand = random(MAX_REMEMBERS);

		//Check jika textdraw sudah harus di ingat, maka random lagi
		if(RememberData[playerid][rand][remindersMustClicked]) rand = random(MAX_REMEMBERS);

		//Double Check
		if(RememberData[playerid][rand][remindersMustClicked]) rand = random(MAX_REMEMBERS);

		//Set agar TextDraw ini wajib di klik
		RememberData[playerid][rand][remindersMustClicked] = true;

		//Set Warna TextDraw
		PlayerTextDrawColor(playerid, RobTD[playerid][rand], 2129619967);

		//Hitung Textdraw yang harus di ingat
		counts++;

		//Maksimal 5 textdraw yang harus di ingat
		if(counts == 5) break;
	}
	return 1;
}

RobWarung_ShowTextDraw(playerid)
{
	//Reset Dulu TextDrawnya
	RobWarung_TextDrawReset(playerid);

	//Random TextDraw Yang Harus Di Klik
	RobWarung_RandomTextDraw(playerid);

	//Player sekarang sedang rob
	IsPlayerRobbing[playerid] = true;

	//Player Wave
	RobWave[playerid] = 1;

	//Show All TextDraw
	for(new i = 0; i<3; i++) PlayerTextDrawShow(playerid, RememberTD[playerid][i]);
	for(new i = 0; i<MAX_REMEMBERS; i++) PlayerTextDrawShow(playerid, RobTD[playerid][i]);

	//Loop Timer
	RobTimers[playerid] = SetTimerEx("RobTimersEx", 20, true, "d", playerid);
	return 1;
}
RobWarung_StartMission(playerid)
{
	//Biar bisa klik textdraw (warna ubah sesuka kalian)
	SelectTextDraw(playerid, 2129619967);

	//Set ulang player data
	RobWave[playerid] = 2;
	RobValue[playerid] = 100.0;
	RobTimersDecrease[playerid] = 0.5;

	//Set Warna ke putih dan show kembali
	for(new i = 0; i<MAX_REMEMBERS; i++) PlayerTextDrawColor(playerid, RobTD[playerid][i], -1), PlayerTextDrawShow(playerid, RobTD[playerid][i]);
	return 1;
}

RobWarung_HideTextDraw(playerid)
{
	//Reset Lagi TextDrawnya 
	RobWarung_TextDrawReset(playerid);

	for(new i = 0; i<3; i++) PlayerTextDrawHide(playerid, RememberTD[playerid][i]);
	for(new i = 0; i<MAX_REMEMBERS; i++) PlayerTextDrawHide(playerid, RobTD[playerid][i]);

	CancelSelectTextDraw(playerid);
	return 1;
}
RobWarung_Succes(playerid)
{
	new rand = RandomEx(10000, 30000);
	IsPlayerRobbing[playerid] = false;
	RobWarung_HideTextDraw(playerid);
    AccountData[playerid][pRedMoney] += rand;
	CooldownRobWarung = gettime()+50;
    Inventory_Remove(playerid, "Laptop", 1);
    ShowItemBox(playerid, "Removed 1x", "Laptop", 19893);
	ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda berhasil mengrampok atm dan mendapatkan sejumlah uang $%s", rand));
	return 1;
}
RobWarung_Failed(playerid)
{
	IsPlayerRobbing[playerid] = false;
	RobWarung_HideTextDraw(playerid);
	ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu gagal pada saat merampok");
	return 1; 
}
CMD:resetrobatm(playerid, params[]) 
{
	CooldownRobWarung = 0;
	ShowTDN(playerid, NOTIFICATION_INFO, "Cooldown telah di reset");
	return 1;
}

KEIZI:RobTimersEx(playerid)
{
	if(IsPlayerRobbing[playerid])
	{
		switch(RobWave[playerid])
		{
			case 1:
			{
				RobValue[playerid] -= RobTimersDecrease[playerid];
				new Float:indicatorvalue = RobValue[playerid]*198/100;
				PlayerTextDrawTextSize(playerid, RememberTD[playerid][1], indicatorvalue, 10.000);
				PlayerTextDrawShow(playerid, RememberTD[playerid][1]);
				if(RobValue[playerid] <= 0) RobWarung_StartMission(playerid);
			}
			case 2:
			{
				RobValue[playerid] -= RobTimersDecrease[playerid];
				new Float:indicatorvalue = RobValue[playerid]*198/100;
				PlayerTextDrawTextSize(playerid, RememberTD[playerid][1], indicatorvalue, 10.000);
				PlayerTextDrawShow(playerid, RememberTD[playerid][1]);
				if(RobValue[playerid] <= 0) RobWarung_Failed(playerid);
			}
		}
	}
	return 1;
}