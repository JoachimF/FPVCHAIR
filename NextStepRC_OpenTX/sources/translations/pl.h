/*
**************************************************************************
*                                                                        *
*              This file is part of the NextStepRC project.              *
*                                                                        *
*                         Based on code named                            *
*             OpenTx - https://github.com/opentx/opentx                  *
*                                                                        *
*              ATmega AVR family (M64, M128, M2560, M2561)               *
*                                                                        *
*   NextStepRC is free software: you can redistribute it and/or modify   *
*   it under the terms of the GNU General Public License as published by *
*   the Free Software Foundation, either version 2 of the License, or    *
*   (at your option) any later version.                                  *
*                                                                        *
*   NextStepRC is distributed in the hope that it will be useful,        *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
*   GNU General Public License for more details.                         *
*                                                                        *
*       License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html          *
*                                                                        *
**************************************************************************
*/



/* Formatting octal codes available in TR_ strings:
 *  \037\x           -sets LCD x-coord (x value in octal)
 *  \036             -newline
 *  \035             -horizontal tab (ARM only)
 *  \001 to \034     -extended spacing (value * FW/2)
 *  \0               -ends current string
 */

// NON ZERO TERMINATED STRINGS
#define LEN_OFFON              "\003"
#define TR_OFFON               "WY\214""ZA\214"

#define LEN_MMMINV             "\003"
#define TR_MMMINV              "---""REV"

#define LEN_NCHANNELS          "\004"
#define TR_NCHANNELS           "\0014KN\0016KN\0018KN10KN12KN14KN16KN"

#define LEN_VBEEPMODE          "\005"
#define TR_VBEEPMODE           "Cichy""Alarm""BezPr""Wsz.\0"

#define LEN_VBEEPLEN           "\005"
#define TR_VBEEPLEN            "0====""=0===""==0==""===0=""====0"

#define LEN_VRENAVIG           "\003"
#define TR_VRENAVIG            "No REaREb"

#define LEN_VBLMODE            TR("\004", "\010")
#define TR_VBLMODE             TR("Wy\203\0""Przy""Dr\200\207""Oba\0""Za\203\0", "Wy\203\200cz  ""Przycisk""Dr\200zki\0 ""Oba\0    ""W\203\200cz   ")

#define LEN_TRNMODE            "\003"
#define TR_TRNMODE             "Wy\203"" +="" :="

#define LEN_TRNCHN             "\003"
#define TR_TRNCHN              "KN1KN2KN3KN4"


#define LEN_UART3MODES         "\015"  /*13 decimal*/
#define TR_UART3MODES          "Wy\203\200cz\0      ""S-Port Kopia ""Telemetria\0  ""Trener SBUS\0 ""Debug\0        "

#define LEN_SWTYPES            "\006"
#define TR_SWTYPES             "Brak\0 ""Chwil.""2POZ\0 ""3POZ\0"

#define LEN_POTTYPES           "\017" /*15 decimal*/
#define TR_POTTYPES            "Brak\0          ""Poten z zapadk\200""Prze\203.Wielopoz.""Potencjometr\0  "

#define LEN_SLIDERTYPES        "\006"
#define TR_SLIDERTYPES         "Brak\0 ""Suwak "

#define LEN_DATETIME           "\005"
#define TR_DATETIME            "DATA:""CZAS:"

#define LEN_VLCD               "\006"
#define TR_VLCD                "NormalOptrex"

#define LEN_VPERSISTENT        "\014"  /*12 decimal*/
#define TR_VPERSISTENT         "Wy\203\200cz\0     ""Lot\0        ""R\202czny Reset"

#define LEN_COUNTRYCODES       TR("\002", "\007")
#define TR_COUNTRYCODES        TR("US""JP""EU", "Ameryka""Japonia""Europa\0")

#define LEN_TARANIS_PROTOCOLS  "\004"
#define TR_TARANIS_PROTOCOLS   "OFF\0""PPM\0""XJT\0""DSM2""CRSF"

#define LEN_XJT_PROTOCOLS      "\004"
#define TR_XJT_PROTOCOLS       "OFF\0""D16\0""D8\0 ""LR12"

#define LEN_DSM_PROTOCOLS      "\004"
#define TR_DSM_PROTOCOLS       "LP45""DSM2""DSMX"

#define LEN_VTRIMINC           TR("\006", "\013") /*11 decimal*/
#define TR_VTRIMINC            TR("Expo\0 ""B.Dok\203""Dok\203.\0""\217redni""Zgrubn", "Expotencja ""B.Dok\203adny\0""Dok\203adny\0  ""\217redni\0    ""Zgrubny\0   ")


#define LEN_VDISPLAYTRIMS      "\006"
#define TR_VDISPLAYTRIMS       "Nie\0  ""Zmie\204\0""Tak\0"

#define LEN_VBEEPCOUNTDOWN     "\006"
#define TR_VBEEPCOUNTDOWN      "Cichy Pik  \0D\210wi\202kWibrac"

#define LEN_VVARIOCENTER       "\006"
#define TR_VVARIOCENTER        "Ton\0  ""Cicho "

#define LEN_CURVE_TYPES        "\010" /*8 decimal*/
#define TR_CURVE_TYPES         "Standard""W\203asny\0 "

#define LEN_RETA123            "\001"

#if defined(CPUM2560)
#define TR_RETA123         "KWGL123ab"
#else
#define TR_RETA123           "KWGL123"
#endif

#define LEN_VPROTOS            "\006"

#if defined(PXX)
#define TR_PXX              "PXX\0  "
#elif defined(DSM2) || defined(IRPROTOS)
#define TR_PXX             "[PXX]\0"
#else
#define TR_PXX
#endif

#if defined(DSM2)
#define TR_DSM2              "LP45\0 ""DSM2\0 ""DSMX\0 "
#elif defined(IRPROTOS)
#define TR_DSM2              "[LP45]""[DSM2]""[DSMX]"
#else
#define TR_DSM2
#endif

#if defined(IRPROTOS)
#define TR_IRPROTOS          "SILV  TRAC09PICZ  SWIFT\0"
#else
#define TR_IRPROTOS
#endif

#define TR_XPPM              "PPM16\0""PPMsim"

#define TR_VPROTOS             "PPM\0  " TR_XPPM TR_PXX TR_DSM2 TR_IRPROTOS

#define LEN_POSNEG             "\003"
#define TR_POSNEG              "POZ""NEG"


#define LEN_VCURVEFUNC         "\003"
#define TR_VCURVEFUNC          "---""x>0""x<0""|x|""f>0""f<0""|f|"

#define LEN_VMLTPX             "\010" /*8 decimal*/
#define TR_VMLTPX              "Dodaj\0  ""Mn\205\207    ""Zast\200p\0 "

#define LEN_VMLTPX2            "\002"
#define TR_VMLTPX2             "+=""*="":="

#define LEN_VMIXTRIMS          "\003"
#define TR_VMIXTRIMS           "WY\214""ZA\214""SK\0""SW\0""GAZ""Lot"

#define TR_CSWTIMER          "Tim\0 "
#define TR_CSWSTICKY         "Sta\203y"
#define TR_CSWRANGE
#define TR_CSWSTAY

