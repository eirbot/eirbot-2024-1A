#ifndef __OLED_SCREEN_H__
#define __OLED_SCREEN_H__

void oledPrintln(const char* message, int ligne, int colonne);
void oledPrintln(const int message, int ligne, int colonne);
void oledPrint(const int message, int ligne, int colonne);
void oledPrintln(const unsigned int message, int ligne, int colonne);
void oledPrintln(const float message, int ligne, int colonne);
void oledPrintln(const char message, int ligne, int colonne);
void oledPrintScore(int score);
void oled_setup();
void oledBlink(int ligne);
void oledSquare(int ligne, char etat);
void oledRefresh();

#endif