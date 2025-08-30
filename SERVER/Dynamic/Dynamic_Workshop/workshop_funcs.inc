#define MAX_WORKSHOP 100
enum E_WORKSHOP
{
	wName[50],
	wLeader[MAX_PLAYER_NAME],
	wPrice,
	wStatus,
	wMoney,
	Float:wExtposX,
	Float:wExtposY,
	Float:wExtposZ,
	Float:wExtposA,
	//Not Save
	Text3D:wLabel,
	wPickup,
	wIcon
};

new wData[MAX_WORKSHOP][E_WORKSHOP],
	Iterator:Workshop<MAX_WORKSHOP>;

Workshop_Save(id)
{
	new dquery[2048];
	format(dquery, sizeof(dquery), "UPDATE workshop SET name='%s', leader='%s', price='%d', status='%d',extposx='%f', extposy='%f', extposz='%f', extposa='%f'",
	wData[id][wName],
	wData[id][wLeader],
	wData[id][wPrice],
	wData[id][wStatus],
	wData[id][wExtposX],
	wData[id][wExtposY],
	wData[id][wExtposZ],
	wData[id][wExtposA]);

	format(dquery, sizeof(dquery), "%s, money='%d' WHERE ID='%d'",
	dquery,
	wData[id][wMoney],
	id);

	return mysql_tquery(g_SQL, dquery);
}

GetWorkshopNearest()
{
	new tmpcount;
	foreach(new id : Workshop)
	{
		if(Iter_Contains(Workshop, id))
		{
	     	tmpcount++;
	    }
	}
	return tmpcount;
}

ReturnWorkshopNearestID(slot)
{
	new tmpcount;
	if(slot < 1 && slot > MAX_WORKSHOP) return -1;
	foreach(new id : Workshop)
	{
		if(Iter_Contains(Workshop, id))
		{
	     	tmpcount++;
	       	if(tmpcount == slot)
	       	{
	        	return id;
	  		}
		}
	}
	return -1;
}



Workshop_Refresh(id)
{
	if(id != -1)
	{
		if(IsValidDynamic3DTextLabel(wData[id][wLabel]))
            DestroyDynamic3DTextLabel(wData[id][wLabel]);

        if(IsValidDynamicPickup(wData[id][wPickup]))
            DestroyDynamicPickup(wData[id][wPickup]);

        if(IsValidDynamicMapIcon(wData[id][wIcon]))
        	DestroyDynamicMapIcon(wData[id][wIcon]);

		new status[128];
		if(wData[id][wStatus] == 1)
		{
			status = "{FF0000}Closed";
		}
		else
		{
			status = "{00FF00}Opened";
		}
		new tstr[254];
        if(strcmp(wData[id][wLeader], "-"))
        {
			format(tstr, sizeof(tstr), "[WORKSHOP ID: %d]\n{ffffff}Workshop Name: {00ff00}%s\n{ffffff}Workshop Status: %s\n{ffffff}Owned by %s\n/wshelp ", id, wData[id][wName], status, wData[id][wLeader]);
            wData[id][wPickup] = CreateDynamicPickup(1239, 23, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.2, 0, 0, _, 50.0);
            wData[id][wLabel] = CreateDynamic3DTextLabel(tstr, COLOR_YELLOW, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.7, 5.0);
            wData[id][wIcon] = CreateDynamicMapIcon(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ], 27, -1, -1, -1, -1, 100.0);
        }
		else
		{
			format(tstr, sizeof(tstr), "[WORKSHOP ID: %d]\n{00FF00}This workshop for sell\n{FFFFFF}Location: {FFFF00}%s\n{FFFFFF}Price: {00FF00}%s\n"WHITE_E"Not Owner", id, GetLocation(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]), FormatMoney(wData[id][wPrice]));
            wData[id][wPickup] = CreateDynamicPickup(1239, 23, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.2, 0, 0, _, 50.0);
            wData[id][wLabel] = CreateDynamic3DTextLabel(tstr, COLOR_YELLOW, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.7, 5.0);
            wData[id][wIcon] = CreateDynamicMapIcon(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ], 27, -1, -1, -1, -1, 100.0);
		}
	}		
	return 1;
}

Player_OwnsWorkshop(playerid, id)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(id == -1) return 0;
	if(!strcmp(wData[id][wLeader], AccountData[playerid][pName], true)) return 1;
	return 0;
}

