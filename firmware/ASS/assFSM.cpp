#include "assFSM.h"

assFSM::assFSM(assWifi* wifi, assLoRa* lora, assData* data, assPixs* pixs, assButts* butts) {
    this->wifi = wifi;
    this->lora = lora;
    this->data = data;
    this->pixs = pixs;
    this->butts = butts;

    allUnlocks.push_back({assUnlocks::NONE,             "None",                         0}); // given
    allUnlocks.push_back({assUnlocks::INIT,             "INIT",                         0}); // default
    allUnlocks.push_back({assUnlocks::DEBUGIT,          "DEBUGIT",                      1}); // not used
    allUnlocks.push_back({assUnlocks::RECEIVED_UNLOCK,  "Received_Unlock",              1}); // not used
    allUnlocks.push_back({assUnlocks::RECEIVED_HELLO,   "Received_Hello",               1}); // not used

    allUnlocks.push_back({assUnlocks::KILLALLHUMANS,    "KILLALLHUMANS",                5}); //robots.txt
    allUnlocks.push_back({assUnlocks::CHANGEME,         "CHANGEMYDIAPER",                  5}); // password guess
    allUnlocks.push_back({assUnlocks::PASSWORD_UNLOCK,  "SuperS3cretP@ssword",          10}); // LoRa XOR
    allUnlocks.push_back({assUnlocks::FOURZEROFOUR,      "404_ASSnotFound",             3}); //UART leak
    allUnlocks.push_back({assUnlocks::NINEONEFIVE,       "915",                         3}); // readme hint
    allUnlocks.push_back({assUnlocks::XSS,               "FRIENDLY_XSS",                3}); //console xss
    allUnlocks.push_back({assUnlocks::ANYTHINGWOKRS,     "theflagisanythingworksyouass",  3}); //Caesar decrypt
    allUnlocks.push_back({assUnlocks::WAVE,                 "WavethatFlag",             3}); // pattern guess
    allUnlocks.push_back({assUnlocks::CHANGED,          "U_CH@N3D_ME",            5}); // sessionID
    allUnlocks.push_back({assUnlocks::IDOR,             "I_IDOR_YUR_ASS",            5}); // IDOR
    allUnlocks.push_back({assUnlocks::SQLI,          "ASSQLinj3ti0n",            3}); // sessionID
    allUnlocks.push_back({assUnlocks::ANSI,             "ASSni_l0g_injection",           7}); //ansi
    allUnlocks.push_back({assUnlocks::ILLEGALTOSELLONEBAY,     "ILLEGALTOSELLONEBAY",    5}); // read the css
    allUnlocks.push_back({assUnlocks::Petpika,     "Petpika",                 10}); // ReadMe 
    allUnlocks.push_back({assUnlocks::BLAME,     "blametheotherkyle",                 1}); // ReadMe 
    allUnlocks.push_back({assUnlocks::ASSHAT,            "ASSHAT",                      1}); // ReadMe 
    allUnlocks.push_back({assUnlocks::ILIKEBIG,     "ILikeBigButts",                 3}); // ReadMe 
    allUnlocks.push_back({assUnlocks::FISH,     "SwedishFish",                 2}); // Pure guess 
    allUnlocks.push_back({assUnlocks::GOGGLYEYES,     "GooglyEyes",                 2}); // Pure guess 
    allUnlocks.push_back({assUnlocks::PIKA,     "pika!pika!",                 4}); // patient output
    allUnlocks.push_back({assUnlocks::ASSUP,            "A55_UP",                      10}); //memory corru[tion vuln]

    allUnlocks.push_back({assUnlocks::FOUND,             "Y0u_F0und_MY_ASS",             7}); // twitter
    allUnlocks.push_back({assUnlocks::ASSOUT,           "youmakeanassoutofyouandme",    10}); // md5
    allUnlocks.push_back({assUnlocks::AUDIOSTEG,        "audio_steganography_simply",   10}); // audio
    allUnlocks.push_back({assUnlocks::BADCOMMIT,        "DO!COMMITdis",                 5}); // commit history
    allUnlocks.push_back({assUnlocks::SMACK_MY_SECURE_ASS,"SMACK_MY_SECURE_ASS",        10}); // binary flag in image
    allUnlocks.push_back({assUnlocks::U_CRACK_ME,         "U_CRACK_ME",                 3}); // ciphertext.txt
    allUnlocks.push_back({assUnlocks::SecurityASSurance,"SecurityASSurance",            7}); // LinkedIn
    allUnlocks.push_back({assUnlocks::AssOverTeakettle,  "AssOverTeakettle",            5}); // GitHub Action

    allUnlocks.push_back({assUnlocks::BOOBS,            "80085",                        1});
    allUnlocks.push_back({assUnlocks::MATTDAMON,        "MATTDAMON",                    3});
    allUnlocks.push_back({assUnlocks::HACKTHEPLANET,    "HackThePlanet",                5});
    allUnlocks.push_back({assUnlocks::WIRESHARK,        "W1RESHARK",                    1});
    allUnlocks.push_back({assUnlocks::ZAPP,              "Zapp_Brannigan",              5});
    allUnlocks.push_back({assUnlocks::MYCODEISLIKEYOURASS_BEAUTIFUL, "MYCODEISLIKEYOURASS_BEAUTIFUL", 5});

    allUnlocks.push_back({assUnlocks::GOTroot_0N_UR_ASS,   "GOTroot_0N_UR_ASS",         1});
    allUnlocks.push_back({assUnlocks::ASSOUT,            "ASSOUT",                      1});
    allUnlocks.push_back({assUnlocks::ASSymmetricEncryption,"ASSymmetricEncryption",    3});
    allUnlocks.push_back({assUnlocks::FIREwall_IN_THE_assHOLE,"FIREwall_IN_THE_assHOLE",3});
    allUnlocks.push_back({assUnlocks::ASSB_CKW3RDS,      "ASSB_CKW3RDS",                7});
    allUnlocks.push_back({assUnlocks::BACKD00Rd_UR_ASS,   "BACKD00Rd_UR_ASS",           7});
    allUnlocks.push_back({assUnlocks::PWND_Yur_ASS,      "PWND_Yur_ASS",                7});
    allUnlocks.push_back({assUnlocks::SHOVE_IT_UP_YUR,    "SH0VE_IT_UP_YUR",            10});
    allUnlocks.push_back({assUnlocks::MY_ASS_15_BETTER_THAN_YURS, "MY_ASS_15_BETTER_THAN_YURS", 10});
    allUnlocks.push_back({assUnlocks::TWO_FINGERS_BUT_WHOLE, "TWO_FINGERS_BUT_WHOLE",   15});
    allUnlocks.push_back({assUnlocks::I_L1K3_B1G,         "I_LIKE_B1G",                 15});

    allPats.push_back({assPatternEyes::NONE,                0,    1,    0,      assPatternCore::NONE,           0,     0x000000,     0x000000,     0x000000,   "NULL",               true});
    allPats.push_back({assPatternEyes::RED,                 0,    2,    14,     assPatternCore::COLOR,          0,     0xFF0000,     0x000000,     0x000000,   "redrum",                true});
    allPats.push_back({assPatternEyes::GREEN,               0,    3,    15,     assPatternCore::COLOR,          0,     0x00FF00,     0x000000,     0x000000,   "gang",              true});
    allPats.push_back({assPatternEyes::BLUE,                0,    4,    16,     assPatternCore::COLOR,          0,     0x0000FF,     0x000000,     0x000000,   "whale",               true});
    allPats.push_back({assPatternEyes::WHITE,               0,    5,    17,     assPatternCore::COLOR,          0,     0xFFFFFF,     0x000000,     0x000000,   "FFFFFF",              true});
    allPats.push_back({assPatternEyes::TEAL,                0,    6,    18,     assPatternCore::COLOR,          0,     0x00FFFF,     0x000000,     0x000000,   "shark",               true});
    allPats.push_back({assPatternEyes::PURPLE,              0,    7,    19,     assPatternCore::COLOR,          0,     0xFF00FF,     0x000000,     0x000000,   "power",             true});
    allPats.push_back({assPatternEyes::YELLOW,              0,    8,    20,     assPatternCore::COLOR,          0,     0xFFFF00,     0x000000,     0x000000,   "0xFFFF00",             true});

    allPats.push_back({assPatternEyes::BLINKRED,            1,    1,    21,     assPatternCore::BLINK,          250,   0xFF0000,     0x000000,     0x000000,   "BLINKy",           true});
    allPats.push_back({assPatternEyes::BLINKBLUE,           1,    2,    22,     assPatternCore::BLINK,          500,   0x00FF00,     0x000000,     0x000000,   "BLINKy BLUE",         true});
    allPats.push_back({assPatternEyes::BLINKORANGE,         1,    3,    23,     assPatternCore::BLINK,          750,  0xFF5000,     0x000000,     0x000000,   "ORANGE",          true});
    allPats.push_back({assPatternEyes::BLINKRW,             1,    4,    24,     assPatternCore::BLINK,          500,   0xFFFFFF,     0xFF0000,     0x000000,   "bling",         true});
    allPats.push_back({assPatternEyes::BLINKYG,             1,    5,    25,     assPatternCore::BLINK,          500,   0xFFFF00,     0x00FF00,     0x000000,   "bling 2",          true});
    allPats.push_back({assPatternEyes::BLINKPL,             1,    6,    26,     assPatternCore::BLINK,          750,   0xFF00FF,     0x90EE90,     0x000000,   "blink 50",        true});
    allPats.push_back({assPatternEyes::BLINKBW,             1,    7,    27,     assPatternCore::BLINK,          1000,  0xFFFFFF,     0x0000FF,     0x000000,   "error",        true});

    allPats.push_back({assPatternEyes::PULSEYELLOW,         2,    1,    28,     assPatternCore::PULSE,          5,     0xFFFF00,     0x000000,     0x000000,   "Yellow Submarine",           true});
    allPats.push_back({assPatternEyes::PULSETEAL,           2,    2,    29,     assPatternCore::PULSE,          10,    0x00FFFF,     0x000000,     0x000000,   "Teal Time",         true});
    allPats.push_back({assPatternEyes::PULSEPURPLE,         2,    3,    30,     assPatternCore::PULSE,          20,    0xFF00FF,     0x000000,     0x000000,   "PP",          true});
    allPats.push_back({assPatternEyes::PULSERED,            2,    4,    31,     assPatternCore::PULSE,          40,    0xFF0000,     0x000000,     0x000000,   "Red Alert",         true});
    allPats.push_back({assPatternEyes::PULSEDOR,            2,    5,    32,     assPatternCore::PULSED,         20,    0xFFA500,     0xFF0000,     0x000000,   "PO",          true});
    allPats.push_back({assPatternEyes::PULSEDGW,            2,    6,    33,     assPatternCore::PULSED,         20,    0x00FF00,     0xFFFFFF,     0x000000,   "Pulse GW",        true});
    allPats.push_back({assPatternEyes::PULSEBP,             2,    7,    34,     assPatternCore::PULSED,         20,    0x0000FF,     0xFF00FF,     0x000000,   "Pulse Blue Purp",        true});

    allPats.push_back({assPatternEyes::SPARKLEWHITE,        3,    1,    35,     assPatternCore::SPARKLE,        100,     0xFFFFFF,     0x000000,     0x000000,   "MrSparkles",         true});
    allPats.push_back({assPatternEyes::SPARKLERED,          3,    2,    36,     assPatternCore::SPARKLEONE,        50,     0xFF0000,     0x000000,     0x000000,   "Red Super Alert",       true});
    allPats.push_back({assPatternEyes::SPARKLELIME,         3,    3,    37,     assPatternCore::SPARKLETEN,        75,     0xFFFF00,     0x00FF00,     0x000000,   "Margarita Time",        true});
    allPats.push_back({assPatternEyes::SPARKLETEAL,         3,    4,    39,     assPatternCore::SPARKLE,        200,     0x00FFFF,     0x000000,     0x000000,   "Teal Terror",        true});
    allPats.push_back({assPatternEyes::SPARKLEPURPLE,       3,    5,    40,     assPatternCore::SPARKLEONE,        500,    0xFF00FF,     0x000000,     0x000000,   "Purple Person",      true});
    allPats.push_back({assPatternEyes::SPARKLEYELLOW,       3,    6,    41,     assPatternCore::SPARKLETEN,        50,    0x000000,     0xFFA500,     0x000000,   "I EAT ORANGE",      true});

    allPats.push_back({assPatternEyes::SCANRED,             4,    1,    88,      assPatternCore::SCAN,          60,    0xFFFFFF,     0xFF0000,     0x000000,   "SCAN 1",               true});
    allPats.push_back({assPatternEyes::SCANWHITE,           4,    2,    89,      assPatternCore::SCAN,          75,    0xFF0000,     0x000000,     0x000000,   "SCAN EVIL",               true});
    allPats.push_back({assPatternEyes::SCANBLUE,            4,    3,    90,      assPatternCore::SCAN,          90,    0x0050FF,     0x202000,     0x000000,   "SCANner2",               true});
    allPats.push_back({assPatternEyes::SCANLIME,            4,    4,    91,      assPatternCore::SCAN,          40,    0x90EE90,     0xFF00FF,     0x000000,   "IV",               true});
    
    allPats.push_back({assPatternEyes::CIRCLEWR,              5,    1,   48,     assPatternCore::CIRCLE,          100,   0xFFFFFF,     0xFF0000,     0x000000,   "Round and Round",             true});
    allPats.push_back({assPatternEyes::CHASERBW,              5,    2,    107,      assPatternCore::CHASER,         100,   0xFFFFFF,     0x0000FF,     0x000000,   "Chase Me",             true});
    allPats.push_back({assPatternEyes::CIRCLEYG,              5,    3,   878,     assPatternCore::CIRCLE,          200,   0xFFFF00,     0x0000FF,     0x000000,   "Circle 2",             true});
    allPats.push_back({assPatternEyes::CHASERWO,              5,    4,    151,      assPatternCore::CHASERTHREE,         200,   0xFFFF00,     0x303030,     0x000000,   "Chaser 3",             true});
    allPats.push_back({assPatternEyes::CIRCLERP,              5,    5,   481,     assPatternCore::CIRCLE,          50,   0xFF0000,     0xFF00FF,     0x000000,   "5",             true});
    allPats.push_back({assPatternEyes::CHASERFAST,              5,    6,    509,      assPatternCore::CHASERMINUS,         50,   0xFFA500,     0x000000,     0x000000,   "sixsixsix",             true});
    
    allPats.push_back({assPatternEyes::ONEBYHELLO,               6,    1,   111,     assPatternCore::ONEBY,          50,   0xFFFFFF,     0x000000,     0x000000,   "Hello World",              true});
    allPats.push_back({assPatternEyes::SNAKEPURP,               6,    2,    667,      assPatternCore::SNAKE,          60,   0xFF00FF,     0x000000,     0x000000,   "Purple Snake",              true});
    allPats.push_back({assPatternEyes::ONEBYPURP,               6,    3,   112,     assPatternCore::ONEBY,          30,   0x00FFFF,     0xFF2050,     0x000000,   "Hello Friend",              true});
    allPats.push_back({assPatternEyes::SNAKEGARD,               6,    4,    668,      assPatternCore::SNAKE,          30,   0x00FF00,     0x606060,     0x000000,   "Garden Snake",              true});
    allPats.push_back({assPatternEyes::ONEBYFROG,               6,    5,   113,     assPatternCore::ONEBY,          20,   0x00FF00,     0x000000,     0x000000,   "Hello Frog",              true});
    allPats.push_back({assPatternEyes::SNAKERATT,               6,    6,    669,      assPatternCore::SNAKE,          20,   0xFFF000,     0xFF0000,     0x000000,   "Rattler",              true});
   
    allPats.push_back({assPatternEyes::PINWHEELAM,            7,    1,   101,     assPatternCore::PINWHEEL,       200,   0xFF0000,     0xFFFFFF,     0x0000FF,   "America",           true});
    allPats.push_back({assPatternEyes::HYPNOTOAD,               7,    2,    81,      assPatternCore::HYPNO,          100,   0x00FFFF,     0xFF00FF,     0xFFFF00,   "HYPNOTOAD",              true});
    allPats.push_back({assPatternEyes::PINWHEELRGB,            7,    3,   102,     assPatternCore::PINWHEEL,       175,   0xFF0000,     0x00FF00,     0x0000FF,   "RGB",           true});
    allPats.push_back({assPatternEyes::HYPNOP,               7,    4,    82,      assPatternCore::HYPNOMINUS,          200,   0xFFFF00,     0x004040,     0x000000,   "Purple 3",              true});
    allPats.push_back({assPatternEyes::PINWHEELTHREE,            7,    5,   103,     assPatternCore::PINWHEELMINUS,       70,   0xFF0000,     0x707070,     0xFFFF00,   "404 Not Found",           true});

    allPats.push_back({assPatternEyes::DRIPGREEN,                8,    1,   471,     assPatternCore::DRIP,           300,   0x00FF00,     0x000000,     0x000000,   "Ooze",               true});
    allPats.push_back({assPatternEyes::FILLRANDOONE,           8,    2,   121,     assPatternCore::FILLRANDO,      200,   0xFFFFFF,     0xFF0000,     0x000000,   "fillup",          true});
    allPats.push_back({assPatternEyes::DRIPRW,                8,    3,   472,     assPatternCore::DRIP,           200,   0x000000,     0x00FFFF,     0x000000,   "YELLOW",               true});
    allPats.push_back({assPatternEyes::FILLRANDOTWO,           8,    4,   122,     assPatternCore::FILLRANDO,      150,   0xFF00FF,     0x00FF00,     0x000000,   "fill two",          true});
    allPats.push_back({assPatternEyes::DRIPPURP,                8,    5,   473,     assPatternCore::DRIP,           150,   0x00FFFF,     0xFFFF00,     0x000000,   "DRIP",               true});
    allPats.push_back({assPatternEyes::FILLRANDOTHREE,           8,    6,   123,     assPatternCore::FILLRANDO,      50,   0x000000,     0xFF0000,     0x000000,   "six",          true});
    
    allPats.push_back({assPatternEyes::FLAG,                9,    1,   46,     assPatternCore::FLAG,           400,   0x000000,     0x000000,     0x000000,   "Flag",               true});
    allPats.push_back({assPatternEyes::RAINBOW,             9,    2,    429,     assPatternCore::RAINBOW,        20,    0xFFFFFF,     0x000000,     0x000000,   "Rainbow Wheel",            true});
    allPats.push_back({assPatternEyes::RAINBOWRANDOM,       9,    3,    495,     assPatternCore::RAINBOWRANDOM,  200,   0xFFFFFF,     0x000000,     0x000000,   "asspixs",      true});
    allPats.push_back({assPatternEyes::RANDO,               9,    4,    496,     assPatternCore::RANDO,         200,   0xFFFFFF,     0x000000,     0x000000,   "hi",      true});
    allPats.push_back({assPatternEyes::FLAGFAST,                9,    5,   420,     assPatternCore::FLAG,           100,   0x000000,     0x000000,     0x000000,   "WavethatFlag",               true});
    allPats.push_back({assPatternEyes::RAINBOWFAST,         9,    6,    433,     assPatternCore::RAINBOW,        5,     0xFFFFFF,     0x000000,     0x000000,   "Vomit",        true});
    allPats.push_back({assPatternEyes::RAINBOWSLOW,         9,    7,    441,     assPatternCore::RAINBOW,        200,   0xFFFFFF,     0x000000,     0x000000,   "walker",        true});
    
}

