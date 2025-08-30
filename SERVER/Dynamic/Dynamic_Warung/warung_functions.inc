#include <YSI_Coding\y_hooks>
#define MAX_WARUNG 50

enum 	e_warung
{
	warungType,
	Float:warungPOS[3],
	warungInterior,
	warungWorld,

	STREAMER_TAG_MAP_ICON:warungMap,
	STREAMER_TAG_PICKUP:warungPickup,
	STREAMER_TAG_3D_TEXT_LABEL:warungLabel,
};

new WarungData[MAX_WARUNG][e_warung],
	Iterator:Warung<MAX_WARUNG>;

Warung_Refresh(id)
{
	if(id != -1)
	{
		if(DestroyDynamic3DTextLabel(WarungData[id][warungLabel]))
			WarungData[id][warungLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		
		if(DestroyDynamicPickup(WarungData[id][warungPickup]))
			WarungData[id][warungPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(WarungData[id][warungMap]))
			WarungData[id][warungMap] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(WarungData[id][warungType] == 1) // shop
		{
			WarungData[id][warungLabel] = CreateDynamic3DTextLabel("Tekan "GREEN"[Y]"WHITE" untuk membeli", -1, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2] + 0.55, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, WarungData[id][warungWorld], WarungData[id][warungInterior]);
			WarungData[id][warungMap] = CreateDynamicMapIcon(WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 17, -1, WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 1500.0, MAPICON_LOCAL, -1, 1);
			WarungData[id][warungPickup] = CreateDynamicPickup(2992, 23, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 2.5, -1, 0);
		}
		else if(WarungData[id][warungType] == 2) // elektronik
		{
			WarungData[id][warungLabel] = CreateDynamic3DTextLabel("Tekan "GREEN"[Y]"WHITE" untuk membeli", -1, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2] + 0.55, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, WarungData[id][warungWorld], WarungData[id][warungInterior]);
			WarungData[id][warungMap] = CreateDynamicMapIcon(WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 48, -1, WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 1500.0, MAPICON_LOCAL, -1, 1);
			WarungData[id][warungPickup] = CreateDynamicPickup(1277, 23, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 2.5, -1, 0);
		}
		else if(WarungData[id][warungType] == 3) // baju
		{
			WarungData[id][warungLabel] = CreateDynamic3DTextLabel("Tekan "GREEN"[Y]"WHITE" untuk membeli pakaian", -1, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2] + 0.55, 4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, WarungData[id][warungWorld], WarungData[id][warungInterior]);
			WarungData[id][warungMap] = CreateDynamicMapIcon(WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 45, -1, WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 1500.0, MAPICON_LOCAL, -1, 1);
			WarungData[id][warungPickup] = CreateDynamicPickup(1275, 23, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 3.0, -1, 0);
		}
	}
	return 1;
}

Warung_Nearest(playerid)
{
	foreach(new i : Warung) if (IsPlayerInRangeOfPoint(playerid, 3.0, WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]))
	{
		return i;
	}
	return -1;
}

WarungNearby(playerid)
{
	foreach(new i : Warung) if (WarungData[i][warungType] == 1)
	{
		static Float:X, Float:Y, Float:Z, Float:dist;
		GetPlayerPos(playerid, X, Y, Z);

		dist = GetDistanceBetweenPoints(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], X, Y, Z);

		if(dist <= 350.0)
		{
			return i;
		}
	}
	return -1;
}

ClothesStoreNearby(playerid)
{
	foreach(new i : Warung) if (WarungData[i][warungType] == 3)
	{
		static Float:X, Float:Y, Float:Z, Float:dist;
		GetPlayerPos(playerid, X, Y, Z);

		dist = GetDistanceBetweenPoints(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], X, Y, Z);

		if(dist <= 350.0)
		{
			return i;
		}
	}
	return -1;
}

ElectronicStoreNearby(playerid)
{
	foreach(new i : Warung) if (WarungData[i][warungType] == 2)
	{
		static Float:X, Float:Y, Float:Z, Float:dist;
		GetPlayerPos(playerid, X, Y, Z);

		dist = GetDistanceBetweenPoints(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], X, Y, Z);

		if(dist <= 350.0)
		{
			return i;
		}
	}
	return -1;
}

