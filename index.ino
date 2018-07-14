//Including required Libraries
#include <Adafruit_Fingerprint.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#include <Servo.h>

Servo Left;
Servo Right;

bool opened=true;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial);

/* Create a WiFi access point and provide a web server on it. */


const char *ssid = "Nabin";
const char *password = "88888888";

ESP8266WebServer server(80);


void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);  //Provides the html page index.h
}

void Unlock(){
  Left.write(0);
  Right.write(0);
  server.send(200, "text/html", "<h1>Bicycle has been Unlocked !</h1>"); //Send HTTP status 200(Ok)and send Unlocked text
  
  }
  
void Lock(){
  Left.write(90);
  Right.write(90);
  server.send(200, "text/html", "<h1>Bicycle has been Locked !</h1>"); //Send HTTP status 200(Ok)and send Locked text
  
  }
void setup()  
{
  Left.attach(D2);
  Right.attach(D3);
  delay(1000);
  //Serial.begin(115200);
  //Serial.println();
  //Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */ 
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
  //Serial.println(myIP);


  
  
  server.on("/", handleRoot);   // Call the 'handleRoot' function when a client requests url
  server.on("/Unlock", Unlock ); //Call the 'Unlock' function when a client requests url
  server.on("/Lock", Lock );  //Call the 'Lock' function when a client requests url



  
  server.begin();
  //Serial.println("HTTP server started");
  //Serial.begin(9600);
 // while (!Serial);  // For Yun/Leo/Micro/Zero/...
  //delay(100);
  //Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
   // Serial.println("Found fingerprint sensor!");
  } else {
   // Serial.println("Did not find fingerprint sensor 😞");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  //Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  //Serial.println("Waiting for valid finger...");
}

void loop()                     // run over and over again
{
  getFingerprintID();
  server.handleClient(); 
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    if(opened)
    {
      opened=false;
      Left.write(90);
      Right.write(90);
    }
    else
    { 
      opened=true;
      Left.write(0);
      Right.write(0);
    }
   // Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    //Serial.println("Did not find a match");
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  //Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  //Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  //Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  //Serial.print(" with confidence of "); Serial.println(finger.confidence);

  
  
  Left.write(0);
  Right.write(0);
  
  return finger.fingerID; 

