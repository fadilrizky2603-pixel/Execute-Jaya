/*

██╗  ██╗ █████╗ ██████╗ ██████╗ ██╗   ██╗    ██████╗  ██████╗ ██╗     ███████╗██████╗ ██╗      █████╗ ██╗   ██╗
██║  ██║██╔══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔══██╗██╔═══██╗██║     ██╔════╝██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝
███████║███████║██████╔╝██████╔╝ ╚████╔╝     ██████╔╝██║   ██║██║     █████╗  ██████╔╝██║     ███████║ ╚████╔╝ 
██╔══██║██╔══██║██╔═══╝ ██╔═══╝   ╚██╔╝      ██╔══██╗██║   ██║██║     ██╔══╝  ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  
██║  ██║██║  ██║██║     ██║        ██║       ██║  ██║╚██████╔╝███████╗███████╗██║     ███████╗██║  ██║   ██║   
╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝        ╚═╝       ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   
										GAMEMODE V2

Owner : Alstonn(irzam)
Developer : XenXen
 
	  Thanks For :	
	- Kalcor (samp)
	- Zeex (plugins crashdetectd)
	- Y_Less (ysi libarary)
	- dhan (developer is gamemode)
	- Bonti (give script & asking)
	- Agus (give script & asking)
	- Galang Indra (give script & asking)
	- etc.

Thanks all administartor and developer

*/

#pragma warning disable 239, 208, 209

#define CGEN_MEMORY             (20000)
#pragma dynamic 				(50000)

#define FOREACH_NO_BOTS         // Disabled the "NPC", "Bot", and "Character" from iterators.
#define FOREACH_NO_LOCALS       // Disabled the "LocalActor" and "LocalVehicle" from iterators.
#define YSI_NO_HEAP_MALLOC      // The AMX is much larger because the allocation pool is embedded in the file.

/* Includes */
#include <crashdetect>
#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 160

#include <memory>
#include <map-zones>

#include <a_mysql>
#include <a_zones>
#include <streamer>
#include <sscanf2> 
#include <gvar>

#include <YSI_Coding\y_timers>      		//by Y_Less from YSI
#include <YSI_Server\y_colours\x11def>      //by Y_Less from YSI
#include <YSI_Storage\y_ini>				//by Y_Less from YSI

#include <easyDialog> 
#include <Pawn.CMD>
#include <FiTimestamp>

#define ENABLE_3D_TRYG_YSI_SUPPORT
#include <3DTryg>
#include <EVF2>

#include <nex-ac>                   //BY Nexus
#include <nex-ac_id.lang> 

#include <strlib>                   //by Slice
#include <sampvoice>
#include <selection>
#include <garageblock>
#include <cb>
//#include <samp_bcrypt> 
//#include <KeyListener>

#include <textdraw-streamer>
#include <progress2>
#include <uicompas>
#include <GPS>
#include <WazeGPS>
#include <profiler>
#include <dialog-pages>

new Count = -1;
new countTimer;
new showCD[MAX_PLAYERS];
new CountText[5][5] =
{
	"~r~1",
	"~y~2",
	"~y~3",
	"~y~4",
	"~y~5"
};

new 
	WorldWeather = 1;

new MySQL: g_SQL;

enum
{
	NOTIFICATION_ERROR,
	NOTIFICATION_SUKSES,
	NOTIFICATION_WARNING,
	NOTIFICATION_INFO,
	NOTIFICATION_SYNTAX
};

enum 
{
	DEFAULT_XP = 5
};

/* Player Enums*/
enum E_PLAYERS
{
	pID,
	pUCP[22],
	pExtraChar,
	pChar,
	pName[MAX_PLAYER_NAME],
	pAdminname[MAX_PLAYER_NAME],
	pWorkshop,
	pWorkshopRank,
	pWsInvite,
	pWsOffer,
	pIP[16],
	pVerifyCode,
	pPassword[65],
	pSalt[65],
	pAdmin,
	pLevel,
	pLevelUp,
	pVip,
	pVipNameCustom[256],
	pVipTime,
	pRegDate[50],
	pLastLogin[50],
	pLastSpawn,
	pMoney,
	pRedMoney,
	STREAMER_TAG_3D_TEXT_LABEL:pMaskLabel,
	STREAMER_TAG_3D_TEXT_LABEL:pLabelDuty,
	pBankMoney,
	pSaldoGopay,
	pTargetGopay,
	pJumlahGopay,
	pBankRek,
	Smartphone,
	pPhone[32],
	pContact,
	pCall,
	pHours,
	pMinutes,
	pSeconds,
	pPaycheck,
	pSkin,
	pFacSkin,
	pGender,
	pUniform,
	pUsingUniform,
	pAge[50],
	pOrigin[32],
	pTinggiBadan,
	pBeratBadan,
	pInDoor,
	pInHouse,
	pInRusun,
	pInBiz,
	pInFamily,
	pRobBank,
	Float: pPosX,
	Float: pPosY,
	Float: pPosZ,
	Float: pPosA,
	pInt,
	pWorld,
	Float:pHealth,
    Float:pArmour,
	pHunger,
	pThirst,
	pHungerTime,
	pThirstTime,
	pStress,
	pStressTime,
	pInjured,
	pInjuredTime,
	pOnDuty,
	pFaction,
	pFactionRank,
	pTazer,
	pTaserGun,
	pLastShot,
	pShotTime,
	pStunned,
	pFamily,
	pFamilyRank,
	pJail,
	pJailTime,
	pJailReason[126],
	pJailBy[MAX_PLAYER_NAME],
	pArrest,
	pArrestTime,
	pWarn,
	pJob,
	pMask,
	pMaskID,
	pMaskOn,
	pHelmet,
	pGuns[13],
    pAmmo[13],
	pWeapon,
	Cache:Cache_ID,
	bool: IsLoggedIn,
	LoginAttempts,
	pSpawned,
	pAdminDuty,
	pAdminHide,

	//the star
	pTheStars,
	pTheStarsTime,

	pFreezeTimer,
	pFreeze,
	pSPY,
	pTogPM,
	pTogGlobal,
	pTogWT,
	Text3D:pAdoTag,
	bool:pAdoActive,
	
	pFlare,
	bool:pFlareActive,
	pFlareIcon[MAX_PLAYERS],

	pTrackCar,
	pTrackHoused,
	pCuffed,
	toySelected,
	bool:PurchasedToy,
	pEditingItem,
	pEditingAmmount,
	pProductModify,
	pCurrSeconds,
	pCurrMinutes,
	pCurrHours,
	pSpec,
	playerSpectated,
	pFriskOffer,
	pDragged,
	pDraggedBy,
	pDragTimer,
	pHelmetOn,
	pSeatBelt,
	pReportTime,
	pAskTime,
	pActivity,
	pActivityStatus,
	pActivityTime,
	Float: ActivityTime,
	Float: NotifyTime,
	pLoadingBar,
	pTimerLoading,
	pDiPesawat,
	//Jobs
	pSideJob,
	pSideJobTime,
	pSweeperTime,
	pBusTime,
	pMowerTime,
	pVehicleFaction,
	pMechVeh,
	pMechColor1,
	pMechColor2,
	EditingSAMPAHID,
	EditingPOMID,
	EditingATMID,
	EditingROBERID,
	EditingLADANGID,
	EditingUraniumID,
	EditingDeerID,
	bool: pOnBusJob,
	pTransfer,
	pTransferRek,
	pTransferName[128],
	gEditID,
	gEdit,
	pHead,
 	pPerut,
 	pLHand,
 	pRHand,
 	pLFoot,
 	pRFoot,
 	pDutyTimer,
	pPark,
	pACWarns,
	pACTime,
	pJetpack,
	pArmorTime,
	pLastUpdate,
	pBus,
	pSweeper,
	pMower,
	pSpeedTime,
	pLoopAnim,
	SelectBandara,
	SelectPelabuhan,
	SelectRusun,
	SelectRumah,
	SelectLastExit,
	pSelectItem,
	pListItem,
	pListItemGudang,
	pBagasiTake,
	pVehListItem,
	pStorageGudang,
	pGiveInv,
	pAmountInv,
	pPmin,
	pPsec,
	pBsec,
	pCSmin,
	pCSsec,
	pDipanggilan,
	pTargetAirdrop[10],
	pNamaAirdrop[32],
	pNomorAirdrop[32],
	pNominal,
	pRekening,
	pTargetFamily[10],
	pOnBadai,
	pGSec,
	pDutyPD,
	pDutyPemerintah,
	pDutyEms,
	pDutyBengkel,
	pDutyPedagang,
	pDutyGojek,
	pDutyTrans,
	pDutyKargo,
	pRespawnVehJob,
	pTimerRespawn,
	pTimerSpawnKanabis,
	pEditingPenumpang,
	pSignalTime,
	pEarphone,
	pRadio,
	pAsapRokok,
	pHisapRokok,
	pMancing,
	Float: pBeratItem,
	Float: pRusunCapacity,
	Float: pGudangCapacity,
	pJerigenUse,
	bool:pActionActive,
	pHasGudangID,
	pGudangRentTime,
	pOwnedRusun,
	Ktp,
	LastSpawn,
	Spawned,
	pRobSec,
	pRobMin,
	pPaycheckTime,
	pSimA,
	pSimB,
	pSimC,
	pSimATime,
	pSimBTime,
	pSimCTime,
	pGunLic,
	pGunLicTime,
	pHuntingLic,
	pHuntingLicTime,
	pStorageSelect,
	DownloadWhatsapp,
	DownloadSpotify,
	DownloadGojek,
	DownloadTwitter,
	EngineOn,
	pSpeedLimit,
	GarkotVehList,
	ClickSpawn,
	pInviteRusun,
	pInviteHouse,
	pInviteAccept,
	pKompensasi,
	pGoodMood,
	pOwnedHouse,
	pOpenBackpackTimer,
	pDealerVeh,
	pTempName[MAX_PLAYER_NAME],
	pTempValue,
	pTempVehID,
	pTempVehJobID,
	pTempSQLFactMemberID,
	pTempSQLFactRank,
	pTempSQLFamMemberID,
	pTempSQLFamRank,
	pTempText[320],
	pTempPlayerID,
	pTempCallNumber,
	pSKS,
	pSKSTime,
	pSKSNameDoc[128],
	pSKSRankDoc[128],
	pSKSReason[128],
	pSKCK,
	pSKCKTime,
	pSKCKNamePol[128],
	pSKCKRankPol[128],
	pSKCKReason[128],
	pBPJS,
	pBPJSTime,
	pBPJSLevel[128],
	pSKWB,
	pSKWBTime,
	pCarSeller,
    pCarOffered,
    pCarValue,
	pTogAutoEngine,
	phoneShown,
	pCaller,
	pDurringKarung,
	pTarget,
	pVehAudioPlay,
	hsAudioPlay,
	pHotlineTime,
	pTraceTime,
	TwitterName[128],
	TwitterPassword[128],
	Twitter,
	bool: pTurningEngine,
	bool: UsingDoor,
	bool: CurrentlyReadWA,
	bool: CurrentlyReadYellow,
	bool: CurrentlyReadTwitter,

	bool: EMSDuringReviving,

	pTrashmaster,
	pTrashmasterDelay,
	pLastVehicle,
	pDeliveryTime,
	pForkliftTime,

	/* Dragging */
	pDragOffer,
	pFriendHouseID,

	pFixmeTime,
	pTempOlah,
	pClaimStarterpack,

	bEditID,
	bEdit,

	pEditSlotID,

	/* Taxi Stuffs */
	pTaxiDuty,
	pTaxiOrder,
	pTaxiPlayer,
	pTaxiFee,
	pTaxiRunDistance,
	Float:tPos[3],
	
	//saving
	aReceivedReports,
	aDutyTimer,
	pFashionItem,

	//notsave
	bool: AirdropPermission,
	bool:phoneAirplaneMode,
	bool:phoneDurringConversation,
	bool:phoneIncomingCall,
	phoneCallingWithPlayerID,
	phoneCallingTime,
	phoneCallRingtone[128],

	pFactDutyTimer,
	Float:pMapSettings,
	pMapRender,
	pSuspectTimer,
	bool: menuShowed,
	playerClickSpawn,
	pTogSpy,
	OnlineTimer,
	bool: ToggleFPS,
	DokterLokalTimer,

	pCheckpoint,
	pXmasTime,
	pTogAC,
	pStyleNotif,
	
	pShowFooter,
	pFooterTimer,

	//Afk System
	Float:pAFKPos[6],
	pAFK,
	pAFKTime,
	pAFKCode,

	pEditTextObject,
	pHUDMode,
	bool: pNameTagShown,
	bool: pNtagShown,

	bool: pFlashShown,
	bool: pFlashOn,

	pJobVehicle,

	//whatsapp
	pWAMessage,
};
new AccountData[MAX_PLAYERS][E_PLAYERS];

enum
{
	DIALOG_MAKE_CHAR,
	DIALOG_DAMAGE_INPUT,
	DIALOG_DAMAGE_LIST,
	DIALOG_ACLIST,
	DIALOG_BALAP_MENU,
	DIALOG_BALAP_INVITE,
	DIALOG_BALAP_SAVE,
	DIALOG_BALAP_LIST,
	DIALOG_BASKET_GUIDE, 
	DIALOG_TEAM_MENU,
	DIALOG_TEAM_SELECT,
	DIALOG_TEAM_LIST,
	WORKSHOP_MONEY,
	WORKSHOP_MENU,
	WORKSHOP_NAME,
	WORKSHOP_INFO,
	WORKSHOP_DEPOSITMONEY,
	WORKSHOP_WITHDRAWMONEY,
	DIALOG_CHARLIST,
	DIALOG_VERIFYCODE,
	DIALOG_UNUSED,
    DIALOG_LOGIN,
    DIALOG_REGISTER,
    DIALOG_AGE,
	DIALOG_ORIGIN,
	DIALOG_TINGGIBADAN,
	DIALOG_BERATBADAN,
	DIALOG_GENDER,
	DIALOG_TOY,
	DIALOG_TOYEDIT,
	DIALOG_TOYEDIT_ANDROID,
	DIALOG_TOYPOSISI,
	DIALOG_TOYPOSISIBUY,
	DIALOG_TOYVIP,
	DIALOG_TOYPOSX,
	DIALOG_TOYPOSY,
	DIALOG_TOYPOSZ,
	DIALOG_TOYPOSRX,
	DIALOG_TOYPOSRY,
	DIALOG_TOYPOSRZ,
	DIALOG_TOYPOSSX,
	DIALOG_TOYPOSSY,
	DIALOG_TOYPOSSZ,
	DIALOG_HELP,
	DIALOG_EDITBONE,
	DIALOG_REPORTS,
	DIALOG_REPORTSREPLY,
	DIALOG_ASKS,
	DIALOG_ASKSREPLY,
	DIALOG_HEALTH,
	DIALOG_TDM,
	DIALOG_DISNAKER,
	DIALOG_MEMBERI,
	DIALOG_SETAMOUNT,
	DIALOG_MODIF,
	DIALOG_MODIF_VELG,
	DIALOG_MODIF_SPOILER,
	DIALOG_MODIF_HOODS,
	DIALOG_MODIF_VENTS,
	DIALOG_MODIF_LIGHTS,
	DIALOG_MODIF_EXHAUSTS,
	DIALOG_MODIF_FRONT_BUMPERS,
	DIALOG_MODIF_REAR_BUMPERS,
	DIALOG_MODIF_ROOFS,
	DIALOG_MODIF_SIDE_SKIRTS,
	DIALOG_MODIF_BULLBARS,
	DIALOG_MODIF_NEON,
	
	DIALOG_STREAMER_CONFIG,
	DANN_RENTAL,
	DANN_UNRENT,
	DANN_ASURANSI,
	DANN_BUYALATSTEAL,
	DANN_PILIHSPAWN,
	DANN_PICKUPVEH,
	DANN_DYNHELP,

	DIALOG_RUSUN,
	DIALOG_RUSUN_OWNED,
	DIALOG_RUSUN_BRANKAS,
	DIALOG_RUSUN_INVITE,
	DIALOG_RUSUN_INVITECONF,
	DIALOG_RUSUN_BROPTION,
	DIALOG_RUSUN_MENU,
	DIALOG_RUSUNOWNED,
	DIALOG_RUSUNOPENSTORAGE,
	DIALOG_RUSUNITEM,

	DIALOG_RUSUNVAULT_DEPOSIT,
	DIALOG_RUSUNVAULT_WITHDRAW,
	DIALOG_RUSUNVAULT_IN,
	DIALOG_RUSUNVAULT_OUT,
	
	DIALOG_KAYU_START,
	DIALOG_SUSU_START,
	DIALOG_MINYAK_START,
	DIALOG_AYAM_START,
	DIALOG_MOWER_START,
	DIALOG_STEAL_SHOP,
	DIALOG_IKEA_MENU,
	DIALOG_IKEA_BESI,
	DIALOG_IKEA_BERLIAN,
	DIALOG_IKEA_EMAS,
	DIALOG_IKEA_TEMBAGA,
	DIALOG_IKEA_AYAMKEMAS,
	DIALOG_IKEA_KAYUKEMAS,
	DIALOG_IKEA_GAS,
	DIALOG_IKEA_PAKAIAN,

	DIALOG_FARMER_OLAH,
	DIALOG_LOUNGES_MASAK,
	DIALOG_HUNTING_SELL,
	DIALOG_BAGASISTORAGE,

	DIALOG_GUDANG,
	DIALOG_GUDANGSTOP,
	DIALOG_GUDANGOPTION,
	DIALOG_GUDANGOWNED,
	DIALOG_GUDANGITEM,
	DIALOG_GUDANGDEPOSIT,
	DIALOG_GUDANGWITHDRAW,

	LokasiGps,
	LokasiUmum,
	LokasiPekerjaan,
	LokasiHobi,
	LokasiPertokoan,
	LokasiWorkshop,
	DialogWarung,
	BeliNasduk,
	BeliAqua,
	BeliUmpan,
	DialogGadget,
	DANN_BOOMBOX,
	DANN_BOOMBOX1,
	DialogSpotify,
	DialogSpotify1,
	DialogFish,
	DialogCargo,
	DialogSpawn,
	DialogDropItem,
	DialogTransfer,
	DialogTransfer1,
	DialogBankConfirm,
	DialogElist,
	// -----------
	DialogShowroom,
	DialogAsuransi,
	// -------------
	DialogKontak,
	DialogOpenContact,
	DialogContact,
	DialogTelepon,
	DialogContactMenu,
	DialogGarasiKota,
	DialogMyVeh,
	DialogTrackMyVeh,
	DialogBagasi,
	// -----------
	DialogToyEdit,

	DIALOG_CRAFTING,
	DIALOG_CRAFTINGCLIP,
	DIALOG_CRAFTINGCONF,
	DIALOG_CRAFTINGCLIPCONF,
	DIALOG_FAMILY_PANEL,
	DIALOG_FAMSTAKE_REDMONEY,
	DIALOG_FAMSTAKE_MONEY,
	DIALOG_FAMGARAGE_OUT,
	DIALOG_BLACKMARKET,
	
	DIALOG_DEPOSIT_POLICE,
	DIALOG_WITHDRAW_POLICE,

	DIALOG_POLVAULT,
	DIALOG_POLVAULT_DEPOSIT,
	DIALOG_POLVAULT_WITHDRAW,
	DIALOG_POLVAULT_IN,
	DIALOG_POLVAULT_OUT,

	DIALOG_POLICE_PANEL,
	DIALOG_POLICE_BOSDESK,
	DIALOG_POLICESETRANK,
	DIALOG_POLICEKICKMEMBER,
	DIALOG_RANK_SET_POLISI,
	DIALOG_POLICE_INVITE,
	DIALOG_POLICE_GARAGE,
	DIALOG_POLICE_GARAGE_BUY,
	DIALOG_POLICE_GARAGE_DEL,
	DIALOG_POLICE_HELI_GARAGE,
	DIALOG_POLICE_HELI_BUY,
	DIALOG_POLICE_HELI_GARAGE_OUT,
	DIALOG_POLICE_GARAGE_OUT,
	DIALOG_POLICE_IMPOUND,
	DIALOG_POLICE_TAKE_IMPOUND,
	DIALOG_FEDERAL_GARAGE,
	DIALOG_FEDERAL_GARAGE_BUY,
	DIALOG_FEDERAL_GARAGE_OUT,
	DIALOG_PDM,
	DIALOG_PDM_VEHICLE,
	DIALOG_PDM_VEHICLE_IMPOUND,
	DIALOG_PDM_OBJECT,
	DIALOG_ADD_HKRIMINAL,
	DIALOG_REMOVE_HKRIMINAL,
	
	DIALOG_EMS_PANEL,
	DIALOG_EMS_GARAGE,
	DIALOG_EMS_GARAGE_BUY,
	DIALOG_EMS_GARAGE_TAKEOUT,
	DIALOG_EMS_GARAGE_DELETE,
	DIALOG_EMSBRANKAS,
	DIALOG_EMSBKCONFIRM,
	DIALOG_EMS_BOSDESK,
	DIALOG_EMS_INVITE,
	DIALOG_EMS_LOCKER,
	DIALOG_EMS_CLOTHES,
	DIALOG_EMSSETRANK,
	DIALOG_EMSKICKMEMBER,
	DIALOG_RANK_SET_EMS,
	DIALOG_DEPOSIT_EMS,
	DIALOG_WITHDRAW_EMS,