function LoadWorkshop()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new wid, name[50], leader[MAX_PLAYER_NAME];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", wid);
	    	cache_get_value_name(i, "name", name);
			format(wData[wid][wName], 50, name);
		    cache_get_value_name(i, "leader", leader);
			format(wData[wid][wLeader], MAX_PLAYER_NAME, leader);
			cache_get_value_name_int(i, "price", wData[wid][wPrice]);
			cache_get_value_name_int(i, "status", wData[wid][wStatus]);
		    cache_get_value_name_float(i, "extposx", wData[wid][wExtposX]);
		    cache_get_value_name_float(i, "extposy", wData[wid][wExtposY]);
		    cache_get_value_name_float(i, "extposz", wData[wid][wExtposZ]);
		    cache_get_value_name_float(i, "extposa", wData[wid][wExtposA]);
			cache_get_value_name_int(i, "money", wData[wid][wMoney]);

			/*for (new j = 0; j < 10; j ++)
			{
				format(str, 24, "Weapon%d", j + 1);
				cache_get_value_name_int(i, str, wData[wid][wGun][j]);

				format(str, 24, "Ammo%d", j + 1);
				cache_get_value_name_int(i, str, wData[wid][wAmmo][j]);
			}*/
			Workshop_Refresh(wid);
			Iter_Add(Workshop, wid);
			Profiler_Dump();
	    }
	    printf("[DATABASE] Number of Workshop loaded: %d.", rows);
		//Profiler_Stop();
	}
}

function WorkshopCreateRepairkit(playerid, wsid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] == wsid)
	{
		{
			if(IsPlayerInRangeOfPoint(playerid, 4.5, wData[wsid][wExtposX], wData[wsid][wExtposY], wData[wsid][wExtposZ]))
			{
				TogglePlayerControllable(playerid, 1);
				Info(playerid, "Kamu telah selesai membuat 1 repairkit.");
				Inventory_Remove(playerid, "Material", 20);
				Inventory_Add(playerid, "Repair Kit", 920, 1);
			}
		}
	}
	return 1;
}

function ShowWorkshopInfo(playerid)
{
	new rows = cache_num_rows();
 	if(rows)
  	{
 		new wname[50],
 			wleader[50],
			wmoney,
			string[512];
			
		cache_get_value_index(0, 0, wname);
		cache_get_value_index(0, 1, wleader);
		cache_get_value_index_int(0, 2, wmoney);

		format(string, sizeof(string), "Workshop ID: %d\nWorkshop Name: %s\nWorkshop Leader: %s\nWorkshop Money: %s",
		AccountData[playerid][pWorkshop], wname, wleader, FormatMoney(wmoney));
		
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Workshop Info", string, "Okay", "");
	}
}

function ShowWorkshopMember(playerid)
{
	new rows = cache_num_rows(), pid, username[50], frank, query[1048];
 	if(rows)
  	{
		for(new i = 0; i != rows; i++)
		{
			cache_get_value_index(i, 0, username);
			pid = GetID(username);
			
			format(query, sizeof(query), "%s"WHITE_E" %d. %s ", query, (i+1), username);
			
			if(IsPlayerConnected(pid))
				strcat(query, ""GREEN_E"(ONLINE)");
			else
				strcat(query, ""RED_E"(OFFLINE) ");
			
			cache_get_value_index_int(i, 1, frank);
			if(frank == 1)
			{
				strcat(query, ""WHITE_E"Trial Service(1)");
			}
			else if(frank == 2)
			{
				strcat(query, ""WHITE_E"Mechanic(2)");
			}
			else if(frank == 3)
			{
				strcat(query, ""WHITE_E"Pro Mechanic(3)");
			}
			else if(frank == 4)
			{
				strcat(query, ""WHITE_E"Staff(4)");
			}
			else if(frank == 5)
			{
				strcat(query, ""WHITE_E"Assistan Manager(5)");
			}
			else if(frank == 6)
			{
				strcat(query, ""WHITE_E"Manager(6)");
			}
			else
			{
				strcat(query, ""WHITE_E"None(0)");
			}
			strcat(query, "\n{FFFFFF}");
		}
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Workshop Member", query, "Okay", "");
	}
}

