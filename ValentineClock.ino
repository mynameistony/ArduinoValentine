#include <SPI.h>         
#include <WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>
#include "stuff.h"

int status = WL_IDLE_STATUS;
char ssid[] = "home network";
char pass[] = "mypassword";  
int keyIndex = 0;            

unsigned int localPort = 2390;

IPAddress timeServer(129, 6, 15, 28);

const int NTP_PACKET_SIZE = 48;

byte packetBuffer[ NTP_PACKET_SIZE]; 
WiFiUDP Udp;

int time = 0;
int hour = 4;
int minute = 20;
boolean isAM = false;

unsigned long lastUpdate = 0;
unsigned long lastLight = 0;

Valentines test(3,4,9600,6,5,9,8);
void setup(){

  Serial.begin(9600);
  test.powerOn();
  
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    while(true);
  } 
  
  while ( status != WL_CONNECTED) { 
    Serial.print("Connecting: ");
    Serial.print(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid);
    Serial.print("...");

    // wait 10 seconds for connection:
    //delay(10000);
  }

  Serial.println("Done.");
  Udp.begin(localPort);
  
  setTime(getTime());
}

void loop()
{
  if(test.getButtonState()){
    Serial.print(test.printRandomMessage());
  }
  
  if(millis() - lastLight > 5000){
    lastLight = millis(); 
    test.lcd->lightOff();
  }  
  
  if(millis() - lastUpdate > 30000){
    lastUpdate = millis();
    setTime(getTime());
    test.printDisplay(hour,minute,isAM,status);
  }
  
  if(test.getDistance() < 50){
    //Remove this
    test.setFade(map(test.getDistance(),0,50,0,255));
    test.lcd->lightOn();
  }
  Serial.print(test.getDistance());
  Serial.print("\t");
  
  Serial.print(hour);
  Serial.print(":");
  if(minute < 10)
    Serial.print("0");
  Serial.print(minute);

  if(isAM)
    Serial.println("AM");
  else
    Serial.println("PM");
    
}
boolean setTime(int newTime){
    if(newTime > 0){
      hour = (newTime / 100) - 8;
      minute = newTime % 100;
  
      if (hour > 12){
        isAM = false;
        hour -= 12;  
      }
      else{
        isAM = true; 
      }
      
      return true;
    }
    
    else{
      return false; 
    }
  
}
int getTime(){
  sendNTPpacket(timeServer);
  
  delay(1000);  

  if ( Udp.parsePacket() ) { 

    Udp.read(packetBuffer,NTP_PACKET_SIZE); 
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
    unsigned long secsSince1900 = highWord << 16 | lowWord;  
    const unsigned long seventyYears = 2208988800UL;     
    unsigned long epoch = secsSince1900 - seventyYears;  
    int hour = (epoch  % 86400L) / 3600;
    int minute = (epoch % 3600) / 60;
    return hour * 100 + minute;
  }
  else  {
    return -1; 
  }
}

// send an NTP request to the time server at the given address 
unsigned long sendNTPpacket(IPAddress& address)
{
  //Serial.println("1");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  //Serial.println("2");
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  
  //Serial.println("3");

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp: 		   
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  //Serial.println("4");
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  //Serial.println("5");
  Udp.endPacket(); 
  //Serial.println("6");
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}