	DIALOG_EMSVAULT,
	DIALOG_EMSVAULT_DEPOSIT,
	DIALOG_EMSVAULT_WITHDRAW,
	DIALOG_EMSVAULT_IN,
	DIALOG_EMSVAULT_OUT,
	// ------------------ PEMERINTAH
	DIALOG_PEMERINTAH_LOCKER,
	DIALOG_PEMERINTAH_LOCKERMALE,
	DIALOG_PEMERINTAH_LOCKERFEMALE,
	DIALOG_PEMERINTAH_PANEL,
	DIALOG_PEMERINTAH_BOSDESK,
	DIALOG_PEMERSETRANK,
	DIALOG_PEMERKICKMEMBER,
	DIALOG_RANK_SET_PEMERINTAH,
	DIALOG_PEMERINTAH_INVITE,
	DIALOG_PEMERINTAH_DEPOSIT,
	DIALOG_PEMERINTAH_WITHDRAW,
	DIALOG_PEMER_GARAGE,
	DIALOG_PEMER_GARAGE_BUY,
	DIALOG_PEMER_GARAGE_TAKEOUT,
	DIALOG_PEMER_GARAGE_DELETE,
	
	DIALOG_PEMERVAULT,
	DIALOG_PEMERVAULT_DEPOSIT,
	DIALOG_PEMERVAULT_WITHDRAW,
	DIALOG_PEMERVAULT_IN,
	DIALOG_PEMERVAULT_OUT,

	DIALOG_PEDSETRANK,
	DIALOG_PEDKICKMEMBER,
	DIALOG_RANK_SET_PEDAGANG,
	DIALOG_LOCKERPEDAGANG,
	DIALOG_PEDAGANG_GARAGE,
	DIALOG_PEDAGANG_GARAGE_BUY,
	DIALOG_PEDAGANG_GARAGE_TAKEOUT,
	DIALOG_PEDAGANG_GARAGE_DELETE,

	DIALOG_BENGKEL_PANEL,
	DIALOG_BENGKEL_LOCKER,
	DIALOG_BENGKEL_CLOTHES,
	DIALOG_BENGKEL_GARAGE,
	DIALOG_MODIF_COLOROPTION,
	DIALOG_MODIF_WARNA1,
	DIALOG_MODIF_WARNA2,
	DIALOG_MODIF_PAINTJOB,
	DIALOG_BENGKELBUYVEH,
	DIALOG_BENGKELTAKEVEH,
	DIALOG_BENGKEL_BRANKASOPTION,
	DIALOG_BENGKEL_BRANKASITEM,
	DIALOG_BENGKEL_BRANKASCONF,
	DIALOG_BENGKEL_BRANKASREPAIRKIT,
	DIALOG_BENGKEL_BRANKASTOOLSKIT,
	DIALOG_BENGKEL_BOSDESK,
	DIALOG_BENGKEL_INVITE,
	DIALOG_BENGKELSETRANK,
	DIALOG_BENGKELKICKMEMBER,
	DIALOG_RANK_SET_BENGKEL,
	DIALOG_BENGKELDELCAR,
	DIALOG_DEPOSIT_BENGKEL,
	DIALOG_WITHDRAW_BENGKEL,

	DIALOG_BENGVAULT,
	DIALOG_BENGVAULT_DEPOSIT,
	DIALOG_BENGVAULT_WITHDRAW,
	DIALOG_BENGVAULT_IN,
	DIALOG_BENGVAULT_OUT,

	DIALOG_BOSDESK_GOJEK,
	DIALOG_DEPOSIT_GOJEK,
	DIALOG_WITHDRAW_GOJEK,
	DIALOG_RANK_SET_GOJEK,
	DIALOG_GOJEK_INVITECONF,
	DIALOG_GOJEK_LOCKER,

	DIALOG_GOJEK_GARAGE,
	DIALOG_GOJEK_GARAGE_BUY,
	DIALOG_GOJEK_GARAGE_TAKEOUT,
	DIALOG_GOJEK_GARAGE_DELETE,

	DIALOG_GOJVAULT,
	DIALOG_GOJVAULT_DEPOSIT,
	DIALOG_GOJVAULT_WITHDRAW,		
	DIALOG_GOJVAULT_IN,	
	DIALOG_GOJVAULT_OUT,

	DIALOG_PAYGOJEK,
	DIALOG_PAYGOJEKAMOUNT,
	DIALOG_TOPUPGOJEK,
	DIALOG_PESANGORIDE,
	DIALOG_PESANGORIDECONF,
	DIALOG_PESANGOCAR,
	DIALOG_PESANGOCARPENUMPANG,
	DIALOG_PESANGOCARCONF,
	DIALOG_GOPAYWITHDRAW,
	
	DIALOG_GOFOOD_PESAN,
	DIALOG_PESAN_NASIGORENG,
	DIALOG_PESAN_BAKSO,
	DIALOG_PESAN_NASIPECEL,
	DIALOG_PESAN_BUBUR,
	DIALOG_PESAN_SUSU,
	DIALOG_PESAN_ESTEH,
	DIALOG_PESAN_KOPI,
	DIALOG_PESAN_CHOCOMATCH,
	DIALOG_PESAN_NOTES,
	
	DIALOG_ITEM_PICKUP,

	DIALOG_FAMSVAULT,
	DIALOG_FAMSVAULT_DEPOSIT,
	DIALOG_FAMSVAULT_WITHDRAW,
	DIALOG_FAMSRM_VAULT,
	DIALOG_FAMSRM_DEPOSIT,
	DIALOG_FAMSRM_WITHDRAW,
	DIALOG_FAMSVAULT_IN,
	DIALOG_FAMSVAULT_OUT,
	DIALOG_FAMSBRANKAS,
	DIALOG_FAMS_WEAPON,
	DIALOG_FAMILIESSETRANK,
	DIALOG_FAMILIESKICKMEMBER,
	DIALOG_RANK_SET_FAMILIES,

	DIALOG_VEHICLE_MENU,
	DIALOG_VHOLSTER,
	DIALOG_VHOLSTER_WITHDRAW,

	DIALOG_SPORTSTORE,

	/* Trans Dialog */
	DIALOG_TRANSORDER,
	DIALOG_TRANS_LOCKER,
	DIALOG_TRANS_DESK,
	DIALOG_TRANSSETRANK,
	DIALOG_TRANSKICKMEMBER,
	DIALOG_RANK_SET_TRANS,
	DIALOG_TRANS_INVITECONF,
	DIALOG_DEPOSIT_TRANS,
	DIALOG_WITHDRAW_TRANS,
	DIALOG_TRANS_GARAGE,
	DIALOG_TRANS_GARAGE_TAKEOUT,
	DIALOG_TRANS_GARAGE_BUY,
	DIALOG_TRANS_GARAGE_DELETE,

	DIALOG_TRANSVAULT,
	DIALOG_TRANSVAULT_DEPOSIT,
	DIALOG_TRANSVAULT_WITHDRAW,
	DIALOG_TRANSVAULT_IN,
	DIALOG_TRANSVAULT_OUT,

	/*Bagasi Dialog*/
	DIALOG_BAGASI,
	DIALOG_BAGASI_DEPOSIT,
	DIALOG_BAGASI_IN,
	DIALOG_BAGASI_WITHDRAW,
	DIALOG_BAGASI_OUT,

	/*Event Dialog*/
	DIALOG_EVENT_SETTING,
	DIALOG_EVENT_REDSKIN,
	DIALOG_EVENT_REDWEAP1,
	DIALOG_EVENT_REDWEAP2,
	DIALOG_EVENT_REDWEAP3,

	DIALOG_EVENT_BLUESKIN,
	DIALOG_EVENT_BLUEWEAP1,
	DIALOG_EVENT_BLUEWEAP2,
	DIALOG_EVENT_BLUEWEAP3,

	DIALOG_EVENT_WWID,
	DIALOG_EVENT_INTID,
	DIALOG_EVENT_TIME,
	DIALOG_EVENT_TARGETSCORE,
	DIALOG_EVENT_PARTICIPRIZE,
	DIALOG_EVENT_PRIZE,
	DIALOG_EVENT_HEALTH,
	DIALOG_EVENT_ARMOUR,

	/* Dialog Aridrop */
	DIALOG_AIRDROP,
	DIALOG_AIRDROPDISPLAY,
	DIALOG_AIRDROP_CONF,
	DIALOG_ADD_CONTACT,
	DIALOG_ADD_CONTACTNUMB,
	DIALOG_EDIT_CONTACTNAME,
	DIALOG_EDIT_CONTACTNUMBER,

	/* Dialog Garasi Umum */
	DIALOG_GARKOT_OUT,

	/* Dialog Gudang */
	DIALOG_GUDANG_BUY,
	DIALOG_GUDANG_OPTION,
	DIALOG_GUDANGVAULT,
	DIALOG_GUDANGVAULT_DEPOSIT,
	DIALOG_GUDANGVAULT_WITHDRAW,
	DIALOG_GUDANGVAULT_IN,
	DIALOG_GUDANGVAULT_OUT,

	/* Score Board Admin Menu */
	DIALOG_CLICKPLAYER,
	DIALOG_BANNEDTIME,
	DIALOG_BANNEDREASON,

	/* Dialog Asuransi */
	DIALOG_ASURANSI_LS,
	DIALOG_ASURANSI_LV,

	/* Dialog Fact Garage */
	DIALOG_FACTION_GARAGE_MENU,
	DIALOG_FACTION_GARAGE1,
	DIALOG_FACTION_GARAGE2,
	DIALOG_FACTION_GARAGE3,
	DIALOG_FACTION_GARAGE4,
	DIALOG_FACTION_GARAGE5,
	DIALOG_FACTION_GARAGE6,

	/* Dialog warung */
	DIALOG_WARUNG,
	DIALOG_WARUNG_ELEKTRONIK, 
	DIALOG_BUY_NASIUDUK,
	DIALOG_BUY_AIRMINERAL, 
	DIALOG_BUY_UMPAN,

	/* Petani Dialog */
	DIALOG_BUY_SEEDS,
	DIALOG_BIBIT_PADI,
	DIALOG_BIBIT_TEBU,
	DIALOG_BIBIT_CABE,

	/* Dialog House Keys */
	DIALOG_HKEYS, 
	DIALOG_HKEYS_ADD,
	DIALOG_HKEYS_REMOVE,
	DIALOG_HOUSEGARAGE_OUT,
	DIALOG_HOUSEHELIPAD_OUT,
	DIALOG_HOUSE_BRANKAS,
	DIALOG_HOUSE_INVITE,
	DIALOG_HOUSE_INVITECONF,
	DIALOG_HOUSEVAULT,
	DIALOG_HOUSEVAULT_DEPOSIT,
	DIALOG_HOUSEVAULT_WITHDRAW,
	DIALOG_HOUSEVAULT_IN,
	DIALOG_HOUSEVAULT_OUT,
	DIALOG_WEAPON_CHEST,

	DIALOG_FIXMEACC,
	DIALOG_ADMIN_HELP,
	DIALOG_DYNAMIC_HELP,

	DIALOG_SWEEPER_START,
	DIALOG_DELIVERY_START,
	DIALOG_FORKLIFT_START,
	DIALOG_RECYCLER_START,
	DIALOG_TRASHMASTER_START,

	/* Dialog Clothes */
	DIALOG_CLOTHES,
	DIALOG_CLOTHES_DELETE,

	/* Atms Dialog */
	DIALOG_ATM_WITHDRAW,
	DIALOG_ATM_DEPOSIT,
	DIALOG_ATM_TRANSFER,
	DIALOG_ATM_TRANSFER1,

	/* Carsteal Dialog */
	DIALOG_CARSTEAL_SHOP,

	/*Whatsapp Dialog*/
	DIALOG_WHATSAPP_CHAT,
	DIALOG_WHATSAPP_CHAT_EMPTY,
	DIALOG_WHATSAPP_SEND,

	/*Yellow Pages*/
	DIALOG_YELLOW_PAGE,
	DIALOG_YELLOW_PAGE_MENU,
	DIALOG_YELLOW_PAGE_EMPTY,
	DIALOG_YELLOW_PAGE_SEND,
	DIALOG_YELLOW_CALL,

	/*Tweets Dialog*/
	DIALOG_TWITTER_SIGN,
	DIALOG_TWITTER_SIGNPASSWORD,
	DIALOG_TWITTER_LOGIN,
	DIALOG_TWITTER_LOGINPASSWORD,
	DIALOG_TWITTER_POST,
	DIALOG_TWITTER_POST_EMPTY,
	DIALOG_TWITTER_POST_SEND,

	/*Invoice Dialog*/
	DIALOG_INVOICE_NAME,
    DIALOG_INVOICE_COST,
    DIALOG_PAY_INVOICE,

	/*Player dialog*/
	DIALOG_PLAYER_MENU,
	DIALOG_PLAYER_DOKUMENT,

	/*Job Mixer Dialog*/
	DIALOG_MIXER,

	DIALOG_SELECT_SPAWN,
	DIALOG_SELECT_SPAWNEXPIRED,

	DIALOG_SHOWROOM_MENU,
	DIALOG_SHOWROOM_SELL,

	DIALOG_WEAPONSHOP,
	DIALOG_VIP_NAME,
	DIALOG_SELLFISH_ILEGAL,
	DIALOG_DISPLAYBANNED,
	DIALOG_RADIO_FREQ,
	DIALOG_VOICEMODE,
	DIALOG_VOICEKEYS,
	DIALOG_INVENTORY,
	DIALOG_CHANGE_PASSWORD,
	DIALOG_MYV_MENU,
	DIALOG_VEHICLE_DETAIL,
	DIALOG_UPGRADE,
	DIALOG_MODSHOP,
}

new AksesorisHat[87] =
{
	18953, 18954, 19554, 18960, 18974, 19067, 19068, 19069, 18891, 18892, 18893, 18894, 18895, 18896, 18897, 18898, 18899, 18900, 18908,
	18940, 18939, 18941, 18942, 18943, 19160, 18636, 18926, 18927, 18928, 18929, 18930, 18931, 18932, 18933, 18934, 18935, 18952, 18976, 18977, 
	18979, 19077, 19517, 19161, 19162, 2054, 18961, 18964, 18965, 18966, 19558, 18955, 18956, 18957, 18958, 18959, 18638, 19520, 18947, 18948, 
	19064,19065, 19066, 18975, 19516, 18639, 18645, 18962, 19095, 19096, 19099, 19100, 19487, 19136, 19330, 19331, 19137, 19528, 19093,
	3002, 3000, 3100, 3105, 3104, 3101, 3102, 3103, 3002,
};

new BackpackToys[7] = 
{
	11745, 19559, 1550, 3026, 371, 1210, 11738,
};

new GlassesToys[33] = 
{
	19138, 19139, 19140, 19006, 19007, 19008, 19009, 19010, 19011, 19012, 19013, 19014, 19015, 19016, 19017, 19018,
	19019, 19020, 19021, 19022, 19023, 19024, 19025, 19026, 19027, 19028, 19029, 19030, 19031, 19032, 19033, 19034, 19035,
};

new AksesorisToys[38] = 
{
	19515, 19142, 19621, 19623, 
	19584, 19591, 19592, 2226, 19878, 
	19038, 19036, 19163, 18919, 18912, 
	18913, 18914, 18915, 18916, 18917, 
	18918, 18911, 18920, 11704, 19037, 
	19317, 19318, 336, 339, 325, 19625,
	19801, 19163, 19904, 2226, 2487, 2614,
	11712, 18635,
};

new ClothesSkinMale[177] = 
{
	1, 2, 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 32, 33, 34, 35, 36, 37, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 58, 59, 60, 61,
	62, 66, 67, 68, 71, 72, 73, 78, 79, 80, 81, 82, 83, 84, 86, 94, 95, 96, 97, 98, 100,
	101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
	117, 118, 120, 122, 123, 124, 125, 126, 127, 128, 132, 133, 134, 135, 136, 137, 142, 
	143, 144, 146, 147, 149, 153, 154, 156, 158, 159, 160, 161, 162, 168, 170, 173, 174,
	175, 176, 177, 179, 180, 182, 183, 184, 185, 186, 187, 200, 202, 203, 204, 206,
	208, 209, 210, 212, 213, 217, 220, 221, 222, 223, 229, 230, 234, 235, 236, 239, 240,
	241, 242, 247, 248, 249, 250, 252, 253, 254, 255, 258, 259, 260, 261, 262, 264, 269,
	270, 271, 272, 273, 289, 290, 291, 292, 293, 296, 297, 299
};

new ClothesSkinFemale[60] = 
{
	9, 10, 11, 12, 13, 31, 38, 39, 40, 41, 53, 54, 55, 56, 63, 64, 65, 69, 75, 76, 77, 87,
	88, 89, 90, 91, 93, 129, 130, 131, 138, 139, 140, 145, 148, 151, 152, 157, 169, 178, 191,
	193, 192, 195, 196, 197, 198, 199, 205, 207, 211, 214, 216, 219, 224, 225, 226, 233, 237, 
	251
};

stock const Float: SpawnPelabuhan[][] = {
	{2744.2397,-2449.5349,13.6950,271.9706},
	{2744.3171,-2457.2017,13.6950,268.3150},
	{2738.2039,-2454.5254,13.6950,269.7540}
};

stock const Float: SpawnBandara[][] = {
	{1694.7468, -2332.3428, 13.5469, 0.0377},
	{1698.4928, -2329.6863, 13.5469, 49.2119}
};

stock const Float: SpawnVenturas[][] = {
	{1677.6498, 1447.7649, 10.7757, 271.1616},
	{1674.8794, 1444.2119, 10.7890, 270.9187}
};

#include "SERVER/utils/utils_defines"
#include "SERVER/utils/utils_vehiclevars"
#include "SERVER/utils/utils_enums"
#include "SERVER/utils/utils_variable"
#include "SERVER/utils/utils_colours"
#include "SERVER/utils/utils_textdraws"
#include "SERVER/voucher/voucher_functions"

#include "SERVER/systems/Pickup"
#include "SERVER/systems/JobVehicles"

/*Clothes System*/
#include "SERVER/toys/toys"
#include "SERVER/toys/toys_helmet"
#include "SERVER/clothes/clothes_functions"

#include "SERVER/fuel_system/fuel_functions"
//#include "SERVER/PlayerStuff/player_slot"
#include "SERVER/Gym/gym_functions"

#include "SERVER/Dynamic/Dynamic_SpeedCam/core"
#include "SERVER/Dynamic/Dynamic_SpeedCam/funcs"
#include "SERVER/Dynamic/Dynamic_SpeedCam/cmd"
#include "SERVER/Dynamic/Dynamic_Button/button_functions"
#include "SERVER/Dynamic/Dynamic_Actor/ui_dynactor"
#include "SERVER/Dynamic/Dynamic_Warung/warung_functions"
#include "SERVER/Dynamic/Dynamic_Pasar/dyn_pasar"
#include "SERVER/Dynamic/Dynamic_Robbery/robbery_functions"
#include "SERVER/area/area"
#include "SERVER/Dynamic/Dynamic_Hunting/hunting_functions"
#include "SERVER/Dynamic/Dynamic_Ladang/ui_dynkanabis"
#include "SERVER/Dynamic/Dynamic_Ladang/kanabis_olah"
#include "SERVER/Dynamic/Dynamic_Object/object_funcs"


#include "SERVER/Dynamic/Dynamic_GarasiKota/Header"
#include "SERVER/Dynamic/Dynamic_GarasiKota/Function"
#include "SERVER/Dynamic/Dynamic_GarasiKota/Commands"


#include "SERVER/Dynamic/Dynamic_Atm/ui_atm"
#include "SERVER/Dynamic/Dynamic_Garbage/dynamic_garbage"
#include "SERVER/Dynamic/Dynamic_Door/dynamic_doors"
#include "SERVER/Dynamic/Dynamic_Gate/dynamic_gatev2"
#include "SERVER/Dynamic/Dynamic_Gudang/gudang_functions"
#include "SERVER/Dynamic/Dynamic_Label/label_functions"

// Map Icon
#include "SERVER/Dynamic/Dynamic_IconMap/Header"
#include "SERVER/Dynamic/Dynamic_IconMap/Function"
#include "SERVER/Dynamic/Dynamic_IconMap/Commands"

//#include "SERVER/Dynamic/Dynamic_Machine/dynamic_slot"
#include "SERVER/Dynamic/Dynamic_ObjectText/objecttext"
#include "SERVER/Dynamic/Dynamic_Uranium/uranium_funcs"
#include "SERVER/Dynamic/Dynamic_Workshop/workshop_funcs"
// #include "SERVER/Dynamic/Dynamic_FactionStuffs/dynamic_factiongarage.inc"

#include "SERVER/jobs/farmer/petani_functions"

#include "SERVER/systems/systems_clip"
#include "SERVER/systems/systems_robbank"
//#include "SERVER/systems/systems_circle"

#include "SERVER/inventory/inventory_functions"
#include "SERVER/inventory/inventory_cmds"
#include "SERVER/inventory/inventory_drop"

#include "SERVER/voice/radiosystem"

// ------------------------------------------
#include "SERVER/user-interface/ui_animations"
#include "SERVER/user-interface/notifikasi/Header.pwn"
#include "SERVER/user-interface/notifikasi/Function.pwn"
#include "SERVER/user-interface/notifikasi/box_func"
#include "SERVER/user-interface/ui_shortkeys"
#include "SERVER/user-interface/ui_smoking"
#include "SERVER/user-interface/ui_ancc"
#include "SERVER/user-interface/ui_warning"