#define TR_CSWEQUAL

#define LEN_VCSWFUNC           "\005"
#define TR_VCSWFUNC            "---\0 " TR_CSWEQUAL "a\173x\0 ""a>x\0 ""a<x\0 " TR_CSWRANGE "|a|>x""|a|<x""AND\0 ""OR\0  ""XOR\0 " TR_CSWSTAY "a=b\0 ""a>b\0 ""a<b\0 ""^}x\0 ""|^|}x" TR_CSWTIMER TR_CSWSTICKY

#define LEN_VFSWFUNC           "\012" /*10 decimal*/

#if defined(VARIO)
#define TR_VVARIO            "Wario\0    "
#else
#define TR_VVARIO            "[Wario]\0  "
#endif

#if defined(AUDIO)
#define TR_SOUND             "GrajD\210wi\202k"
#else
#define TR_SOUND             "Pikanie\0  "
#endif

#if defined(HAPTIC)
#define TR_HAPTIC            "Wibracje\0 "
#else
#define TR_HAPTIC            "[Wibracje]"
#endif

#if defined(VOICE)
#define TR_PLAY_TRACK      "Graj\217cie\207k"
#define TR_PLAY_BOTH         "Graj Oba\0 "
#define TR_PLAY_VALUE        TR("Graj Wart\0","GrajWarto\206")
#else
#define TR_PLAY_TRACK        "[Graj \217ci]"
#define TR_PLAY_BOTH         "[Graj Oba]"
#define TR_PLAY_VALUE        "[Graj War]"
#endif

#define TR_SF_BG_MUSIC        "Muz. t\203a\0 ""Muz.t\203a ||"

#if defined(SDCARD)
#define TR_SDCLOGS           "Logi->SD\0 "
#else
#define TR_SDCLOGS           "[Logowa\201]\0"
#endif

#if defined(GVARS)
#define TR_ADJUST_GVAR       "Ustaw \0   "
#else
#define TR_ADJUST_GVAR       "[UstawZG] "
#endif

#define TR_SF_PLAY_SCRIPT   "[Lua]\0    "

#if defined(DEBUG)
#define TR_SF_TEST          "Test\0"
#else
#define TR_SF_TEST
#endif

#if   defined(OVERRIDE_CHANNEL_FUNCTION)
#define TR_SF_SAFETY        "Bezp.\0    "
#else
#define TR_SF_SAFETY        "---\0      "
#endif

#define TR_SF_SCREENSHOT

#define TR_SF_RESERVE         "[rezerwa]\0"

#if defined(PCBGRUVIN9X) || defined(PCBMEGA2560)
#define TR_VFSWFUNC          TR_SF_SAFETY "Trener \0  ""Inst-Trim ""Resetuj\0  " TR_ADJUST_GVAR TR_SOUND TR_PLAY_TRACK TR_PLAY_BOTH TR_PLAY_VALUE TR_VVARIO TR_HAPTIC TR_SDCLOGS "Pod\206wietl\0" TR_SF_TEST
#else
#define TR_VFSWFUNC          TR_SF_SAFETY "Trener \0  ""Inst-Trim ""Resetuj\0  " TR_ADJUST_GVAR TR_SOUND TR_PLAY_TRACK TR_PLAY_BOTH TR_PLAY_VALUE TR_VVARIO TR_HAPTIC "Pod\206wietl\0" TR_SF_TEST
#endif

#define LEN_VFSWRESET          TR("\004", "\011")  /*9 decimal*/

#if defined(FRSKY)
#define TR_FSW_RESET_TELEM   TR("Telm", "Telemetra")
#else
#define TR_FSW_RESET_TELEM
#endif

#if ROTARY_ENCODERS == 2
#define TR_FSW_RESET_ROTENC  TR("REa\0""REb\0", "RotEnc A\0""RotEnc B\0")
#elif ROTARY_ENCODERS == 1
#define TR_FSW_RESET_ROTENC  TR("R.E.", "RotEnc\0  ")
#else
#define TR_FSW_RESET_ROTENC
#endif

#define TR_FSW_RESET_TIMERS  "Tmr1""Tmr2"

#define TR_VFSWRESET           TR(TR_FSW_RESET_TIMERS "All\0" TR_FSW_RESET_TELEM TR_FSW_RESET_ROTENC, TR_FSW_RESET_TIMERS "All\0     " TR_FSW_RESET_TELEM TR_FSW_RESET_ROTENC)

#define LEN_FUNCSOUNDS         TR("\004", "\006")
#define TR_FUNCSOUNDS          TR("Bp1\0""Bp2\0""Bp3\0""Ost1""Ost2""Chee""Rata""Tik ""Syre""Dzwo""SciF""Robt""Chrp""Tada""Crck""Alrm", "Beep1 ""Beep2 ""Beep3 ""Ostrz1""Ostrz1""Cheep ""Ratata""Tick  ""Syrena""Dzwone""SciFi ""Robot ""Chirp ""Tada  ""Krytcz""AlmZeg")

#define LEN_VTELEMCHNS         TR("\004", "\005")

#define TR_TELEM_RESERVE
#define TR_TELEM_TIME
#define TR_SWR
#define TR_RX_BATT
#define TR_A3_A4
#define TR_A3_A4_MIN

#define TR_ASPD_MAX            TR("ASp+", "ASpd+")

#define TR_TELEM_RSSI_RX     TR("Rx\0  ", "Rx\0 ")

#define TR_TELEM_TIMERS      TR("Tmr1""Tmr2", "Tmr1\0""Tmr2\0")

#define TR_VTELEMCHNS        "---\0""Bat\0" TR_TELEM_TIME TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_TIMERS TR_SWR "Tx\0 " TR_TELEM_RSSI_RX TR_RX_BATT "A1\0 ""A2\0 " TR_A3_A4 "Alt\0""Rpm\0""Fuel""T1\0 ""T2\0 ""Spd\0""Dist""GAlt""Cell""Cels""Vfas""Curr""Cnsp""Powr""AccX""AccY""AccZ""Hdg\0""VSpd""ASpd""dTE\0" TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE "A1-\0""A2-\0" TR_A3_A4_MIN "Alt-""Alt+""Rpm+""T1+\0""T2+\0""Spd+""Dst+" TR_ASPD_MAX "Cel-""Cls-""Vfs-""Cur+""Pwr+" TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE TR_TELEM_RESERVE "Acc\0""Time"

#define LENGTH_UNIT_IMP        "ft\0"
#define SPEED_UNIT_IMP         "mph"
#define LENGTH_UNIT_METR       "m\0 "
#define SPEED_UNIT_METR        "kmh"

#if defined(IMPERIAL_UNITS)
#define LENGTH_UNIT        LENGTH_UNIT_IMP
#define SPEED_UNIT         SPEED_UNIT_IMP
#else
#define LENGTH_UNIT        LENGTH_UNIT_METR
#define SPEED_UNIT         SPEED_UNIT_METR
#endif
#define LEN_VTELEMUNIT       "\003"
#define TR_VTELEMUNIT        "V\0 ""A\0 ""m/s""-\0 " SPEED_UNIT LENGTH_UNIT "@\0 ""%\0 ""mA\0""mAh""W\0 "

