#include <ESP8266WiFi.h> 
const char* ssid = "Tarun_Kavin"; //wifi ssid / wifi name
const char* password = "Spavi@1413"; //wifi password
int ledPin = 13; // GPIO13 
WiFiServer server(80); 
void setup() { 
 Serial.begin(115200); 
 delay(10); 
 pinMode(D4, OUTPUT);
 pinMode(D5, OUTPUT);
 pinMode(D6, OUTPUT);
 pinMode(D7, OUTPUT); 
 digitalWrite(ledPin, LOW); 
 // Connect to WiFi network 
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, password); 
 while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
 } 
 Serial.println(""); 
 Serial.println("WiFi connected to"); 
 Serial.print(ssid);
 // Start the server 
 server.begin(); 
 Serial.println("Server started"); 
 // Print the IP address 
 Serial.print("Use this URL to connect: "); 
 Serial.print("http://"); 
 Serial.print(WiFi.localIP()); 
 Serial.println("/"); 
} 
void loop() { 
 // Check if a client has connected 
 WiFiClient client = server.available(); 
 //serial.println(client);
 if (client==0) { 
   return; 
 } 
 Serial.println("Client connected");
 // Wait until the client sends some data 
 while(!client.available()){ 
  Serial.print(".");
   delay(500); 
 } 
 String request = client.readStringUntil('\r'); 
 //Serial.println(request); 
 client.flush(); 
 // Match the request 
 int i=0;
 if (request.indexOf("/CAR=UP") != -1)  { 
   digitalWrite(D4,HIGH);
   digitalWrite(D5,HIGH);
   delay(1000);
   digitalWrite(D4,LOW);
   digitalWrite(D5,LOW);
   i=1;
 } 
 if (request.indexOf("/CAR=DOWN") != -1)  { 
   digitalWrite(D6, HIGH);
   digitalWrite(D7,HIGH); 
   delay(1000);
   digitalWrite(D6, LOW);
   digitalWrite(D7,LOW);
   i=2;
 } 
 if (request.indexOf("/CAR=LEFT") != -1)  { 
   digitalWrite(D6, HIGH);
   digitalWrite(D5,LOW); 
   delay(1000);
   digitalWrite(D6, LOW);
   i=3;
 } 
 if (request.indexOf("/CAR=RIGHT") != -1)  { 
   digitalWrite(D4,HIGH);
   digitalWrite(D7,LOW); 
   delay(1000);
   digitalWrite(D4, LOW);
   i=4;
 } 
 if (request.indexOf("/CAR=RESETBUTTONS") != -1)  { 
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
   i=5;
 } 

 
// Set ledPin according to the request 
//digitalWrite(ledPin, value); 
 // Return the response 
 client.println("HTTP/1.1 200 OK"); 
 client.println("Content-Type: text/html"); 
 client.println(""); //  do not forget this one 
 client.println("<!DOCTYPE HTML>"); 
 client.println("<html>"); 
 client.print("<body style='background: #FF0000'>"); 
 client.println("<h1 align ='center'>"); 
 client.println("<font-color='#FF0000'>"); 
 client.println("REMOTE CAR BY STP"); 
 client.println("</font>"); 
 client.println("</h1>"); 
 client.println("<bg color ='#00ff00'>"); 
 client.println("</bg>"); 
 client.println("<p align ='center'>"); 
 client.print("car is now: "); 
 client.println("</p>"); 
 if(i==1) { 
   client.println("<p align ='center'>"); 
   client.print(" MOVING FWD"); 
   client.println("</p>"); 
 } 
 else if(i==2) { 
   client.println("<p align ='center'>"); 
   client.print(" MOVING BACKWARD"); 
   client.println("</p>"); 
 } 
 else if(i==3) { 
   client.println("<p align ='center'>"); 
   client.print(" MOVING LEFT"); 
   client.println("</p>"); 
 } 
 else if(i==4) { 
   client.println("<p align ='center'>"); 
   client.print(" MOVING RIGHT"); 
   client.println("</p>"); 
 } 
 else{
  client.println("<p align ='center'>"); 
  client.print(" CAR ACTIVE"); 
  client.println("</p>"); 
  }

 client.println("<br><br>"); 
 client.println("<p align ='center'>"); 
 client.println("<a  href=\"/CAR=UP\"\"><button>FORWARD </button></a>"); 
 client.println("<a  href=\"/CAR=DOWN\"\"><button>BACKWARD </button></a><br />");
 client.println("<a  href=\"/CAR=LEFT\"\"><button>LEFT </button></a>"); 
 client.println("<a  href=\"/CAR=RIGHT\"\"><button>RIGHT </button></a><br />");
 client.println("<a  href=\"/CAR=RESETBUTTON\"\"><button>reset button </button></a><br />");
    
 client.println("</p>"); 
 client.println("<p>"); 
 client.println("<marquee direction='right'>"); 
 client.println("test piece"); 
 client.println("</marquee>"); 
 client.println("</p>"); 
 client.println("</body>"); 
 client.println("</html>"); 
 delay(1); 
 Serial.println("Client disonnected"); 
 Serial.println(""); 
} 
 