#include "SERVER/Dynamic/Dynamic_Rusun/rusun_functions"
#include "SERVER/Dynamic/Dynamic_House/dyn_house"

#include "SERVER/PlayerStuff/PlayerAFK"
#include "SERVER/PlayerStuff/IdleAnimation"
#include "SERVER/PlayerStuff/NameTag"
#include "SERVER/PlayerStuff/player_login"

/*PhoneSystem*/
#include "SERVER/FractionPlayer/FAMILIES/families_functions"
// #include "SERVER/FractionPlayer/FAMILIES/families_garage.inc"

#include "SERVER/jobs/miner/minerv2_functions"
#include "SERVER/jobs/lumberjack/lumber_functions"
#include "SERVER/jobs/bus/bus_funcs"
#include "SERVER/jobs/chicken factory/butcher_functions"
#include "SERVER/jobs/milker/milker_functions"
#include "SERVER/jobs/oilman/oilman_function"
#include "SERVER/jobs/fisherman/nelayan_funcs"
#include "SERVER/jobs/delivery/deliveryside_functions"
#include "SERVER/jobs/mowingjob/mowerside_functions"
#include "SERVER/jobs/sweeper/sweeper_functions"
#include "SERVER/jobs/forklift/forkliftside_functions"
#include "SERVER/jobs/tailor/tailorv2_functions"
#include "SERVER/jobs/tailor/tailor_forward"
#include "SERVER/jobs/hauling/kargo_func"
#include "SERVER/jobs/RicycleJob/recycler_functions"
#include "SERVER/jobs/trashmaster/trashmaster_functions"
#include "SERVER/jobs/electrican/electric_funcs"
#include "SERVER/jobs/mixer/callback"

#include "SERVER/Dynamic/Dynamic_Garbage/rongsokan_functions"
#include "SERVER/PlayerSmartphone/smartphone_contacts"
#include "SERVER/PlayerSmartphone/phone_funcs"

#include "SERVER/vehiclemod/modshop"
#include "SERVER/vehicles/vehicles_functions"
#include "SERVER/vehicles/vehicles_cmds"

#include "SERVER/weapons/weapons_functions"

#include "SERVER/Dynamic/Dynamic_Rental/dyn_rental"

#include "SERVER/FractionPlayer/stuff_goodside"

#include "SERVER/toko-olahraga/business_olahraga"

/* Factions */
#include "SERVER/FractionPlayer/FactionMenu"
#include "SERVER/FractionPlayer/Pemerintah/pemerintah_functions"
#include "SERVER/FractionPlayer/Bengkel/bengkel_brankas"
#include "SERVER/FractionPlayer/Bengkel/bengkel_functions"
#include "SERVER/FractionPlayer/Pedagang/lounges_brankas"
#include "SERVER/FractionPlayer/Pedagang/lounges_vars"
#include "SERVER/FractionPlayer/Pedagang/lounges_functions"
#include "SERVER/FractionPlayer/EMS/ems_brankas"
#include "SERVER/FractionPlayer/EMS/ems"
// #include "SERVER/FractionPlayer/EMS/medic_funcs"
#include "SERVER/FractionPlayer/Police/sapd_functions"
// #include "SERVER/FractionPlayer/Police/sapd_taser"
// #include "SERVER/FractionPlayer/Police/sapd_spike"
#include "SERVER/FractionPlayer/trans/trans_functions"
#include "SERVER/FractionPlayer/trans/trans_stuffs"
// #include "SERVER/FractionPlayer/Gojek/cmds_gojek"
// #include "SERVER/FractionPlayer/Gojek/gojek_functions"

#include "SERVER/reports/systems_ask"
#include "SERVER/reports/systems_reports"

#include "SERVER/events/admin_events.inc"
#include "commands/cmds_hooks"
#include "SERVER/systems/systems_anticbug"
#include "SERVER/systems/systems_dialogs"
// #include "SERVER/systems/systems_spawn.inc" Dimatikan sementara
#include "SERVER/systems/systems_functions"
#include "SERVER/systems/systems_native"
// #include "SERVER/systems/systems_anticheat.inc"
#include "SERVER/systems/systems_anticheatv2"
#include "SERVER/systems/systems_barqte"
#include "SERVER/systems/systems_robatm"
#include "SERVER/systems/systems_switchgun"
#include "SERVER/systems/systems_cumidarat"
#include "SERVER/systems/systems_basketteam"
#include "SERVER/systems/systems_basketball"
#include "SERVER/systems/systems_race"
#include "SERVER/systems/systems_actoggle"

// #include "SERVER/systems/antiremcs_dan.inc"
// #include "SERVER/systems/system_keylistener"

#include "SERVER/toll/toll_functions"

// #include "SERVER/PlayerSpawn/spawn_functions.inc" Dimatikan sementara
#include "SERVER/jobs/Disnaker/disnaker_functions"

// #include "commands\boxing_funcs.inc"
#include "commands\management"
#include "commands\pengurus"
#include "commands\cmds_faction"
#include "commands\cmds_player"
#include "commands\cmds_admin"
#include "commands\earthquake"
#include "commands\NoClip"

#include "SERVER/carsteal/carsteal_functions"
#include "SERVER/PlayerStuff/player_toystd"
// #include "SERVER/mapping/mapping_server.inc"

// #include "SERVER/events/xmas.inc"
//#include "SERVER/events/events.inc"

#include "SERVER/showroom/showroom_functions"
#include "SERVER/PlayerStuff/player_actions"
#include "SERVER/PlayerStuff/player_asuransi"
#include "SERVER/PlayerStuff/player_fishingactivity"
//#include "SERVER/PlayerStuff/player_dice"
#include "SERVER/damages/damagelog_functions"

#include "SERVER/tags/core"
#include "SERVER/tags/cmd"
#include "SERVER/tags/funcs"
#include "SERVER/tags/impl"

// #include "commands\DISCORD"

#include "SERVER/PlayerCrafting/crafting_functions.inc"
// ----------------------------------------
#include "SERVER/streamer/streamer"
#include "SERVER/invoices/invoices"
#include "SERVER/blacklist/blacklist_functions"
#include "SERVER/timers/timer_task"
// #include "SERVER/timers/timer_ptask_anticheat.inc"
#include "SERVER/timers/timer_ptask_jail"
#include "SERVER/timers/timer_ptask_update"
#include "SERVER/playermarker/playermark"

forward OnGameModeInitEx();
forward OnGameModeExitEx();


main() 
{

}

stock DatabaseConnection()
{
	g_SQL = mysql_connect("157.245.60.247", "u1_BW6yNxyUlf", "RwtZ=jhdd@VfTUB^da+g^n5f", "s1_execute");
	if (g_SQL == MYSQL_INVALID_HANDLE || mysql_errno(g_SQL) != 0)
	{
		print("Happy Roleplay: Connection To MYSQL Failed! Server Shutting Down!");
		SendRconCommand("exit");
	}
	else
	{
		print("Happy Roleplay: Database successfully connected to MySQL.");
	}
	return 1;
}

public OnGameModeInit()
{
	Profiler_Start();
	DatabaseConnection();
	ShowNameTags(false);
	EnableTirePopping(0);
	CreateTextDraw();
	// StreamerConfig();
	// LoadMap();
	LoadWarungArea();
	LoadArea();
	LoadServerPickup();	
	ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(0);
	AllowInteriorWeapons(1);
	DisableInteriorEnterExits();
	LimitPlayerMarkerRadius(15.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);

	SetGameModeText(sprintf("%s", TEXT_GAMEMODE));
	SendRconCommand(sprintf("weburl %s", TEXT_WEBURL));
	SendRconCommand(sprintf("language %s", TEXT_LANGUAGE));
	// SendRconCommand("hostname Happy Roleplay | SA-MP Indonesia");
	SendRconCommand("mapname San Andreas");
	BlockGarages(.text="Tutup");

	/* Load From Database */
	mysql_tquery(g_SQL, "SELECT * FROM `brankas_ems`", "LoadBrankasEms");
	mysql_tquery(g_SQL, "SELECT * FROM `brankas_lounges`", "LoadBrankasLounges");
	mysql_tquery(g_SQL, "SELECT * FROM `buttons`", "LoadButtons");
	mysql_tquery(g_SQL, "SELECT * FROM `doors`", "LoadDoors");
	mysql_tquery(g_SQL, "SELECT * FROM `families`", "Families_Load");
	// mysql_tquery(g_SQL, "SELECT * FROM `families_garage`", "LoadFamiliesGarkot");
	mysql_tquery(g_SQL, "SELECT * FROM `house`", "LoadRumah");
	mysql_tquery(g_SQL, "SELECT * FROM `gate`", "LoadGate");
	mysql_tquery(g_SQL, "SELECT * FROM `actors`", "Actor_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `bike_rentals`", "Rental_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `public_garage`", "LoadPublicGarage");
	mysql_tquery(g_SQL, "SELECT * FROM `gudang`", "LoadGudang");
	mysql_tquery(g_SQL, "SELECT * FROM `warung`", "LoadWarung");
	mysql_tquery(g_SQL, "SELECT * FROM `pasar`", "LoadPasar");
	mysql_tquery(g_SQL, "SELECT * FROM `robbery`", "LoadDynamicRobbery" );
	mysql_tquery(g_SQL, "SELECT * FROM `atms`", "LoadATM");
	mysql_tquery(g_SQL, "SELECT * FROM `trash`", "LoadTrash");
	mysql_tquery(g_SQL, "SELECT * FROM `stuffs`", "LoadBrankasGoodside");
	mysql_tquery(g_SQL, "SELECT * FROM `ladang`", "LoadKanabis");
	mysql_tquery(g_SQL, "SELECT * FROM `icons`", "Icons_Load", "");
	mysql_tquery(g_SQL, "SELECT * FROM `label_fivem`", "LoadLabel");
	mysql_tquery(g_SQL, "SELECT * FROM `dynamic_rusun`", "Rusun_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `hunting`", "LoadDeer");
	mysql_tquery(g_SQL, "SELECT * FROM `weeds`", "Weed_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `voucher`", "LoadVoucher");
	mysql_tquery(g_SQL, "SELECT * FROM `objects`", "LoadDynamicObject");
	//mysql_tquery(g_SQL, "SELECT * FROM `slotmachine`", "LoadSlotMachine");
	mysql_tquery(g_SQL, "SELECT * FROM `objecttext`", "ObjectText_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `uranium`", "Load_Uranium");
	mysql_tquery(g_SQL, "SELECT * FROM `workshop`", "LoadWorkshop");
	mysql_tquery(g_SQL, "SELECT * FROM `tags` ORDER BY `tagId` ASC LIMIT "#MAX_DYNAMIC_TAGS";", "Tags_Load");

	for (new i; i < sizeof(ColorList); i++) {
        format(color_string, sizeof(color_string), "%s{%06x}%03d %s", color_string, ColorList[i] >>> 8, i, ((i+1) % 16 == 0) ? ("\n") : (""));
    }

    for (new i; i < sizeof(FontNames); i++) {
        format(object_font, sizeof(object_font), "%s%s\n", object_font, FontNames[i]);
    }
	
	for(new i = 0; i < sizeof(BarrierInfo);i ++)
	{
		new
		Float:X = BarrierInfo[i][brPos_X],
		Float:Y = BarrierInfo[i][brPos_Y];

		ShiftCords(0, X, Y, BarrierInfo[i][brPos_A]+90.0, 3.5);
		CreateDynamicObject(966,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z],0.00000000,0.00000000,BarrierInfo[i][brPos_A]);
		if(!BarrierInfo[i][brOpen])
		{
			gBarrier[i] = CreateDynamicObject(968,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.8,0.00000000,90.00000000,BarrierInfo[i][brPos_A]+180);
			MoveObject(gBarrier[i],BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[i][brPos_A]+180);
			MoveObject(gBarrier[i],BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.75,BARRIER_SPEED,0.0,90.0,BarrierInfo[i][brPos_A]+180);
		}
		else gBarrier[i] = CreateDynamicObject(968,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.8,0.00000000,20.00000000,BarrierInfo[i][brPos_A]+180);
	}

	/* Mprice Stuffs*/
	OldTembagaPrice = TembagaPrice;
	OldBesiPrice = BesiPrice;
	OldEmasPrice = EmasPrice;
	OldBerlianPrice = BerlianPrice;
	OldMaterialPrice = MaterialPrice;
	OldAlumuniumPrice = AlumuniumPrice;
	OldKaretPrice = KaretPrice;
	OldKacaPrice = KacaPrice;
	OldBajaPrice = BajaPrice;
	OldAyamKemasPrice = AyamKemasPrice;
	OldSusuOlahPrice = SusuOlahPrice;
	OldPakaianPrice = PakaianPrice;
	OldKayuKemasPrice = KayuKemasPrice;
	OldGasPrice = GasPrice;
	
	SetTimer("WeatherRotator", 1800000, true);
	CallLocalFunction("OnGameModeInitEx", "");

	OpenVote = 0;
    VoteYes = 0;
    VoteNo = 0;
    VoteTime = 0;
    VoteText[0] = EOS;
	return 1;
} 

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	#if defined DEBUG_MODE
	    printf("[debug] OnPlayerInteriorChange(PID : %d New-Int : %d Old-Int : %d)", playerid, newinteriorid, oldinteriorid);
	#endif

	CancelEdit(playerid);

	foreach(new i : Player) if (AccountData[i][pSpec] != INVALID_PLAYER_ID && AccountData[i][pSpec] == playerid)
	{
		SetPlayerInterior(i, GetPlayerInterior(playerid));
		SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(playerid));
	}

	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
    if (!AccountData[playerid][IsLoggedIn])
    {
		GameTextForPlayer(playerid, "~r~Stay in your world bastard!", 2000, 4);
		SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"LIGHTGREY" Anda ditendang karena diduga Fake Spawn!");
        KickEx(playerid);
    }
    return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(SQL_IsCharacterLogged(playerid) && AccountData[playerid][pAdmin] > 0)
	{
		if(!IsPlayerConnected(clickedplayerid)) return 0;
		if(clickedplayerid == playerid) return 0;

		new title[127];
		format(title, sizeof(title), ""City"Happy Roleplay "WHITE"- %s(%d)", ReturnName(clickedplayerid), clickedplayerid);
		ShowPlayerDialog(playerid, DIALOG_CLICKPLAYER, DIALOG_STYLE_LIST, title, 
		""City"Menu Admin\n\
		\nSpectator Pemain\
		\n"GRAY"Tarik Pemain\
		\nTeleport Ke Pemain\
		\n"GRAY"Banned Pemain\
		\nKick Pemain\
		\n"GRAY"Stats Pemain", "Pilih", "Batal");
		ClickPlayerID[playerid] = clickedplayerid;
	}
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetCameraData(playerid);

	if(!AccountData[playerid][IsLoggedIn])
	{		
		new query[268];
		mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `playerucp` WHERE `ucp` = '%s' LIMIT 1", AccountData[playerid][pUCP]);
        mysql_pquery(g_SQL, query, "CheckPlayerUCP", "id", playerid, g_RaceCheck[playerid]);
		SetPlayerColor(playerid, X11_GRAY);
	}
	return 1;
}

public OnGameModeExit()
{
	#if defined DEBUG_MODE
	    printf("[debug] OnGameModeExit()");
	#endif

    SaveAll();
	
	foreach(new playerid : Player)
		TerminateConnection(playerid);

	CallLocalFunction("OnGameModeExitEx", "");
	mysql_close(g_SQL);
	Profiler_Stop();
	return 1;
}

forward OnPlayerCarJacking(playerid);
public OnPlayerCarJacking(playerid)
{
	new Float:playerPos[3];
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
	
	SetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2] + 9.0);
	TogglePlayerControllable(playerid, false);
	GameTextForPlayer(playerid, "No Jacking!", 5500, 4);
	SetPlayerVirtualWorld(playerid, (playerid+1));
	SetTimerEx("OnPlayerCarJackingUpdate", 5500, false, "d", playerid);
	return 1;	
}

forward OnPlayerCarJackingUpdate(playerid);
public OnPlayerCarJackingUpdate(playerid)
{
	TogglePlayerControllable(playerid, true);
	SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
		new driverid = GetVehicleDriver(vehicleid);
		if(driverid != INVALID_PLAYER_ID && IsPlayerInVehicle(driverid, vehicleid) && !IsVehicleEmpty(vehicleid) && IsPlayerChangeSeat[playerid] == false)
		{
			SetTimerEx("OnPlayerCarJacking", 250, false, "d", playerid);
		}
		new vehicle_near = GetNearestVehicle(playerid);
		if((vehicle_near = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
		{
			/*if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_POLISI)
			{
				if(AccountData[playerid][pFaction] != FACTION_POLISI && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Polisi!");
				}
			}*/
			if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_PEMERINTAH)
			{
				if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Pemerintah!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_EMS)
			{
				if(AccountData[playerid][pFaction] != FACTION_EMS && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction EMS!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_TRANS)
			{
				if(AccountData[playerid][pFaction] != FACTION_TRANS && AccountData[playerid][pFaction] != FACTION_BENGKEL && AccountData[playerid][pFaction] != FACTION_POLISI)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Transportasi!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_BENGKEL)
			{
				if(AccountData[playerid][pFaction] != FACTION_POLISI && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Bengkel!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_PEDAGANG)
			{
				if(AccountData[playerid][pFaction] != FACTION_PEDAGANG && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Pedagang!");
				}
			}
		}
	}
	return 1;
}

forward TrackSuspect(suspectid, policeid);
public TrackSuspect(suspectid, policeid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(suspectid, x, y, z);

	SetPlayerRaceCheckpoint(policeid, 1, x, y, z, 0.0, 0.0, 0.0, 5.0);
	Info(policeid, "Tracking Suspect Updated!");
	pMapCP[policeid] = true;
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned])
		return 0;

	if(AccountData[playerid][pAdmin] > 0 && AccountData[playerid][pAdminDuty])
	{
		if(strlen(text) > 64)
		{
			SendNearbyMessage(playerid, 15.0, -1, "Admin "RED"%s"WHITE": (( %.64s...", AccountData[playerid][pAdminname], text);
			SendNearbyMessage(playerid, 15.0, -1, "...%s ))", text[64]);
		}
		else 
		{
			SendNearbyMessage(playerid, 15.0, -1, "Admin "RED"%s"WHITE": (( %s ))", AccountData[playerid][pAdminname], text);
		}
	}
	return 0;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if (result != -1 && !AccountData[playerid][IsLoggedIn])
	{
		SendClientMessage(playerid, -1, ""RED"[AntiCheat]"ARWIN1" Anda ditendang dari server karena menggunakan CMD dalam keadaan tidak login!");
		return KickEx(playerid);
	}
	
    if (result == -1)
    {
		if(AccountData[playerid][pStyleNotif] == 1) //TD
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Perintah ~y~'/%s'~w~ tidak diketahui, ~y~'/help'~w~ untuk info lanjut!", cmd));
		}
		else
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Perintah "YELLOW"'/%s'"WHITE" tidak diketahui, "YELLOW"'/help'"WHITE" untuk info lanjut!", cmd));
		}
		return 0;
    }
	return 1;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	return 1;
}

public OnPlayerConnect(playerid)
{
	g_RaceCheck[playerid] ++;
	ResetVariables(playerid);
	ReturnIP(playerid);
	CreatePlayerTextDraws(playerid);
	OnLoadMixerProperty(playerid);
	Player_ToggleTelportAntiCheat(playerid, false);
	Player_ToggleAntiHealthHack(playerid, false);
	Player_ToggleDisableAntiCheat(playerid, false);
	EnableAntiCheatForPlayer(playerid, 11, true);
	EnableAntiCheatForPlayer(playerid, 19, true);
	EnableAntiCheatForPlayer(playerid, 4, true);

	if(g_RestartServer || g_AsuransiTime) {
		TextDrawShowForPlayer(playerid, gServerTextdraws[0]);
	}

	GetPlayerName(playerid, AccountData[playerid][pUCP], MAX_PLAYER_NAME + 1);

    if(AccountData[playerid][pHead] < 0) return AccountData[playerid][pHead] = 20;
    if(AccountData[playerid][pPerut] < 0) return AccountData[playerid][pPerut] = 20;
    if(AccountData[playerid][pRFoot] < 0) return AccountData[playerid][pRFoot] = 20;
    if(AccountData[playerid][pLFoot] < 0) return AccountData[playerid][pLFoot] = 20;
    if(AccountData[playerid][pLHand] < 0) return AccountData[playerid][pLHand] = 20;
    if(AccountData[playerid][pRHand] < 0) return AccountData[playerid][pRHand] = 20;
	
	PantaiArea[playerid] = CreateDynamicRectangle(345.3125, -2094.787811279297, 415.3125, -2007.7878112792969);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		RemovePlayerFromVehicle(playerid);
	}

	KillTimer(AccountData[playerid][DokterLokalTimer]);
	KillTimer(AccountData[playerid][pDutyTimer]);
	RemoveDrag(playerid);
	CheckDrag(playerid);
	Report_Clear(playerid);
	Ask_Clear(playerid);

	g_RaceCheck[playerid] ++;
	
	if (AccountData[playerid][IsLoggedIn])
	{
		UpdatePlayerData(playerid);
		UnloadPlayerVehicle(playerid);

		if (AccountData[playerid][pJobVehicle] != 0)
		{
			DestroyJobVehicle(playerid);
			AccountData[playerid][pJobVehicle] = 0;
		}
	}

	if(IsValidDynamic3DTextLabel(AccountData[playerid][pAdoTag])) DestroyDynamic3DTextLabel(AccountData[playerid][pAdoTag]);
	if(IsValidDynamic3DTextLabel(AccountData[playerid][pMaskLabel])) DestroyDynamic3DTextLabel(AccountData[playerid][pMaskLabel]);

    if(AccountData[playerid][pAdminDuty] == 1)
	if(IsValidDynamic3DTextLabel(AccountData[playerid][pLabelDuty]))
		DestroyDynamic3DTextLabel(AccountData[playerid][pLabelDuty]);

	new reasontext[526], frmxt[255], Float:pX, Float:pY, Float:pZ;
	GetPlayerPos(playerid, pX, pY, pZ);

	switch(reason)
	{
	    case 0: format(reasontext, sizeof(reasontext), "Timeout/Crash");
	    case 1: format(reasontext, sizeof(reasontext), "Quit");
		case 2: format(reasontext, sizeof(reasontext), "Kicked/Banned");
	}

	if(DestroyDynamic3DTextLabel(labelDisconnect[playerid])) 
		labelDisconnect[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	format(frmxt, sizeof(frmxt), "Player ["YELLOW"%d"WHITE"]"YELLOW" %s | %s"WHITE" Telah keluar dari server.\nReason: "RED"%s", playerid, AccountData[playerid][pName], AccountData[playerid][pUCP], reasontext);
	labelDisconnect[playerid] = CreateDynamic3DTextLabel(frmxt, -1, pX, pY, pZ, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 15.0, -1, 0);
	labelDisconnectTimer[playerid] = SetTimerEx("DestroyLabelOut", 30000, false, "i", playerid);
	
	if(AccountData[playerid][phoneDurringConversation])
	{
		CutCallingLine(playerid);
	}
	TerminateConnection(playerid);
	return 1;
}	

