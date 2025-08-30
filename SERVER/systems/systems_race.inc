#include <YSI_Coding\y_hooks>

// =====================[ Konstanta & Enum ]=====================
#define MAX_ROUTE 10 // 9 + 1 (finish)

// =====================[ Variabel Global ]=====================
new
    Float:RacePos[MAX_PLAYERS][MAX_ROUTE][3],
    RaceIndex[MAX_PLAYERS],
    RaceWith[MAX_PLAYERS],
    bool:InRace[MAX_PLAYERS],
    Text3D:RaceNametag[MAX_PLAYERS] = { Text3D:INVALID_STREAMER_ID, ... };

// =====================[ CMD /race ]=====================
CMD:race(playerid, params[]) {
    ShowPlayerDialog(playerid, DIALOG_BALAP_MENU, DIALOG_STYLE_LIST, "Menu Balapan",
        "1. Simpan Checkpoint\n2. Simpan Finish\n3. Undang Pemain\n4. Ikuti Sendiri\n5. Mulai Balapan\n6. Lihat Anggota",
        "Pilih", "Tutup");
    return 1;
}

// =====================[ Dialog Handler ]=====================
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(!response) return 1;

    switch(dialogid) {
        case DIALOG_BALAP_MENU: {
            switch(listitem) {
                case 0: ShowPlayerDialog(playerid, DIALOG_BALAP_SAVE, DIALOG_STYLE_INPUT, "Simpan Checkpoint", "Masukkan nomor checkpoint (1-9):", "Simpan", "Batal");
                case 1: {
                    new Float:x, Float:y, Float:z;
                    GetPlayerPos(playerid, x, y, z);
                    RacePos[playerid][9][0] = x;
                    RacePos[playerid][9][1] = y;
                    RacePos[playerid][9][2] = z;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Checkpoint finish berhasil disimpan.");
                }
                case 2: ShowPlayerDialog(playerid, DIALOG_BALAP_INVITE, DIALOG_STYLE_INPUT, "Undang Pemain", "Masukkan ID pemain yang ingin diundang:", "Undang", "Batal");
                case 3: {
                    RaceWith[playerid] = playerid;
                    ShowTDN(playerid, NOTIFICATION_INFO, "Kamu mengikuti balapan milikmu sendiri.");
                    CreateRaceNametag(playerid);
                }
                case 4: StartRace(playerid);
                case 5: {
                    new list[1024], count = 0;
                    foreach (new i : Player) {
                        if(RaceWith[i] == playerid) {
                            format(list, sizeof(list), "%s%s\n", list, ReturnName(i));
                            count++;
                        }
                    }
                    if(!count) format(list, sizeof(list), "Belum ada anggota yang bergabung.");
                    ShowPlayerDialog(playerid, DIALOG_BALAP_LIST, DIALOG_STYLE_MSGBOX, "Anggota Balapan", list, "Tutup", "");
                }
            }
        }

        case DIALOG_BALAP_SAVE: {
            new index = strval(inputtext);
            if(index < 1 || index > 9) {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Index checkpoint harus antara 1 sampai 9.");
                return 1;
            }

            new Float:x, Float:y, Float:z;
            GetPlayerPos(playerid, x, y, z);
            RacePos[playerid][index - 1][0] = x;
            RacePos[playerid][index - 1][1] = y;
            RacePos[playerid][index - 1][2] = z;

            new msg[64];
            format(msg, sizeof(msg), "Checkpoint ke-%d berhasil disimpan!", index);
            ShowTDN(playerid, NOTIFICATION_SUKSES, msg);
        }

        case DIALOG_BALAP_INVITE: {
            new pid = strval(inputtext);

            if(pid == playerid)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Gunakan opsi 'Ikuti Sendiri' untuk ikut balapanmu.");

            if(!IsPlayerConnected(pid) || !IsPlayerNearPlayer(playerid, pid, 5.0))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tidak berada di dekatmu atau tidak valid.");

            if(RaceWith[pid] != INVALID_PLAYER_ID)
                return ShowTDN(playerid, NOTIFICATION_WARNING, "Pemain tersebut sudah mengikuti balapan lain.");

            RaceWith[pid] = playerid;
            RaceWith[playerid] = playerid;

            CreateRaceNametag(pid);

            new msg[128];
            format(msg, sizeof(msg), "Kamu mengundang %s untuk ikut balapanmu!", ReturnName(pid));
            ShowTDN(playerid, NOTIFICATION_SUKSES, msg);

            format(msg, sizeof(msg), "Kamu telah diundang oleh %s untuk ikut balapan!", ReturnName(playerid));
            ShowTDN(pid, NOTIFICATION_INFO, msg);
        }
    }
    return 1;
}

// =====================[ Fungsi Mulai Balapan ]=====================
StartRace(ownerid) {
    for(new i = 0; i < MAX_ROUTE - 1; i++) {
        if(RacePos[ownerid][i][0] == 0.0 && RacePos[ownerid][i][1] == 0.0 && RacePos[ownerid][i][2] == 0.0) {
            new msg[64];
            format(msg, sizeof(msg), "Checkpoint %d belum disimpan!", i + 1);
            ShowTDN(ownerid, NOTIFICATION_WARNING, msg);
            return 1;
        }
    }

    if(RacePos[ownerid][9][0] == 0.0 && RacePos[ownerid][9][1] == 0.0 && RacePos[ownerid][9][2] == 0.0) {
        ShowTDN(ownerid, NOTIFICATION_WARNING, "Checkpoint FINISH belum disimpan.");
        return 1;
    }

    foreach (new i : Player) {
        if(IsPlayerConnected(i) && RaceWith[i] == ownerid) {
            InRace[i] = true;
            RaceIndex[i] = 0;

            GameTextForPlayer(i, "~g~Balapan dimulai!", 3000, 5);
            DisablePlayerRaceCheckpoint(i);
            SetPlayerRaceCheckpoint(i, 0,
                RacePos[ownerid][0][0], RacePos[ownerid][0][1], RacePos[ownerid][0][2],
                RacePos[ownerid][1][0], RacePos[ownerid][1][1], RacePos[ownerid][1][2], 5.0);
        }
    }
    return 1;
}

// =====================[ Buat & Hapus Nametag Dinamis ]=====================
stock CreateRaceNametag(playerid) {
    if(IsValidDynamic3DTextLabel(RaceNametag[playerid])) {
        DestroyDynamic3DTextLabel(RaceNametag[playerid]);
    }
    new label[64];
    format(label, sizeof(label), "[RACE] %s", ReturnName(playerid));
    RaceNametag[playerid] = CreateDynamic3DTextLabel(label, 0xFFAA00FF, 0.0, 0.0, 0.5, 25.0, playerid, .testlos = 1);
}

hook OnPlayerDisconnect(playerid, reason) {
    if(IsValidDynamic3DTextLabel(RaceNametag[playerid])) {
        DestroyDynamic3DTextLabel(RaceNametag[playerid]);
        RaceNametag[playerid] = Text3D:INVALID_STREAMER_ID;
    }
    RaceWith[playerid] = INVALID_PLAYER_ID;
    InRace[playerid] = false;
    return 1;
}

