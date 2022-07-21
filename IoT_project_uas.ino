
#include <OneWire.h> //Library OneWire
#include <DallasTemperature.h> // Library untuk Dallas temperature
#include <LiquidCrystal_I2C.h> //Library I2C LCD
#include "CTBot.h" //Library CTBot untuk Telegram

LiquidCrystal_I2C lcd(0x27, 16, 2); //alamat I2C
#define buzzer D3 //pin D3 untuk buzzer
#define ONE_WIRE_BUS D4 // pin D4 digunakan untuk data hasil baca sensor

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
CTBot myBot;
String ssid = "Awan";    //nama ssid wifi kalian
String pass = "12345678";  //password wifi kalian
String token = "5551348830:AAFXsKxh51Wg1qVstf3MYMkTTx_34gUiKIs";    //token bot baru kalian
const int id = 999141582;    //id telegram kalian

#define simizu D0
void setup(void)
{
  pinMode(simizu, OUTPUT);
  digitalWrite(simizu, HIGH); // turn off the led (inverted logic!)


  Serial.begin(9600);
  sensors.begin(); //memulai baca sensor
  lcd.begin(); //memulai LCD
  lcd.backlight(); //menyalakan Lampu latar belakang LCD
  pinMode(buzzer, OUTPUT); //inisialisasi buzzer sebagai output
  myBot.wifiConnect(ssid, pass); //koneksi dengan hotspot
  myBot.setTelegramToken(token); //memastikan token

  //tes koneksi dengan hotspot
  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }
}

void loop(void)
{
  sensors.requestTemperatures(); //baca sensor
  int suhu = sensors.getTempCByIndex(0);
  //Penulisan suhu pada LCD dan serial monitor
  Serial.println(suhu);

  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("On")) {                   //Perintah dari telegram ke perangkat
      digitalWrite(simizu, HIGH);                              //Lampi dihidupkan
      myBot.sendMessage(msg.sender.id, "Simizu ON"); //Balasan dari perangkat ke Bot Telegram
      lcd.setCursor(0, 1);
      lcd.print("Simizu On");
    }
    else if (msg.text.equalsIgnoreCase("Off")) {              //Perintah dari telegram ke perangkat
      digitalWrite(simizu, LOW);                              //Lampi dihidupkan
      myBot.sendMessage(msg.sender.id, "Simizu OFF"); //Balasan dari perangkat ke Bot Telegram
      lcd.setCursor(0, 1);
      lcd.print("Simizu Off");
    }
    else {                                                    // otherwise...
      // generate the message for the sender
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Try LIGHT ON or LIGHT OFF.";
      myBot.sendMessage(msg.sender.id, reply);             // and send it
    }

  }
  //Jika suhu lebih dari 30
  if (suhu > 30) {
    myBot.sendMessage(id, "Suhu Akuarium Terlalu Panas!"); //mengirimkan pesan ke telegram
    buzzerNyala(); //menyalakan buzzer
    lcd.setCursor(0, 0);
    lcd.print("SUHU PANAS! "); //menampilkan SUHU PANAS di LCD
  }

  else if (suhu < 25) {
    myBot.sendMessage(id, "Suhu Akuarium Terlalu Dingin!"); //mengirimkan pesan ke telegram
    buzzerNyala(); //menyalakan buzzer
    lcd.setCursor(0, 0);
    lcd.print("SUHU DINGIN! "); //menampilkan SUHU DINGIN di LCD
  }
  else {
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Suhu air : ");
    lcd.print(suhu);
  }
  //  lcd.clear();
}

void buzzerNyala() { //Function untuk menyalakan buzzer
  digitalWrite(buzzer, HIGH);
  delay (500);
  digitalWrite(buzzer, LOW);
  delay (500);
}
