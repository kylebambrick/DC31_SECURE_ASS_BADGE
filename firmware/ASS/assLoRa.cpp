#include "assLoRa.h"
#include "assFSM.h"

assLoRa::assLoRa() : controller(nullptr) {
    this->thisDevice.name = "null";
    this->thisDevice.powerlevel = 0.42;
    this->thisDevice.lastupdatebyme = -1;
    this->thisDevice.pattern = 0;
    this->thisDevice.patternState = 0;
    this->thisDevice.patternTime = 0;
    this->thisDevice.stamp = 1337;
    this->STATE = assStates::IDLE;
}

void assLoRa::setController(assFSM* controller) {
    this->controller = controller;
}

void assLoRa::init() {

  for(int i = 0; i < 3; i++) {
    Device emptyDevice;
    deviceList[i] = emptyDevice;
  }

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  if (!LoRa.begin(915E6)) {
    //debugln(".");
    delay(500);
  }
}

void assLoRa::update() {
  receiveData();
  updateStuff();
  if (this->STATE == assStates::KILLALLHUMANS) 
    sendData();
}

void assLoRa::receiveData() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    ////debug("Received packet: ");
    String message = "";

    // read packet
    while (LoRa.available()) {
      char receivedChar = (char)LoRa.read();
      message += receivedChar;
      ////debug(receivedChar);
    }
    ////debugln(); // new line after printing entire message

    // Parse the received data
    parseData(message);

    // print RSSI of packet
    ////debug("with RSSI ");
    ////debugln(LoRa.packetRssi());
  }
}

void assLoRa::sendData() {
    unsigned long time = millis();
    if (time >= this->LAST_TRANSMIT) {
        //debugln("Time to send something at time: " + String(time) + ", LAST_TRANSMIT: " + String(this->LAST_TRANSMIT) + ", TRANSMIT: " + String(this->TRANSMIT));
        LoRa.beginPacket();
        LoRa.print(craftMessage());
        LoRa.endPacket();
        this->LAST_TRANSMIT = time + this->TRANSMIT;
    }
}

String assLoRa::craftMessage() {
    updateDevice();
    unsigned long time = millis();

    String message = "";
    message += thisDevice.name + ",";
    message += String(thisDevice.powerlevel * MULTIPLIER, 0) + ",";
    message += String(thisDevice.pattern) + ",";
    message += "0,";
    message += String(thisDevice.patternState) + ",";
    message += String(thisDevice.patternTime) + ",";
    message += String(thisDevice.stamp) + ";";
    for(int i = 0; i < 2; i++) {
        String name = deviceList[i].name;
        if (name != "null") {
            message += name + ",";
            message += String(deviceList[i].powerlevel * MULTIPLIER, 0) + ",";
            message += String(deviceList[i].pattern) + ",";
            unsigned long lastseen = time - deviceList[i].lastupdatebyme;
            message += String(lastseen) + ",";
            message += String(replaceNewParam(deviceList[i].stamp,i+1)) + ";";
        }
    }

    //debugln("RECIEVED : " + message);

    message = "ASS:" + XOR(message, PASSWORD);
    //debugln("Encrypted Message: " + message);

    return message;
}

