#include <ArduinoJson.h>
int numero = 0;
String mensaje = "";
int litro = 2000;

int bomba1 = 13;
int bomba2 = 12;
int bomba3 = 11;
int bomba4 = 10;
void setup(){
    Serial.begin(9600);
    pinMode(7, INPUT);
    pinMode(bomba1, OUTPUT);
    pinMode(bomba2, OUTPUT);
    pinMode(bomba3, OUTPUT);
    pinMode(bomba4, OUTPUT);

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
            abastecimiento(cantidad, bomba);
            mensaje = "";
        }
    }
    delay(50);
}

void Senrializar(){
StaticJsonDocument<200> doc;
    doc["sensor"] = "gps";
    doc["time"] = numero;
    serializeJson(doc, Serial);
    Serial.println();
    numero++;
}

void Deenrializar(String mensaje){
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
void abastecimiento(int cantidad, int bomba){
    //Regla de 3, si para llenar 1 litro se necesitan 2000ms
    //Para llenar 30 litros se necesitan 60000ms
    int tiempo = litro * cantidad;
    //Si la bomba es 1, encender el pin 13
    int bombaSeleccionada = 0;
    if(bomba == 1){
        bombaSeleccionada = 13;
    }else if(bomba == 2){
        bombaSeleccionada = 12;
    }else if(bomba == 3){
        bombaSeleccionada = 11;
    }else if(bomba == 4){
        bombaSeleccionada = 10;
    }
    digitalWrite(bombaSeleccionada, HIGH);
    delay(tiempo);
    digitalWrite(bombaSeleccionada, LOW);
    
}
