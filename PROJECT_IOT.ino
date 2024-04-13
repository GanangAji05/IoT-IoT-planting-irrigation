#define BLYNK_TEMPLATE_ID "TMPL66u_9cjkC"
#define BLYNK_TEMPLATE_NAME "Monitoring kebun"
#define BLYNK_AUTH_TOKEN "D3FvS9s3PMXRHELzNIzsYaWNQKKOSC0n"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MIRACLE-";
char pass[] = "ganjuranrt1";

WidgetLCD lcd(V2);
WidgetLCD lcdPompa(V3);

int value, distance, level, value2;
const int trigputih = D5;
const int echoabu = D6;
const int analog = A0;
int tanah;
String lemah;
String jarak;
long duration;

BLYNK_WRITE(V1) {
  value2 = param.asInt();
  digitalWrite(D8, value2);
}
BLYNK_WRITE(V0) {
  value = param.asInt();
  digitalWrite(D7, value);
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(analog, INPUT);
  pinMode(trigputih, OUTPUT);
  pinMode(echoabu, INPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  delay(200);
  Blynk.begin(auth, ssid, pass);
}
void Senddata() {

  //Ultrasonik
  digitalWrite(trigputih, LOW);
  delay(200);
  digitalWrite(trigputih, HIGH);
  delay(1000);
  digitalWrite(trigputih, LOW);
  duration = pulseIn(echoabu, HIGH);
  distance = duration * 0.034 / 2;

  //Soil Mouistur
  tanah = analogRead(analog);
}

void Keadaan_Pompa_Tanki() {
  //Keadaan POMPA
  lcdPompa.clear();
  if (value == HIGH) {
    Serial.println("POMPA TANKI HIDUP ");
    lcdPompa.print(0, 0, "POMPATANKI= ");
    lcdPompa.print(11, 0, "HIDUP");

  } else if (value == LOW) {
    Serial.println("POMPA TANKI MATI ");
    lcdPompa.print(0, 0, "POMPATANKI= ");
    lcdPompa.print(12, 0, "MATI");
  }
}

void Keadaan_Pompa_Penyiraman() {
  //Keadaan POMPA
  if (value2 == HIGH) {
    Serial.println("POMPA Penyiraman HIDUP ");
    lcdPompa.print(0, 1, "POMPASIRAM=");
    lcdPompa.print(11, 1, "HIDUP");
  } else if (value2 == LOW) {
    Serial.println("POMPA Penyiraman MATI ");
    lcdPompa.print(0, 1, "POMPASIRAM=");
    lcdPompa.print(12, 1, "MATI");
  }
}

void Keadaan_Tanah() {
  lcd.clear();
  //keadaan Tanah
  if (tanah <= 900 && tanah >= 600) {
    Serial.println("Basah");
    lcd.clear();
    lcd.print(0, 0, "TANAH = ");
    lcd.print(9, 0, "BASAH");
  } else if (tanah >= 900) {
    Serial.println("Kering");
    lcd.print(0, 0, "TANAH = ");
    lcd.print(9, 0, "KERING");
  } else if (tanah <= 600) {
    Serial.println("Tanah sangat basah");
    lcd.print(0, 0, "TANAH = ");
    lcd.print(9, 0, "SANGAT");
  }
}

void Keadaan_Tanki() {
  //Keadaan Tanki
  if (distance <= 4) {
    Serial.println("Tanki 100%");
    lcd.print(0, 1, "TANKI = ");
    lcd.print(9, 1, "100%");
  } else if (distance == 5) {
    Serial.println("Tanki 80%");
    lcd.print(0, 1, "TANKI = ");
    lcd.print(9, 1, "80%");
  } else if (distance == 7) {
    Serial.println("Tanki 50%");
    lcd.print(0, 1, "TANKI = ");
    lcd.print(9, 1, "50%");
  } else if (distance == 8) {
    Serial.println("Tanki 30%");
    lcd.print(0, 1, "TANKI = ");
    lcd.print(9, 1, "30%");
  } else if (distance == 9) {
    Serial.println("Tanki 10%");
    lcd.print(0, 1, "TANKI = ");
    lcd.print(9, 1, "10%");
  } else if (distance == 10) {
    Serial.println("Tanki 0%");
    lcd.print(0, 1, "TANKI = ");
    lcd.print(9, 1, "0%");
  }
}

void loop() {
  Blynk.run();
  Keadaan_Tanah();
  Keadaan_Tanki();
  Keadaan_Pompa_Tanki();
  Keadaan_Pompa_Penyiraman();
  Senddata();
}