#include <YSI_Coding\y_hooks>
#define MAX_RUMAH 1000
#define MAX_HOUSECAPACITY 100
#define MAX_MEMBER_HOUSE    3

new pTimerMasukRumah[MAX_PLAYERS] = {-1, ...};

enum housedata {
    hsOwner[MAX_PLAYER_NAME],
    hsOwnerID,
    hsType,
    Float:hsExtPos[4],
    Float:hsIntPos[4],
    hsInt,
    STREAMER_TAG_3D_TEXT_LABEL:hsLabel,
    STREAMER_TAG_3D_TEXT_LABEL:hsLabelExit,
    STREAMER_TAG_3D_TEXT_LABEL:hsLabelBrankas,
    hsClaimed,
    hsWeapon[5],
    hsAmmo[5],

    // Garage Sistem
    Float:housegaragePos[3],
    Float:housegarageSpawnPos[4],
    STREAMER_TAG_AREA:housegarageArea,
    // STREAMER_TAG_PICKUP:housegaragePickup,
    // STREAMER_TAG_3D_TEXT_LABEL:housegarageLabel,
    housegarageInt,
    housegarageWorld,
    Float:houseMaxCapacity,

    // Helipad Sistem
    Float:househelipadPos[3],
    Float:househelipadSpawnPos[4],
    STREAMER_TAG_OBJECT:househelipadObject,
    STREAMER_TAG_AREA:househelipadArea,
    househelipadInt,
    househelipadWorld,

    // Brankas
    Float:housebrankasPos[3],
    STREAMER_TAG_3D_TEXT_LABEL:housebrankasLabel,

    hsAudio,
    hsURL[ 128 ],
};
new HouseData[MAX_RUMAH][housedata],
    Iterator:House<MAX_RUMAH>;

House_HaveAccess(playerid, houseid)
{
    if(HouseData[houseid][hsOwnerID] == AccountData[playerid][pID])
        return 1;
    
    if(AccountData[playerid][pFriendHouseID] == houseid)
        return 1;
    
    return 0;
}

stock House_IsOwner(playerid, houseid)
{
    if (AccountData[playerid][pID] == -1)
        return 0;
    
    if (HouseData[houseid][hsOwnerID] != 0 && HouseData[houseid][hsOwnerID] == AccountData[playerid][pID])
        return 1;

    return 0;
}
forward LoadKeysList(playerid);
public LoadKeysList(playerid)
{
    for(new i = 0; i < 3; i ++)
    {
        HouseMemberName[playerid][i][0] = EOS;
    }

    for(new x = 0; x < cache_num_rows(); x ++)
    {
        cache_get_value_name(x, "Char_Name", HouseMemberName[playerid][x]);
    }
    ShowKeysHouseList(playerid);
    return 1;
}

ShowKeysHouseList(playerid)
{
    new playerName[128], count = 0, strgbg[125];
    for(new i; i < MAX_MEMBER_HOUSE; i ++) if (HouseMemberName[playerid][i][0] != EOS)
    {
        format(strgbg, sizeof(strgbg), ""WHITE"%s\n", HouseMemberName[playerid][i]);
        strcat(playerName, strgbg);
        count++;
    }
    if(count < MAX_MEMBER_HOUSE)
        strcat(playerName, ""GREEN"+ Berikan Kunci");
    ShowPlayerDialog(playerid, DIALOG_HKEYS, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Pemegang Kunci", playerName, "Pilih", "Batal");
    return 1;
}

HouseSave(id)
{
    new shstr[1218];
    format(shstr, sizeof(shstr), "UPDATE `house` SET `HS_Owner`='%s', `HS_OwnerID`=%d, `HS_Claimed`=%d, `HS_Type`=%d, `HS_Interior`=%d, \
    `HS_ExtPosX`=%f, `HS_ExtPosY`=%f, `HS_ExtPosZ`=%f, `HS_ExtPosA`=%f, `HS_IntPosX`=%f, `HS_IntPosY`=%f, `HS_IntPosZ`=%f, `HS_IntPosA`=%f, \
    `HS_Weapon1`=%d, `HS_Weapon2`=%d, `HS_Weapon3`=%d, `HS_Weapon4`=%d, `HS_Weapon5`=%d, `HS_Ammo1`=%d, `HS_Ammo2`=%d, `HS_Ammo3`=%d, `HS_Ammo4`=%d, `HS_Ammo5`=%d, `HS_GarageX`=%f, `HS_GarageY`=%f, `HS_GarageZ`=%f, \
    `HS_GarageSpawnX`=%f, `HS_GarageSpawnY`=%f, `HS_GarageSpawnZ`=%f, `HS_GarageSpawnA`=%f, `HS_GarageInterior`=%d, `HS_GarageWorld`=%d, `HS_Capacity`=%f, \
    `HS_HelipadX`=%f, `HS_HelipadY`=%f, `HS_HelipadZ`=%f, `HS_HelipadSpawnX`=%f, `HS_HelipadSpawnY`=%f, `HS_HelipadSpawnZ`=%f, `HS_HelipadSpawnA`=%f, `HS_HelipadInterior`=%d, `HS_HelipadWorld`=%d, \
    `HS_BrankasX`=%f, `HS_BrankasY`=%f, `HS_BrankasZ`=%f WHERE `ID`=%d",
    HouseData[id][hsOwner], HouseData[id][hsOwnerID], HouseData[id][hsClaimed], HouseData[id][hsType], HouseData[id][hsInt], HouseData[id][hsExtPos][0],
    HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2], HouseData[id][hsExtPos][3], HouseData[id][hsIntPos][0], HouseData[id][hsIntPos][1], HouseData[id][hsIntPos][2], HouseData[id][hsIntPos][3],
    HouseData[id][hsWeapon][0], HouseData[id][hsWeapon][1], HouseData[id][hsWeapon][2], HouseData[id][hsWeapon][3], HouseData[id][hsWeapon][4], HouseData[id][hsAmmo][0], HouseData[id][hsAmmo][1], HouseData[id][hsAmmo][2], HouseData[id][hsAmmo][3], HouseData[id][hsAmmo][4],
    HouseData[id][housegaragePos][0], HouseData[id][housegaragePos][1], HouseData[id][housegaragePos][2], HouseData[id][housegarageSpawnPos][0], HouseData[id][housegarageSpawnPos][1], HouseData[id][housegarageSpawnPos][2], HouseData[id][housegarageSpawnPos][3],
    HouseData[id][housegarageInt], HouseData[id][housegarageWorld], HouseData[id][houseMaxCapacity], HouseData[id][househelipadPos][0], HouseData[id][househelipadPos][1], HouseData[id][househelipadPos][2],
    HouseData[id][househelipadSpawnPos][0], HouseData[id][househelipadSpawnPos][1], HouseData[id][househelipadSpawnPos][2], HouseData[id][househelipadSpawnPos][3], HouseData[id][househelipadInt], HouseData[id][househelipadWorld], 
    HouseData[id][housebrankasPos][0], HouseData[id][housebrankasPos][1], HouseData[id][housebrankasPos][2], id);
    return mysql_tquery(g_SQL, shstr);
}

/*HouseBrankas_Area(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1025.4963, -1850.0709, -34.0800)) return 1;
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1961.6010, -2393.2036, -5.3809)) return 1;
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1470.4167, 1581.6273, 711.3125)) return 1;    
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1152.3268, -1634.0383, -26.7109)) return 1; // Brankas Frank
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1312.5522, 1571.3951, 1006.0914)) return 1; // Brankas Rudy
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1699.7654, -1472.8687, 3002.8413)) return 1; // Brankas Bas
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1385.3816, -772.1603, 3007.1279)) return 1; // Brankas Taufiq
    if(IsPlayerInRangeOfPoint(playerid, 2.0, -899.7325, -509.3965, -87.1744)) return 1; // Brankas Bay
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1555.4872, -1613.9661, 328.7875)) return 1; // Brankas Vin
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 2056.2632, 1326.3376, 1003.5000)) return 1; // Brankas Agus
    if(IsPlayerInRangeOfPoint(playerid, 2.0, -2533.4326, 1984.3046, 9.0048)) return 1; // Brankas Piyo
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1177.7626, -1735.0680, 3059.0205)) return 1; // Brankas Mahen
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1312.9015, -1421.9357, 1018.0255)) return 1; // Brankas Abeng
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1311.6315, 1595.9337, 1010.9063)) return 1; // Brankas Serana
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 3453.3645, 586.9905, 637.0519)) return 1; // Brankas A
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1531.9861, -673.5004, 49.2960)) return 1; // Gema
    if(IsPlayerInRangeOfPoint(playerid, 2.0, -2685.3752, 776.8386, 10055.9629)) return 1; // Aluna
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1333.4060, 4589.4561, 1013.9850)) return 1; // Azzahra
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1671.7180, -352.1066, 3002.8413)) return 1; // Bejo
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 1671.7257, 3647.8896, 3002.8413)) return 1; // Aiden
    return 0;
}*/

House_Nearest(playerid)
{
    foreach(new i : House) if (IsPlayerInRangeOfPoint(playerid, 1.0, HouseData[i][hsExtPos][0], HouseData[i][hsExtPos][1], HouseData[i][hsExtPos][2]))
    {
        return i;
    }
    return -1;
}

GarasiHouseNearest(playerid)
{
    foreach(new i : House) if (IsPlayerInDynamicArea(playerid, HouseData[i][housegarageArea]))
    {
        return i;
    }
    return -1;
}

HelipadHouseNearest(playerid)
{
    foreach(new i : House) if (IsPlayerInRangeOfPoint(playerid, 3.0, HouseData[i][househelipadPos][0], HouseData[i][househelipadPos][1], HouseData[i][househelipadPos][2]))
    {
        return i;
    }
    return -1;
}

House_Inside(playerid)
{
    if(AccountData[playerid][pInHouse] != -1)
    {
        for (new i = 0; i != MAX_RUMAH; i ++) if (i == AccountData[playerid][pInHouse] && GetPlayerInterior(playerid) == HouseData[i][hsInt] && GetPlayerVirtualWorld(playerid) != -1) {
            return i;
        }
    }
    return -1;
}

/*House_Inside(playerid)
{
    if (AccountData[playerid][pInHouse] != -1)
    {
        foreach(new hid : House) if(hid == AccountData[playerid][pInHouse] && GetPlayerInterior(playerid) == HouseData[hid][hsInt] && GetPlayerVirtualWorld(playerid) != -1) {
            return hid;
        }
    }
    return -1;
}*/

