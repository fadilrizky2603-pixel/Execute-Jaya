#include <YSI_Coding\y_hooks>
#define UANG_MINIMUN 10000  //Ini ada minimal uang di dapat dari rampok
#define UANG_MAXIMUM 80000//Ini ada maximal uang di dapat dari rampok
#define BOM_PRICE 20000  //Ini untuk harga bom
#define ROBBANK_RESTART 600000   //Ini waktu untuk restart system robbank setelah /plantbomb
enum Rob_Bank
{
	bool:BankVaultStatus,
	BankVault,
	Text3D:BankSafe[7],
    Text3D:BankBomb,
	bool:BankStatus[7],
    BankC4Object
}

new Float:SafePositions[7][3] =
{
    {-2126.0955,-32.6601,18.4475},
    {-2122.4985,-32.5808,18.4475},
    {-2119.6265,-32.9726,18.4475},
    {-2120.5078,-36.2819,18.4475},
    {-2122.8188,-39.2246,18.4475},
    {-2125.4878,-39.2236,18.4475},
    {-2128.5854,-39.6378,18.4475}
};

new RobBank[Rob_Bank];
hook OnGameModeInit()
{
	RobBank_Init();
}

forward RobBank_Destroy();
public RobBank_Destroy()
{
    DestroyDynamicObject(RobBank[BankVault]);
    RobBank[BankVaultStatus] = false;
    for(new idx = 0; idx<7; idx++)
    {
        DestroyDynamic3DTextLabel(RobBank[BankSafe][idx]);
        RobBank[BankStatus][idx] = false;
    }
}
RobBank_Init()
{
	RobBank[BankVault] = CreateDynamicObject(2634, -2130.27, -36.0915, 18.9575, 0.000000, 0.000000, 90.040008, -1, -1, -1, 300.00, 300.00); 
	RobBank[BankSafe][0] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"to take the money", -1, -2126.0955,-32.6601,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	RobBank[BankSafe][1] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"to take the money", -1, -2122.4985,-32.5808,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	RobBank[BankSafe][2] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"to take the money", -1, -2119.6265,-32.9726,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	RobBank[BankSafe][3] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"to take the money", -1, -2120.5078,-36.2819,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	RobBank[BankSafe][4] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"to take the money", -1, -2122.8188,-39.2246,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	RobBank[BankSafe][5] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"to take the money", -1, -2125.4878,-39.2236,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	RobBank[BankSafe][6] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"to take the money", -1, -2128.5854,-39.6378,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
    RobBank[BankBomb] = CreateDynamic3DTextLabel(""GREEN"USE "WHITE"to plant the bomb", -1, -2130.8911,-34.7848,18.4475+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	RobBank[BankVaultStatus] = false;
	for(new idx = 0; idx<7; idx++)
	{
		RobBank[BankStatus][idx] = false;
	}
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys & KEY_YES)
    {
        // Ambil uang dari brankas
        for (new i = 0; i < 7; i++)
        {
            if (IsPlayerInRangeOfPoint(playerid, 1.5, SafePositions[i][0], SafePositions[i][1], SafePositions[i][2]))
            {
                if (!RobBank[BankVaultStatus]) return SendClientMessage(playerid, -1, "Vault masih tertutup!");
                if (RobBank[BankStatus][i]) return SendClientMessage(playerid, -1, "Brankas ini sudah kosong!");
                if (AccountData[playerid][pRobBank] == 1) return SendClientMessage(playerid, -1, "Tunggu sebentar!");

                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.0, 1, 0, 0, 1, 0, 1);
                AccountData[playerid][pRobBank] = 1;
                SetTimerEx("TakeBrankasMoney", 5000, false, "dd", playerid, i);
                return 1;
            }
        }
    }
    return 1;
}

forward UpdateRobBank();
public UpdateRobBank()
{
    CreateExplosion(-2130.8911,-34.7848,18.4475, 0, 2);
    DestroyDynamicObject(RobBank[BankVault]);
    DestroyDynamicObject(RobBank[BankC4Object]);
    RobBank[BankVaultStatus] = true;
    SetTimer("RobBank_Destroy", ROBBANK_RESTART, false);
}

forward TakeBrankasMoney(playerid, type);
public TakeBrankasMoney(playerid, type)
{
    new rand = RandomEx(UANG_MINIMUN, UANG_MAXIMUM), robstr[128];
	UpdateDynamic3DTextLabelText(RobBank[BankSafe][type], 0xFF0000FF, "Penyimpana Sudah Kosong");
	RobBank[BankStatus][type] = true;

    AccountData[playerid][pRedMoney] = rand;
    format(robstr, sizeof(robstr), "ROBBANK: Kamu mendapatkan uang merah sebanyak $%d", rand);
    ShowTDN(playerid, NOTIFICATION_SUKSES, robstr);

	ClearAnimations(playerid);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    AccountData[playerid][pRobBank] = 0;
	return 1;
}