#define STR_V                  (STR_VTELEMUNIT+1)
#define STR_A                  (STR_VTELEMUNIT+4)

#define LEN_VALARM             "\003"
#define TR_VALARM              "---""\220\205\203""Pom""Cze"

#define LEN_VALARMFN           "\001"
#define TR_VALARMFN            "<>"

#define LEN_VTELPROTO          "\007"
#define TR_VTELPROTO           "None\0  ""Hub\0   ""WSHHigh"

#define LEN_AMPSRC           TR("\003", "\005")
#define TR_AMPSRC            TR("---""A1\0""A2\0""FAS""Cel", "---\0 ""A1\0  ""A2\0  ""FAS\0 ""Cells")

#define LEN_VARIOSRC           "\004"
#if defined(FRSKY_SPORT)
#define TR_VARIOSRC          "VSpd""A1\0 ""A2\0 ""dTE\0"
#else
#define TR_VARIOSRC          "Wys\0""Wys+""VSpd""A1\0 ""A2\0"
#endif

#define LEN_VTELEMSCREENTYPE "\004"
#define TR_VTELEMSCREENTYPE    "Licz""Pask"

#define LEN_GPSFORMAT          "\004"
#define TR_GPSFORMAT           "DMS\0""NMEA"

#define LEN2_VTEMPLATES        13
#define LEN_VTEMPLATES         "\015" /*13 decimal*/
#define TR_VTEMPLATES          "Usu\204 Miksy ""Prosty. 4kn\0 ""Prze\203\200-T-Cut\0""V-Tail      \0""Elevon-Delta\0""eCCPM       \0""Ustaw Heli  \0""Test serwa  \0"

#define LEN_VSWASHTYPE         "\004"
#define TR_VSWASHTYPE          "---\0""120\0""120X""140\0""90\0"

#define LEN_VKEYS              "\005"
#define TR_VKEYS               TR("Menu\0""Exit\0""D\205\203 \0""G\205ra\0""Prawo""Lewo\0", "Menu\0""Exit\0""Enter""Page\0""Plus\0""Minus")

#define LEN_VRENCODERS         "\003"
#define TR_VRENCODERS          "REa""REb"

#define LEN_VSWITCHES          "\003"
#define LEN_VSRCRAW            "\004"

#define TR_STICKS_VSRCRAW      TR("SK \0""SW \0""Gaz\0""Lot\0", "\307SK ""\307SW ""\307Gaz""\307Lot")
#define TR_TRIMS_VSRCRAW       TR("TrSK""TrSW""TrGA""TrLO", "\313SK ""\313SW ""\313Gaz""\313Lot")

#define TR_POTS_VSRCRAW      "P1\0 ""P2\0 ""P3\0 "
#define TR_SW_VSRCRAW        "3POS"
#define TR_9X_3POS_SWITCHES  "ID0""ID1""ID2"

#define TR_LOGICALSW         "L1\0""L2\0""L3\0""L4\0""L5\0""L6\0""L7\0""L8\0""L9\0""L10""L11""L12"

#define TR_TRIMS_SWITCHES      TR("tRl""tRr""tEd""tEu""tTd""tTu""tAl""tAr", "\313Rl""\313Rr""\313Ed""\313Eu""\313Td""\313Tu""\313Al""\313Ar")

#if defined(PCBGRUVIN9X) || defined(PCBMEGA2560)
#define TR_ROTARY_ENCODERS   "REa\0""REb\0"
#define TR_ROTENC_SWITCHES   "REa""REb"
#else
#define TR_ROTARY_ENCODERS
#define TR_ROTENC_SWITCHES
#endif

#define TR_PHYS_SWITCHES     "GAZ""SK ""SW ""LOT""GEA""TRN"

#define TR_ON_ONE_SWITCHES     "ON\0""One"

#define TR_VSWITCHES         "---" TR_9X_3POS_SWITCHES TR_PHYS_SWITCHES TR_TRIMS_SWITCHES TR_ROTENC_SWITCHES TR_LOGICALSW TR_ON_ONE_SWITCHES

#if defined(HELI)
#define TR_CYC_VSRCRAW       "CYC1""CYC2""CYC3"
#else
#define TR_CYC_VSRCRAW       "[C1]""[C2]""[C3]"
#endif

#define TR_EXTRA_VSRCRAW

#define TR_VSRCRAW             "---\0" TR_STICKS_VSRCRAW TR_POTS_VSRCRAW TR_ROTARY_ENCODERS "MAX\0" TR_CYC_VSRCRAW TR_TRIMS_VSRCRAW TR_SW_VSRCRAW TR_EXTRA_VSRCRAW

#define LEN_VTMRMODES          "\003"
#define TR_VTMRMODES           "WY\214""ABS""THs""TH%""THt"

#define LEN_VTRAINERMODES      "\022" /*18 decimal*/
#define TR_VTRAINERMODES       "Trener/Jack\0      ""Ucze\204/Jack\0       ""Trener/SBUS Modu\203 ""Trener/CPPM Modu\203 ""Trener/Bateria\0   "

#define LEN_VFAILSAFE          "\011" /*9 decimal*/
#define TR_VFAILSAFE           "Brak   \0 ""Utrzymuj\0""W\203asne  \0""0 sygna\203u""Odbiornik"

#if defined(MAVLINK)
#define LEN_MAVLINK_BAUDS    "\006"
#define TR_MAVLINK_BAUDS     "4800  ""9600  ""14400 ""19200 ""38400 ""57600 ""76800 ""115200"
#define LEN_MAVLINK_AC_MODES "\011" /*9 decimal*/
#define TR_MAVLINK_AC_MODES  "Stabiliz.""Akro     ""Alt Hold ""Auto     ""Sterowany""Loiter   ""RTL      ""Ko\203o     ""Utrzymuj ""L\200duj    ""OF Loiter""Toy A    ""Toy M    ""B\214\213DNY   "
#define LEN_MAVLINK_AP_MODES "\015" /*13 decimal*/
#define TR_MAVLINK_AP_MODES  "R\202czny      ""Ko\203o         ""Stabilizacja ""Trening      ""Fly by Wire A""Fly by Wire A""Auto         ""RTL          ""Loiter       ""Sterowany    ""Inicjalizacja""B\214\213DNY       "
#endif

#define LEN_VSENSORTYPES        "\012" /*10 decimal*/
#define TR_VSENSORTYPES        "U\207ytkownik""Obliczone "

#define LEN_VFORMULAS          "\010" /*8 decimal*/
#define TR_VFORMULAS           "Dodaj\0  ""\217rednie\0""Min\0    ""Max\0    ""Mn\205\207\0   ""Zliczani""Kom\205rka\0""Zu\207ycie\0""Zasi\202g\0 "

#define LEN_VPREC              "\004"
#define TR_VPREC               "0.--""0.0 ""0.00"

#define LEN_VCELLINDEX         "\007"
#define TR_VCELLINDEX          "Niskie\0""1\0     ""2\0     ""3\0     ""4\0     ""5\0     ""6\0     ""Wysokie""Delta\0"

