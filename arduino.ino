#include <LiquidCrystal.h>

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

char c[33];
char* split_data[2];
char* print_word;

void setup() {

    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.clear();
}

void printAdScroll(int seconds) {

    float count = 0.0;
    while (count <= seconds) {
        lcd.scrollDisplayLeft();
        delay(200);
        count += 0.2; 
    }
    lcd.clear();
}

void loop() {

    int seconds;

    while (Serial.available()) {
        delay(100);
  
        int i = 0;
        while (Serial.available() > 0) {
            c[i++] = Serial.read();
        }
        
        for(; i < 33; i++) {
            c[i] = ' ';
        }

        char* split = strtok(c, "-");

        int k = 0;
        while(split) {
            split_data[k++] = split;
            split = strtok(NULL, "-");
        }

        print_word = split_data[1];
        int seconds = atoi(split_data[0]);

        lcd.setCursor(15,0);
        for (i = 0; i < 16; i++) {
          lcd.write(print_word[i]);
        }

 
        printAdScroll(seconds);
        
    }
    delay(100);
}