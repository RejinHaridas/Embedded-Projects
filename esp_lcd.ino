
#include <LiquidCrystal.h>

const int RS = 23;    // Register Select
const int EN = 22;    // Enable Pin
const int D4 = 21;    // Data Pin 4
const int D5 = 19;    // Data Pin 5
const int D6 = 18;    // Data Pin 6
const int D7 = 5;     // Data Pin 7

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int i = 0;  // Variable to control the horizontal cursor movement

void setup() {
  Serial.begin(115200);
  
  // Initialize the LCD
  lcd.begin(16, 2);  // 16 columns, 2 rows
  lcd.clear();
  lcd.home();        // Set cursor to top left
  lcd.print("HELLO WORLD");
  delay(1000);
  
  lcd.setCursor(0, 1);  // Move to second row
  lcd.print("WELCOME ");
  delay(2000);
}

void loop() {
  static int counter = 0;
  
  lcd.setCursor(i, 1);  // Set cursor in second row and move horizontally
  lcd.print(counter);    // Print the counter
  
  counter++;             // Increment counter
  
  i++;                   // Increment cursor position
  if (i > 15) {          // Reset cursor position when reaching the end of the row
    i = 0;
    lcd.clear();         // Optional: clear the screen before restarting
  }

  delay(1000);           // Wait 1 second before updating
}
/*#include <LiquidCrystal.h>

const int RS = 23;    // Register Select
const int EN = 22;    // Enable Pin
const int D4 = 21;    // Data Pin 4
const int D5 = 19;    // Data Pin 5
const int D6 = 18;    // Data Pin 6
const int D7 = 5;     // Data Pin 7

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 lcd.begin(16,2);
 lcd.clear();
 lcd.home();
 lcd.print("HELLO WORLD");
 delay(1000);
 lcd.setCursor(0,1);
 lcd.print("WELCOME ");
 delay(2000);
 
}
int i=0;
void loop() {
  // put your main code here, to run repeatedly:
  static int counter = 0;
  lcd.setCursor(i,1);
  lcd.print(counter);
  counter++;
  i++;
  delay(1000);

}
*/