// ZERO TERMINATED STRINGS
#define INDENT               "\001"
#define LEN_INDENT           1
#define INDENT_WIDTH         (FW/2)
#define BREAKSPACE           " "

#define TR_ENTER             "[MENU]"

#define TR_EXIT                "[WYJ\217]"

#define TR_POPUPS            TR_ENTER "\010" TR_EXIT
#define OFS_EXIT             sizeof(TR_ENTER)

#define TR_MENUWHENDONE        CENTER "\006"TR_ENTER " > DALEJ  "
#define TR_FREE                "woln"
#define TR_DELETEMODEL         "SKASUJ MODEL"
#define TR_COPYINGMODEL        "Kopiuj model.."
#define TR_MOVINGMODEL         "Przenie\206 model."
#define TR_LOADINGMODEL        "Za\203aduj model.."
#define TR_NAME                "Nazwa"
#define TR_MODELNAME           "Nazwa modelu"
#define TR_PHASENAME           "Nazwa Fazy"
#define TR_MIXNAME             "Nazwa Mix"
#define TR_INPUTNAME           "Wpisz Nazw"
#define TR_EXPONAME            "Nazwa Exp"
#define TR_BITMAP              "Obrazek    "
#define TR_TIMER               TR("Timer", "Timer ")
#define TR_ELIMITS             TR("Limi+25%", "Kana\203 +/- 125% ")
#define TR_ETRIMS              TR("E.Trym ", "Poszer Trymery")
#define TR_TRIMINC             "Krok Trym"
#define TR_DISPLAY_TRIMS       TR("Pok.Trym.","Poka\207 Trymery")
#define TR_TTRACE              TR("\221r\205d gaz", INDENT "\221r\205d\203o gazu ")
#define TR_TTRIM               TR("TryGaz", INDENT "TrymWolnObrot\205")
#define TR_BEEPCTR             TR("\217rodBeep", "Pikn.\217rodka")
#define TR_USE_GLOBAL_FUNCS    TR("Funk.Glb.","U\207yj Funkcji Glb")
#define TR_PROTO               TR(INDENT "Proto", INDENT "Protok\205\203")
#define TR_PPMFRAME          INDENT "Ramka PPM"
#define TR_MS                  "ms"
#define TR_SWITCH              "Prze\203\200"
#define TR_TRIMS               "Trymy"
#define TR_FADEIN              "Pojawia"
#define TR_FADEOUT             "Zanik   "
#define TR_DEFAULT             "(Bazowa) "
#define TR_CHECKTRIMS          CENTER "\006Spr  \012Trymy"
#define OFS_CHECKTRIMS         CENTER_OFS+(9*FW)
#define TR_SWASHTYPE           "Typ tarczy"
#define TR_COLLECTIVE          TR("Kolektyw", "\221r\205d\203o Kolektywu")
#define TR_AILERON             "Lateral cyc. source"
#define TR_ELEVATOR            "Long. cyc. source"
#define TR_SWASHRING           "Tarcza    "
#define TR_ELEDIRECTION        TR("Ster Wysoko\206c","D\203ug. Kierunku cyklu")
#define TR_AILDIRECTION        TR("Kierunek Lotk","Lateral cyc. direction")
#define TR_COLDIRECTION        TR("PIT Direction","Coll. pitch direction")
#define TR_MODE                INDENT "Tryb"
#define TR_NOFREEEXPO          "BrakWoln.Expo!"
#define TR_NOFREEMIXER         "BrakWoln.Mix\205w!"
#define TR_INSERTMIX           "WSTAW MIX"
#define TR_EDITMIX             "EDYTUJ MIX"
#define TR_SOURCE              INDENT "\221r\205d\203o"
#define TR_WEIGHT              "Waga "
#define TR_EXPO                TR("Expo", "Exponential")
#define TR_SIDE                "Strona"
#define TR_DIFFERENTIAL        "R\205\207nic"
#define TR_OFFSET              INDENT"Ofset "
#define TR_TRIM                "Trym"
#define TR_DREX                "DRex"
#define DREX_CHBOX_OFFSET      30
#define TR_CURVE               "Krzywa"
#define TR_FLMODE              "Tryb"
#define TR_MIXWARNING          "UWAGA"
#define TR_OFF                 "Wy\203."
#define TR_MULTPX              "Z\203\200cz."
#define TR_DELAYDOWN           "Op\205zn.(-)"
#define TR_DELAYUP             "Op\205zn.(+)"
#define TR_SLOWDOWN            "Spowoln.(-)"
#define TR_SLOWUP              "Spowoln.(+)"
#define TR_MIXER               "MIKSERY"
#define TR_CV                  "Kr"
#define TR_GV                  "ZG"
#define TR_ACHANNEL            "A\004Kana\203"
#define TR_RANGE               INDENT "Zakres"
#define TR_CENTER              INDENT "\217rodek"
#define TR_BAR                 "Pas"
#define TR_ALARM               INDENT "Alarm"
#define TR_USRDATA             TR("Dane U\207ytk.", "Dane u\207ytkownika")
#define TR_BLADES              " \214opaty \206migla"
#define TR_SCREEN              "Ekran "
#define TR_SOUND_LABEL         "D\210wi\202k"
#define TR_LENGTH              INDENT"D\203ugo\206\201"
#define TR_BEEP_LENGTH         INDENT "D\203ug. Beepa"
#define TR_SPKRPITCH           INDENT"D\210wi\202k"
#define TR_HAPTIC_LABEL        "Wibracja"
#define TR_HAPTICSTRENGTH      INDENT"Si\203a"
#define TR_CONTRAST            "Kontrast"
#define TR_ALARMS_LABEL        "Alarmy"
#define TR_BATTERY_RANGE       TR("Poka\207PasBat.", "Poka\207 pasek bateri")
#define TR_BATTERYWARNING      INDENT"Bateria roz\203adowana"
#define TR_INACTIVITYALARM     INDENT"Alarm bezczynno\206ci"
#define TR_MEMORYWARNING       INDENT"Pe\203na pami\202\201"
#define TR_ALARMWARNING        INDENT"Wy\203\200cz d\210wi\202k"
#define TR_RENAVIG             "Nawigacja potencjometrem"
#define TR_THROTTLE_LABEL      "Gaz    "
#define TR_THROTTLEREVERSE     TR("OdwrGaz", INDENT "OdwrGaz")
#define TR_TIMER_NAME          INDENT "Nazwa"
#define TR_MINUTEBEEP          TR(INDENT "Minuta", INDENT "PikCoMinut\202")
#define TR_BEEPCOUNTDOWN       INDENT "Odliczanie"
#define TR_PERSISTENT          TR(INDENT "Dok\203.", INDENT "Dok\203adny")
#define TR_BACKLIGHT_LABEL     "Pod\206wietl"
#define TR_BLDELAY             INDENT"Czas trwania"
#define TR_BLONBRIGHTNESS      INDENT"Jasno\206c w\203."
#define TR_BLOFFBRIGHTNESS     INDENT"Jasno\206\201 wy\203."
#define TR_BLCOLOR             INDENT "Color"
#define TR_SPLASHSCREEN        "Logo ekranu"
#define TR_THROTTLEWARNING     TR(IF_CPUARM(INDENT)"OstrzGaz", INDENT "Ostrze\207enieGaz")
#define TR_SWITCHWARNING       TR("OstrzPrze\203", INDENT "PozycjaPrze\203")
#define TR_POTWARNING          TR("Ostrz.Poten.", INDENT "PozycjaPotencj.")
#define TR_TIMEZONE            TR("Strefa czasowa" ,"Strefa czasowa GPS")
#define TR_ADJUST_RTC          INDENT "RegulujRTC"
#define TR_GPS                 "GPS"
#define TR_RXCHANNELORD        TR("KolejnKan.RX", "Bazowa kolejno\206\201 kana\203\205w")
#define TR_STICKS              "Dr\200\207ki"
#define TR_POTS                "Pots"
#define TR_SWITCHES            "Prze\203\200cz"
#define TR_SWITCHES_DELAY      "Op\205\210n.Prze\203."
#define TR_SLAVE               "Ucze\204"
#define TR_MODESRC             " Tryb\006% \221r\205d\203o"
#define TR_MULTIPLIER          "Mno\207nik"
#define TR_CAL                 "Kal."
#define TR_VTRIM               "Trym- +"
#define TR_BG                  "BG:"
#define TR_MENUTOSTART       CENTER "\010" TR_ENTER " KALIBRUJ"
#define TR_SETMIDPOINT         TR(CENTER "\002Cenruj dr\200\207ki/potencj",CENTER "\010Ustaw dr\200zki/potencj na \206rodku")
#define TR_MOVESTICKSPOTS      "Poruszaj dr\200\207kami/pot"
#define TR_RXBATT              "Rx Batt:"
#define TR_TXnRX               "Tx:\0Rx:"
#define OFS_RX                 4
#define TR_ACCEL               "Acc:"
#define TR_NODATA              CENTER "BrakDAN"
#define TR_TOTTM1TM2THRTHP     "\037\146SES\036TM1\037\146TM2\036THR\037\146TH%"
#define TR_TMR1LATMAXUS        "Tmr1Lat max\037\124us"
#define STR_US                 (STR_TMR1LATMAXUS+13)
#define TR_TMR1LATMINUS        "Tmr1Lat min\037\124us"
#define TR_TMR1JITTERUS        "Tmr1 Jitter\037\124us"