void assFSM::init() {
    this->info = data->loadInfo();

    if (this->info.name == "NULL" || this->info.name.isEmpty() || this->info.name == "null") {
        debugln("NEED TO SET A NAME. EITHER INIT OR SOMETHING WENT flag{A55_UP}");
        setName();
        data->saveInfo(this->info);
    }

    debugln();
    debug("SWARM ID: ");
    debugln(this->info.name);  
    debugln();

    debug("SURVEILLANCE MODE ROUTINE: ");
    debugln(this->info.pattern);
    debugln();
   
    debugln("FLAGS CAPTURED:");
    for (const String& unlock : info.unlocks) {
        unlockThing(getUnlockFromName(unlock), true);
        debugln(unlock);
    }
    cleanSwarmNames();
    debugln();
    debugln("SWARM R.F.'s:");
    for (const String& name : info.swarm) debugln(name);

    countUp(102);
    setLevel();
    debugln();
    debugln("SWARM SWAGGER: " + String(getLevel()));
    debugln();

    setEyesInit(this->info.pattern);
    this->PATTERN_PREVIOUS = this->info.pattern;

    lora->updateDevice();
    this->BORED_TIME = millis() + this->GET_BORED;
    pixs->setPatternMouth(assPatternMouth::SPARKLE);

}