House_Typee(houseid)
{
    if(HouseData[houseid][hsType] == 1)
    {
        HouseData[houseid][hsIntPos][0] = 1019.2642;
        HouseData[houseid][hsIntPos][1] = -1849.3958;
        HouseData[houseid][hsIntPos][2] = -34.0859;
        HouseData[houseid][hsIntPos][3] = 178.3657;
        HouseData[houseid][hsInt] = 2;
    }
    if(HouseData[houseid][hsType] == 2)
    {
        HouseData[houseid][hsIntPos][0] = 1960.2148;
        HouseData[houseid][hsIntPos][1] = -2387.8936;
        HouseData[houseid][hsIntPos][2] = -8.9141;
        HouseData[houseid][hsIntPos][3] = 268.7358;
        HouseData[houseid][hsInt] = 7;
    }
    if(HouseData[houseid][hsType] == 3)
    {
        HouseData[houseid][hsIntPos][0] = 1155.8569;
        HouseData[houseid][hsIntPos][1] = -1651.1879;
        HouseData[houseid][hsIntPos][2] = -26.7109;
        HouseData[houseid][hsIntPos][3] = 358.9859;
        HouseData[houseid][hsInt] = 3;
    }
    if(HouseData[houseid][hsType] == 4)
    {
        HouseData[houseid][hsIntPos][0] = 1155.8569;
        HouseData[houseid][hsIntPos][1] = -1651.1879;
        HouseData[houseid][hsIntPos][2] = -26.7109;
        HouseData[houseid][hsIntPos][3] = 358.9859;
        HouseData[houseid][hsInt] = 3;

    }
    new query[512];
    mysql_format(g_SQL, query, sizeof query, "UPDATE house SET HS_IntPosX='%f', HS_IntPosY='%f', HS_IntPosZ='%f', HS_IntPosA='%f', HS_Interior='%d' WHERE ID='%d'", HouseData[houseid][hsIntPos][0], HouseData[houseid][hsIntPos][1], HouseData[houseid][hsIntPos][2], HouseData[houseid][hsIntPos][3], HouseData[houseid][hsInt], houseid);
    mysql_tquery(g_SQL, query);
}

HouseRefresh(houseid)
{
    if(houseid != -1)
    {
        if(DestroyDynamic3DTextLabel(HouseData[houseid][hsLabel]))
            HouseData[houseid][hsLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(HouseData[houseid][hsLabelExit]))
            HouseData[houseid][hsLabelExit] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(HouseData[houseid][hsLabelBrankas]))
            HouseData[houseid][hsLabelBrankas] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        /*if(DestroyDynamicPickup(HouseData[houseid][housegaragePickup]))
            HouseData[houseid][housegaragePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(HouseData[houseid][housegarageLabel]))
            HouseData[houseid][housegarageLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;*/

        if(DestroyDynamicObject(HouseData[houseid][househelipadObject]))
            HouseData[houseid][househelipadObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamicArea(HouseData[houseid][househelipadArea]))
            HouseData[houseid][househelipadArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(HouseData[houseid][housebrankasLabel]))
            HouseData[houseid][housebrankasLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        static string[255];
        
        if(strcmp(HouseData[houseid][hsOwner], "-") || HouseData[houseid][hsOwnerID] != 0) 
        {
            // format(string, sizeof string, ""GREEN"[Y]"WHITE" Rumah %s\n%s", HouseData[houseid][hsOwner], GetTypeHouseName(houseid));
            format(string, sizeof(string), ""LIGHTGREY"[%s House]\n"WHITE"Use "YELLOW"[Y]"WHITE" to Enter House\nRumah %s", GetTypeHouseName(houseid), HouseData[houseid][hsOwner]);
        }

        if(HouseData[houseid][hsClaimed] != 1) 
        {
            format(string, sizeof string, ""YELLOW"`/klaimrumah`"WHITE" Untuk mengklaim Rumah");
        }

        if(HouseData[houseid][househelipadPos][0] != 0.0)
        {
            HouseData[houseid][househelipadObject] = CreateCirclePickup(PICKUP_GREEN, HouseData[houseid][househelipadPos][0], HouseData[houseid][househelipadPos][1], HouseData[houseid][househelipadPos][2], HouseData[houseid][househelipadWorld], HouseData[houseid][househelipadInt], -1); 
            HouseData[houseid][househelipadArea] = CreateDynamicSphere(HouseData[houseid][househelipadPos][0], HouseData[houseid][househelipadPos][1], HouseData[houseid][househelipadPos][2], 2.0, HouseData[houseid][househelipadWorld], HouseData[houseid][househelipadInt], -1, 0);
        }

        if(HouseData[houseid][housegaragePos][0] != 0.0)
        {
            HouseData[houseid][housegarageArea] = CreateDynamicSphere(HouseData[houseid][housegaragePos][0], HouseData[houseid][housegaragePos][1], HouseData[houseid][housegaragePos][2], 5.0, HouseData[houseid][housegarageWorld], HouseData[houseid][housegarageInt], -1);
            // HouseData[houseid][housegaragePickup] = CreateDynamicPickup(19131, 23, HouseData[houseid][housegaragePos][0], HouseData[houseid][housegaragePos][1], HouseData[houseid][housegaragePos][2] + 1.5, HouseData[houseid][housegarageWorld], HouseData[houseid][housegarageInt], -1, 10.0, -1, 0);
            // HouseData[houseid][housegarageLabel] = CreateDynamic3DTextLabel(""LIGHTGREY"[House Garage]\n"WHITE"Gunakan "YELLOW"klakson"WHITE" untuk memasukkan kendaraan\nTekan "YELLOW"[Y]"WHITE" untuk mengeluarkan kendaraan", -1, HouseData[houseid][housegaragePos][0], HouseData[houseid][housegaragePos][1], HouseData[houseid][housegaragePos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, HouseData[houseid][housegarageWorld], HouseData[houseid][housegarageInt], -1, 10.0, -1, 0);
        }
        if(HouseData[houseid][hsExtPos][0] != 0.0)
        {
            HouseData[houseid][hsLabel] = CreateDynamic3DTextLabel(string, -1, HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2] + 0.15, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 5.0, -1, 0);
        }

        if(HouseData[houseid][hsIntPos][0] != 0.0)
        {
            HouseData[houseid][hsLabelExit] = CreateDynamic3DTextLabel(""RED"[Y]"WHITE" Keluar", -1, HouseData[houseid][hsIntPos][0],HouseData[houseid][hsIntPos][1], HouseData[houseid][hsIntPos][2] + 0.15, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, houseid, HouseData[houseid][hsInt], -1, 5.0, -1, 0);
        }

        if(HouseData[houseid][housebrankasPos][0] != 0.0)
        {
            HouseData[houseid][housebrankasLabel] = CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, HouseData[houseid][housebrankasPos][0], HouseData[houseid][housebrankasPos][1], HouseData[houseid][housebrankasPos][2], 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, houseid, HouseData[houseid][hsInt], -1, 8.0, -1, 0);
        }
        
        /*if(HouseData[houseid][hsType] == 1)
        {
            HouseData[houseid][hsLabelBrankas] = CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1025.4963, -1850.0709, -34.0800, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
        }
        if(HouseData[houseid][hsType] == 2)
        {
            HouseData[houseid][hsLabelBrankas] = CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1961.6010, -2393.2036, -5.3809, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
        }
        if(HouseData[houseid][hsType] == 3 || HouseData[houseid][hsType] == 4)
        {
            HouseData[houseid][hsLabelBrankas] = CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1152.3268, -1634.0383, -26.7109, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
        }*/
    }
    return 1;
}

/*hook OnGameModeInit()
{
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1470.4167, 1581.6273, 711.3125, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 10, -1, 10.0, -1, 0); // Frank
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1312.5522, 1571.3951, 1006.0914, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 23, -1, 10.0, -1, 0); // Rudy
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1699.7654, -1472.8687, 3002.8413, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 35, -1, 10.0, -1, 0); // Gil
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1385.3816, -772.1603, 3007.1279, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 25, -1, 10.0, -1, 0); // Taufiq
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, -899.7325, -509.3965, -87.1744, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 30, -1, 10.0, -1, 0); // Bay
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1555.4872, -1613.9661, 328.7875, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 21, -1, 10.0, -1, 0); // Vin
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 2056.2632, 1326.3376, 1003.5000, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 10, -1, 10.0, -1, 0); // Agus
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, -2533.4326, 1984.3046, 9.0048, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 30, -1, 10.0, -1, 0); // Piyo
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1177.7626, -1735.0680, 3059.0205, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 31, -1, 10.0, -1, 0); // Mahen
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1312.9015, -1421.9357, 1018.0255, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 41, -1, 10.0, -1, 0); // Abeng
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1311.6315, 1595.9337, 1010.9063, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 42, -1, 10.0, -1, 0); // Serana
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 3453.3645, 586.9905, 637.0519, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 43, -1, 10.0, -1, 0); // A
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1531.9861, -673.5004, 49.2960, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 44, -1, 10.0, -1, 0); // Gema
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, -2685.3752, 776.8386, 10055.9629, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 45, -1, 10.0, -1, 0); // Aluna
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1333.4060, 4589.4561, 1013.9850, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 46, -1, 10.0, -1, 0); // Azzahra
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1671.7180, -352.1066, 3002.8413, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 47, -1, 10.0, -1, 0); // Bejo
    CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE"- Brankas", -1, 1671.7257, 3647.8896, 3002.8413, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 48, -1, 10.0, -1, 0); // Aiden
    return 1;
}*/