void assLoRa::parseData(String packet) {
    unsigned long time = millis();

    //debugln("Parse packet: " + packet);

    if (!packet.startsWith("ASS:")) {
        //debugln("Bad Packet - no ASS");
        controller->talk(assMouthTalk::LORA_BADPACKET);
        debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
        return;
    }

    this->packetCount++;

    packet = packet.substring(4);

    // Remove "ASS:" from the start of the packet
    packet = XOR(packet, PASSWORD);

    //debugln("Decrypted packet: " + String(packet));


    int numDevices = std::count(packet.begin(), packet.end(), ';');
    //debugln("Number of devices in packet: " + String(numDevices));

    for(int i = 0; i < numDevices; i++) {
        String deviceData = packet.substring(0, packet.indexOf(';'));
        packet = packet.substring(packet.indexOf(';') + 1);

        // Parsing data from packet
        String name = deviceData.substring(0, deviceData.indexOf(','));
        //debugln("Parsing device: " + name);
        if(name == thisDevice.name) {
            //debugln("Device is me. My name got around.");
            // Pink pixel?
            continue;
        }
        if (!verifyName(name)) {
            //debugln("Bad Packet - invalid name: " + name);
            controller->talk(assMouthTalk::LORA_BADPACKET);
            debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
            return; // Bad packet
        }

        deviceData = deviceData.substring(deviceData.indexOf(',') + 1);
        double powerlevel = deviceData.substring(0, deviceData.indexOf(',')).toDouble();
        powerlevel = powerlevel / MULTIPLIER;
        if (!verifyLevel(powerlevel, name)) {
            //debugln("Bad Packet - invalid level: " + String(powerlevel));
            controller->talk(assMouthTalk::LORA_BADPACKET);
            debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
            return; // Bad packet
        }

        deviceData = deviceData.substring(deviceData.indexOf(',') + 1);
        int pattern = deviceData.substring(0, deviceData.indexOf(',')).toInt();
        if (pattern > 999 || pattern < 0) {
            //debugln("Bad Packet - invalid pattern: " + String(pattern));
            controller->talk(assMouthTalk::LORA_BADPACKET);
            debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
            return; // Bad packet
        }

        deviceData = deviceData.substring(deviceData.indexOf(',') + 1);
        int lastseeninswarm = deviceData.substring(0, deviceData.indexOf(',')).toInt();
        if (lastseeninswarm > DROP || lastseeninswarm < 0) {
            //debugln("Bad Packet - invalid lastseen: " + String(lastseeninswarm));
            controller->talk(assMouthTalk::LORA_BADPACKET);
            debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
            return; // Bad packet
        }

        int patternState = -1;
        int patternTime = -1;
        if (i == 0) {
            deviceData = deviceData.substring(deviceData.indexOf(',') + 1);
            patternState = deviceData.substring(0, deviceData.indexOf(',')).toInt();
            if (patternState < -1 || patternState > 1337) {
                controller->talk(assMouthTalk::LORA_BADPACKET);
                debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
                return; // Bad packet
            }
            //debugln("Pattern State is " + String(patternState));

            deviceData = deviceData.substring(deviceData.indexOf(',') + 1);
            patternTime = deviceData.substring(0, deviceData.indexOf(',')).toInt();
            if (patternTime < -1 || patternTime > DROP) {
                controller->talk(assMouthTalk::LORA_BADPACKET);
                debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
                return; // Bad packet
            }
        }

        deviceData = deviceData.substring(deviceData.indexOf(',') + 1);
        int stamp = deviceData.substring(0, deviceData.indexOf(',')).toInt();
        if (!verifyStamp(stamp, name)) {
            //debugln("Bad Packet - invalid stamp: " + String(stamp));
            controller->talk(assMouthTalk::LORA_BADPACKET);
            debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: ERROR");
            return; // Bad packet
        }

        if (i==0) debugln("SUPERSECURE_v31 A.S.S. PROTOCOL: CODE 3 - Name: " + name + " - Swagger: " + powerlevel);

        bool c = false;
        // Check if the device is already in the list
        for(int j = 0; j < 3; j++) {
            if(this->deviceList[j].name == name) {
                c = true;
                //debugln("Device in devicelist");

                if (i > 0) { // We do additional checks for secondardy sightings
                    //debugln("Performing secondary checks");
                    int plevel = int(powerlevel);
                    int dlevel  = int(this->deviceList[j].powerlevel);
                    int lastupdatebyme = time - this->deviceList[j].lastupdatebyme;
                    if (replaceNewParam(this->deviceList[j].stamp,0) == replaceNewParam(stamp,0)) { // stamps should change each time
                        //debugln("Rejected update to devicelist: Repeated packet. Stamps are identical. ");
                        break;
                    }
                    if (retrieveNewParam(this->deviceList[j].stamp) == 0) {
                        //debugln("Rejected update to devicelist: Stored stamp parameter is zero against non-zero parameter");
                        break;
                    }
                    if (LAST_UPDATE > lastupdatebyme) {
                        //debugln("Rejected update to devicelist: Must wait to update");
                        break;
                    }
                    if (lastseeninswarm + (LAST_UPDATE / 3) > lastupdatebyme) {
                        //debugln("Rejected update to devicelist: Difference between known and received last update is too small. Potential repeated packet");
                        break;
                    }
                    if (plevel < dlevel) {
                        //debugln("Rejected update to devicelist: Provided level is less than stored level");
                        break;
                    }
                    if (plevel - dlevel > 20) {
                        //debugln("Rejected update to devicelist: Provided level is unexpectadly higher than stored level");
                        break;
                    }
                    if (this->deviceList[j].powerlevel == powerlevel) {
                        //debugln("Rejected update to devicelist: Stored level is equal to provided level. Potential repeated packet.");
                        break;
                    }
                }
                //if (i==0) //debugln("Received update directly from device");
                //debugln("Updating devicelist");

                this->deviceList[j].lastupdatebyme = time - lastseeninswarm;
                this->deviceList[j].powerlevel = powerlevel;
                this->deviceList[j].pattern = pattern;
                this->deviceList[j].patternState = patternState;
                this->deviceList[j].patternTime = patternTime;
                this->deviceList[j].stamp = stamp;
            }
        }
        if (c) continue;
        
        controller->addSwarmName(name);

        int minPowerIndex = 0;
        for(int j = 1; j < 3; j++) {
            if(this->deviceList[j].powerlevel < this->deviceList[minPowerIndex].powerlevel) {
                minPowerIndex = j;
            }
        }

        if (this->deviceList[minPowerIndex].powerlevel < powerlevel) {
            //debugln("Added device to devicelist. Superseeded " + deviceList[minPowerIndex].name);
            this->deviceList[minPowerIndex].name = name;
            this->deviceList[minPowerIndex].powerlevel = powerlevel;
            this->deviceList[minPowerIndex].pattern = pattern;
            this->deviceList[minPowerIndex].lastupdatebyme = time;
            this->deviceList[minPowerIndex].patternState = patternState;
            this->deviceList[minPowerIndex].patternTime = patternTime;
        }
    }

    //debugln("Finished parsing packet.");
    controller->talk(assMouthTalk::LORA_RECEIPT);
    //controller->hello();

    /*
    debugln("Current device list:");
    for(int i = 0; i < 3; i++) {
        debug("Name: " + this->deviceList[i].name + ", ");
        debug("Power level: " + String(this->deviceList[i].powerlevel) + ", ");
        debug("Last updated by me: " + String((time - this->deviceList[i].lastupdatebyme)/1000) + ", ");
        debugln("Pattern: " + String(this->deviceList[i].pattern));
    }*/
}