forward LoadWarung();
public LoadWarung()
{
	new id, rows = cache_num_rows();
	if(rows)
	{
		for(new i = 0; i < rows; i ++)
		{
			id = cache_get_field_int(i, "ShopID");
			WarungData[id][warungPOS][0] = cache_get_field_float(i, "ShopX");
			WarungData[id][warungPOS][1] = cache_get_field_float(i, "ShopY");
			WarungData[id][warungPOS][2] = cache_get_field_float(i, "ShopZ");
			WarungData[id][warungInterior] = cache_get_field_int(i, "ShopInterior");
			WarungData[id][warungWorld] = cache_get_field_int(i, "ShopWorld");
			WarungData[id][warungType] = cache_get_field_int(i, "ShopType");
			
			Warung_Refresh(id);
			Iter_Add(Warung, id);
			Profiler_Dump();
		}
		printf("[Dynamic Warung]: Jumlah total Warung yang dimuat %d.", rows);
	}
	return 1;
}

Warung_Save(id)
{
	new cQuery[525];
	format(cQuery, sizeof(cQuery), "UPDATE `warung` SET \ 
	`ShopX` = %f, `ShopY` = %f, `ShopZ` = %f, `ShopInterior` = %d, `ShopWorld` = %d \ 
	WHERE `ShopID` = %d", WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 
	WarungData[id][warungWorld], WarungData[id][warungInterior], id);
	return mysql_tquery(g_SQL, cQuery);
}