#define TR_TMIXMAXMS         "TmixMaks\037\124ms"
#define TR_FREESTACKMINB     "Wolny stos\037\124b"

#define TR_MENUTORESET         CENTER TR_ENTER " >> Reset"
#define TR_PPM_TRAINER         "TR"
#define TR_CH                  "KN"
#define TR_MODEL               "MODEL"
#define TR_FP                  "FL"
#define TR_MIX                 "MIX"
#define TR_EEPROMLOWMEM        "Niska pami\202\201 EEPROM"
#define TR_ALERT               "\006UWAGA"
#define TR_PRESSANYKEYTOSKIP   "Wci\206nij guzik->ignoruj"
#define TR_THROTTLENOTIDLE     "Gaz nie na zerze"
#define TR_ALARMSDISABLED      "Alarmy wy\203\200czone"
#define TR_PRESSANYKEY         TR("\010Wci\206nij jaki\206 klawisz","Wci\206nij jaki\206 klawisz")
#define TR_BADEEPROMDATA       "\006B\203\200d danych EEPROM"
#define TR_EEPROMFORMATTING    "\004Formatowanie EEPROM"
#define TR_EEPROMOVERFLOW      "Prze\203adowany EEPROM"
#define TR_MENURADIOSETUP      "USTAWIENIA RADIA"
#define TR_MENUDATEANDTIME     "DATA I CZAS"
#define TR_MENUTRAINER         "TRENER"
#define TR_MENUGLOBALFUNCS     "FUNKCJE GLOBALNE"
#define TR_MENUVERSION         "WERSJA"
#define TR_MENUDIAG            TR("PRZE\214","TEST PRZE\214")
#define TR_MENUANA             TR("WE-ANA","WEJ\217CIA ANALOG.")
#define TR_MENUCALIBRATION     "KALIBRACJA"
#define TR_TRIMS2OFFSETS     "\006Trims => Subtrims"
#define TR_MENUMODELSEL        TR("WYB.MODEL","WYB\216R MODELU")
#define TR_MENUSETUP           TR("USTAW","USTAW MODELU")
#define TR_MENUFLIGHTPHASE     "FAZA LOTU"
#define TR_MENUFLIGHTPHASES    "FAZY LOTU"
#define TR_MENUHELISETUP       "USTAW HELI"

#define TR_MENUINPUTS        "DR\211\220KI"
#define TR_MENULIMITS        "SERWA "

