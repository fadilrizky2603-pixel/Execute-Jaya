
#include <YSI_Coding\y_hooks>

#define MAX_AC 53
#define MAX_PER_PAGE 20

new AntiCheatStatus[MAX_AC];
new AntiCheatPage[MAX_PLAYERS];

new const AntiCheatNames[MAX_AC][] = {
    "Anti-AirBreak (onfoot)", "Anti-AirBreak (in vehicle)", "Anti-teleport hack (onfoot)", "Anti-teleport hack (in vehicle)",
    "Anti-teleport hack (into/between vehicles)", "Anti-teleport hack (vehicle to player)", "Anti-teleport hack (pickups)",
    "Anti-FlyHack (onfoot)", "Anti-FlyHack (in vehicle)", "Anti-SpeedHack (onfoot)", "Anti-SpeedHack (in vehicle)",
    "Anti-Health hack (in vehicle)", "Anti-Health hack (onfoot)", "Anti-Armour hack", "Anti-Money hack", "Anti-Weapon hack",
    "Anti-Ammo hack (add)", "Anti-Ammo hack (infinite)", "Anti-Special actions hack", "Anti-GodMode from bullets (onfoot)",
    "Anti-GodMode from bullets (in vehicle)", "Anti-Invisible hack", "Anti-lagcomp-spoof", "Anti-Tuning hack",
    "Anti-Parkour mod", "Anti-Quick turn", "Anti-Rapid fire", "Anti-FakeSpawn", "Anti-FakeKill", "Anti-Pro Aim",
    "Anti-CJ run", "Anti-CarShot", "Anti-CarJack", "Anti-UnFreeze", "Anti-AFK Ghost", "Anti-Full Aiming", "Anti-Fake NPC",
    "Anti-Reconnect", "Anti-High ping", "Anti-Dialog hack", "Protection from sandbox", "Protection from invalid version",
    "Anti-Rcon hack", "Anti-Tuning crasher", "Anti-Invalid seat crasher", "Anti-Dialog crasher",
    "Anti-Attached object crasher", "Anti-Weapon Crasher", "Protection from connection flood in one slot",
    "Anti-callback functions flood", "Anti-flood by seat changing", "Anti-DoS", "Anti-NOPs"
};

// Variabel global untuk menyimpan index tombol next dan prev tiap player
new BtnNextIndex[MAX_PLAYERS];
new BtnPrevIndex[MAX_PLAYERS];

stock LoadAntiCheatSettings()
{
    new File:handle = fopen("nex-ac_settings.cfg", io_read);
    if (!handle) return;

    new line[16], index = 0;
    while (fread(handle, line) && index < MAX_AC)
        AntiCheatStatus[index++] = strval(line);

    fclose(handle);
}

stock SaveAntiCheatSettings()
{
    new File:handle = fopen("nex-ac_settings.cfg", io_write);
    if (!handle) return;

    new line[32];
    for (new i = 0; i < MAX_AC; i++)
    {
        format(line, sizeof(line), "%d\r\n", AntiCheatStatus[i]);
        fwrite(handle, line);
    }
    fclose(handle);
}

stock ShowAntiCheatDialog(playerid)
{
    new page = AntiCheatPage[playerid];
    new start = page * MAX_PER_PAGE;
    new end = start + MAX_PER_PAGE;
    if (end > MAX_AC) end = MAX_AC;

    new dialog[2048];
    dialog[0] = '\0';

    // Tampilkan daftar status AntiCheat sesuai halaman
    for (new i = start; i < end; i++)
    {
        format(dialog, sizeof(dialog), "%s%d. %s - %s\n", dialog, i + 1,
            AntiCheatNames[i], AntiCheatStatus[i] ? "{00FF00}Enabled" : "{FF0000}Disabled");
    }

    // Reset index tombol next dan prev
    BtnNextIndex[playerid] = -1;
    BtnPrevIndex[playerid] = -1;

    new totalItems = end - start;
    new hasNext = (page + 1) * MAX_PER_PAGE < MAX_AC;
    new hasPrev = page > 0;

    // Tambahkan tombol Next jika ada halaman berikutnya
    if (hasNext)
    {
        format(dialog, sizeof(dialog), "%s{40FF00}>>> Next", dialog);
        BtnNextIndex[playerid] = totalItems; // Tombol next berada setelah item terakhir
    }

    // Tambahkan tombol Previous jika ada halaman sebelumnya
    if (hasPrev)
    {
        format(dialog, sizeof(dialog), "%s\n{FF0000}<<< Prev", dialog);
        BtnPrevIndex[playerid] = (BtnNextIndex[playerid] == -1) ? totalItems : totalItems + 1;
    }

    ShowPlayerDialogPages(playerid, DIALOG_ACLIST, DIALOG_STYLE_LIST, "Nex-AC Toggle Menu", dialog, "Toggle", "Close", MAX_PER_PAGE, "{40FF00}>>> Next", "{FF0000}<<< Prev", true);
    return 1;
}

CMD:actoggle(playerid, params[])
{
    if (AccountData[playerid][pAdmin] < 5)
    {
        SendClientMessage(playerid, -1, "Anda tidak punya izin untuk menggunakan command ini.");
        return 1;
    }

    AntiCheatPage[playerid] = 0;
    ShowAntiCheatDialog(playerid);
    return 1;
}

public OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[], btn_next_index, btn_previous_index)
{
    if (dialogid == DIALOG_ACLIST && response)
    {
        new page = AntiCheatPage[playerid];
        new start = page * MAX_PER_PAGE;
        new end = start + MAX_PER_PAGE;
        if (end > MAX_AC) end = MAX_AC;

        if (listitem == BtnNextIndex[playerid])
        {
            // Next page
            if ((page + 1) * MAX_PER_PAGE < MAX_AC)
                AntiCheatPage[playerid]++;
        }
        else if (listitem == BtnPrevIndex[playerid])
        {
            // Previous page
            if (page > 0)
                AntiCheatPage[playerid]--;
        }
        else if (listitem < (end - start))
        {
            // Toggle status AntiCheat
            new index = start + listitem;
            AntiCheatStatus[index] = !AntiCheatStatus[index];
            SaveAntiCheatSettings();

            new msg[128];
            format(msg, sizeof(msg), "[NEX-AC] %s telah %s.", AntiCheatNames[index],
                AntiCheatStatus[index] ? "diaktifkan" : "dinonaktifkan");
            SendClientMessage(playerid, -1, msg);
        }

        ShowAntiCheatDialog(playerid);
    }
    return 1;
}

hook OnGameModeInit()
{
    LoadAntiCheatSettings();
    return 1;
}
