#include "assG.h"
#include "assFSM.h"
#include "assWifi.h"
#include "assHTML.h"
#include <Regexp.h>

assWifi::assWifi() : _isApRunning(false), _server(80), controller(nullptr) {}

void assWifi::setController(assFSM* controller) {
  this->controller = controller;
}

void assWifi::startWifi(const String& ssid) {
  if (!_isApRunning) {
    WiFi.softAP(ssid.c_str());

    _server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleRoot(request); });
    _server.on("/style_root.css", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleStyle(request); });
    _server.on("/style_home.css", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleHomeStyle(request); });
    _server.on("/script_home.js", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleHomeScript(request); });
    _server.on("/unlock", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleUnlock(request); });
    _server.on("/readme", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleReadMe(request); });
    _server.on("/console", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleIndex(request); });
    _server.on("/robots.txt", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleRobots(request); });
    _server.on("/pattern", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handlePattern(request); });
    _server.on("/capture", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleFlag(request); });
    _server.on("/bff", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleBFF(request); });
    _server.on("/login", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleLoginGET(request); });
    _server.on("/login", HTTP_POST, [this](AsyncWebServerRequest *request){ this->handleLoginPOST(request); });
    _server.on("/admin.php", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleADMIN(request); });
    _server.on("/search", HTTP_POST, [this](AsyncWebServerRequest *request){ this->handleSearchPost(request); });

    _server.on("/submit", HTTP_GET, [this](AsyncWebServerRequest *request){ this->handleSubmit(request); });
    _server.on("/submit", HTTP_POST, [this](AsyncWebServerRequest *request){ this->handleSubmitPost(request); });
    
    _server.onNotFound([](AsyncWebServerRequest *request){ request->send(404, "text/html", "Try Harder");});

    _isApRunning = true;

    _server.begin();

  }
}

void assWifi::stopWifi() {
  WiFi.softAPdisconnect(true);
  _server.end();
  _isApRunning = false;
}

bool assWifi::getApRunningStatus() const {
  return _isApRunning;
}

void assWifi::saySomething(const String& param) {
  HTTPClient http; //Need to make it scoped to saySomething or guru meditation crashes... Idk wtf it's doing.
  if (http.begin("http://192.168.4.1" + param)) http.GET();
  //controller->talk(assMouthTalk::WIFI_200POST); //=> for some fucking reason right before code cutoff it fucking started cauing it to fucking crash each time...
}

void assWifi::handleRoot(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  request->send(200, "text/html", rootHTML);
}

void assWifi::handleRobots(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  request->send(200, "text/plain", robots);
}

void assWifi::handleIndex(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  request->send(200, "text/html", generateHome());
  //controller->unlockThing(assUnlocks::RECEIVED_HELLO);
}

void assWifi::handleReadMe(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  request->send(200, "text/html",  String(headerHomeHTML) + String(readmeHTML) + String(footerHTML));
}

void assWifi::handleUnlock(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  if (controller->unlockThing(assUnlocks::RECEIVED_UNLOCK)) request->send(200, "text/plain", "Pattern unlocked");
  else request->send(200, "text/plain", "Fail. Try harder");
}

void assWifi::handleSubmit(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  if(request->hasParam("text")) request->send(200, "text/plain", "Text received: " + request->getParam("text")->value());
  else request->send(200, "text/html", String(headerHomeHTML) + String(submitGETHTML) + String(footerHTML));
}

void assWifi::handleLoginGET(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);

  String html = String(headerHomeHTML);
  html += "<form method=\"post\">"
                  "Username:<br>"
                  "<input type=\"text\" name=\"username\">"
                  "<br>"
                  "Password:<br>"
                  "<input type=\"password\" name=\"password\">"
                  "<br><br>"
                  "<input type=\"submit\" value=\"Submit\">"
                "</form>";
  html += String(footerHTML);
  request->send(200, "text/html", html);
}

