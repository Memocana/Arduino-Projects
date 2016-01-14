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
          Serial.println("1 LOW");
          digitalWrite(7, LOW);
        }
        else if(readString.indexOf("?lightoff") >0)//checks for off
        {
          mode = 0;
          digitalWrite(7, HIGH);
          Serial.println("1 HIGH");

        }
        if(readString.indexOf("?seq1") >0)//checks for on
        {
          for (int i = 0; i < 11; i++) {
            digitalWrite(7, !digitalRead(7));
            delay(100);
          }
          
          if (mode == 1) {
            readString =" ?lighton ";
            digitalWrite(7, LOW);
            delay(100);
          } else {
            readString =" ?lightoff ";
            digitalWrite(7, HIGH);
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

          client.print("Lights: ");
          if (digitalRead(7) == LOW) {
            client.print("are ON");
          }
          else {
            client.print("are OFF.");
          }

          client.println("<br />");

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
          client.println("<p id='demo'></p><script>var now = Date();\n document.getElementById('demo').innerHTML = now;</script>");
          client.println("<p><?php");
          client.println("$minutes = date('i')");
          client.println("echo date('H:i:s')");
          client.println("if ($minutes == 0) {");
          client.println("$url = '10.0.6.250/?seq1;");
          client.println("header( 'Location: $url' );");//bu satıra dikkat!
          client.println("}");
          client.println("</?></p>");
          client.println("<br />");
          client.println("<a href=\"/?lighton\"\">Turn On</a>");
          client.println("<a href=\"/?lightoff\"\">Turn Off</a><br />");
          client.println("<br />");
          client.println("<a href=\"/?seq1\"\">Sequence 1</a>");
          client.println("<br />");
          client.println("<a href=\"/?seq2\"\">Sequence 2</a>");
          client.println("<br />");   

          client.print("Lights: ");
          if (mode == 1) {
            client.print("are ON");
          }
          else {
            client.print("are OFF.");
          }

          client.println("<br />");

          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);

          client.stop();//bağlantı fin.


          readString="";


        }
      }
    }
  }
}