Device assLoRa::getLeader() {
    Device leader = thisDevice;

    for(int i = 0; i < 3; i++) {
        if(this->deviceList[i].powerlevel > leader.powerlevel) {
            // This device has a higher power level, so it's the new leader
            leader = this->deviceList[i];
        }
    }

    if (leader.name == "null") leader = thisDevice;

    //debugln("Current leader is " + leader.name);

    return leader;
}

void assLoRa::updateStuff() {
    //Drop expired devices
    Device emptyDevice;
    for(int i = 0; i < 3; i++) {
        if (this->deviceList[i].powerlevel > 0) {
            if(millis() - this->deviceList[i].lastupdatebyme > DROP && this->deviceList[i].name != "null" && this->deviceList[i].powerlevel != 0.42) {
                // Remove the device by replacing it with the "empty" device
                //debugln("Device " + deviceList[i].name + " dropped from list due to age");
                this->deviceList[i] = emptyDevice;
            }
        }
    }

    Device leader = getLeader();
    currentLeader = String(leader.name);

    if (controller->bored()) this->TRANSMIT = this->TRANSMIT_SLOW;
    else this->TRANSMIT = this->TRANSMIT_MED; 

    if (leader.name == this->thisDevice.name) {
        this->thisDevice.pattern = controller->getPatIntAnon();
        leader.pattern = this->thisDevice.pattern;
        this->TRANSMIT = this->TRANSMIT_FAST;
    }

    if (previousLeader == currentLeader && leader.name == this->thisDevice.name && leader.pattern == previousPattern) {
        //debugln("I'm the leader and nothing has changed.");
        return;
    }

    if (previousLeader == currentLeader && leader.patternState == -1 && leader.pattern == previousPattern) {
        //debugln("No update required");
        return;
    }

    // Do we need to update? I.e. no lead change and did not receive direct update from leader
    if (previousLeader != currentLeader) {
        //debugln("Leadership change. Updating pattern.");
        controller->talk(assMouthTalk::LORA_LEADCHANGE);
    }

    //if (leader.patternState != -1) debugln("Pattern state != -1. Received packet from leader or I am the new leader.");
    // To address the corner case, wherein someone in range is next to someone out of range and there's no syncing, we would need to change this.

    /*
    if (leader.pattern != previousPattern) {
        debugln("New pattern");
        //controller->talk(assMouthTalk::LORA_MELEAD);
    }*/

    bool noupdate = false;
    if (leader.patternState == -1) noupdate = true;

    /*debugln("Updating pattern with pattern: " + String(leader.pattern) 
        + ", patternTime: " + String(leader.patternTime + 1) 
        + ", patternState: " + String(leader.patternState) 
        + ", noupdate: " + String(noupdate)); */

    // Add check to not update for certain paterns like static and sparkle
    controller->leadChange(leader.pattern, leader.patternTime + 1, leader.patternState, noupdate);

    previousLeader = currentLeader;
    previousPattern = leader.pattern;

    for(int i = 0; i < 3; i++) {
        deviceList[i].patternState = -1;
    }
}

