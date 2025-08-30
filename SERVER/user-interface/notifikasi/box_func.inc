enum eStuffBox
{
	BoxMessage1[320],
	BoxMessage2[320],
	BoxModel,
	BoxSize
}
new InfoBox[MAX_PLAYERS][4][eStuffBox];
new MaxPlayerBox[MAX_PLAYERS];
new PlayerText: TextDrawItemBox[MAX_PLAYERS][6*10];
new IndexBox[MAX_PLAYERS];

VRRP::HiddenBox(playerid)
{
	if(!IndexBox[playerid]) return 1;
	--IndexBox[playerid];
	MaxPlayerBox[playerid]--;
	for(new i=-1; ++i<10;) {
		if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][(IndexBox[playerid]*10)+i]))
		PlayerTextDrawDestroy(playerid, TextDrawItemBox[playerid][(IndexBox[playerid]*10)+i]);
	}

	return 1;
}

ShowItemBox(playerid, pesan1[], pesan2[], model)
{
	ShowingBox(playerid, pesan1, pesan2, model);
	return 1;
}

stock ShowingBox(playerid, string:message[], string:message2[], model)
{
	if(MaxPlayerBox[playerid] == 4) return 1;
	MaxPlayerBox[playerid]++;
	for(new x=-1;++x<IndexBox[playerid];)
	{
		for(new i=-1;++i<10;) 
		if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][(x*10) + i]))
		PlayerTextDrawDestroy(playerid, TextDrawItemBox[playerid][(x*10) + i]);
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
		CreateBox(playerid, x, x * 10, new_x);
		new_x += (InfoBox[playerid][x][BoxSize]*7.25)+40.0;
	}
	SetTimerEx("HiddenBox", 7000, false, "i", playerid);
	return 1;
}

stock CreateBox(const playerid, index, i, const Float:new_x)
{
	new lines = InfoBox[playerid][index][BoxSize];
	new Float:x = (lines * 10) + new_x;
	new Float:posisibaru = x-14.0;

	PlayerPlaySound(playerid, 1150, 0, 0, 0);

    TextDrawItemBox[playerid][i] = CreatePlayerTextDraw(playerid, 1000.000000+posisibaru, 108.500000, "");
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.425000, 1.400000);
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 255);
	PlayerTextDrawBoxColor(playerid, TextDrawItemBox[playerid][i], 50);
	PlayerTextDrawUseBox(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetSelectable(playerid, TextDrawItemBox[playerid][i], 0);

	if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][i])) {
		PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	}

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 367.000+posisibaru, 312.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 37.000, 47.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 370417079);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 255);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetSelectable(playerid, TextDrawItemBox[playerid][i], 0);

	if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][i])) {
		PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	}

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 367.000+posisibaru, 357.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 37.000, 2.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], COLOR_GOLD);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 255);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);

	if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][i])) {
		PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	}

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 368.000+posisibaru, 315.000, "_");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 32.000, 40.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 5);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextDrawItemBox[playerid][i], InfoBox[playerid][index][BoxModel]);
	PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextDrawItemBox[playerid][i], 0, 0);

	if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][i])) {
		PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	}

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 369.000+posisibaru, 313.000, InfoBox[playerid][index][BoxMessage1]);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.119, 0.898);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 150);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);

	if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][i])) {
		PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	}

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 386.000+posisibaru, 347.000, InfoBox[playerid][index][BoxMessage2]);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.119, 0.898);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 2);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 150);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);

	if(IsValidDynamicPlayerTextDraw(playerid, TextDrawItemBox[playerid][i])) {
		PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	}
	return 1;
}