void assFSM::refresh() {
    unsigned long time = millis();

    if (time > this->BORED_TIME) {
        this->BORED_TIME = time + this->GET_BORED;
        if (random(3) == 2) {
            debugln("Sparkle time!");
            pixs->setPatternMouth(assPatternMouth::SPARKLE);
        } else {
            debugln("I need chapstick.");
            if (STATE_S == assStates::LORA) pixs->setPatternMouth(assPatternMouth::PULSELORA);
            else pixs->setPatternMouth(assPatternMouth::PULSEAUTON);
        }
        switch (random(6)) {
            case 0:
                debugln(118);
                wifi->saySomething("/login.php?user=root&password=p@ssword123!");
                //debugln("/login?user=admin&password=p@ssword123!");
                break;
            case 1:
                debugln(118);
                wifi->saySomething("/admin_console.php?search=I_LIKE_BIG_BUTTS");
                break;
            case 2:
                debugln(118);
                wifi->saySomething("/unlocks?flag=404_ASSnotFound");
                break;
            case 6:
                debugln(118);
                wifi->saySomething("/admin_console.php?reset=true");
                break;
            case 3:
                wifi->saySomething("/readme.html");
                //debugln("/admin/console/debug.php?cmd=tail+-f+splunkd.log");
                break;
            case 4:
                debugln(118);
                //wifi->saySomething("/SECUREASS/SYSTEM/CONSOLE/");
                wifi->saySomething("/unlocks?flag=404_ASSnotFound");
                break;
            case 5:
                debugln(118);
                //wifi->saySomething("/apiv2/server/info/?endpoint=localhost:8080");
                wifi->saySomething("/unlocks?flag=404_ASSnotFound");
                break;
            default:
                debugln(118);
                wifi->saySomething("/unlocks?flag=404_ASSnotFound");
                //debugln("SaySometing Default");
                break;
        }
        if (random(100) > 96) {
            debugln("");
            debugln("");
            debugln("flag{pika!pika!}");
            debugln("       \\:.             .:/"); 
            debugln("        \\``._________.''/ "); 
            debugln("         \\             / "); 
            debugln(" .--.--, / .':.   .':. \\"); 
            debugln("/__:  /  | '::' . '::' |"); 
            debugln("   / /   |`.   ._.   .'|"); 
            debugln("  / /    |.'         '.|"); 
            debugln(" /___-_-,|.\\  \\   /  /.|"); 
            debugln("      // |''\\.   ;,/ '|"); 
            debugln("      `==|:=         =:|"); 
            debugln("         `.          .'"); 
            debugln("           :-._____.-:"); 
            debugln("          `''       `''"); 
            debugln("");
            debugln("");
        }
    }

    if (this->PATTERN_PREVIOUS == this->info.pattern && !this->SAVE && time < this->SAVE_TIME)  
        return;

    this->SAVE_TIME = time + this->AUTOSAVE;

    cleanSwarmNames();
    setLevel();
    data->saveInfo(this->info);

    this->SAVE = false;
    this->PATTERN_PREVIOUS = this->info.pattern;
}

