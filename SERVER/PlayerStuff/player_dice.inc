enum E_ROLLEDSTUFF
{
	Text3D:TimeRolled
}
new PlayerRolledVars[MAX_PLAYERS][E_ROLLEDSTUFF];
new timedadu[MAX_PLAYERS];

CMD:roll(playerid, const params[])
{
	new angka;
	if(sscanf(params, "d", angka)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/roll [angka]");

	if(timedadu[playerid])
		return Error(playerid, "Harap tunggu sebentar");
	new randomdadu1 = random(angka);
	if(angka == 0)
		return Error(playerid, "Angka yang anda masukan tidak valid");
	if(angka < 1)
		return Error(playerid, "Angka yang anda masukan tidak valid");
	if(randomdadu1 < 1)
	{
		randomdadu1 = 1;
	}	
	if(angka > randomdadu1)
	{
		randomdadu1 = randomdadu1-1;
	}
	new str[200];
	new Float: x, Float: y, Float: z;
	GetPlayerPos(playerid, x, y, z);

	ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
	format(str, 200, "Rolled : {FF0000}%d{FFFFFF} from: "LG_E"%d", randomdadu1, angka);
	PlayerRolledVars[playerid][TimeRolled] = va_Create3DTextLabel(str, -1,  x, y, z, 15.0, 0, 1);
	timedadu[playerid] = 400;
	SetTimerEx("hapusdadu", 4000, 0, "i", playerid);
	return 1;
}

function hapusdadu(playerid)
{
	timedadu[playerid] = 0;
	Delete3DTextLabel(PlayerRolledVars[playerid][TimeRolled]);
	return 1;
}