void assWifi::handleLoginPOST(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);

  if(request->hasParam("username", true) && request->hasParam("password", true)) {
    String username = request->getParam("username", true)->value();
    String password = request->getParam("password", true)->value();

    if (password == "password") {
      request->send(401, "text/plain", "Error: we change dit from password");
      return;
    }

    if (password != "changeme" && username != "admin") {
      request->send(401, "text/plain", "Error: User does not exist");
      return;
    }

    if(username != "admin") {
      request->send(401, "text/plain", "Error: Wrong user");
    }

    if(password != "changeme") {
      request->send(401, "text/plain", "Error: Wrong password");
    }

    if (password == "changeme" && username == "admin") {
      AsyncWebServerResponse *response = request->beginResponse(303, "text/plain", "flag{CHANGEMYDIAPER}");
      response->addHeader("Set-Cookie", "sessionID=drxpsdzbkdsbyzkcdsyxckbebkki; SameSite=Lax");
      response->addHeader("Set-Cookie", "user=1337;");
      response->addHeader("Location", "/admin.php?user=1337");
      request->send(response);
    }
  }
}

void assWifi::handleADMIN(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);

  if (!request->hasHeader("Cookie")) {
    AsyncWebServerResponse *response = request->beginResponse(303);
    response->addHeader("Location", "/tryharder");
    request->send(response);
  }
  
  String user_response = "NULL";

  String cookieHeader = request->header("Cookie");
  int cookieStart = cookieHeader.indexOf("sessionID=");
  int cookieEnd = cookieHeader.indexOf(';', cookieStart);
  if (cookieEnd < 0) cookieEnd = cookieHeader.length();
  String cookie = cookieHeader.substring(cookieStart + String("sessionID=").length(), cookieEnd);

  if (cookie.length() == String("drxpsdzbkdsbyzkcdsyxckbebkki").length()) {

    if (cookie == "drxpsdzbkdsbyzkcdsyxckbebkki") {
      AsyncWebServerResponse *response = request->beginResponse(200);
      response->addHeader("Set-Cookie", "sessionID=drxpsdzbkdsbyzkcdsyxckbebkki; SameSite=Lax");
      response->addHeader("Set-Cookie", "user=1337;");

      String user_response = "NULL";
      if (request->hasParam("user")) {
        String user = request->getParam("user")->value();
        if (user == "1337") user_response = "1337 h@x0r";
        else if (user == "1") user_response = "SECURE A.S.S. SYSTEM ADMIN";
        else if (user == "2") user_response = "admin";
        else user_response = "flag{I_IDOR_YUR_ASS}";
      }

      String html = "";
      html += String(headerHomeHTML);
      html += "<h1>WELCOME <b>" + user_response + "</b>.</h1>";
      html += "<form action=\"/search\" method=\"post\">"
              "SEARCH:"
              "<input type=\"text\" name=\"search\">"
              "<input type=\"submit\" value=\"Submit\">"
              "</form>";
      html += String(footerHTML);

      request->send(200, "text/html", html);
      return;
    }
    request->send(200, "text/plain", "Bad sessionID generation. flag{U_CH@N3D_ME}");
    return;
  }

  AsyncWebServerResponse *response = request->beginResponse(303);
  response->addHeader("Location", "/tryharder");
  request->send(response);
  
}

int assWifi::isBadANSI(String input) {
    String patterns[20] = {"\x1b","\x1B", "\u001b", "\033", "\x9", "\x8", "\x1b[31m", "\x1b[0m","\\x1b", "\\u001b", "\\033", "\\x9", "\\x8", "\\x1b[31m", "\\x1b[0m"};
    int count = 0;

    for (int i = 0; i < 20; i++) {
        MatchState ms;
        ms.Target((char *)input.c_str());
        count += ms.MatchCount((char *)patterns[i].c_str());
    }

    // Return the number of matched patterns
    return count;

  }

int assWifi::isBadSQL(String input) {
    String patterns[20] = {"DROP", "TABLE", "UNION","SELECT", "OR '1'='1'"};
    int count = 0;

    for (int i = 0; i < 20; i++) {
        MatchState ms;
        ms.Target((char *)input.c_str());
        count += ms.MatchCount((char *)patterns[i].c_str());
    }

    // Return the number of matched patterns
    return count;
}

void assWifi::handleSearchPost(AsyncWebServerRequest *request) {
  if(request->hasParam("search", true)) {  // true, true checks for POST and from a form
    String search = request->getParam("search", true)->value();  // true, true checks for POST and from a form
    if (isBadSQL(search) > 2) {
      request->send(200, "text/html", "flag{ASSQLinj3ti0n}");
      return;
    }
  }
  request->send(200, "text/html", "ERROR: search failed. See job diag for more information.");
}

