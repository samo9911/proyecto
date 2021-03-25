#include <ESP8266WiFi.h>

const char* ssid = "TELECABLE_4D73";
const char* password = "DC54B3484D73";
 
int relevadorPin = 15; // 
byte sensorPin =14; //  para el sensor de movimiento
byte movimiento = 0; // Variable que detecta el movimiento
WiFiServer server(80);
 
void setup() {
   pinMode(sensorPin,INPUT);
   pinMode(relevadorPin,OUTPUT);
   digitalWrite(relevadorPin, LOW);
  Serial.begin(115200);
  delay(10);
 
 
  // Coneccion con la red a internet
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
  Serial.println("WiFi conectado");
 
  // Inicio del servidor
  server.begin();
  Serial.println("Servidor iniciado");
 
  // Imprimir la direccion IP
  Serial.print("Use esta URL: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Revisar si el cliente se a conectado
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // revisando los datos del cliente
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  byte estado = digitalRead(sensorPin);

  if(estado == HIGH) {
    Serial.println("Se ha detectado movimiento!");
    movimiento++;
    delay(1000);
    Serial.println(movimiento);
  }
  else if (estado == LOW) {
    delay(1500);
    Serial.println("Sin movimiento!");
  }
 
// Establecion la accion segun la orden

 
  // regresa una respuesta
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Estdo del Pin ");
 
  if(estado == HIGH) {
    client.print("encendido");
  } else {
    client.print("apagado");
  }
  client.println("<br><br>");
  client.println("<a> estado </a>");
 
 
  delay(1);
  Serial.println("Clinte desconectado");
  Serial.println("");
 
}
