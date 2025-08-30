#include <YSI_Coding\y_hooks>

new bool: DurringRefill[MAX_PLAYERS] = {false, ...};
new pTimerRefill[MAX_PLAYERS] = {-1, ...};
new RefillPrice[MAX_PLAYERS] = {0, ...};
new STREAMER_TAG_3D_TEXT_LABEL:pomLabel[MAX_PLAYERS][140];
new STREAMER_TAG_3D_TEXT_LABEL:RefillLabel[MAX_PLAYERS];

static Float:RefillArea[140][3] = 
{
    {1379.3347, 459.6162, 19.9777},
    {1380.3101, 461.7066, 20.0718},
    {1384.7469, 459.7309, 20.0737},
    {1383.7095, 457.6685, 19.9849},

    {1009.4893, -937.3367, 42.1797},
    {1009.1791, -934.7787, 42.1797},
    {1005.6673, -935.2690, 42.1797},
    {1005.9335, -937.8239, 42.1797},
    {1002.1943, -938.3406, 42.1797},
    {1001.9116, -935.7847, 42.1797},
    {998.4645, -936.2556, 42.1797},
    {998.7998, -938.8237, 42.1797},

    {-1611.3740, -2722.0090, 48.5391},
    {-1609.9081, -2719.9377, 48.5391},
    {-1608.0846, -2717.6262, 48.5391},
    {-1606.6044, -2715.5688, 48.5391},
    {-1604.7007, -2713.2839, 48.5335},
    {-1603.2515, -2711.1956, 48.5335},
    {-1601.3973, -2708.9238, 48.5391},
    {-1599.9268, -2706.7866, 48.5391},
    {-2240.5552, -2562.8757, 31.9219},
    {-2242.7939, -2561.6533, 31.9219},
    {-2245.5547, -2560.2996, 31.9219},
    {-2247.8481, -2559.0979, 31.9219},    

    {-92.9854, -1161.2942, 2.2030},
    {-90.9183, -1162.3363, 2.2478},
    {-86.5004, -1164.4913, 2.2450},
    {-84.2754, -1165.4738, 2.2393},
    {-89.2178, -1177.1200, 2.1218},
    {-91.3930, -1175.9028, 2.1996},
    {-95.9691, -1174.3303, 2.3270},
    {-98.0782, -1173.2810, 2.3977},
    
    {654.2443, -570.3237, 16.3359},
    {657.0209, -570.3949, 16.3359},
    {657.0211, -559.7999, 16.3359},
    {654.2224, -559.7070, 16.3359}, 

    {1942.7666, -1778.4630, 13.3906},
    {1942.8177, -1774.3499, 13.3906},
    {1942.7950, -1771.3076, 13.3906},
    {1942.6736, -1767.2361, 13.3906},
    {1940.3669, -1767.2260, 13.3828},
    {1940.3251, -1771.2075, 13.3906},
    {1940.2731, -1774.4557, 13.3906},
    {1940.2289, -1778.5177, 13.3906}, 

    {54.9892, -300.6185, 1.6272},
    {53.0321, -300.6405, 1.6765},
    {53.0324, -298.3067, 1.6765},
    {54.9885, -298.2956, 1.6273},

    {2109.1577, 913.6782, 10.8203},
    {2109.1038, 915.6482, 10.8203},
    {2114.8672, 915.7737, 10.8203},
    {2114.9031, 913.6741, 10.8203},
    {2120.7678, 913.6027, 10.8203},
    {2120.8201, 915.8837, 10.8203},
    {2120.7791, 924.3390, 10.8203},
    {2120.7827, 926.5418, 10.8203},
    {2114.8367, 926.7383, 10.8203},
    {2115.0212, 924.4167, 10.8203},
    {2108.9326, 924.5459, 10.8203},
    {2109.0078, 926.4336, 10.8203},

    {1601.9888, 2194.6638, 10.8203},
    {1602.0625, 2192.6497, 10.8203},
    {1596.1560, 2192.7461, 10.8203},
    {1596.1055, 2194.6082, 10.8203},
    {1590.4354, 2194.6221, 10.8203},
    {1590.3419, 2192.6001, 10.8203},
    {1590.3776, 2203.5720, 10.8203},
    {1590.3302, 2205.3357, 10.8203},
    {1596.1454, 2205.3269, 10.8203},
    {1596.1533, 2203.4749, 10.8203},
    {1601.9685, 2203.4272, 10.8203},
    {1601.9036, 2205.3643, 10.8203},

    {624.5205, 1676.9932, 6.9922},
    {623.3845, 1678.5353, 6.9922},
    {621.1226, 1681.7411, 6.9922},
    {620.0032, 1683.1333, 6.9922},
    {617.5823, 1686.8186, 6.9922},
    {616.5840, 1688.1630, 6.9922},
    {614.2996, 1691.5265, 6.9922},
    {612.9919, 1693.1340, 6.9922},
    {610.9586, 1696.4761, 6.9922},
    {609.6895, 1698.0280, 6.9922},
    {607.4445, 1701.5067, 6.9922},
    {606.2874, 1703.0111, 6.9995},
    {604.0156, 1706.5691, 6.9922},
    {603.0014, 1707.8643, 6.9922},

    {-1329.2285, 2668.4670, 50.0625},
    {-1329.1315, 2670.0986, 50.0625},
    {-1328.7433, 2673.9514, 50.0625},
    {-1328.5145, 2675.5149, 50.0625},
    {-1327.9497, 2679.2866, 50.0625},
    {-1327.7405, 2680.9238, 50.0625},
    {-1327.1564, 2684.7676, 50.0625},
    {-1327.0731, 2686.4170, 50.0625},

    {-2412.7778, 970.8113, 45.2969},
    {-2409.3625, 970.9482, 45.3016},
    {-2409.2021, 976.2747, 45.2969},
    {-2412.4475, 976.1577, 45.2969},
    {-2412.5857, 981.5041, 45.2969},
    {-2409.3110, 981.5568, 45.2969},

    {-1464.8589, 1859.6145, 32.6328},
    {-1465.0861, 1861.4481, 32.6398},
    {-1465.3000, 1867.4950, 32.6328},
    {-1465.4963, 1869.1262, 32.6328},
    {-1477.9500, 1868.4729, 32.6398},
    {-1477.8525, 1866.2003, 32.6398},
    {-1477.7329, 1860.5038, 32.6328},
    {-1477.6095, 1858.6425, 32.6398},

    {72.4317, 1219.6854, 18.8182},
    {75.1066, 1219.0424, 18.8219},
    {73.9821, 1215.3553, 18.8266},
    {71.5473, 1215.9365, 18.8195},
    {68.2624, 1216.8950, 18.8064},
    {65.4576, 1217.5251, 18.8194},
    {66.6390, 1221.3043, 18.8196},
    {69.2445, 1220.6901, 18.8061},

    {-1664.4591, 415.9224, 7.1797},
    {-1666.4644, 417.8424, 7.1797},
    {-1670.8046, 413.4890, 7.1797},
    {-1668.9584, 411.5749, 7.1797},
    {-1674.2866, 406.2628, 7.1797},
    {-1676.1379, 408.0254, 7.1797},
    {-1680.1700, 403.9199, 7.1797},
    {-1678.4148, 402.1906, 7.1797},
    {-1685.1273, 408.7676, 7.1797},
    {-1686.8746, 410.5726, 7.1797},
    {-1682.6534, 414.6003, 7.1797},
    {-1680.9406, 412.9160, 7.1797},
    {-1675.5721, 418.2293, 7.1797},
    {-1677.4652, 420.0475, 7.1797},
    {-1673.0267, 424.3049, 7.1797},
    {-1671.3322, 422.6688, 7.1797},

    {3521.5911, -1962.4232, 16.0292},
    {3521.8403, -1960.4658, 16.0292},
    {3524.0715, -1960.2682, 16.0292},
    {3524.0503, -1962.3649, 16.0292},
    {3527.6011, -1962.3693, 16.0292},
    {3527.5986, -1960.2015, 16.0292},
    {3529.7446, -1960.3197, 16.0292},
    {3529.6462, -1962.2744, 16.0292}
};