void assWifi::handlePattern(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200POST);
  controller->hello();
  if(request->hasParam("id")) {
    String id = request->getParam("id")->value();
    debugln("SURVEILLANCE MODE ROUTINE id : ");
    debugln(id);
    if (isBadANSI(id) > 1) debugln("flag{ASSni_l0g_injection}");
    bool setPat = controller->setPatternWeb(id);
    if (setPat) request->send(200, "text/plain", "Set SURVEILLANCE MODE ROUTINE to id: " + id);
    else request->send(500, "text/plain", "Failed to set SURVEILLANCE MODE ROUTINE. Can you count? Is it in AUTON MODE?");
  } else request->send(500, "text/plain", "wat?");
}

void assWifi::handleFlag(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200POST);
  controller->hello();
  if(request->hasParam("flag")) {
    String flag = request->getParam("flag")->value();
    assUnlocks unlock = controller->getUnlockFromName(flag);
    if (unlock != assUnlocks::NONE) {
      if (controller->addUnlock(unlock)) {
        request->send(200, "text/plain", "GET PSYCHED!!! Captured flag " + flag + " for " + controller->getValueFromUnlock(unlock) + " SWAGGER." ); 
      } else request->send(500, "text/plain", "FLAG " + flag + " already captured for " + controller->getValueFromUnlock(unlock) + " SWAGGER."); 
    } else request->send(500, "text/plain", "BAD FLAG. TRY HARDER");
  } else request->send(500, "text/plain", "wat?");
}

bool assWifi::containsXSS(String input) {
  input.toLowerCase();
  int count = 0;

  if (input.indexOf("<") != -1) count++;
  if (input.indexOf(">") != -1) count++;
  if (input.indexOf("\"") != -1) count++;
  if (input.indexOf("script") != -1) count++;
  if (input.indexOf("alert") != -1) count++;
  if (input.indexOf("prompt") != -1) count += 2;
  if (input.indexOf(";") != -1) count++;

  if (count > 2) return true;
  return false;
}

void assWifi::handleBFF(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200POST);
  controller->hello();
  if(request->hasParam("bff")) {
    String bff = request->getParam("bff")->value();
    this->BEST_FRIEND = bff;
    debugln("YOUR NEW EXTERMINATION TARGET: " + bff);
    String flag = "";
    if (containsXSS(bff)) flag = "<p>flag{FRIENDLY_XSS}</p>";
    request->send(200, "text/html", "<p>I have a new friend named " + bff + "!</p>" + flag ); 
  } else request->send(500, "text/plain", "wat? you have no friends");
}

void assWifi::handleSubmitPost(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200POST);
  controller->hello();
  if(request->hasParam("text", true, true)) request->send(200, "text/plain", "Text received: " + request->getParam("text", true, true)->value());
  else request->send(200, "text/plain", "...");
}

void assWifi::handleHomeScript(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  request->send(200, "application/javascript", "alert(\"Try Harder\");");
}

void assWifi::handleStyle(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  request->send(200, "text/css", styleRootCSS);
}

void assWifi::handleHomeStyle(AsyncWebServerRequest *request) {
  controller->talk(assMouthTalk::WIFI_200);
  controller->hello();
  request->send(200, "text/css", styleHomeCSS);
}



String assWifi::generateHome() {
  String home = "";
  home += String(headerHomeHTML);
  home += generateInfo();
  home += "<div class=\"Flags\"><h2>Submit a Flag</h2><form action=\"/capture\" method=\"GET\"><input type=\"text\" id=\"flagInput\" name=\"flag\"><button type=\"submit\">Submit</button></form></div>&nbsp;&nbsp;";
  home += generatePatterns();
  home += String(footerHTML);
  return home;
}

