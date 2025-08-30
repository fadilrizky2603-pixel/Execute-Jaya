enum eItemBox
{
	ItemBoxIcon,
	ItemBoxMessage[64],
	ItemBoxJumlahMessage[64],
	ItemBoxLoading,
	ItemBoxSize,
	Float:NotifyPositionIcon,
	Float:ItemRX,
	Float:ItemRY,
	Float:ItemRZ,
	Float:ItemScale
}
new InfoItemBox[MAX_PLAYERS][7][eItemBox];
new MaxPlayerItemBox[MAX_PLAYERS];
new PlayerText:TextDrawItemBox[MAX_PLAYERS][8*10];
new IndexItemBox[MAX_PLAYERS];

function HideItemBox(playerid)
{
	if(!IndexItemBox[playerid]) return 1;
	--IndexItemBox[playerid];
	MaxPlayerItemBox[playerid]--;
	for(new i=-1;++i<10;)
    {
        if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][(IndexItemBox[playerid]*10)+i]))
            PlayerTextDrawDestroy(playerid, TextDrawItemBox[playerid][(IndexItemBox[playerid]*10)+i]);
    }
	return 1;
}

ShowItemBox(playerid, const string[], const total[], time)
{
	if(MaxPlayerItemBox[playerid] == 5) return 1;
	MaxPlayerItemBox[playerid]++;
	new validtime = time*1000;
	for(new x=-1; ++x <IndexItemBox[playerid];)
	{
		for(new i=-1;++i<9;)
        {
            if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][(x*10) + i]))
                PlayerTextDrawDestroy(playerid, TextDrawItemBox[playerid][(x*10) + i]);
        }
		InfoItemBox[playerid][IndexItemBox[playerid]-x] = InfoItemBox[playerid][(IndexItemBox[playerid]-x)-1];
	}
    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);

	//textdraw settings item box sesuai model yang kalian inginkan
	format(InfoItemBox[playerid][0][ItemBoxMessage], 64, "%s", string);
	format(InfoItemBox[playerid][0][ItemBoxJumlahMessage], 64, "%s", total);

	new Float:teksamount = strlen(InfoItemBox[playerid][0][ItemBoxJumlahMessage]);
	InfoItemBox[playerid][0][NotifyPositionIcon] = 3.0 * teksamount;

	for (new id = 0; id < sizeof(g_aInventoryItems); id ++) if(!strcmp(g_aInventoryItems[id][e_InventoryItem], string, true))
	{
		InfoItemBox[playerid][0][ItemBoxIcon] = g_aInventoryItems[id][e_InventoryModel];
	}
	
	//============================================================================
	++IndexItemBox[playerid];
	new Float:new_x=0.0;
	for(new x=-1;++x<IndexItemBox[playerid];)
	{
		CreateItemBox(playerid, x, x * 10, new_x);
		new_x += (InfoItemBox[playerid][x][ItemBoxSize]*7.25)+60.0;
	}
	SetTimerEx("HideItemBox", validtime, false, "d", playerid);
	return 1;
}

CreateItemBox(const playerid, index, i, const Float:new_x)
{
	new lines = InfoItemBox[playerid][index][ItemBoxSize];
	new Float:x = (lines * 10) + new_x;
	new Float:posisibaru = x-1.0;

	TextDrawItemBox[playerid][i] = CreatePlayerTextDraw(playerid, 270.000, 170.000, "Gambar teks baru");
    PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.000, 1.500);
    PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 1);
    PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 1);
    PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 150);
    PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
    PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 314.000+posisibaru, 341.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 50.000, 70.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 1667457892);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 255);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 314.000+posisibaru, 400.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 50.000, 11.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 1111638753);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 255);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 314.000+posisibaru, 342.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], InfoItemBox[playerid][index][NotifyPositionIcon], 9.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 1684301055);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 255);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 319.000+posisibaru, 350.000, "_");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 40.000, 48.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 5);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextDrawItemBox[playerid][i], InfoItemBox[playerid][index][ItemBoxIcon]);
	if(InfoItemBox[playerid][index][ItemBoxIcon] == 18867)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], -254.000000, 0.000000, 0.000000, 2.779998);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 16776)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 0.000000, 0.000000, -85.000000, 1.000000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 1581)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 0.000000, 0.000000, -180.000000, 1.000000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 19580)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], -95.000000, 0.000000, 1.000000, 1.000000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 2703)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], -80.000, 0.000, 0.000, 1.000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 19896)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], -50.000, 0.000, -10.000, 1.000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 18875)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 95.000, 180.000, 0.000, 1.000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 19878)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 163.000, 210.000, -50.000, 1.000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 19883)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 163.000, 210.000, -50.000, 1.000);
	}
	else if(InfoItemBox[playerid][index][ItemBoxIcon] == 11736)
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 120.000, -30.000, 0.000, 1.000);
	}
	else
	{
		PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 0.000, 0.000, 0.000, 1.000);
	}
	PlayerTextDrawSetPreviewVehCol(playerid, TextDrawItemBox[playerid][i], 0, 0);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 340.000+posisibaru, 400.000, InfoItemBox[playerid][index][ItemBoxMessage]);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.140, 1.098);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 2);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 150);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 316.000+posisibaru, 342.000, InfoItemBox[playerid][index][ItemBoxJumlahMessage]);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.128, 0.898);
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 390.000, 110.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 150);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	return true;
}