public OnPlayerSpawn(playerid)
{
	if(AccountData[playerid][pGender] == 0)
	{
		TogglePlayerControllable(playerid,0);
		SetPlayerHealth(playerid, 100.0);
		SetPlayerCameraPos(playerid, 584.769, -2183.039, 131.617);
		SetPlayerCameraLookAt(playerid, 582.755, -2178.958, 129.546);
		InterpolateCameraPos(playerid, 584.769, -2183.039, 131.617, 584.769, -2183.039, 131.617, 20000, CAMERA_MOVE);
		SetPlayerVirtualWorld(playerid, 3);
		ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Tanggal Lahir", "Mohon masukkan tanggal lahir sesuai format hh/bb/tttt cth: (25/09/2001)", "Input", "");
	}
	else
	{
		if(!AccountData[playerid][pSpawned])
		{
			AccountData[playerid][pSpawned] = 1;
			SetCameraBehindPlayer(playerid);
			Streamer_ToggleIdleUpdate(playerid, true);
			StopAudioStreamForPlayer(playerid);
			
			GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
			SetPlayerScore(playerid, AccountData[playerid][pLevel]);
			SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
			SetPlayerArmour(playerid, AccountData[playerid][pArmour]);
			SetPlayerInterior(playerid, AccountData[playerid][pInt]);
			SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
			PreloadAnimations(playerid);

			TogglePlayerControllable(playerid, false);
			static Float:X, Float:Y, Float:Z;
			GetPlayerPos(playerid, X, Y, Z);
			ShowPlayerFooter(playerid, "~y~MEMUAT OBJECT", 7000);
			AccountData[playerid][pFreeze] = 1;
			AccountData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", 7000, false, "iffff", playerid, X, Y, Z); //defer SetPlayerToUnfreeze[time](playerid);
			Player_ToggleTelportAntiCheat(playerid, true);

			SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 0);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);

			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 0);

			SendClientMessageEx(playerid, -1, ""BLUEJEGE"SERVER: "WHITE"Selamat datang "YELLOW"%s.", ReturnName(playerid));
			SendClientMessageEx(playerid, -1, ""BLUEJEGE"SERVER: "WHITE"Today is "YELLOW"%s", ReturnTime());
			SendClientMessageEx(playerid, -1, ""BLUEJEGE"SERVER: "WHITE"Server memerlukan waktu "YELLOW"%d milisecond"WHITE" untuk memuat char anda.", GetPlayerPing(playerid));
			SendClientMessage(playerid, -1, ""LIGHTSKYBLUE"NOTE:"WHITE" Jika anda punya pertanyaan gunakan "RED"/ask"WHITE", untuk keperluan lainnya anda dapat menggunakan "RED"/help");
			SendClientMessage(playerid, -1, ""LIGHTSKYBLUE"NOTE:"WHITE" Sering sering menggunakan cmd "RED"/saveme"WHITE", untuk menyimpan charater anda ke database server");
			SendClientMessage(playerid, -1, ""LIGHTSKYBLUE"NOTE:"WHITE" Discord kita yaitu: "GOLD1"dsc.gg/happyroleplay");
			SendClientMessage(playerid, -1, ""LIGHTSKYBLUE"MOTD: "WHITE"Selamat bermain dan memulai cerita di "City"Happy Roleplay");

			new vQuery[300];
			mysql_format(g_SQL, vQuery, sizeof(vQuery), "SELECT * FROM `player_vehicles` WHERE `PVeh_OwnerID` = '%d' ORDER BY `id` ASC", AccountData[playerid][pID]);
			mysql_tquery(g_SQL, vQuery, "Vehicle_Load", "d", playerid);

			if(VoucherData[0][voucherExists] && AccountData[playerid][pKompensasi] < 1)
			{
				SendClientMessageEx(playerid, -1, "[i] Anda memiliki kompensasi yang belum di claim! gunakan "YELLOW"'/klaimkompensasi'"WHITE" untuk mengambil kompensasi");
			}
			if(AccountData[playerid][pDutyPD] || AccountData[playerid][pDutyPemerintah] || AccountData[playerid][pDutyEms] 
				|| AccountData[playerid][pDutyBengkel] || AccountData[playerid][pDutyTrans] || AccountData[playerid][pDutyPedagang])
			{
				AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "d", playerid);
			}
		}

		if(IsPlayerInEvent(playerid))
		 	return 0;
		
		Streamer_ToggleIdleUpdate(playerid, true);
		PreloadAnimations(playerid);
		if(AccountData[playerid][pUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
		else
		{
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
		}

		if(AccountData[playerid][pInjured] == 1 && AccountData[playerid][pInjuredTime] != 0)
		{
			TogglePlayerControllable(playerid, false);
			SetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
			SetPlayerFacingAngle(playerid, AccountData[playerid][pPosA]);
			SetPlayerInterior(playerid, AccountData[playerid][pInt]);
			SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
		}

		if(AccountData[playerid][pAdminDuty] > 0)
		{
			SetPlayerColor(playerid, X11_DARKRED);
		}
		SetTimerEx("TimersSpawn", 5000, false, "d", playerid);
	}
	return 1;
}

forward TimersSpawn(playerid);
public TimersSpawn(playerid)
{
	if(!AccountData[playerid][pSpawned])
		return 0;

	if(AccountData[playerid][pJail] > 0)
	{
		SpawnPlayerInJail(playerid);
	}
	if(AccountData[playerid][pArrestTime] > 0)
	{
		SetPlayerArrest(playerid, AccountData[playerid][pArrest]);
	}
	TogglePlayerControllable(playerid, 1);
	SetPlayerInterior(playerid, AccountData[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
	AttachPlayerToys(playerid);
	SetWeapons(playerid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(!AccountData[playerid][pSpawned])
		return 0;

	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		if(AccountData[i][pAdmin] > 0 && AccountData[i][pTheStars] > 0)
		{
			SendDeathMessageToPlayer(i, killerid, playerid, reason);
			return 1;
		}
	}
	new reasontext[596];
	switch(reason)
	{
		case 0: reasontext = "Tangan Kosong";
		case 1: reasontext = "Brass Knuckles";
		case 2: reasontext = "Golf Club";
		case 3: reasontext = "Nite Stick";
		case 4: reasontext = "Knife";
		case 5: reasontext = "Basebal Bat";
		case 6: reasontext = "Shovel";
		case 7: reasontext = "Pool Cue";
		case 8: reasontext = "Katana";
		case 9: reasontext = "Chain Shaw";
		case 14: reasontext = "Cane";
		case 18: reasontext = "Molotov";
		case 22: reasontext = "Colt 45";
		case 23: reasontext = "SLC";
		case 24: reasontext = "Desert Eagle";
		case 25: reasontext = "Shotgun";
		case 26: reasontext = "Sawnoff Shotgun";
		case 27: reasontext = "Combat Shotgun";
		case 28: reasontext = "Micro SMG/Uzi";
		case 29: reasontext = "MP5";
		case 30: reasontext = "AK-47";
		case 31: reasontext = "M4";
		case 32: reasontext = "Tec-9";
		case 33: reasontext = "Coutry Rifle";
		case 38: reasontext = "Mini Gun";
		case 49: reasontext = "Tertabrak Kendaraan";
		case 50: reasontext = "Helicopter Blades";
		case 51: reasontext = "Explode";
		case 53: reasontext = "Drowned";
		case 54: reasontext = "Splat";
		case 255: reasontext = "Suicide";
	}

	SetPlayerArmedWeapon(playerid, 0);
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ )
{
	new weaponid = EditingWeapon[playerid];
	if(response)
	{
		if(weaponid)
		{
			new enum_index = weaponid - 22, weaponname[18], string[340];
 
            GetWeaponName(weaponid, weaponname, sizeof(weaponname));
           
            WeaponSettings[playerid][enum_index][Position][0] = fOffsetX;
            WeaponSettings[playerid][enum_index][Position][1] = fOffsetY;
            WeaponSettings[playerid][enum_index][Position][2] = fOffsetZ;
            WeaponSettings[playerid][enum_index][Position][3] = fRotX;
            WeaponSettings[playerid][enum_index][Position][4] = fRotY;
            WeaponSettings[playerid][enum_index][Position][5] = fRotZ;
 
            RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
            SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
 
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil merubah posisi letak %s", weaponname));
           
			EditingWeapon[playerid] = 0;
            mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, PosX, PosY, PosZ, RotX, RotY, RotZ) VALUES ('%d', %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f) ON DUPLICATE KEY UPDATE PosX = VALUES(PosX), PosY = VALUES(PosY), PosZ = VALUES(PosZ), RotX = VALUES(RotX), RotY = VALUES(RotY), RotZ = VALUES(RotZ)", AccountData[playerid][pID], weaponid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
            mysql_tquery(g_SQL, string);
		}

		if(AccountData[playerid][toySelected] != -1)
		{
			new id = AccountData[playerid][toySelected];
			pToys[playerid][id][toy_x] = fOffsetX;
			pToys[playerid][id][toy_y] = fOffsetY;
			pToys[playerid][id][toy_z] = fOffsetZ;
			pToys[playerid][id][toy_rx] = fRotX;
			pToys[playerid][id][toy_ry] = fRotY;
			pToys[playerid][id][toy_rz] = fRotZ;
			pToys[playerid][id][toy_sx] = fScaleX;
			pToys[playerid][id][toy_sy] = fScaleY;
			pToys[playerid][id][toy_sz] = fScaleZ;
			
			MySQL_SavePlayerToys(playerid);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyimpan kordinat baru.");
			AccountData[playerid][toySelected] = -1;
		}
	}
	else
	{
		if(EditingWeapon[playerid])
		{
			new enum_index = weaponid - 22;
			SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
			EditingWeapon[playerid] = 0;
		}

		if(AccountData[playerid][toySelected] != -1)
		{
			new id = AccountData[playerid][toySelected];
			SetPlayerAttachedObject(playerid,
				id,
				modelid,
				boneid,
				pToys[playerid][id][toy_x],
				pToys[playerid][id][toy_y],
				pToys[playerid][id][toy_z],
				pToys[playerid][id][toy_rx],
				pToys[playerid][id][toy_ry],
				pToys[playerid][id][toy_rz],
				pToys[playerid][id][toy_sx],
				pToys[playerid][id][toy_sy],
				pToys[playerid][id][toy_sz]);
			AccountData[playerid][toySelected] = -1;
		}
	}
	SetPVarInt(playerid, "UpdatedToy", 1);
	return 1;
}


public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingDeerID] != -1 && Iter_Contains(Hunt, AccountData[playerid][EditingDeerID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingDeerID];
	        HuntData[etid][DeerPOS][0] = x;
	        HuntData[etid][DeerPOS][1] = y;
	        HuntData[etid][DeerPOS][2] = z;
	        HuntData[etid][DeerROT][0] = rx;
	        HuntData[etid][DeerROT][1] = ry;
	        HuntData[etid][DeerROT][2] = rz;

	        SetDynamicObjectPos(objectid, HuntData[etid][DeerPOS][0], HuntData[etid][DeerPOS][1], HuntData[etid][DeerPOS][2]);
	        SetDynamicObjectRot(objectid, HuntData[etid][DeerROT][0], HuntData[etid][DeerROT][1], HuntData[etid][DeerROT][2]);

			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HuntData[etid][DeerLabel], E_STREAMER_X, HuntData[etid][DeerPOS][0]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HuntData[etid][DeerLabel], E_STREAMER_Y, HuntData[etid][DeerPOS][1]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HuntData[etid][DeerLabel], E_STREAMER_Z, HuntData[etid][DeerPOS][2] + 1.1);

		    HuntSave(etid);
	        AccountData[playerid][EditingDeerID] = -1;
	    }
	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingDeerID];
	        SetDynamicObjectPos(objectid, HuntData[etid][DeerPOS][0], HuntData[etid][DeerPOS][1], HuntData[etid][DeerPOS][2]);
	        SetDynamicObjectRot(objectid, HuntData[etid][DeerROT][0], HuntData[etid][DeerROT][1], HuntData[etid][DeerROT][2]);
	        AccountData[playerid][EditingDeerID] = -1;
	    }
	}
	else if(AccountData[playerid][EditingLADANGID] != -1 && Iter_Contains(Ladang, AccountData[playerid][EditingLADANGID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingLADANGID];
	        LadangData[etid][kanabisX] = x;
	        LadangData[etid][kanabisY] = y;
	        LadangData[etid][kanabisZ] = z;
	        LadangData[etid][kanabisRX] = rx;
	        LadangData[etid][kanabisRY] = ry;
	        LadangData[etid][kanabisRZ] = rz;

	        SetDynamicObjectPos(objectid, LadangData[etid][kanabisX], LadangData[etid][kanabisY], LadangData[etid][kanabisZ]);
	        SetDynamicObjectRot(objectid, LadangData[etid][kanabisRX], LadangData[etid][kanabisRY], LadangData[etid][kanabisRZ]);

		    Ladang_Save(etid);
	        AccountData[playerid][EditingLADANGID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingLADANGID];
	        SetDynamicObjectPos(objectid, LadangData[etid][kanabisX], LadangData[etid][kanabisY], LadangData[etid][kanabisZ]);
	        SetDynamicObjectRot(objectid, LadangData[etid][kanabisRX], LadangData[etid][kanabisRY], LadangData[etid][kanabisRZ]);
	        AccountData[playerid][EditingLADANGID] = -1;
	    }
	}
	else if(AccountData[playerid][EditingATMID] != -1 && Iter_Contains(ATMS, AccountData[playerid][EditingATMID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingATMID];
	        AtmData[etid][atmX] = x;
	        AtmData[etid][atmY] = y;
	        AtmData[etid][atmZ] = z;
	        AtmData[etid][atmRX] = rx;
	        AtmData[etid][atmRY] = ry;
	        AtmData[etid][atmRZ] = rz;

	        SetDynamicObjectPos(objectid, AtmData[etid][atmX], AtmData[etid][atmY], AtmData[etid][atmZ]);
	        SetDynamicObjectRot(objectid, AtmData[etid][atmRX], AtmData[etid][atmRY], AtmData[etid][atmRZ]);

		  	Atm_Refresh(etid);
		    Atm_Save(etid);
	        AccountData[playerid][EditingATMID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingATMID];
	        SetDynamicObjectPos(objectid, AtmData[etid][atmX], AtmData[etid][atmY], AtmData[etid][atmZ]);
	        SetDynamicObjectRot(objectid, AtmData[etid][atmRX], AtmData[etid][atmRY], AtmData[etid][atmRZ]);
	        AccountData[playerid][EditingATMID] = -1;
	    }
	}
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	if(!InRace[playerid]) return 1;
	{
		new ownerid = RaceWith[playerid];
		new index = ++RaceIndex[playerid];

		// Jika sudah mencapai FINISH
		if(index >= MAX_ROUTE - 1) {
			InRace[playerid] = false;
			DisablePlayerRaceCheckpoint(playerid);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Selamat! Kamu telah mencapai garis finish.");
			return 1;
		}

		// Lanjut ke checkpoint berikutnya
		SetPlayerRaceCheckpoint(playerid, 0,
			RacePos[ownerid][index][0], RacePos[ownerid][index][1], RacePos[ownerid][index][2],
			RacePos[ownerid][index + 1][0], RacePos[ownerid][index + 1][1], RacePos[ownerid][index + 1][2],
			5.0);

	}
	if(pMapCP[playerid])
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil sampai ke lokasi tujuan");
		DisablePlayerRaceCheckpoint(playerid);
		pMapCP[playerid] = false;
	}
	if(AccountData[playerid][pTrackCar] == 1)
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil sampai ke lokasi tujuan");
		AccountData[playerid][pTrackCar] = 0;
		DisablePlayerRaceCheckpoint(playerid);
	}
	if(AccountData[playerid][pTrackHoused] == 1)
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil sampai ke lokasi tujuan");
		AccountData[playerid][pTrackHoused] = 0;
		DisablePlayerRaceCheckpoint(playerid);
	}
	if(AccountData[playerid][pDiPesawat])
	{
		DisablePlayerCheckpoint(playerid);
		AccountData[playerid][pDiPesawat] = false;
		AccountData[playerid][pPosX] = 1696.1014;
		AccountData[playerid][pPosY] = -2329.8801;
		AccountData[playerid][pPosZ] = 13.5469;
		AccountData[playerid][pPosA] = 63.8332;
		AccountData[playerid][pInDoor] = 7;
		SetPlayerVirtualWorldEx(playerid, 0);
		SetPlayerInteriorEx(playerid, 0);
		SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
	}
	if(jobs::mixer[playerid][mixerDuty][1])
    {
        DisablePlayerCheckpoint(playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][3], "MENUMPAHKAN");
        ShowProgressBar(playerid);
        jobs::mixer[playerid][mixerDuty][1] = false;
        jobs::mixer[playerid][mixerTimer] = SetTimerEx("CorLokasi", 1000, true, "i", playerid);
    }
    if(jobs::mixer[playerid][mixerDuty][2])
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            RemovePlayerFromVehicle(playerid);
            DestroyVehicle(GetPlayerVehicleID(playerid));
            GiveMoney(playerid, 150);
            jobs::mixer[playerid][mixerDuty][2] = false; 
            jobs::mixer_reset_enum(playerid);
        }
        
    }
	return 1;
}

