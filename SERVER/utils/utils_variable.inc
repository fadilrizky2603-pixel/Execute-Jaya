new g_ServerLocked;
new g_AsuransiAll; 
new g_AsuransiTime; 
new g_RestartServer; 
new g_RestartTime;
new g_RusunTime;
new g_RobberyTime = 0;
new g_Schedule;
new g_ScheduleTime;
new g_Message;
new g_MessageTimer;

new CooldownRobWarung;

//Anti Weapon Hack
new const g_aWeaponSlots[] = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 10, 10, 8, 8, 8, 0, 0, 0, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 4, 6, 6, 7, 7, 7, 7, 8, 12, 9, 9, 9, 11, 11, 11
};

/* Voting System */
new OpenVote = 0,
    VoteYes = 0,
    VoteNo = 0,
    VoteTime = 0,
    VoteText[128];

new bool: TogOOC;

new PlayerChar[MAX_PLAYERS][MAX_CHARS][MAX_PLAYER_NAME + 1];
new HouseMemberName[MAX_PLAYERS][3][MAX_PLAYER_NAME + 1];

new g_RaceCheck[MAX_PLAYERS];

new CSelect[MAX_PLAYERS];
new SelectAcc[MAX_PLAYERS];
new BuyClothes[MAX_PLAYERS];
new BuyTopi[MAX_PLAYERS];
new BuyGlasses[MAX_PLAYERS];
new BuyTAksesoris[MAX_PLAYERS];
new BuyBackpack[MAX_PLAYERS];
	
new NearestVehicleID[MAX_PLAYERS];
new ShowroomVeh[MAX_PLAYERS];

new TogIsiBensin[MAX_PLAYERS];
new STREAMER_TAG_AREA:PantaiArea[MAX_PLAYERS];
new STREAMER_TAG_3D_TEXT_LABEL: labelDisconnect[MAX_PLAYERS];
new labelDisconnectTimer[MAX_PLAYERS] = {-1, ...};
new NearestSingle[MAX_PLAYERS];
new ListBosDesk[MAX_PLAYERS][50];
new NearestPlayer[MAX_PLAYERS][MAX_PLAYERS];
new bool: pPassengerClickMap[MAX_PLAYERS];
new bool: pMapCP[MAX_PLAYERS];
new SharelocSender[MAX_PLAYERS];
new SharelocTimer[MAX_PLAYERS] = {0, ...};
new PlayerPressedJump[MAX_PLAYERS];
new bool: VehicleJobLocked[MAX_PLAYERS];
new Smoking[MAX_PLAYERS];
new IsDragging[MAX_PLAYERS];

new Shakehand[MAX_PLAYERS] = {false, ...};
new ShakehandBy[MAX_PLAYERS] = {INVALID_PLAYER_ID, ...};

// new bool:g_ucpActived[MAX_PLAYERS];

new color_string[3256], object_font[200];

new FixmeOption[MAX_PLAYERS];
new ListFixme[MAX_PLAYERS][MAX_PLAYERS];
new bool: FixmeExists[MAX_PLAYERS],
    FixmeTime[MAX_PLAYERS];

/* Forklift Stuffs */
new ForkliftVehicles[2];

/* Sweeper Stuffs */
new SweeperVehicles[3];
new SweeperIndex[MAX_PLAYERS];
new bool:DurringSweeping[MAX_PLAYERS];

/* Delivery Stuffs */
new DeliveryVehicles[2];
new TrashmasterVehicles[3];

/* Mowing Stuffs */
new MowerVehicles[3];

/* Quiz Stuffs */
new bool: Quiz;
new bool: QuizAnswerMade;
new QuizAnswer[255];
new QuizPrice;

/* Tunjangan */
new bool:PlayerTaserOn[MAX_PLAYERS] = {false, ...};

new bool: SignalExists[MAX_PLAYERS] = { false, ... },
    Float:SignalPos[MAX_PLAYERS][3],
    SignalTimer[MAX_PLAYERS],
    ListSignal[MAX_PLAYERS][MAX_PLAYERS];

new ClickPlayerID[MAX_PLAYERS];

new PlayerTextdraws[MAX_PLAYERS][playerTextdraws];

// mprice changed price
new TembagaPrice = 3;
new BesiPrice = 2;
new EmasPrice = 4;
new BerlianPrice = 100;
new MaterialPrice = 5;
new AlumuniumPrice = 13;
new KaretPrice = 5;
new KacaPrice = 10;
new BajaPrice = 12;
new AyamKemasPrice = 13;
new SusuOlahPrice = 13;
new PakaianPrice = 25;
new KayuKemasPrice = 21;
new GasPrice = 5;

new OldTembagaPrice;
new OldBesiPrice;
new OldEmasPrice;
new OldBerlianPrice;
new OldMaterialPrice;
new OldAlumuniumPrice;
new OldKaretPrice;
new OldKacaPrice;
new OldBajaPrice;
new OldAyamKemasPrice;
new OldSusuOlahPrice;
new OldPakaianPrice;
new OldKayuKemasPrice;
new OldGasPrice;

new bool: IsPlayerSmoking[MAX_PLAYERS] = { false, ... };
new CountSmoking[MAX_PLAYERS] = { 0, ... };
new SmokingDelayTime[MAX_PLAYERS] = { 0, ... };

new STREAMER_TAG_OBJECT: FireworkObject[MAX_PLAYERS];
new FireworkTimer[MAX_PLAYERS] = {-1, ...};

// Live mode
new bool: LivemodeOn[MAX_PLAYERS] = { false, ... };
new LivemodeTittle[MAX_PLAYERS][255];
new LoginTimer[MAX_PLAYERS];
new LoginAttemps[MAX_PLAYERS];

new WarningTimer[MAX_PLAYERS],
    bool: ShowWarning[MAX_PLAYERS];

new bool:IsPlayerChangeSeat[MAX_PLAYERS] = { false, ... },
    ChangeSeatWithPlayerID[MAX_PLAYERS] = { INVALID_PLAYER_ID, ... },
    ChangeSeatVehicleID[MAX_PLAYERS] = { -1, ... };

new bool: PlayerVoting[MAX_PLAYERS] = { false, ... };

new ListedVehObject[MAX_PLAYERS][MAX_VEHICLE_OBJECT], // Untuk menyimpan index id array vehicle object ke playerid
    Player_EditingObject[MAX_PLAYERS], // Sebagai flagger untuk menandakan player sedang edit object atau tidak 
    Player_EditVehicleObject[MAX_PLAYERS], // Variable Holder
    Player_EditVehicleObjectSlot[MAX_PLAYERS] // Variable Holder
;

// new CircleHunger[MAX_PLAYERS],
//     CircleThirst[MAX_PLAYERS],
//     CircleStress[MAX_PLAYERS]
// ;