void assFSM::hello() {
    return;
    //this->BORED = false;
    //this->BORED_TIME = millis() + this->GET_BORED;
}

void assFSM::setState(assStateName state_name, assStates state) {
    switch (state_name) {
        case assStateName::STATE:
            STATE = state;
            break;
        case assStateName::STATE_S:
            if (state != STATE_S) {
                STATE_S = state;
                if (STATE_S == assStates::LORA) {
                    lora->updateState(assStates::KILLALLHUMANS);
                    setPatternEyes(PATTERN_EYE_SWARM, 0, -1);
                    pixs->setPatternMouth(assPatternMouth::PULSELORA);
                    break;
                }
                pixs->setPatternMouth(assPatternMouth::PULSEAUTON);
                lora->updateState(assStates::IDLE);
                setPatternEyes(PATTERN_EYE_SELECT, 0, -1);
            }
            break;
        case assStateName::STATE_A:
            if (state == assStates::PUSHED && STATE_S == assStates::WIFI) nextInLine(); 
            break;
        case assStateName::STATE_B:
            if (state == assStates::PUSHED && STATE_S == assStates::WIFI) nextCategory();
            break;
    }
}

bool assFSM::unlockThing(assUnlocks unlock, bool init) {
    
    if(!addUnlock(unlock) && !init) return false; 

    if (init) pixs->setPatternMouth(assPatternMouth::SPARKLE);

    bool return_me = !init;

    switch(unlock) {
        case assUnlocks::NONE:
            // Code for NONE
            return return_me;
            break;
        case assUnlocks::INIT:
            // Code for INIT
            return return_me;
            break;
        case assUnlocks::RECEIVED_UNLOCK:
            //unlockedPatternsEyes.push_back(assPatternEyes::RECEIVED_UNLOCK);
            return return_me;
            break;
        case assUnlocks::RECEIVED_HELLO:
            //unlockedPatternsEyes.push_back(assPatternEyes::RECEIVED_HELLO);
            return return_me;
            break;
        case assUnlocks::BOOBS:
            // Code for BOOBS
            return return_me;
            break;
        case assUnlocks::HACKTHEPLANET:
            // Code for HACKTHEPLANET
            return return_me;
            break;
        case assUnlocks::KILLALLHUMANS:
            // Code for KILLALLHUMANS
            return return_me;
            break;
        default:
            return return_me;
    }
    return false;
}