CMD:createws(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);
	
	new query[512];
	new wid = Iter_Free(Workshop);

	if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "You cant create more door!");
	new price;

	if(sscanf(params, "d", price)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/createws [price]");

	format(wData[wid][wLeader], 128, "-");
	format(wData[wid][wName], 128, "No Name");

	wData[wid][wPrice] = price;
	GetPlayerPos(playerid, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]);

	GetPlayerFacingAngle(playerid, wData[wid][wExtposA]);

	wData[wid][wMoney] = 0;
	wData[wid][wStatus] = 1;
  	
  	Workshop_Refresh(wid);

	Iter_Add(Workshop, wid);
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO workshop SET ID='%d', leader='%s', name='%s', price='%d'", wid, wData[wid][wLeader], wData[wid][wName], wData[wid][wPrice]);
	mysql_tquery(g_SQL, query, "OnWorkshopCreated", "i", wid);
	return 1;
}

function OnWorkshopCreated(wid)
{
	Workshop_Save(wid);
	return 1;
}

CMD:wsdelete(playerid, params[])
{
 	if(AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

    new wid, query[128];
	if(sscanf(params, "i", wid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsdelete [wid]");
	if(!Iter_Contains(Workshop, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "The you specified ID of doesn't exist.");
	
    format(wData[wid][wName], 50, "None");
	format(wData[wid][wLeader], 50, "None");

	wData[wid][wExtposX] = 0;
	wData[wid][wExtposY] = 0;
	wData[wid][wExtposZ] = 0;
	wData[wid][wExtposA] = 0;

	wData[wid][wMoney] = 0;
	
	DestroyDynamic3DTextLabel(wData[wid][wLabel]);
	DestroyDynamicPickup(wData[wid][wPickup]);
	DestroyDynamicMapIcon(wData[wid][wIcon]);
	
	Iter_Remove(Workshop, wid);
	
	mysql_format(g_SQL, query, sizeof(query), "UPDATE player_characters SET Char_Workshop=-1,Char_WorkshopRank=0,Char_OnDuty=0 WHERE Char_Workshop=%d", wid);
	mysql_tquery(g_SQL, query);
	
	foreach(new ii : Player)
	{
 		if(AccountData[ii][pWorkshop] == wid)
   		{
			AccountData[ii][pWorkshop]= -1;
			AccountData[ii][pWorkshopRank] = 0;
		}
	}

	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM workshop WHERE ID=%d", wid);
	mysql_tquery(g_SQL, query);
    SendStaffMessage(COLOR_RED, "Admin %s telah menghapus Workshop ID: %d.", AccountData[playerid][pAdminname], wid);
	return 1;
}

CMD:gotows(playerid, params[])
{
	new wid;
	if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", wid))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotows [id]");
	if(!Iter_Contains(Workshop, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "The Workshop you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ], wData[wid][wExtposA]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	SendClientMessageEx(playerid, COLOR_WHITE, "You has teleport to workshop id %d", wid);
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
	return 1;
}

CMD:wsedit(playerid, params[])
{
    static
        wid,
        type[24],
        string[128],
		otherid;

    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", wid, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [name] location, name, leader, position, money, component");
        return 1;
    }

    if((wid < 0 || wid >= MAX_WORKSHOP))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "You have specified an invalid ID.");

	if(!Iter_Contains(Workshop, wid)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "The you specified ID of doesn't exist.");

    if(!strcmp(type, "name", true))
    {
        new name[50];

        if(sscanf(string, "s[50]", name))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [name] [Workshop Name]");

        format(wData[wid][wName], 50, name);
		Workshop_Save(wid);
		Workshop_Refresh(wid);

        SendStaffMessage(COLOR_LRED, "Admin %s has changed the Workshop name ID: %d to: %s.", AccountData[playerid][pAdminname], wid, name);
    }
    else if(!strcmp(type, "leader", true))
    {
        if(sscanf(string, "d", otherid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [leader] [playerid]");
		
		if(otherid == INVALID_PLAYER_ID)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "invalid player wid");

        format(wData[wid][wLeader], 50, AccountData[otherid][pName]);
        AccountData[otherid][pWorkshop] = wid;
        AccountData[otherid][pWorkshopRank] = 6;
		Workshop_Save(wid);
		Workshop_Refresh(wid);

        SendStaffMessage(COLOR_LRED, "Admin %s has changed the Workshop leader ID: %d to: %s.", AccountData[playerid][pAdminname], wid, AccountData[otherid][pName]);
    }
    else if(!strcmp(type, "location", true))
    {
    	GetPlayerFacingAngle(playerid, wData[wid][wExtposA]);
        GetPlayerPos(playerid, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]);
        Workshop_Save(wid);
		Workshop_Refresh(wid);
		
		SendStaffMessage(COLOR_LRED, "Admin %s has changed the Workshop safepos ID: %d.", AccountData[playerid][pAdminname], wid);
    }
    else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [money] [ammount]");

        wData[wid][wMoney] = money;
		
        Workshop_Save(wid);
		Workshop_Refresh(wid);
		
		SendStaffMessage(COLOR_LRED, "Admin %s has changed the Workshop money ID: %d to %s.", AccountData[playerid][pAdminname], wid, FormatMoney(money));   
	}
    return 1;
}

CMD:wshelp(playerid)
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop");

	new str[3500];
	strcat(str, "Commands\tInformation\n");
	strcat(str, "/wsdesk\tUntuk membuka menu/locker list pada workshop\n"); 
	strcat(str, "/wsstorage\tUntuk menyimpan/memasukan barang\n"); 
	strcat(str, "/wsinvite\tUntuk menginvite seseorang menjadi anggota workshop\n");
	strcat(str, "/wskick\tUntuk mengeluarkan seseorang dari anggota workshop\n");
	strcat(str, "/wssetrank\tUntuk mengatur rank anggota workshop\n");
	strcat(str, "/wsmodif\tUntuk membuka menu modif kendaraan\n");
	strcat(str, "/wsann\tUntuk membuat pengumuman workshop\n");
	strcat(str, "/wscreate\tUntuk membuat tool kit dan repair kit\n");
	strcat(str, "/lockws\tUntuk merubah status Open/Closed pada worskhop");
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Workshop Commands", str, "Close","");
	return true;
}

