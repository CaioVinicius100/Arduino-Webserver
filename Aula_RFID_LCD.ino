#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char card[14];
int i;
int c;
char card_pass[14] = {"4E0004424E46"};
int avaliado;
SoftwareSerial mySerial(10, 9); // RX, TX

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Goodnight moon!");
  mySerial.begin(9600);
}

void loop() { // run over and over
  
  i = 0;
  avaliado = 0;
  lcd.setCursor(3, 0);

  while (mySerial.available()) {
    c = mySerial.read();

    if ((c != 2)  && (c != 3) && (c != 10) && (c != 13)) {
      card[i] = c;
      i++;
    }

    if (c == 3) {
      for (int j = 0; j < 14; j++) {
        Serial.print(card_pass[j]);
        Serial.print("\t");
        Serial.println(card[j]);
        if (card_pass[j] == card[j]) {
          avaliado = 1;
        }
        else {
          avaliado = 0;
          break;
        }
      }
      
      if (avaliado == 1) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ACESSO PERMITIDO");
        //Serial.println("Aqui");
      }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        //Serial.println("Aqui_nao");
        lcd.print("ACESSO NEGADO");
      }
    }


    delay(5);
  }
}


