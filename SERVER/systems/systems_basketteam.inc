#include <YSI_Coding\y_hooks>
#define MAX_TEAM_PLAYERS 5

enum
{
    E_TEAM_BASKET_NONE = -1,
    E_TEAM_BASKET_A,
    E_TEAM_BASKET_B
};

enum E_BASKET_RING
{
    RING_TEAM_A,
    RING_TEAM_B
}

new PlayerText: basketscore[MAX_PLAYERS][8];
new bool:IsScoreVisible[MAX_PLAYERS];

// Posisi tengah lapangan basket
#define BASKETBALL_X 2349.100830
#define BASKETBALL_Y -1329.676147
#define BASKETBALL_Z 22.952470

#define BASKETBALL_RANGE 19.0 // radius dalam meter

new PlayerTeam[MAX_PLAYERS];
new TeamA[MAX_TEAM_PLAYERS];
new TeamB[MAX_TEAM_PLAYERS];
new TeamACount;
new TeamBCount;
new Text3D:TeamNametag[MAX_PLAYERS];

new BasketScoreA, BasketScoreB;

hook OnPlayerConnect(playerid)
{
    basketscore[playerid][0] = CreatePlayerTextDraw(playerid, 512.000, 108.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, basketscore[playerid][0], 31.000, 35.000);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][0], 1);
    PlayerTextDrawColor(playerid, basketscore[playerid][0], -16776961);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][0], 255);
    PlayerTextDrawFont(playerid, basketscore[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][0], 1);

    basketscore[playerid][1] = CreatePlayerTextDraw(playerid, 554.000, 108.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, basketscore[playerid][1], 31.000, 35.000);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][1], 1);
    PlayerTextDrawColor(playerid, basketscore[playerid][1], 512819199);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][1], 255);
    PlayerTextDrawFont(playerid, basketscore[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][1], 1);

    basketscore[playerid][2] = CreatePlayerTextDraw(playerid, 517.000, 134.000, "Team A");
    PlayerTextDrawLetterSize(playerid, basketscore[playerid][2], 0.170, 0.899);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][2], 1);
    PlayerTextDrawColor(playerid, basketscore[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][2], 150);
    PlayerTextDrawFont(playerid, basketscore[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][2], 1);

    basketscore[playerid][3] = CreatePlayerTextDraw(playerid, 560.000, 134.000, "Team B");
    PlayerTextDrawLetterSize(playerid, basketscore[playerid][3], 0.170, 0.899);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][3], 1);
    PlayerTextDrawColor(playerid, basketscore[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][3], 150);
    PlayerTextDrawFont(playerid, basketscore[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][3], 1);

    basketscore[playerid][4] = CreatePlayerTextDraw(playerid, 527.000, 110.000, "0");
    PlayerTextDrawLetterSize(playerid, basketscore[playerid][4], 0.429, 2.799);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][4], 2);
    PlayerTextDrawColor(playerid, basketscore[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][4], 150);
    PlayerTextDrawFont(playerid, basketscore[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][4], 1);

    basketscore[playerid][5] = CreatePlayerTextDraw(playerid, 568.000, 110.000, "1");
    PlayerTextDrawLetterSize(playerid, basketscore[playerid][5], 0.429, 2.799);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][5], 2);
    PlayerTextDrawColor(playerid, basketscore[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][5], 150);
    PlayerTextDrawFont(playerid, basketscore[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][5], 1);

    basketscore[playerid][6] = CreatePlayerTextDraw(playerid, 533.000, 145.000, "");
    PlayerTextDrawLetterSize(playerid, basketscore[playerid][6], 0.180, 0.999);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][6], 1);
    PlayerTextDrawColor(playerid, basketscore[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][6], 150);
    PlayerTextDrawFont(playerid, basketscore[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][6], 1);

    basketscore[playerid][7] = CreatePlayerTextDraw(playerid, 537.000, 104.000, "_");
    PlayerTextDrawTextSize(playerid, basketscore[playerid][7], 22.000, 28.000);
    PlayerTextDrawAlignment(playerid, basketscore[playerid][7], 1);
    PlayerTextDrawColor(playerid, basketscore[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, basketscore[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, basketscore[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, basketscore[playerid][7], 0);
    PlayerTextDrawFont(playerid, basketscore[playerid][7], 5);
    PlayerTextDrawSetProportional(playerid, basketscore[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, basketscore[playerid][7], 2114);
    PlayerTextDrawSetPreviewRot(playerid, basketscore[playerid][7], -76.000, -16.000, 0.000, 0.899);
    PlayerTextDrawSetPreviewVehCol(playerid, basketscore[playerid][7], 0, 0);

    IsScoreVisible[playerid] = false;
}

AddBasketScore(E_BASKET_RING:ring)
{
    switch (ring)
    {
        case RING_TEAM_A:
        {
            // Ring A dimasuki bola, berarti Team B dapat poin
            BasketScoreB++;
            ShowBasketText("TEAM B +1");
        }
        case RING_TEAM_B:
        {
            // Ring B dimasuki bola, berarti Team A dapat poin
            BasketScoreA++;
            ShowBasketText("TEAM A +1");
        }
    }

    // Cek kemenangan
    if (BasketScoreA >= 21)
    {
        ShowBasketText("TEAM A MENANG!");
        EndBasketGame();
        return;
    }
    else if (BasketScoreB >= 21)
    {
        ShowBasketText("TEAM B MENANG!");
        EndBasketGame();
        return;
    }
}

CMD:resetscore(playerid)
{
    EndBasketGame();
    ShowBasketText("SELESAI!");
    return 1;
}

stock ShowBasketText(const text[])
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i))
        {
            if (IsPlayerInRangeOfPoint(i, BASKETBALL_RANGE, BASKETBALL_X, BASKETBALL_Y, BASKETBALL_Z))
            {
                PlayerTextDrawSetString(i, basketscore[i][6], text);
            }
        }
    }
}


