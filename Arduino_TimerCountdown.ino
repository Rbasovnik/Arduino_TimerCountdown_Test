#include <LiquidCrystal.h>

LiquidCrystal lcd(4,5,6,7,8,9);

#define BTN_UP      0
#define BTN_DOWN    1
#define BTN_LEFT    2
#define BTN_RIGHT   3
#define BTN_SELECT  4
#define BTN_NONE    5
#define STATE_TIME  2
#define STATE_COUNTDOWN 4

int readButton(){
  int value = analogRead(A0);
  if(value < 70){
    return BTN_RIGHT;
  }
  if(value < 235){
    return BTN_UP;
  }
  if(value < 416){
    return BTN_DOWN;
  }
  if(value < 620){
    return BTN_LEFT;
  }
  if(value < 881){
    return BTN_SELECT;
  }
  return BTN_NONE;
}

char tiempo[16];
int secondsValue = 0;
int minutesValue = 0;

void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
  lcd.print(tiempo);
  lcd.setCursor(0,1);
  lcd.print("^");
}

  int cursorPosition = 0;
  int previousValue = BTN_NONE;
  int state = STATE_TIME;
  long tInicial = 0;
  int tiempoBomba;
  long currentMillis;
  
  
  void stateTime(){  
  delay(100);
  int value = readButton();
  if(previousValue == BTN_NONE && value != BTN_NONE){
    switch(value){
      case BTN_RIGHT:
        if(cursorPosition == 0 || cursorPosition == 3){
          lcd.setCursor(cursorPosition, 1);
          lcd.print(" ");
          cursorPosition ++;
          lcd.setCursor(cursorPosition, 1);
          lcd.print("^");
        }
        else if (cursorPosition == 1){
          lcd.setCursor(cursorPosition, 1);
          lcd.print(" ");
          cursorPosition +=2 ;
          lcd.setCursor(cursorPosition, 1);
          lcd.print("^");
        }
      break;
      case BTN_LEFT:
        if(cursorPosition == 4 || cursorPosition == 1){
          lcd.setCursor(cursorPosition, 1);
          lcd.print(" ");
          cursorPosition --;
          lcd.setCursor(cursorPosition, 1);
          lcd.print("^");
        }
        else if (cursorPosition == 3){
          lcd.setCursor(cursorPosition, 1);
          lcd.print(" ");
          cursorPosition -= 2;
          lcd.setCursor(cursorPosition, 1);
          lcd.print("^");
        }
      break;
      case BTN_UP:
       if(cursorPosition == 3 && secondsValue < 50){
          secondsValue += 10;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
        }
       if(cursorPosition == 4 && secondsValue < 59){
          secondsValue++;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
        }
       if(cursorPosition == 0 && minutesValue <= 80){
          minutesValue += 10;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
       }
       if(cursorPosition == 1 && minutesValue < 99){
          minutesValue++;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
       }
      break;
      case BTN_DOWN:
        if(cursorPosition == 3 && secondsValue >= 10){
          secondsValue -= 10;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
        }
       if(cursorPosition == 4 && secondsValue >= 0){
          secondsValue--;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
        }
       if(cursorPosition == 0 && minutesValue >= 10){
          minutesValue -= 10;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
       }
       if(cursorPosition == 1 && minutesValue >= 0){
          minutesValue--;
          lcd.setCursor(cursorPosition, 0);
          lcd.clear();
          sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
          lcd.print(tiempo);
       }
      break;
    case BTN_SELECT:
    state = STATE_COUNTDOWN;
    tInicial = millis();
        tiempoBomba = (minutesValue*60) + secondsValue;
    break;
    }
  
  }
  }

  void stateCountdown()
  {
  currentMillis = millis();
  if((currentMillis - tInicial)>=1000){
    tiempoBomba--;
    tInicial = currentMillis;
  }
  minutesValue = tiempoBomba/60;
  secondsValue = tiempoBomba%60;
  sprintf(tiempo, "%.2d:%.2d", minutesValue, secondsValue);
  lcd.setCursor(0,0);
    lcd.print(tiempo);
    
    if(tiempoBomba == 0){
      state = STATE_TIME;
    } 
  }

void loop()
{
  switch(state){
    case STATE_TIME:
      stateTime();
      break;
    case STATE_COUNTDOWN:
      stateCountdown();
      break;
  }
  delay(50);
}

