
void riego(){

const int sensorPin = A0;
 int humedad = analogRead(sensorPin);
 float porcentaje = ((1-(humedad/1023.0))*100); 
   //Serial.print("Nivel de humedad del suelo: "); Serial.println(humedad);
   //Serial.print("Porcentaje de humedad del suelo: "); Serial.print (porcentaje) ; Serial.println ("%");
   

  
   if(humedad > 500)
   {
      //Serial.println("Encendido"); 
      //Serial.println("Riego Activado");
   // digitalWrite(6, RELAY_ON);   
      //hacer las acciones necesarias

      
   }
  
}