Dialog:DeathRespawnConf(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(!IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang Pingsan!");

	SetPlayerHealthEx(playerid, 100.0);
	AccountData[playerid][pHunger] = 100;
	AccountData[playerid][pThirst] = 100;
	AccountData[playerid][pStress] = 0;
	AccountData[playerid][pInjured] = 0;
	AccountData[playerid][pInjuredTime] = 0;
	Inventory_Clear(playerid);
	ResetPlayerWeaponsEx(playerid);
	
	ShowTDN(playerid, NOTIFICATION_INFO, "Kamu koma dan dilarikan ke Rumah Sakit");

	SetPlayerPositionEx(playerid, 907.8289, 711.1892, 5010.3184, 358.7794, 5000);
	SetPlayerVirtualWorldEx(playerid, 5);
	SetPlayerInteriorEx(playerid, 5);

	foreach(new pid : Player) {
		if(AccountData[pid][pFaction] == FACTION_EMS && AccountData[pid][pDutyEms]) {
			SendClientMessageEx(pid, -1, ""YELLOW"[Koma]"WHITE_E" %s telah terbangun di ruang koma", ReturnName(playerid));
		}
	}

	AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], "KOMA", 0);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	/* Job Mixer */
	if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 2.0, 641.2187,1238.3390,11.6796))
    {
		if(jobs::mixer[playerid][mixerDuty][0]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memulai pekerjaan");
        if(GetPlayerJob(playerid) != JOB_DRIVER_MIXERS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pekerja supir mixer");
        jobs::mixer[playerid][mixerVehicle] = CreateVehicle(524, 639.8187,1250.2065,11.6333,306.5278, 5, 5, 60000, false);
		if(IsValidVehicle(jobs::mixer[playerid][mixerVehicle]))
		{
			VehicleCore[jobs::mixer[playerid][mixerVehicle]][vCoreFuel]=MAX_FUEL_FULL;
		    PutPlayerInVehicle(playerid, jobs::mixer[playerid][mixerVehicle], 0);
			jobs::mixer[playerid][mixerDuty][0] = true;
		}
        ShowPlayerFooter(playerid, "~w~~h~Isi kendaraan dengan ~g~beton ~w~di~n~belakang", 3000, 1);
    }
    if(PRESSED(KEY_CROUCH) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInRangeOfPoint(playerid, 3.0, 590.0992,1243.8767,11.7188))
    {
        if(GetPlayerJob(playerid) != JOB_DRIVER_MIXERS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pekerja supir mixer");
        ShowMixTD(playerid);
    }
	/* Senter */
	if(PRESSED(KEY_CTRL_BACK) && AccountData[playerid][pFlashShown] && !IsPlayerInAnyVehicle(playerid))
	{
		switch(AccountData[playerid][pFlashOn])
		{
			case false:
            {
				if (!IsPlayerPlayingAnimation(playerid, "ped", "phone_talk"))
				{
					ApplyAnimationEx(playerid, "ped", "phone_talk", 1.1, 1, 1, 1, 1, 1, 1);
				}
				
                AccountData[playerid][pFlashOn] = true;
                SetPlayerAttachedObject(playerid, 5, 19295, 1,  0.068000, 0.606000, 0.000000,  0.000000, -4.500000, 12.299996,  1.000000, 1.000000, 1.020000); // Light Objects
                ShowPlayerFooter(playerid, "~w~Senter ~g~Nyala", 3000);
            }
            case true:
            {
                AccountData[playerid][pFlashOn] = false;
                RemovePlayerAttachedObject(playerid, 5);
                ShowPlayerFooter(playerid, "~w~Senter ~r~Mati", 3000);
            }
		}
	}

	/* Greenzone */
	if(newkeys & KEY_FIRE && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && IsPlayerInDynamicArea(playerid, AreaData[BandaraGreenZone]))
	{
		ClearAnimations(playerid, 1);
        SetPlayerArmedWeapon(playerid, 0);

        SetPVarInt(playerid, "GreenzoneWarning", GetPVarInt(playerid, "GreenzoneWarning")+1);
		Info(playerid, "Anda tidak dapat memukul / menembak di Area Greenzone. "RED"%d/5"WHITE" anda akan ditendang dari server.", GetPVarInt(playerid, "GreenzoneWarning"));

        if(GetPVarInt(playerid, "GreenzoneWarning") == 5) {
			Warning(playerid, "Anda telah ditendang dari server karena mendapatkan "RED"5"WHITE" peringatan Greenzone!");
			DeletePVar(playerid, "GreenzoneWarning");
            KickEx(playerid);
        }
	}

	if((newkeys & KEY_JUMP) && !IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !IsPlayerInEvent(playerid) && !DurringHunting[playerid] && !AccountData[playerid][pAdminDuty])
	{
		PlayerPressedJump[playerid] ++;
		SetTimerEx("PressJumpReset", 3000, false, "d", playerid); // Makes it where if they dont spam the jump key, they wont fall

		if(PlayerPressedJump[playerid] >= 3)
		{
			new Float: POS[3];
			GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
			SetPlayerPos(playerid, POS[0], POS[1], POS[2] - 0.2);
			ApplyAnimationEx(playerid, "PED", "FALL_collapse", 4.1, 0, 1, 0, 0, 0, 1); // applies the fallover animation
			PlayerPlayNearbySound(playerid, 1163);
			PlayerPressedJump[playerid] = 0;
		}
	}

	/* Voting Systemm */
	if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP) && !AccountData[playerid][pInjured])
	{
		if(AccountData[playerid][pRFoot] < 50 || AccountData[playerid][pLFoot] < 50)
		{
			ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, 0, 1, 1, 0, 0);
		}
	}

	if(newkeys & KEY_YES && OpenVote == 1 && !PlayerVoting[playerid] && !AccountData[playerid][ActivityTime])
	{

		ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Setuju untuk Voting yang sedang berjalan");

		PlayerVoting[playerid] = true;
		VoteYes += 1;
		SendClientMessageToAllEx(-1, ""YELLOW"VOTE:"WHITE" %s // Yes: "GREEN"%d"WHITE" // No: "RED"%d", VoteText, VoteYes, VoteNo);
		SendClientMessageToAllEx(-1, "~> Gunakan "GREEN"Y"WHITE" untuk Yes & "RED"N"WHITE" untuk Tidak");
	}

	if(newkeys & KEY_NO && OpenVote == 1 && !PlayerVoting[playerid] && !AccountData[playerid][ActivityTime])
	{

		ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Tidak Setuju untuk Voting yang sedang berjalan");

		PlayerVoting[playerid] = true;
		VoteNo += 1;
		SendClientMessageToAllEx(-1, ""YELLOW"VOTE:"WHITE" %s // Yes: "GREEN"%d"WHITE" // No: "RED"%d", VoteText, VoteYes, VoteNo);
		SendClientMessageToAllEx(-1, "~> Gunakan "GREEN"Y"WHITE" untuk Yes & "RED"N"WHITE" untuk Tidak");
	}

	/* Anti Bike Hopping */
	if(PRESSED(KEY_ACTION))
	{
		static vehicleid;

		if(IsPlayerInAnyVehicle(playerid) && ((vehicleid = GetPlayerVehicleID(playerid)) != INVALID_VEHICLE_ID))
		{
			if(GetVehicleModel(vehicleid) == 509 || GetVehicleModel(vehicleid) == 481 || GetVehicleModel(vehicleid) == 510)
			{
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x, y, z);
				SetPlayerPos(playerid, x, y, z);

				ApplyAnimationEx(playerid, "PED", "BIKE_fall_off", 4.1, 0, 1, 1, 1, 0, 1);
			}
		}
	}

	if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP) && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED && !AccountData[playerid][pInjured])
	{
		ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, 0, 1, 1, 0, 0);
	}
	if(newkeys & KEY_YES)
	{
		if(AccountData[playerid][pInjured])
		{
		    Dialog_Show(playerid, DeathRespawnConf, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Konfirmasi Koma",
		    "Apakah anda benar benar yakin ingin melakukan tindakan ini?\n"RED"NOTE: Tindakan ini dapat menghilangkan semua barang di tas termasuk uang cash", "Iya", "Tidak");
		}
	}
	if(newkeys & KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
		foreach(new famid : Families)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, FamData[famid][famExtPos][0], FamData[famid][famExtPos][1], FamData[famid][famExtPos][2]))
			{
				if(IsDoorMyFamilie(playerid) == AccountData[playerid][pFamily])
				{
					if(FamData[famid][famIntPos][0] == 0.0 && FamData[famid][famIntPos][1] == 0.0 && FamData[famid][famIntPos][2] == 0.0)
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Interior ini masih kosong!");

					if(AccountData[playerid][pFaction] == FACTION_NONE)
						if(AccountData[playerid][pFamily] == -1)
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki Akses untuk masuk kedalam sini!");
					
					AccountData[playerid][UsingDoor] = true;
					Player_ToggleTelportAntiCheat(playerid, false);
					SetPlayerPositionEx(playerid, FamData[famid][famIntPos][0], FamData[famid][famIntPos][1], FamData[famid][famIntPos][2], FamData[famid][famIntPos][3], 5000);

					SetPlayerInterior(playerid, FamData[famid][famInterior]);
					SetPlayerVirtualWorld(playerid, famid);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, 0);
					AccountData[playerid][pInFamily] = famid;
				}
				else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Families ini!");
			}
			new infamily = AccountData[playerid][pInFamily];
			if(AccountData[playerid][pInFamily] != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, FamData[infamily][famIntPos][0], FamData[infamily][famIntPos][1],FamData[infamily][famIntPos][2]))
			{
				AccountData[playerid][pInFamily] = -1;
				AccountData[playerid][UsingDoor] = true;
				Player_ToggleTelportAntiCheat(playerid, false);
				SetPlayerPositionEx(playerid, FamData[infamily][famExtPos][0], FamData[infamily][famExtPos][1], FamData[infamily][famExtPos][2], FamData[infamily][famExtPos][3], 5000);

				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, WorldWeather);
				Player_ToggleTelportAntiCheat(playerid, true);
			}
		}
	}
	
	if(newkeys & KEY_LOOK_BEHIND)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) return 0;

		new vehid = GetNearestVehicleToPlayer(playerid, 3.0, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun di sekitar!");

		foreach(new iter : PvtVehicles)
		{
			if(PlayerVehicle[iter][pVehExists])
			{
				if(PlayerVehicle[iter][pVehPhysic] == vehid)
				{
					if(PlayerVehicle[iter][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
					
					PlayerPlaySound(playerid, 1147, 0.0, 0.0, 0.0);
					PlayerVehicle[iter][pVehLocked] = !(PlayerVehicle[iter][pVehLocked]);

					PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
					LockVehicle(PlayerVehicle[iter][pVehPhysic], PlayerVehicle[iter][pVehLocked]);
					ToggleVehicleLights(PlayerVehicle[iter][pVehPhysic], PlayerVehicle[iter][pVehLocked]);
					GameTextForPlayer(playerid, sprintf("~w~%s %s", GetVehicleName(PlayerVehicle[iter][pVehPhysic]), PlayerVehicle[iter][pVehLocked] ? ("~r~Locked") : ("~g~Unlocked")), 4000, 4);
					return 1;
				}
			}
		}

		if(AccountData[playerid][pJobVehicle] != 0)
		{
			if (vehid == JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle])
			{
				PlayerPlaySound(playerid, 1147, 0.0, 0.0, 0.0);
				JobVehicle[AccountData[playerid][pJobVehicle]][Locked] = !(JobVehicle[AccountData[playerid][pJobVehicle]][Locked]);

				PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
				LockVehicle(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], JobVehicle[AccountData[playerid][pJobVehicle]][Locked]);
				ToggleVehicleLights(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], JobVehicle[AccountData[playerid][pJobVehicle]][Locked]);
				GameTextForPlayer(playerid, sprintf("~w~%s %s", GetVehicleName(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]), JobVehicle[AccountData[playerid][pJobVehicle]][Locked] ? ("~r~Locked") : ("~g~Unlocked")), 4000, 4);
			}
			return 1;
		}

		if(PlayerElectricJob[playerid][ElectricVehicle] == vehid)
		{
			PlayerPlaySound(playerid, 1147, 0.0, 0.0, 0.0);
			PlayerElectricJob[playerid][ElectricLocked] = !(PlayerElectricJob[playerid][ElectricLocked]);

			PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
			LockVehicle(PlayerElectricJob[playerid][ElectricVehicle], PlayerElectricJob[playerid][ElectricLocked]);
			ToggleVehicleLights(PlayerElectricJob[playerid][ElectricVehicle], PlayerElectricJob[playerid][ElectricLocked]);
			GameTextForPlayer(playerid, sprintf("~w~%s %s", GetVehicleName(PlayerElectricJob[playerid][ElectricVehicle]), PlayerElectricJob[playerid][ElectricLocked] ? ("~r~Locked") : ("~g~Unlocked")), 4000, 4);
			return 1;
		}
	}
	if(newkeys & KEY_CTRL_BACK)
	{
		if(IsPlayerInjured(playerid))
		{
		    SetPlayerInterior(playerid, 0);
		    SetPlayerVirtualWorld(playerid, 0);
		}
	}
	if(PRESSED(KEY_NO))
	{
		if(AccountData[playerid][pInjured])
		{
			if(SignalExists[playerid]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sudah mengirim signal, tunggu hingga EMS merespon!");
			
			GetPlayerPos(playerid, SignalPos[playerid][0], SignalPos[playerid][1], SignalPos[playerid][2]);
			SignalExists[playerid] = true;
			SignalTimer[playerid] = 120;
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim sinyal kepada EMS!");
			foreach(new i : Player) if (AccountData[i][pSpawned] && AccountData[i][pFaction] == FACTION_EMS) if (AccountData[i][pDutyEms])
			{
				SendClientMessageEx(i, -1, ""RED"[Emergency Signal]"WHITE" Signal terlah diterima dari daerah "YELLOW"%s", GetLocation(SignalPos[playerid][0], SignalPos[playerid][1], SignalPos[playerid][2]));
				Info(i, "Buka Smartphone ~> GPS ~> Signal Emergency (EMS) jika ingin merespon signal");
			}
		}
	}
	if((newkeys & KEY_NO) && aOfferID[playerid] == INVALID_PLAYER_ID)
	{
		if (AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tidak dapat membuka radial saat actvitity berjalan!");
		if (AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak ddapat melakukan ini ketika sedang pingsan!");
		
		ShowPlayerRadial1(playerid, true);
	}
	//-----[ Toll System ]-----	
	if(newkeys & KEY_CROUCH)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new forcount = MuchNumber(sizeof(BarrierInfo));
			for(new i = 0; i < forcount;i ++)
			{
				if(i < sizeof(BarrierInfo))
				{
					if(IsPlayerInRangeOfPoint(playerid,8.0,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]))
					{
						if(BarrierInfo[i][brOrg] == TEAM_NONE)
						{
							if(!BarrierInfo[i][brOpen])
							{
								if(AccountData[playerid][pMoney] < 100 && !IsVehicleFaction(GetPlayerVehicleID(playerid)))
								{
									ShowTDN(playerid, NOTIFICATION_INFO, "Anda membutuhkan "YELLOW"$100"WHITE" untuk membayar Toll");
								}
								else if(IsVehicleFaction(GetPlayerVehicleID(playerid)))
								{
									MoveDynamicObject(gBarrier[i],BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[i][brPos_A]+180);
									SetTimerEx("BarrierClose",15000,0,"i",i);
									BarrierInfo[i][brOpen] = true;
									ShowTDN(playerid, NOTIFICATION_INFO, "Hati hati dijalan, Pintu akan tertutup selama 15 detik");
									if(BarrierInfo[i][brForBarrierID] != -1)
									{
										new barrierid = BarrierInfo[i][brForBarrierID];
										MoveDynamicObject(gBarrier[barrierid],BarrierInfo[barrierid][brPos_X],BarrierInfo[barrierid][brPos_Y],BarrierInfo[barrierid][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[barrierid][brPos_A]+180);
										BarrierInfo[barrierid][brOpen] = true;
									}
								}
								else
								{
									MoveDynamicObject(gBarrier[i],BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[i][brPos_A]+180);
									SetTimerEx("BarrierClose",15000,0,"i",i);
									BarrierInfo[i][brOpen] = true;
									ShowTDN(playerid, NOTIFICATION_INFO, "Hati hati dijalan, Pintu akan tertutup selama 15 detik");
									ShowItemBox(playerid, "Removed $100", "Uang", 1212);
									TakeMoney(playerid, 100);
									if(BarrierInfo[i][brForBarrierID] != -1)
									{
										new barrierid = BarrierInfo[i][brForBarrierID];
										MoveDynamicObject(gBarrier[barrierid],BarrierInfo[barrierid][brPos_X],BarrierInfo[barrierid][brPos_Y],BarrierInfo[barrierid][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[barrierid][brPos_A]+180);
										BarrierInfo[barrierid][brOpen] = true;
									}
								}
							}
						}
						else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuka toll ini!");
						break;
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if((oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER) && AccountData[playerid][pTogAutoEngine])
	{
		if(!GetEngineStatus(vehicleid))
		{
			if(IsEngineVehicle(vehicleid) && !IsADealerVehicle(playerid, vehicleid))
			{
				AccountData[playerid][pTurningEngine] = true;
				SetTimerEx("EngineStatus", 2500, false, "id", playerid, vehicleid);
				SendRPMeAboveHead(playerid, "Mencoba menghidupkan mesin kendaraan", X11_PLUM1);
			}
		}
	}
	if(newstate == PLAYER_STATE_WASTED && AccountData[playerid][pJail] < 1)
    {	
		if(IsPlayerInEvent(playerid))
			return 1;

		SetPlayerArmedWeapon(playerid, 0);
		ResetPlayer(playerid);

		if(!AccountData[playerid][pInjured] && !IsPlayerInEvent(playerid))
		{
			AccountData[playerid][pInjured] = 1;
			AccountData[playerid][pInjuredTime] = 5400;
			
			AccountData[playerid][pInt] = GetPlayerInterior(playerid);
			AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

			GetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
			GetPlayerFacingAngle(playerid, AccountData[playerid][pPosA]);
		}
	}
	//Spec Player
	if(newstate == PLAYER_STATE_ONFOOT)
	{
		if(AccountData[playerid][playerSpectated] != 0)
		{
			foreach(new ii : Player)
			{
				if(AccountData[ii][pSpec] == playerid)
				{
					PlayerSpectatePlayer(ii, playerid);
					SendClientMessageEx(ii, -1, ""YELLOW"SPEC:"WHITE" %s(%d) sekarang berjalan kaki.", AccountData[playerid][pName], playerid);
				}
			}
		}
	}
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
		if(AccountData[playerid][pInjured] == 1)
        {
            //RemoveFromVehicle(playerid);
			RemovePlayerFromVehicle(playerid);
            SetPlayerHealthEx(playerid, 99999);
        }
		foreach (new ii : Player) if(AccountData[ii][pSpec] == playerid) 
		{
            PlayerSpectateVehicle(ii, GetPlayerVehicleID(playerid));
        }
	}
     
	new vehicle_index = -1;
	if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
	{
		if((newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) && PlayerVehicle[vehicle_index][vehAudio])
		{
			PlayVehicleAudio(playerid, vehicle_index);
		}
	}
	
	if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) && AccountData[playerid][pVehAudioPlay])
	{
		StopAudioStreamForPlayer(playerid);
		AccountData[playerid][pVehAudioPlay] = 0;
	}
	if(oldstate == PLAYER_STATE_DRIVER)
    {	
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)
            return RemovePlayerFromVehicle(playerid);/*RemoveFromVehicle(playerid);*/
		
		for(new i; i<14; i++)
		{
			TextDrawHideForPlayer(playerid, Speedo_Index[i]);
		}
		PlayerTextDrawHide(playerid, Speedo_Fuel[playerid]);
		PlayerTextDrawHide(playerid, Speedo_KMH[playerid]);
		PlayerTextDrawHide(playerid, Speedo_Location[playerid]);

		for(new i; i < 21; i++) {
        PlayerTextDrawHide(playerid, compastd[playerid][i]);
		}
		for(new j; j < 4; j++) {
			PlayerTextDrawShow(playerid, HappyLogo[playerid][j]);
		}
	}
	else if(newstate == PLAYER_STATE_DRIVER)
    {	
		static pviterid = -1;

		if((pviterid = Vehicle_Nearest2(playerid)) != -1)
		{
			if(IsABike(PlayerVehicle[pviterid][pVehPhysic]) || GetVehicleModel(PlayerVehicle[pviterid][pVehPhysic]) == 424)
			{
				if(PlayerVehicle[pviterid][pVehLocked])
				{
					RemovePlayerFromVehicle(playerid);
					ClearAnimations(playerid, 1);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini terkunci!");
					return 1;
				}
			}
		}
		if(!IsEngineVehicle(vehicleid))
        {
            SwitchVehicleEngine(vehicleid, true);
        }
		
		for(new i; i<14; i++)
		{
			TextDrawShowForPlayer(playerid, Speedo_Index[i]);
		}
		PlayerTextDrawShow(playerid, Speedo_KMH[playerid]);
		PlayerTextDrawShow(playerid, Speedo_Location[playerid]);
		PlayerTextDrawShow(playerid, Speedo_Fuel[playerid]);

		for(new i; i < 21; i++) {
        PlayerTextDrawShow(playerid, compastd[playerid][i]);
        }
        for(new j; j < 4; j++) {
            PlayerTextDrawHide(playerid, HappyLogo[playerid][j]);
        }
		new Float:health;
        GetVehicleHealth(GetPlayerVehicleID(playerid), health);
        VehicleHealthSecurityData[GetPlayerVehicleID(playerid)] = health;
        VehicleHealthSecurity[GetPlayerVehicleID(playerid)] = true;
		
		if(AccountData[playerid][playerSpectated] != 0)
  		{
			foreach(new ii : Player)
			{
    			if(AccountData[ii][pSpec] == playerid)
			    {
        			PlayerSpectateVehicle(ii, vehicleid);
					SendClientMessageEx(ii, -1, ""YELLOW"SPEC:"WHITE" %s(%d) sekarang mengendarai %s(%d).", AccountData[playerid][pName], playerid, GetVehicleModelName(GetVehicleModel(vehicleid)), vehicleid);
				}
			}
		}
		SetPVarInt(playerid, "LastVehicleID", vehicleid);
	}
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	switch(weaponid){ case 0..18, 39..54: return 1;} //invalid weapons
	if(1 <= weaponid <= 46 && AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] == weaponid)
	{
		AccountData[playerid][pAmmo][g_aWeaponSlots[weaponid]]--;
		if(AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] != 0 && !AccountData[playerid][pAmmo][g_aWeaponSlots[weaponid]])
		{
			AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] = 0;
		}
	}

	if(PlayerHasTazer(playerid) && AccountData[playerid][pFaction] == FACTION_POLISI)
	{
		SetPlayerArmedWeapon(playerid, 0);
		PlayerPlayNearbySound(playerid, 6003);
	}
	return 1;
}

stock GivePlayerHealth(playerid,Float:Health)
{
	new Float:health; GetPlayerHealth(playerid,health);
	SetPlayerHealth(playerid,health+Health);
}

