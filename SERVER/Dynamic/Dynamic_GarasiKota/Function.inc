#include <YSI_Coding\y_hooks>

GarkotNearby(playerid)
{
    for(new i = 0; i < MAX_PUBLIC_GARAGE; i ++)
    {
        if(Iter_Contains(PublicGarage, i))
        {
            new Float:X, Float:Y, Float:Z, Float:dist;
            GetPlayerPos(playerid, X, Y, Z);

            dist = GetDistanceBetweenPoints(PublicGarage[i][pgPOS][0], PublicGarage[i][pgPOS][1], PublicGarage[i][pgPOS][2], X, Y, Z);

            if(dist <= 350.0)
            {
                return i;
            }
        }
    }
    return -1;
}

CityTR:LoadPublicGarage()
{
    new id = -1;
    new rows = cache_num_rows();

    if (rows)
    {
        for (new i; i < rows; i ++)
        {
            cache_get_value_name_int(i, "pgID", id);
            cache_get_value_name_int(i, "pgInterior", PublicGarage[id][pgInterior]);
            cache_get_value_name_int(i, "pgWorld", PublicGarage[id][pgWorld]);
            
            cache_get_value_name(i, "pgName", PublicGarage[id][pgName]);
            
            cache_get_value_name_float(i, "pgPosX", PublicGarage[id][pgPOS][0]);
            cache_get_value_name_float(i, "pgPosY", PublicGarage[id][pgPOS][1]);
            cache_get_value_name_float(i, "pgPosZ", PublicGarage[id][pgPOS][2]);
            
            cache_get_value_name_float(i, "pgSpawnX", PublicGarage[id][pgSpawnPOS][0]);
            cache_get_value_name_float(i, "pgSpawnY", PublicGarage[id][pgSpawnPOS][1]);
            cache_get_value_name_float(i, "pgSpawnZ", PublicGarage[id][pgSpawnPOS][2]);
            cache_get_value_name_float(i, "pgSpawnA", PublicGarage[id][pgSpawnPOS][3]);

            RefreshPublicGarage(id);
            Iter_Add(PublicGarage, id);
            Profiler_Dump();
        }
        printf("[Dynamic Public Garage]: Jumlah total Public Garage yang dimuat %d", rows);
    }
    return 1;
}

RefreshPublicGarage(id)
{
    if (id != -1)
    {
        if (IsValidDynamicObject(PublicGarage[id][pgObject]))
            DestroyDynamicObject(PublicGarage[id][pgObject]);
        
        if (IsValidDynamicMapIcon(PublicGarage[id][pgIcon]))
            DestroyDynamicMapIcon(PublicGarage[id][pgIcon]);
        
        if (IsValidDynamicArea(PublicGarage[id][pgArea]))
            DestroyDynamicArea(PublicGarage[id][pgArea]);
        
        PublicGarage[id][pgObject] = INVALID_STREAMER_ID;
        PublicGarage[id][pgIcon] = INVALID_STREAMER_ID;
        PublicGarage[id][pgArea] = INVALID_STREAMER_ID;

        if (PublicGarage[id][pgPOS][0] != 0.0)
        {
            PublicGarage[id][pgObject] = CreateCirclePickup(PICKUP_GREEN, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], PublicGarage[id][pgWorld], PublicGarage[id][pgInterior], -1); 
            PublicGarage[id][pgIcon] = CreateDynamicMapIcon(PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], 55, -1, PublicGarage[id][pgWorld], PublicGarage[id][pgInterior], -1, 1000.0, MAPICON_LOCAL, -1, 0);
            PublicGarage[id][pgArea] = CreateDynamicSphere(PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], 2.0, PublicGarage[id][pgInterior], PublicGarage[id][pgWorld]);
        }
    }
    return 1;
}

PublicGarage_Save(id)
{
    new shstr[596];
    format(shstr, sizeof(shstr), "UPDATE `public_garage` SET `pgName`='%s', `pgPosX`=%f, `pgPosY`=%f, `pgPosZ`=%f, \
    `pgSpawnX`=%f, `pgSpawnY`=%f, `pgSpawnZ`=%f, `pgSpawnA`=%f, `pgInterior`=%d, `pgWorld`=%d WHERE `pgID`=%d",
    PublicGarage[id][pgName], PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2],
    PublicGarage[id][pgSpawnPOS][0], PublicGarage[id][pgSpawnPOS][1], PublicGarage[id][pgSpawnPOS][2], PublicGarage[id][pgSpawnPOS][3], PublicGarage[id][pgInterior], PublicGarage[id][pgWorld], id);
    return mysql_tquery(g_SQL, shstr);
}

CityTR:OnPublicGarageAdded(playerid, pgid)
{
    PublicGarage_Save(pgid);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Public Garage ID: %d dengan nama %s.", GetAdminName(playerid), pgid, PublicGarage[pgid][pgName]);

    new shstr[125];
	format(shstr, sizeof(shstr), "Menggunakan CMD /addgarkot dengan ID: %d - %s", pgid, PublicGarage[pgid][pgName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new i : PublicGarage)
    {
        if(areaid == PublicGarage[i][pgArea])
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ShowKey(playerid, "[Y] Akses Garasi Umum");
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                ShowKey(playerid, "[H] Simpan Kendaraan");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new i : PublicGarage)
    {
        if(areaid == PublicGarage[i][pgArea])
        {
            HideShortKey(playerid);
        }
    }
    return 1;
}