CMD:addwarung(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		id = Iter_Free(Warung),
		type,
		tss[525],
		Float:x,
		Float:y,
		Float:z
	;
	GetPlayerPos(playerid, x, y, z);

	if(sscanf(params, "d", type)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addshop [type]~n~1. Warung 2. Elektronik 3. Pakaian");
	if(type < 1 || type > 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Type!");
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah warung lagi!");

	if(type == 1) 
	{
		WarungData[id][warungPOS][0] = x;
		WarungData[id][warungPOS][1] = y;
		WarungData[id][warungPOS][2] = z;
		WarungData[id][warungType] = 1;
		WarungData[id][warungInterior] = GetPlayerInterior(playerid);
		WarungData[id][warungWorld] = GetPlayerVirtualWorld(playerid);

		Warung_Refresh(id);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Warung ID: %d", GetAdminName(playerid), id);
	}
	else if(type == 2)
	{
		WarungData[id][warungPOS][0] = x;
		WarungData[id][warungPOS][1] = y;
		WarungData[id][warungPOS][2] = z;
		WarungData[id][warungType] = 2;
		WarungData[id][warungInterior] = GetPlayerInterior(playerid);
		WarungData[id][warungWorld] = GetPlayerVirtualWorld(playerid);

		Warung_Refresh(id);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Warung Elektronik ID: %d", GetAdminName(playerid), id);
	}
	else if(type == 3)
	{
		WarungData[id][warungPOS][0] = x;
		WarungData[id][warungPOS][1] = y;
		WarungData[id][warungPOS][2] = z;
		WarungData[id][warungType] = 3;
		WarungData[id][warungInterior] = GetPlayerInterior(playerid);
		WarungData[id][warungWorld] = GetPlayerVirtualWorld(playerid);

		Warung_Refresh(id);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Membuat Dynamic Toko Baju ID: %d", GetAdminName(playerid), id);
	}
	Iter_Add(Warung, id);

	mysql_format(g_SQL, tss, sizeof(tss), "INSERT INTO `warung` SET `ShopID`=%d, `ShopX`=%f, `ShopY`=%f, `ShopZ`=%f, `ShopInterior`=%d, `ShopWorld`=%d, `ShopType`=%d",
	id, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungInterior], WarungData[id][warungWorld], WarungData[id][warungType]);
	mysql_tquery(g_SQL, tss, "OnWarungCreated", "dd", playerid, id);
	return 1;
}

CMD:removewarung(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new id, icsr[255];
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removewarung [id]");
	if(!Iter_Contains(Warung, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak ada!");
	if(id < 0 || id > MAX_WARUNG) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak valid!");

	WarungData[id][warungPOS][0] = WarungData[id][warungPOS][1] = WarungData[id][warungPOS][2] = 0.0;
	WarungData[id][warungInterior] = WarungData[id][warungWorld] = WarungData[id][warungType] = 0;

	Warung_Refresh(id);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Menghapus Dynamic Warung ID: %d", GetAdminName(playerid), id);

	Iter_Remove(Warung, id);
	mysql_format(g_SQL, icsr, sizeof(icsr), "DELETE FROM `warung` WHERE `ShopID` = %d", id);
	mysql_tquery(g_SQL, icsr);
	return 1;
}

CMD:gotowarung(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new id;
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotowarung [id]");
	if(!Iter_Contains(Warung, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak ada!");
	if(id < 0 || id > MAX_WARUNG) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak valid!");

	SetPlayerPos(playerid, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2]);
	SetPlayerInterior(playerid, WarungData[id][warungInterior]);
	SetPlayerVirtualWorld(playerid, WarungData[id][warungWorld]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Warung ID:%d", GetAdminName(playerid), id);
	return 1;
}

forward OnWarungCreated(playerid, id);
public OnWarungCreated(playerid, id)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat warung!");
	Warung_Save(id);
	return 1;
}

/* Hook */
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		new id = Warung_Nearest(playerid);
		if(id > -1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 1.5, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2]))
			{
				if(WarungData[id][warungType] == 1) 
				{
					ShowPlayerDialog(playerid, DIALOG_WARUNG, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""City"Happy Roleplay "WHITE"- Warung No.%02d", id), 
					"Nama Item\tHarga\
					\nNasi Uduk\t$250\
					\n"GRAY"Air Mineral\t"GRAY"$200\
					\nRokok (12 batang)\t$55\
					\n"GRAY"Korek Api\t"GRAY"$150\
					\nPancingan\t$80\
					\n"GRAY"Umpan\t"GRAY"$18\
					\nHelm\t$150\
					\n"GRAY"Masker\t"GRAY"$650\
					\nPilox\t$10000\
					\n"GRAY"Senter\t"GRAY"$1000", "Pilih", "Batal");
				}
				else if(WarungData[id][warungType] == 2)
				{
					ShowPlayerDialog(playerid, DIALOG_WARUNG_ELEKTRONIK, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""City"Happy Roleplay "WHITE"- Warung No.%02d", id),
					"Nama Item\tHarga\
					\nVervhone (Smartphone)\t$1800\
					\n"GRAY"Radio\t"GRAY"$950\
					\nEarphone\t$300\
					\n"GRAY"Boombox\t"GRAY"$500", "Pilih", "Batal");
				}
				else if(WarungData[id][warungType] == 3)
				{
					SetPlayerCameraFacingStore(playerid);
				}
			}
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_WARUNG_ELEKTRONIK:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			switch(listitem)
			{
				case 0: //smartphone
				{
					if(AccountData[playerid][pMoney] < 1800) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 1800);

					Inventory_Add(playerid, "Smartphone", 18870);
					ShowItemBox(playerid, "Received 1x", "Smartphone", 18870);
				}
				case 1: // Radio
				{
					// if(AccountData[playerid][pRadio]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki radio!");
					if(AccountData[playerid][pMoney] < 950) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 950);

					// AccountData[playerid][pRadio] = 1;
					Inventory_Add(playerid, "Radio", 19942);
					ShowItemBox(playerid, "Received 1x", "Radio", 19942);
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");

					/*new icsr[125];
					mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Radio`=1 WHERE `pID`=%d", AccountData[playerid][pID]);
					mysql_tquery(g_SQL, icsr);*/
					
				}
				case 2: //Earphone
				{
					if(AccountData[playerid][pEarphone]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki earphone!");	
					if(AccountData[playerid][pMoney] < 300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 300);

					AccountData[playerid][pEarphone] = 1;
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");

					new icsr[125];
					mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Earphone`=1 WHERE `pID`=%d", AccountData[playerid][pID]);
					mysql_tquery(g_SQL, icsr);
				}
				case 3: //bomboox
				{
					if(AccountData[playerid][pVip] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");
					if(AccountData[playerid][pMoney] < 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					if(PlayerHasItem(playerid, "Boombox")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki boombox!");

					TakeMoney(playerid, 500);
					Inventory_Add(playerid, "Boombox", 2103);
					ShowItemBox(playerid, "Received 1x", "Boombox", 2103);
				}
			}
		}
		case DIALOG_WARUNG:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			switch(listitem)
			{
				case 0: // nasi uduk
				{
					ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung", 
					"Anda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
				}
				case 1: //airmineral
				{
					ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung", 
					"Anda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
				}
				case 2: //Rokok
				{
					if(AccountData[playerid][pMoney] < 55) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 55);

					Inventory_Add(playerid, "Rokok", 19896, 12);
					ShowItemBox(playerid, "Received 12x", "Rokok", 19896);
				}
				case 3: //Korek api
				{
					if(AccountData[playerid][pMoney] < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 150);

					Inventory_Add(playerid, "Korek Api", 19998);
					ShowItemBox(playerid, "Received 1x", "Korek Api", 19998);
				}
				case 4: // Pancingan
				{
					if(AccountData[playerid][pMoney] < 80) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 80);

					Inventory_Add(playerid, "Pancingan", 18632);
					ShowItemBox(playerid, "Received 1x", "Pancingan", 18632);
				}
				case 5: // Umpan
				{
					ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung", 
					"Anda akan membeli umpan seharga "GREEN"$18/umpan\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli)", "Beli", "Batal");
				}
				case 6: //Helm
				{
					if(AccountData[playerid][pHelmet]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki helm!");
					if(AccountData[playerid][pMoney] < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 150);
					AccountData[playerid][pHelmet] = 1;
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");	
				}
				case 7: // masker
				{
					if(AccountData[playerid][pMoney] < 650) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 650);

					Inventory_Add(playerid, "Masker", 19036);
					ShowItemBox(playerid, "Received 1x", "Masker", 19036);
				}
				case 8:
				{
					if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 10000);

					Inventory_Add(playerid, "Pilox", 365);
					ShowItemBox(playerid, "Received 1x", "Pilox", 365);
				}
				case 9:
				{
					if(AccountData[playerid][pMoney] < 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 1000);

					Inventory_Add(playerid, "Senter", 18641);
					ShowItemBox(playerid, "Received 1x", "Senter", 18641);
				}
			}
		}
		case DIALOG_BUY_NASIUDUK:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		
			if(isnull(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Tidak dapat diisi kosong!\nAnda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(!IsNumeric(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Hanya dapat diisi angka!\nAnda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(strval(inputtext) < 1 || strval(inputtext) > (strval(inputtext) * 250))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Jumlah tidak valid!\nAnda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}
			new quantity = strval(inputtext);
			new value = quantity * 250;

			if(value > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, value);

			Inventory_Add(playerid, "Nasi Uduk", 19567, quantity);
			ShowItemBox(playerid, sprintf("Received %dx", quantity), "Nasi Uduk", 19567);
		}
		case DIALOG_BUY_AIRMINERAL:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		
			if(isnull(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Tidak dapat diisi kosong!\nAnda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(!IsNumeric(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Hanya dapat diisi angka!\nAnda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(strval(inputtext) < 1 || strval(inputtext) > (strval(inputtext) * 200))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Jumlah tidak valid!\nAnda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}
			new quantity = strval(inputtext);
			new value = quantity * 200;

			if(value > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, value);

			Inventory_Add(playerid, "Air Mineral", 19570, quantity);
			ShowItemBox(playerid, sprintf("Received %dx", quantity), "Air Mineral", 19570);
		}
		case DIALOG_BUY_UMPAN:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		
			if(isnull(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Tidak dapat diisi kosong!\nAnda akan membeli umpan seharga "GREEN"$18/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(!IsNumeric(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Hanya dapat diisi angka!\nAnda akan membeli umpan seharga "GREEN"$18/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(strval(inputtext) < 1 || strval(inputtext) > (strval(inputtext) * 18))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Warung",
				"Error: Jumlah tidak valid!\nAnda akan membeli umpan seharga "GREEN"$18/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}
			new quantity = strval(inputtext);
			new value = quantity * 18;

			if(AccountData[playerid][pMoney] < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, value);

			Inventory_Add(playerid, "Umpan", 1603, quantity);
			ShowItemBox(playerid, sprintf("Received %dx", quantity), "Umpan", 1603);
		}
	}
	return 1;
}