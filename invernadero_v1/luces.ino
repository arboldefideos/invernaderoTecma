void luces(float horaencF, float horaapagF) {

  HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
  float horamin = HoraFecha.hour() + HoraFecha.minute() / 60.0;

  if (horamin > horaencF && horamin < horaapagF)
  {
    digitalWrite(4, RELAY_ON);
    estadoIluminacion = 1;
  }
  else
  {
    digitalWrite(4, RELAY_OFF);
    estadoIluminacion = 0;
  }
}
