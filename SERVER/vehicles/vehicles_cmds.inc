#include <YSI_Coding\y_hooks>
CMD:avcolor(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 4) 
		return PermissionError(playerid);
	
	new color1, color2, vehicleid = GetPlayerVehicleID(playerid), vehicle_index = RETURN_INVALID_VEHICLE_ID;
	if(sscanf(params, "dd", color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/avcolor [pVehcolor1] [pVehcolor2]");
	if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai kendaraan!");
	if(VehicleCore[vehicleid][vehAdmin] || SidejobVehicles(vehicleid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini static!");

	if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
	{
		ChangeVehicleColor(vehicleid, color1, color2);

		PlayerVehicle[vehicle_index][pVehColor1] = color1;
		PlayerVehicle[vehicle_index][pVehColor2] = color2;
		SavePlayerVehicle(PlayerVehicle[vehicle_index][pVehPhysic]);
	}
	return 1;
}

CMD:trunkfix(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);
	
	new vehid;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/trunkfix [vehicle id]");
	if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tidak valid/spawn!");
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
	{
		if(PlayerVehicle[i][pVehPhysic] == vehid)
		{
			if(PlayerVehicle[i][pVehCapacity] <= 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak bug, hanya 30kg keatas yang dapat di reset!");

			PlayerVehicle[i][pVehCapacity] = 0;
			SavePlayerVehicle(i);
		}
	}

	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mereset kapasitas bagasi kendaraan tersebut!");
	return 1;
}

CMD:aseat(playerid, params[])
{
	new otherid;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/aseat [driver id]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerInVehicle(otherid, GetPlayerVehicleID(playerid))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada di kendaraan yang sama!");
	if(GetVehicleDriver(GetPlayerVehicleID(playerid)) != otherid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut bukan driver!");
	if(!IsPlayerInVehicle(otherid, GetPlayerVehicleID(playerid))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada di kendaraan yang sama!");
	if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukan ini kepada diri sendiri!");

	ChangeSeatWithPlayerID[otherid] = playerid;
	ChangeSeatVehicleID[otherid] = GetPlayerVehicleID(otherid);
	ChangeSeatVehicleID[playerid] = GetPlayerVehicleID(playerid);
	SendClientMessageEx(otherid, -1, ""SKYBLUE"SWITCH SEAT:"YELLOW" %s(%d)"WHITE" Meminta untuk bertukar kemudi. Gunakan "YELLOW"'/accept seat'"WHITE" untuk menerima", ReturnName(playerid), playerid);
	ShowTDN(playerid, NOTIFICATION_INFO, "Berhasil meminta untuk bertukar posisi kemudi. Tunggu pemain tersebut menerima!");
	return 1;
}

alias:takeoutveh("tov")
CMD:takeoutveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);
	
	new vehid, Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	if(sscanf(params, "d", vehid))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/takeoutveh [VID Database]");

	foreach(new iterid : PvtVehicles)
	{
		if(vehid == PlayerVehicle[iterid][pVehID])
		{
			if(!IsValidVehicle(PlayerVehicle[iterid][pVehPhysic]))
			{
				if(PlayerVehicle[iterid][pVehInsuranced]){
					PlayerVehicle[iterid][pVehInsuranced] = false;
				}

				if(PlayerVehicle[iterid][pVehImpounded]){
					PlayerVehicle[iterid][pVehImpounded] = false;
					PlayerVehicle[iterid][pVehImpoundDuration] = 0;
					PlayerVehicle[iterid][pVehImpoundFee] = 0;
					format(PlayerVehicle[iterid][pVehImpoundReason], 64, "N/A");
				}

				if(PlayerVehicle[iterid][pVehParked] >= 0){
					PlayerVehicle[iterid][pVehParked] = -1;
				}

				if(PlayerVehicle[iterid][pVehFamiliesGarage] >= 0) {
					PlayerVehicle[iterid][pVehFamiliesGarage] = -1;
				}

				if(PlayerVehicle[iterid][pVehHouseGarage] >= 0) {
					PlayerVehicle[iterid][pVehHouseGarage] = -1;
				}

				if(PlayerVehicle[iterid][pVehHelipadGarage] >= 0) {
					PlayerVehicle[iterid][pVehHelipadGarage] = -1;
				}

				if(PlayerVehicle[iterid][pVehFactStored] >= 0) {
					PlayerVehicle[iterid][pVehFactStored] = -1;
				}

				PlayerVehicle[iterid][pVehWorld] = GetPlayerVirtualWorld(playerid);
				PlayerVehicle[iterid][pVehInterior] = GetPlayerInterior(playerid);
				
				PlayerVehicle[iterid][pVehPos][0] = x;
				PlayerVehicle[iterid][pVehPos][1] = y;
				PlayerVehicle[iterid][pVehPos][2] = z;

				OnPlayerVehicleRespawn(iterid);
				SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menggunakan Forced Veh pada kendaraan Database ID: "YELLOW"%d", GetAdminName(playerid), vehid);
			}
			else return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut masih spawn!");
		}
	}
	return 1;
}

CMD:agiveplate(playerid, params[])
{
	new vehid = -1;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/agiveplate [VID]");
	if(SidejobVehicles(vehid) || VehicleCore[vehid][vehAdmin]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sidejob/static!");
	if((vehid = Vehicle_Nearest(playerid, 3.0)) != -1)
	{
		if(PlayerVehicle[vehid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut milik rental!");
		if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak valid!");
		if(PlayerVehicle[vehid][pVehPlateOwn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut sudah memiliki Nomor Plat!");

		new 
			xd1 = random(sizeof(g_Alphabet)),
			xd2 = random(sizeof(g_Alphabet)),
			xd3 = random(sizeof(g_Alphabet));
		
		PlayerVehicle[vehid][pVehPlateOwn] = 1;

		format(PlayerVehicle[vehid][pVehPlate], 64, "AE %d%d%d%d %s%s%s", random(10), random(10), random(10), random(10), g_Alphabet[xd1], g_Alphabet[xd2], g_Alphabet[xd3]);
		SetVehicleNumberPlate(PlayerVehicle[vehid][pVehPhysic], PlayerVehicle[vehid][pVehPlate]);
		SavePlayerVehicle(vehid);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Plate berhasil terpasang ke kendaraan tersebut!");
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun di sekitar!");
	return 1;
}

alias:setvehdonation("svd")
CMD:setvehdonation(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 7) return PermissionError(playerid);

	new vehid;
	if(sscanf(params, "i", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setvehdonation [pVehID]");
	if(VehicleCore[vehid][vehAdmin] || vehid == INVALID_VEHICLE_ID || SidejobVehicles(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "VID Kendaraan tidak valid!");
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehPhysic] == vehid)
	{
		if(!PlayerVehicle[i][vehDonation])
		{
			PlayerVehicle[i][vehDonation] = 1;
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengubah status kendaraan menjadi Donasi!");
		}
	}
	return 1;
}

CMD:setfuel(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);

	new vehid, fuel;
	if(sscanf(params, "id", vehid, fuel)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setfuel [VID] [amount]");
	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Kendaraan tidak valid!");

	VehicleCore[vehid][vCoreFuel] = fuel;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menetapkan Fuel kendaraan VID: "YELLOW"%d"ARWIN1" menjadi %d Liter", GetAdminName(playerid), vehid, fuel);
	return 1;
}

CMD:vinvis(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);
	
	Info(playerid, "Admin Vehicle Invisible for you is now '%s'", (GetPVarInt(playerid, "vehCollision") != 1) ? ("Disabled") : ("Enabled"));
	SetPVarInt(playerid, "vehCollision", !GetPVarInt(playerid, "vehCollision"));
	DisableRemoteVehicleCollisions(playerid, GetPVarInt(playerid, "vehCollision"));
	return 1;
}

CMD:sellveh(playerid, params[]) 
{
	new otherid, vid, price;
	if(sscanf(params, "udd", otherid, vid, price)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sellveh [name/playerid] [VID] [harga]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 2.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus dekat dengan anda!");
	if(!GetNearestVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan kendaraan yang ingin dijual!");
	if(price < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1");

	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
	{
		if(PlayerVehicle[i][pVehPhysic] == vid)
		{
			if(PlayerVehicle[i][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan milik anda!");
			if(PlayerVehicle[i][pVehFaction] > FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat dijual!");
			if(PlayerVehicle[i][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat dijual!");
			if(!PlayerVehicle[i][pVehPlateOwn] && !IsABicycle(PlayerVehicle[i][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut belum memiliki Nomor Plat!");

			AccountData[otherid][pCarSeller] = playerid;
			AccountData[otherid][pCarOffered] = vid;
			AccountData[otherid][pCarValue] = price;
			format(AccountData[otherid][pTempText], 256, "%s", PlayerVehicle[i][pVehPlate]);
			SetPVarString(otherid, "CarName", GetVehicleName(PlayerVehicle[i][pVehPhysic]));

			Dialog_Show(playerid, SellVehMenu, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Metode Pembayaran", "Cash\nSaldo Rekening", "Pilih", "Batal");
			SetPVarInt(playerid, "CarBuyer", otherid);
		}
	}
	return 1;
}

Dialog:SellVehMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new otherid = GetPVarInt(playerid, "CarBuyer"), string[128];
		GetPVarString(otherid, "CarName", string, sizeof(string));
		
		if(otherid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		if(!IsPlayerNearPlayer(playerid, otherid, 5.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak di dekat anda!");
		switch(listitem)
		{
			case 0: // Cash
			{
				Dialog_Show(otherid, BuyvehCashMenu, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Beli Kendaraan",
				""WHITE"%s menawarkan anda {FFFF00}%s{FFFFFF} seharga {00FF00}%s\
				\n"WHITE"Metode Pembayaran: "YELLOW"Cash\
				\n"WHITE"Tekan "GREEN"Iya"WHITE" untuk membeli kendaraannya\
				\nTekan "RED"Tidak"WHITE" untuk membatalkan pembelian kendaraannya.\
				\n\nNOTE: Uang akan terpotong otomatis jika anda menerima pembelian kendaraan", "Iya", "Tidak", AccountData[playerid][pName], string, FormatMoney(AccountData[otherid][pCarValue]));
			}
			case 1: // Bank
			{
				Dialog_Show(otherid, BuyvehRekeningMenu, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Beli Kendaraan",
				""WHITE"%s menawarkan anda {FFFF00}%s{FFFFFF} seharga {00FF00}%s\
				\n"WHITE"Metode Pembayaran: "YELLOW"Saldo Rekening\
				\n"WHITE"Tekan "GREEN"Iya"WHITE" untuk membeli kendaraannya\
				\nTekan "RED"Tidak"WHITE" untuk membatalkan pembelian kendaraannya.\
				\n\nNOTE: Saldo Rekening akan terpotong otomatis jika anda menerima pembelian kendaraan", "Iya", "Tidak", AccountData[playerid][pName], string, FormatMoney(AccountData[otherid][pCarValue]));
			}
		}
	}
	else
	{
		foreach(new i : Player) if (IsPlayerConnected(i)) 
		{
			if(AccountData[i][pCarSeller] == playerid)
			{
				AccountData[i][pCarSeller] = INVALID_PLAYER_ID;
				AccountData[i][pCarOffered] = -1;
				AccountData[i][pCarValue] = 0;
				AccountData[i][pTempText] = EOS;
				DeletePVar(i, "CarName");
			}
		}
		DeletePVar(playerid, "CarBuyer");
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
	}
	return 1;
}

Dialog:BuyvehCashMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(AccountData[playerid][pCarSeller] == INVALID_PLAYER_ID)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada tawaran kendaraan untukmu!");
		
		new 
			seller = AccountData[playerid][pCarSeller],
			vehicleid = AccountData[playerid][pCarOffered],
			price = AccountData[playerid][pCarValue];
		
		if(!IsPlayerNearPlayer(playerid, seller, 3.0))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat Seller!");
		
		new count = 0;
		foreach(new carid : PvtVehicles)
		{
			if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
				count ++;
		}
		if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");
		if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
		
		new vehicle_index;
		if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
		{
			PlayerVehicle[vehicle_index][pVehOwnerID] = AccountData[playerid][pID];
			TakeMoney(playerid, price);
			GiveMoney(seller, price);
			SendClientMessageToAllEx(X11_CORNFLOWERBLUE, "[i] %s Milik %s terjual kepada %s seharga %s", AccountData[playerid][pTempText], GetRPName(seller), GetRPName(playerid), FormatMoney(price));

			new cQuery[598];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET `PVeh_OwnerID`=%d WHERE `id`=%d", PlayerVehicle[vehicle_index][pVehOwnerID], PlayerVehicle[vehicle_index][pVehID]);
			mysql_tquery(g_SQL, cQuery);

			static shstr[255];
			format(shstr, sizeof(shstr), "Membeli %s milik %s seharga %s", GetVehicleName(PlayerVehicle[vehicle_index][pVehPhysic]), AccountData[AccountData[playerid][pCarSeller]][pName], FormatMoney(AccountData[playerid][pCarValue]));
			AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, AccountData[playerid][pCarValue]);

			AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
			AccountData[playerid][pCarOffered] = -1;
			AccountData[playerid][pCarValue] = 0;
			DeletePVar(playerid, "CarName");
		}
	}
	else
	{
		DeletePVar(AccountData[playerid][pCarSeller], "CarBuyer");

		AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
		AccountData[playerid][pCarOffered] = -1;
		AccountData[playerid][pCarValue] = 0;
		AccountData[playerid][pTempText] = EOS;
		DeletePVar(playerid, "CarName");
		ShowTDN(playerid, NOTIFICATION_WARNING, "Anda menolak membeli kendaraan");
	}
	return 1;
}

Dialog:BuyvehRekeningMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(AccountData[playerid][pCarSeller] == INVALID_PLAYER_ID)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada tawaran kendaraan untukmu!");
		
		new 
			seller = AccountData[playerid][pCarSeller],
			vehicleid = AccountData[playerid][pCarOffered],
			price = AccountData[playerid][pCarValue];
		
		if(!IsPlayerNearPlayer(playerid, seller, 3.0))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat Seller!");
		
		new count = 0;
		foreach(new carid : PvtVehicles)
		{
			if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
				count ++;
		}
		if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");
		if(AccountData[playerid][pBankMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo Rekening anda tidak cukup!");
		
		new vehicle_index;
		if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
		{
			PlayerVehicle[vehicle_index][pVehOwnerID] = AccountData[playerid][pID];
			AccountData[playerid][pBankMoney] -= price;
			AccountData[seller][pBankMoney] += price;
			// TakeMoney(playerid, price);
			// GiveMoney(seller, price);
			SendClientMessageToAllEx(X11_CORNFLOWERBLUE, "[i] %s Milik %s terjual kepada %s seharga %s", AccountData[playerid][pTempText], GetRPName(seller), GetRPName(playerid), FormatMoney(price));

			new cQuery[598];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET `PVeh_OwnerID`=%d WHERE `id`=%d", PlayerVehicle[vehicle_index][pVehOwnerID], PlayerVehicle[vehicle_index][pVehID]);
			mysql_tquery(g_SQL, cQuery);

			static shstr[255];
			format(shstr, sizeof(shstr), "Membeli %s milik %s seharga %s", GetVehicleName(PlayerVehicle[vehicle_index][pVehPhysic]), AccountData[AccountData[playerid][pCarSeller]][pName], FormatMoney(AccountData[playerid][pCarValue]));
			AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, AccountData[playerid][pCarValue]);

			AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
			AccountData[playerid][pCarOffered] = -1;
			AccountData[playerid][pCarValue] = 0;
			DeletePVar(playerid, "CarName");
		}
	}
	else
	{
		DeletePVar(AccountData[playerid][pCarSeller], "CarBuyer");

		AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
		AccountData[playerid][pCarOffered] = -1;
		AccountData[playerid][pCarValue] = 0;
		AccountData[playerid][pTempText] = EOS;
		DeletePVar(playerid, "CarName");
		ShowTDN(playerid, NOTIFICATION_WARNING, "Anda menolak membeli kendaraan");
	}
	return 1;
}

/*CMD:sellveh(playerid, params[]) 
{
	new otherid, vid, price;
	if(sscanf(params, "udd", otherid, vid, price)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sellveh [name/playerid] [VID] [harga]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 2.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus dekat dengan anda!");
	if(!GetNearestVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan kendaraan yang ingin dijual!");
	if(price < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1");

	foreach(new iterid : PvtVehicles) 
	{
		if(vid == PlayerVehicle[iterid][pVehPhysic]) 
		{
			if(PlayerVehicle[iterid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan milik anda!");
			if(PlayerVehicle[iterid][pVehFaction] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat dijual!");
			if(PlayerVehicle[iterid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat dijual!");
			if(!PlayerVehicle[iterid][pVehPlateOwn] && !IsABicycle(PlayerVehicle[iterid][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut belum memiliki plate!");

			AccountData[otherid][pCarSeller] = playerid;
			AccountData[otherid][pCarOffered] = vid;
			AccountData[otherid][pCarValue] = price;
			format(AccountData[otherid][pTempText], 256, "%s", PlayerVehicle[iterid][pVehPlate]);
			
			SendClientMessageEx(otherid, -1, "[i] Seseorang %s menawarkan anda {FFFF00}%s{FFFFFF} seharga {00FF00}%s{FFFF00} '/accept buyveh'{FFFFFF} untuk menerima", ReturnName(playerid), GetVehicleName(vid), FormatMoney(price));
			SendClientMessageEx(playerid, -1, "[i] Anda menawarkan {FFFF00}%s{FFFFFF} dengan harga {00FF00}%s{FFFFFF} kepada %s", GetVehicleName(vid), FormatMoney(price), ReturnName(otherid));
		}
	}
	return 1;
}*/

CMD:aeject(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 2) return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/aeject [name/playerid]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerInAnyVehicle(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak di dalam kendaraan!");

	RemovePlayerFromVehicle(otherid);
	SendClientMessageEx(playerid, -1, "[i] Anda menendang pemain "YELLOW"%s(%d)"WHITE" dari kendaraan", AccountData[otherid][pName], otherid);
	return 1;
}

CMD:sl(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;
	
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new Float:speed;
		if(sscanf(params, "f", speed)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sl [speed]~n~/sl 0 untuk disable");

		if(speed > 0.0)
		{
			SetVehicleSpeedCap(GetPlayerVehicleID(playerid), speed);
			ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Speed limit diatur ke %.1f", speed));
		}
		else if(speed < 1.0)
		{
			DisableVehicleSpeedCap(GetPlayerVehicleID(playerid));
			ShowTDN(playerid, NOTIFICATION_INFO, "Speed limit dimatikan");
		}
	}
	else return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengemudikan kendaraan!");
	return 1;
}

CMD:eject(playerid, params[])
{
	new vehid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new otherid;
		if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/eject [playerid/Name]");
		if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
		
		if(IsPlayerInVehicle(otherid, vehid))
		{
			RemovePlayerFromVehicle(otherid);
			SendRPMeAboveHead(playerid, "Menendang seseorang keluar dari kendaraannya", X11_PLUM1);
			ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("%s telah menendang anda dari kendaraannya", GetRPName(playerid)));
		}
		else 
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak didalam kendaraan!");
		}
	}
	else 
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam kendaraan!");
	}
	return 1;
}

CMD:importveh(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/importveh [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	
	new count = 0;
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[otherid][pID])
			count ++;
	}

	if(count >= GetPlayerVehicleLimit(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan player tersebut telah penuh!");

	new Float:POS[4];
	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	GetPlayerFacingAngle(otherid, POS[3]);
	Vehicle_Create(otherid, model[0], FACTION_NONE, POS[0], POS[1], POS[2], POS[3], color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);
	
	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /importveh membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

CMD:aimportveh(playerid, params[])
{
	if(CheckAdmin(playerid, 7)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/importveh [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");

	new Float:POS[4];
	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	GetPlayerFacingAngle(otherid, POS[3]);
	Vehicle_Create(otherid, model[0], FACTION_NONE, POS[0], POS[1], POS[2], POS[3], color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);
	
	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /aimportveh membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

alias:createpv("makeveh", "cpv", "makepv", "vcreate")
CMD:createpv(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/createpv [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	
	new count = 0;
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[otherid][pID])
			count ++;
	}

	if(count >= GetPlayerVehicleLimit(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan player tersebut telah penuh!");

	VehicleImport_Create(otherid, model[0], FACTION_NONE, 0.0, 0.0, 0.0, 0.0, color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);

	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /makepv membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

CMD:amakepv(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/createpv [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");

	VehicleImport_Create(otherid, model[0], FACTION_NONE, 0.0, 0.0, 0.0, 0.0, color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);

	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /amakepv membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

alias:deletepv("destroypv", "dpv", "vdelete")
CMD:deletepv(playerid, params[])
{
	if(CheckAdmin(playerid, 4))
		return PermissionError(playerid);
	
	if(isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/destroypv [VID Vehicles]");
	
	if(strval(params) == INVALID_VEHICLE_ID)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid VID Vehicles!");
	
	if(Vehicle_GetID(strval(params)) != -1)
	{
		Vehicle_Delete(Vehicle_GetID(strval(params)));
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menghancurkan kendaraan ID:"YELLOW" %d.", GetAdminName(playerid), strval(params));
	}
	else 
		ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Player Vehicle ID!");
	
	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /deletepv menghapus kendaraan vID: %d.", strval(params));
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

alias:avehlist("apv")
CMD:avehlist(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
		return PermissionError(playerid);
	new 
		otherid,
		CMDString[3056],
		bool: found = false 
	;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/apv [playerid/Name]");
	if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");

	static frmtxt[255];
	format(CMDString,sizeof(CMDString),"VID\tModel Kendaraan(Database ID)\tNomor Plate\t/Rental/Status/\n");
	foreach(new iter : PvtVehicles)
	{
		if(PlayerVehicle[iter][pVehExists])
		{
			if(IsValidVehicle(PlayerVehicle[iter][pVehPhysic]) || !IsValidVehicle(PlayerVehicle[iter][pVehPhysic]))
			{
				if(PlayerVehicle[iter][pVehOwnerID] == GetUCPSQLID(otherid))
				{
					if(strcmp(PlayerVehicle[iter][pVehPlate], "-") || strcmp(PlayerVehicle[iter][pVehPlate], "-"))
					{
						new currentTime = PlayerVehicle[iter][pVehRentTime] - gettime();
						new hours = (currentTime % 86400) / 3600;
						new minutes = (currentTime % 3600) / 60;
						new seconds = currentTime % 60;
						format(frmtxt, sizeof(frmtxt), "%d Jam %d Menit %d Detik", hours, minutes, seconds);

						if(PlayerVehicle[iter][pVehRental] != -1 && PlayerVehicle[iter][pVehRentTime] > 0)
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t%s/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], frmtxt, GetMyVehicleStatus(iter, "Spawned"));
						}
						else 
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t"GREEN"Dimiliki"WHITE"/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], GetMyVehicleStatus(iter, "Spawned"));
						}
						found = true;
					}
					else
					{
						if(PlayerVehicle[iter][pVehRental] != -1 && PlayerVehicle[iter][pVehRentTime] > 0)
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t%s/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], frmtxt, GetMyVehicleStatus(iter, "Spawned"));
						}
						else 
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t"GREEN"Dimiliki"WHITE"/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], GetMyVehicleStatus(iter, "Spawned"));
						}
						found = true;
					}
				}
			}
		}
	}
	if(found)
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""City"Happy Roleplay "WHITE"- Player Vehicle", CMDString, "Tutup", "");
	else 
		ShowTDN(playerid, NOTIFICATION_WARNING, "Pemain tersebut tidak memiliki kendaraan apapun!");
	return 1;
}

CMD:aveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);

	if(vehicleid == INVALID_VEHICLE_ID)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak berada didekat Kendaraan apapun.");
	
	SendClientMessageEx(playerid, X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" Kendaraan didekatmu VID: "YELLOW"%d - %s(%d).", GetAdminName(playerid), vehicleid, GetVehicleName(vehicleid), GetVehicleModel(vehicleid));
	return 1;
}

CMD:sendveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

	new otherid, VID, Float:x, Float:y, Float:z;
	if(sscanf(params, "ud", otherid, VID)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sendveh [name/playerid] [vID]~n~/apv - mencari VID pemain");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsValidVehicle(VID)) return ShowTDN(playerid, NOTIFICATION_ERROR, "VID Tidak valid!");

	GetPlayerPos(otherid, x, y, z);
	SetVehiclePos(VID, x, y, z + 0.5);
	SetVehicleVirtualWorld(VID, GetPlayerVirtualWorld(otherid));
	LinkVehicleToInterior(VID, GetPlayerInterior(otherid));
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" mengirim kendaraan "YELLOW"%d - %s(%d)"ARWIN1" kepada "YELLOW"%s(%d) - %s", AccountData[playerid][pAdminname], VID, GetVehicleName(VID), GetVehicleModel(VID), AccountData[otherid][pName], otherid, GetLocation(x, y, z));
	return 1;
}

alias:getveh("vget")
CMD:getveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

	new VID, Float:x, Float:y, Float:z;
	if(sscanf(params, "d", VID)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/getveh [VID]~n~/apv - mencari VID pemain");
	if(VID == INVALID_VEHICLE_ID || !IsValidVehicle(VID)) return ShowTDN(playerid, NOTIFICATION_ERROR, "VID Tidak valid!");
	GetPlayerPos(playerid, z, z, z);

	GetXYInFrontOfPlayer(playerid, x, y, 3.0);
	SetVehiclePos(VID, x, y, z);

	SetVehicleVirtualWorld(VID, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(VID, GetPlayerInterior(playerid));
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menarik kendaraan "YELLOW"%d - %s(%d)"ARWIN1" ke %s", AccountData[playerid][pAdminname], VID, GetVehicleName(VID), GetVehicleModel(VID), GetLocation(x, y, z));
	return 1;
}

CMD:gotoveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
		return PermissionError(playerid);

	new vehid, Float:posisiX, Float:posisiY, Float:posisiZ;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotoveh [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	
	GetVehiclePos(vehid, posisiX, posisiY, posisiZ);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke kendaraan "YELLOW"VID %d - %s(%d)"ARWIN1". Lokasi %s", GetAdminName(playerid), vehid, GetVehicleName(vehid), GetVehicleModel(vehid), GetLocation(posisiX, posisiY, posisiZ));
	SetPlayerPosition(playerid, posisiX, posisiY, posisiZ+3.0, 4.0, 0);
	SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(vehid));
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	return 1;
}

CMD:respawnveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new vehid, Float:posisiX, Float:posisiY, Float:posisiZ;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/respawnveh [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	GetVehiclePos(vehid, posisiX, posisiY, posisiZ);
	if(IsVehicleEmpty(vehid))
	{
		SetTimerEx("RespawnPV", 3000, false, "d", vehid);
		Info(playerid, "Your respawned vehicle location %s (vehicle id: %d).", GetLocation(posisiX, posisiY, posisiZ), vehid);
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "This Vehicle in used by someone.");
	return 1;
}

CMD:myv(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus terkoneksi ke dalam server!");
	if(!GetOwnedVeh(playerid)) return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Kepemilikan Kendaraan", "Anda tidak memiliki kendaraan apapun!", "Tutup", "");

	new count = GetOwnedVeh(playerid);
	static 
		vid,
		list[512],
		CMDString[4056],
		Status1[512],
		StatusSpawn[512],
		PlateStatus[128]
	;

	CMDString = "";
	strcat(CMDString, "VID\tModel(Database ID)\tPlate(Masa Berlaku)\tRental/Status/\n", sizeof(CMDString));
	Loop(itt, (count + 1), 1)
	{
		vid = ReturnPlayerVehID(playerid, itt);

		if(PlayerVehicle[vid][pVehPlateOwn]) {
			format(PlateStatus, sizeof(PlateStatus), "- ("DARKRED"Permanent"WHITE")");
		} else {
			format(PlateStatus, sizeof(PlateStatus), " (Kosong)");
		}

		if(PlayerVehicle[vid][pVehPhysic] == INVALID_VEHICLE_ID) {
			format(StatusSpawn, sizeof(StatusSpawn), "[Despawned]");
		} else {
			format(StatusSpawn, sizeof(StatusSpawn), "%d", PlayerVehicle[vid][pVehPhysic]);
		}

		if(PlayerVehicle[vid][pVehRental] > 0 && PlayerVehicle[vid][pVehRentTime] != 0) {
			new currentTime = PlayerVehicle[vid][pVehRentTime] - gettime();
			new hours = (currentTime % 86400) / 3600;
			new minutes = (currentTime % 3600) / 60;
			new seconds = currentTime % 60;

			format(Status1, sizeof(Status1), "%d Jam %d Menit %d Detik", hours, minutes, seconds);
		} else {
			format(Status1, sizeof(Status1), ""GREEN"Dimiliki");
		}

		if(itt == count)
		{
			format(list, sizeof(list), "%s\t%s [%d]\t%s %s\t%s"WHITE"/%s/\n", StatusSpawn, GetVehicleModelName(PlayerVehicle[vid][pVehModelID]), PlayerVehicle[vid][pVehID], PlayerVehicle[vid][pVehPlate], PlateStatus, Status1, GetMyVehicleStatus(vid, "Spawned"));
		}
		else format(list, sizeof(list), "%s\t%s [%d]\t%s %s\t%s"WHITE"/%s/\n", StatusSpawn, GetVehicleModelName(PlayerVehicle[vid][pVehModelID]), PlayerVehicle[vid][pVehID], PlayerVehicle[vid][pVehPlate], PlateStatus, Status1, GetMyVehicleStatus(vid, "Spawned"));
		strcat(CMDString, list);
	}
	ShowPlayerDialog(playerid, DialogMyVeh, DIALOG_STYLE_TABLIST_HEADERS, ""City"Happy Roleplay "WHITE"- Kepemilikan Kendaraan", CMDString, "Cari", "Cancel");
	return 1;
}

CMD:en(playerid, params[])
{
	if(AccountData[playerid][pTurningEngine])
		return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang menyalakan mesin, tunggu sebentar!");
	
	new vehid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(!IsEngineVehicle(vehid))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan kendaraan bermesin!");
		
		if(GetEngineStatus(vehid))
		{
			SwitchVehicleEngine(vehid, false);
			SendRPMeAboveHead(playerid, "Mesin mati", X11_LIGHTGREEN);
		}
		else 
		{
			SendRPMeAboveHead(playerid, "Mencoba menghidupkan mesin kendaraan", X11_PLUM1);
			AccountData[playerid][pTurningEngine] = true;
			SetTimerEx("EngineStatus", 2500, false, "id", playerid, vehid);
		}
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didalam kendaraan apapun!");
	return 1;
}

CMD:windows(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	new vehicle_index = Vehicle_ReturnID(vehicleid);

	if(vehicle_index == RETURN_INVALID_VEHICLE_ID) return 1;
	if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam kendaraan untuk menggunakan ini!");
	if(!IsFourWheelVehicle(vehicleid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya dapat menggunakannya di kendaraan roda 4!");

	Dialog_Show(playerid, WindowsControl, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Vehicle Windows Control", "Driver Seat\nPassenger Seat\nBack Left\nBack Right\nClose All", "Choose", "Close");
	return 1;
}

Dialog:WindowsControl(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            driver, passenger, backleft, backright;

        GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            switch(listitem)
            {
                case 0: SetVehicleParamsCarWindows(vehicleid, !driver, passenger, backleft, backright);
                case 1: SetVehicleParamsCarWindows(vehicleid, driver, !passenger, backleft, backright);
                case 2: SetVehicleParamsCarWindows(vehicleid, driver, passenger, !backleft, backright);
                case 3: SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, !backright);
                default: SetVehicleParamsCarWindows(vehicleid, !driver, !driver, !driver, !driver);
            }
            Info(playerid, "Anda mengaktifkan toggle windows");
        }
    }
    return 1;
}

CMD:tow(playerid, params[]) 
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		new carid = GetPlayerVehicleID(playerid);
		if(IsATowTruck(carid))
		{
			new closestcar = GetClosestCar(playerid, carid);

			if(GetDistanceToCar(playerid, closestcar) <= 8 && !IsTrailerAttachedToVehicle(carid)) 
			{
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menderek kendaraan!");
				AttachTrailerToVehicle(closestcar, carid);
				return 1;
			}
		}
		else
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai Tow truck.");
			return 1;
		}
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai Tow truck.");
		return 1;
	}
	return 1;
}

CMD:untow(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
		{
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil melepas derekan!");
			DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
		}
		else
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Tow penderek kosong!");
		}
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai Tow truck.");
		return 1;
	}
	return 1;
}

/* Hooks */
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	foreach(new id : PublicGarage)
	{
		if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2]))
			{
				HideShortKey(playerid);
				
				new carid = -1, bool: found = false;
				if((carid = Vehicle_Nearest2(playerid)) != -1)
				{
					if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
					if(PlayerVehicle[carid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan!");
					if(PlayerVehicle[carid][pVehFaction] != FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat disimpan disini!");

					Vehicle_GetStatus(carid);
					PlayerVehicle[carid][pVehParked] = id;

					found = true;

					RemovePlayerFromVehicle(playerid);
					SetTimerEx("InputVehicleToGarage", 2000, false, "d", carid);
				}
				if(!found) return false;
			}
		}
		if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2]))
			{
				HideShortKey(playerid);
				
				if(!CountPlayerVehicleParked(playerid, id)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

				new vehid, count = CountPlayerVehicleParked(playerid, id), lstr[596];
				format(lstr, sizeof(lstr), "No\tModel Kendaraan\tNomor Plat\n");
				for(new itt; itt < count; itt ++)
				{
					vehid = ReturnAnyVehicleParked(playerid, itt, id);
					if(itt == count)
					{
						format(lstr, sizeof(lstr), "%s%d\t%s\t%s", lstr, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
					}
					else format(lstr, sizeof(lstr), "%s%d\t%s\t%s\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
				}
				AccountData[playerid][pPark] = id;
				ShowPlayerDialog(playerid, DIALOG_GARKOT_OUT, DIALOG_STYLE_TABLIST_HEADERS, "Garasi Umum - Ambil Kendaraan", lstr, "Pilih", "Batal");
			}
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_GARKOT_OUT:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
			if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan yang ingin dikeluarkan!");

			new id = ReturnAnyVehicleParked(playerid, listitem, AccountData[playerid][pPark]);
			if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan yang ingin dikeluarkan!");

			if(!IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[AccountData[playerid][pPark]][pgPOS][0], PublicGarage[AccountData[playerid][pPark]][pgPOS][1], PublicGarage[AccountData[playerid][pPark]][pgPOS][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat Garasi Umum!");
			if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
			PlayerVehicle[id][pVehParked] = -1;
			PlayerVehicle[id][pVehHouseGarage] = -1;
			PlayerVehicle[id][pVehHelipadGarage] = -1;
			PlayerVehicle[id][pVehFamiliesGarage] = -1;
			PlayerVehicle[id][pVehFactStored] = -1;

			if(PlayerVehicle[id][pVehLocked])
				PlayerVehicle[id][pVehLocked] = false;

			PlayerVehicle[id][pVehPos][0] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][0];
			PlayerVehicle[id][pVehPos][1] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][1];
			PlayerVehicle[id][pVehPos][2] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][2];
			PlayerVehicle[id][pVehPos][3] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][3];

			PlayerVehicle[id][pVehWorld] = PublicGarage[AccountData[playerid][pPark]][pgWorld];
            PlayerVehicle[id][pVehInterior] = PublicGarage[AccountData[playerid][pPark]][pgInterior];

			PlayerVehicle[id][pVehFuel] = PlayerVehicle[id][pVehFuel];
			PlayerVehicle[id][pVehHealth] = PlayerVehicle[id][pVehHealth];

			OnPlayerVehicleRespawn(id);

			SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
		}
	}
	return 1;
}