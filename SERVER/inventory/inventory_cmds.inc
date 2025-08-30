#include <YSI_Coding\y_hooks>

new PlayerText: i_box[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_model[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_bar[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_item[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_qwt[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_string[MAX_PLAYERS][31];

CreateInventoryTextdraw(playerid)
{
    i_box[playerid][0] = CreatePlayerTextDraw(playerid, 210.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][0], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][0], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][0], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][0], 1);

    i_box[playerid][1] = CreatePlayerTextDraw(playerid, 252.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][1], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][1], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][1], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][1], 1);

    i_box[playerid][2] = CreatePlayerTextDraw(playerid, 294.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][2], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][2], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][2], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][2], 1);

    i_box[playerid][3] = CreatePlayerTextDraw(playerid, 336.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][3], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][3], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][3], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][3], 1);

    i_box[playerid][4] = CreatePlayerTextDraw(playerid, 210.000, 194.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][4], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][4], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][4], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][4], 1);

    i_box[playerid][5] = CreatePlayerTextDraw(playerid, 252.000, 194.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][5], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][5], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][5], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][5], 1);

    i_box[playerid][6] = CreatePlayerTextDraw(playerid, 294.000, 194.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][6], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][6], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][6], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][6], 1);

    i_box[playerid][7] = CreatePlayerTextDraw(playerid, 336.000, 194.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][7], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][7], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][7], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][7], 1);

    i_box[playerid][8] = CreatePlayerTextDraw(playerid, 210.000, 249.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][8], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][8], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][8], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][8], 1);

    i_box[playerid][9] = CreatePlayerTextDraw(playerid, 252.000, 249.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][9], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][9], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][9], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][9], 1);

    i_box[playerid][10] = CreatePlayerTextDraw(playerid, 294.000, 249.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][10], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][10], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][10], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][10], 1);

    i_box[playerid][11] = CreatePlayerTextDraw(playerid, 336.000, 249.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][11], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][11], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][11], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][11], 1);

    i_box[playerid][12] = CreatePlayerTextDraw(playerid, 210.000, 305.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][12], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][12], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][12], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][12], 1);

    i_box[playerid][13] = CreatePlayerTextDraw(playerid, 252.000, 305.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][13], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][13], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][13], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][13], 1);

    i_box[playerid][14] = CreatePlayerTextDraw(playerid, 294.000, 305.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][14], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][14], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][14], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][14], 1);

    i_box[playerid][15] = CreatePlayerTextDraw(playerid, 336.000, 305.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_box[playerid][15], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][15], 150);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][15], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][15], 1);

    i_model[playerid][0] = CreatePlayerTextDraw(playerid, 210.000, 140.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][0], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][0], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][0], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][0], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][0], 0, 0);

    i_model[playerid][1] = CreatePlayerTextDraw(playerid, 252.000, 140.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][1], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][1], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][1], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][1], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][1], 0, 0);

    i_model[playerid][2] = CreatePlayerTextDraw(playerid, 294.000, 140.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][2], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][2], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][2], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][2], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][2], 0, 0);

    i_model[playerid][3] = CreatePlayerTextDraw(playerid, 336.000, 140.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][3], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][3], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][3], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][3], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][3], 0, 0);

    i_model[playerid][4] = CreatePlayerTextDraw(playerid, 210.000, 194.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][4], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][4], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][4], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][4], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][4], 0, 0);

    i_model[playerid][5] = CreatePlayerTextDraw(playerid, 252.000, 194.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][5], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][5], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][5], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][5], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][5], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][5], 0, 0);

    i_model[playerid][6] = CreatePlayerTextDraw(playerid, 294.000, 194.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][6], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][6], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][6], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][6], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][6], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][6], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][6], 0, 0);

    i_model[playerid][7] = CreatePlayerTextDraw(playerid, 336.000, 194.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][7], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][7], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][7], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][7], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][7], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][7], 0, 0);

    i_model[playerid][8] = CreatePlayerTextDraw(playerid, 210.000, 249.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][8], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][8], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][8], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][8], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][8], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][8], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][8], 0, 0);

    i_model[playerid][9] = CreatePlayerTextDraw(playerid, 252.000, 249.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][9], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][9], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][9], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][9], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][9], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][9], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][9], 0, 0);

    i_model[playerid][10] = CreatePlayerTextDraw(playerid, 294.000, 249.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][10], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][10], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][10], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][10], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][10], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][10], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][10], 0, 0);

    i_model[playerid][11] = CreatePlayerTextDraw(playerid, 336.000, 249.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][11], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][11], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][11], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][11], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][11], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][11], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][11], 0, 0);

    i_model[playerid][12] = CreatePlayerTextDraw(playerid, 210.000, 305.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][12], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][12], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][12], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][12], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][12], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][12], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][12], 0, 0);

    i_model[playerid][13] = CreatePlayerTextDraw(playerid, 252.000, 305.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][13], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][13], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][13], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][13], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][13], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][13], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][13], 0, 0);

    i_model[playerid][14] = CreatePlayerTextDraw(playerid, 294.000, 305.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][14], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][14], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][14], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][14], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][14], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][14], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][14], 0, 0);

    i_model[playerid][15] = CreatePlayerTextDraw(playerid, 336.000, 305.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][15], 38.000, 50.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][15], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][15], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][15], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][15], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][15], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][15], 0, 0);

    i_bar[playerid][0] = CreatePlayerTextDraw(playerid, 210.000, 186.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][0], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][0], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][0], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][0], 1);

    i_bar[playerid][1] = CreatePlayerTextDraw(playerid, 252.000, 186.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][1], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][1], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][1], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][1], 1);

    i_bar[playerid][2] = CreatePlayerTextDraw(playerid, 294.000, 186.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][2], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][2], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][2], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][2], 1);

    i_bar[playerid][3] = CreatePlayerTextDraw(playerid, 336.000, 186.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][3], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][3], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][3], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][3], 1);

    i_bar[playerid][4] = CreatePlayerTextDraw(playerid, 210.000, 240.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][4], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][4], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][4], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][4], 1);

    i_bar[playerid][5] = CreatePlayerTextDraw(playerid, 252.000, 240.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][5], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][5], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][5], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][5], 1);

    i_bar[playerid][6] = CreatePlayerTextDraw(playerid, 294.000, 240.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][6], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][6], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][6], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][6], 1);

    i_bar[playerid][7] = CreatePlayerTextDraw(playerid, 336.000, 240.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][7], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][7], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][7], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][7], 1);

    i_bar[playerid][8] = CreatePlayerTextDraw(playerid, 210.000, 295.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][8], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][8], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][8], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][8], 1);

    i_bar[playerid][9] = CreatePlayerTextDraw(playerid, 252.000, 295.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][9], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][9], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][9], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][9], 1);

    i_bar[playerid][10] = CreatePlayerTextDraw(playerid, 294.000, 295.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][10], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][10], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][10], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][10], 1);

    i_bar[playerid][11] = CreatePlayerTextDraw(playerid, 336.000, 295.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][11], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][11], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][11], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][11], 1);

    i_bar[playerid][12] = CreatePlayerTextDraw(playerid, 210.000, 351.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][12], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][12], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][12], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][12], 1);

    i_bar[playerid][13] = CreatePlayerTextDraw(playerid, 252.000, 351.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][13], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][13], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][13], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][13], 1);

    i_bar[playerid][14] = CreatePlayerTextDraw(playerid, 294.000, 351.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][14], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][14], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][14], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][14], 1);

    i_bar[playerid][15] = CreatePlayerTextDraw(playerid, 336.000, 351.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_bar[playerid][15], 38.000, 4.000);
    PlayerTextDrawAlignment(playerid, i_bar[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_bar[playerid][15], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_bar[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_bar[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_bar[playerid][15], 255);
    PlayerTextDrawFont(playerid, i_bar[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, i_bar[playerid][15], 1);

    i_item[playerid][0] = CreatePlayerTextDraw(playerid, 211.000, 180.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][0], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][0], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][0], 1);

    i_item[playerid][1] = CreatePlayerTextDraw(playerid, 253.000, 180.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][1], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][1], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][1], 1);

    i_item[playerid][2] = CreatePlayerTextDraw(playerid, 295.000, 180.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][2], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][2], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][2], 1);

    i_item[playerid][3] = CreatePlayerTextDraw(playerid, 337.000, 180.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][3], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][3], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][3], 1);

    i_item[playerid][4] = CreatePlayerTextDraw(playerid, 211.000, 234.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][4], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][4], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][4], 1);

    i_item[playerid][5] = CreatePlayerTextDraw(playerid, 253.000, 234.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][5], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][5], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][5], 1);

    i_item[playerid][6] = CreatePlayerTextDraw(playerid, 295.000, 234.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][6], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][6], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][6], 1);

    i_item[playerid][7] = CreatePlayerTextDraw(playerid, 337.000, 234.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][7], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][7], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][7], 1);

    i_item[playerid][8] = CreatePlayerTextDraw(playerid, 211.000, 289.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][8], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][8], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][8], 1);

    i_item[playerid][9] = CreatePlayerTextDraw(playerid, 253.000, 289.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][9], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][9], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][9], 1);

    i_item[playerid][10] = CreatePlayerTextDraw(playerid, 295.000, 289.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][10], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][10], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][10], 1);

    i_item[playerid][11] = CreatePlayerTextDraw(playerid, 337.000, 289.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][11], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][11], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][11], 1);

    i_item[playerid][12] = CreatePlayerTextDraw(playerid, 211.000, 345.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][12], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][12], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][12], 1);

    i_item[playerid][13] = CreatePlayerTextDraw(playerid, 253.000, 345.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][13], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][13], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][13], 1);

    i_item[playerid][14] = CreatePlayerTextDraw(playerid, 295.000, 345.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][14], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][14], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][14], 1);

    i_item[playerid][15] = CreatePlayerTextDraw(playerid, 337.000, 345.000, "Snack");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][15], 0.109, 0.599);
    PlayerTextDrawAlignment(playerid, i_item[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_item[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][15], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][15], 1);

    i_qwt[playerid][0] = CreatePlayerTextDraw(playerid, 246.000, 141.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][0], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][0], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][0], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][0], 1);

    i_qwt[playerid][1] = CreatePlayerTextDraw(playerid, 288.000, 141.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][1], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][1], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][1], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][1], 1);

    i_qwt[playerid][2] = CreatePlayerTextDraw(playerid, 330.000, 141.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][2], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][2], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][2], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][2], 1);

    i_qwt[playerid][3] = CreatePlayerTextDraw(playerid, 372.000, 141.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][3], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][3], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][3], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][3], 1);

    i_qwt[playerid][4] = CreatePlayerTextDraw(playerid, 246.000, 195.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][4], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][4], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][4], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][4], 1);

    i_qwt[playerid][5] = CreatePlayerTextDraw(playerid, 288.000, 195.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][5], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][5], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][5], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][5], 1);

    i_qwt[playerid][6] = CreatePlayerTextDraw(playerid, 330.000, 195.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][6], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][6], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][6], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][6], 1);

    i_qwt[playerid][7] = CreatePlayerTextDraw(playerid, 372.000, 195.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][7], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][7], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][7], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][7], 1);

    i_qwt[playerid][8] = CreatePlayerTextDraw(playerid, 246.000, 250.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][8], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][8], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][8], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][8], 1);

    i_qwt[playerid][9] = CreatePlayerTextDraw(playerid, 288.000, 250.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][9], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][9], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][9], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][9], 1);

    i_qwt[playerid][10] = CreatePlayerTextDraw(playerid, 330.000, 250.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][10], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][10], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][10], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][10], 1);

    i_qwt[playerid][11] = CreatePlayerTextDraw(playerid, 372.000, 250.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][11], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][11], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][11], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][11], 1);

    i_qwt[playerid][12] = CreatePlayerTextDraw(playerid, 246.000, 306.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][12], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][12], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][12], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][12], 1);

    i_qwt[playerid][13] = CreatePlayerTextDraw(playerid, 288.000, 306.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][13], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][13], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][13], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][13], 1);

    i_qwt[playerid][14] = CreatePlayerTextDraw(playerid, 330.000, 306.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][14], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][14], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][14], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][14], 1);

    i_qwt[playerid][15] = CreatePlayerTextDraw(playerid, 372.000, 306.000, "1x (0.1)");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][15], 0.100, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][15], 3);
    PlayerTextDrawColor(playerid, i_qwt[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][15], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][15], 1);

    i_string[playerid][0] = CreatePlayerTextDraw(playerid, 210.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][0], 10.000, 12.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][0], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][0], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][0], 1);

    i_string[playerid][1] = CreatePlayerTextDraw(playerid, 252.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][1], 10.000, 12.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][1], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][1], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][1], 1);

    i_string[playerid][2] = CreatePlayerTextDraw(playerid, 294.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][2], 10.000, 12.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][2], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][2], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][2], 1);

    i_string[playerid][3] = CreatePlayerTextDraw(playerid, 336.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][3], 10.000, 12.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][3], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][3], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][3], 1);

    i_string[playerid][4] = CreatePlayerTextDraw(playerid, 216.000, 142.000, "1");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][4], 0.209, 0.999);
    PlayerTextDrawAlignment(playerid, i_string[playerid][4], 3);
    PlayerTextDrawColor(playerid, i_string[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][4], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][4], 1);

    i_string[playerid][5] = CreatePlayerTextDraw(playerid, 259.000, 141.000, "2");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][5], 0.209, 0.999);
    PlayerTextDrawAlignment(playerid, i_string[playerid][5], 3);
    PlayerTextDrawColor(playerid, i_string[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][5], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][5], 1);

    i_string[playerid][6] = CreatePlayerTextDraw(playerid, 301.000, 141.000, "3");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][6], 0.209, 0.999);
    PlayerTextDrawAlignment(playerid, i_string[playerid][6], 3);
    PlayerTextDrawColor(playerid, i_string[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][6], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][6], 1);

    i_string[playerid][7] = CreatePlayerTextDraw(playerid, 343.000, 141.000, "4");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][7], 0.209, 0.999);
    PlayerTextDrawAlignment(playerid, i_string[playerid][7], 3);
    PlayerTextDrawColor(playerid, i_string[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][7], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][7], 1);

    i_string[playerid][8] = CreatePlayerTextDraw(playerid, 215.000, 127.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][8], 17.000, 8.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][8], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][8], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][8], 1);

    i_string[playerid][9] = CreatePlayerTextDraw(playerid, 218.000, 122.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][9], 1.000, 8.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][9], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][9], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][9], 1);

    i_string[playerid][10] = CreatePlayerTextDraw(playerid, 228.000, 122.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][10], 1.000, 8.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][10], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][10], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][10], 1);

    i_string[playerid][11] = CreatePlayerTextDraw(playerid, 219.000, 122.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][11], 9.000, 1.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][11], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][11], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][11], 1);

    i_string[playerid][12] = CreatePlayerTextDraw(playerid, 235.000, 121.000, "Xeno Tadasi Inventory");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][12], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][12], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][12], 1);

    i_string[playerid][13] = CreatePlayerTextDraw(playerid, 235.000, 129.000, "2.1/50");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][13], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][13], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][13], 1);

    i_string[playerid][14] = CreatePlayerTextDraw(playerid, 340.000, 122.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][14], 34.000, 14.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][14], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][14], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][14], 1);

    i_string[playerid][15] = CreatePlayerTextDraw(playerid, 354.000, 125.000, "search");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][15], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][15], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][15], 1);

    i_string[playerid][16] = CreatePlayerTextDraw(playerid, 343.000, 124.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_string[playerid][16], 5.000, 7.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][16], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][16], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][16], 1);

    i_string[playerid][17] = CreatePlayerTextDraw(playerid, 344.000, 126.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_string[playerid][17], 3.000, 3.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][17], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][17], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][17], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][17], 1);

    i_string[playerid][18] = CreatePlayerTextDraw(playerid, 348.000, 128.000, "/");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][18], -0.179, 0.499);
    PlayerTextDrawAlignment(playerid, i_string[playerid][18], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][18], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][18], 1);

    i_string[playerid][19] = CreatePlayerTextDraw(playerid, 381.000, 140.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][19], 2.000, 216.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][19], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][19], COLOR_GOLD);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][19], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][19], 1);

    i_string[playerid][20] = CreatePlayerTextDraw(playerid, 387.000, 191.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][20], 47.000, 100.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][20], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][20], 150);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][20], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][20], 1);

    i_string[playerid][21] = CreatePlayerTextDraw(playerid, 387.000, 191.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][21], 47.000, 20.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][21], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][21], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, i_string[playerid][21], 1);

    i_string[playerid][22] = CreatePlayerTextDraw(playerid, 387.000, 211.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][22], 47.000, 20.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][22], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][22], 0);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][22], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, i_string[playerid][22], 1);

    i_string[playerid][23] = CreatePlayerTextDraw(playerid, 387.000, 231.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][23], 47.000, 20.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][23], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][23], 0);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][23], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, i_string[playerid][23], 1);

    i_string[playerid][24] = CreatePlayerTextDraw(playerid, 387.000, 251.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][24], 47.000, 20.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][24], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][24], 0);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][24], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, i_string[playerid][24], 1);

    i_string[playerid][25] = CreatePlayerTextDraw(playerid, 387.000, 271.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, i_string[playerid][25], 47.000, 20.000);
    PlayerTextDrawAlignment(playerid, i_string[playerid][25], 1);
    PlayerTextDrawColor(playerid, i_string[playerid][25], 0);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][25], 255);
    PlayerTextDrawFont(playerid, i_string[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, i_string[playerid][25], 1);

    i_string[playerid][26] = CreatePlayerTextDraw(playerid, 411.000, 198.000, "Amount");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][26], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][26], 2);
    PlayerTextDrawColor(playerid, i_string[playerid][26], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][26], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][26], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][26], 1);

    i_string[playerid][27] = CreatePlayerTextDraw(playerid, 411.000, 218.000, "Use");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][27], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][27], 2);
    PlayerTextDrawColor(playerid, i_string[playerid][27], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][27], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][27], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][27], 1);

    i_string[playerid][28] = CreatePlayerTextDraw(playerid, 411.000, 238.000, "Give");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][28], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][28], 2);
    PlayerTextDrawColor(playerid, i_string[playerid][28], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][28], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][28], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][28], 1);

    i_string[playerid][29] = CreatePlayerTextDraw(playerid, 411.000, 257.000, "Drop");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][29], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][29], 2);
    PlayerTextDrawColor(playerid, i_string[playerid][29], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][29], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][29], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][29], 1);

    i_string[playerid][30] = CreatePlayerTextDraw(playerid, 411.000, 278.000, "Close");
    PlayerTextDrawLetterSize(playerid, i_string[playerid][30], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_string[playerid][30], 2);
    PlayerTextDrawColor(playerid, i_string[playerid][30], -1);
    PlayerTextDrawSetShadow(playerid, i_string[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, i_string[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, i_string[playerid][30], 150);
    PlayerTextDrawFont(playerid, i_string[playerid][30], 1);
    PlayerTextDrawSetProportional(playerid, i_string[playerid][30], 1);
}

hook OnPlayerConnect(playerid)
{
    CreateInventoryTextdraw(playerid);
    return 1;
}

ShowInventoryTD(playerid)
{
    forex(i,31)
    {
        PlayerTextDrawShow(playerid, inv::string[playerid][i]);
    }
    AccountData[playerid][pAmountInv] = 0;
    PlayerTextDrawSetString(playerid, inv::string[playerid][26], "Amount");
}

Inventory_Show(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;
    HideHbe(playerid);
    new str[120];
    for(new index; index < 16; index ++) 
    {
        PlayerTextDrawShow(playerid, inv::box[playerid][index]);
        if(InventoryData[playerid][index][invExists])
        {
            for (new i; i < sizeof(g_aInventoryItems); i ++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
            {
                
                PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][index], InventoryData[playerid][index][invModel]);
                PlayerTextDrawShow(playerid, inv::model[playerid][index]);

                format(str, sizeof(str), "%s", g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invQuantity]);
                PlayerTextDrawSetString(playerid, inv::item[playerid][index], str);
                PlayerTextDrawShow(playerid, inv::item[playerid][index]);

                format(str, sizeof(str), "%dx (%.1f)", InventoryData[playerid][index][invQuantity], Float:GetInventoryWeight(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invQuantity]));
                PlayerTextDrawSetString(playerid, inv::qwt[playerid][index], str);
                PlayerTextDrawShow(playerid, inv::qwt[playerid][index]);

                PlayerTextDrawShow(playerid, inv::bar[playerid][index]);
            }
        }
    }
    
    ShowInventoryTD(playerid);
    format(str, sizeof(str), "%.1f/50", AccountData[playerid][pBeratItem]);
    PlayerTextDrawSetString(playerid, inv::string[playerid][13], str);

    format(str, sizeof(str), "%s", AccountData[playerid][pName]);
    PlayerTextDrawSetString(playerid, inv::string[playerid][12], str);
    
    SelectTextDraw(playerid, COLOR_GOLD);
    return 1;
}

