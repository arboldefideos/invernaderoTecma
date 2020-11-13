
#include <UIPEthernet.h>
#include "PubSubClient.h"

#define CLIENT_ID       "Invernadero"
unsigned long hora = 0;         //Hora de cambio de estado
const int intervalo = 3000;      //Intervalo (millisegundos)
uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

EthernetClient ethClient;
PubSubClient mqttClient;

#include <LiquidCrystal.h>
const int rs = 26, en = 27, d4 = 25, d5 = 24, d6 = 23, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temp, hum;// float tempV, humV;

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc; // Activa el RTC
DateTime HoraFecha;
char tiempo[100];
char tiempoCorto[100];

#define RELAY_ON 0
#define RELAY_OFF 1
float horaencF = 5.0; float horaapagF = 23.0;
float estadoIluminacion;

int techo = 28;
float estadoVentilacion;

void setup() {
  // setup serial communication
  Serial.begin(9600);
  dht.begin(); Serial.println ("Sensor Temperatura inicializado");
  Serial.println("Version: 0.0.9beta");
  Serial.print("Hora de encendido: "); Serial.println(horaencF);
  Serial.print("Hora de apagado: "); Serial.println(horaapagF);
  Serial.print("Temperatura de encendido de ventilacion forzada: "); Serial.println(techo);


  rtc.begin(); Serial.println("RTC inicializado");
  actualizaHora();
  Serial.print("Hora del RTC: "); Serial.println(tiempoCorto);

  pinMode (3, OUTPUT);   pinMode (4, OUTPUT);
  digitalWrite (3, RELAY_OFF);  digitalWrite (4, RELAY_OFF);
  // setup ethernet communication using DHCP
  Serial.println("Negociando con DHCP en la red");
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Ethernet configuration using DHCP failed"));
  }
  Serial.print("IP Local: ");
  Serial.println(Ethernet.localIP());

  // setup mqtt client
  Serial.print("Configurando cliente mqtt: ");
  mqttClient.setClient(ethClient);

  mqttClient.setServer("192.168.0.3", 1883); //for using local broker
  Serial.println(F("cliente MQTT configurado"));

  lcd.begin(16, 2);
  Serial.println("Inicializando LCD");

  // Informo en el Mosquitto todo lo anterior:
  Serial.println("Informando la configuracion en MQTT");
  
  char msg[20];
  if (mqttClient.connect(CLIENT_ID)) {
    mqttClient.publish("arboldefideos/taller/invernadero/config/encendidoLuces ", dtostrf(horaencF, 6, 2, msg));
    mqttClient.publish("arboldefideos/taller/invernadero/config/apagadoLuces", dtostrf(horaapagF, 6, 2, msg));
    mqttClient.publish("arboldefideos/taller/invernadero/config/termostato", dtostrf(techo, 6, 2, msg));
    mqttClient.publish("arboldefideos/taller/invernadero/config/actualizacion", dtostrf((intervalo / 1000), 6, 2, msg));
    mqttClient.publish("arboldefideos/taller/invernadero/config/horaRTC", (tiempoCorto));
  }



  Serial.println("Comienzo de la ejecucion.....");

}

void loop() {
  actualizaHora();       //ponerEnHoraRTC();
  luces (horaencF, horaapagF);
   float temp = dht.readTemperature();
  termoF(techo, temp);
  if (millis() - hora >= intervalo) {
    hora = millis();
    sendData();
    lcd_display();
    riego();
  }
  mqttClient.loop();
}
