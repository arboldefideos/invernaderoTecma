void termoF(int techo, float temp) {

  if (temp > techo)
  {
    digitalWrite(5, RELAY_ON);
    estadoVentilacion = 1;
  }
  else
  {
    digitalWrite(5, RELAY_OFF);
    estadoVentilacion = 0;
  }
}
