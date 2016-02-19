#include <SoftwareSerial.h>
#include <ParallaxLCD.h>

#define LCD_SCREEN      1

#define BETA            3977.0f
#define RTHERM          10000.0f
#define THERM_T0        25.0f
#define R1              1000.0f          //Resistor value in Ohms of the resistor in voltage divider with Rth
#define V_MAX           5.0f               //Analog voltage max
#define AI_PIN          2               //Analog input pin for the thermistor
#define ADC_RES         1024            //ADC Resolution
#define S_SERIAL_PIN    4
#define LCD_ROWS        2
#define LCD_COLS        16
#define ALARM_THRESH    50.0f


ParallaxLCD lcd(S_SERIAL_PIN, LCD_ROWS, LCD_COLS); // desired pin, rows, cols

void setup() {
#if(LCD_SCREEN)
  lcd.setup();
  lcd.empty();
  delay(500);
  lcd.backLightOn();
#endif 
}

void loop() {
  //Get voltage across thermistor
  int aiVal = analogRead(AI_PIN);
  float aiVoltage = aiVal*V_MAX/ADC_RES;

  //compute resistance
  float Vr = (aiVoltage);// / V_MAX);
  float Rth = (Vr*R1/(V_MAX - Vr));

  //Compute temp from simplified Steinhart-Hart model
  float Rinf = RTHERM*exp(-BETA/(THERM_T0 + 273.15));
  float temp = BETA/(log(Rth/Rinf));
  temp = temp - 273.15;
  
#if(LCD_SCREEN)
  int significand = floor(temp); 
  int mantissa = (temp - significand)*100;
  int offset = 5;
  int digitsInSignificand = 0;
  
  lcd.at(0, 1, "Temperature:");
  lcd.at(1, offset, significand);
  digitsInSignificand = floor(log10(fabs(significand)));
  lcd.at(1, offset + digitsInSignificand + 1, ".");
  lcd.at(1, offset + digitsInSignificand + 2, mantissa);
  delay(250);

  if(temp > ALARM_THRESH){
    lcd.playTone(50, 217, 226);
  }  
#endif
}
