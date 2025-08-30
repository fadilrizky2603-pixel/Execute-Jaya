#include <YSI_Coding\y_hooks>

new DriveByWeapons[46]; // max weaponid = 46
new PlayerWeaponIndex[MAX_PLAYERS];
new DriveByWeaponCount = 0;

hook OnGameModeInit()
{
    // Generate all drive-by compatible weapons (except Desert Eagle)
    for (new i = 0; i <= 46; i++) // Weapon IDs range from 0 - 46
    {
        // Skip unarmed (0), melee, and heavy weapons, also skip Desert Eagle (24)
        if (i == 0 || i == 1 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 ||
            i == 15 || i == 16 || i == 17 || i == 18 || i == 24 || i == 35 || i == 36 ||
            i == 37 || i == 38 || i == 39) continue;

        DriveByWeapons[DriveByWeaponCount++] = i;
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    PlayerWeaponIndex[playerid] = 0;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if ((newkeys & KEY_YES) && !(oldkeys & KEY_YES))
    {
        if (IsPlayerInAnyVehicle(playerid) &&
            (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER))
        {
            PlayerWeaponIndex[playerid]++;
            if (PlayerWeaponIndex[playerid] >= DriveByWeaponCount)
            {
                PlayerWeaponIndex[playerid] = 0;
            }

            new weaponid = DriveByWeapons[PlayerWeaponIndex[playerid]];
            SetPlayerArmedWeapon(playerid, weaponid);
            GameTextForPlayer(playerid, "~w~Weapon Switched", 1000, 3);
        }
    }
    return 1;
}