forward LoadRumah();
public LoadRumah()
{
    new hid, rows = cache_num_rows();
    if(rows)
    {
        for(new i = 0; i < rows; i ++)
        {
            cache_get_value_name_int(i, "ID", hid);
            cache_get_field_content(i, "HS_Owner", HouseData[hid][hsOwner], 128);
            
            cache_get_value_name_int(i, "HS_OwnerID", HouseData[hid][hsOwnerID]);
            cache_get_value_name_int(i, "HS_Type", HouseData[hid][hsType]);
            cache_get_value_name_int(i, "HS_Claimed", HouseData[hid][hsClaimed]);

            cache_get_value_name_float(i, "HS_ExtPosX", HouseData[hid][hsExtPos][0]);
            cache_get_value_name_float(i, "HS_ExtPosY", HouseData[hid][hsExtPos][1]);
            cache_get_value_name_float(i, "HS_ExtPosZ", HouseData[hid][hsExtPos][2]);
            cache_get_value_name_float(i, "HS_ExtPosA", HouseData[hid][hsExtPos][3]);
            cache_get_value_name_float(i, "HS_IntPosX", HouseData[hid][hsIntPos][0]);
            cache_get_value_name_float(i, "HS_IntPosY", HouseData[hid][hsIntPos][1]);
            cache_get_value_name_float(i, "HS_IntPosZ", HouseData[hid][hsIntPos][2]);
            cache_get_value_name_float(i, "HS_IntPosA", HouseData[hid][hsIntPos][3]);
            
			cache_get_value_name_int(i, "HS_Interior", HouseData[hid][hsInt]);
			cache_get_value_name_int(i, "HS_Weapon1", HouseData[hid][hsWeapon][0]);
			cache_get_value_name_int(i, "HS_Weapon2", HouseData[hid][hsWeapon][1]);
			cache_get_value_name_int(i, "HS_Weapon3", HouseData[hid][hsWeapon][2]);
			cache_get_value_name_int(i, "HS_Weapon4", HouseData[hid][hsWeapon][3]);
			cache_get_value_name_int(i, "HS_Weapon5", HouseData[hid][hsWeapon][4]);
			cache_get_value_name_int(i, "HS_Ammo1", HouseData[hid][hsAmmo][0]);
			cache_get_value_name_int(i, "HS_Ammo2", HouseData[hid][hsAmmo][1]);
			cache_get_value_name_int(i, "HS_Ammo3", HouseData[hid][hsAmmo][2]);
			cache_get_value_name_int(i, "HS_Ammo4", HouseData[hid][hsAmmo][3]);
			cache_get_value_name_int(i, "HS_Ammo5", HouseData[hid][hsAmmo][4]);

            // Garage
			cache_get_value_name_float(i, "HS_GarageX", HouseData[hid][housegaragePos][0]);
			cache_get_value_name_float(i, "HS_GarageY", HouseData[hid][housegaragePos][1]);
			cache_get_value_name_float(i, "HS_GarageZ", HouseData[hid][housegaragePos][2]);
			cache_get_value_name_float(i, "HS_GarageSpawnX", HouseData[hid][housegarageSpawnPos][0]);
			cache_get_value_name_float(i, "HS_GarageSpawnY", HouseData[hid][housegarageSpawnPos][1]);
			cache_get_value_name_float(i, "HS_GarageSpawnZ", HouseData[hid][housegarageSpawnPos][2]);
			cache_get_value_name_float(i, "HS_GarageSpawnA", HouseData[hid][housegarageSpawnPos][3]);
            cache_get_value_name_float(i, "HS_Capacity", HouseData[hid][houseMaxCapacity]);

            cache_get_value_name_int(i, "HS_GarageInterior", HouseData[hid][housegarageInt]);
            cache_get_value_name_int(i, "HS_GarageWorld", HouseData[hid][housegarageWorld]);

            // Helipad
            cache_get_value_name_float(i, "HS_HelipadX", HouseData[hid][househelipadPos][0]);
            cache_get_value_name_float(i, "HS_HelipadY", HouseData[hid][househelipadPos][1]);
            cache_get_value_name_float(i, "HS_HelipadZ", HouseData[hid][househelipadPos][2]);
            cache_get_value_name_float(i, "HS_HelipadSpawnX", HouseData[hid][househelipadSpawnPos][0]);
            cache_get_value_name_float(i, "HS_HelipadSpawnY", HouseData[hid][househelipadSpawnPos][1]);
            cache_get_value_name_float(i, "HS_HelipadSpawnZ", HouseData[hid][househelipadSpawnPos][2]);
            cache_get_value_name_float(i, "HS_HelipadSpawnA", HouseData[hid][househelipadSpawnPos][3]);

            cache_get_value_name_int(i, "HS_HelipadInterior", HouseData[hid][househelipadInt]);
            cache_get_value_name_int(i, "HS_HelipadWorld", HouseData[hid][househelipadWorld]);
            
            HouseData[hid][househelipadArea] = CreateDynamicSphere(HouseData[hid][househelipadPos][0], HouseData[hid][househelipadPos][1], HouseData[hid][househelipadPos][2], 2.0, HouseData[hid][househelipadWorld], HouseData[hid][househelipadInt], -1, 0);

            // Brankas
            cache_get_value_name_float(i, "HS_BrankasX", HouseData[hid][housebrankasPos][0]);
            cache_get_value_name_float(i, "HS_BrankasY", HouseData[hid][housebrankasPos][1]);
            cache_get_value_name_float(i, "HS_BrankasZ", HouseData[hid][housebrankasPos][2]);
        
            Iter_Add(House, hid);   
            HouseRefresh(hid);
            Profiler_Dump();
        }
        printf("[Dynamic House]: Jumlah total Rumah yang dimuat %d.", rows);
    }
    return 1;
}

