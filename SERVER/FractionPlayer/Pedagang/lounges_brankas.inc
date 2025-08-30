#include <YSI_Coding\y_hooks>

new Sambal,
    Beras,
    Gula,
    Garam,
    Ikan,
    AyamFillet,
    SusuOlahan,
    AirMineral,
    NasiGoreng,
    Bakso,
    NasiPecel,
    BuburPedas,
    SusuFresh,
    EsTeh,
    KopiKenangan,
    CochoMatcha;

BrankasLounge_Save()
{
    new str[2024];
    
    format(str, sizeof str, "UPDATE brankas_lounges SET sambal='%d', beras='%d', gula='%d', garam='%d', ikan='%d', ayamfillet='%d', susuolahan='%d', airmineral='%d', nasigoreng='%d', bakso='%d', nasipecel='%d', buburpedas='%d', susufresh='%d', esteh='%d', kopikenangan='%d', cochomatcha='%d' WHERE id=0", 
    Sambal, Beras, Gula, Garam, Ikan, AyamFillet, SusuOlahan, AirMineral, NasiGoreng, Bakso, NasiPecel, BuburPedas, SusuFresh, EsTeh, KopiKenangan, CochoMatcha);
    return mysql_tquery(g_SQL, str);
}

function LoadBrankasLounges()
{
    cache_get_value_name_int(0, "sambal", Sambal);
    cache_get_value_name_int(0, "beras", Beras);
    cache_get_value_name_int(0, "gula", Gula);
    cache_get_value_name_int(0, "garam", Garam);
    cache_get_value_name_int(0, "ikan", Ikan);
    cache_get_value_name_int(0, "ayamfillet", AyamFillet);
    cache_get_value_name_int(0, "susuolahan", SusuOlahan);
    cache_get_value_name_int(0, "airmineral", AirMineral);
    cache_get_value_name_int(0, "nasigoreng", NasiGoreng);
    cache_get_value_name_int(0, "bakso", Bakso);
    cache_get_value_name_int(0, "nasipecel", NasiPecel);
    cache_get_value_name_int(0, "buburpedas", BuburPedas);
    cache_get_value_name_int(0, "susufresh", SusuFresh);
    cache_get_value_name_int(0, "esteh", EsTeh);
    cache_get_value_name_int(0, "kopikenangan", KopiKenangan);
    cache_get_value_name_int(0, "cochomatcha", CochoMatcha);
    Profiler_Dump();
	printf("[Brankas] Loaded Data Lounges...");
}

CMD:setblounge(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new jumlah;
    if(sscanf(params, "d", jumlah))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setblounge [jumlah]");
    
    Sambal = jumlah;
    Beras = jumlah;
    Gula = jumlah;
    Garam = jumlah;
    Ikan = jumlah;
    AyamFillet = jumlah;
    SusuOlahan = jumlah;
    AirMineral = jumlah;
    NasiGoreng = jumlah;
    Bakso = jumlah;
    NasiPecel = jumlah;
    BuburPedas = jumlah;
    SusuFresh = jumlah;
    EsTeh = jumlah;
    KopiKenangan = jumlah;
    CochoMatcha = jumlah;
    BrankasLounge_Save();
    return 1;
}