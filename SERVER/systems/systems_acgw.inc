#include <YSI_Coding\y_hooks>

forward OnPlayerSpeedCheat(playerid, speedtype);

#include <rAsc>

#define 	MAX_CHEAT_WARNING		2
#define     CRASH_TERSHOLD          5

#define     BulletCrasher -5.5
#define     InvalidSeat1 -1000000.0
#define     InvalidSeat2 1000000.0

#define MAX_DAMAGE_RECORDS 100
#define DAMAGE_TIME_FRAME 10

#define 	INFINITY 			(Float:0x7F800000)
#define 	NAN 	 			(Float:0x7FFFFFFF)
#define 	MIN_DIST_TOLERATE	0.6

new damageRecords[MAX_PLAYERS][MAX_DAMAGE_RECORDS][3];
new damageRecordCount[MAX_PLAYERS];

new
	g_acWarn[MAX_PLAYERS],
    Float:g_acOldSpeed[MAX_VEHICLES];

new
    ram_warn[MAX_PLAYERS],
    g_acCarShot[MAX_PLAYERS];

new backward_warning[MAX_PLAYERS] = {0, ...};

new WarningCode[MAX_PLAYERS][53],
    slapper_warn[MAX_PLAYERS]= {0, ...},
    engine_hack_warn[MAX_PLAYERS]= {0, ...},
    speed_hack[MAX_PLAYERS]= {0, ...},
    airbreak_hack[MAX_PLAYERS]= {0, ...},
    ac_weapon_h[MAX_PLAYERS]= {0, ...},
    ac_ammo_h[MAX_PLAYERS]= {0, ...},
    ac_ammo_inf_h[MAX_PLAYERS]= {0, ...},
    ac_enter_car[MAX_PLAYERS] = {0, ...},
    ac_awh_warning[MAX_PLAYERS] = {0, ...},
    AirBreak_Speed[MAX_PLAYERS],
    AirBreak_Height[MAX_PLAYERS],
    AirBreak_Warn[MAX_PLAYERS],
    Float:AirBreak_Pos[MAX_PLAYERS][3];

new HitData[MAX_PLAYERS][2]; 
    const MAX_HITS = 5; 
    const TIME_INTERVAL = 10;

new fcrash_time_svr;
new fcrash_count;
new fcrash_player[MAX_PLAYERS];

new Float:fcrash_x, Float:fcrash_y, Float:fcrash_z;

new rasc_warning[MAX_PLAYERS];

new AOFCT[MAX_PLAYERS];
new AOFCW[MAX_PLAYERS];

static
    hack_health[MAX_PLAYERS] = {0, ...},
    hack_armour[MAX_PLAYERS] = {0, ...},
    hack_teleport[MAX_PLAYERS] = {0, ...},
    hack_airbreak[MAX_PLAYERS] = {0, ...},
    hack_vehiclehealth[MAX_PLAYERS] = {0, ...},
    hack_vehtele[MAX_PLAYERS] = {0, ...},
    hack_fly[MAX_PLAYERS] = {0, ...},
    UsingMods[MAX_PLAYERS][9];


stock Float:GetVehicleDistanceToVehicle(vehicleid, targetid)
{
	new Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2;

	if (GetVehiclePos(vehicleid, x1, y1, z1) && GetVehiclePos(targetid, x2, y2, z2))
	{
		return VectorSize(x1 - x2, y1 - y2, z1 - z2);
	}

	return NAN;
}

stock AC_IsABike(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 448, 461..463, 468, 521..523, 581, 586, 481, 509, 510: return 1;
	}
	return 0;
}

hook OnGameModeInit()
{
    EnableAntiCheat(3, 0);
    EnableAntiCheat(14, 0);
    EnableAntiCheat(23, 0); // disable Tunning Hack
    EnableAntiCheat(24, 0); // disable Parkour Mod
    EnableAntiCheat(31, 0); // disable Car Shot
    EnableAntiCheat(33, 0); // disable Unfreeze
    EnableAntiCheat(34, 0); // disable AFK Ghost
    EnableAntiCheat(35, 0); // disable Full Aiming
    EnableAntiCheat(36, 0); // disable Fake NPC
    EnableAntiCheat(37, 0); // disable Reconnect
    EnableAntiCheat(38, 0); // disable High Ping
    EnableAntiCheat(39, 0); // disable Dialog Hack
    EnableAntiCheat(40, 0); // disable Protection from sandbox
    EnableAntiCheat(41, 0); // disable Protection from invalid version
    EnableAntiCheat(42, 0); // disable Rcon Hack
    EnableAntiCheat(43, 0); // disable Tuning Crasher
    EnableAntiCheat(45, 0); // disable Dialog Crasher
    EnableAntiCheat(46, 0); // disable Attached Object Crasher
    EnableAntiCheat(47, 0); // disable Weapon Crasher
    EnableAntiCheat(48, 0); // disable Protection from connection flood in one slot
    EnableAntiCheat(49, 0); // disable Callback functions flood
    EnableAntiCheat(50, 0); // disable DoS
    EnableAntiCheat(51, 0); // disable NOPs
    EnableAntiCheat(52, 0); // disable NOPs
}