#define TR_MENUCURVES          "KRZYWE"
#define TR_MENUCURVE           "KRZYWA"
#define TR_MENULOGICALSWITCH    "PRZE\214. LOGICZNY"
#define TR_MENULOGICALSWITCHES   TR("PRZE\214. LOG.", "PRZE\214. LOGICZNE")
#define TR_MENUCUSTOMFUNC      "FUNKCJE SPECJALNE"
#define TR_MENUCUSTOMSCRIPTS   "W\214ASNE SKRYPTY"
#define TR_MENUCUSTOMSCRIPT    "W\214ASNY SKRYPT"
#define TR_MENUTELEMETRY       "TELEMETRIA"
#define TR_MENUTEMPLATES       "SZABLONY"
#define TR_MENUSTAT            "STAT"
#define TR_MENUDEBUG           "DEBUG"
#define TR_RXNUM             "NumOdb"
#define TR_SYNCMENU            "[Synch]"
#define TR_LIMIT               INDENT "Limit"
#define TR_MINRSSI             "Min Rssi"
#define TR_LATITUDE            "Szer. geo."
#define TR_LONGITUDE           "D\203.   geo."
#define TR_GPSCOORD            TR("Koord.GPS","Typ koordynat GPS")
#define TR_VARIO               TR("Wario","Wariometr")
#define TR_PITCH_AT_ZERO       INDENT "Ton przy Zerze"
#define TR_PITCH_AT_MAX        INDENT "Ton przy Max"
#define TR_REPEAT_AT_ZERO      INDENT "Powt\205rz przy Zerze"
#define TR_POWEROFF            "\027Wy\203\200czanie.."
#define TR_SHUTDOWN            "Wy\203\200czanie.."
#define TR_SAVEMODEL           "Zapisz ustwienia modelu"
#define TR_BATT_CALIB          "Kalib:Baterii"
#define TR_CURRENT_CALIB       " +=\006Kalibracja pr\200du"
#define TR_VOLTAGE             TR (INDENT"Napi\202cie",INDENT"\221r\205d\203o Napi\202cia")
#define TR_CURRENT             TR (INDENT"Pr\200d",INDENT"\221r\205d\203o Pr\200du")
#define TR_SELECT_MODEL        "Wyb\205r modelu"
#define TR_CREATE_MODEL        "Nowy model"
#define TR_COPY_MODEL          "Skopiuj model"
#define TR_MOVE_MODEL          "Przenie\206 model"
#define TR_BACKUP_MODEL        "Zbackupuj model"
#define TR_DELETE_MODEL        "Skasuj model"
#define TR_RESTORE_MODEL       "Odtw\205rz model"
#define TR_SDCARD_ERROR        "B\203\200d karty SD"
#define TR_NO_SDCARD           "Brak karty SD"
#define TR_SDCARD_FULL         "Karta Pe\203na "
#define TR_INCOMPATIBLE        "Niekompatybilne"
#define TR_WARNING             "UWAGA"
#define TR_EEPROMWARN          "EEPROM"
#define TR_EEPROM_CONVERTING   "Konwersja EEPROM"
#define TR_THROTTLEWARN        "GAZ"
#define TR_ALARMSWARN          "ALARM"
#define TR_SWITCHWARN          TR("Prze\203\200","Kontrola")
#define TR_FAILSAFEWARN        "FAILSAFE"
#define TR_NO_FAILSAFE         "Brak Failsafe"
#define TR_KEYSTUCK            "Blokada klucza"
#define TR_INVERT_THR          TR("Odw.Gaz?","Odwr\205\201 gaz?")
#define TR_SPEAKER_VOLUME      INDENT "G\203o\206no\206\201"
#define TR_LCD                 "LCD"
#define TR_BRIGHTNESS          INDENT "Jasno\206\201"
#define TR_CPU_TEMP            "Temp. CPU\016>"
#define TR_CPU_CURRENT         "Pr\200d"
#define TR_CPU_MAH             "Zu\207ycie"
#define TR_COPROC              "CoProc."
#define TR_COPROC_TEMP         "Temp. MB"
#define TR_CAPAWARNING         INDENT "Ma\203a pojemno\206\201"
#define TR_TEMPWARNING         INDENT "Przegrzanie"
#define TR_FUNC                "Funkc"
#define TR_V1                  "V1"
#define TR_V2                  "V2"
#define TR_DURATION            "Czas trwania"
#define TR_DELAY               "Op\205\210nienie"
#define TR_SD_CARD             "SD"
#define TR_SDHC_CARD           "SD-HC"
#define TR_NO_SOUNDS_ON_SD     "Brak d\210wi\202k\205w na SD"
#define TR_NO_MODELS_ON_SD     "Brak modelu na SD"
#define TR_NO_BITMAPS_ON_SD    "Brak obrazk\205w na SD"
#define TR_NO_SCRIPTS_ON_SD    "Brak skrypt\205w na SD"
#define TR_SCRIPT_SYNTAX_ERROR "Skrypt:syntax error"
#define TR_SCRIPT_PANIC        "Skrypt:panic"
#define TR_SCRIPT_KILLED       "Skrypt:killed"
#define TR_SCRIPT_ERROR        "Nieznany b\203\200d"
#define TR_PLAY_FILE           "Odtw\205rz"
#define TR_DELETE_FILE         "Skasuj"
#define TR_COPY_FILE           "Kopiuj"
#define TR_RENAME_FILE         "Zmie\204 nazw\202"
#define TR_ASSIGN_BITMAP       "Wybierz obrazek"
#define TR_EXECUTE_FILE        "Wykonaj"
#define TR_REMOVED             " skasowane"
#define TR_SD_INFO             "Informacje"
#define TR_SD_FORMAT           "Formatuj"
#define TR_NA                  "[X]"
#define TR_HARDWARE            "HARDWARE"
#define TR_FORMATTING          "Formatowanie.."
#define TR_TEMP_CALIB          "Temp. kalibracji"
#define TR_TIME                "Czas"
#define TR_BAUDRATE            "Pr\202dko\206\201 BT"
#define TR_SD_INFO_TITLE       "SD INFO"
#define TR_SD_TYPE             "Typ:"
#define TR_SD_SPEED            "Pr\202dko\206\201:"
#define TR_SD_SECTORS          "Sektory :"
#define TR_SD_SIZE             "Wielko\206\201:"
#define TR_TYPE                INDENT TR_SD_TYPE
#define TR_GLOBAL_VARS         "Zmienne Globalne"
#define TR_GLOBAL_V            "Zmien.Glob."
#define TR_GLOBAL_VAR          "Zmienna Globalna"
#define TR_MENUGLOBALVARS      "ZMIENNE GLOBALNE"
#define TR_OWN                 "W\203asno\206\201"
#define TR_DATE                "Data"
#define TR_ROTARY_ENCODER      "R.Encs"
#define TR_CHANNELS_MONITOR    "MONITOR KANA\214\216W"
#define TR_MIXERS_MONITOR      "MONITOR MIKSER"
#define TR_PATH_TOO_LONG       "\217cie\207ka za d\203uga"
#define TR_VIEW_TEXT           "Poka\207 tekst"
#define TR_FLASH_BOOTLOADER    "Flash BootLoader"
#define TR_FLASH_EXTERNAL_DEVICE "Sflashuj Modu\203 Zewn\202trzny"
#define TR_FLASH_INTERNAL_MODULE "Sflashuj Modu\203 Wewn\202trzny"
#define TR_WRITING             "\032Zapis...  "
#define TR_CONFIRM_FORMAT      "Zatwierd\210 Format?"
#define TR_INTERNALRF          "Wewn.Modu\203 RF"
#define TR_EXTERNALRF          "Zewn.Modu\203 RF"
#define TR_FAILSAFE            TR(INDENT"Failsafe",INDENT"Tryb Failsafe")
#define TR_FAILSAFESET         "USTAWIENIE FAILSAFE"
#define TR_MENUSENSOR          "CZUJNIK"
#define TR_COUNTRYCODE         "Kod regionu"
#define TR_VOICELANG           "J\202zyk g\203osu"
#define TR_UNITSSYSTEM         "Jednostki"
#define TR_EDIT                "Edytuj"
#define TR_INSERT_BEFORE       "Wstaw przed"
#define TR_INSERT_AFTER        "Wstaw za"
#define TR_COPY                "Kopiuj"
#define TR_MOVE                "Przenie\206"
#define TR_PASTE               "Wklej"
#define TR_DELETE              "Kasuj"
#define TR_INSERT              "Wstaw"
#define TR_RESET_FLIGHT        "Zeruj lot"
#define TR_RESET_TIMER1        "Zeruj Timer1"
#define TR_RESET_TIMER2        "Zeruj Timer2"
#define TR_RESET_TIMER3        "Zeruj Timer3"
#define TR_RESET_TELEMETRY     "Wyczy\206\201 telemetri\202"
#define TR_STATISTICS          "Statystyki"
#define TR_ABOUT_US            "O nas"
#define TR_AND_SWITCH          "Prze\203\200cznik AND"
#define TR_SF                  "FS"
#define TR_GF                  "FG"
#define TR_SPEAKER             INDENT"G\203o\206nik"
#define TR_BUZZER              INDENT"Brz\202czyk"
#define TR_BYTES               "bajty"
#define TR_MODULE_BIND         TR("[BND]","[Bind]")
#define TR_MODULE_RANGE        TR("[Zas]","Zasi\202g")
#define TR_RESET_BTN           "[Reset]"
#define TR_SET                 "[Set]"
#define TR_TRAINER             "Port Trenera"
#define TR_ANTENNAPROBLEM      CENTER "Problem z anten\200 TX"
#define TR_MODELIDUSED         TR("ID zaj\202te","ID modelu zaj\202te")
#define TR_MODULE              INDENT "Modu\203 "
#define TR_TELEMETRY_TYPE      TR("Typ ", "Typ Telemetrii")
#define TR_TELEMETRY_SENSORS   "Czujniki"
#define TR_VALUE               "Warto\206\201"
#define TR_TOPLCDTIMER         "Top LCD Timer"
#define TR_UNIT                "Jedn"
#define TR_TELEMETRY_NEWSENSOR INDENT "Dodaj nowy czujnik..."
#define TR_CHANNELRANGE        TR(INDENT "ZakrKn",INDENT "Zakres kana\203u")
#define TR_LOWALARM            INDENT "Alarm niski"
#define TR_CRITICALALARM       INDENT "Alarm krytyczny"
#define TR_ENABLE_POPUP        "Aktywuj Popup"
#define TR_DISABLE_POPUP       "Wy\203\200cz Popup"
#define TR_CURVE_PRESET        "Predef..."
#define TR_PRESET              "Predef."
#define TR_MIRROR              "Lustro"
#define TR_CLEAR               "Wyczy\206\201"
#define TR_RESET               "Resetuj"
#define TR_RESET_SUBMENU       "Reset..."
#define TR_COUNT               "Punkty"
#define TR_PT                  "pkt"
#define TR_PTS                 "pkty"
#define TR_SMOOTH              "G\203adka"
#define TR_COPY_STICKS_TO_OFS  "Skopiuj Dr\200\207ki Do Offsetu"
#define TR_COPY_TRIMS_TO_OFS   "Skopiuj Trymery Do subtrymer\205w"
#define TR_INCDEC              "Zwi\202ksz/Zmnie"
#define TR_GLOBALVAR           "Zm.Global."
#define TR_MIXSOURCE           "\221r\205d\203o Miks."
#define TR_CONSTANT            "Stala   "
#define TR_PERSISTENT_MAH      TR(INDENT "Zap. mAh", INDENT "Zapisz mAh")
#define TR_PREFLIGHT           "Lista Ostrze\207e\204"
#define TR_CHECKLIST           TR(INDENT "Czeklista",INDENT "Poka\207 List\202 Ostrze\207e\204")
#define TR_FAS_OFFSET          TR(INDENT "FAS Ofs", INDENT "FAS Offset")
#define TR_UART3MODE           "Port szreg."
#define TR_SCRIPT              "Skrypt"
#define TR_INPUTS              "Wej\206cia"
#define TR_OUTPUTS             "Wyj\206cia"
#define TR_EEBACKUP            "\012[ENTER D\203ugo] Backup EEPROMu"
#define TR_FACTORYRESET        "\012[MENU Long]: Ustaw.Fabrycz"
#define TR_CONFIRMRESET        "WYkasowa\201 wszytkie modele?    "
#define TR_TO_MANY_LUA_SCRIPTS "Za du\207o skrypt\205w Lua!"