String assWifi::generateInfo() {
  String info = "<div class=\"Info\"><h2>Info</h2>";
  info += "<p><b>A.S.S. R.F. ID:</b> " + controller->getName() +  "</p>";
  info += "<p><b>SWARM SWAGGER:</b> " + String(controller->getLevel()) +  "</p>";
  info += "<p><b>A.S.S. MATES SEEN:</b> " + String(controller->sumSwarmNames()) +  "</p>";
  info += "<p><b>FLAGS CAPTURED:</b> " + String(controller->getUnlockedCount()) +  "/" + String(random(42)) + "</p>";
  info += "<p><b>ACTIVE SURVEILLANCE MODE ROUTINE:</b> "+ String(controller->getCurrentPatternName()) + " </p>";
  info += "<p><b>QUOTE OF THE DAY:</b> when you assume... cde88cee93335a33bd022d9d7e5d3760 </p>";
  info += "<p><b>R.T.X.T - HUMAN INTERACTION CONTROL SCHEME:</b> <p style=\"visibility:hidden;\"> ERROR: ROBOTS TRANSCLUSIVE XENOMORPHIC TRANSCRIPTOR's code not found. See readme for code info.</p>";
  info += "<p><b>BEST FRIEND:</b> " + BEST_FRIEND + " </p>";
  info += "<div><p><b>ADD A BEST FRIEND:</b> <form action=\"/bff\" method=\"GET\"><input type=\"text\" id=\"friendInput\" name=\"bff\"><button type=\"submit\">Submit</button></form></p> </div>";
  info += "</div>&nbsp;&nbsp;";
  return info;
}

String assWifi::generatePatterns() {
  String info = "<script>function showPatterns(id){var contents=document.getElementsByClassName(\"patterns\");for(var i=0;i<contents.length;i+=1){if(contents[i].id===id){contents[i].style.display=\"block\"}else{contents[i].style.display=\"none\"}}}</script>"
                "<div class=\"Patterns\"><h2>Execute SURVEILLANCE MODE ROUTINE</h2><div>"
                "<a href=\"#\" onclick=\"showPatterns(\'color\')\"><b>Colors</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'blinky\')\"><b>Blinky</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'pulse\')\"><b>Pulse</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'sparkle\')\"><b>MrSparkles</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'scanner\')\"><b>FACIAL ID</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'chaser\')\"><b>Circles</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'snake\')\"><b>Snake</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'hypno\')\"><b>Hypno Toad</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'fill\')\"><b>Drips</b></a>  "
                "<a href=\"#\" onclick=\"showPatterns(\'rainbow\')\"><b>rainbows and butterflies</b></a>  "
                "</div>&nbsp;<div>";

  String Colors = "<div id=\"color\" class=\"patterns\">";
  String Blinky = "<div id=\"blinky\" class=\"patterns\">";
  String Pulse = "<div id=\"pulse\" class=\"patterns\">";
  String Sparkle = " <div id=\"sparkle\" class=\"patterns\">";
  String Scan = "<div id=\"scanner\" class=\"patterns\">";
  String Chaser = "<div id=\"chaser\" class=\"patterns\">";
  String Snake = "<div id=\"snake\" class=\"patterns\">";
  String Hypno = "<div id=\"hypno\" class=\"patterns\">";
  String Drip = "<div id=\"fill\" class=\"patterns\">";
  String Rainbow = "<div id=\"rainbow\" class=\"patterns\">";

  String* patterns = controller->getPatternInfo();
  for (int i = 0; i < 200;) {
    if(patterns[i] == "END" || patterns[i + 1] == "END" || patterns[i + 2] == "END") break;
    else if (patterns[i] == "0") Colors += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "1") Blinky += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "2") Pulse += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "3") Sparkle += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "4") Scan += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "5") Chaser += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "6") Snake += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "7") Hypno += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "8") Drip += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    else if (patterns[i] == "9") Rainbow += "<div><a href=\"/pattern?id=" + patterns[++i] + "\">" + patterns[++i] + "</a></div>";
    i++;
  }

  String div = "</div>";
  Colors += div;
  Blinky += div;
  Pulse += div;
  Sparkle += div;
  Scan += div;
  Chaser += div;
  Snake += div;
  Hypno += div;
  Drip += div;
  Rainbow += div;
  info = info + Colors + Blinky + Pulse + Sparkle  + Scan + Chaser + Snake + Hypno + Drip + Rainbow + div + div;
  info += "&nbsp;&nbsp;<script>showPatterns(\'none\');</script>";

  return info;
}