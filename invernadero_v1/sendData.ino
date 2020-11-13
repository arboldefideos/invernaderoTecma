void sendData() {
  char msgBuffer[20];
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  //Serial.print("Temperatura: ") & Serial.print(tempF);
  //Serial.print(" Humedad: ") & Serial.print(humF);
  //Serial.println();

  const int sensorPin = A0;
  int humedad = analogRead(sensorPin);
  float porcentaje = ((1-(humedad/1023.0))*100); 
  int riego ;
  if (humedad > 500) {
    riego = 1;
  }
  else {
    riego = 0 ;
  } ;

  if (mqttClient.connect(CLIENT_ID)) {
    //envio variables
    mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/temp", dtostrf(temp, 6, 2, msgBuffer));
    mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/hum", dtostrf(hum, 6, 2, msgBuffer));
    mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/hora", tiempoCorto) ;
    mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/humedadSuelo", dtostrf(porcentaje, 6, 2, msgBuffer));
    //envio estados


    if (estadoIluminacion == 1 ) {
      mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/luces", "ENCENDIDA");
    }
    else {
      mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/luces", "APAGADA");
    }

    if (estadoVentilacion == 1 ) {
      mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/ventilacion", "ENCENDIDA");
    }
    else {
      mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/ventilacion", "APAGADA");
    }

    if (riego == 1) {
      mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/riego", "ENCENDIDO");
    }
    else {
      mqttClient.publish("arboldefideos/taller/invernadero/tiemporeal/riego", "APAGADO");
    }
  }
}