CMD:customint(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new hid, Float:x, Float:y, Float:z, Float:a, int;
    if(sscanf(params, "dffffd", hid, x, y, z, a, int)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/customint [house id] [int x] [int y] [int z] [int a], interior");
    if(hid < 0 || hid >= MAX_RUMAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID House tidak valid!");
    if(!Iter_Contains(House, hid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID House tidak ada!");

    HouseData[hid][hsIntPos][0] = x;
    HouseData[hid][hsIntPos][1] = y;
    HouseData[hid][hsIntPos][2] = z;
    HouseData[hid][hsIntPos][3] = a;
    HouseData[hid][hsInt] = int;

    HouseRefresh(hid);
    HouseSave(hid);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Mengcustom interior House ID %d", AccountData[playerid][pAdminname], hid);
    
    new query[255];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `house` SET `HS_IntPosX`=%f, `HS_IntPosY`=%f, `HS_IntPosZ`=%f, `HS_IntPosA`=%f, `HS_Interior`=%d WHERE `ID`=%d", HouseData[hid][hsIntPos][0], HouseData[hid][hsIntPos][1], HouseData[hid][hsIntPos][2], HouseData[hid][hsIntPos][3], HouseData[hid][hsInt], hid);
    mysql_tquery(g_SQL, query);
    return 1;
}

CMD:addhouse(playerid, params[])
{
    if(CheckAdmin(playerid, 6)) 
        return PermissionError(playerid);
    
    new houseid = Iter_Free(House), query[512];
    if(houseid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuat dynamic rumah lagi!");
    new type;
    if(sscanf(params, "d", type)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addhouse [type] [1 - 3]");
    format(HouseData[houseid][hsOwner], 128, "-");
    HouseData[houseid][hsOwnerID] = 0;
    GetPlayerPos(playerid, HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2]);
    GetPlayerFacingAngle(playerid, HouseData[houseid][hsExtPos][3]);
    HouseData[houseid][hsType] = type;
    HouseData[houseid][hsClaimed] = 0;

    HouseRefresh(houseid);
    House_Typee(houseid);
    Iter_Add(House, houseid);
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO house SET ID='%d', HS_Owner='%s', HS_OwnerID='%d', HS_Claimed='%d', HS_Type='%d', HS_ExtPosX='%f', HS_ExtPosY='%f', HS_ExtPosZ='%f', HS_ExtPosA='%f'", houseid, HouseData[houseid][hsOwner], HouseData[houseid][hsOwnerID], HouseData[houseid][hsClaimed], HouseData[houseid][hsType], HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2], HouseData[houseid][hsExtPos][3]);
	mysql_tquery(g_SQL, query, "OnHouseCreated", "ii", playerid, houseid);    
	return 1;
}

CMD:edithouse(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    static 
        did,
        type[24],
        string[128];
    
    if(sscanf(params, "ds[24]S()[128]", did, type, string)) 
    {
        Syntax(playerid, "/edithouse [id] [entinity]");
        Syntax(playerid, "~> (owner, location, delete, brankas, type, garage, garagespawn, garageremove, helipad, helipadspawn, helipadremove)");
        return 1;
        //ShowTDN(playerid, NOTIFICATION_SYNTAX, "/edithouse [id] [entity]~n~location, delete, type, garage, garagepos, garagespawn, garageremove");
    }
    if(did < 0 || did >= MAX_RUMAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID House tidak valid!");
    if(!Iter_Contains(House, did)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rumah tidak ada!");

    if(!strcmp(type, "garage", true))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        HouseData[did][housegaragePos][0] = x;
        HouseData[did][housegaragePos][1] = y;
        HouseData[did][housegaragePos][2] = z;
        HouseData[did][housegarageInt] = GetPlayerInterior(playerid);
        HouseData[did][housegarageWorld] = GetPlayerVirtualWorld(playerid);

        HouseRefresh(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menetapkan Garasi Rumah ID: %d", AccountData[playerid][pAdminname], did);
    }
    else if(!strcmp(type, "owner", true))
    {
        new otherid;
        if(sscanf(string, "u", otherid)) return Syntax(playerid, "/edithouse [id] [owner] [name/playerid]");
        if(!IsPlayerConnected(otherid)) return Error(playerid, "Pemain tersebut tidak terkoneksi ke server!");
        foreach(new ii : House) if (HouseData[ii][hsExtPos][0] != 0.0)
        {
            if(!strcmp(HouseData[ii][hsOwner], AccountData[otherid][pName], true)) return Error(playerid, "Pemain tersebut sudah memiliki rumah lain!");
        }
        static oldhousename[MAX_PLAYER_NAME];
        format(oldhousename, MAX_PLAYER_NAME, HouseData[did][hsOwner]);

        format(HouseData[did][hsOwner], MAX_PLAYER_NAME, AccountData[otherid][pName]);
        HouseData[did][hsOwnerID] = AccountData[otherid][pID];

        HouseRefresh(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah hak milik Rumah %s menjadi milik %s", AccountData[playerid][pAdminname], oldhousename, AccountData[otherid][pName]);

        static shstr[200];
        format(shstr, sizeof(shstr), "Menggunakan cmd /edithouse [owner] pada House ID: milik %s menjadi milik %s.", did, oldhousename, AccountData[otherid][pName]);
        AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr); 
    }
    else if(!strcmp(type, "brankas", true))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        HouseData[did][housebrankasPos][0] = x;
        HouseData[did][housebrankasPos][1] = y;
        HouseData[did][housebrankasPos][2] = z;

        HouseRefresh(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menetapkan posisi Brankas Rumah ID: %d", AccountData[playerid][pAdminname], did);
    }
    else if(!strcmp(type, "helipad", true))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        HouseData[did][househelipadPos][0] = x;
        HouseData[did][househelipadPos][1] = y;
        HouseData[did][househelipadPos][2] = z;
        HouseData[did][househelipadInt] = GetPlayerInterior(playerid);
        HouseData[did][househelipadWorld] = GetPlayerVirtualWorld(playerid);

        HouseRefresh(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menetapkan Helipad Rumah ID: %d", AccountData[playerid][pAdminname], did);
    }
    else if(!strcmp(type, "type", true))
    {
        new value;
        if(sscanf(string, "d", value)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/edithouse [id] [type] [type 1 - 4]");
        if(value < 1 || value > 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Type tidak valid!");

        HouseData[did][hsType] = value;
        HouseRefresh(did);
        House_Typee(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Mengubah type ID Rumah: %d menjadi Type %s", GetAdminName(playerid), did, GetTypeHouseName(did));

        static shstr[255];
        format(shstr, sizeof(shstr), "Menggunakan cmd /edithouse [type] %s pada House ID: %d.", GetTypeHouseName(did), did);
        AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr); 
    }
    else if(!strcmp(type, "location", true))
    {
        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        HouseData[did][hsExtPos][0] = x;
        HouseData[did][hsExtPos][1] = y;
        HouseData[did][hsExtPos][2] = z;
        HouseData[did][hsExtPos][3] = a;

        HouseRefresh(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Memindahkan exterior position Rumah ID: %d", AccountData[playerid][pName], did);
    }
    else if(!strcmp(type, "delete", true))
    {   
        DestroyDynamic3DTextLabel(HouseData[did][hsLabel]);
        DestroyDynamic3DTextLabel(HouseData[did][hsLabelExit]);
        DestroyDynamic3DTextLabel(HouseData[did][hsLabelBrankas]);
        // DestroyDynamicPickup(HouseData[did][housegaragePickup]);
        // DestroyDynamic3DTextLabel(HouseData[did][housegarageLabel]);
        DestroyDynamicArea(HouseData[did][housegarageArea]);

        HouseData[did][hsExtPos][0] = HouseData[did][hsExtPos][1] = HouseData[did][hsExtPos][2] = HouseData[did][hsExtPos][3] = 0.0;
        HouseData[did][hsIntPos][0] = HouseData[did][hsIntPos][1] = HouseData[did][hsIntPos][2] = HouseData[did][hsIntPos][3] = 0.0;
        HouseData[did][housegaragePos][0] = HouseData[did][housegaragePos][1] = HouseData[did][housegaragePos][2] = 0.0;
        HouseData[did][housegarageSpawnPos][0] = HouseData[did][housegarageSpawnPos][1] = HouseData[did][housegarageSpawnPos][2] = HouseData[did][housegarageSpawnPos][3] = 0.0;
        HouseData[did][hsLabel] = HouseData[did][hsLabelBrankas] = HouseData[did][hsLabelExit] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        HouseData[did][housegarageArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        HouseData[did][hsInt] = 0;
        
        HouseRefresh(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menggusur Rumah ID: %d.", GetAdminName(playerid), did);

        foreach(new i : Player) if(IsPlayerConnected(i)) 
        {
            if(HouseData[did][hsOwnerID] == AccountData[i][pID])
            {
                AccountData[i][pOwnedHouse] = -1;
            }
        }
        Iter_Remove(House, did);
        
        static jskc[512], tss[255], shstr[125];
        mysql_format(g_SQL, jskc, sizeof(jskc), "UPDATE `player_characters` SET `Char_OwnedHouse` = -1, `Char_FriendHouse`= -1 WHERE `pID`=%d", HouseData[did][hsOwnerID]);
        mysql_tquery(g_SQL, jskc);  

        mysql_format(g_SQL, tss, sizeof(tss), "UPDATE `player_characters` SET `Char_FriendHouse`=-1 WHERE `Char_FriendHouse`=%d", did);
        mysql_tquery(g_SQL, tss);

        mysql_format(g_SQL, jskc, sizeof(jskc), "DELETE FROM `house` WHERE `ID`=%d", did);
        mysql_tquery(g_SQL, jskc);

        format(shstr, sizeof(shstr), "Menggunakan cmd /edithouse [delete] pada House ID: %d.", did);
        AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr); 
    }
    else if(!strcmp(type, "garageremove", true))
    {
        HouseData[did][housegaragePos][0] = HouseData[did][housegaragePos][1] = HouseData[did][housegaragePos][2] = 0.0;
        HouseData[did][housegarageSpawnPos][0] = HouseData[did][housegarageSpawnPos][1] = HouseData[did][housegarageSpawnPos][2] = HouseData[did][housegarageSpawnPos][3] = 0.0;
        HouseData[did][housegarageInt] = HouseData[did][housegarageWorld] = 0;

        // if(DestroyDynamicPickup(HouseData[did][housegaragePickup])) HouseData[did][housegaragePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        // if(DestroyDynamic3DTextLabel(HouseData[did][housegarageLabel])) HouseData[did][housegarageLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicArea(HouseData[did][housegarageArea])) HouseData[did][housegarageArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        HouseRefresh(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Telah menghapus Garasi Rumah ID: %d", AccountData[playerid][pAdminname], did);
        
        new shstr[225];
        format(shstr, sizeof(shstr), "Menggunakan cmd /edithouse [garageremove] pada House ID: %d.", did);
        AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr); 
    }
    else if(!strcmp(type, "helipadremove", true))
    {
        HouseData[did][househelipadPos][0] = HouseData[did][househelipadPos][1] = HouseData[did][househelipadPos][2] = 0.0;
        HouseData[did][househelipadSpawnPos][0] = HouseData[did][househelipadSpawnPos][1] = HouseData[did][househelipadSpawnPos][2] = HouseData[did][househelipadSpawnPos][3] = 0.0;
        HouseData[did][househelipadInt] = HouseData[did][househelipadWorld] = 0;

        if(DestroyDynamicObject(HouseData[did][househelipadObject])) HouseData[did][househelipadObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        if(DestroyDynamicArea(HouseData[did][househelipadArea])) HouseData[did][househelipadArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        HouseRefresh(did);
        HouseSave(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Telah menghapus Helipad Rumah ID: %d", AccountData[playerid][pAdminname], did);

        new shstr[225];
        format(shstr, sizeof(shstr), "Menggunakan cmd /edithouse [helipadremove] pada House ID: %d.", did);
        AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr); 
    }
    else if(!strcmp(type, "garagespawn", true))
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        new Float:x, Float:y, Float:z, Float:a;
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehiclePos(vehicleid, x, y, z);
            GetVehicleZAngle(vehicleid, a);

            HouseData[did][housegarageSpawnPos][0] = x;
            HouseData[did][housegarageSpawnPos][1] = y;
            HouseData[did][housegarageSpawnPos][2] = z;
            HouseData[did][housegarageSpawnPos][3] = a;

            HouseSave(did);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan Garasi Rumah Spawn ID: %d", AccountData[playerid][pAdminname], did);
        }
        else 
        {
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);

            HouseData[did][housegarageSpawnPos][0] = x;
            HouseData[did][housegarageSpawnPos][1] = y;
            HouseData[did][housegarageSpawnPos][2] = z;
            HouseData[did][housegarageSpawnPos][3] = a;

            HouseSave(did);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan Garasi Rumah Spawn ID: %d", AccountData[playerid][pAdminname], did);
        }
    }
    else if(!strcmp(type, "helipadspawn", true))
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        new Float:x, Float:y, Float:z, Float:a;
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehiclePos(vehicleid, x, y, z);
            GetVehicleZAngle(vehicleid, a);

            HouseData[did][househelipadSpawnPos][0] = x;
            HouseData[did][househelipadSpawnPos][1] = y;
            HouseData[did][househelipadSpawnPos][2] = z;
            HouseData[did][househelipadSpawnPos][3] = a;

            HouseSave(did);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan spawn Helipad Rumah ID: %d", AccountData[playerid][pAdminname], did);
        }
        else 
        {
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);

            HouseData[did][househelipadSpawnPos][0] = x;
            HouseData[did][househelipadSpawnPos][1] = y;
            HouseData[did][househelipadSpawnPos][2] = z;
            HouseData[did][househelipadSpawnPos][3] = a;

            HouseSave(did);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan spawn Helipad Rumah ID: %d", AccountData[playerid][pAdminname], did);
        }
    }
    return 1;
}

CMD:gotohouse(playerid, params[])
{
    if(CheckAdmin(playerid, 4))
        return PermissionError(playerid);
    
    new hid;
    if(sscanf(params, "d", hid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotohouse [id]");
    if(!Iter_Contains(House, hid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID House itu tidak ada!");
    SetPlayerPosition(playerid, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2], HouseData[hid][hsExtPos][3]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Rumah ID: %d", GetAdminName(playerid), hid);
    return 1;
}

CMD:gotointhouse(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);
    
    new id;
    if(sscanf(params, "d", id)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotointhouse [house id]");
    
    if((id < 0 || id >= MAX_RUMAH))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID House tidak valid!");

    if(!Iter_Contains(House, id))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID House tidak ada!");

    SetPlayerPositionEx(playerid, HouseData[id][hsIntPos][0], HouseData[id][hsIntPos][1], HouseData[id][hsIntPos][2], HouseData[id][hsIntPos][3], 1500);
    SetPlayerInteriorEx(playerid, HouseData[id][hsInt]);
    SetPlayerVirtualWorldEx(playerid, id);
    AccountData[playerid][pInHouse] = id;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Interior Rumah ID: %d", GetAdminName(playerid), id);
    return 1;
}

function OnHouseCreated(playerid, hid)
{
    House_Typee(hid);
    HouseRefresh(hid);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Dynamic Rumah ID: %d.", GetAdminName(playerid), hid);

    static shstr[125];
	format(shstr, sizeof(shstr), "Menggunakan cmd /addhouse dengan type rumah %s id %d.", GetTypeHouseName(HouseData[hid][hsType]), hid);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
    return 1;
}

GetTypeHouseName(hid)
{
    new name[128];
    if(hid != -1)
    {
        if(HouseData[hid][hsType] == 1)
        {
            name = "Standart";
        }
        else if(HouseData[hid][hsType] == 2)
        {
            name = "Medium";
        }
        else if(HouseData[hid][hsType] == 3)
        {
            name = "Modern";
        }
        else if(HouseData[hid][hsType] == 4 || HouseData[hid][hsType] == 99)
        {
            name = "Mansion";
        }
    }
    return name;
}

ShowHouseWeapons(playerid, hid) 
{
    if(hid == -1) return 0;

    static shstr[596];

    shstr[0] = 0;

    format(shstr, sizeof(shstr), "#\tWeapon\tAmmo\n");
    for (new i = 0; i < 5; i ++) 
    {
        if(!HouseData[hid][hsWeapon][i])
            format(shstr, sizeof(shstr), "%s"GREEN"%d\t"GREEN"Empty Slot\t"GREEN"-\n", shstr, i);
        
        else 
            format(shstr, sizeof(shstr), "%s"GREEN"%d\t"GREEN"%s\t"GREEN"%d\n", shstr, i, ReturnWeaponName(HouseData[hid][hsWeapon][i]), HouseData[hid][hsAmmo][i]);
    }
    ShowPlayerDialog(playerid, DIALOG_WEAPON_CHEST, DIALOG_STYLE_TABLIST_HEADERS, ""City"Happy Roleplay "WHITE"- Weapon Chest", shstr, "Pilih", "Batal");
    return 1;
}

forward OnHouseDeposit(playerid);
public OnHouseDeposit(playerid)
{
    AccountData[playerid][menuShowed] = false;
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    HouseBrankas[playerid][housebrankasID] = 0;
    HouseBrankas[playerid][housebrankasTemp] = EOS;
    HouseBrankas[playerid][housebrankasModel] = 0;
    HouseBrankas[playerid][housebrankasQuant] = 0;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    foreach(new i : House)
    {
        if(areaid == HouseData[i][househelipadArea])
        {
            ShowKey(playerid, "[Y] Helipad House");
        }

        if(areaid == HouseData[i][housegarageArea])
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                ShowKey(playerid, "[H] Put The Vehicle");
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ShowKey(playerid, "[Y] Take Vehicle");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    foreach(new i : House)
    {
        if(areaid == HouseData[i][househelipadArea])
        {
            HideShortKey(playerid);
        }

        if(areaid == HouseData[i][housegarageArea])
        {
            HideShortKey(playerid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new hid = House_Nearest(playerid);
        if(hid > -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.0, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2]))
            {
                if(!House_HaveAccess(playerid, hid))
                {
                    new title[100];
                    format(title, sizeof(title), ""City"Happy Roleplay "WHITE"- %s", HouseData[hid][hsOwner]);
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, title, "Rumah ini sudah dimiliki warga lain!", "Tutup", "");
                }
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                AccountData[playerid][ActivityTime] = 1;
                pTimerMasukRumah[playerid] = SetTimerEx("MasukRumah", 1000, true, "dd", playerid, hid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "MASUK");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }
        }
        new inhouseid = AccountData[playerid][pInHouse];
        if(AccountData[playerid][pInHouse] != -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.0, HouseData[inhouseid][hsIntPos][0], HouseData[inhouseid][hsIntPos][1], HouseData[inhouseid][hsIntPos][2]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                
                AccountData[playerid][ActivityTime] = 1;
                pTimerMasukRumah[playerid] = SetTimerEx("KeluarRumah", 1000, true, "dd", playerid, inhouseid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "KELUAR");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }
        }
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new hid = House_Inside(playerid);
        if(hid > -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, HouseData[hid][housebrankasPos][0], HouseData[hid][housebrankasPos][1], HouseData[hid][housebrankasPos][2]))
            {
                if(HouseData[hid][hsType] > 3) 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik\
                    \nPemegang Kunci", hid, GetLocation(HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[hid][hsOwner]),
                    shstr, "Pilih", "Batal");
                } 
                else 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik", hid, GetLocation(HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[hid][hsOwner]),
                    shstr, "Pilih", "Batal");             
                }
            }
        }
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new ghid = GarasiHouseNearest(playerid);
        if(ghid != -1)
        {
            if(!House_HaveAccess(playerid, ghid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini bukan milik anda!");
            if(CountPlayerVehicleHoused(playerid, ghid) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

            new vehid, count = CountPlayerVehicleHoused(playerid, ghid), list[596];
            format(list, sizeof(list), "No\tModel Kendaraan\tNomor Plat\n");
            for(new itt; itt < count; itt ++)
            {
                vehid = ReturnAnyVehicleHoused(playerid, itt, ghid);
                if(itt == count)
                {
                    format(list, sizeof(list), "%s%d\t%s\t%s", list, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
                } else format(list, sizeof(list), "%s%d\t%s\t%s\n", list, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
            }
            AccountData[playerid][pPark] = ghid;
            ShowPlayerDialog(playerid, DIALOG_HOUSEGARAGE_OUT, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""City"Happy Roleplay "WHITE"- Garasi Rumah %d", ghid), list, "Pilih", "Batal");
            HideShortKey(playerid);
        }

        new hpid = HelipadHouseNearest(playerid);
        if(hpid != -1)
        {
            if(!House_HaveAccess(playerid, hpid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Helipad ini bukan milik anda!");
            if(CountPlayerHelipadHoused(playerid, hpid) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di helipad ini!");

            new vehid, count = CountPlayerHelipadHoused(playerid, hpid), list[596];
            format(list, sizeof(list), "No\tModel Kendaraan\tNomor Plat\n");
            for(new itt; itt < count; itt ++)
            {
                vehid = ReturnAnyVehicleHelipad(playerid, itt, hpid);
                if(itt == count)
                {
                    format(list, sizeof(list), "%s%d\t%s\t%s", list, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
                } else format(list, sizeof(list), "%s%d\t%s\t%s\n", list, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
            }
            AccountData[playerid][pPark] = hpid;
            ShowPlayerDialog(playerid, DIALOG_HOUSEHELIPAD_OUT, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""City"Happy Roleplay "WHITE"- Garasi Helipad %d", hpid), list, "Pilih", "Batal");
        }
    }
    if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new ghid = GarasiHouseNearest(playerid);
        if(ghid > -1)
        {
            if(!House_HaveAccess(playerid, ghid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini bukan milik anda!");
            new carid = -1, bool: found = false;
            if((carid = Vehicle_Nearest2(playerid)) != -1)
            {
                if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                if(PlayerVehicle[carid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memasukkan kendaraan Rental!");
                
                Vehicle_GetStatus(carid);
                PlayerVehicle[carid][pVehHouseGarage] = ghid;

                found = true;

                RemovePlayerFromVehicle(playerid);
                SetTimerEx("InputVehicleToGarage", 2000, false, "d", carid);
                /*if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                {
                    DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                    SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                    PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                }*/
                
                HideShortKey(playerid);
            }
            if(!found) return false;
        }

        new hpid = HelipadHouseNearest(playerid);
        if(hpid > -1)
        {
            if(!House_HaveAccess(playerid, hpid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Helipad ini bukan milik anda!");
            new carid = -1, bool: found = false;
            if((carid = Vehicle_Nearest2(playerid)) != -1)
            {
                if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                if(PlayerVehicle[carid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memasukkan kendaraan Rental!");
                if(!IsAHelicopter(PlayerVehicle[carid][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat memasukkan Helicopter!");

                Vehicle_GetStatus(carid);
                PlayerVehicle[carid][pVehHelipadGarage] = hpid;

                found = true;

                if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                {
                    DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                    SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                    PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                }
            }
            if(!found) return false;
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_HOUSEVAULT:
        {
            new id = House_Inside(playerid);
            if(id == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat brankas rumah!");
            }

            if(!response)
            {
                if(HouseData[id][hsType] > 3) 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik\
                    \nPemegang Kunci", id, GetLocation(HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[id][hsOwner]),
                    shstr, "Pilih", "Batal");
                } 
                else 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik", id, GetLocation(HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[id][hsOwner]),
                    shstr, "Pilih", "Batal");             
                }
                AccountData[playerid][menuShowed] = false;
                return 1;
            }

            switch(listitem)
            {
                case 0: //deposit
                {
                    HouseBrankas[playerid][housebrankasID] = 0;
                    HouseBrankas[playerid][housebrankasTemp] = EOS;
                    HouseBrankas[playerid][housebrankasModel] = 0;
                    HouseBrankas[playerid][housebrankasQuant] = 0;

                    new str[1218], amounts, itemname[64], tss[128], frmtcapacity[125];
                    if(HouseData[id][hsType] == 1) {
                        frmtcapacity = "450 kg";
                    } else if(HouseData[id][hsType] == 2) {
                        frmtcapacity = "500 kg";
                    } else if(HouseData[id][hsType] == 3) {
                        frmtcapacity = "700 kg";
                    }

                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/%s)\n", HouseData[id][houseMaxCapacity], frmtcapacity);
                    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
                    mysql_query(g_SQL, tss);
                    new rows = cache_num_rows();
                    if(rows)
                    {
                        for(new x; x < rows; ++x)
                        {
                            cache_get_value_name(x, "invItem", itemname);
                            cache_get_value_name_int(x, "invQuantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""City"Happy Roleplay "WHITE"- Brankas Rumah", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Brankas Rumah",
                        "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                    }
                }
                case 1: //withdraw
                {
                    new str[1218], amounts, itemname[64], tss[128], frmtcapacity[125];
                    if(HouseData[id][hsType] == 1) {
                        frmtcapacity = "450 kg";
                    } else if(HouseData[id][hsType] == 2) {
                        frmtcapacity = "500 kg";
                    } else if(HouseData[id][hsType] == 3) {
                        frmtcapacity = "700 kg";
                    }

                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/%s)\n", HouseData[id][houseMaxCapacity], frmtcapacity);
                    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `player_housestorage` WHERE `ID`=%d", AccountData[playerid][pID]);
                    mysql_query(g_SQL, tss);
                    if(cache_num_rows())
                    {
                        for(new x; x < cache_num_rows(); ++x)
                        {
                            cache_get_value_name(x, "hsItemName", itemname);
                            cache_get_value_name_int(x, "hsItemQuantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""City"Happy Roleplay "WHITE"- Brankas Rumah", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Brankas Rumah",
                        "Tidak ada barang di brankas saat ini!", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_HOUSEVAULT_DEPOSIT:
        {
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            if(listitem == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
            }

            new tss[128];
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
            mysql_query(g_SQL, tss);
            if(cache_num_rows() > 0)
            {
                cache_get_value_name(listitem, "invItem", HouseBrankas[playerid][housebrankasTemp]);
                cache_get_value_name_int(listitem, "invModel", HouseBrankas[playerid][housebrankasModel]);
                cache_get_value_name_int(listitem, "invQuantity", HouseBrankas[playerid][housebrankasQuant]);

                new shstr[528];
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan berapa jumlah item yang ingin disimpan:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_IN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Rumah", 
                shstr, "Input", "Batal");
            }
        }
        case DIALOG_HOUSEVAULT_IN:
        {
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nError: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin disimpan:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_IN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Rumah", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nError: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_IN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Rumah", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > HouseBrankas[playerid][housebrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nError: Jumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_IN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Rumah", 
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            if(HouseData[AccountData[playerid][pInHouse]][hsType] == 1) if(HouseData[AccountData[playerid][pInHouse]][houseMaxCapacity] >= 450.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Penyimpanan brankas telah penuh!"), AccountData[playerid][menuShowed] = false;
            if(HouseData[AccountData[playerid][pInHouse]][hsType] == 2) if(HouseData[AccountData[playerid][pInHouse]][houseMaxCapacity] >= 500.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Penyimpanan brankas telah penuh!"), AccountData[playerid][menuShowed] = false;
            if(HouseData[AccountData[playerid][pInHouse]][hsType] == 3) if(HouseData[AccountData[playerid][pInHouse]][houseMaxCapacity] >= 700.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Penyimpanan brankas telah penuh!"), AccountData[playerid][menuShowed] = false;

            Inventory_Remove(playerid, HouseBrankas[playerid][housebrankasTemp], quantity);
            ShowItemBox(playerid, sprintf("Removed %dx", quantity), HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasModel]);
            if(HouseData[AccountData[playerid][pInHouse]][hsType] != 4) AddCapacityHouse(AccountData[playerid][pInHouse], HouseBrankas[playerid][housebrankasTemp], quantity);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `player_housestorage` WHERE `ID`=%d AND `hsItemName`='%s'", AccountData[playerid][pID], HouseBrankas[playerid][housebrankasTemp]);
            mysql_query(g_SQL, shstr);
            if(cache_num_rows() > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `player_housestorage` SET `hsItemQuantity` = `hsItemQuantity` + %d WHERE `ID` = %d AND `hsItemName` = '%s'", quantity, AccountData[playerid][pID], HouseBrankas[playerid][housebrankasTemp]);
                mysql_tquery(g_SQL, invstr, "OnHouseDeposit", "d", playerid);
            }
            else 
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `player_housestorage` SET `ID`=%d, `hsItemName`='%s', `hsItemModel`=%d, `hsItemQuantity`=%d", AccountData[playerid][pID], HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasModel], quantity);
                mysql_tquery(g_SQL, invstr, "OnHouseDeposit", "d", playerid);
            }
        }
        case DIALOG_HOUSEVAULT_WITHDRAW:
        {
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            if(listitem == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
            }

            new shstr[596], tss[128];
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `player_housestorage` WHERE `ID`=%d", AccountData[playerid][pID]);
            mysql_query(g_SQL, tss);
            if(cache_num_rows())
            {
                cache_get_value_name_int(listitem, "hsItemID", HouseBrankas[playerid][housebrankasID]);
                cache_get_value_name(listitem, "hsItemName", HouseBrankas[playerid][housebrankasTemp]);
                cache_get_value_name_int(listitem, "hsItemModel", HouseBrankas[playerid][housebrankasModel]);
                cache_get_value_name_int(listitem, "hsItemQuantity", HouseBrankas[playerid][housebrankasQuant]);

                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_OUT, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
            }
        }
        case DIALOG_HOUSEVAULT_OUT:
        {
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nError: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin anda ambil:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_OUT, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Rumah", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nError: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_OUT, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Rumah", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > HouseBrankas[playerid][housebrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nError: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT_OUT, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Brankas Rumah", 
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext), jts[255];

            if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventiry anda telah penuh!"), AccountData[playerid][menuShowed] = false;

            HouseBrankas[playerid][housebrankasQuant] -= quantity;
            if(HouseBrankas[playerid][housebrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `player_housestorage` SET `hsItemQuantity`= %d WHERE `hsItemID`=%d", HouseBrankas[playerid][housebrankasQuant], HouseBrankas[playerid][housebrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            else 
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `player_housestorage` WHERE `hsItemID`=%d", HouseBrankas[playerid][housebrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            Inventory_Add(playerid, HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasModel], quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), HouseBrankas[playerid][housebrankasTemp], HouseBrankas[playerid][housebrankasModel]);
            if(HouseData[AccountData[playerid][pInHouse]][hsType] != 4) ReduceCapacityHouse(AccountData[playerid][pInHouse], HouseBrankas[playerid][housebrankasTemp], quantity);

            HouseBrankas[playerid][housebrankasID] = 0;
            HouseBrankas[playerid][housebrankasTemp] = EOS;
            HouseBrankas[playerid][housebrankasModel] = 0;
            HouseBrankas[playerid][housebrankasQuant] = 0;
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_HOUSE_BRANKAS:
        {
            if(!response) return 1;

            if(AccountData[playerid][pInHouse] == -1)
            {
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rumah!");
            }

            new id = House_Inside(playerid);
            if(id == -1) return 0;
            switch(listitem)
            {
                case 2:
                {
                    new frmxt[158], count = 0;

                    foreach(new i : Player) if (i != playerid) if (IsPlayerInRangeOfPoint(i, 1.5, HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]))
                    {
                        format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
                        NearestPlayer[playerid][count++] = i;
                    }

                    if(count == 0)
                    {
                        PlayerPlaySound(playerid, 5206, 0, 0, 0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Undang Teman", 
                        "Tidak ada player yang berada dekat dengan pintu rumah anda!", "Tutup", "");
                    }

                    ShowPlayerDialog(playerid, DIALOG_HOUSE_INVITE, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Undang Teman", frmxt, "Undang", "Batal");
                }
                case 3:
                {
                    if(!House_HaveAccess(playerid, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya pemilik rumah dan pemegang kunci yang dapat mengakses!");
                    ShowPlayerClothes(playerid);
                }
                case 4:
                {
                    if(!House_HaveAccess(playerid, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya pemilik rumah dan pemegang kunci yang dapat mengakses!");
                    DropClothesPlayer(playerid);
                }
                case 5:
                {
                    if(!House_HaveAccess(playerid, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya pemilik rumah dan pemegang kunci yang dapat mengakses!");
                    ShowHouseWeapons(playerid, id);
                }
                case 6:
                {
                    if(!House_HaveAccess(playerid, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya pemilik rumah dan pemegang kunci yang dapat mengakses!");
                    ShowPlayerDialog(playerid, DIALOG_HOUSEVAULT, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Brankas Rumah",
                    "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
                    AccountData[playerid][menuShowed] = true;
                }
                case 7:// Putar Musik
                {
                    Dialog_Show(playerid, DialogHouseMusik, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- House Musik",
                    "House Musik - Cerahi hidupmu secerah matahari di pagi hari\
                    \nKami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\
                    \n"RED"NOTE: Fitur ini tidak support link dari Youtube secara langsung!\
                    \n"YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste dibawah ini):", "Input", "Cancel");
                }
                case 8: // Pemegang Kunci
                {
                    if(!House_IsOwner(playerid, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pemilik rumah!");
                    new query[255];
                    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_characters` WHERE `Char_FriendHouse`= '%d'", id);
                    mysql_tquery(g_SQL, query, "LoadKeysList", "d", playerid);
                }
            }
        }
        case DIALOG_WEAPON_CHEST:
        {
            new hid = AccountData[playerid][pInHouse];
            if(!House_HaveAccess(playerid, hid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya pemilik rumah dan pemegang kunci yang dapat mengakses!");
            
            if(!response) 
            {
                if(HouseData[hid][hsType] > 3) 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik\
                    \nPemegang Kunci", hid, GetLocation(HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[hid][hsOwner]),
                    shstr, "Pilih", "Batal");
                } 
                else 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik", hid, GetLocation(HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[hid][hsOwner]),
                    shstr, "Pilih", "Batal");             
                }
                return 1;
            }

            if(HouseData[hid][hsWeapon][listitem] != 0)
            {
                GivePlayerWeaponEx(playerid, HouseData[hid][hsWeapon][listitem], HouseData[hid][hsAmmo][listitem]);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda mengambil %s dari chest!", ReturnWeaponName(HouseData[hid][hsWeapon][listitem])));
                HouseData[hid][hsWeapon][listitem] = 0;
                HouseData[hid][hsAmmo][listitem] = 0;

                HouseSave(hid);
                ShowHouseWeapons(playerid, hid);
            }
            else 
            {
                new 
                    weaponid = GetPlayerWeapon(playerid),
                    ammo = GetPlayerAmmo(playerid);
                
                if(!weaponid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memegang senjata apapun/slot chest tersebut kosong!");

                ResetWeapon(playerid, weaponid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda menyimpan %s ke dalam chest!", ReturnWeaponName(weaponid)));

                HouseData[hid][hsWeapon][listitem] = weaponid;
                HouseData[hid][hsAmmo][listitem] = ammo;

                HouseSave(hid);
                ShowHouseWeapons(playerid, hid);
            }
        }
        case DIALOG_HOUSE_INVITE:
        {
            if(!response)
            {
                if(HouseData[AccountData[playerid][pInHouse]][hsType] > 3) 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik\
                    \nPemegang Kunci", AccountData[playerid][pInHouse], GetLocation(HouseData[AccountData[playerid][pInHouse]][hsExtPos][0], HouseData[AccountData[playerid][pInHouse]][hsExtPos][1], HouseData[AccountData[playerid][pInHouse]][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hsOwner]),
                    shstr, "Pilih", "Batal");
                } 
                else 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik", AccountData[playerid][pInHouse], GetLocation(HouseData[AccountData[playerid][pInHouse]][hsExtPos][0], HouseData[AccountData[playerid][pInHouse]][hsExtPos][1], HouseData[AccountData[playerid][pInHouse]][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hsOwner]),
                    shstr, "Pilih", "Batal");             
                }
                return 1;
            }

            if(listitem == -1)
            {
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih pemain untuk diundang!");
            }

            new targetid = NearestPlayer[playerid][listitem];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            
            AccountData[targetid][pInviteAccept] = AccountData[playerid][pInHouse];
            ShowPlayerDialog(targetid, DIALOG_HOUSE_INVITECONF, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Undang Teman", 
            "Pemilik rumah mengundang anda untuk masuk ke dalam rumahnya", "Iya", "Tidak");
        }
        case DIALOG_HOUSE_INVITECONF:
        {
            if(!response) return 1;
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            AccountData[playerid][ActivityTime] = 1;
            pTimerMasukRumah[playerid] = SetTimerEx("MasukRumahAccept", 800, true, "dd", playerid, AccountData[playerid][pInviteAccept]);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "MASUK");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
        }
        case DIALOG_HOUSEGARAGE_OUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = ReturnAnyVehicleHoused(playerid, listitem, AccountData[playerid][pPark]);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            // if(!IsPlayerInRangeOfPoint(playerid, 2.0, HouseData[AccountData[playerid][pPark]][housegaragePos][0], HouseData[AccountData[playerid][pPark]][housegaragePos][1], HouseData[AccountData[playerid][pPark]][housegaragePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat Garasi Rumah!");
            if(!IsPlayerInDynamicArea(playerid, HouseData[AccountData[playerid][pPark]][housegarageArea])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat Garasi Rumah!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
			PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehHelipadGarage] = -1;
			PlayerVehicle[id][pVehFamiliesGarage] = -1;
			PlayerVehicle[id][pVehFactStored] = -1;

            PlayerVehicle[id][pVehWorld] = GetPlayerVirtualWorld(playerid);
            PlayerVehicle[id][pVehInterior] = GetPlayerInterior(playerid);

            if(PlayerVehicle[id][pVehLocked])
				PlayerVehicle[id][pVehLocked] = false;

			PlayerVehicle[id][pVehPos][0] = HouseData[AccountData[playerid][pPark]][housegarageSpawnPos][0];
			PlayerVehicle[id][pVehPos][1] = HouseData[AccountData[playerid][pPark]][housegarageSpawnPos][1];
			PlayerVehicle[id][pVehPos][2] = HouseData[AccountData[playerid][pPark]][housegarageSpawnPos][2];
			PlayerVehicle[id][pVehPos][3] = HouseData[AccountData[playerid][pPark]][housegarageSpawnPos][3];

            PlayerVehicle[id][pVehFuel] = PlayerVehicle[id][pVehFuel];
            PlayerVehicle[id][pVehHealth] = PlayerVehicle[id][pVehHealth];

			OnPlayerVehicleRespawn(id);

            AccountData[playerid][pPark] = -1;
			SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_HOUSEHELIPAD_OUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = ReturnAnyVehicleHelipad(playerid, listitem, AccountData[playerid][pPark]);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            if(!IsPlayerInRangeOfPoint(playerid, 2.0, HouseData[AccountData[playerid][pPark]][househelipadPos][0], HouseData[AccountData[playerid][pPark]][househelipadPos][1], HouseData[AccountData[playerid][pPark]][househelipadPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat Garasi Rumah!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
			PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehHelipadGarage] = -1;
			PlayerVehicle[id][pVehFamiliesGarage] = -1;
			PlayerVehicle[id][pVehFactStored] = -1;

            PlayerVehicle[id][pVehWorld] = GetPlayerVirtualWorld(playerid);
            PlayerVehicle[id][pVehInterior] = GetPlayerInterior(playerid);

            if(PlayerVehicle[id][pVehLocked])
				PlayerVehicle[id][pVehLocked] = false;

			PlayerVehicle[id][pVehPos][0] = HouseData[AccountData[playerid][pPark]][househelipadSpawnPos][0];
			PlayerVehicle[id][pVehPos][1] = HouseData[AccountData[playerid][pPark]][househelipadSpawnPos][1];
			PlayerVehicle[id][pVehPos][2] = HouseData[AccountData[playerid][pPark]][househelipadSpawnPos][2];
			PlayerVehicle[id][pVehPos][3] = HouseData[AccountData[playerid][pPark]][househelipadSpawnPos][3];

			OnPlayerVehicleRespawn(id);

            AccountData[playerid][pPark] = -1;
			SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_HKEYS:
        {
            new houseid = House_Inside(playerid);
            if(houseid == -1) return 0;

            if(!response) 
            {
                if(HouseData[houseid][hsType] > 3) 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik\
                    \nPemegang Kunci", houseid, GetLocation(HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[houseid][hsOwner]),
                    shstr, "Pilih", "Batal");
                } 
                else 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik", houseid, GetLocation(HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[houseid][hsOwner]),
                    shstr, "Pilih", "Batal");             
                }
                return 1;
            }

            if(HouseMemberName[playerid][listitem][0] == EOS) return ShowPlayerDialog(playerid, DIALOG_HKEYS_ADD, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Bagikan Kunci",
            "Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Input", "Kembali");

            static shstr[255];
            format(shstr, sizeof(shstr), "Apakah anda yakin ingin menarik kunci dari %s?", HouseMemberName[playerid][listitem]);
            ShowPlayerDialog(playerid, DIALOG_HKEYS_REMOVE, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay"WHITE"- Pemegang Kunci", shstr, "Iya", "Tidak");
            SetPVarString(playerid, "RemoveKeysName", HouseMemberName[playerid][listitem]);
        }
        case DIALOG_HKEYS_REMOVE:
        {
            new playerName[64], playerNameOnline[64];
            GetPVarString(playerid, "RemoveKeysName", playerName, MAX_PLAYER_NAME);
            if(!response) 
            {
                new query[255];
                mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_Name` FROM `player_characters` WHERE `Char_FriendHouse`=%d", AccountData[playerid][pInHouse]);
                mysql_tquery(g_SQL, query, "LoadKeysList", "d", playerid);
                return 1;
            }

            foreach(new i : Player) if (IsPlayerConnected(i))
            {
                GetPlayerName(i, playerNameOnline, MAX_PLAYER_NAME);

                if(strfind(playerNameOnline, playerName, true) != -1)
                {
                    AccountData[i][pFriendHouseID] = -1;
                    new query[256];
                    mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_FriendHouse`=-1 WHERE `Char_Name`= '%e'", playerName);
                    mysql_tquery(g_SQL, query);
                }
            }
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda menarik kunci rumah dari %s", playerName));
            new query[256];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_FriendHouse`=-1 WHERE `Char_Name`= '%s'", playerName);
            mysql_tquery(g_SQL, query);
        }
        case DIALOG_HKEYS_ADD:
        {
            new id = House_Inside(playerid);
            if(!response)
            {
                if(HouseData[id][hsType] > 3) 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik\
                    \nPemegang Kunci", id, GetLocation(HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[id][hsOwner]),
                    shstr, "Pilih", "Batal");
                } 
                else 
                {
                    new shstr[596];
                    format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
                    \n"GRAY"Alamat Rumah: "YELLOW"%s\
                    \n\
                    \nUndang Teman\
                    \n"GRAY"Lemari Pakaian\
                    \nMembuang Pakaian\
                    \n"GRAY"Weapon Chest\
                    \nBrankas\
                    \n"GRAY"Musik", id, GetLocation(HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]));
                    ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[id][hsOwner]),
                    shstr, "Pilih", "Batal");             
                }
                return 1;
            }

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_HKEYS_ADD, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Bagikan Kunci",
            "Error: Tidak dapat diisi kosong!\nMohon masukkan playerid yang ingin diberikan kunci rumah:", "Input", "Kembali");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_HKEYS_ADD, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Bagikan Kunci",
            "Error: Hanya dapat diisi angka!\nMohon masukkan playerid yang ingin diberikan kunci rumah:", "Input", "Kembali");
            
            new targetid = strval(inputtext);
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(targetid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda adalah pemilik rumah, tidak dapat ditambahkan!");
            if(!IsPlayerNearPlayer(playerid, targetid, 5.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada didekat anda!");
            foreach(new i : Player) if (IsPlayerConnected(i))
            {
                if(i == targetid)
                {
                    AccountData[i][pFriendHouseID] = id;
                    SendClientMessageEx(i, -1, "[i] %s Memberikan anda kunci rumahnya", AccountData[playerid][pName]);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda membagikan kunci rumah kepada %s.", ReturnName(i)));

                    new query[255];
                    mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_FriendHouse` = %d WHERE `pID` = %d", id, AccountData[i][pID]);
                    mysql_tquery(g_SQL, query);
                }
            }
        }
    }
    return 1;
}

Dialog:DialogHouseMusik(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        if(HouseData[AccountData[playerid][pInHouse]][hsType] > 3) 
        {
            new shstr[596];
            format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
            \n"GRAY"Alamat Rumah: "YELLOW"%s\
            \n\
            \nUndang Teman\
            \n"GRAY"Lemari Pakaian\
            \nMembuang Pakaian\
            \n"GRAY"Weapon Chest\
            \nBrankas\
            \n"GRAY"Musik\
            \nPemegang Kunci", AccountData[playerid][pInHouse], GetLocation(HouseData[AccountData[playerid][pInHouse]][hsExtPos][0], HouseData[AccountData[playerid][pInHouse]][hsExtPos][1], HouseData[AccountData[playerid][pInHouse]][hsExtPos][2]));
            ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hsOwner]),
            shstr, "Pilih", "Batal");
        } 
        else 
        {
            new shstr[596];
            format(shstr, sizeof(shstr), "House ID: "YELLOW"%d\
            \n"GRAY"Alamat Rumah: "YELLOW"%s\
            \n\
            \nUndang Teman\
            \n"GRAY"Lemari Pakaian\
            \nMembuang Pakaian\
            \n"GRAY"Weapon Chest\
            \nBrankas\
            \n"GRAY"Musik", AccountData[playerid][pInHouse], GetLocation(HouseData[AccountData[playerid][pInHouse]][hsExtPos][0], HouseData[AccountData[playerid][pInHouse]][hsExtPos][1], HouseData[AccountData[playerid][pInHouse]][hsExtPos][2]));
            ShowPlayerDialog(playerid, DIALOG_HOUSE_BRANKAS, DIALOG_STYLE_LIST, sprintf(""City"Happy Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hsOwner]),
            shstr, "Pilih", "Batal");             
        }
        return 1;
    }

    if(isnull(inputtext))
    {
        static jskc[512];
        format(jskc, sizeof(jskc), ""VERONA_ARWIN"House Music - Cerahi Hidupmu Secerah Matahari Di Pagi Hari\nError: Tidak dapat diisi kosong!\n"VERONA_ARWIN"Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n"RED_E"Note: Fitur ini tidak support link Youtube secara langsung!\n\n"YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste dibawah ini):");
        Dialog_Show(playerid, DialogHouseMusik, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- House Musik", jskc, "Input", "Cancel");
        return 1;
    }

    if(strlen(inputtext) < 1 || strlen(inputtext) > 128)
    {
        static jskc[512];
        format(jskc, sizeof(jskc), ""VERONA_ARWIN"House Music - Cerahi Hidupmu Secerah Matahari Di Pagi Hari\n\n"VERONA_ARWIN"Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n"RED_E"Note: Fitur ini tidak support link Youtube secara langsung!\n\n"YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste dibawah ini):");
        Dialog_Show(playerid, DialogHouseMusik, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- House Musik", jskc, "Input", "Cancel");
        return 1;
    }

    PlayHouseAudioInHouse(playerid, inputtext);
    return 1;
}

CMD:klaimrumah(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    new id = House_Nearest(playerid);
    if(id != -1)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]))
        {
            if(AccountData[playerid][pOwnedHouse] > -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki rumah!");
            if(HouseData[id][hsClaimed] != 1)
            {
                HouseData[id][hsOwnerID] = AccountData[playerid][pID];
                HouseData[id][hsClaimed] = 1;
                AccountData[playerid][pOwnedHouse] = id;
                GetPlayerName(playerid, HouseData[id][hsOwner], MAX_PLAYER_NAME);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil mengklaim rumah Type %s", GetTypeHouseName(id)));

                HouseRefresh(id);
                HouseSave(id);
            }
            else ShowTDN(playerid, NOTIFICATION_ERROR, "Rumah ini sudah diklaim/expired!");
        }
    }
    return 1;
}

forward MasukRumahAccept(playerid, houseid);
public MasukRumahAccept(playerid, houseid)
{
    if(houseid == -1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2]))
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 4)
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);    

        Player_ToggleTelportAntiCheat(playerid, false);
        SetPlayerPositionEx(playerid, HouseData[houseid][hsIntPos][0], HouseData[houseid][hsIntPos][1], HouseData[houseid][hsIntPos][2], HouseData[houseid][hsIntPos][3], 6000);
        SetPlayerInterior(playerid, HouseData[houseid][hsInt]);
        SetPlayerVirtualWorld(playerid, houseid);
        AccountData[playerid][pInHouse] = houseid;
        if(HouseData[houseid][hsAudio])
        {
            PlayHouseAudio(playerid, houseid);
        }
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue; 
        progressvalue = AccountData[playerid][ActivityTime]*103/4;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward MasukRumah(playerid, houseid);
public MasukRumah(playerid, houseid)
{
    if(houseid == -1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 1.5, HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2]))
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 4)
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);    

        Player_ToggleTelportAntiCheat(playerid, false);
        SetPlayerPositionEx(playerid, HouseData[houseid][hsIntPos][0], HouseData[houseid][hsIntPos][1], HouseData[houseid][hsIntPos][2], HouseData[houseid][hsIntPos][3], 6000);
        SetPlayerInterior(playerid, HouseData[houseid][hsInt]);
        SetPlayerVirtualWorld(playerid, houseid);
        AccountData[playerid][pInHouse] = houseid;

        if(HouseData[houseid][hsAudio])
        {
            PlayHouseAudio(playerid, houseid);
        }
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue; 
        progressvalue = AccountData[playerid][ActivityTime]*103/4;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

forward KeluarRumah(playerid, houseid);
public KeluarRumah(playerid, houseid)
{
    if(houseid == -1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 4)
    {
        KillTimer(pTimerMasukRumah[playerid]);
        pTimerMasukRumah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        AccountData[playerid][pInHouse] = -1;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Player_ToggleTelportAntiCheat(playerid, false);
        SetPlayerPositionEx(playerid, HouseData[houseid][hsExtPos][0], HouseData[houseid][hsExtPos][1], HouseData[houseid][hsExtPos][2], HouseData[houseid][hsExtPos][3], 6000);
        
        SetPlayerInterior(playerid, 0);
        SetPlayerVirtualWorld(playerid, 0);
        SetCameraBehindPlayer(playerid);
        SetPlayerWeather(playerid, WorldWeather);
        Player_ToggleTelportAntiCheat(playerid, true);

        if(AccountData[playerid][hsAudioPlay]) {
            StopAudioStreamForPlayer(playerid);
            AccountData[playerid][hsAudioPlay] = 0;
        }
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*103/4;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][2], progressvalue, 21.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
        return 0;
    }
    return 1;
}

AddCapacityHouse(houseid, const item[], quantity)
{
    if(!strcmp(item, "Nasi Goreng"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kopi Kenangan"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Batu Kotor"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.030;
    }
    else if(!strcmp(item, "Nasi Uduk"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kanabis"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Batu Bersih"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.030;
    }
    else if(!strcmp(item, "Air Mineral"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Besi"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Tembaga"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Berlian"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Emas"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Smartphone"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Radio"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.15;
    }
    else if(!strcmp(item, "Kayu"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.06;
    }
    else if(!strcmp(item, "Kayu Potongan"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Kayu Kemas"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.08;
    }
    else if(!strcmp(item, "Marijuana"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Benang"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kain"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Pakaian"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Bandage"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Medkit"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Alprazolam"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Ayam Hidup"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.15;
    }
    else if(!strcmp(item, "Ayam Potong"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Ayam Kemas"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Sampah Makanan"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Kevlar"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.90;
    }
    else if(!strcmp(item, "Botol"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Petrol"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "Pure Oil"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "GAS"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.60;
    }
    else if(!strcmp(item, "Ikan"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Rokok"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Pancingan"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.08;
    }
    else if(!strcmp(item, "Umpan"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Hiu"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.90;
    }
    else if(!strcmp(item, "Penyu"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.80;
    }
    else if(!strcmp(item, "Ikan Tawar"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.03;
    }
    else if(!strcmp(item, "Jerigen"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Tools Kit"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.30;
    }
    else if(!strcmp(item, "Repair Kit"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.35;
    }
    else if(!strcmp(item, "Linggis"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Kunci T"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Nasi Pecel"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bubur Pedas"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Es Teh"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Jus Apel"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Boombox"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.20;
    }
    else if(!strcmp(item, "Kebab A5"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bakso"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Choco Matcha"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Teh Jeruk"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Susu Murni"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Susu Olahan"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Susu Fresh"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Cabe"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Padi"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Garam Kristal"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.006;
    }
    else if(!strcmp(item, "Tebu"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Beras"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Sambal"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Gula"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Garam"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Daging"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Tanduk"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.03;
    }
    else if(!strcmp(item, "Kulit"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bulu"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Boxmats"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Baja"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Material"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.025;
    }
    else if(!strcmp(item, "Kaca"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Karet"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.006;
    }
    else if(!strcmp(item, "Plastik"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Alumunium"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Backpack"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "Masker"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Plat Besi"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.025;
    }
    else if(!strcmp(item, "Korek Api"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Bibit Padi"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Tebu"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Cabe"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Pilox"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Uranium ACD"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.020;
    }
    else if(!strcmp(item, "Uranium"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Senter"))
    {
        HouseData[houseid][houseMaxCapacity] += quantity*0.006;
    }
    HouseSave(houseid);
    return 1;
}

ReduceCapacityHouse(houseid, const item[], quantity)
{
    if(!strcmp(item, "Nasi Goreng"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kopi Kenangan"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Batu Kotor"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.030;
    }
    else if(!strcmp(item, "Nasi Uduk"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kanabis"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Batu Bersih"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.030;
    }
    else if(!strcmp(item, "Air Mineral"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Besi"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Tembaga"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Berlian"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Emas"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Smartphone"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Radio"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.15;
    }
    else if(!strcmp(item, "Kayu"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.06;
    }
    else if(!strcmp(item, "Kayu Potongan"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Kayu Kemas"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.08;
    }
    else if(!strcmp(item, "Marijuana"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Benang"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kain"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Pakaian"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Bandage"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Medkit"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Alprazolam"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Ayam Hidup"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.15;
    }
    else if(!strcmp(item, "Ayam Potong"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Ayam Kemas"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Sampah Makanan"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Kevlar"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.90;
    }
    else if(!strcmp(item, "Botol"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Petrol"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "Pure Oil"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "GAS"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.60;
    }
    else if(!strcmp(item, "Ikan"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Rokok"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Pancingan"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.08;
    }
    else if(!strcmp(item, "Umpan"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Hiu"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.90;
    }
    else if(!strcmp(item, "Penyu"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.80;
    }
    else if(!strcmp(item, "Ikan Tawar"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.03;
    }
    else if(!strcmp(item, "Jerigen"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Tools Kit"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.30;
    }
    else if(!strcmp(item, "Repair Kit"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.35;
    }
    else if(!strcmp(item, "Linggis"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Kunci T"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Nasi Pecel"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bubur Pedas"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Es Teh"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Jus Apel"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Boombox"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.20;
    }
    else if(!strcmp(item, "Kebab A5"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bakso"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Choco Matcha"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Teh Jeruk"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Susu Murni"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Susu Olahan"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Susu Fresh"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Cabe"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Padi"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Garam Kristal"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.006;
    }
    else if(!strcmp(item, "Tebu"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Beras"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Sambal"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Gula"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Garam"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Daging"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Tanduk"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.03;
    }
    else if(!strcmp(item, "Kulit"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bulu"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Boxmats"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Baja"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Material"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.025;
    }
    else if(!strcmp(item, "Kaca"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Karet"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.006;
    }
    else if(!strcmp(item, "Plastik"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Alumunium"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Backpack"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "Masker"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Plat Besi"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.025;
    }
    else if(!strcmp(item, "Korek Api"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Bibit Padi"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Tebu"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Cabe"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Pilox"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Uranium ACD"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.020;
    }
    else if(!strcmp(item, "Uranium"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Senter"))
    {
        HouseData[houseid][houseMaxCapacity] -= quantity*0.006;
    }
    if(HouseData[houseid][houseMaxCapacity] < 0) {
        HouseData[houseid][houseMaxCapacity] = 0;
    }

    HouseSave(houseid);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    pTimerMasukRumah[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerMasukRumah[playerid]);
    pTimerMasukRumah[playerid] = -1;
    return 1;
}