void assLoRa::updateState(assStates assState) {

    updateDevice();

    this->STATE = assStates::IDLE;
    if (assState != assStates::KILLALLHUMANS) return;

    this->STATE = assStates::KILLALLHUMANS;
    this->LAST_TRANSMIT = 0;

    if (currentLeader == String(this->thisDevice.name)) return;

    Device leader = getLeader();

    controller->leadChange(leader.pattern, leader.patternTime + 1, leader.patternState, false);

}

void assLoRa::updateDevice() {
    this->thisDevice.name = controller->getName();
    this->thisDevice.pattern = controller->getPatIntAnon();
    this->thisDevice.powerlevel = controller->getLevel(true);
    this->thisDevice.patternState = controller->getPatternState();
    this->thisDevice.patternTime = controller->getPatternTime();
    this->thisDevice.stamp = generateStamp(this->thisDevice.name, 0);
}

bool assLoRa::verifyName(String str) {
  if(str.length() != 7) { // Check the length
    return false;
  }

  for(int i = 0; i < 3; i++) { // Check the first 3 characters for being uppercase
    if(!isAlpha(str.charAt(i)) || !isUpperCase(str.charAt(i))) {
      return false;
    }
  }

  if(str.charAt(3) != '-') { // Check the 4th character for being a dash
    return false;
  }

  for(int i = 4; i < 7; i++) { // Check the last 3 characters for being digits
    if(!isDigit(str.charAt(i))) {
      return false;
    }
  }

  return true;
}

bool assLoRa::verifyLevel(float level, String str) {
  // Make sure level does not exceed 1337
  if(level >= 1337.1f) return false;

  // Extract hundredths digit
  float temp = (level * 10) - int(level * 10);
  int hundredths = int(temp * 10);

  // Ensure that the hundredths digit is the same as the middle number of the string
  if(str.length() > 5 && isDigit(str[5])) {
    int digit = str[5] - '0'; // Get the digit from the string
    if(hundredths != digit) {
      return false;
    }
  }

  return true;
}