CMD:wscreate(playerid)
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop");

	ShowPlayerDialog(playerid, DIALOG_BENGKEL_BRANKASITEM, DIALOG_STYLE_TABLIST_HEADERS, ""City"Happy Roleplay "WHITE"- Barang Bengkel", 
	"Nama Item\tKeterangan\
	\nRepair Kits\tUntuk memperbaiki mesin kendaraan dan juga body\
	\n"GRAY"Tools Kit\t"GRAY"Untuk memperbaiki mesin kendaraan tidak dengan body", "Pilih", "Batal");
	return 1;
}

CMD:wsdesk(playerid, const params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return Error(playerid, "Kamu bukan anggota workshop!");

	new wsid = AccountData[playerid][pWorkshop];

	if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wsid][wExtposX], wData[wsid][wExtposY], wData[wsid][wExtposZ]))
	{
		new string[254];
		format(string, sizeof(string), "Workshop Info\nToggle Duty\nMoney Storage ({00FF00}$%d)", wData[wsid][wMoney]);
		ShowPlayerDialog(playerid, WORKSHOP_MENU, DIALOG_STYLE_LIST, "Workshop Menu", string,"Next","Close");
	}
	else return Error(playerid, "Kamu bukan anggota workshop ini!");
	return 1;
}

CMD:wsstorage(playerid, const params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");

	new wsid = AccountData[playerid][pWorkshop];

	if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wsid][wExtposX], wData[wsid][wExtposY], wData[wsid][wExtposZ]))
	{
		AccountData[playerid][menuShowed] = true;
		ShowPlayerDialog(playerid, DIALOG_BENGVAULT, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Brankas Bengkel", 
		"Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
	}
	else return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop ini!");
	return 1;
}