int assFSM::countUp(int up) { 
    if (this->info.count > 9999 || this->info.count < 0) this->info.count = 0;
    this->info.count += up;
    //debugln("Count: " + String(this->info.count));
    return this->info.count;
}

void assFSM::setLevel() {
    double level = 0.0;

    level += this->LEVEL_INIT;

    level += sumUnlockValues();

    int swarmSize = sumSwarmNames();
    double swarmLevel = 0;
    if (swarmSize > 2) swarmLevel += 5;
    if (swarmSize > 3) swarmLevel += 3;
    if (swarmSize > 4) swarmLevel += 2;
    if (swarmSize > 5) swarmLevel += 1;
    if (swarmSize > 7) swarmLevel += .5 * std::min(swarmSize - 4, 10);
    if (swarmSize > 16) swarmLevel += 0.2 * std::min(swarmSize - 14, 10);
    if (swarmSize > 30) swarmLevel += 0.1 * (swarmSize - 24);
    level += swarmLevel;

    if (level >= 1337.1) level = 1337; 

    double wholeNumberPart = int(level);

    double fractional = level - wholeNumberPart;

    double digit = 0;

    if (info.name.length() > 5 && isDigit(info.name[5]))
        digit = 0.01 * (info.name[5] - '0');

    level = wholeNumberPart + fractional + digit;

    /*
    // Add value for time
    double mil = 1.38889e-9 * millis();
    if (mil >= 0.01) mil = 0.009999999;
    level += mil;
    */

    double count = double(countUp()) / 1000000;
    level += count; 

    this->LEVEL = level;
    //debugln("Swagger: " + String(level, 6));
}