/*enum eStuffBox
{
	BoxMessage1[320],
	BoxMessage2[320],
	BoxModel,
	BoxSize
}
new InfoBox[MAX_PLAYERS][4][eStuffBox];
new MaxPlayerBox[MAX_PLAYERS];
new PlayerText: TextDrawBox[MAX_PLAYERS][4*5];
new IndexBox[MAX_PLAYERS];

NERO::HiddenBox(playerid)
{
	if(!IndexBox[playerid]) return 1;
	--IndexBox[playerid];
	MaxPlayerBox[playerid]--;
	for(new i=-1; ++i<5;) PlayerTextDrawDestroy(playerid, TextDrawBox[playerid][(IndexBox[playerid]*5)+i]);

	return 1;
}

ShowItemBox(playerid, const pesan1[], const pesan2[], model)
{
	ShowingBox(playerid, pesan1, pesan2, model);
	return 1;
}

stock ShowingBox(playerid, const string:message[], const string:message2[], model)
{
	if(MaxPlayerBox[playerid] == 4) return 1;
	MaxPlayerBox[playerid]++;
	for(new x=-1;++x<IndexBox[playerid];)
	{
		for(new i=-1;++i<5;) PlayerTextDrawDestroy(playerid, TextDrawBox[playerid][(x*5) + i]);
		InfoBox[playerid][IndexBox[playerid]-x] = InfoBox[playerid][(IndexBox[playerid]-x)-1];
	}
	format(InfoBox[playerid][0][BoxMessage1], 320, "%s", message);
	format(InfoBox[playerid][0][BoxMessage2], 320, "%s", message2);
	InfoBox[playerid][0][BoxModel] = model;
	InfoBox[playerid][0][BoxSize] = 3;

	++IndexBox[playerid];
	new Float:new_x=0.0;
	for(new x=-1;++x<IndexBox[playerid];)
	{
		CreateBox(playerid, x, x * 5, new_x);
		new_x += (InfoBox[playerid][x][BoxSize]*7.25)+35.0;
	}
	SetTimerEx("HiddenBox", 7000, false, "i", playerid);
	return 1;
}

stock CreateBox(const playerid, index, i, const Float:new_x)
{
	new lines = InfoBox[playerid][index][BoxSize];
	new Float:x = (lines * 5) + new_x;
	new Float:posisibaru = x-30.0;

	PlayerPlaySound(playerid, 1150, 0, 0, 0);
    TextDrawBox[playerid][i] = CreatePlayerTextDraw(playerid, 367.000+posisibaru, 329.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 55.000, 70.000);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], 842682623);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 255);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 4);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 367.000+posisibaru, 396.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 55.000, 3.000);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], -261923073);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 255);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 4);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 367.000+posisibaru, 329.000, "_");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 55.000, 66.000);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 5);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetPreviewModel(playerid, TextDrawBox[playerid][i], InfoBox[playerid][index][BoxModel]);
    PlayerTextDrawSetPreviewRot(playerid, TextDrawBox[playerid][i], 0.000, 0.000, 0.000, 1.500);
    PlayerTextDrawSetPreviewVehCol(playerid, TextDrawBox[playerid][i], 0, 0);
	PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 369.000+posisibaru, 330.000, InfoBox[playerid][index][BoxMessage1]);
    PlayerTextDrawLetterSize(playerid, TextDrawBox[playerid][i], 0.119, 0.999);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 150);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 394.000+posisibaru, 381.000, InfoBox[playerid][index][BoxMessage2]);
    PlayerTextDrawLetterSize(playerid, TextDrawBox[playerid][i], 0.119, 0.999);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 2);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 150);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);
	return 1;
}*/