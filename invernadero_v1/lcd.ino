  //Informacion en el LCD
 void lcd_display() {
  float tempF = dht.readTemperature();
  lcd.setCursor(0, 0); lcd.print("Temp:"); lcd.print(int(tempF));
  lcd.setCursor(8, 0); lcd.print(tiempoCorto);
  if (estadoVentilacion == 1) {
    lcd.setCursor(0, 1); lcd.print("VENT. ENCENDIDA");
  }
  else {
    lcd.setCursor(0, 1); lcd.print("Ilum: "); if (estadoIluminacion == 1) {
      lcd.print("ON");
    } else {
      lcd.print("OFF") ;
    }
  }
 }
 
