// Define pin connections & motor's steps per revolution
// const int pas_r = 500;
// const int vit_min = 2500;
// const int vit_max = 500;
// const int delta_r = (vit_min-vit_min)/pas_r;
const int dirPinD = 5;
const int stepPinD = 6;
const int dirPinG = 8;
const int stepPinG = 9;
const int tour = 200;
// unsigned long time = 0;
// unsigned long deltat = 0;

int r_pasD = 0;
int r_dirD = 0;
unsigned long r_timeD = 0;
int r_delaiD = 0;
char r_hlD = 0;
char mot_libreD = 1;
int r_pas_faitsD = 0;
int r_pas_restantsD = 0;

int r_pasG = 0;
int r_dirG = 0;
unsigned long r_timeG = 0;
int r_delaiG = 0;
char r_hlG = 0;
char mot_libreG = 1;
int r_pas_faitsG = 0;
int r_pas_restantsG = 0;

unsigned long a = 0;

void setup()
{
    // Declare pins as Outputs
    pinMode(stepPinD, OUTPUT);
    pinMode(dirPinD, OUTPUT);
    pinMode(stepPinG, OUTPUT);
    pinMode(dirPinG, OUTPUT);
}
void loop()
{
    if (mot_libreG == 1)
    {
        delay(2000);
        def_avancerG(3 * tour, a);
        def_avancerD(3 * tour, a);
        a = (a == 0);
    }
    ver_avancerG();
    ver_avancerD();
    // avancerMotD1(10000, 1);
}

void def_avancerD(unsigned int pas, char dir)
{
    r_pasD = pas;
    // r_dirD = dir;
    r_timeD = micros();
    r_delaiD = 2500;
    r_pas_faitsD = 0;
    r_pas_restantsD = pas;
    mot_libreD = 0;
    if (dir > 0)
        digitalWrite(dirPinD, HIGH);
    if (dir <= 0)
        digitalWrite(dirPinD, LOW);
}

void def_avancerG(unsigned int pas, char dir)
{
    r_pasG = pas;
    // r_dirG = dir;
    r_timeG = micros();
    r_delaiG = 2500;
    r_pas_faitsG = 0;
    r_pas_restantsG = pas;
    mot_libreG = 0;
    if (dir > 0)
        digitalWrite(dirPinG, HIGH);
    if (dir <= 0)
        digitalWrite(dirPinG, LOW);
}

void ver_avancerD()
{
    if (r_pas_restantsD <= 0)
        mot_libreD = 1;
    else
    {
        if (micros() - r_timeD >= r_delaiD)
        {
            r_timeD = micros();
            if (r_hlD == 0)
            {
                digitalWrite(stepPinD, HIGH);
                r_hlD = 1;
            }
            else
            {
                digitalWrite(stepPinD, LOW);
                r_hlD = 0;
                r_pas_restantsD--;
                r_pas_faitsD++;
                if (r_delaiD > 500 && r_pas_faitsD <= r_pasD / 2)
                {
                    r_delaiD -= 4;
                }
                if (r_pas_restantsD < 500 || (r_pasD < 1000 && r_pas_restantsD < r_pasD / 2))
                {
                    r_delaiD += 4;
                }
            }
        }
    }
}

void ver_avancerG()
{
    if (r_pas_restantsG <= 0)
        mot_libreG = 1;
    else
    {
        if (micros() - r_timeG >= r_delaiG)
        {
            r_timeG = micros();
            if (r_hlG == 0)
            {
                digitalWrite(stepPinG, HIGH);
                r_hlG = 1;
            }
            else
            {
                digitalWrite(stepPinG, LOW);
                r_hlG = 0;
                r_pas_restantsG--;
                r_pas_faitsG++;
                if (r_delaiG > 500 && r_pas_faitsG <= r_pasG / 2)
                {
                    r_delaiG -= 4;
                }
                if (r_pas_restantsG < 500 || (r_pasG < 1000 && r_pas_restantsG < r_pasG / 2))
                {
                    r_delaiG += 4;
                }
            }
        }
    }
}

// void avancerMotD1(int pas, char dir){
//   if(dir>0) digitalWrite(dirPin, HIGH);
//   if(dir<0) digitalWrite(dirPin, LOW);
//   for(int x = 0; x < pas; x++)
//   {
//     digitalWrite(stepPin, HIGH);
//     delayMicroseconds(500);
//     digitalWrite(stepPin, LOW);
//     delayMicroseconds(500);
//   }
// }
/*
void avancerMotD2(int pas, char dir){
  if(dir>0) digitalWrite(dirPin, HIGH);
  if(dir<0) digitalWrite(dirPin, LOW);
  if(pas < 1000){
    avancerMotD1(pas, dir);
  }
  else {
    for(int x = 0; x < pas_r; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(vit_min - x*delta_r);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(vit_min - x*dRampe);
    }
    for(int x = 0; x < pas - 2*pas_r; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(vit_max);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(vit_max);
    }
    for(int x = 0; x < pas_r; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(vit_max + x*delta_r);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(vit_max + x*delta_r);
    }
  }
}


void rampe(){
    for(int x = 0; x < 50; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2525 - x*dRampe);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2525 - x*dRampe);
  }
}
*/