static GetCodeAC(code)
{    
    new string[128];
    switch(code)
    {
		case 0: string = "AirBreak: On Foot";
		case 1: string = "AirBreak: Inside Vehicle";
		case 2: string = "Teleport Hack: On Foot";
		case 3: string = "Teleport Hack: Inside Vehicle";
		case 4: string = "Teleport Hack: Into/Between Vehicle";
		case 5: string = "Teleport Hack: Vehicle to Player";
		case 6: string = "Teleport Hack: Pickups";
		case 7: string = "FlyHack: On Foot";
		case 8: string = "FlyHack: Inside Vehicle";
		case 9: string = "SpeedHack: On Foot";
		case 10: string = "SpeedHack: Inside Vehicle";
		case 11: string = "Health Hack: Inside Vehicle";
		case 12: string = "Health Hack: On Foot";
		case 13: string = "Armour Hack";
		case 15: string = "Weapon Hack";
		case 16: string = "Ammo Hack: Spawning";
		case 17: string = "Ammo Hack: Infinite";
		case 18: string = "Special Actions Hack";
		case 19: string = "GodMode from a bullets: On Foot";
		case 20: string = "GodMode from a bullets: Inside Vehicle";
		case 21: string = "Invisible Hack";
		case 22: string = "Lagcomp-Spoof";
		case 23: string = "Tuning Hack";
		case 24: string = "Parkour Mod";
		case 25: string = "Quick Turn";
		case 26: string = "Rapid Fire";
		case 27: string = "Fake Spawn";
		case 28: string = "Fake Kill";
		case 29: string = "Aimbot";
		case 30: string = "CJ Run";
		case 31: string = "Car Shot";
		case 32: string = "Car Jacking";
		case 33: string = "UnFreeze";
		case 34: string = "AFK Ghost";
		case 35: string = "Full Aiming";
		case 36: string = "Fake NPC";
		case 37: string = "Reconnect";
		case 38: string = "High Ping";
		case 39: string = "Dialog Hack";
		case 40: string = "Protection from Sandbox";
		case 41: string = "Protection from Invalid Version";
		case 42: string = "Rcon Hack";
		case 43: string = "Tuning Crasher";
		case 44: string = "Invalid Seat Crasher";
		case 45: string = "Dialog Crasher";
		case 46: string = "Attached Object Crasher";
		case 47: string = "Weapon Crasher";
		case 48: string = "Protection from connection flood in one slot";
		case 49: string = "Callback functions flood";
		case 50: string = "Flood by seat changing";
		case 51: string = "DoS";
        case 52: string = "NOPs";
    }
    return string;
}

stock Float:AC_GetVehicleSpeed(vehicleid)
{
    new
        Float:x,
        Float:y,
        Float:z,
        Float:speed;
        
    GetVehicleVelocity(vehicleid, x, y, z);
    speed = VectorSize(x, y, z);
    
    return floatmul(speed, 195.12); 
}

AC_PlayerHasWeapon(playerid, weaponid)
{
	new
	    weapon,
	    ammo;

	for(new i = 0; i < 13; i++) {
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

	    if (weapon == weaponid) return 1;
	}
	return 0;
}

static ResetPlayerWarningCode(playerid) 
{
	for(new i = 0; i < 52; i++) 
    {
		WarningCode[playerid][i] = 0;
	}
	return 1;
}

stock AddDamageRecord(issuerid, playerid, timestamp)
{
    damageRecords[issuerid][damageRecordCount[issuerid]][0] = playerid;
    damageRecords[issuerid][damageRecordCount[issuerid]][1] = timestamp;
    damageRecordCount[issuerid]++;
    if(damageRecordCount[issuerid] >= MAX_DAMAGE_RECORDS)
    {
        damageRecordCount[issuerid] = MAX_DAMAGE_RECORDS - 1;
        for(new i = 0; i < MAX_DAMAGE_RECORDS - 1; i++)
        {
            damageRecords[issuerid][i][0] = damageRecords[issuerid][i + 1][0];
            damageRecords[issuerid][i][1] = damageRecords[issuerid][i + 1][1];
        }
    }
    return 1;
}