stock EndBasketGame()
{
    BasketScoreA = 0;
    BasketScoreB = 0;

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (!IsPlayerConnected(i)) continue;

        if (PlayerTeam[i] == E_TEAM_BASKET_A || PlayerTeam[i] == E_TEAM_BASKET_B)
        {
            LeaveTeam(i);
        }

        if (IsPlayerInRangeOfPoint(i, BASKETBALL_RANGE, BASKETBALL_X, BASKETBALL_Y, BASKETBALL_Z))
        {
            SendClientMessage(i, -1, "Pertandingan basket telah berakhir. Silakan bergabung kembali.");
        }
    }
}

ShowScore(playerid)
{
    PlayerTextDrawShow(playerid, basketscore[playerid][0]);
    PlayerTextDrawShow(playerid, basketscore[playerid][1]);
    PlayerTextDrawShow(playerid, basketscore[playerid][2]);
    PlayerTextDrawShow(playerid, basketscore[playerid][3]);
    PlayerTextDrawShow(playerid, basketscore[playerid][4]);
    PlayerTextDrawShow(playerid, basketscore[playerid][5]);
    PlayerTextDrawShow(playerid, basketscore[playerid][6]);
}

HideScore(playerid)
{
    PlayerTextDrawHide(playerid, basketscore[playerid][0]);
    PlayerTextDrawHide(playerid, basketscore[playerid][1]);
    PlayerTextDrawHide(playerid, basketscore[playerid][2]);
    PlayerTextDrawHide(playerid, basketscore[playerid][3]);
    PlayerTextDrawHide(playerid, basketscore[playerid][4]);
    PlayerTextDrawHide(playerid, basketscore[playerid][5]);
    PlayerTextDrawHide(playerid, basketscore[playerid][6]);
}

forward UpdateScoreTD(playerid);
public UpdateScoreTD(playerid)
{
    if (!IsPlayerConnected(playerid)) return 1;

    // Cek jarak player ke titik basketball
    if (IsPlayerInRangeOfPoint(playerid, BASKETBALL_RANGE, BASKETBALL_X, BASKETBALL_Y, BASKETBALL_Z))
    {
        if (!IsScoreVisible[playerid])
        {
            ShowScore(playerid);
            IsScoreVisible[playerid] = true;
        }
    }
    else
    {
        if (IsScoreVisible[playerid])
        {
            HideScore(playerid);
            IsScoreVisible[playerid] = false;
        }
    }

    return 1; // teruskan ptask
}


// Fungsi untuk menampilkan nametag
ShowPlayerTeamTag(playerid, const teamName[], color)
{
    if (IsValidDynamic3DTextLabel(TeamNametag[playerid]))
        DestroyDynamic3DTextLabel(TeamNametag[playerid]);

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    TeamNametag[playerid] = CreateDynamic3DTextLabel(teamName, color, x, y, z + 1.0, 20.0, playerid);
}

// Fungsi untuk keluar dari tim
LeaveTeam(playerid)
{
    if (PlayerTeam[playerid] == E_TEAM_BASKET_A)
    {
        for (new i = 0; i < TeamACount; i++)
        {
            if (TeamA[i] == playerid)
            {
                for (new j = i; j < TeamACount - 1; j++)
                    TeamA[j] = TeamA[j + 1];
                TeamACount--;
                break;
            }
        }
    }
    else if (PlayerTeam[playerid] == E_TEAM_BASKET_B)
    {
        for (new i = 0; i < TeamBCount; i++)
        {
            if (TeamB[i] == playerid)
            {
                for (new j = i; j < TeamBCount - 1; j++)
                    TeamB[j] = TeamB[j + 1];
                TeamBCount--;
                break;
            }
        }
    }

    PlayerTeam[playerid] = E_TEAM_BASKET_NONE;

    if (IsValidDynamic3DTextLabel(TeamNametag[playerid]))
        DestroyDynamic3DTextLabel(TeamNametag[playerid]);

    SendClientMessage(playerid, -1, "Kamu telah keluar dari tim basket.");
    return 1;
}