Inventory_Close(playerid)
{
    forex(i,31)
    {
        PlayerTextDrawHide(playerid, inv::string[playerid][i]);
    }
    /*forex(i, 26)
    {
        TextDrawHideForPlayer(playerid, inv::textdraw[i]);
    }*/
    forex(i, 16)
    {
        PlayerTextDrawColor(playerid, inv::box[playerid][i], 150);
        PlayerTextDrawHide(playerid, inv::box[playerid][i]);
        PlayerTextDrawHide(playerid, inv::model[playerid][i]);
        PlayerTextDrawHide(playerid, inv::item[playerid][i]);
        PlayerTextDrawHide(playerid, inv::qwt[playerid][i]);
        PlayerTextDrawHide(playerid, inv::bar[playerid][i]);
    }
    ShowHbe(playerid);
    CancelSelectTextDraw(playerid);
    AccountData[playerid][pSelectItem] = -1;
    AccountData[playerid][pAmountInv] = 0;
    return 1;
}


stock SelectItem(playerid, i)
{
    AccountData[playerid][pSelectItem] = i;
    PlayerTextDrawColor(playerid, inv::box[playerid][i], -190554032);
    PlayerTextDrawShow(playerid, inv::box[playerid][i]);
    PlayerPlaySound(playerid, 1052, 0, 0, 0);
    return 1;
}