/*public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new
        Float: vehicleHealth,
        playerVehicleId = GetPlayerVehicleID(playerid);

    new Float:health = GetPlayerHealth(playerid, health);
    GetVehicleHealth(playerVehicleId, vehicleHealth);
    if(AccountData[playerid][pSeatBelt] == 0 || AccountData[playerid][pHelmetOn] == 0)
    {
    	if(GetVehicleSpeed(vehicleid) <= 20)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -1);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 50)
    	{
    		new asakit = RandomEx(0, 2);
    		new bsakit = RandomEx(0, 2);
    		new csakit = RandomEx(0, 2);
    		new dsakit = RandomEx(0, 2);
    		AccountData[playerid][pLFoot] -= dsakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= dsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -2);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 90)
    	{
    		new asakit = RandomEx(0, 3);
    		new bsakit = RandomEx(0, 3);
    		new csakit = RandomEx(0, 3);
    		new dsakit = RandomEx(0, 3);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= csakit;
    		AccountData[playerid][pRFoot] -= dsakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -5);
    		return 1;
    	}
    	return 1;
    }
    if(AccountData[playerid][pSeatBelt] == 1 || AccountData[playerid][pHelmetOn] == 1)
    {
    	if(GetVehicleSpeed(vehicleid) <= 20)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -1);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 50)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		new dsakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= dsakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= dsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -1);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 90)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		new dsakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= csakit;
    		AccountData[playerid][pRFoot] -= dsakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -3);
    		return 1;
    	}
    }
    return 1;
}*/

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(damagedid != INVALID_PLAYER_ID && weaponid == WEAPON_CHAINSAW) {
        TogglePlayerControllable(playerid, 0);
        SetPlayerArmedWeapon(playerid, 0);
        TogglePlayerControllable(playerid, 1);
        SetCameraBehindPlayer(playerid);

        SetPVarInt(playerid, "ChainsawWarning", GetPVarInt(playerid, "ChainsawWarning")+1);

        if(GetPVarInt(playerid, "ChainsawWarning") == 3) {
			SendClientMessageToAllEx(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena Abusing Chainsaw!", ReturnName(playerid), playerid);
            DeletePVar(playerid, "ChainsawWarning");
            KickEx(playerid);
        }
    }
	else if(damagedid != INVALID_PLAYER_ID)
	{
		AccountData[damagedid][pLastShot] = playerid;
		AccountData[damagedid][pShotTime] = gettime();
		if(AccountData[playerid][pFaction] == FACTION_POLISI && PlayerHasTazer(playerid) && !AccountData[damagedid][pStunned])
		{
			if(GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus keadaan onfoot untuk dilumpuhkan!");
			
			if(GetPlayerDistanceFromPlayer(playerid, damagedid) > 5.0)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus lebih dekat untuk melumpuhkan pemain tersebut!");
			
			AccountData[damagedid][pStunned] = 10;
			TogglePlayerControllable(damagedid, 0);
			
			ApplyAnimation(damagedid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);
			ShowTDN(damagedid, NOTIFICATION_WARNING, "Kamu terkena stun gun / taser!");
		}
	}
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(!IsPlayerInEvent(playerid))
	{
		new sakit = RandomEx(1, 4);
		new asakit = RandomEx(1, 5);
		new bsakit = RandomEx(1, 7);
		new csakit = RandomEx(1, 4);
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 9)
		{
			AccountData[playerid][pHead] -= 20;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 3)
		{
			AccountData[playerid][pPerut] -= sakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 6)
		{
			AccountData[playerid][pRHand] -= bsakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 5)
		{
			AccountData[playerid][pLHand] -= asakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 8)
		{
			AccountData[playerid][pRFoot] -= csakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 7)
		{
			AccountData[playerid][pLFoot] -= bsakit;	
		}
	}
	if(issuerid != INVALID_PLAYER_ID && bodypart == 3 && weaponid >= 22 && weaponid <= 45)
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player) if (IsPlayerConnected(i)) if (SQL_IsCharacterLogged(i))
		{
			if(AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
			{
				SendClientMessageEx(i, X11_ORANGE1, "[WAR ALERT]"WHITE" Terdeteksi penembakan di daerah %s.", GetLocation(x, y, z));
			}
		}
	}
    return 1;
}

ptask Inspike_Timer[1000](playerid)
{
	if(!AccountData[playerid][pSpawned]) 
		return 0;

	static s_Keys, s_UpDown, s_LeftRight;
    GetPlayerKeys( playerid, s_Keys, s_UpDown, s_LeftRight );

    if ( AccountData[playerid][pFreeze] && ( s_Keys || s_UpDown || s_LeftRight ) )
        return 0;

	CheckPlayerInSpike(playerid);
    return 1;
}

task VehicleUpdate[30000]()
{
	foreach(new i: Vehicle) if (IsEngineVehicle(i) && GetEngineStatus(i))
	{
		if (GetFuel(i) > 0)
		{
			VehicleCore[i][vCoreFuel] --;
			if (GetFuel(i) <= 0)
			{
				SwitchVehicleEngine(i, false);
				VehicleCore[i][vCoreFuel] = 0;
			}
		}
	}
	return 1;
}

timer Vehicle_UpdatePosition[2000](vehicleid)
{
	new
		Float:x,
		Float:y,
		Float:z,
		Float:a
	;

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);

	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, a);
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new vehicle_index; // Index = Vehicle id ingame, vehicleid = Index DB
    vehicle_index = Vehicle_ReturnID(vehicleid);
    if(vehicle_index != RETURN_INVALID_VEHICLE_ID)
    {
		new panels, doors, lights, tires;
		GetVehicleDamageStatus(PlayerVehicle[vehicle_index][pVehPhysic], panels, doors, lights, tires);
		if(PlayerVehicle[vehicle_index][pVehBodyUpgrade] == 3 && PlayerVehicle[vehicle_index][pVehBodyRepair] > 0)
		{
			panels = doors = lights = tires = 0;
            UpdateVehicleDamageStatus(PlayerVehicle[vehicle_index][pVehPhysic], panels, doors, lights, tires);
			PlayerVehicle[vehicle_index][pVehBodyRepair] -= 50.0;
		}
		else if(PlayerVehicle[vehicle_index][pVehBodyRepair] <= 0)
		{
			PlayerVehicle[vehicle_index][pVehBodyRepair] = 0;
		}
	}
	if(GetPlayerJob(playerid) == JOB_DRIVER_MIXERS){
		if(jobs::mixer[playerid][mixerSlump] > 0 && IsValidVehicle(vehicleid))
		{
			new rand = RandomEx(2,4);
			jobs::mixer[playerid][mixerSlump]-=rand;

			new Float: progressvalue; 
			progressvalue = jobs::mixer[playerid][mixerSlump]*61/100;
			PlayerTextDrawTextSize(playerid, jobs::PBMixer[playerid], progressvalue, 13.0);
			PlayerTextDrawShow(playerid, jobs::PBMixer[playerid]);
		}
	}
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	new Float: vhealth;

	AntiCheatGetVehicleHealth(vehicleid, vhealth);
	SetVehicleHealth(vehicleid, vhealth);
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	defer Vehicle_UpdatePosition(vehicleid);

	for (new vid = 1; vid < sizeof(JobVehicle); vid ++) if (JobVehicle[vid][Vehicle] != INVALID_VEHICLE_ID)
	{
		if (vehicleid == JobVehicle[vid][Vehicle])
		{
			foreach(new i : Player)
			{
				if (AccountData[i][pJobVehicle] == JobVehicle[vid][Vehicle])
				{
					if (AccountData[i][pJobVehicle] != 0)
					{
						DestroyJobVehicle(i);
						AccountData[i][pJobVehicle] = 0;
						break;
					}
				}
			}
		}
	}

	foreach(new i : PvtVehicles) if (vehicleid == PlayerVehicle[i][pVehPhysic] && IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
	{
		if (PlayerVehicle[i][pVehRental] == -1)
		{
			PlayerVehicle[i][pVehInsuranced] = true;
			
			foreach(new pid : Player) if(PlayerVehicle[i][pVehOwnerID] == AccountData[pid][pID])
			{
				Syntax(pid, "Kendaraan anda rusak dan sudah dikirimkan ke Asuransi!");
			}
			
			for (new slot = 0; slot < MAX_VEHICLE_OBJECT; slot ++) if (VehicleObjects[i][slot][vehObjectExists])
			{
				if (VehicleObjects[i][slot][vehObject] != INVALID_STREAMER_ID)
					DestroyDynamicObject(VehicleObjects[i][slot][vehObject]);
				
				VehicleObjects[i][slot][vehObject] = INVALID_STREAMER_ID;
			}

			if (IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
			
			PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
		}
		else
		{
			PlayerVehicle[i][pVehRental] = -1;
			PlayerVehicle[i][pVehRentTime] = 0;
			PlayerVehicle[i][pVehExists] = false;

			foreach(new pid : Player) if(PlayerVehicle[i][pVehOwnerID] == AccountData[pid][pID])
			{
				Info(pid, "Kendaaraanmu rental anda telah hancur. Anda dikenakan denda sebesar "GREEN"%s!", FormatMoney(PlayerVehicle[i][pVehPrice]/2));
				TakeMoney(pid, (PlayerVehicle[i][pVehPrice]/2));
			}

			if(IsValidVehicle(PlayerVehicle[i][pVehPhysic])) 
			{
				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
				PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
			}

			new cQuery[200];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "DELETE FROM `player_vehicles` WHERE `id` = '%d'", PlayerVehicle[i][pVehID]);
			mysql_tquery(g_SQL, cQuery);

			Vehicle_ResetVariable(i);
			Iter_Remove(PvtVehicles, i);
		}
	}

	//ini untuk menghapus kendaraan yang dispawn oleh admin
	if(VehicleCore[vehicleid][vehAdmin])
	{
		DestroyVehicle(VehicleCore[vehicleid][vehAdminPhysic]);
		VehicleCore[vehicleid][vehAdminPhysic] = INVALID_VEHICLE_ID;
		VehicleCore[vehicleid][vehAdmin] = false;
	}
	return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	if(newstate)
	{
		SwitchVehicleLight(vehicleid, true);
		vehicleid = GetPlayerVehicleID(playerid);
		
		foreach(new i : PvtVehicles)
		{
			if(vehicleid == PlayerVehicle[i][pVehPhysic])
			{
				if(PlayerVehicle[i][pVehFaction] != FACTION_POLISI && PlayerVehicle[i][pVehFaction] != FACTION_EMS) 
					return 0;

				gToggleELM[vehicleid] = true;
				gELMTimer[vehicleid] = SetTimerEx("ToggleELM", 80, true, "d", vehicleid);
			}
		}
	}
	else 
	{
		static panels, doors, lights, tires;

		gToggleELM[vehicleid] = false;
		KillTimer(gELMTimer[vehicleid]);

		GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
		UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
	}
	return 1;
}

hook OnVehicleCreated(vehicleid)
{
	TrunkVehEntered[vehicleid] = INVALID_PLAYER_ID;
	return 1;
}

hook OnVehicleDestroyed(vehicleid)
{
	new index = -1;
    //new playerid = GetVehicleDriver(vehicleid);
	if((index = Vehicle_GetID(vehicleid)) != -1)
	{
		if(PlayerVehicle[index][vehSirenOn])
		{
			PlayerVehicle[index][vehSirenOn] = false;
			if(IsValidDynamicObject(PlayerVehicle[index][vehSirenObject]))
			{
				DestroyDynamicObject(PlayerVehicle[index][vehSirenObject]);
				PlayerVehicle[index][vehSirenObject] = INVALID_STREAMER_ID;
			}
		}

		if(IsBagasiOpened[PlayerVehicle[index][pVehPhysic]])
		{
			IsBagasiOpened[PlayerVehicle[index][pVehPhysic]] = false;
		}

		if(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]] != INVALID_PLAYER_ID)
		{
			new Float:x, Float:y, Float:z;
			GetVehicleBoot(vehicleid, x, y, z);
			PlayerSpectateVehicle(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], INVALID_VEHICLE_ID);

			SetSpawnInfo(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], 0, AccountData[TrunkVehEntered[PlayerVehicle[index][pVehPhysic]]][pSkin], x, y, z, 0.0, 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], false);
			SetPVarInt(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], "PlayerInTrunk", 0);
			AccountData[TrunkVehEntered[PlayerVehicle[index][pVehPhysic]]][pTempVehID] = INVALID_VEHICLE_ID;
			TrunkVehEntered[PlayerVehicle[index][pVehPhysic]] = INVALID_PLAYER_ID;
		}

		for (new slot = 0; slot < MAX_VEHICLE_OBJECT; slot ++) if (VehicleObjects[index][slot][vehObjectExists])
		{
			if (VehicleObjects[index][slot][vehObject] != INVALID_STREAMER_ID)
				DestroyDynamicObject(VehicleObjects[index][slot][vehObject]);
			
			VehicleObjects[index][slot][vehObject] = INVALID_STREAMER_ID;
		}
		
		PlayerVehicle[index][pVehPhysic] = INVALID_VEHICLE_ID;
	}

	if(gToggleELM[vehicleid])
	{
		gToggleELM[vehicleid] = false;
		KillTimer(gELMTimer[vehicleid]);
	}
	foreach(new ii : Player) if(jobs::mixer[ii][mixerVehicle] == vehicleid) 
	{
		if(jobs::mixer[ii][mixerDuty][0] && IsValidVehicle(jobs::mixer[ii][mixerVehicle]))
		{
			for(new i; i<3; i++)
			{
				TextDrawHideForPlayer(ii, jobs::GBMixer[i]);
			}
			PlayerTextDrawHide(ii, jobs::PBMixer[ii]);
			jobs::mixer_reset_enum(ii);
			ShowTDN(ii, NOTIFICATION_WARNING, "Anda gagal mengirimkan beton karena kendaraan anda hancur!");
		}
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(AccountData[playerid][pTogAutoEngine] && !IsABicycle(vehicleid))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(GetEngineStatus(vehicleid)) 
			{
				AccountData[playerid][pTempVehID] = vehicleid;
				SetTimerEx("EngineTurnOff", 1500, false, "dd", playerid, vehicleid);
			}
		}
	}
	return 1;
}

forward EngineTurnOff(playerid, vehicleid);
public EngineTurnOff(playerid, vehicleid)
{
	if(AccountData[playerid][pTempVehID] == vehicleid)
	{
		SwitchVehicleEngine(vehicleid, false);
		SendRPMeAboveHead(playerid, "Mesin mati", X11_LIGHTGREEN);	
	
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
	}
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
   	if((AccountData[playerid][pAdmin] >= 1 || AccountData[playerid][pTheStars] >= 1) && AccountData[playerid][pAdminDuty] == 1)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid > 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            SetVehiclePos(vehicleid, fX, fY, fZ+10);
        }
        else
        {
            SetPlayerPosFindZ(playerid, fX, fY, 999.0);
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 0);
        }
    }

	if(AccountData[playerid][pAdmin] >= 1 || AccountData[playerid][pTheStars] >= 1)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid > 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			SetPVarFloat(playerid, "tpX", fX);
			SetPVarFloat(playerid, "tpY", fY);
			SetPVarFloat(playerid, "tpZ", fZ + 5.0);
		}
		else 
		{
			SetPVarFloat(playerid, "tpX", fX);
			SetPVarFloat(playerid, "tpY", fY);
			SetPVarFloat(playerid, "tpZ", fZ);
		}
	}
    return 1;
}