double assFSM::getLevel(bool set) { 
    if (set) setLevel();
    return this->LEVEL;
}

// Check if the unlock is present in the info.unlocks vector
bool assFSM::isUnlocked(assUnlocks unlock) {
  String name = getNameFromUnlock(unlock);
  return std::find(info.unlocks.begin(), info.unlocks.end(), name) != info.unlocks.end();
}

// Get the name of the unlock
String assFSM::getNameFromUnlock(assUnlocks unlock) {
  for (const auto& u : allUnlocks) {
    if (u.unlock == unlock) {
      return u.name;
    }
  }
  return ""; // Return empty string if not found
}

// Get the value of the unlock
int assFSM::getValueFromUnlock(assUnlocks unlock) {
  for (const auto& u : allUnlocks) {
    if (u.unlock == unlock) {
      return u.value;
    }
  }
  return -1; // Return -1 if not found
}

// Get the unlock from its name
assUnlocks assFSM::getUnlockFromName(String name) {
  for (const auto& u : allUnlocks) {
    if (u.name == name) {
      return u.unlock;
    }
  }
  return assUnlocks::NONE; // Return NONE if not found
}

// Add an unlock to the info.unlocks vector
bool assFSM::addUnlock(assUnlocks unlock) {
  if (!isUnlocked(unlock)) { // Only add the unlock if it's not already present
    info.unlocks.push_back(getNameFromUnlock(unlock));
    setLevel();
    this->SAVE = true;
    //talk(assMouthTalk::UNLOCK);
    pixs->setPatternMouth(assPatternMouth::SPARKLE);
    return true;
  }
  return false;
}

// Remove an unlock from the info.unlocks vector
void assFSM::removeUnlock(assUnlocks unlock) {
  String name = getNameFromUnlock(unlock);
  auto it = std::find(info.unlocks.begin(), info.unlocks.end(), name);
  if (it != info.unlocks.end()) { // Only erase the unlock if it's present
    info.unlocks.erase(it);
  }
}

int assFSM::sumUnlockValues() {
  int sum = 0;
  for (const String& unlockName : info.unlocks) {
    assUnlocks unlockEnum = getUnlockFromName(unlockName);
    int unlockValue = getValueFromUnlock(unlockEnum);
    if (unlockValue != -1) { // -1 signifies that the unlock wasn't found in allUnlocks
      sum += unlockValue;
    }
  }
  return sum;
}

int assFSM::getUnlockedCount() {
    int count = -1;
    for (const String& unlockName : info.unlocks)
        if (getValueFromUnlock(getUnlockFromName(unlockName)) != -1) count++;
        
    return count;
}

bool assFSM::addSwarmName(const String& name) {
    //debugln("Adding to list: " + name);
    if (!isValidName(name)) return false;
    for (const String& existingName : info.swarm)
        if (existingName == name) return false;  // The name is already in the list.
    //debugln("Adding to list because it's new: " + name);
    info.swarm.push_back(name);
    this->SAVE = true;
    setLevel();
    pixs->setPatternMouth(assPatternMouth::SPARKLE);
    //talk(assMouthTalk::NEWFRIEND);
    return true;
}

int assFSM::sumSwarmNames() {
  return info.swarm.size();
}

void assFSM::cleanSwarmNames() {
  std::vector<String> cleanedSwarm;
  for (const String& name : info.swarm) {
    if (!isValidName(name)) {
        //debugln("Invalid name: " + name);
        continue;  // Skip invalid names.
    }
    //debugln("Valid name: " + name);
    bool isDuplicate = false;
    for (const String& existingName : cleanedSwarm) {
      if (existingName == name) {
        isDuplicate = true;
        break;
      }
    }
    if (!isDuplicate) cleanedSwarm.push_back(name);
  }
  info.swarm = cleanedSwarm;
}

bool assFSM::isValidName(const String& name) {
  if (name.length() != 7) return false;
  for (int i = 0; i < 3; ++i) if (!isAlpha(name[i]) ||  !(name[i] >= 'A' && name[i] <= 'Z')) return false;
  if (name[3] != '-') return false;
  for (int i = 4; i < 7; ++i) if (!isDigit(name[i])) return false;
  return true;
}

