# Tambak_Pinter
Tambak Pinter OR Akuarium Pinter

=== Download Libray ===
1. Sevomotor https://www.arduinolibraries.info/libraries/servo
2. LiquidCrystal I2C https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
3. CTBot https://www.arduinolibraries.info/libraries/ct-bot
4. DallasTemperature https://www.arduinolibraries.info/libraries/dallas-temperature
5. OneWire https://www.arduinolibraries.info/libraries/one-wire
6. Arduino Json https://www.arduinolibraries.info/libraries/arduino-json
Apabila ingin mengembangkan dengan memberikan pakan ikan tomatis bisa menambahkan kode berikut di logika if else
        
        
        ///////////////////////////////////////////////
        // Masukan Library
        #include <Servo.h>
        //////////////////////////////////////////////////
        
        ///////////////////////////////////////////////
        int pos = 0;  // variable to store the servo position
        ///////////////////////////////////////////////
        
        
       //////////////////////////////
       /////tambakan di void setup///
        myservo.attach(5);
       ///////////////////////////////
      
      
      ///////////////////////////// Kode logika if
      else if (msg.text.equalsIgnoreCase("Makan")) {  // if the received message is "LIGHT ON"...      
      digitalWrite(led, LOW);                         // turn on the LED (inverted logic!)      
      for (pos = 0; pos <= 180; pos += 1) {           // goes from 0 degrees to 180 degrees      
        // in steps of 1 degree        
        myservo.write(pos);  // tell servo to go to position in variable 'pos'        
        delay(20);           // waits 15ms for the servo to reach the position        
      }
      for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees      
        myservo.write(pos);                  // tell servo to go to position in variable 'pos'        
        delay(20);                           // waits 15ms for the servo to reach the position        
      }
      myBot.sendMessage(msg.sender.id, "Ikan Sudah Di Kasih Makan");  // notify the sender      
      lcd.setCursor(0, 1);      
      lcd.println("Sudah Makan");      
      lcd.clear();      
   }



1. Buat BotFather telgram
![Screenshot_20220721-164616_Telegram](https://user-images.githubusercontent.com/95010003/180200037-eb371ca7-2198-4ef8-999a-263fa8b65460.jpg)

2. Dapatkan id telgram
![Screenshot_20220721-164639_Telegram](https://user-images.githubusercontent.com/95010003/180200118-27452d8e-f8bb-44fd-8ad6-08c77fcc8dc1.jpg)

3. Hasilnya
![Screenshot_20220721-164539_Telegram](https://user-images.githubusercontent.com/95010003/180200146-c78a6039-b74e-4729-8c38-9e5fda6b404f.jpg)
