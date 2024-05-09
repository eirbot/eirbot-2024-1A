#include <Arduino.h>
#include <Adafruit_SSD1306.h>

//========= Police de caractère : FreeMono (fournie avec librairie Adafruit GFX)

// #include <Fonts/FreeMono9pt7b.h>                    // Normal (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeMono12pt7b.h>
//#include <Fonts/FreeMono18pt7b.h>
//#include <Fonts/FreeMono24pt7b.h>

//#include <Fonts/FreeMonoBold9pt7b.h>              // Gras (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeMonoBold12pt7b.h>
//#include <Fonts/FreeMonoBold18pt7b.h>
//#include <Fonts/FreeMonoBold24pt7b.h>

//#include <Fonts/FreeMonoOblique9pt7b.h>           // Italique (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeMonoOblique12pt7b.h>
//#include <Fonts/FreeMonoOblique18pt7b.h>
//#include <Fonts/FreeMonoOblique24pt7b.h>

//#include <Fonts/FreeMonoBoldOblique9pt7b.h>       // Gras + Italique (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeMonoBoldOblique12pt7b.h>
//#include <Fonts/FreeMonoBoldOblique18pt7b.h>
//#include <Fonts/FreeMonoBoldOblique24pt7b.h>

//========= Police de caractère : FreeSans (fournie avec librairie Adafruit GFX)

#include <Fonts/FreeSans9pt7b.h>                    // Normal (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSans12pt7b.h>
//#include <Fonts/FreeSans18pt7b.h>
//#include <Fonts/FreeSans24pt7b.h>

//#include <Fonts/FreeSansBold9pt7b.h>              // Gras (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSansBold12pt7b.h>
//#include <Fonts/FreeSansBold18pt7b.h>
//#include <Fonts/FreeSansBold24pt7b.h>

//#include <Fonts/FreeSansOblique9pt7b.h>           // Italique (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSansOblique12pt7b.h>
//#include <Fonts/FreeSansOblique18pt7b.h>
//#include <Fonts/FreeSansOblique24pt7b.h>

//#include <Fonts/FreeSansBoldOblique9pt7b.h>       // Gras + Italique (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSansBoldOblique12pt7b.h>
//#include <Fonts/FreeSansBoldOblique18pt7b.h>
//#include <Fonts/FreeSansBoldOblique24pt7b.h>

//========= Police de caractère : FreeSerif (fournie avec librairie Adafruit GFX)

// #include <Fonts/FreeSerif9pt7b.h>                   // Normal (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSerif12pt7b.h>
//#include <Fonts/FreeSerif18pt7b.h>
//#include <Fonts/FreeSerif24pt7b.h>

//#include <Fonts/FreeSerifBold9pt7b.h>             // Gras (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSerifBold12pt7b.h>
//#include <Fonts/FreeSerifBold18pt7b.h>
//#include <Fonts/FreeSerifBold24pt7b.h>

//#include <Fonts/FreeSerifItalic9pt7b.h>           // Italique (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSerifItalic12pt7b.h>
//#include <Fonts/FreeSerifItalic18pt7b.h>
//#include <Fonts/FreeSerifItalic24pt7b.h>

//#include <Fonts/FreeSerifBoldItalic9pt7b.h>       // Gras + Italique (en 9, 12, 18, et 24 pts)
//#include <Fonts/FreeSerifBoldItalic12pt7b.h>
//#include <Fonts/FreeSerifBoldItalic18pt7b.h>
//#include <Fonts/FreeSerifBoldItalic24pt7b.h>


#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);   // Le "Wire" indique qu'on travaille en I2C


// ========================
// Initialisation programme
// ========================
void oled_setup() {

  // Initialisation de l'écran OLED
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED));                               // Arrêt du programme (boucle infinie) si échec d'initialisation
  

  // Affichage d'un texte "Hello World", avec une des autre polices disponibles 
  ecranOLED.clearDisplay();                 // Vidange du buffer de l'écran OLED
  ecranOLED.setTextSize(1);                 // Sélection de l'échelle 1:1
  ecranOLED.setTextColor(WHITE);            // Couleur "blanche" (ou colorée, si votre afficheur monochrome est bleu, jaune, ou bleu/jaune)
  ecranOLED.setCursor(0,50);                 // Positionnement du curseur dans l'angle haut-gauche, avec décalage de 1 pixel vers le bas

  // ecranOLED.setFont(&alarm_clock6pt7b);     // Sélection de la police "Alarm Clock"
  // ecranOLED.println("AlarmClock");            // …et affichage du nom de cette police

  // ecranOLED.setFont(&FreeMono9pt7b);        // Sélection de la police "Free Mono"
  // ecranOLED.println("FreeMono");            // …et affichage du nom de cette police

  ecranOLED.setFont(&FreeSans9pt7b);        // Sélection de la police "Free Sans"
  // ecranOLED.println("FreeSans");            // …et affichage du nom de cette police

  // ecranOLED.setFont(&FreeSerif9pt7b);       // Sélection de la police "Free Serif"
  // ecranOLED.println("FreeSerif");           // …et affichage du nom de cette police

  // ecranOLED.fillRect(0, -15, 128, 20, BLACK);

  ecranOLED.display();

  // Nota : pour revenir à la police de caractère "d'origine", il suffit d'écrire la ligne : display.setFont();
  
}

void oledRefresh(){
  ecranOLED.clearDisplay();
}

void oledPrintln(const char* message, int ligne, int colonne){
  // ecranOLED.clearDisplay();
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.fillRect(colonne, ligne-12, 115, 13, BLACK);
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.println(message);
  ecranOLED.display();
}

void oledPrintln(const int message, int ligne, int colonne){
  // ecranOLED.clearDisplay();
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.fillRect(colonne, ligne-12, 115, 13, BLACK);
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.println(message);
  ecranOLED.display();
}

void oledPrint(const int message, int ligne, int colonne){
  // ecranOLED.clearDisplay();
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.print(message);
  ecranOLED.display();
}

void oledPrintln(const unsigned int message, int ligne, int colonne){
  // ecranOLED.clearDisplay();
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.fillRect(colonne, ligne-12, 115, 13, BLACK);
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.println(message);
  ecranOLED.display();
}

void oledPrintln(const float message, int ligne, int colonne){
  // ecranOLED.clearDisplay();
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.fillRect(colonne, ligne-12, 115, 13, BLACK);
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.println(message);
  ecranOLED.display();
}

void oledPrintln(const char message, int ligne, int colonne){
  // ecranOLED.clearDisplay();
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.fillRect(colonne, ligne-12, 115, 13, BLACK);
  ecranOLED.setCursor(colonne,ligne);
  ecranOLED.println(message);
  ecranOLED.display();
}

void oledPrintScore(int score){
  ecranOLED.setCursor(0, 60);
  ecranOLED.setTextSize(5);
  ecranOLED.println(score);
  ecranOLED.display();
  ecranOLED.setTextSize(1);
}

void oledBlink(int ligne){
  ecranOLED.fillRect(120, ligne, 5, 5, INVERSE);
}

void oledSquare(int ligne, char etat){
  ecranOLED.fillRect(120, ligne, 5, 5, etat);
}