int assLoRa::generateStamp(String name, int p1) {
    ////debugln("Generating stamp for name: " + name);

    int num = alphabetNumberSum(name);
    if(num < 10) num = num * 10;
    if(num < 100) num = num * 10;
    int r1 = random(0, 10);
    num = (num * 10) + r1;
    int v1 = 9 - r1;
    num = (num * 10) + v1;
    int r2 = random(0, 10);
    num = (num * 10) + r2;
    int v2 = 9 - r2; 
    num = (num * 10) + v2;
    int p2 = 9 - p1;
    num = (num * 10) + p1;
    num = (num * 10) + p2;

    ////debugln("Generated stamp: " + String(num));
    return num;
}

bool assLoRa::verifyStamp(int number, String name) {
    ////debugln("Verifying stamp for name " + name + " with stamp " + String(number));

    int num = alphabetNumberSum(name);

    int alphagive = int(number / 1000000);
    int alphagen = alphabetNumberSum(name);
    if (alphagen < 10) alphagen = alphagen * 10;
    if (alphagen < 100) alphagen = alphagen * 10;
    if (alphagen != alphagive) {
        //debugln("Alphanumeric sums not equal expected " + String(alphagen) + " received " + String(alphagive));
        return false;
    }
    ////debugln("Alpha sums match");

    int r1 = int(number / 100000) % 10;
    int v1gen = 9 - r1;
    int v1give = int(number / 10000) % 10;
    if (v1gen != v1give) {
        //debugln("v1s not equal expected " + String(v1gen) + " received " + String(v1give));
        return false;
    }
    ////debugln("v1s match");

    int r2 = int(number / 1000) % 10;
    int v2gen = 9 - r2;
    int v2give = int(number / 100) % 10;
    if (v2gen != v2give) {
        //debugln("v2s not equal expected " + String(v2gen) + " received " + String(v2give));
        return false;
    }
    ////debugln("v2s match");

    int p1 = int(number / 10) % 10;
    int p2gen = 9 - p1;
    int p2give = number % 10;
    if (p2gen != p2give) {
        //debugln("p2s not equal expected " + String(p2gen) + " received " + String(p2give));
        return false;
    }
    ////debugln("p2s match");

    return true;

}

int assLoRa::retrieveNewParam(long number) {
    number /= 10;
    return number % 10; // Return the second to last digit of the number
}

int assLoRa::replaceNewParam(int num, int p) {

    num /= 100; // Remove the last two digits from the number
    num = (num * 10) + p; // Add the new newParam
    num = (num * 10) + (9-p);
    
    return num;
}

int assLoRa::alphabetNumberSum(String name) {
    int sum = 0;
    for(int i = 0; i < name.length(); i++) {
        char c = name.charAt(i);
        if(isAlpha(c)) {
            // Convert to uppercase and find alphabet number
            sum += toupper(c) - 'A' + 1;
        } else if(isDigit(c)) {
            // Convert char to integer
            sum += c - '0';
        }
    }
    return sum;
}

// Function that XOR encrypts/decrypts a string with a given password
String assLoRa::XOR(String input, String key) {
  String output = "";  // Output string
  unsigned int j = 0;  // Position in key

  // Iterate over the input string
  for(unsigned int i = 0; i < input.length(); i++) {

    // XOR the input character with the corresponding character in the key
    char c = input[i] ^ key[j];

    // Append the encrypted/decrypted character to the output string
    output += c;

    // Move to the next character in the key
    // If we have reached the end of the key, go back to the first character
    j = (j + 1) % key.length();
  }

  return output;
}

byte assLoRa::hexToByte(String hex) {
  return (byte) strtol(hex.c_str(), NULL, 16);
}

String assLoRa::xorDecrypt(String input, String key) {
  String output = "";
  unsigned int j = 0;

  for(unsigned int i = 0; i < input.length(); i += 2) {
    String hexByte = input.substring(i, i+2);
    byte b = hexToByte(hexByte);
    char c = b ^ key[j];
    output += String(c);
    j = (j + 1) % key.length();
  }

  return output;
}
