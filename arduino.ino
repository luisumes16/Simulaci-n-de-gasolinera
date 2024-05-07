#include <ArduinoJson.h>
int numero = 0;
String mensaje = "";
int litro = 2000;
void setup(){
    Serial.begin(9600);
    pinMode(7, INPUT);
    pinMode(13, OUTPUT);
}
void loop(){

    //Leer el JSON y guardarlo en un char
    int sensorValue = digitalRead(7);
    if(sensorValue == HIGH){
        Senrializar();
    }
    if(Serial.available()){
        char input = Serial.read();
        mensaje += input;
        Serial.println  (mensaje);
        char* allchar = mensaje.c_str();
        if(input == '}'){
           
                    
            StaticJsonDocument<64> doc;
            deserializeJson(doc, allchar);

            int preciodia = doc["preciodia"]; // 20
            int bomba = doc["bomba"]; // 1
            int cantidad = doc["cantidad"]; // 30

            //Regla de 3, si para llenar 1 litro se necesitan 2000ms
            //Para llenar 30 litros se necesitan 60000ms
            int tiempo = litro * cantidad;
            //Si la bomba es 1, encender el pin 13
            
                digitalWrite(13, HIGH);
                delay(tiempo);
                digitalWrite(13, LOW);
            

            //const char* sensor = doc["sensor"];
            //long time          = doc["time"];
            
           // Serial.println(sensor);
            //delay(2000);
            //Serial.println("Mostrado");
            //delay(2000);
           /* if(time%2 == 0){
                digitalWrite(13, HIGH);
                
            }else {
                digitalWrite(13, LOW);
            }*/
            mensaje = "";
            
        }

     
    }
/*
   char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

StaticJsonDocument<16> doc;
deserializeJson(doc, json);

const char* sensor = doc["sensor"];
long time          = doc["time"];
double latitude    = doc["data"][0];
double longitude   = doc["data"][1];
Serial.println(time);




     char* json = Serial.read();
    StaticJsonDocument<16> doc;

    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;

    }

    const char* sensor = doc["sensor"]; // "gps"
    long time = doc["time"]; // 1351824120
    Serial.println(sensor);
*/
  
   
    delay(50);
}

void Senrializar(){
StaticJsonDocument<200> doc;
    doc["sensor"] = "gps";
    doc["time"] = numero;
    //doc["data"]["latitude"] = 48.756080;
    //doc["data"]["longitude"] = 2.302038;
    serializeJson(doc, Serial);
    Serial.println();
    numero++;
}

void Deenrializar(String mensaje){
  //generar un json y guardarlo en un char
    //char* json = Serial.read();
     StaticJsonDocument<200> doc2;
            DeserializationError error = deserializeJson(doc2, mensaje);
            if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return;
            }
            serializeJson(doc2, Serial);
            Serial.println();
            mensaje = "";
}