stock CheckForCheating(issuerid)
{
    new currentTime = GetTickCount();
    new differentPlayers[MAX_PLAYERS];
    new uniquePlayerCount = 0;
    for(new i = 0; i < damageRecordCount[issuerid]; i++)
    {
        if(currentTime - damageRecords[issuerid][i][1] <= DAMAGE_TIME_FRAME * 1000)
        {
            new damagedPlayer = damageRecords[issuerid][i][0];
            new isUnique = 1;
            for(new j = 0; j < uniquePlayerCount; j++)
            {
                if(differentPlayers[j] == damagedPlayer)
                {
                    isUnique = 0;
                    break;
                }
            }
            
            if(isUnique)
            {
                differentPlayers[uniquePlayerCount] = damagedPlayer;
                uniquePlayerCount++;
            }
        }
    }
    if(uniquePlayerCount > 10)
    {
        SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s(%s) {FF6347}(Damager/Killer)", ReturnName(issuerid), pData[issuerid][pUcp]);
        SendClientMessageEx(issuerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (Damager/Killer)");
        KickEx(issuerid);
    }
    return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {

    if(issuerid != INVALID_PLAYER_ID) {

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        new Float:range = GetPlayerDistanceFromPoint(issuerid, x, y, z);

        if(weaponid == 0 && range >= 15.0) {
            SendClientMessageEx(issuerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: damager (hits %s with fist in %.2fmeter range)", ReturnName(playerid), range);
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using damager/killer", ReturnName(playerid));
            KickEx(issuerid);
        } 
    }
    if(issuerid != INVALID_PLAYER_ID && weaponid <= 15 && !GetPVarInt(issuerid, "IsAtEvent"))
    {
        new currentTime = GetTickCount();
        AddDamageRecord(issuerid, playerid, currentTime);
        CheckForCheating(issuerid);
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}
forward OnCheatDetected(playerid, ip_address[], type, code);
public OnCheatDetected(playerid, ip_address[], type, code)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if(pData[playerid][pAdminDuty])
        return 0;

    switch(code)
    {
        case 0: 
        {/*
            if(++hack_airbreak[playerid] >= 3)
            {
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                hack_airbreak[playerid] = 0;
                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(COLOR_RED, "AntiCheat: %s possible onfoot airbreak hack.", ReturnName(playerid));*/
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using onfoot airbreak (has been kicked) [nex-ac]", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            hack_airbreak[playerid] = 0;
            KickEx(playerid);

        }
        case 1: 
        {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using vehicle airbreak [nex-ac]", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            hack_airbreak[playerid] = 0;
            KickEx(playerid);
        }
        //Teleport hack
        case 2:
        {
            new Float:x, Float:y, Float:z;
            new vw, int;
            int = GetPlayerInterior(playerid);
            vw = GetPlayerVirtualWorld(playerid);
            AntiCheatGetPos(playerid, x, y, z);
            SetPlayerInterior(playerid, int);
            SetPlayerVirtualWorld(playerid, vw);
            SetPlayerPos(playerid, x, y, z);

            if(++hack_teleport[playerid] >= 3)
            {
                SendClientMessageEx(playerid, COLOR_RED, "[Anticheat] "WHITE_E"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                hack_teleport[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(COLOR_RED, "AntiCheat: %s possible teleport hack.", ReturnName(playerid));
        }
        //Vehicle teleport hack
        case 3: 
        {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s possible vehicle teleport hack.", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
        case 4: 
        {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s possible wrap vehicle hack.", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
        //Vehicle teleport to player hack
        case 5: 
        {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s possible vehicle teleport to player hack.", ReturnName(playerid)); 
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
        
        //Flyhack on foot
        case 7: 
        {
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            hack_fly[playerid] = 0;
            KickEx(playerid);
        }    
        //Flyhack in vehicle
        case 8: 
        {

            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            hack_fly[playerid] = 0;
            KickEx(playerid);
        }
        case 9:
        {
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: %s", GetCodeAC(code));
            KickEx(playerid);
        }
        //Speedhack in vehicle
        case 10: 
        {
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: %s", GetCodeAC(code));
            if(++speed_hack[playerid] >= 3) 
            {
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (SpeedHack)");

                speed_hack[playerid] = 0;   
                KickEx(playerid);  
            }
        }
        //Vehicle health hack
        case 11: 
        {
            new vehicleid = GetPlayerVehicleID(playerid);

            if (vehicleid == INVALID_VEHICLE_ID) 
            {
                return 0;
            }
            if(++hack_vehiclehealth[playerid] >= 5)
            {
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                hack_vehiclehealth[playerid] = 0;
                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(COLOR_RED, "AntiCheat: %s possible vehicle health hack.", ReturnName(playerid));
        }
        //Health hack
        case 12: 
        {
            new Float:ac_hp;
            AntiCheatGetHealth(playerid, ac_hp);
            SetPlayerHealthEx(playerid, ac_hp);
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: %s", GetCodeAC(code));
        }
        //Armour Hack
        case 13: 
        {
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: %s", GetCodeAC(code));
            new Float:ac_ap;
            AntiCheatGetArmour(playerid, ac_ap);
            SetPlayerArmour(playerid, ac_ap);
            if(++hack_armour[playerid] >= 3)
            {
                SendAdminMessage(COLOR_RED, "AntiCheat: %s possible armour hack.", ReturnName(playerid));
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                hack_armour[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
        }
        //Weapon hack
        case 15: 
        {

            if(GetPlayerWeapon(playerid) != 0)
                SendAdminMessage(COLOR_RED, "AntiCheat: %s possible weapon hack (%s)", ReturnName(playerid), ReturnWeaponName(GetPlayerWeapon(playerid)));
            else 
                SendAdminMessage(COLOR_RED, "AntiCheat: %s possible weapon hack", ReturnName(playerid));
            defer AC_SetWeaponBack[1000](playerid);

            if (++ac_weapon_h[playerid] >= 3) {

                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                ac_weapon_h[playerid] = 0;
                KickEx(playerid);
            }
        }
        case 16, 17: {


            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: %s", GetCodeAC(code));
            if(++ac_ammo_h[playerid] >= 3) {

                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                ac_weapon_h[playerid] = 0;
                KickEx(playerid); 
            }
        }
        case 18: 
        {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is using special animations hack.", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
        case 21: {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using invisible hack (has been kicked)", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Invisible");
            KickEx(playerid); 
        }
        case 26: 
        {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s possible rapid fire hack.", ReturnName(playerid)); 
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);   
        }
        case 27: {
            KickEx(playerid);
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
        }
        case 32: {
            if(IsPlayerInAnyVehicle(playerid)) {
                GameTextForPlayer(playerid, "~r~CARJACKING NOT ALLOWED", 3000, 3);
                SendAdminMessage(COLOR_RED, "AntiCheat: %s attempts to Car Jacking", ReturnName(playerid)); 
                new Float:x, Float:y, Float:z;
                GetPlayerPos(playerid, x, y, z);
                SetPlayerPos(playerid, x, y, z + 1.5);
                SetCameraBehindPlayer(playerid);
            }
        }
        case 40: 
        {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is using sandboxie.", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
        default: {

            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: %s", GetCodeAC(code));
            if(++WarningCode[playerid][code] >= 3) {

                new ip[24];
                GetPlayerIp(playerid, ip, sizeof(ip));
                SendAdminMessage(COLOR_RED, "AntiCheat: %s (%s) possible %s", ReturnName(playerid), ip, GetCodeAC(code));
                KickEx(playerid);
            }
        }
    }
    return 1;
}
hook OnPlayerConnect(playerid) 
{
    backward_warning[playerid] = 0;
	ResetPlayerWarningCode(playerid);
    vehLastEntered[playerid] = 0;
    HitData[playerid][0] = 0; 
    HitData[playerid][1] = 0; 
    lastVehicleID[playerid] = INVALID_VEHICLE_ID;
    fcrash_count = 0;
    fcrash_player[playerid] = 0;
    rasc_warning[playerid] = 0;
    ac_enter_car[playerid] = 0;
    ac_awh_warning[playerid ]= 0;
    slapper_warn[playerid] = 0;
    engine_hack_warn[playerid] = 0;
    speed_hack[playerid] = 0;
    airbreak_hack[playerid] = 0;
    hack_health[playerid] = 0;
    hack_armour[playerid] = 0;
    hack_teleport[playerid] = 0;
    hack_airbreak[playerid] = 0;
    hack_vehiclehealth[playerid] = 0;
    hack_vehtele[playerid] = 0;
    hack_fly[playerid] = 0;
    ac_weapon_h[playerid] = 0;
    ac_ammo_h[playerid] = 0;
    ac_ammo_inf_h[playerid] = 0;
    ram_warn[playerid] = 0;
    for(new i = 0; i < 9; i++) {
        UsingMods[playerid][i] = false;
    }
}


hook OnPlayerDisconnect(playerid, reason) 
{
    if(pData[playerid][pSpawned] && reason == 0) {


        if(GetTickCount() - fcrash_time_svr < 10000) {
            foreach(new i : Player) if(GetPlayerDistanceFromPoint(i, fcrash_x, fcrash_y, fcrash_z) <= 25.0 && !pData[i][pAdminDuty]) {
                if(i == playerid) {
                    continue;
                }

                fcrash_player[i]++;
                fcrash_count++;

                if(fcrash_player[i] >= 5) {
                    SendAdminMessage(COLOR_RED, "AntiCheat: %s kemungkinan menggunakan crasher", ReturnName(i));
                    fcrash_player[i] = 0;
                }
                break;
            }
        }


        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        fcrash_x = x;
        fcrash_y = y;
        fcrash_z = z;
        fcrash_time_svr = GetTickCount();
    }

	ResetPlayerWarningCode(playerid);

    slapper_warn[playerid] = 0;
    engine_hack_warn[playerid] = 0;
    speed_hack[playerid] = 0;
    airbreak_hack[playerid] = 0;
    hack_health[playerid] = 0;
    hack_armour[playerid] = 0;
    hack_teleport[playerid] = 0;
    hack_airbreak[playerid] = 0;
    hack_vehiclehealth[playerid] = 0;
    hack_vehtele[playerid] = 0;
    hack_fly[playerid] = 0;
    ac_weapon_h[playerid] = 0;
    ac_ammo_h[playerid] = 0;
    ac_ammo_inf_h[playerid] = 0;

}

/* Funcs */

stock Float:AC_GetPlayerSpeed(playerid, bool:kmh = false)
{
    new 
        Float:Vx,
        Float:Vy,
        Float:Vz,
        Float:rtn;

    if(IsPlayerInAnyVehicle(playerid)) {
        GetVehicleVelocity(GetPlayerVehicleID(playerid), Vx, Vy, Vz);
    } else {
        GetPlayerVelocity(playerid, Vx, Vy, Vz);        
    }

    rtn = floatsqroot(floatabs(floatpower(Vx + Vy + Vz, 2)));
    return kmh ? (rtn * 100 * 1.61) : (rtn * 100);
}
timer OnUpsideDownCheck[500](playerid, vehicleid) {

    new Float:health;
    GetVehicleHealth(vehicleid, health);
    if(IsVehicleUpsideDown(vehicleid) && health < 300.0) {
        SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Vehicle Troller");
        FlipVehicle(vehicleid);
        SetVehicleHealth(vehicleid, 1000.0);
        SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using vehicle troller (has been kicked)", ReturnName(playerid));
        KickEx(playerid);
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
        ac_enter_car[playerid]++;

        if(ac_enter_car[playerid] > 5) {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using vehicle troller (has been kicked)", ReturnName(playerid));
            KickEx(playerid);
        }
        new vehicleid = GetPlayerVehicleID(playerid), Float:health, current_time = GetTickCount();

        if(lastVehicleID[playerid] != vehicleid && vehLastEntered[playerid] != 0) {
            if(current_time - vehLastEntered[playerid] < 2000) {
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Vehicle Troller");
                SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using vehicle troller (has been kicked)", ReturnName(playerid));
                KickEx(playerid);
            }
        }
        GetVehicleHealth(vehicleid, health);

        vehLastPlayerID[vehicleid] = playerid;
        vehLastEntered[vehicleid] = GetTickCount();
        lastVehicleID[playerid] = vehicleid;
        vehLastHealth[vehicleid] = health;

        // upside down
        defer OnUpsideDownCheck[500](playerid, vehicleid);
    }
    if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {        
        new vehicleid = lastVehicleID[playerid];

        vehLastExited[vehicleid] = GetTickCount();

        new Float:health;
        GetVehicleHealth(vehicleid, health);

        if(vehLastExited[vehicleid] - vehLastEntered[vehicleid] < 2000 && health < 300.0) {
            SetVehicleHealth(vehicleid, 1000.0);
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Vehicle Destroyer");
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using vehicle destroyer", ReturnName(playerid));
            KickEx(playerid);
        }
    }
    if(newstate == PLAYER_STATE_SPECTATING && (oldstate == PLAYER_STATE_ONFOOT || oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)) {
        if(!g_PlayerSpectating[playerid] && !pData[playerid][pAdminDuty]) {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using invisible hack (has been kicked)", ReturnName(playerid));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Invisible");
            KickEx(playerid); 
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    if(killerid != INVALID_PLAYER_ID) {

        if(!pData[killerid][pSpawned]) {

            SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using fakespawn (has been kicked)", ReturnName(playerid));
            KickEx(killerid);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

ptask internal_reduce_warning[4000](playerid) {
	if(ac_enter_car[playerid] > 0)
	{
		ac_enter_car[playerid]--;
	}
    if(ram_warn[playerid] > 0) {
        ram_warn[playerid]--;
    }
    if(g_acCarShot[playerid] > 0) {
        g_acCarShot[playerid]--;
    }
    if(g_acWarn[playerid] > 0) {
        g_acWarn[playerid]--;
    }
    return 1;
}

stock IsVehicleAir(playerid, vehicleid)
{
	vehicleid = GetPlayerVehicleID(playerid);
	switch(GetVehicleModel(vehicleid))
	{
		case 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 498, 563, 447, 469: return 1;
	}
	return 0;
}

stock Float:abrk_GetPlayerSpeed(playerid){
	new Float:x,Float:y,Float:z;
	GetPlayerVelocity(playerid,x,y,z);
	return floatmul(VectorSize(x,y,z),1.0);
}
/*
ptask airbreak_update[500](playerid) {

    if(airbreak_status) {
        if(pData[playerid][pSpawned] && !pData[playerid][pKicked] && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0 && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE && !pData[playerid][pAdminDuty]) {

            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                new Float:x, Float:y, Float:z, Float:diff, Float:z_mapandreas;
                new vehicleid = GetPlayerVehicleID(playerid);
                GetVehiclePos(vehicleid, x ,y , z);
                MapAndreas_FindZ_For2DCoord(x, y, z_mapandreas);
                diff = z - z_mapandreas;
                new Float:speed = AC_GetVehicleSpeed(vehicleid);

                if(diff > 5.0 && AC_GetVehicleSpeed(vehicleid) > 5.0 && GetClosestDynObjectToPlayer(playerid, 10.0) == INVALID_STREAMER_ID) {

                    if(veh_arbrk_speed[playerid] >= speed && speed <= veh_arbrk_speed[playerid] + 1.0) {
                        veh_arbrk_warn[playerid]++;
                        if(veh_arbrk_warn[playerid] >= 3) {
                            SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s(%s) {FF6347}(Airbreak)", ReturnName(playerid), pData[playerid][pUcp]);
                            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (Airbreak)");
                            KickEx(playerid);
                        }
                    }  
                }
                veh_arbrk_speed[playerid] = speed;
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                new Float:x, Float:y, Float:z, Float:diff, Float:z_mapandreas;
                GetPlayerPos(playerid, x, y, z);
                MapAndreas_FindZ_For2DCoord(x, y, z_mapandreas);
                diff = z - z_mapandreas;
                new Float:speed = AC_GetPlayerSpeed(playerid);
                if(diff > 5.0 && speed >= 10.0 && GetClosestDynObjectToPlayer(playerid, 10.0) == INVALID_STREAMER_ID) {
                    if(oft_arbrk_speed[playerid] >= speed && speed <= oft_arbrk_speed[playerid] + 1.0) {
                        oft_arbrk_warn[playerid]++;
                        if(oft_arbrk_warn[playerid] >= 3) {
                            SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s(%s) {FF6347}(Airbreak)", ReturnName(playerid), pData[playerid][pUcp]);
                            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (Airbreak)");
                            KickEx(playerid);
                        }
                    }
                }
                oft_arbrk_speed[playerid] = speed;
            }
        }
    }
    return 1;
}*/

stock AC_GetNearbyPlayers(playerid)
{
	new count, intid, worldid, Float: posX, Float: posY, Float: posZ;
	intid = GetPlayerInterior(playerid);
	worldid = GetPlayerVirtualWorld(playerid);
	GetPlayerPos(playerid, posX, posY, posZ);

 	foreach(new i : StreamedPlayer[playerid]) {

	    if(playerid == i) 
            continue;

		if(intid == GetPlayerInterior(i) && worldid == GetPlayerVirtualWorld(i) && IsPlayerInRangeOfPoint(i, posX, posY, posZ, 50.0)) count++;
	}
	return count;
}

ptask anti_cheat_update[1000](playerid)
{
    new
        ac_weapon[13],
        ac_ammo[13]
        ;

    if(HitData[playerid][0] > 0) {
        HitData[playerid][0]--;
    }

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
        new vehicleid = GetPlayerVehicleID(playerid),
            Float:speed;

        speed = AC_GetVehicleSpeed(vehicleid);

        if(IsVehicleDrivingBackwards(vehicleid)) {

            new keys, ud, lr;

            GetPlayerKeys(playerid, keys, ud, lr);
            if(speed >= 60.0 && keys == 36) {
                SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using speedhack (forward-backward)", ReturnName(playerid));
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Backwards Speedhack");
                if(++backward_warning[playerid] >= 3) {
                    KickEx(playerid);
                }     
            }
            if(speed >= 80.0) {
                SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using speedhack (forward-backward)", ReturnName(playerid));
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Backwards Speedhack");
                if(++backward_warning[playerid] >= 3) {
                    KickEx(playerid);
                }  
            }
        }

        new keys, ud, lr;
        GetPlayerKeys(playerid, keys, ud, lr);

        if(!keys && speed > 230) {
            if(++g_acWarn[playerid] > 3) // toleransi
            {
                SendClientMessage(playerid, -1, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (SpeedHack #1)");
                g_acWarn[playerid] = 0;   
                KickEx(playerid);
            }
        }

        if(speed >= 230 && speed >= g_acOldSpeed[vehicleid] && speed <= g_acOldSpeed[vehicleid] + 1.0) {
            if(++g_acWarn[playerid] > 3) 
            {
                SendClientMessage(playerid, -1, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (SpeedHack #2)");
                g_acWarn[playerid] = 0;   
                KickEx(playerid);  
            }   
        }
        g_acOldSpeed[vehicleid] = speed;
    }
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && !pData[playerid][pAdminDuty]) {
        SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using jetpack spawn (has been kicked)", ReturnName(playerid));
        SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Jetpack");
        KickEx(playerid);
    }


    if(!pData[playerid][pAdminDuty]) {

        if(pData[playerid][pSpawned] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
            if(AC_GetPlayerSpeed(playerid) > 100 && GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID) {
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: Speed Hack");
                KickEx(playerid);
            }
        }

        if(!TaserData[playerid][TaserEnabled] && !IsAtEvent[playerid] && !pData[playerid][pInjured]) {

            for(new i = 0; i < 13; i++) 
            {
                GetPlayerWeaponData(playerid, i, ac_weapon[i], ac_ammo[i]);

                if(ac_weapon[i] && pData[playerid][pGuns][g_aWeaponSlots[ac_weapon[i]]] != ac_weapon[i]) 
                {
                    SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using weapon hack (%s)", ReturnName(playerid), ReturnWeaponName(ac_weapon[i]));
                    defer AC_SetWeaponBack[1000](playerid);
                    ac_weapon_h[playerid]++;

                    if(ac_weapon_h[playerid] >= 3) 
                    {
                        SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using weapon hack %s (has been kicked)", ReturnName(playerid), ReturnWeaponName(ac_weapon[i]));
                        ac_weapon_h[playerid] = 0;
                        SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (Weapon Hack)");
                        KickEx(playerid);
                    }
                }
            }        
        }
        if (AC_GetPlayerSpeed(playerid) > 350.0)
        {
            new ip[24];
            GetPlayerIp(playerid, ip, sizeof(ip));
            SendAdminMessage(COLOR_RED, "AntiCheat: Cheat detected on {FFFF00}%s (%s) [%s] {FF6347}(%s)", ReturnName(playerid), pData[playerid][pUcp], ip, (IsPlayerInAnyVehicle(playerid)) ? ("Vehicle Speedhack") : ("Onfoot Speedhack"));
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (SpeedHack)");
            KickEx(playerid);
        }

        new vehicleid = GetPlayerVehicleID(playerid);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsAPlane(vehicleid) && AC_GetVehicleSpeed(vehicleid) > 250) 
        {
            if(++speed_hack[playerid] > 5) 
            {
                SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s {FF6347}(Vehicle Speedhack)", ReturnName(playerid));
                SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (SpeedHack)");
                speed_hack[playerid] = 0;   
                KickEx(playerid);  
            }
        }
        new Float:X,Float:Y,Float:Z;
        GetPlayerPos(playerid,X,Y,Z);
        if(Z == BulletCrasher || !(InvalidSeat1 <= Z <= InvalidSeat2)) 
        {
            new tipcrasher[56];
            tipcrasher= "Bad Vehicle Crasher";
            if(Z == BulletCrasher)
                tipcrasher= "Bullet Crasher";

            SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s {FF6347}(%s)", ReturnName(playerid), tipcrasher);
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (Crasher)");
            KickEx(playerid);
        }
        if(AC_PlayerHasWeapon(playerid, WEAPON_BOMB) && !pData[playerid][pAdminDuty]) 
        {
            CallLocalFunction("OnPlayerCrasher", "d", playerid);
        }
        new Float:x,Float:y,Float:z;
        GetPlayerCameraFrontVector(playerid,x,y,z);
        if(floatcmp(1.0,floatabs(x))==-1 || floatcmp(1.0,floatabs(y))==-1 || floatcmp(1.0,floatabs(z))==-1)
        {
            if(AOFCT[playerid] < GetTickCount())
                AOFCW[playerid] = 0;
            else 
                AOFCW[playerid]++;
                
            if(AOFCW[playerid] < 2) 
                AOFCT[playerid]= GetTickCount()+1000; 
            else {
                CallLocalFunction("OnPlayerCrasher", "d", playerid);
            }
        }
        if(!pData[playerid][pSpawned] && GetPlayerSkin(playerid) == 0 && AC_GetPlayerSpeed(playerid) > 1.0) {
            SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (Fake Spawn)");
            SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s(%s) {FF6347}(Fake Spawn)", ReturnName(playerid), pData[playerid][pUcp]);
            KickEx(playerid);        
        }
        new speed, time = GetTickCount();
        if(GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID && GetPlayerSurfingObjectID(playerid) == INVALID_OBJECT_ID && GetPlayerPing(playerid) < 260 && AC_GetPlayerSpeed(playerid) < 30 && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_ONFOOT))
        {
            speed = floatround((GetPlayerDistanceFromPoint(playerid, AirBreak_Pos[playerid][0], AirBreak_Pos[playerid][1], AirBreak_Pos[playerid][2]) / float (time - AirBreak_Height[playerid])) * 1000.0);
            GetPlayerPos(playerid, AirBreak_Pos[playerid][0], AirBreak_Pos[playerid][1], AirBreak_Pos[playerid][2]);
            if(speed > 65 && AirBreak_Speed[playerid] > 65)
            {
                AirBreak_Warn[playerid] ++;
                if(AirBreak_Warn[playerid] < 5)
                {
                    SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s {FF6347}(Airbreak Surfing)", ReturnName(playerid));
                    AirBreak_Speed[playerid] = 0;
                }
                else
                {
                    SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s {FF6347}(Airbreak Surfing)", ReturnName(playerid));
                    KickEx(playerid);
                }
            }
            AirBreak_Speed[playerid] = speed;
        }
        else
        {
            GetPlayerPos(playerid, AirBreak_Pos[playerid][0], AirBreak_Pos[playerid][1], AirBreak_Pos[playerid][2]);
            AirBreak_Speed[playerid] = 0;
        }
        AirBreak_Height[playerid] = time;
    }
    return 1;
}


function OnPlayerCrasher(playerid) 
{
    SendAdminMessage(COLOR_RED, "AntiCheat: {FFFFFF}Cheat detected on {FFFF00}%s {FF6347}(Crasher)", ReturnName(playerid));
    SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been kicked from the server because of using some suspicious programs (Crasher)");
    KickEx(playerid);
    return 1;
}

function UAC_OnPlayerUpdate(playerid) {
    new vehicleid = GetPlayerVehicleID(playerid), nearest_vehicleid;
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && AC_GetVehicleSpeed(vehicleid) > 5.0) {

		new Float:x, Float:y, Float:z;

		if (!GetVehiclePos(vehicleid, x, y, z))
		{
			return INVALID_VEHICLE_ID;
		}

		new Float:f_dist = INFINITY, Float:e_sec_dist;

		nearest_vehicleid = INVALID_VEHICLE_ID;

		for(new i = 0; i < MAX_VEHICLES; i++) if(IsValidVehicle(i))
		{
			if (i != vehicleid && (e_sec_dist = GetVehicleDistanceFromPoint(i, x, y, z)) < f_dist)
			{
				f_dist = e_sec_dist;
				nearest_vehicleid = i;
			}
		}
        
        if(nearest_vehicleid != INVALID_VEHICLE_ID && !AC_IsABike(nearest_vehicleid)) {
            new Float:v_dist_e = GetVehicleDistanceToVehicle(vehicleid, nearest_vehicleid);
            if(v_dist_e <= MIN_DIST_TOLERATE) {
                new Float:px, Float:py, Float:pz;
                GetPlayerPos(playerid, px, py, pz);
                SetPlayerPos(playerid, px, py, pz + 2.5);
                GameTextForPlayer(playerid, "~r~NO COLLISION DETECTED", 3000, 3);
                SendAdminMessage(COLOR_RED, "AntiCheat: %s is possible using nocollision.", ReturnName(playerid));
            }
        }
    }
    return 1;
}
timer AC_SetWeaponBack[1000](playerid) 
{
    if(!GetPVarInt(playerid, "IsAtEvent")) {

        new
            ac_weapon[13],
            ac_ammo[13];

        for (new i = 0; i < 12; i++) 
        {
            AntiCheatGetWeaponData(playerid, i, ac_weapon[i], ac_ammo[i]);

            if (pData[playerid][pGuns][i] != ac_weapon[i]) 
            {
                ResetWeapon(playerid, ac_weapon[i]);
            }
        }
    }
    return 1;
}

timer AC_SetHealthBack[1000](playerid, Float:health) 
{
    SetPlayerHealthEx(playerid, health);
}

timer AC_SetArmorBack[1000](playerid, Float:armour) 
{    
    SetPlayerArmourEx(playerid, armour);
}

public OnPlayerSpeedCheat(playerid, speedtype) {
        
    if(!pData[playerid][pAdminDuty]) {

        new rasc_names[][] = {
            "Onfoot Speedhack",
            "Vehicle Speedhack",
            "Plane Speedhack"
        };

        SendClientMessageEx(playerid, COLOR_YELLOW, "(AntiCheat) {FFFFFF}You have been detected for using: %s", rasc_names[speedtype]);
        if(++rasc_warning[playerid] >= 3) {
            SendAdminMessage(COLOR_RED, "AntiCheat: %s has been detected for using: %s (rasc)", ReturnName(playerid), rasc_names[speedtype]);
            KickEx(playerid);
        } 
    }
    return 1;
}

forward internal_resetImmun(playerid);
public internal_resetImmun(playerid) {

    if(g_aPlayerImmun[playerid])
        g_aPlayerImmun[playerid] = 0;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {

    g_aEnterCar[playerid] = 1;
    SetTimerEx("internal_TolerateEnter", 10000, false, "d", playerid);
    return 1;
}

forward internal_TolerateEnter(playerid);
public internal_TolerateEnter(playerid) {

    if(!g_aEnterCar[playerid])
        return 1;

    g_aEnterCar[playerid] = 0;

    return 1;
}

stock IsVehicleUpsideDown(vehicleid)
{
    new
        Float:w,
        Float:x,
        Float:y,
        Float:z;

    GetVehicleRotationQuat(vehicleid, w, x, y, z);

    new Float:angle = atan2(((y * z) + (w * x)) * 2.0, (w * w) - (x * x) - (y * y) + (z * z));

    return ((angle > 90.0) || (angle < -90.0));
}

stock FlipVehicle(vehicleid)
{
	new
	    Float:fAngle;

	GetVehicleZAngle(vehicleid, fAngle);

	SetVehicleZAngle(vehicleid, fAngle);
	SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
}

stock IsVehicleDrivingBackwards(vehicleid)
{
    new
        Float:Float[3]
    ;
    if(GetVehicleVelocity(vehicleid, Float[1], Float[2], Float[0]))
    {
        GetVehicleZAngle(vehicleid, Float[0]);
        if(Float[0] < 90)
        {
            if(Float[1] > 0 && Float[2] < 0) return true;
        }
        else if(Float[0] < 180)
        {
            if(Float[1] > 0 && Float[2] > 0) return true;
        }
        else if(Float[0] < 270)
        {
            if(Float[1] < 0 && Float[2] > 0) return true;
        }
        else if(Float[1] < 0 && Float[2] < 0) return true;
    }
    return false;
}