hook OnGameModeInit()
{
    CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Untuk mengakses menu basket", 0xFFFFFFFF, 2359.2971,-1314.4943,23.8125, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    CreateDynamic3DTextLabel(""RED"Team A", 0xFFFFFFFF, 2349.5110,-1336.3993,23.8125, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    CreateDynamic3DTextLabel(""GREEN"Team B", 0xFFFFFFFF, 2349.1997,-1323.4734,23.8125, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 2.0, 2359.2971,-1314.4943,23.8125))
    {
		ShowPlayerDialog(playerid, DIALOG_TEAM_MENU, DIALOG_STYLE_LIST, "Pilih Tim Basket", "Join Team\nLeave Team\nTeam List\nGuide", "Pilih", "Batal");
    }
    return 1;
}

// Dialog handler
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_TEAM_MENU:
        {
            if(!response) return false;
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0:// join
                {
                    ShowPlayerDialog(playerid, DIALOG_TEAM_SELECT, DIALOG_STYLE_LIST, "Pilih Tim Basket", "Team A\nTeam B", "Pilih", "Batal");
                }
                case 1://leave
                {
                    if (PlayerTeam[playerid] == E_TEAM_BASKET_NONE)
                    {
                        ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu belum bergabung ke tim manapun.");
                        return 1;
                    }
                    LeaveTeam(playerid);
                }
                case 2://list team
                {
                    if (PlayerTeam[playerid] == E_TEAM_BASKET_NONE)
                    {
                        ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus bergabung ke salah satu tim terlebih dahulu untuk melihat daftar tim.");
                        return 1;
                    }

                    new list[1024], name[MAX_PLAYER_NAME];

                    strcat(list, "Team Basket A:\n");
                    for (new i = 0; i < TeamACount; i++)
                    {
                        if (IsPlayerConnected(TeamA[i]))
                        {
                            GetPlayerName(TeamA[i], name, sizeof(name));
                            format(list, sizeof(list), "%s- %s\n", list, name);
                        }
                    }

                    strcat(list, "\nTeam Basket B:\n");
                    for (new i = 0; i < TeamBCount; i++)
                    {
                        if (IsPlayerConnected(TeamB[i]))
                        {
                            GetPlayerName(TeamB[i], name, sizeof(name));
                            format(list, sizeof(list), "%s- %s\n", list, name);
                        }
                    }

                    ShowPlayerDialog(playerid, DIALOG_TEAM_LIST, DIALOG_STYLE_MSGBOX, "Daftar Pemain di Tim Basket", list, "Tutup", "");
                }
                case 3:// Hapus Kendaraan
                {
                    ShowPlayerDialog(playerid, DIALOG_BASKET_GUIDE, DIALOG_STYLE_MSGBOX,
                    "Cara Bermain Basket",
                    "Kontrol Permainan:\n\
                    \n\
                    > Dribble Bola:\n\
                    Tekan tombol Y untuk melakukan dribble.\n\
                    \n\
                    > Shoot (Lempar ke Ring):\n\
                    Tekan tombol Y saat dekat ring untuk melakukan shoot.\n\
                    \n\
                    > Ambil Bola:\n\
                    Dekati bola, lalu tekan tombol Y untuk mengambil.\n\
                    \n\
                    > Oper Bola:\n\
                    Gunakan perintah Y untuk mengoper bola ke teman.\n\
                    \n\
                    > Reset Bola Basket:\n\
                    Gunakan perintah /resetbasket untuk mengreset basket jika hilang.\n\
                    \n\
                    > Reset Score:\n\
                    Gunakan perintah /resetscore untuk mengreset point team.\n\
                    \n\
                    Gunakan timing dan posisi yang tepat untuk mencetak skor!\n\
                    Selamat bermain!",
                    "Oke", "");
                }
            }
        }
        case DIALOG_TEAM_SELECT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            // new count = 0;
            // foreach(new carid : PvtVehicles)
            // {
            //     if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
            //         count ++;
            // }
            // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

            switch(listitem)
            {
                case 0: // Team A
                {
                    if (TeamACount >= MAX_TEAM_PLAYERS)
                    {
                        ShowTDN(playerid, NOTIFICATION_ERROR, "Team Basket A sudah penuh.");
                        return 1;
                    }
                    LeaveTeam(playerid);
                    PlayerTeam[playerid] = E_TEAM_BASKET_A;
                    TeamA[TeamACount++] = playerid;
                    ShowPlayerTeamTag(playerid, "TEAM BASKET A", 0xFF5500FF);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Kamu bergabung ke Tim Basket A.");
                }
                case 1: // Team B
                {
                    if (TeamBCount >= MAX_TEAM_PLAYERS)
                    {
                        ShowTDN(playerid, NOTIFICATION_ERROR, "Team Basket B sudah penuh.");
                        return 1;
                    }
                    LeaveTeam(playerid);
                    PlayerTeam[playerid] = E_TEAM_BASKET_B;
                    TeamB[TeamBCount++] = playerid;
                    ShowPlayerTeamTag(playerid, "TEAM BASKET B", 0x00AAFFFF);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Kamu bergabung ke Tim Basket B.");
                }
            }
        }
    }
    return 1;
}

// Reset data saat player disconnect
hook OnPlayerDisconnect(playerid, reason)
{
    LeaveTeam(playerid);
    return 1;
}