bool assFSM::getMode() {
    if (STATE_S == assStates::LORA) return false;
    return true;
}

void assFSM::setFriend(const char* new_friend) {
    strncpy(FRIEND, new_friend, sizeof(FRIEND));
    FRIEND[sizeof(FRIEND) - 1] = '\0'; // ensure null-termination
}

int assFSM::getPatInt(assPatternEyes pat) {
    for (const auto& p : allPats)
        if (p.patName == pat) return p.uniqueID;
    return 0;
}

String assFSM::getCurrentPatternName() {
    for (const auto& p : allPats)
        if (p.patName == PATTERN_EYE_CURRENT) return p.name;
    return "NONE";
}

int assFSM::getPatIndexCat(assPatternEyes pat) {
    for (const auto& p : allPats)
        if (p.patName == pat) return p.category;
    return 0;
}

int assFSM::getPatIndexPlace(assPatternEyes pat) {
    for (const auto& p : allPats)
        if (p.patName == pat) return p.place_in_line;
    return 0;
}

assPatternEyes assFSM::getPatEnum(int num) {
    for (const auto& p : allPats)
        if (p.uniqueID == num) return p.patName;
    return assPatternEyes::NONE;
}

assPatternEyes assFSM::getPatEnumFromNums(int cat, int place) {
    for (const auto& p : allPats)
        if (p.category == cat && p.place_in_line == place) return p.patName;
    return assPatternEyes::NONE;
}

int assFSM::getPatternState() { return pixs->getPatternState(); };

int assFSM::getPatternTime() { return pixs->getPatternTime(); };

void assFSM::setPatternMouth(assPatternMouth pattern) { pixs->setPatternMouth(pattern); };

void assFSM::talk(assMouthTalk talk) { pixs->talk(talk); }

void assFSM::setCurrentEyePattern(assPatternEyes pattern, int time, int state, bool noupdate) {
    for (const auto& p : allPats) {
        if (p.patName == pattern) {
            if (p.patName != this->PATTERN_EYE_CURRENT) debugln("Setting SURVEILLANCE MODE ROUTINE to: " + p.name);
            pixs->setCurrentEyePattern(p.patCore, p.color, p.diff, time, state, noupdate, p.colorOff, p.color3);
            return;         
        }
    }
}

void assFSM::setEyesInit(int pattern) {
    PATTERN_EYE_CURRENT = getPatEnum(pattern);
    PATTERN_EYE_SELECT = PATTERN_EYE_CURRENT;    
    PATTERN_EYE_SWARM = PATTERN_EYE_CURRENT;    


    /*
    auto it = std::find(unlockedPatternsEyes.begin(), unlockedPatternsEyes.end(), PATTERN_EYE_CURRENT);
    if(it != unlockedPatternsEyes.end())
        PATTERN_EYE_INDEX = std::distance(unlockedPatternsEyes.begin(), it);
    */
    setCurrentEyePattern(PATTERN_EYE_CURRENT, 0, true);
}

void assFSM::setPatternEyes(assPatternEyes pattern, int num, int state, bool noupdate) {
    PATTERN_EYE_CURRENT = pattern;
  
    /*
    // Update the PATTERN_EYE_INDEX
    auto it = std::find(unlockedPatternsEyes.begin(), unlockedPatternsEyes.end(), pattern);
    if(it != unlockedPatternsEyes.end())
        PATTERN_EYE_INDEX = std::distance(unlockedPatternsEyes.begin(), it);
    */
  
    if (getMode()) {
        PATTERN_EYE_SELECT = PATTERN_EYE_CURRENT;
        this->info.pattern = getPatInt(PATTERN_EYE_SELECT);
    } else {
        PATTERN_EYE_SWARM = PATTERN_EYE_CURRENT;
    }
    // Update the pixs with the new pattern
    setCurrentEyePattern(PATTERN_EYE_CURRENT, num, state, noupdate);
}

void assFSM::nextCategory() {
    //debugln("next category");
    if (getMode()) {
        int cat = getPatIndexCat(PATTERN_EYE_SELECT) + 1;
        if (cat > this->MAX_CAT) cat = 0;
        //debugln(String(cat));
        
        for (const auto& p : allPats) {
            //debug(".");
            if (p.category == cat && p.place_in_line == 1) {
                PATTERN_EYE_SELECT = p.patName;
                //debugln("found it");
                break;
            }
        }

        PATTERN_EYE_CURRENT = PATTERN_EYE_SELECT;
        this->info.pattern = getPatInt(PATTERN_EYE_CURRENT);

        setCurrentEyePattern(PATTERN_EYE_CURRENT, 0, -1);
        pixs->setPatternMouth(assPatternMouth::BLINK);
    }
}

