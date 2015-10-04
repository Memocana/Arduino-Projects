#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>
//#include <SD.h>
#define DHT11_PIN 5 //dht 5.pinde

//File dosya;

/*
Röleler:
 - Light 1 --> pin 6
 - Light 2 --> pin 7
 - Led --> pin 5
 */


#include <Servo.h>
Servo myservo;  //servo kullanmak istersek

byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x0F, 0x4A, 0x57 }; //mac address
byte ip[] = { 
  10, 0, 6, 250 }; // seçilen ip
EthernetServer server(80);
byte gateway[] = { 
  10, 0, 0, 253 }; 
byte subnet[] = { 
  255, 255, 248, 0 }; 
String readString;
int mode = 0;
int steps = 0;
//////////////////////

void setup(){
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Ethernet.begin(mac, ip, gateway, subnet); //ethernet başlangıç
  server.begin();
  Serial.begin(9600);
}

void loop(){

  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
        }
        if(readString.indexOf("?lighton") >0)//checks for on
        {
          mode = 1;
          Serial.println("1 On");
        }
        else{
          if(readString.indexOf("?lightoff") >0)//checks for off
          {
            mode = 0;
            Serial.println("1 Off");
          }
        }
        if(readString.indexOf("?light2on") >0)//checks for on
        {
          mode = 2;
          Serial.println("2 On");
          digitalWrite(6, HIGH);   
          digitalWrite(5, HIGH);   
          delay(1000);
        }
        else{
          if(readString.indexOf("?light2off") >0)//checks for off
          {
            mode = 0;
            Serial.println("2 Off");
            digitalWrite(6, LOW);   
            digitalWrite(5, LOW);   
            delay(1000);
          }
        }

        if(readString.indexOf("?light3on") >0)//checks for on
        {
          mode = 3;
          Serial.println("3 On");
        }
        else{
          if(readString.indexOf("?light3off") >0)//checks for off
          {
            mode = 0;
            Serial.println("3 Off");
          }
        }

        if (c == '\n') {

          ///////////////
          Serial.println(readString);

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.print("Light 1: ");
          if (digitalRead(6) == HIGH) {
            client.print("is ON");
          }
          else {
            client.print("is OFF.");
          }

          client.println("<br />");
          client.print("Light 2: ");
          if (digitalRead(7) == LOW) {
            client.print("is OFF.");
          }
          else {
            client.print("is ON.");
          }

          client.println("<br />");
          client.print("Led's : ");
          if (digitalRead(5) == LOW) {
            client.print("are OFF.");
          }
          else {
            client.print("are ON.");
          }

          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel='stylesheet' type='text/css' href='http://homeautocss.net84.net/a.css' />");
          client.println("<TITLE>Control Panel</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>Hisar CS Patates Control Panel</H1>");
          client.println("<br />");
          client.println("Software Version : v1.3beta2");
          client.println("<hr />");
          client.println("<br />");
          client.println(Ethernet.localIP());
          client.println("<br />");
          client.println("<br />");
          client.println("<a href=\"/?lighton\"\">Turn On Sequence 1</a>");
          client.println("<a href=\"/?lightoff\"\">Turn Off Sequence 1</a><br />");
          client.println("<br />");
          client.println("<a href=\"/?light2on\"\">Turn On Sequence 2</a>");
          client.println("<a href=\"/?light2off\"\">Turn Off Sequence 2</a><br />");
          client.println("<br />");
          client.println("<a href=\"/?light3on\"\">Turn On Sequence 3</a>");
          client.println("<a href=\"/?light3off\"\">Turn Off Sequence</a><br />");
          client.println("<br />");   

          client.print("Light 1: ");
          if (mode == 1) {
            client.print("is ON");
          }
          else {
            client.print("is OFF.");
          }

          client.println("<br />");
          client.print("Light 2: ");
          if (mode == 2) {
            client.print("is ON.");
          }
          else {
            client.print("is OFF.");
          }

          client.println("<br />");
          client.print("Led's : ");
          if (mode == 3) {
            client.print("are ON");
          }
          else {
            client.print("are OFF.");
          }

          /*client.println("<br />");
           client.print("Nem ");
           client.println(DHT.humidity, 1);
           client.print("Sicaklik ");
           client.println(DHT.temperature, 1);
           */
          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);

          client.stop();//bağlantı fin.


          readString="";


        }
      }
    }
  }
  if (mode == 1) {
    //stuff
  }  
  else if (mode == 2) {
    //digitalWrite(6, HIGH);   
  }  
  else if (mode   == 3) {
    //
  } 
  else if (mode == 0) {
    digitalWrite(6, LOW);   
  }
  steps++;
  if (steps % 4 == 0) {
    steps = 0;
  }
}