stock UnselectItem(playerid)
{
    if(AccountData[playerid][pSelectItem] != -1)
    {
        PlayerTextDrawHide(playerid, inv::box[playerid][AccountData[playerid][pSelectItem]]);
        PlayerTextDrawColor(playerid, inv::box[playerid][AccountData[playerid][pSelectItem]], 150);
		PlayerTextDrawShow(playerid, inv::box[playerid][AccountData[playerid][pSelectItem]]);
    }
    AccountData[playerid][pSelectItem] = -1;
    return 1;
}

stock MoveItemToNewSlot(playerid, b, a)
{
    //textdraw slot before moving
	PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][b], 11477);
	PlayerTextDrawSetString(playerid, inv::item[playerid][b], "_");
	PlayerTextDrawSetString(playerid, inv::qwt[playerid][b], "_");
    //var inv item
	InventoryData[playerid][a][invExists] = true;
	InventoryData[playerid][a][invModel] = InventoryData[playerid][b][invModel];
	InventoryData[playerid][a][invQuantity] = InventoryData[playerid][b][invQuantity];
	strpack(InventoryData[playerid][a][invItem], InventoryData[playerid][b][invItem], 32 char);
    //var after inv item
	InventoryData[playerid][b][invExists] = false;
	InventoryData[playerid][b][invModel] = 0;
	InventoryData[playerid][b][invQuantity] = 0;
	strpack(InventoryData[playerid][b][invItem], "", 32 char);
    //textdrawslot after moving
	new invStr[64];
	format(invStr, 64, "%dx (%.1f)", InventoryData[playerid][a][invQuantity], Float:GetInventoryWeight(InventoryData[playerid][a][invItem], InventoryData[playerid][a][invQuantity]));
	PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][a], InventoryData[playerid][a][invModel]);
	PlayerTextDrawSetString(playerid, inv::item[playerid][a], InventoryData[playerid][a][invItem]);
	PlayerTextDrawSetString(playerid, inv::qwt[playerid][a], invStr);
	//all show and hide slot textdraw
    PlayerTextDrawHide(playerid, inv::box[playerid][b]);
	PlayerTextDrawHide(playerid, inv::model[playerid][b]);
	PlayerTextDrawHide(playerid, inv::qwt[playerid][b]);
	PlayerTextDrawHide(playerid, inv::item[playerid][b]);
	PlayerTextDrawHide(playerid, inv::bar[playerid][b]);

    PlayerTextDrawShow(playerid, inv::box[playerid][a]);
	PlayerTextDrawShow(playerid, inv::model[playerid][a]);
	PlayerTextDrawShow(playerid, inv::qwt[playerid][a]);
	PlayerTextDrawShow(playerid, inv::item[playerid][a]);
	PlayerTextDrawShow(playerid, inv::bar[playerid][a]);
    return 1;
}