bool assFSM::setPatternWeb(String id) {
    if (getMode()) {
        int uniqueID = id.toInt();
        for (auto &p : allPats) {
            if (p.uniqueID == uniqueID) {
                if (p.unlocked) {
                    PATTERN_EYE_SELECT = getPatEnum(id.toInt());
                    PATTERN_EYE_CURRENT = PATTERN_EYE_SELECT;
                    this->info.pattern = getPatInt(PATTERN_EYE_CURRENT);
                    setCurrentEyePattern(PATTERN_EYE_CURRENT, 0, -1);
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

void assFSM::nextInLine() {
    //debugln("next in line");
    if (getMode()) {
        int cat = getPatIndexCat(PATTERN_EYE_SELECT);
        //debugln(String(cat));
        int line = getPatIndexPlace(PATTERN_EYE_SELECT) + 1; 
        if (line > this->MAX_LINE[cat]) line = 1;
        //debugln(String(line));

        bool found = false;
        while (!found) {
            for (auto &p : allPats) {
                if (p.category == cat && p.place_in_line == line) {
                    if (p.unlocked) {
                        PATTERN_EYE_SELECT = p.patName;
                        found = true;
                        break;
                    } else {
                        line++;
                        if (line > this->MAX_LINE[cat]) line = 1;
                        break;
                    }
                }
            }
        }

        PATTERN_EYE_CURRENT = PATTERN_EYE_SELECT;
        this->info.pattern = getPatInt(PATTERN_EYE_CURRENT);

        setCurrentEyePattern(PATTERN_EYE_CURRENT, 0, -1);
        pixs->setPatternMouth(assPatternMouth::BLINK);
    }
}

/*
void assFSM::nextPatternEyes() {
    if (getMode()) {
        PATTERN_EYE_INDEX++;
        if (PATTERN_EYE_INDEX >= unlockedPatternsEyes.size()) {
            PATTERN_EYE_INDEX = 0;
        }
        PATTERN_EYE_CURRENT = unlockedPatternsEyes[PATTERN_EYE_INDEX];
        PATTERN_EYE_SELECT = PATTERN_EYE_CURRENT;
        this->info.pattern = getPatInt(PATTERN_EYE_SELECT);

        // Update the pixs with the new pattern
        setCurrentEyePattern(PATTERN_EYE_CURRENT, 0, -1);
        pixs->setPatternMouth(assPatternMouth::LEFT);
    }
}

void assFSM::previousPatternEyes() {
    if (getMode()) {
        PATTERN_EYE_INDEX--;
        if (PATTERN_EYE_INDEX < 0) {
            PATTERN_EYE_INDEX = unlockedPatternsEyes.size() - 1;
        }
        PATTERN_EYE_CURRENT = unlockedPatternsEyes[PATTERN_EYE_INDEX];
        PATTERN_EYE_SELECT = PATTERN_EYE_CURRENT;
        this->info.pattern = getPatInt(PATTERN_EYE_SELECT);

        // Update the pixs with the new pattern
        setCurrentEyePattern(PATTERN_EYE_CURRENT, 0, -1);
        pixs->setPatternMouth(assPatternMouth::RIGHT);
    }
}
*/

void assFSM::leadChange(int pat, int time, int state, bool noupdate) {
    //debugln("Performing lead update");
    PATTERN_EYE_SWARM = getPatEnum(pat);
    if (STATE_S == assStates::LORA) { 
        PATTERN_EYE_CURRENT = PATTERN_EYE_SWARM;
        setPatternEyes(PATTERN_EYE_CURRENT, time, state, noupdate);
    }
} 

void assFSM::setName(bool ran) {
    String name = "ASS";

    // Generate three random digits
    int num1 = random(10);
    int num2 = random(10);
    int num3 = random(10);
    String nums = "-" + String(num1) + String(num2) + String(num3);
 
    if (ran) {
        // Array of banned acronyms
        String banned_acronyms[] = {"KKK", "SSS", "XXX", "ABC", "XYZ", "ZZZ", "KTB", "KOK", "DIK", "CIA", "FBI", "DEA", "ICE", "FAG", "GAY", "FTP", "SSH", "BIG", "FAT", "KUK", "TIT"};
        int num_banned = sizeof(banned_acronyms) / sizeof(banned_acronyms[0]);

        while(true) {
            // Generate three random capital letters
            char letter1 = random(26) + 65; // ASCII values of A-Z are 65-90
            char letter2 = random(26) + 65;
            char letter3 = random(26) + 65;

            // Construct the new name
            name = String(letter1) + String(letter2) + String(letter3) + "-" + String(num1) + String(num2) + String(num3);

            // Check against banned acronyms
            bool is_banned = false;
            for(int i = 0; i < num_banned; i++) {
                if(name.startsWith(banned_acronyms[i])) {
                    is_banned = true;
                    break;
                }
            }

            if(!is_banned) break;
        }
        //debugln("Random name: " + name);
    } else {
        String approved_acronyms[] = {
            "XXX","ABC","XYZ","ZZZ","AAA","FBI","CIA","DUI","ASS","DIK","BUT","FTP","SSH","DOG","CAT","BIG","TIT","KTB","BUG","POP","SYN","ACK","RDP","PDF","DEA","ICE",
            "FED","COP","POO","SPL","DEF","CON","ONE","TWO","SIX","TCP","UDP","HHV","LOL","PWN","NOT","AND","XOR","GET","FUK","YOU","LAS","GOD","DAD","MOM"
        };
        name = approved_acronyms[random(48)] + nums;
    }

    debugln("HENCE FORTH YOU ARE KNOW AS: " + name);

    // Set the new name
    this->info.name = name;
}

String assFSM::getFile(const char* path) {
    return data->read(path);
}


String* assFSM::getPatternInfo() {
    String* patterns = new String[200];
    int i = -1;
    for (const auto& p : allPats) {
        patterns[++i] = p.category;
        if (p.unlocked) {
            patterns[++i] = p.uniqueID;
            patterns[++i] = p.name;
        } else {
            patterns[++i] = "1337";
            patterns[++i] = "REDACTED";
        }
    }
    patterns[++i] = "END";
    return patterns;
}
