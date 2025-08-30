
#include <YSI_Coding\y_hooks>

stock ReloadWeapon(playerid, weaponid, clipName[], ammoAdd)
{
    new slot = g_aWeaponSlots[weaponid];

    // Cek senjata aktif di tangan dan cocok dengan slot data
    if(GetPlayerWeapon(playerid) == weaponid && AccountData[playerid][pGuns][slot] == weaponid)
    {
        AccountData[playerid][pAmmo][slot] += ammoAdd;
        GivePlayerWeapon(playerid, weaponid, AccountData[playerid][pAmmo][slot]);

        Inventory_Remove(playerid, clipName, 1);

        new msg[64];
        format(msg, sizeof msg, "Reload berhasil: %s (+%d peluru)", clipName, ammoAdd);
        ShowTDN(playerid, NOTIFICATION_SUKSES, msg);
    }
    else
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata tidak cocok atau tidak sedang dipegang.");
    }
}

stock AddWeaponToInventory(playerid, itemname[])
{
    new weaponid;
    
    // Tentukan weaponid berdasarkan itemname
    if (strcmp(itemname, "Colt 45", true) == 0)
    {
        weaponid = 22; 
    }
    if (strcmp(itemname, "Silenced Pistol", true) == 0)
    {
        weaponid = 23;  
    }
    if (strcmp(itemname, "Desert Eagle", true) == 0)
    {
        weaponid = 24;
    }
    if (strcmp(itemname, "Shotgun", true) == 0)
    {
        weaponid = 25;
    }
    if (strcmp(itemname, "Sawn-off Shotgun", true) == 0)
    {
        weaponid = 26;
    }
    if (strcmp(itemname, "UZI", true) == 0)
    {
        weaponid = 28;
    }
    if (strcmp(itemname, "TEC9", true) == 0)
    {
        weaponid = 32;
    }
    else if (strcmp(itemname, "AK-47", true) == 0)
    {
        weaponid = 30;
    }
    else
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak bisa disimpan.");
    }

    // Tambahkan senjata ke inventory
    Inventory_Add(playerid, weaponid, 1);  // Menambahkan satu senjata berdasarkan weaponid
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Senjata berhasil disimpan ke inventory.");
}