#if defined(MAVLINK)
#define TR_MAVLINK_RC_RSSI_SCALE_LABEL  "MaksRSSI"
#define TR_MAVLINK_PC_RSSI_EN_LABEL     "PC RSSI EN"
#define TR_MAVMENUSETUP_TITLE           "Ustaw.Mavlink"
#define TR_MAVLINK_BAUD_LABEL           "Baudrate"
#define TR_MAVLINK_INFOS                "INFO"
#define TR_MAVLINK_MODE                 "TRYB"
#define TR_MAVLINK_CUR_MODE             "Aktualy Tryb"
#define TR_MAVLINK_ARMED                "Aktywny"
#define TR_MAVLINK_BAT_MENU_TITLE       "BAT RSSI"
#define TR_MAVLINK_BATTERY_LABEL        "Status bateriOdbiorn."
#define TR_MAVLINK_RC_RSSI_LABEL        "RC RSSI"
#define TR_MAVLINK_PC_RSSI_LABEL        "PC RSSI"
#define TR_MAVLINK_NAV_MENU_TITLE       "NAV"
#define TR_MAVLINK_COURSE               "Kurs"
#define TR_MAVLINK_HEADING              "Kierunek"
#define TR_MAVLINK_BEARING              "Orientacja"
#define TR_MAVLINK_ALTITUDE             "Wysoko\206\201"
#define TR_MAVLINK_GPS                  "GPS"
#define TR_MAVLINK_NO_FIX               "NO Fix"
#define TR_MAVLINK_SAT                  "SAT"
#define TR_MAVLINK_HDOP                 "HDOP"
#define TR_MAVLINK_LAT                  "SZR"
#define TR_MAVLINK_LON                  "DLG"
#endif

// Taranis column headers
#define TR_PHASES_HEADERS      { " Nazwa", " Prze\203\200.", " Trymer SK   ", " Trymer SW     ", " Trymer Gazu   ", " Trymer Lotek ", " Pojawian", " Zanik    " }
#define TR_LIMITS_HEADERS      { " Nazwa", " Subtrim ", " Min ", " Max ", " Kierunek  ", " Krzywa", " \217rodek PPM ", " Tryb subtrim " }
#define TR_CSW_HEADERS         { " Funkcja  ", " V1 ", " V2 ", " V2 ", " AND Prze\203\200 ", " CzasTrwa ", " Op\205\210n " }

// About screen
#define TR_ABOUTUS             TR("   O   ", "  O  ")

#define TR_ABOUT_OPENTX_1      TR("OpenTX\001is\001open\001source,\001non", "OpenTX is open source, non-")
#define TR_ABOUT_OPENTX_2      TR("commercial,\001wo\001warranties.", "commercial and comes with no")
#define TR_ABOUT_OPENTX_3      TR("It\001was\001developed\001for\001free.", "warranties. It was developed")
#define TR_ABOUT_OPENTX_4      TR("Support through donations", "for free. Support through")
#define TR_ABOUT_OPENTX_5      TR("is welcome!", "donations is welcome!")

#define TR_ABOUT_BERTRAND_1    "Bertrand Songis"
#define TR_ABOUT_BERTRAND_2    "OpenTX g\203\205wny autor"
#define TR_ABOUT_BERTRAND_3    "Companion9x wsp\205\203-autor"

#define TR_ABOUT_MIKE_1        "Mike Blandford"
#define TR_ABOUT_MIKE_2        "Guru kodu i driwer\205w"
#define TR_ABOUT_MIKE_3        TR("Arguably,\001one\001of\001the\001best", "Arguably, one of the best")
#define TR_ABOUT_MIKE_4        "Inspirational"

#define TR_ABOUT_ROMOLO_1      "Romolo Manfredini"
#define TR_ABOUT_ROMOLO_2      "Companion9x wsp\205\203-autor"
#define TR_ABOUT_ROMOLO_3      ""

#define TR_ABOUT_ANDRE_1       "Andre Bernet"
#define TR_ABOUT_ANDRE_2       "Funkcjonalno\206\201, u\207ytkowo\206\201,"
#define TR_ABOUT_ANDRE_3       "debugging, documentacja"

