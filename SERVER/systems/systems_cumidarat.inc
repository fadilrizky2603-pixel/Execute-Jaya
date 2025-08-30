new CumiSmoke[MAX_PLAYERS];

CMD:cumi(playerid, params[])
{
    if (!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, -1, "Kamu harus berada di dalam kendaraan!");

    new vehicleid = GetPlayerVehicleID(playerid);

    // Ambil posisi dan rotasi kendaraan
    new Float:x, Float:y, Float:z;
    new Float:rz;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, rz);

    // Posisi knalpot (kanan belakang bawah Huntley - disesuaikan agar PAS)
    new Float:offsetX = 0.6;
    new Float:offsetY = -2.0;
    new Float:offsetZ = 0.25;

    // Rotasi offset ke world position
    new Float:fx = x + (offsetX * floatsin(-rz, degrees)) + (offsetY * floatcos(-rz, degrees));
    new Float:fy = y + (offsetX * floatcos(-rz, degrees)) - (offsetY * floatsin(-rz, degrees));
    new Float:fz = z + offsetZ;

    // Buat asap langsung di posisi knalpot
    CumiSmoke[playerid] = CreateDynamicObject(2780, fx, fy, fz, 0.0, 0.0, rz);

    SetTimerEx("RemoveCumiSmoke", 5000, false, "i", playerid);
    return 1;
}

forward RemoveCumiSmoke(playerid);
public RemoveCumiSmoke(playerid)
{
    if (IsValidDynamicObject(CumiSmoke[playerid]))
    {
        DestroyDynamicObject(CumiSmoke[playerid]);
        CumiSmoke[playerid] = INVALID_OBJECT_ID;
    }
    return 1;
}