Dialog:DOKUMENT_MENU(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
	}

	switch(listitem)
	{
		case 1: // lihat ktp
		{
			if(!AccountData[playerid][Ktp]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki KTP!");
			ShowKTPTD(playerid);
		}
		case 2: // Tunjukan KTP
		{
			if(!AccountData[playerid][Ktp]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki KTP!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					ShowMyKTPTD(playerid, i);
				}
			}
		}
		case 3: // Lihat SIM
		{
			DisplayLicensi(playerid, playerid);
		}
		case 4: // Tunjukan SIM
		{
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplayLicensi(i, playerid);
				}
			}
		}
		case 5: // Lihat SKWB
		{
			if (!AccountData[playerid][pSKWB]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKWB!");

			DisplaySKWB(playerid, playerid);
		}
		case 6: // tunjukan SKWB
		{
			if(!AccountData[playerid][pSKWB]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKWB!");
			
			foreach(new i : Player) if (IsPlayerConnected(i))
			{
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplaySKWB(playerid, i);
				}
			}
		}

		case 8: //lihat bpjs
		{
			if(!AccountData[playerid][pBPJS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki BPJS/Expired!");
			DisplayBPJS(playerid, playerid);
		}
		case 9: //tunjukan bpjs
		{
			if(!AccountData[playerid][pBPJS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki BPJS/Expired!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{   
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplayBPJS(i, playerid);
				}
			}
		}
		case 10: //lihat skck
		{
			if(!AccountData[playerid][pSKCK]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKCK/Expired!");
			DisplaySKCK(playerid, playerid);
		}
		case 11: //tunjuk skck
		{
			if(!AccountData[playerid][pSKCK]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKCK/Expired!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{   
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplaySKCK(i, playerid);
				}
			}
		}
		case 12: //lihat sks
		{
			if(!AccountData[playerid][pSKS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Surat Keterangan Sehat/Expired!");
			DisplaySKS(playerid, playerid);
		}
		case 13: //tunjuk sks
		{
			if(!AccountData[playerid][pSKS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Surat Keterangan Sehat/Expired!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{   
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplaySKS(i, playerid);
				}
			}
		}
	}
	return 1;
}


public OnClickDynamicTextDraw(playerid, Text:textid)
{
	//innventory
	
	return 1;
}

public OnClickDynamicPlayerTextDraw(playerid, PlayerText: textid)
{
	for(new i = 0; i<MAX_REMEMBERS; i++) if(textid == RobTD[playerid][i])
	{
		if(RememberData[playerid][i][remindersMustClicked])
		{
			PlayerPlaySound(playerid, 21001, 0,0,0);
			PlayerTextDrawColor(playerid, RobTD[playerid][i], 2129619967);
			PlayerTextDrawShow(playerid, RobTD[playerid][i]);
			RobCount[playerid]++;
			if(RobCount[playerid] >= 5) RobWarung_Succes(playerid);
		}
		else RobValue[playerid] -= 1.0;
	}
	if(textid == inv::string[playerid][25])//close
	{
		Inventory_Close(playerid);
	}
	if(textid == inv::string[playerid][21])//amount
	{
		if(AccountData[playerid][pSelectItem] == -1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih item!");
		ShowPlayerDialog(playerid, DIALOG_SETAMOUNT, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Set Amount",
		"Mohon masukkan berapa jumlah item yang akan diberikan:", "Set", "Batal");
	}
	if(textid == inv::string[playerid][22])//use
	{
		new
			itemid = AccountData[playerid][pSelectItem],
			string[64];

		if(AccountData[playerid][pSelectItem] == -1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih barang!");
		strunpack(string, InventoryData[playerid][itemid][invItem]);
			
		if(ItemCantUse(string)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak bisa digunakan!");
		OnPlayerUseItem(playerid, itemid, string);
	}
	if(textid == inv::string[playerid][23])//give
	{
		if(AccountData[playerid][pSelectItem] == -1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih barang!");
		if(AccountData[playerid][pAmountInv] == 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum input jumlah yang akan diberikan!");
		
		new frmxt[355], string[512];
		strunpack(string, InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem]);
		

		if(!strcmp(string, "Sampah Makanan"))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memberikan sampah kepada orang lain!");
		
		if(!strcmp(string, "Boombox"))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memberikan Boombox kepada orang lain!");

		new count = 0;
		foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5))
		{
			format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
			NearestPlayer[playerid][count++] = i;
		}
		
		if(count == 0)
		{
			PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
			Inventory_Close(playerid);
			return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""City"Happy Roleplay "WHITE"- Give Item",
			"Tidak ada player yang dekat dengan anda!", "Tutup", "");
		}

		ShowPlayerDialog(playerid, DIALOG_MEMBERI, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Give Item", frmxt, "Pilih", "Close");
	}
	if(textid == inv::string[playerid][24])//drop
	{
		if(AccountData[playerid][pSelectItem] < 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih barang!");
		if(AccountData[playerid][pAmountInv] == 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum menentukan jumlah barang!");
		if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
		
		new itemid = AccountData[playerid][pSelectItem],
			amount = AccountData[playerid][pAmountInv],
			model = InventoryData[playerid][AccountData[playerid][pSelectItem]][invModel],
			string[ 256 ];
		
		strunpack(string, InventoryData[playerid][itemid][invItem]);
		
		new trash_nearest = TrashNearest(playerid);
		if(trash_nearest != -1)
		{
			if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");
			if(amount > InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda tidak memiliki %s sebanyak itu!", string));
			Inventory_Remove(playerid, string, amount);
			Inventory_Close(playerid);
			ShowItemBox(playerid, sprintf("Removed %dx", amount), string, model);
			ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);

			SendRPMeAboveHead(playerid, sprintf("Membuang %d %s miliknya ke tong sampah", amount, string), X11_PLUM1);
		}
		else if(IsPeleburanArea(playerid))
		{
			if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
			if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
			if(amount < 1 || amount > InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

			Inventory_Remove(playerid, string, amount);
			Inventory_Close(playerid);
			ShowItemBox(playerid, sprintf("Removed %dx", amount), string, model);
			ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
			
			SendRPMeAboveHead(playerid, sprintf("Melempar %d %s ke tempat peleburan", amount, string), X11_PLUM1);
		}
		else
		{
			if(!strcmp(string, "Sampah Makanan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang sampah sembarangan!");
				return 1;
			}
			else if(!strcmp(string, "Hiu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Penyu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Kayu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Kayu Potongan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Ayam Hidup"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Ayam Potongan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Bulu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Boxmats"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Pancingan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Umpan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Batu Kotor"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Batu Bersih"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Petrol"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Pure Oil"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "GAS"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}

			if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah input tidak valid!");
			if(amount > InventoryData[playerid][itemid][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda tidak memiliki %s sebanyak itu!", string));
			
			if(!strcmp(string, "Radio", true))
			{
				if(ToggleRadio[playerid] || RadioMicOn[playerid])
				{
					ToggleRadio[playerid] = false;
					RadioMicOn[playerid] = false;
					CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, false);
					CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, false);
					CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, 0);
					PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "0");
				}
			}
			DropPlayerItem(playerid, itemid, amount);
		}
	}
	if (textid == RADIALHAPPY[playerid][15]) // Close Radial 1
	{
		PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
	}

	if (textid == RADIALHAPPY[playerid][9]) // Kendaraan
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		new vehid = GetNearestVehicleToPlayer(playerid, 3.5, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun di sekitar!"), CancelSelectTextDraw(playerid);
		
		static string[178];
		NearestVehicleID[playerid] = vehid;
		format(string, sizeof(string), "Kunci\
		\n"GRAY"Lampu\
		\nHood buka/tutup\
		\n"GRAY"Trunk buka/tutup\
		\nBagasi\
		\n"GRAY"Holster\
		\nMasuk ke dalam bagasi");
		
		ShowPlayerDialog(playerid, DIALOG_VEHICLE_MENU, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Vehicle Menu",
		string, "Pilih", "Batal");
	}

	if (textid == RADIALHAPPY[playerid][8]) // Dokument
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		Dialog_Show(playerid, DOKUMENT_MENU, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Dokument",
		""YELLOW"Identitas:\
		\n\n> Lihat KTP\
		\n"GRAY"> Tunjukan KTP\
		\n> Lihat SIM\
		\n"GRAY"> Tunjukan SIM\
		\n> Lihat SKWB\
		\n"GRAY"> Tunjukan SKWB\
		\n\n"YELLOW"Dokument:\
		\n\n> Lihat BPJS\
		\n"GRAY"> Perlihatkan BPJS\
		\n> Lihat SKCK\
		\n"GRAY"> Perlihatkan SKCK\
		\n> Lihat SKS\
		\n"GRAY"> Perlihatkan SKS", "Pilih", "Batal");
	}

	if (textid == RADIALHAPPY[playerid][13]) // Faction Panel
	{
		new frmtx[300], count = 0;

		foreach(new i : Player) if (i != playerid) if (IsPlayerNearPlayer(playerid, i, 2.5))
		{
			format(frmtx, sizeof(frmtx), "%sPlayer ID: %d\n", frmtx, i);
			NearestPlayer[playerid][count++] = i;
		}
			
		if (AccountData[playerid][pFaction] == FACTION_NONE && AccountData[playerid][pFamily] == -1)
		{
			Dialog_Show(playerid, PANEL_NONE, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Menu Warga", "Drag/Undrag Person", "Pilih", "Batal");
			ShowPlayerRadial1(playerid, false);
		}
		else if (AccountData[playerid][pFaction] == FACTION_TRANS && AccountData[playerid][pFamily] == -1)
		{
			Dialog_Show(playerid, PANEL_NONE, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Menu Warga", "Drag/Undrag Person", "Pilih", "Batal");
			ShowPlayerRadial1(playerid, false);
		}
		else
		{
			if (count > 0)
			{
				Dialog_Show(playerid, DialogKantongPanel, DIALOG_STYLE_LIST, ""City"Happy Roleplay"WHITE" - Faction Panel", frmtx, "Pilih", "Batal");
			}
			else ShowTDN(playerid, NOTIFICATION_WARNING, "Tidak ada orang disekitar anda!");
			
			return ShowPlayerRadial1(playerid, false);
		}
		
		if (AccountData[playerid][pFamily] > -1 && AccountData[playerid][pFamilyRank] > 1)
		{
			if (count > 0)
			{
				Dialog_Show(playerid, FamiliesKantongList, DIALOG_STYLE_LIST, ""City"Happy Roleplay"WHITE" - Faction Panel (Gang)", frmtx, "Pilih", "Batal");
			}
			else ShowTDN(playerid, NOTIFICATION_WARNING, "Tidak ada orang disekitar anda!");
			return ShowPlayerRadial1(playerid, false);
		}
	}

	if (textid == RADIALHAPPY[playerid][10]) // Inventory
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);

		if(AccountData[playerid][ActivityTime] != 0)
		{
			CancelSelectTextDraw(playerid);
			return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
		}
		
		Inventory_Show(playerid);
		PlayerPlaySound(playerid, 1039, 0.0, 0.0, 0.0);
	}

	if (textid == RADIALHAPPY[playerid][14]) // Clothes
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		callcmd::fashion(playerid);
	}

	if (textid == RADIALHAPPY[playerid][12]) // Invoice
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		ShowPlayerInvoice(playerid);
	}

	if (textid == RADIALHAPPY[playerid][11]) // Smartphone
	{
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		ShowingSmartphone(playerid);
	}
	//job mixer
	if(textid == jobs::Pmixer[playerid][5])
	{
		jobs::mixer_select_case(playerid, 1);
	}
	if(textid == jobs::Pmixer[playerid][6])
	{
		jobs::mixer_select_case(playerid, 2);
	}
	if(textid == jobs::Pmixer[playerid][7])
	{
		jobs::mixer_select_case(playerid, 3);
	}
	if(textid == jobs::Pmixer[playerid][8])
	{
		jobs::mixer_select_case(playerid, 4);
	}
	if(textid == jobs::Pmixer[playerid][9])
	{
		jobs::mixer_select_case(playerid, 5);
	}
	if(textid == jobs::Pmixer[playerid][10])//confirm
	{
		jobs::mixer_confirm(playerid);
	}
	//phone_funcs
	
	if(textid == CloseButtonPhone[playerid])
    {
        Toggle_PhoneTD(playerid, false);
        CancelSelectTextDraw(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        RemovePlayerAttachedObject(playerid, 9);
        AccountData[playerid][phoneShown] = false;
        SendRPMeAboveHead(playerid, "Menutup HP Miliknya.", X11_PLUM1);
    }

    if(textid == ContactButtonPhone[playerid])
    {
        ShowPlayerDialog(playerid, DialogOpenContact, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Kontak", "Tambahkan Kontak Baru\nLihat Daftar Kontak", "Pilih", "Batal");
    }

    if(textid == GpsButtonPhone[playerid])
    {
        if(BusIndex[playerid] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai supir bus!");
        if(DurringSweeping[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai pembersih jalan!");
        if(PlayerKargoVars[playerid][KargoStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai Supir Kargo!");

        if(AccountData[playerid][pFaction] == FACTION_EMS && AccountData[playerid][pDutyEms]) {
            Dialog_Show(playerid, GpsMenu, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Menu Gps",
            "Lokasi GPS\n"GRAY"Signal Emergency (EMS)", "Pilih", "Batal");
        } else {
            ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Lokasi",
			"Lokasi Umum\
			\n"GRAY"Lokasi Pekerjaan\
			\nLokasi Hobi\
			\n"GRAY"Lokasi Pertokoan\
			\nLokasi Workshop\
			\n"GRAY"ATM Terdekat\
			\nGarasi Umum Terdekat\
			\n"GRAY"Tong Sampah Terdekat\
			\nWarung Terdekat\
			\n"GRAY"Pom Bensin Terdekat\
			\nBengkel Modshop\
			\n"GRAY"Rumah Saya\
			\n"RED"(Disable Checkpoint)\
			\n"RED"(Disable Shareloc)", "Pilih", "Batal");
        }
    }

    if(textid == AirdropButtonPhone[playerid])
    {
        new strings[255];
        format(strings, sizeof(strings), "Status: %s\
        \nShare Contacts", AccountData[playerid][AirdropPermission] ? ""LIGHTGREEN"Share Contact diizinkan" : ""RED"Share Contact tidak diizinkan");
        
        ShowPlayerDialog(playerid, DIALOG_AIRDROPDISPLAY, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Airdrop", strings, "Pilih", "Batal");
    }

    if(textid == SettingButtonPhone[playerid])
    {
        Dialog_Show(playerid, SettingPhone, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Pengaturan",
        "Tentang Ponsel\
        \n"GRAY"Ubah Nada Dering Telepon\
        \nHapus Nada Dering\
        \n"GRAY"%s Mode Pesawat", "Pilih", "Batal", AccountData[playerid][phoneAirplaneMode] ? "Matikan" : "Nyalakan");
    }

    if(textid == VehicleButtonPhone[playerid])
    {
        // ShowContactList(playerid);
        callcmd::myv(playerid, "");
    }

    if(textid == WhatsappButtonPhone[playerid])
    {
        ShowContactList(playerid);
    }

    if(textid == SpotifyButtonPhone[playerid])
    {
        Toggle_PhoneTD(playerid, false);
        Toggle_SpotifyTD(playerid, true);
    }

    if(textid == CloseSpotifyButton[playerid])
    {
        Toggle_SpotifyTD(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }

    if(textid == YellowButtonPhone[playerid])
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_MENU, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Yellow Pages",
        "Melihat antrian iklan\nKirim iklan baru", "Pilih", "Batal");
    }

    if(textid == CallButtonPhone[playerid])
    {
        ShowPlayerDialog(playerid, DialogTelepon, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Telepon", "Mohon masukan nomor telepon yang ingin anda hubungi:", "Telfon", "Batal");
    }

    if(textid == BankButtonPhone[playerid])
    {
        Toggle_PhoneTD(playerid, false);
        Toggle_BankTD(playerid, true);
    }

    if(textid == CloseCallButton[playerid])
    {
        Toggle_CallTD(playerid, false);
        PlayerTextDrawHide(playerid, RedButtonincomingCall[playerid]);
        PlayerTextDrawHide(playerid, GreenButtonincomingCall[playerid]);
        PlayerTextDrawHide(playerid, RedButtonoutComingCall[playerid]);
        CancelSelectTextDraw(playerid);
        AccountData[playerid][phoneShown] = false;
    }

    if(textid == TransButtonPhone[playerid])
    {
        if(AccountData[playerid][phoneAirplaneMode]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone anda sedang Mode Pesawat!");
        if(AccountData[playerid][pTaxiPlayer] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang menjadi penumpang di Trans!");
        
        ShowPlayerDialog(playerid, DIALOG_TRANSORDER, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Pesan Transportasi",
        "Hai, kamu ingin memesan Trans, mau kemana hari ini?", "Input", "Batal");
    }

    if(textid == CloseBankButton[playerid])
    {
        Toggle_BankTD(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }

    if(textid == CloseTwitterHome[playerid])
    {
        Toggle_TwitterHome(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }
    
    if(textid == CloseTwitterHomePage[playerid])
    {
        Toggle_TwitterHomepage(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }

    if(textid == TwitterButtonPhone[playerid])
    {
        Toggle_PhoneTD(playerid, false);
        if(!AccountData[playerid][Twitter])
        {
            Toggle_TwitterHome(playerid, true);
        }
        else
        {
            Toggle_TwitterHomepage(playerid, true);
        }
    }

    if(textid == TransferBankButton[playerid])
    {
        ShowPlayerDialog(playerid, DialogTransfer, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Transfer", 
        "Mohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");
    }

    if(textid == ATRP_SpotifyTD[playerid][17]) // Earphone
    {
        if(AccountData[playerid][pEarphone] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Earphone!");
        
        ShowPlayerDialog(playerid, DialogSpotify, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Spotify", "Matikan Musik\nPutar Musik", "Select", "Cancel");
    }

    if(textid == ATRP_SpotifyTD[playerid][18]) // boomboox
    {
        if(!AccountData[playerid][pVip]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");

        if(GetPVarType(playerid, "PlacedBB"))
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ")))
			{
				ShowPlayerDialog(playerid, DANN_BOOMBOX, DIALOG_STYLE_LIST, ""City"Happy Roleplay "WHITE"- Boombox", "Matikan Boombox\nPutar Musik", "Select", "Cancel");
			}
			else
			{
	   			return ShowTDN(playerid, NOTIFICATION_ERROR, "~g~[!]~w~: Kamu tidak berada didekat boombox mu!");
			}
	    }
	    else
	    {
	    	ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak menaruh boombox sebelumnya!");
		}  
    }

    if(textid == ATRP_TwitterHomeTD[playerid][19]) // Daftar
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_TWITTER_SIGN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Daftar Twitter",
        "Hai, selamat datang di Twitter!\
        \nSilahkan masukkan username Twitter kamu, ini akan ditampilkan pada setiap post tweet yang kamu buat:\
        \nIngat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\
        \nPanjang username 7 - 24 karakter!", "Set", "Batal");
    }

    if(textid == ATRP_TwitterHomeTD[playerid][17]) // Login Jika sudah punya akun twitter
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_TWITTER_LOGIN, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Login Twitter", 
        "Hai, selamat datang di Twitter!\
        \nSilahkan masukkan username Twitter kamu yang telah terdaftar:", "Input", "Batal");
    }

    if(textid == ATRP_TwitterHomepageTD[playerid][17]) // Tweet
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerTwitterPage(playerid);
        AccountData[playerid][CurrentlyReadTwitter] = true;
    }

    if(textid == ATRP_TwitterHomepageTD[playerid][19]) // Logout Twitter
    {
        Toggle_TwitterHomepage(playerid, false);
        Toggle_TwitterHome(playerid, true);
        AccountData[playerid][Twitter] = false;
    }

    if(textid == RedButtonincomingCall[playerid])
    {
        foreach(new i : Player) if(IsPlayerConnected(i) && AccountData[i][phoneCallingWithPlayerID] == playerid)
        {
            new phoneCallFromID = i;
            ApplyAnimation(phoneCallFromID, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            RemovePlayerAttachedObject(phoneCallFromID, 9);
            
            ApplyAnimation(playerid, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            RemovePlayerAttachedObject(playerid, 9);

            if(AccountData[playerid][phoneShown]) {
                AccountData[playerid][phoneShown] = false;
            }
            
            if(AccountData[phoneCallFromID][phoneShown]) {
                AccountData[phoneCallFromID][phoneShown] = false;
            }

            HideAllSmartphone(playerid), HideAllSmartphone(phoneCallFromID);
            Toggle_CallTD(playerid, false), Toggle_CallTD(phoneCallFromID, false);
            CancelSelectTextDraw(playerid), CancelSelectTextDraw(phoneCallFromID);
            PlayerTextDrawHide(playerid, RedButtonincomingCall[playerid]);
            PlayerTextDrawHide(playerid, GreenButtonincomingCall[playerid]);
            PlayerTextDrawHide(phoneCallFromID, RedButtonoutComingCall[playerid]);
            StopAudioStreamForPlayer(playerid);
            
            AccountData[playerid][phoneCallingTime] = 0;
            AccountData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneIncomingCall] = false;
            
            AccountData[phoneCallFromID][phoneCallingTime] = 0;
            AccountData[phoneCallFromID][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[phoneCallFromID][phoneIncomingCall] = false;
            AccountData[phoneCallFromID][phoneIncomingCall] = false;
        }
    }

    if(textid == GreenButtonincomingCall[playerid])
    {
        if(AccountData[playerid][phoneDurringConversation]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang dalam percakapan!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan tidak dapat mengangkat panggilan!");
        foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][phoneCallingWithPlayerID] == playerid)
        {
            new callingWithPlayerID = i;
            AccountData[playerid][phoneDurringConversation] = true;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneCallingTime] = 0;
            AccountData[playerid][phoneCallingWithPlayerID] = callingWithPlayerID;

            AccountData[callingWithPlayerID][phoneDurringConversation] = true;
            AccountData[callingWithPlayerID][phoneIncomingCall] = false;
            AccountData[callingWithPlayerID][phoneCallingTime] = 0;
            AccountData[callingWithPlayerID][phoneCallingWithPlayerID] = playerid;

            ApplyAnimationEx(playerid, "ped", "phone_talk", 3.1, 0, 1, 0, 1, 1, 1);
            SetPlayerAttachedObject(playerid, 9, 18870, 6,  0.099000, 0.009999, 0.000000,  78.200027, 179.000061, -1.500000,  1.000000, 1.000000, 1.000000); // 276
            
            ApplyAnimationEx(callingWithPlayerID, "ped", "phone_talk", 3.1, 0, 1, 0, 1, 1, 1);
            SetPlayerAttachedObject(callingWithPlayerID, 9, 18870, 6,  0.099000, 0.009999, 0.000000,  78.200027, 179.000061, -1.500000,  1.000000, 1.000000, 1.000000); // 276
            
            static contnstr[25];
            format(contnstr, sizeof(contnstr), "%s", AccountData[callingWithPlayerID][pPhone]);
            for(new cid; cid < MAX_CONTACTS; ++cid)
            {
                if(ContactData[playerid][cid][contactExists])
                {
                    if(!strcmp(ContactData[playerid][cid][contactNumber], AccountData[callingWithPlayerID][pPhone], false))
                    {
                        format(contnstr, sizeof(contnstr), "%s", ContactData[playerid][cid][contactName]);
                    }
                }
            }
            PlayerTextDrawSetString(playerid, ContactNameTD[playerid], contnstr);
            StopAudioStreamForPlayer(playerid);

            HideAllSmartphone(playerid), HideAllSmartphone(callingWithPlayerID);
            PlayerTextDrawHide(playerid, GreenButtonincomingCall[playerid]);
            PlayerTextDrawHide(playerid, RedButtonincomingCall[playerid]);
            PlayerTextDrawShow(playerid, RedButtonoutComingCall[playerid]);
            Toggle_CallTD(playerid, true), Toggle_CallTD(callingWithPlayerID, true);
            CancelSelectTextDraw(playerid), CancelSelectTextDraw(callingWithPlayerID);
            CallRemoteFunction("ConnectPlayerCalling", "dd", playerid, callingWithPlayerID);
        }
    }

    if(textid == RedButtonoutComingCall[playerid])
    {
        new callDurringWithPlayerID = AccountData[playerid][phoneCallingWithPlayerID];
        if(!AccountData[playerid][phoneIncomingCall] && callDurringWithPlayerID != INVALID_PLAYER_ID)
        {
            if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ClearAnimations(playerid, 1);
                ApplyAnimation(playerid, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            }
            
            if(!IsPlayerInAnyVehicle(callDurringWithPlayerID) && GetPlayerState(callDurringWithPlayerID) == PLAYER_STATE_ONFOOT)
            {
                ClearAnimations(callDurringWithPlayerID, 1);
                ApplyAnimation(callDurringWithPlayerID, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            }
            RemovePlayerAttachedObject(playerid, 9);
            RemovePlayerAttachedObject(callDurringWithPlayerID, 9);
            CallRemoteFunction("DisconnectPlayerCalling", "dd", playerid, callDurringWithPlayerID);

            if(AccountData[playerid][phoneShown]) {
                AccountData[playerid][phoneShown] = false;
            }
            
            if(AccountData[callDurringWithPlayerID][phoneShown]) {
                AccountData[callDurringWithPlayerID][phoneShown] = false;
            }

            HideAllSmartphone(playerid), HideAllSmartphone(callDurringWithPlayerID);
            Toggle_CallTD(playerid, false), Toggle_CallTD(callDurringWithPlayerID, false);
            PlayerTextDrawHide(playerid, RedButtonoutComingCall[playerid]), PlayerTextDrawHide(callDurringWithPlayerID, RedButtonoutComingCall[callDurringWithPlayerID]);
            PlayerTextDrawHide(callDurringWithPlayerID, RedButtonincomingCall[callDurringWithPlayerID]), PlayerTextDrawHide(callDurringWithPlayerID, GreenButtonincomingCall[callDurringWithPlayerID]);
            CancelSelectTextDraw(playerid), CancelSelectTextDraw(callDurringWithPlayerID);
            StopAudioStreamForPlayer(callDurringWithPlayerID);
            AccountData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[playerid][phoneDurringConversation] = false;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneCallingTime] = 0;
            
            AccountData[callDurringWithPlayerID][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[callDurringWithPlayerID][phoneDurringConversation] = false;
            AccountData[callDurringWithPlayerID][phoneIncomingCall] = false;
            AccountData[callDurringWithPlayerID][phoneCallingTime] = 0;
            Info(playerid, "Telepon terputus...");
            Info(callDurringWithPlayerID, "Telepon terputus...");
        }
        else
        {
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
            RemovePlayerAttachedObject(playerid, 9);

            if(AccountData[playerid][phoneShown]) {
                AccountData[playerid][phoneShown] = false;
            }
            PlayerTextDrawHide(playerid, RedButtonoutComingCall[playerid]);
            HideAllSmartphone(playerid);
            Toggle_CallTD(playerid, false);
            CancelSelectTextDraw(playerid);
            AccountData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[playerid][phoneDurringConversation] = false;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneCallingTime] = 0;
            Info(playerid, "Nomor tersebut berada di panggilan lain/tidak aktif...");
        }
    }
	//showroom
	new showroomID = GetPVarInt(playerid, "SelectShowroomID");
    if(textid == ATRP_ShowroomTD[playerid][11]) // Next Veh
    {
        if(showroomID != 0)
        {
            if(showroomID == 1) // Truk
            {
                if(SelectVeh[playerid] == sizeof(TrukShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleTruckSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(TrukShowroom[SelectVeh[playerid]]), FormatMoney(TrukCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 2) // Suv
            {
                if(SelectVeh[playerid] == sizeof(SuvShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleSuvSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(SuvShowroom[SelectVeh[playerid]]), FormatMoney(SuvCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 3) // Motor
            {
                if(SelectVeh[playerid] == sizeof(MotorShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleMotorSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(MotorShowroom[SelectVeh[playerid]]), FormatMoney(MotorCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 4) // Low ride
            {
                if(SelectVeh[playerid] == sizeof(ClassicShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleLowriderSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(ClassicShowroom[SelectVeh[playerid]]), FormatMoney(ClassicCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 5) // Compact
            {
                if(SelectVeh[playerid] == sizeof(CompactShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleCompactSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(CompactShowroom[SelectVeh[playerid]]), FormatMoney(CompactCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 6) // Luxury
            {
                if(SelectVeh[playerid] == sizeof(LuxuryShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleLuxurySelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(LuxuryShowroom[SelectVeh[playerid]]), FormatMoney(LuxuryCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
        }
    }
    else if(textid == ATRP_ShowroomTD[playerid][10]) // Previous veh
    {
        if(showroomID != 0)
        {
            if(showroomID == 1) // truk
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleTruckSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(TrukShowroom[SelectVeh[playerid]]), FormatMoney(TrukCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 2) // Suv
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleSuvSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(SuvShowroom[SelectVeh[playerid]]), FormatMoney(SuvCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 3) // Motor
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleMotorSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(MotorShowroom[SelectVeh[playerid]]), FormatMoney(MotorCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 4) // Lowrider
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleLowriderSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(ClassicShowroom[SelectVeh[playerid]]), FormatMoney(ClassicCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 5) // Compact
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleCompactSelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(CompactShowroom[SelectVeh[playerid]]), FormatMoney(CompactCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
            else if(showroomID == 6) // Luxury
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleLuxurySelect(playerid);

                PlayerTextDrawSetString(playerid, ATRP_ShowroomTD[playerid][14], sprintf("%s~n~~g~%s", GetVehicleModelName(LuxuryShowroom[SelectVeh[playerid]]), FormatMoney(LuxuryCost(playerid))));
                PlayerTextDrawShow(playerid, ATRP_ShowroomTD[playerid][14]);
            }
        }
    }
    else if(textid == ATRP_ShowroomTD[playerid][13]) // Keluar Showroom
    {
        EnableAntiCheatForPlayer(playerid, 4, true);
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;

        SetPlayerPositionEx(playerid, 1042.3744, 234.2350, 15.5392, 265.1649, 1500);
        SetPlayerVirtualWorld(playerid, DoorData[AccountData[playerid][pInDoor]][dIntvw]);
        SetCameraBehindPlayer(playerid);
        SetPVarInt(playerid, "SelectShowroomID", 0);
        SelectVeh[playerid] = 0;
        CancelSelectTextDraw(playerid);
        Toggle_ShowroomTD(playerid, false);
    }
    else if(textid == ATRP_ShowroomTD[playerid][12]) // Buy
    {
        if(showroomID != 0)
        {
            if(showroomID == 1) // Truk
            {
                new count = 0, modelid = TrukShowroom[SelectVeh[playerid]], cost = TrukCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, random(255), random(255), cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 2) // Suv
            {
                new count = 0, modelid = SuvShowroom[SelectVeh[playerid]], cost = SuvCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, random(255), random(255), cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 3) // Motor
            {
                new count = 0, modelid = MotorShowroom[SelectVeh[playerid]], cost = MotorCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, random(255), random(255), cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 4) // Low
            {
                new count = 0, modelid = ClassicShowroom[SelectVeh[playerid]], cost = ClassicCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, random(255), random(255), cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 5) // Compact
            {
                new count = 0, modelid = CompactShowroom[SelectVeh[playerid]], cost = CompactCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, random(255), random(255), cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 6) // Luxury
            {
                new count = 0, modelid = LuxuryShowroom[SelectVeh[playerid]], cost = LuxuryCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, random(255), random(255), cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
        }
    }
	//radio
	if(textid == ATRP_RadioTD[playerid][10]) //set freq
    {   
        ShowPlayerDialog(playerid, DIALOG_RADIO_FREQ, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Radio Fx",
        "Masukkan frekuensi radio yang ingin diterapkan pada kolom dibawah ini\
        \n(Frekuensi harus berada diantara 0 - 9999)\
        \nCatatan: Masukkan frekuensi 0 untuk memutuskan saluran frekuensi/netral", "Submit", "Batal");
    }
    else if(textid == ATRP_RadioTD[playerid][9]) // Close
    {
        SendRPMeAboveHead(playerid, "Menutup Radio miliknya.", X11_PLUM1);
        if(!IsPlayerInAnyVehicle(playerid))
        {
            ClearAnimations(playerid, 1);
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }
        RemovePlayerAttachedObject(playerid, 9);
        RadioTextdrawToggle(playerid, false);
        CancelSelectTextDraw(playerid);
    }
    else if(textid == ATRP_RadioTD[playerid][8]) // Power
    {
        RadioMicOn[playerid] = false;
        CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, false);
        switch(ToggleRadio[playerid])
        {
            case false:
            {
                ToggleRadio[playerid] = true;
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, true);
                if(!IsPlayerInAnyVehicle(playerid))
                {
                    ClearAnimations(playerid, 1);
                    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
                }
                RemovePlayerAttachedObject(playerid, 9);
                ShowTDN(playerid, NOTIFICATION_INFO, "Berhasil menyalakan radio");
                
                CancelSelectTextDraw(playerid);
                RadioTextdrawToggle(playerid, false);
            }
            case true:
            {
                ToggleRadio[playerid] = false;
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, false);
                if(!IsPlayerInAnyVehicle(playerid))
                {
                    ClearAnimations(playerid, 1);
                    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
                }
                RemovePlayerAttachedObject(playerid, 9);
                ShowTDN(playerid, NOTIFICATION_INFO, "Berhasil mematikan radio");
                
                CancelSelectTextDraw(playerid);
                RadioTextdrawToggle(playerid, false);
            }
        }
    }
	//toys
	if(textid == P_TOYS[playerid][1]) // X Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_x] -= 0.020;
	
		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][2]) // X Plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_x] += 0.020;
	
		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][4]) // Y Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_y] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][5]) // Y Plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_y] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][7]) // Z Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_z] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][8]) // Z Plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_z] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][10]) // Rot x Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rx] -= 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][11]) // Rot x Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rx] += 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][13]) // Rot y Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_ry] -= 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][14]) // Rot y Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_ry] += 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][16]) // rot z min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rz] -= 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][17]) // rot z plus 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rz] += 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][19]) // skale x min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sx] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][20]) // skale x plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sx] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][22]) // skale y min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sy] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][23]) // skale y plus 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sy] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][25]) // skale z min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sz] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][26]) // skale z plus 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sz] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][27]) // Keluar
	{
		HideTDToys(playerid);
		MySQL_SavePlayerToys(playerid);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyimpan Kordinat Baru");
	}
	//atm
	if(textid == VR_ATMTD[playerid][36])// Withdraw
	{
		ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Fleeca Bank", "Mohon masukan berapa jumlah uang yang anda ingin anda ambil:", "Submit", "Batal");
	}
	if(textid == VR_ATMTD[playerid][37])// Deposit
	{
		ShowPlayerDialog(playerid, DIALOG_ATM_DEPOSIT, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Fleeca Bank", "Mohon masukan berapa jumlah uang yang ingin anda masukkan:", "Submit", "Batal");
	}
	if(textid == VR_ATMTD[playerid][38])// Transfer
	{
		ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER, DIALOG_STYLE_INPUT, ""City"Happy Roleplay "WHITE"- Fleeca Bank", "Mohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");
	}
	if(textid == VR_ATMTD[playerid][43])// Log Out
	{
		HideATMTD(playerid);
	}
	/* Clothes Sistem */
	if(textid == P_MENUCLOTHES[playerid][6]) // Pakaian
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x + 0.2, y + 1.4, z + 0.8);
		SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.2);
		for(new pdip; pdip < 12; pdip++)
		{
			PlayerTextDrawHide(playerid, P_MENUCLOTHES[playerid][pdip]);
		}

		for(new txd; txd < 16; txd++)
		{
			PlayerTextDrawShow(playerid, P_CLOTHESSELECT[playerid][txd]);
		}
		BuyClothes[playerid] = 1;
		CSelect[playerid] = 0;

		SetPlayerSkin(playerid, (AccountData[playerid][pGender] == 1) ? ClothesSkinMale[CSelect[playerid]] : ClothesSkinFemale[CSelect[playerid]]);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", CSelect[playerid] + 1, ((AccountData[playerid][pGender] == 1) ? sizeof(ClothesSkinMale) : sizeof(ClothesSkinFemale)));
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);

		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][8], "PAKAIAN");
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == P_MENUCLOTHES[playerid][7]) // Topi Dan Helmet
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x + 0.2, y + 1.4, z + 1.0);
		SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.5);

		for(new txid; txid < 12; txid++)
		{
			PlayerTextDrawHide(playerid, P_MENUCLOTHES[playerid][txid]);
		}
		
		for(new txd; txd < 16; txd++)
		{
			PlayerTextDrawShow(playerid, P_CLOTHESSELECT[playerid][txd]);
		}
		BuyTopi[playerid] = 1;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 0);
		SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.356, 0.005, -0.004, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);

		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][8], "TOPI/HELM");
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == P_MENUCLOTHES[playerid][8]) // Kacamata Toys
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x + 0.2, y + 1.4, z + 1.0);
		SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.5);

		for(new txid; txid < 12; txid++)
		{
			PlayerTextDrawHide(playerid, P_MENUCLOTHES[playerid][txid]);
		}
		
		for(new txd; txd < 16; txd++)
		{
			PlayerTextDrawShow(playerid, P_CLOTHESSELECT[playerid][txd]);
		}
		BuyGlasses[playerid] = 1;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 1);
		SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);

		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][8], "KACAMATA");
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, COLOR_GREY);
	}
	if(textid == P_MENUCLOTHES[playerid][9]) // Aksesoris
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x + 0.2, y + 1.6, z + 0.5);
		SetPlayerCameraLookAt(playerid, x, y - 1.0, z);
		
		for(new pdip; pdip < 12; pdip++)
		{
			PlayerTextDrawHide(playerid, P_MENUCLOTHES[playerid][pdip]);
		}

		for(new txd; txd < 16; txd++)
		{
			PlayerTextDrawShow(playerid, P_CLOTHESSELECT[playerid][txd]);
		}
		BuyTAksesoris[playerid] = 1;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 2);
		SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][8], "AKSESORIS");
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == P_MENUCLOTHES[playerid][10]) // Tas / Backpack
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x + 0.2, y + 1.6, z + 0.5);
		SetPlayerCameraLookAt(playerid, x, y - 1.0, z);

		for(new pdip; pdip < 12; pdip++)
		{
			PlayerTextDrawHide(playerid, P_MENUCLOTHES[playerid][pdip]);
		}

		for(new txd; txd < 16; txd++)
		{
			PlayerTextDrawShow(playerid, P_CLOTHESSELECT[playerid][txd]);
		}
		BuyBackpack[playerid] = 1;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 3);
		SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);

		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][8], "TAS/KOPER");
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == P_MENUCLOTHES[playerid][11]) // Batal
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan");
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, 1);
		for(new txd; txd < 12; txd ++)
		{
			PlayerTextDrawHide(playerid, P_MENUCLOTHES[playerid][txd]);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		CancelSelectTextDraw(playerid);
	}
	if(textid == P_CLOTHESSELECT[playerid][14]) // Kembali
	{
		if(BuyClothes[playerid] == 1)
		{
			for(new txd; txd < 16; txd ++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			SetPlayerCameraFacingStore(playerid);
			BuyClothes[playerid] = 0;
			CSelect[playerid] = 0;
			if(AccountData[playerid][pUsingUniform])
			{
				SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
			}
			else 
			{
				SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			}
		}

		if(BuyTopi[playerid] == 1)
		{
			for(new txd; txd < 16; txd ++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			SetPlayerCameraFacingStore(playerid);
			BuyTopi[playerid] = 0;
			SelectAcc[playerid] = 0;
			AttachPlayerToys(playerid);
			RemovePlayerAttachedObject(playerid, 9);
		}

		if(BuyGlasses[playerid] == 1)
		{
			for(new txd; txd < 16; txd ++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			SetPlayerCameraFacingStore(playerid);
			BuyGlasses[playerid] = 0;
			SelectAcc[playerid] = 0;
			AttachPlayerToys(playerid);
			RemovePlayerAttachedObject(playerid, 9);
		}

		if(BuyTAksesoris[playerid] == 1)
		{
			for(new txd; txd < 16; txd ++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			SetPlayerCameraFacingStore(playerid);
			BuyTAksesoris[playerid] = 0;
			SelectAcc[playerid] = 0;
			AttachPlayerToys(playerid);
			RemovePlayerAttachedObject(playerid, 9);
		}

		if(BuyBackpack[playerid] == 1)
		{
			for(new txd; txd < 16; txd ++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			SetPlayerCameraFacingStore(playerid);
			BuyBackpack[playerid] = 0;
			SelectAcc[playerid] = 0;
			AttachPlayerToys(playerid);
			RemovePlayerAttachedObject(playerid, 9);
		}
	}
	if(textid == P_CLOTHESSELECT[playerid][12]) // Next Cloth
	{
		if(BuyClothes[playerid] == 1)
		{
			if(CSelect[playerid] == ((AccountData[playerid][pGender] == 1) ? sizeof(ClothesSkinMale) - 1 : sizeof(ClothesSkinFemale) - 1))
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else CSelect[playerid] ++;
			SetPlayerSkin(playerid, (AccountData[playerid][pGender] == 1) ? ClothesSkinMale[CSelect[playerid]] : ClothesSkinFemale[CSelect[playerid]]);
		
			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", CSelect[playerid] + 1, ((AccountData[playerid][pGender] == 1) ? sizeof(ClothesSkinMale) : sizeof(ClothesSkinFemale)));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyTopi[playerid] == 1)
		{
			if(SelectAcc[playerid] == sizeof(AksesorisHat) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.269, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
			
			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyGlasses[playerid] == 1)
		{
			if(SelectAcc[playerid] == sizeof(GlassesToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyTAksesoris[playerid] == 1)
		{
			if(SelectAcc[playerid] == sizeof(AksesorisToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyBackpack[playerid] == 1)
		{
			if(SelectAcc[playerid] == sizeof(BackpackToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if(textid == P_CLOTHESSELECT[playerid][11]) // Prev Cloth
	{
		if(BuyClothes[playerid] == 1)
		{
			if(CSelect[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else CSelect[playerid] --;
			SetPlayerSkin(playerid, (AccountData[playerid][pGender] == 1) ? ClothesSkinMale[CSelect[playerid]] : ClothesSkinFemale[CSelect[playerid]]);

			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", CSelect[playerid] + 1, ((AccountData[playerid][pGender] == 1) ? sizeof(ClothesSkinMale) : sizeof(ClothesSkinFemale)));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyTopi[playerid] == 1)
		{
			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.269, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
			
			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyGlasses[playerid] == 1)
		{
			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyTAksesoris[playerid] == 1)
		{
			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}

		if(BuyBackpack[playerid] == 1)
		{
			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128];
			format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if(textid == P_CLOTHESSELECT[playerid][9]) // Rot Kiri
	{
		static Float:x, Float:y, Float:z, Float:angle;
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);

		SetPlayerPos(playerid, x, y, z);
		SetPlayerFacingAngle(playerid, angle - 15.0);
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if(textid == P_CLOTHESSELECT[playerid][10]) // Rot Kanana
	{
		static Float:x, Float:y, Float:z, Float:angle;
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);

		SetPlayerPos(playerid, x, y, z);
		SetPlayerFacingAngle(playerid, angle + 15.0);
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if(textid == P_CLOTHESSELECT[playerid][13]) // Beli Clothes
	{
		if(BuyClothes[playerid] == 1)
		{
			new price = 200;

			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup! (Price: $200)");
			TakeMoney(playerid, price);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli baju seharga ~g~$200");
			
			AccountData[playerid][pSkin] = GetPlayerSkin(playerid);
			for(new tx; tx < 16; tx++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][tx]);
			}
			BuyClothes[playerid] = 0;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			CancelSelectTextDraw(playerid);
			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
		}

		if(BuyTopi[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 0;

			new price = 80;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: $80)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = AksesorisHat[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
			ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""City"Happy Roleplay"WHITE"- Ubah Tulang(Bone)", 
			"Spine\
			\n"GRAY"Head\
			\nLeft Upper Arm\
			\n"GRAY"Right Upper Arm\
			\nLeft Hand\
			\n"GRAY"Right Hand\
			\nLeft Thigh\
			\n"GRAY"Right Thigh\
			\nLeft Foot\
			\n"GRAY"Right Foot\
			\nRight Calf\
			\n"GRAY"Left Calf\
			\nLeft Forearm\
			\n"GRAY"Right Forearm\
			\nLeft Clavicle\
			\n"GRAY"Right Clavicle\
			\nNeck\
			\n"GRAY"Jaw", "Select", "Cancel");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Topi seharga ~g~$80");
			for(new txd; txd < 16; txd++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			BuyTopi[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}

		if(BuyGlasses[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 1;

			new price = 50;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: $50)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = GlassesToys[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
			ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""City"Happy Roleplay"WHITE"- Ubah Tulang(Bone)", 
			"Spine\
			\n"GRAY"Head\
			\nLeft Upper Arm\
			\n"GRAY"Right Upper Arm\
			\nLeft Hand\
			\n"GRAY"Right Hand\
			\nLeft Thigh\
			\n"GRAY"Right Thigh\
			\nLeft Foot\
			\n"GRAY"Right Foot\
			\nRight Calf\
			\n"GRAY"Left Calf\
			\nLeft Forearm\
			\n"GRAY"Right Forearm\
			\nLeft Clavicle\
			\n"GRAY"Right Clavicle\
			\nNeck\
			\n"GRAY"Jaw", "Select", "Cancel");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Kacamata seharga ~g~$50");
			for(new txd; txd < 16; txd++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			BuyGlasses[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}

		if(BuyTAksesoris[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 2;

			new price = 100;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: $100)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = AksesorisToys[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
			ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""City"Happy Roleplay"WHITE"- Ubah Tulang(Bone)", 
			"Spine\
			\n"GRAY"Head\
			\nLeft Upper Arm\
			\n"GRAY"Right Upper Arm\
			\nLeft Hand\
			\n"GRAY"Right Hand\
			\nLeft Thigh\
			\n"GRAY"Right Thigh\
			\nLeft Foot\
			\n"GRAY"Right Foot\
			\nRight Calf\
			\n"GRAY"Left Calf\
			\nLeft Forearm\
			\n"GRAY"Right Forearm\
			\nLeft Clavicle\
			\n"GRAY"Right Clavicle\
			\nNeck\
			\n"GRAY"Jaw", "Select", "Cancel");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Aksesoris seharga ~g~$100");
			for(new txd; txd < 16; txd++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			BuyTAksesoris[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}

		if(BuyBackpack[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 3;

			new price = 100;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: 100)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = BackpackToys[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Tas seharga ~g~$100");
			for(new txd; txd < 16; txd++)
			{
				PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			}
			BuyBackpack[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	// Inventory
	for(new x; x < MAX_INVENTORY; x ++)
	{
		if(textid == inv::box[playerid][x])
		{
			new Old = AccountData[playerid][pSelectItem];
			if(InventoryData[playerid][x][invExists])
			{
				UnselectItem(playerid);
				SelectItem(playerid, x);
			}
			else 
			{
				PlayerPlaySound(playerid, 1052, 0, 0, 0);
				if(Old != -1)
				{ 
					if(InventoryData[playerid][x][invExists])
						return 0;

					MoveItemToNewSlot(playerid, Old, x);
					UnselectItem(playerid);
					Old = -1;
				}
			}
		}
	}
	return 1;
}

RemovePlayerWeapon(playerid, weaponid)
{
	// Reset the player's weapons.
	ResetPlayerWeapons(playerid);
	// Set the armed slot to zero.
	SetPlayerArmedWeapon(playerid, 0);
	// Set the weapon in the slot to zero.
	AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] = 0;
	AccountData[playerid][pACTime] = gettime() + 2;
	// Set the player's weapons.
	SetWeapons(playerid);
	return 1;
}

SetCameraData(playerid)
{
	switch(random(2))
	{
		case 0: //customer parking ganton
		{
			SetPlayerCameraPos(playerid, 902.991, -901.185, 94.368);
			SetPlayerCameraLookAt(playerid, 898.424, -899.630, 93.054);
			InterpolateCameraPos(playerid, 902.991, -901.185, 94.368, 852.659, -880.944, 88.302, 30000, CAMERA_MOVE);
		}
		case 1: // vinewood
		{
			SetPlayerCameraPos(playerid, 485.642, -2111.710, 68.742);
			SetPlayerCameraLookAt(playerid, 483.018, -2107.744, 67.201);
			InterpolateCameraPos(playerid, 485.642, -2111.710, 68.742, 470.870, -2081.438, 61.609, 25000, CAMERA_MOVE);
		}
	}
	return 1;
}
