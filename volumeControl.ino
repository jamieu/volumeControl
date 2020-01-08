void setup() {
  // initialize serial ports
  Serial.begin(9600);    // USB serial port 0
  Serial1.begin(9600);   // AV1 | serial port 1 | 19(RX), 18(TX)
  Serial2.begin(9600);   // Lumagen | serial port 2 | 17(RX), 16(TX)

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("<Arduino is ready>");

  Serial.write("ZB+"); // set [+] char to [block] char for volume bars (Lumagen)
}

char rx_char;
char rx_char1;
char rx_char2;

int currentVolume;
int volume;

String mode;
String nightmode;

String response;

void loop() {

  if (Serial.available() > 0) {
    if (Serial.read() == '@')  {  // AV1 command responses
       response = Serial.readStringUntil('\n');
       if (response.startsWith("VOL")) {
          volume = response.substring(4).toInt();
       } 
       if (response.startsWith("MODE")) {
          mode = response.substring(5);
       } 
       if (response.startsWith("NIGHT")) {
          nightmode = response.substring(5);
       } 
    }
  }

  // Update Lumagen OSD when volume changes
  if (volume != currentVolume) {
    currentVolume = volume;
    displayVolume(volume, mode, nightmode);
  }

  // Request the current volume settings from the AV1
  // Serial.println("#VOL ?");
  // Serial.println("#MODE ?");
  // Serial.println("#NIGHT ?");
  
  if (Serial1.available() > 0) {
    ; // AV1
  }
  
  if (Serial2.available() > 0) {
    ; // Lumagen
  }
    
  delay(1000);
}

String volumeBar(int volume, String mode, String nightmade) {
  int vol = ceil(volume / 10);
  String bar = "";
  for (int i = 0; i < vol; i++) {
    bar += "+";
  }
  for (int i = 0; i < 10 - vol; i++) {
    bar += " ";
  }
  String msg = "ZT1Volume: " + bar + " (" + volume + ")       Mode: " + mode;
  return msg;
}

void displayVolume(int volume, String mode, String nightmade) {
  String msg = volumeBar(volume, mode, nightmade);
  Serial2.println("ZT" + 2 + msg);
}


/*
= AV1 commands =
#VOL ?<CR>
#MODE ?<CR> returns @MODE PLIIMOVIE<CR>
#NIGHT ?<CR>

= Lumagen  commands =
ZTMxxxx<CR> 
Print message on the screen-- M = '0' to ‘9’
'9' leaves message until "ZC" sent. 
2 lines, 30 characters per line, legal characters '' through 'z' (0x20 - 0x7a in hex), 
a carriage return or '{' can be used to terminate message. 
*/