#define TR_ABOUT_ROB_1         "Rob Thomson"
#define TR_ABOUT_ROB_2         "openrcforums webmaster"

#define TR_ABOUT_KJELL_1       "Kjell Kernen"
#define TR_ABOUT_KJELL_2       "www.open-tx.org main author"
#define TR_ABOUT_KJELL_3       "OpenTX Recorder author"
#define TR_ABOUT_KJELL_4       "Companion contributor"

#define TR_ABOUT_MARTIN_1      "Martin Hotar"
#define TR_ABOUT_MARTIN_2      "Projekty graficzne"

#define TR_ABOUT_HARDWARE_1  "Brent Nelson"
#define TR_ABOUT_HARDWARE_2  "Sky9x tw\205rca/producent"
#define TR_ABOUT_HARDWARE_3  ""

#define TR_ABOUT_PARENTS_1     "Projekty macierzyste"
#define TR_ABOUT_PARENTS_2     TR("Ersky9x (Mike Blandford)", "Ersky9x (Mike Blandford)")
#define TR_ABOUT_PARENTS_3     "ER9X (Erez Raviv)"
#define TR_ABOUT_PARENTS_4     "TH9X (Thomas Husterer)"

#define TR_CHR_SHORT           'k'
#define TR_CHR_LONG            'd'
#define TR_CHR_TOGGLE          't'
#define TR_CHR_HOUR            'h'
#define TR_CHR_INPUT           'I'   // Values between A-I will work

#define TR_BEEP_VOLUME         "G\203o\206n pikan"
#define TR_WAV_VOLUME          "G\203o\206n wav  "
#define TR_VARIO_VOLUME        "G\203o\206n wario "
#define TR_BG_VOLUME           "G\203o\206n t\203a"

#define TR_TOP_BAR             "G\205rnPas"
#define TR_ALTITUDE            INDENT "Wysoko\206\201"
#define TR_SCALE               "Skala"
#define TR_VIEW_CHANNELS       "Poka\207 Kana\203y"
#define TR_VIEW_NOTES          "Poka\207 Notki"
#define TR_MODS_FORBIDDEN      "Modyfikacje zabronione!"
#define TR_UNLOCKED            "Odblokowane"
#define TR_ID                  "ID"
#define TR_PRECISION           "Precyzja "
#define TR_RATIO               "Wsp\205\203cz."
#define TR_FORMULA             "Formu\203a"
#define TR_CELLINDEX           "Cell index"
#define TR_LOGS                "Logi"
#define TR_OPTIONS             "Opcje  "

#define TR_ALTSENSOR           "Alt sensor"
#define TR_CELLSENSOR          "Cell sensor"
#define TR_GPSSENSOR           "GPS sensor"
#define TR_CURRENTSENSOR       "Sensor"
#define TR_AUTOOFFSET          "Auto Ofset"
#define TR_ONLYPOSITIVE        "Dodatni"
#define TR_FILTER              "Filtr"
#define TR_TELEMETRYFULL       "Wszyskie miejsca zaj\202te!"
//TODO: translation
#define TR_INVERTED_SERIAL     INDENT "Odwr\205\201"
#define TR_IGNORE_INSTANCE     INDENT "Ignoruj przypadek"
#define TR_DISCOVER_SENSORS    INDENT "Znajd\210 nowe czujniki"
#define TR_STOP_DISCOVER_SENSORS INDENT "Szukanie STOP "
#define TR_DELETE_ALL_SENSORS  INDENT "Usu\204 czujniki     "
#define TR_CONFIRMDELETE       "Usun\200\201 wszystkie ?"

#define TR_MENU_INPUTS         "\314Wej\206ci"
#define TR_MENU_LUA            "\322SkryptyLUA"
#define TR_MENU_STICKS         "\307Dr\200\207ki"
#define TR_MENU_POTS           "\310Pots"
#define TR_MENU_MAX            "\315MAX"
#define TR_MENU_HELI           "\316Cyclic"
#define TR_MENU_TRIMS          "\313Trymy"
#define TR_MENU_SWITCHES       "\312Prze\203czn"
#define TR_MENU_LOGICAL_SWITCHES "\312Prze\203\200czn.Logicz"
#define TR_MENU_TRAINER        "\317Trener "
#define TR_MENU_CHANNELS       "\320Kana\203y  "
#define TR_MENU_GVARS          "\311ZmGlo"
#define TR_MENU_TELEMETRY      "\321Telemetry"
#define TR_MENU_OTHER          "Inny "
#define TR_MENU_INVERT         "Odwr\205\201"

#define ZSTR_RSSI              "\022\023\023\011"
#define ZSTR_SWR               "\023\027\022"
#define ZSTR_A1                "\001\034"
#define ZSTR_A2                "\001\035"
#define ZSTR_A3                "\001\036"
#define ZSTR_A4                "\001\037"
#define ZSTR_BATT              "\022\350\002\354"
#define ZSTR_ALT               "\001\364\354"
#define ZSTR_TEMP1             "\024\363\360\034"
#define ZSTR_TEMP2             "\024\363\360\035"
#define ZSTR_RPM               "\022\020\015"
#define ZSTR_FUEL              "\006\353\373\364"
#define ZSTR_VSPD              "\026\023\360\374"
#define ZSTR_ACCX              "\001\375\375\030"
#define ZSTR_ACCY              "\001\375\375\031"
#define ZSTR_ACCZ              "\001\375\375\032"
#define ZSTR_CURR              "\003\353\356\356"
#define ZSTR_VFAS              "\026\006\001\023"
#define ZSTR_ASPD              "\001\023\360\374"
#define ZSTR_GSPD              "\007\023\360\374"
#define ZSTR_HDG               "\010\374\371"
#define ZSTR_CELLS             "\003\373\364\355"
#define ZSTR_GPSALT            "\007\001\364\354"
#define ZSTR_GPSDATETIME       "\004\377\354\373"
#define ZSTR_GPS               "\007\020\023"
#define ZSTR_BATT1_VOLTAGE     "\022\002\034\026"
#define ZSTR_BATT2_VOLTAGE     "\022\002\035\026"
#define ZSTR_BATT1_CURRENT     "\022\002\034\001"
#define ZSTR_BATT2_CURRENT     "\022\002\035\001"
#define ZSTR_BATT1_CONSUMPTION "\022\002\034\003"
#define ZSTR_BATT2_CONSUMPTION "\022\002\035\003"
#define ZSTR_RX1_FAILSAFE      "\022\350\034\006"
#define ZSTR_RX1_LOSTFRAME     "\022\350\034\014"
#define ZSTR_RX1_CONN_LOST     "\022\350\034\003"
#define ZSTR_RX1_NO_SIGNAL     "\022\350\034\023"
#define ZSTR_RX2_FAILSAFE      "\022\350\035\006"
#define ZSTR_RX2_LOSTFRAME     "\022\350\035\014"
#define ZSTR_RX2_CONN_LOST     "\022\350\035\003"
#define ZSTR_RX2_NO_SIGNAL     "\022\350\035\023"