IsRefillArea(playerid)
{
    for(new i = 0; i < sizeof(RefillArea); i++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.5, RefillArea[i][0], RefillArea[i][1], RefillArea[i][2]))
            return 1;
    }
    return 0;
}

hook OnPlayerConnect(playerid)
{
    /* Reset Vars */
    pTimerRefill[playerid] = -1;
    RefillPrice[playerid] = -1;
    DurringRefill[playerid] = false;

    if(DestroyDynamic3DTextLabel(RefillLabel[playerid]))   
        RefillLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    for (new i = 0; i < sizeof(RefillArea); i++)
    {
        if(DestroyDynamic3DTextLabel(pomLabel[playerid][i]))
            pomLabel[playerid][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        pomLabel[playerid][i] = CreateDynamic3DTextLabel("", -1, RefillArea[i][0], RefillArea[i][1], RefillArea[i][2], 1.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 1.0, -1, 0);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    /* Reset Vars */
    KillTimer(pTimerRefill[playerid]);
    pTimerRefill[playerid] = -1;
    RefillPrice[playerid] = -1;
    DurringRefill[playerid] = false;
    
    for (new x = 0; x < sizeof(RefillArea); x ++)
    {
        if(DestroyDynamic3DTextLabel(pomLabel[playerid][x]))
            pomLabel[playerid][x] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    if(DestroyDynamic3DTextLabel(RefillLabel[playerid]))
        RefillLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    return 1;
}

RefreshLabelPoms(playerid)
{
    new vehid = GetNearestVehicleToPlayer(playerid, 2.0, false);

    for(new x = 0; x < sizeof(RefillArea); x++)
    {
        if(!IsPlayerInAnyVehicle(playerid))
        {
            if(vehid != INVALID_VEHICLE_ID)
            {
                if(!DurringRefill[playerid]) UpdateDynamic3DTextLabelText(pomLabel[playerid][x], -1, "Tekan"GREEN" Y"WHITE" untuk mengisi BBM");
            }
            else 
            {
                UpdateDynamic3DTextLabelText(pomLabel[playerid][x], -1, "Tekan "GREEN"Y"WHITE" untuk membeli jerigen\nHarga:"DARKGREEN" $1500");
            }
        }
        else 
        {
            UpdateDynamic3DTextLabelText(pomLabel[playerid][x], -1, "");
        }
    }
    return 1;
}

ptask PlayerEnterPoms[2000](playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;
    
    if(IsRefillArea(playerid)) {
        RefreshLabelPoms(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new carid = GetNearestVehicleToPlayer(playerid, 2.0, false);
        if(IsRefillArea(playerid))
        {
            if(carid != INVALID_VEHICLE_ID)
            {
                if(!DurringRefill[playerid])
                {
                    if(AccountData[playerid][pMoney] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                    if(GetEngineStatus(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mematikan mesin!");
                    if(GetFuel(carid) >= 100) return ShowTDN(playerid, NOTIFICATION_WARNING, "Bensin kendaraan ini full!");

                    ApplyAnimationEx(playerid,"CAMERA","camstnd_idleloop", 4.1, 1, 0, 0, 0, 0, 1);
                    SendRPMeAboveHead(playerid, "Mengisi bahan bakar kendaraan didepan", X11_PLUM1);

                    if(DestroyDynamic3DTextLabel(RefillLabel[playerid]))
                        RefillLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                
                    DurringRefill[playerid] = true;
                    AccountData[playerid][pTempVehID] = carid;
                    RefillPrice[playerid] = 0;
                    RefillLabel[playerid] = CreateDynamic3DTextLabel(" ", -1, 0.0, 0.0, 1.1, 5.0, INVALID_PLAYER_ID, carid, 1, 0, 0, -1, 5.0, -1, 0);
                    pTimerRefill[playerid] = SetTimerEx("VehicleRefill", 550, true, "dd", playerid, carid);
                }
                else 
                {
                    KillTimer(pTimerRefill[playerid]);
                    pTimerRefill[playerid] = -1;
                    DurringRefill[playerid] = false;
                    RefillPrice[playerid] = 0;

                    if(DestroyDynamic3DTextLabel(RefillLabel[playerid]))
                        RefillLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

                    ClearAnimations(playerid, 1);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
                }
            }
            else 
            {
                if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
                TakeMoney(playerid, 1500);

                Inventory_Add(playerid, "Jerigen", 1650);
                ShowItemBox(playerid, "Recieved 1x", "Jerigen", 1650);
                ShowItemBox(playerid, "Removed $1500", "Uang", 1212);
            }
        }   
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJerigenUse])
        {
            new carid = GetNearestVehicleToPlayer(playerid, 3.5, false);
            if(carid != INVALID_VEHICLE_ID)
            {
                if(!DurringRefill[playerid])
                {
                    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                    if(GetEngineStatus(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mematikan mesin!");
                    if(GetFuel(carid) >= 100) return ShowTDN(playerid, NOTIFICATION_WARNING, "Bensin kendaraan ini full!");

                    ApplyAnimationEx(playerid,"CAMERA","camstnd_idleloop", 4.1, 1, 0, 0, 0, 0, 1);
                    SendRPMeAboveHead(playerid, "Mengisi bahan bakar kendaraan didepan", X11_PLUM1);
           
                    DurringRefill[playerid] = true;
                    pTimerRefill[playerid] = SetTimerEx("VehicleRefillJerigen", 550, true, "dd", playerid, carid);
                }
                else 
                {
                    KillTimer(pTimerRefill[playerid]);
                    pTimerRefill[playerid] = -1;
                    DurringRefill[playerid] = false;
                    RefillPrice[playerid] = 0;
                    AccountData[playerid][pJerigenUse] = false;

                    if(DestroyDynamic3DTextLabel(RefillLabel[playerid]))
                        RefillLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                    
                    Inventory_Remove(playerid, "Jerigen");
                    RemovePlayerAttachedObject(playerid, 9);
                    ClearAnimations(playerid, 1);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
                }
            }
        }
    }
    return 1;
}
forward VehicleRefillJerigen(playerid, vehicleid);
public VehicleRefillJerigen(playerid, vehicleid) 
{
    if(vehicleid == -1) return 0;
    
    new FuelCount = GetFuel(vehicleid);

    if(GetNearestVehicleToPlayer(playerid, 3.0, false) != vehicleid)
    {
        KillTimer(pTimerRefill[playerid]);
        pTimerRefill[playerid] = -1;
        DurringRefill[playerid] = false;
        AccountData[playerid][pJerigenUse] = false;

        ClearAnimations(playerid, 1);
        RemovePlayerAttachedObject(playerid, 9);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        Error(playerid, "Anda terlalu jauh dari kendaraan");
        if(IsValidDynamic3DTextLabel(RefillLabel[playerid])) DestroyDynamic3DTextLabel(RefillLabel[playerid]);
        AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        return 0;
    }

    if(vehicleid == AccountData[playerid][pTempVehID])
    {
        FuelCount ++;
        UpdateDynamic3DTextLabelText(RefillLabel[playerid], -1, sprintf("%d%", FuelCount));
        
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        VehicleCore[AccountData[playerid][pTempVehID]][vCoreFuel] += 1;

        if(FuelCount >= 100)
        {
            DurringRefill[playerid] = false;
            KillTimer(pTimerRefill[playerid]);
            pTimerRefill[playerid] = -1;
            AccountData[playerid][pJerigenUse] = false;

            ClearAnimations(playerid, 1);
            RemovePlayerAttachedObject(playerid, 9);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
            if(IsValidDynamic3DTextLabel(RefillLabel[playerid])) DestroyDynamic3DTextLabel(RefillLabel[playerid]);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
    }
    return 1;
}

forward VehicleRefill(playerid, vehicleid);
public VehicleRefill(playerid, vehicleid)
{
    if(vehicleid == -1) return 0;
    
    new FuelCount = GetFuel(vehicleid);

    if(GetNearestVehicleToPlayer(playerid, 3.0, false) != vehicleid)
    {
        KillTimer(pTimerRefill[playerid]);
        pTimerRefill[playerid] = -1;
        DurringRefill[playerid] = false;
        RefillPrice[playerid] = 0;

        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        Error(playerid, "Anda terlalu jauh dari kendaraan");
        if(IsValidDynamic3DTextLabel(RefillLabel[playerid])) DestroyDynamic3DTextLabel(RefillLabel[playerid]);
        AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        return 0;
    }

    if(AccountData[playerid][pTempVehID] == vehicleid)
    {
        FuelCount ++;
        RefillPrice[playerid] += 10;
        UpdateDynamic3DTextLabelText(RefillLabel[playerid], -1, sprintf("%d%", FuelCount));
        for(new i = 0; i < sizeof(RefillArea); i ++) {
            UpdateDynamic3DTextLabelText(pomLabel[playerid][i], -1, sprintf("Tekan "GREEN"Y"WHITE" untuk membatalkan isi bbm\n"WHITE"Harga: "DARKGREEN"$%d", RefillPrice[playerid]));
        }

        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        TakeMoney(playerid, 10);
        VehicleCore[AccountData[playerid][pTempVehID]][vCoreFuel] += 1;

        if(FuelCount >= 100)
        {
            KillTimer(pTimerRefill[playerid]);
            pTimerRefill[playerid] = -1;
            DurringRefill[playerid] = false;
            RefillPrice[playerid] = 0;

            ClearAnimations(playerid, 1);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
            if(IsValidDynamic3DTextLabel(RefillLabel[playerid])) DestroyDynamic3DTextLabel(RefillLabel[playerid]);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }

        if(AccountData[playerid][pMoney] < 1)
        {
            KillTimer(pTimerRefill[playerid]);
            pTimerRefill[playerid] = -1;
            DurringRefill[playerid] = false;
            RefillPrice[playerid] = 0;

            ClearAnimations(playerid, 1);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
            if(IsValidDynamic3DTextLabel(RefillLabel[playerid])) DestroyDynamic3DTextLabel(RefillLabel[playerid]);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
    }
    return 1;
}