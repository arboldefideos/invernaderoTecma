void actualizaHora() {

  int segundo, minuto, hora, dia, mes;
  long anio; //variable año

  HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
  segundo = HoraFecha.second();
  minuto = HoraFecha.minute();
  hora = HoraFecha.hour();
  dia = HoraFecha.day();
  mes = HoraFecha.month();
  anio = HoraFecha.year();
  sprintf(tiempo, "Hora = %d:%d:%d Fecha = %d/%d/%d ", hora, minuto, segundo, dia, mes, anio);
  sprintf(tiempoCorto, "%d:%d:%d ", hora, minuto, segundo);
}

void ponerEnHoraRTC() {

  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    while (1);
  }
  // Fijar a fecha y hora de compilacion
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.print("Tiempo ajustado, volver a la configuracion anterior");
  delay(1000);
  
}
