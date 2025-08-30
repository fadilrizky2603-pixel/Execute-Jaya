#include <YSI_Coding\y_hooks>

#define MAX_WEAPONS 47
#define DAMAGE_PER_PAGE 10

new Float:CustomWeaponDamage[MAX_WEAPONS];
new WeaponPage[MAX_PLAYERS];
new const WeaponNames[MAX_WEAPONS][] = {
    "Fist", "Brass Knuckles", "Golf Club", "Night Stick", "Knife", "Baseball Bat", "Shovel", "Pool Cue", "Katana", "Chainsaw",
    "Purple Dildo", "Dildo", "Vibrator", "Silver Vibrator", "Flower", "Cane", "Grenade", "Tear Gas", "Molotov", "Vehicle Gun",
    "Vehicle Gun", "Vehicle Gun", "Colt 45", "Silenced Pistol", "Deagle", "Shotgun", "Sawn-off", "Combat Shotgun", "Mac-10", "MP5",
    "AK-47", "M4", "Tec-9", "Rifle", "Sniper", "Rocket Launcher", "Heat Seeking", "Flamethrower", "Minigun", "Satchel",
    "Detonator", "Spraycan", "Fire Extinguisher", "Camera", "Night Vision", "Thermal Vision", "Parachute"
};

stock LoadWeaponDamage()
{
    new File:f = fopen("weapon_damage.cfg", io_read);
    if (!f) return print("[WeaponDamage] File tidak ditemukan.");

    new line[64], wid;
    new Float:damage;

    while (fread(f, line))
    {
        if (sscanf_manual(line, wid, damage)) continue;
        if (wid >= 0 && wid < MAX_WEAPONS) CustomWeaponDamage[wid] = damage;
    }
    fclose(f);
    print("[WeaponDamage] Damage berhasil dimuat.");
}

stock SaveWeaponDamage()
{
    new File:f = fopen("weapon_damage.cfg", io_write);
    if (!f) return print("[WeaponDamage] Gagal menyimpan file.");

    new line[64];
    for (new i = 0; i < MAX_WEAPONS; i++)
    {
        format(line, sizeof(line), "%d %.2f\n", i, CustomWeaponDamage[i]);
        fwrite(f, line);
    }
    fclose(f);
    print("[WeaponDamage] Damage berhasil disimpan.");
}

stock sscanf_manual(const input[], &index, &Float:value)
{
    new tmp1[16], tmp2[16];
    if (sscanf2fields(input, tmp1, sizeof(tmp1), tmp2, sizeof(tmp2)) == 2)
    {
        index = strval(tmp1);
        value = floatstr(tmp2);
        return 0;
    }
    return 1;
}

stock sscanf2fields(const input[], field1[], size1, field2[], size2)
{
    new i = 0, j = 0, step = 0;
    while (input[i])
    {
        if (input[i] == ' ' || input[i] == '\t')
        {
            if (step == 0) { field1[j] = 0; j = 0; step = 1; }
            i++;
            continue;
        }

        if (step == 0 && j < size1 - 1) field1[j++] = input[i];
        else if (step == 1 && j < size2 - 1) field2[j++] = input[i];

        i++;
    }
    if (step == 1) field2[j] = 0;
    return (step == 1) ? 2 : 0;
}

stock ShowWeaponDamageDialog(playerid)
{
    new page = WeaponPage[playerid];
    new start = page * DAMAGE_PER_PAGE;
    new end = start + DAMAGE_PER_PAGE;
    if (end > MAX_WEAPONS) end = MAX_WEAPONS;

    new dialog[2048];
    dialog[0] = '\0';

    for (new i = start; i < end; i++)
    {
        format(dialog, sizeof(dialog), "%s%d. %s - %.2f\n", dialog, i, WeaponNames[i], CustomWeaponDamage[i]);
    }

    //new totalItems = end - start;
    new hasNext = (page + 1) * DAMAGE_PER_PAGE < MAX_WEAPONS;
    new hasPrev = page > 0;

    if (hasNext) strcat(dialog, "{40FF00}>>> Next");
    if (hasPrev) strcat(dialog, "\n{FF0000}<<< Prev");

    ShowPlayerDialogPages(playerid, DIALOG_DAMAGE_LIST, DIALOG_STYLE_LIST, "Weapon Damage Settings", dialog, "Edit", "Close", DAMAGE_PER_PAGE, "{40FF00}>>>", "{FF0000}<<<");
}

CMD:damagetoggle(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
    WeaponPage[playerid] = 0;
    ShowWeaponDamageDialog(playerid);
    return 1;
}

hook OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[], btn_next_index, btn_previous_index)
{
    if (dialogid == DIALOG_DAMAGE_LIST && response)
    {
        new page = WeaponPage[playerid];
        new start = page * DAMAGE_PER_PAGE;
        new end = start + DAMAGE_PER_PAGE;
        if (end > MAX_WEAPONS) end = MAX_WEAPONS;

        if (listitem == btn_next_index) WeaponPage[playerid]++;
        else if (listitem == btn_previous_index) WeaponPage[playerid]--;
        else if (listitem < (end - start))
        {
            new index = start + listitem;
            SetPVarInt(playerid, "edit_weaponid", index);
            new str[64];
            format(str, sizeof(str), "Masukkan damage baru untuk %s:", WeaponNames[index]);
            ShowPlayerDialog(playerid, DIALOG_DAMAGE_INPUT, DIALOG_STYLE_INPUT, "Edit Damage", str, "Set", "Cancel");
            return 1;
        }

        ShowWeaponDamageDialog(playerid);
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if (dialogid == DIALOG_DAMAGE_INPUT && response)
    {
        new wid = GetPVarInt(playerid, "edit_weaponid");
        new Float:damage = floatstr(inputtext);
        CustomWeaponDamage[wid] = damage;
        SaveWeaponDamage();
        SendClientMessage(playerid, -1, "Damage berhasil diubah dan disimpan!");
        ShowWeaponDamageDialog(playerid);
        return 1;
    }
    return 0;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:x, Float:y, Float:z)
{
    if (hittype == BULLET_HIT_TYPE_PLAYER)
    {
        new Float:damage = CustomWeaponDamage[weaponid];
        new Float:hp;
        GetPlayerHealth(hitid, hp);
        SetPlayerHealth(hitid, hp - damage);
    }
    return 1;
}

hook OnGameModeInit()
{
    LoadWeaponDamage();
    return 1;
}

hook OnGameModeExit()
{
    SaveWeaponDamage();
    return 1;
}