CMD:lockws(playerid, const params[])
{
	if(AccountData[playerid][pWorkshopRank] < 5)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya rank 5 dan 6 yang bisa menutup workshop");

	foreach(new wid : Workshop)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
		{
			if(!Player_OwnsWorkshop(playerid, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "You don't own this workshop.");
			if(!wData[wid][wStatus])
			{
				wData[wid][wStatus] = 1;
				Workshop_Save(wid);
				Workshop_Refresh(wid);

				ShowTDN(playerid, NOTIFICATION_SUKSES, "You have closed your workshop!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				wData[wid][wStatus] = 0;
				Workshop_Save(wid);
				Workshop_Refresh(wid);

				ShowTDN(playerid, NOTIFICATION_SUKSES, "You have opened your workshop!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

CMD:wsinvite(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak bergabung workshop manapun");
		
	if(AccountData[playerid][pWorkshopRank] < 5)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You must workshop rank 5 - 6!");
	
	new otherid;
    if(sscanf(params, "u", otherid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsinvite [playerid/PartOwName]");
		
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
		
	if(!NearPlayer(playerid, otherid, 5.0))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "You must be near this player.");
	
	if(AccountData[otherid][pWorkshop] != -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut sudah bergabung workshop lain!");
		
	if(AccountData[otherid][pFaction] != 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak bisa menginvite anggota faction");

	AccountData[otherid][pWsInvite] = AccountData[playerid][pWorkshop];
	AccountData[otherid][pWsOffer] = playerid;
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda telah menginvite %s untuk menjadi anggota workshop.", AccountData[otherid][pName]));
	ShowTDN(otherid, NOTIFICATION_SUKSES, sprintf("%s telah menginvite anda untuk menjadi anggota workshop. Type: /accept workshop", AccountData[playerid][pName]));
	return 1;
}

CMD:wskick(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You are not in Workshop!");
		
	if(AccountData[playerid][pWorkshopRank] < 5)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You must Workshop level 5 - 6!");
	
	new otherid;
    if(sscanf(params, "u", otherid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wskick [playerid/PartOwName]");
		
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(AccountData[otherid][pWorkshopRank] > AccountData[playerid][pWorkshopRank])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You cant kick him.");
		
	AccountData[otherid][pWorkshopRank] = 0;
	AccountData[otherid][pWorkshop] = -1;
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda telah mengeluarkan %s dari anggota Workshop.", AccountData[otherid][pName]));
	ShowTDN(otherid, NOTIFICATION_SUKSES, sprintf("%s telah mengeluarkan anda dari anggota Workshop.", AccountData[playerid][pName]));
	return 1;
}

CMD:wssetrank(playerid, params[])
{
	new rank, otherid;
	if(AccountData[playerid][pWorkshopRank] < 6)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You must Workshop leader!");
		
	if(sscanf(params, "ud", otherid, rank))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wssetrank [playerid/PartOwName] [rank 1-6]");
	
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(AccountData[otherid][pWorkshop] != AccountData[playerid][pWorkshop])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "This player is not in your Workshop!");
	
	if(rank < 1 || rank > 6)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "rank must 1 - 6 only");
	
	AccountData[otherid][pWorkshopRank] = rank;
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("You has set %s Workshop rank to level %d", AccountData[otherid][pName], rank));
	ShowTDN(otherid, NOTIFICATION_SUKSES, sprintf("%s has set your Workshop rank to level %d", AccountData[playerid][pName], rank));
	return 1;
}

CMD:wsann(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pekerja workshop");

	new lstr[1024];
	format(lstr, sizeof(lstr), "{8D6D48}[BENGKEL] %s {FFFFFF}: %s", AccountData[playerid][pName], params);
	va_SendClientMessageToAll(-1, lstr);
	return 1;
}

CMD:wsmodif(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan pekerja workshop");
	{
		static minsty[512];
		if(AccountData[playerid][pMechVeh] == INVALID_VEHICLE_ID)
		{
			format(minsty, sizeof(minsty), ""WHITE"Ganti Warna Kendaraan\n");
			format(minsty, sizeof(minsty), "%s"GRAY"Velg Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Spoiler Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"GRAY"Hood Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Vents Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"GRAY"Lights Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Exhaust Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"GRAY"Front Bumper\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Rear Bumper\n", minsty);
			format(minsty, sizeof(minsty), "%s"GRAY"Roofs Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Side Kirts\n", minsty);
			format(minsty, sizeof(minsty), "%s"GRAY"Bullbars Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Hydraulic Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"GRAY"Nitro X3\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Nitro X5\n", minsty);
			format(minsty, sizeof(minsty), "%s"GRAY"Nitro X10\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Neon Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "%s"WHITE"Upgrade Kendaraan\n", minsty);
			format(minsty, sizeof(minsty), "\n%s"RED"> Remove Hydraulic\n", minsty);
			format(minsty, sizeof(minsty), "%s"RED"> Remove Nitro\n", minsty);
			ShowPlayerDialog(playerid, DIALOG_MODIF, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Modifikasi", minsty, "Pilih", "Batal");
		}
	}
	return 1;
}
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case WORKSHOP_MENU:
		{
			if(!response) return 1;
			new wid = AccountData[playerid][pWorkshop];

			new status[128];
			if(wData[wid][wStatus] == 1)
			{
				status = "{FF0000}Closed";
			}
			else
			{
				status = "{00FF00}Opened";
			}
			switch(listitem) 
			{
				case 0:
				{
					new mstr[248], lstr[512];
					format(mstr,sizeof(mstr),""WHITE_E"Workshop ID %d", wid);
					format(lstr,sizeof(lstr),""WHITE_E"Workshop Name:\t"RED_E"%s\n"WHITE_E"Workshop Status:\t%s\nWorkshop Member\t", wData[wid][wName], status);
					ShowPlayerDialog(playerid, WORKSHOP_INFO, DIALOG_STYLE_TABLIST, mstr, lstr,"Select","Close");
				}
				case 1:
				{
					if(AccountData[playerid][pOnDuty] == 1)
					{
						AccountData[playerid][pOnDuty] = 0;
						SetPlayerColor(playerid, COLOR_WHITE);
						SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
						SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s mengganti pakaian kerja dengan pakaian biasa", ReturnName(playerid));
					}
					else
					{
						AccountData[playerid][pOnDuty] = 1;
						SetPlayerColor(playerid, COLOR_WHITE);
						if(AccountData[playerid][pGender] == 1)
						{
							SetPlayerSkin(playerid, 268);
							AccountData[playerid][pFacSkin] = 268;
						}
						else
						{
							SetPlayerSkin(playerid, 69); //194
							AccountData[playerid][pFacSkin] = 69; //194
						}
						SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s mengambil pakaian kerja dari dalam locker dan langsung memakainya", ReturnName(playerid));
					}
				}
				case 2:
				{
					//Workshop Money
					ShowPlayerDialog(playerid, WORKSHOP_MONEY, DIALOG_STYLE_LIST, "Workshop Money", "Withdraw Money\nDeposit Money", "Select", "Back");
				}
			}
			return 1;
		}
		case WORKSHOP_INFO:
		{
			new wid = AccountData[playerid][pWorkshop];
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						if(AccountData[playerid][pWorkshopRank] < 6)
						return Error(playerid,"Hanya rank 6 yang bisa mengubah nama.");

						new mstr[248];
						format(mstr,sizeof(mstr),""WHITE_E"Nama Workshop: "RED_E"%s\n\n"WHITE_E"Masukkan nama workshop yang kamu inginkan\nMaksimal 32 karakter untuk nama workshop", wData[wid][wName]);
						ShowPlayerDialog(playerid, WORKSHOP_NAME, DIALOG_STYLE_INPUT,"Workshop Name", mstr,"Done","Back");
					}
					case 1:
					{
						return callcmd::lockws(playerid, "");
					}
					case 2:
					{
						if(AccountData[playerid][pWorkshop] == -1)
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");

						new query[512];
						mysql_format(g_SQL, query, sizeof(query), "SELECT Char_Name, Char_WorkshopRank FROM player_characters WHERE Char_Workshop = %d", AccountData[playerid][pWorkshop]);
						mysql_tquery(g_SQL, query, "ShowWorkshopMember", "i", playerid);
					}
				}
			}
			return 1;
		}
		case WORKSHOP_NAME:
		{
			if(response)
			{
				new wid = AccountData[playerid][pWorkshop];

				if(!Player_OwnsWorkshop(playerid, wid)) return Error(playerid, "You don't own this workshop.");
				
				if (isnull(inputtext))
				{
					new mstr[512];
					format(mstr,sizeof(mstr),""RED_E"NOTE: "WHITE_E"Nama Workshop tidak di perbolehkan kosong!\n\n"WHITE_E"Nama Workshop: "RED_E"%s\n\n"WHITE_E"Masukkan nama Workshop yang kamu inginkan\nMaksimal 32 karakter untuk nama Bisnis", wData[wid][wName]);
					ShowPlayerDialog(playerid, WORKSHOP_NAME, DIALOG_STYLE_INPUT,"Workshop Name", mstr,"Done","Back");
					return 1;
				}
				if(strlen(inputtext) > 32 || strlen(inputtext) < 5)
				{
					new mstr[512];
					format(mstr,sizeof(mstr),""RED_E"NOTE: "WHITE_E"Nama Workshop harus 5 sampai 32 karakter.\n\n"WHITE_E"Nama Workshop: "RED_E"%s\n\n"WHITE_E"Masukkan nama Workshop yang kamu inginkan\nMaksimal 32 karakter untuk nama Bisnis", wData[wid][wName]);
					ShowPlayerDialog(playerid, WORKSHOP_NAME, DIALOG_STYLE_INPUT,"Workshop Name", mstr,"Done","Back");
					return 1;
				}
				format(wData[wid][wName], 32, ColouredText(inputtext));

				Workshop_Refresh(wid);
				Workshop_Save(wid);

				ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Workshop name set to: \"%s\".", wData[wid][wName]));
			}
		}
		case WORKSHOP_MONEY:
		{
			if(response)
			{
				new wid = AccountData[playerid][pWorkshop];
				if(wid == -1) return Error(playerid, "Kamu bukan anggota workshop!");
				if(response)
				{
					switch (listitem)
					{
						case 0: 
						{
							if(AccountData[playerid][pWorkshopRank] < 5)
								return Error(playerid, "Hanya rank 5 dan 6 yang bisa mengambil ini!");
								
							new str[128];
							format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN_E"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to withdraw from the safe:", FormatMoney(wData[wid][wMoney]));
							ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw Money", str, "Withdraw", "Back");
						}
						case 1: 
						{
							new str[128];
							format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN_E"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to deposit into the safe:", FormatMoney(wData[wid][wMoney]));
							ShowPlayerDialog(playerid, WORKSHOP_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit Money", str, "Deposit", "Back");
						}
					}
				}
				else callcmd::wsdesk(playerid, "");
			}
			return 1;
		}
		case WORKSHOP_WITHDRAWMONEY:
		{
			new wid = AccountData[playerid][pWorkshop];
			if(wid == -1) return Error(playerid, "Kamu bukan anggota workshop!");
			
			if(response)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN_E"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to withdraw from the safe:", FormatMoney(wData[wid][wMoney]));
					ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw Money", str, "Withdraw", "Back");
					return 1;
				}
				if(amount < 1 || amount > wData[wid][wMoney])
				{
					new str[128];
					format(str, sizeof(str), ""RED_E"ERROR: "WHITE_E"Insufficient funds.\n\nMoney Balance: "GREEN_E"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to withdraw from the safe:", FormatMoney(wData[wid][wMoney]));
					ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw Money", str, "Withdraw", "Back");
					return 1;
				}
				wData[wid][wMoney] -= amount;
				GiveMoney(playerid, amount);

				Workshop_Save(wid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %s money from storage.", ReturnName(playerid), FormatMoney(amount));
				callcmd::wsdesk(playerid, "");
				return 1;
			}
			else callcmd::wsdesk(playerid, "");
			return 1;
		}
		case WORKSHOP_DEPOSITMONEY:
		{
			new wid = AccountData[playerid][pWorkshop];
			if(wid == -1) return Error(playerid, "Kamu bukan anggota workshop.");
			if(wData[wid][wMoney] > 1500000) return Error(playerid, "Penyimpanan sudah penuh!");

			if(response)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN_E"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to deposit into the safe:", FormatMoney(wData[wid][wMoney]));
					ShowPlayerDialog(playerid, WORKSHOP_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit Money", str, "Deposit", "Back");
					return 1;
				}
				if(amount < 1 || amount > AccountData[playerid][pMoney])
				{
					new str[128];
					format(str, sizeof(str), ""RED_E"ERROR: "WHITE_E"Insufficient funds.\n\nMoney Balance: "GREEN_E"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to deposit into the safe:", FormatMoney(wData[wid][wMoney]));
					ShowPlayerDialog(playerid, WORKSHOP_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit Money", str, "Deposit", "Back");
					return 1;
				}
				wData[wid][wMoney] += amount;
				GiveMoney(playerid, -amount);

				Workshop_Save(wid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %s money into storage.", ReturnName(playerid), FormatMoney(amount));
			}
			else callcmd::wsdesk(playerid, "");
		}
	}
	return 1;
}