#include <Servo.h>

#include <LedControl.h>

Servo servoG, servoD;

//VAR global
int R, GouDouCouN;
int ob[] = {9, 9, 9, 9, 9, 9}; //stockage des LEDs
int duree_dent = 20;
boolean ok;
//servo

int servoG_home = 10;
int servoD_home = 170;
int servoG_repos = 145;
int servoD_repos = 35;
int servoG_sol = 175;
int servoD_sol = 5;
int servoG_etat, servoD_etat;
int vitesse_servo = 10;

//LED
int DIN = 12;
int CS =  11;
int CLK = 10;

byte Dent_O[8] = {0xC3, 0xC3, 0x00, 0xC3, 0xC3, 0x00, 0xC3, 0xC3};
byte Dent_F[8] = {0x3C, 0x3C, 0x00, 0x3C, 0x3C, 0x00, 0x3C, 0x3C};
byte Dent_N[8] = {0x66, 0x66, 0x00, 0xC3, 0xC3, 0x00, 0x66, 0x66};

byte Dent_1[8] = {0x66, 0x66, 0x00, 0xC3, 0xC3, 0x00, 0x06, 0x06};
byte Dent_2[8] = {0x66, 0x66, 0x00, 0x03, 0x03, 0x00, 0x66, 0x66};
byte Dent_3[8] = {0x06, 0x06, 0x00, 0xC3, 0xC3, 0x00, 0x66, 0x66};
byte Dent_4[8] = {0x66, 0x66, 0x00, 0xC3, 0xC3, 0x00, 0x60, 0x60};
byte Dent_5[8] = {0x66, 0x66, 0x00, 0xC0, 0xC0, 0x00, 0x66, 0x66};
byte Dent_6[8] = {0x60, 0x60, 0x00, 0xC3, 0xC3, 0x00, 0x66, 0x66};

byte C1[8] = {0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00};
byte C2[8] = {0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00};
byte C3[8] = {0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C};

byte Smile[8] = {0x38, 0x24, 0x22, 0x22, 0x22, 0x22, 0x24, 0x38};
byte Point[8] = {0x00, 0x20, 0x50, 0x8D, 0x40, 0x20, 0x00, 0x00};


byte Bisou1[8] = {0x10, 0x38, 0x7C, 0x2C, 0x2C, 0x7C, 0x38, 0x10};
byte Bisou2[8] = {0x38, 0x6C, 0xC6, 0x46, 0x46, 0xC6, 0x6C, 0x38};

LedControl lc = LedControl(DIN, CLK, CS, 0);


//boucle
boolean fin = true;
void setup() {
  bootlc();
   printByte(Point);
  delay(500);
  servoG.attach(5);
  servoD.attach(7);
  servoG.write(servoG_home);
  servoD.write(servoD_home);
  servoG_etat = servoG_home;
  servoD_etat = servoD_home;

  Serial.begin(9600);

  servoG_M(servoG_repos);
  servoD_M(servoD_repos);
}

void loop() {
  bootlc();
  printByte(Smile);
  delay(10);
  for (int i = 0; i < 3; i++) {
    clack();
  };
  ModeNormal();

};
//mode
void ModeNormal() {
  Serial.print("normalMode");
  delay(500);

  clack();
  delay(1000);

  //2 cycles led de 30 sec
  for (int i = 0; i < 2; i++) {

    brossage(5);//6*2*5sec= 60sec
  };
  //pause cracha
  crache();

  //2 cycles led de 24 sec
  for (int i = 0; i < 2; i++) {

    brossage(4);//6*2*4= 48sec / total 108
  };
  //pause cracha
  crache();

  //3 cycles led de 18 sec
  for (int i = 0; i < 3; i++) {


    brossage(3);//6*3*3= 54sec / total 162
  };
  //2 cycles led de 12 sec
  for (int i = 0; i < 2; i++) {
    brossage(2);;//6*2*2= 24 sec / total 186
  };

  //cycle led de 6 sec
  for (int i = 0; i < 2; i++) {
    brossage(1);//6*1*1000= 6 sec / total 198 soit 3min et 18sec
  };
  //cycle led de fin
  crache();
  modeFin();

Serial.println(":D");
}




void crache() {
  lc.clearDisplay(0);
  delay(10);
  printByte(C1);
  delay(2000);
  pieds(2);
  delay(1000);
  printByte(C2);
  delay(500);
  printByte(C3);
  delay(3000);
  printByte(C2);
  delay(500);
  pieds(3);
  printByte(C1);
  delay(2000);
  lc.clearDisplay(0);

}
void clack() {
  printByte(Dent_O);
  delay(500);
  printByte(Dent_F);
  delay(500);

}

void printByte(byte character []){

  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  };
}

void brossage(int duree_dent) {

  ordreBrossage();
  delay(500);
  for (int a = 0; a < 6; a++) {

    switch (ob[a]) {
      case 0:
        pieds(0);
        for (int i = 0; i < duree_dent; i++) {
          printByte(Dent_1);
          delay(500);
          printByte(Dent_N);
          delay(500);


        }
        break;
      case 1:
        pieds(3);
        for (int i = 0; i < duree_dent; i++) {
          printByte(Dent_2);
          delay(500);
          printByte(Dent_N);
          delay(500);

        }
        break;
      case 2:
        pieds(1);
        for (int i = 0; i < duree_dent; i++) {
          printByte(Dent_3);
          delay(500);
          printByte(Dent_N);
          delay(500);

        } break;
      case 3:
        pieds(0);
        for (int i = 0; i < duree_dent; i++) {
          printByte(Dent_4);
          delay(500);
          printByte(Dent_N);
          delay(500);

        } break;
      case 4:
        pieds(3);
        for (int i = 0; i < duree_dent; i++) {
          printByte(Dent_5);
          delay(500);
          printByte(Dent_N);
          delay(500);
        };
        break;
      case 5:
        pieds(1);
        for ( int i = 0; i < duree_dent; i++) {
          printByte(Dent_6);
          delay(500);
          printByte(Dent_N);
          delay(500);
        };
        break;
      default :
        pieds(3);
        printByte(Point);
        delay(5000);
        break;
    };
  };
  pieds(3);
  printByte(Dent_N);
}

void ordreBrossage() {
  //remplit un array de 6 cases avec 012345 en evitant les doublons
  for (int c = 0; c < 6; c++) {
    ok = false;
    while (ok == false) {
      ok = true;

      randHOME();//choisi R
      for (int j = 0; j < c; j++) {
        if (R == ob[j]) {
          ok = false;
        };
      };
    };
    ob[c] = R;
  };
  //print les led allumées
  for (int a = 0; a < 6; a++) {
    Serial.print(ob[a]);
  };
}

void pieds(int GouDouCouN) {
  /*
    0 =gauche
    1=doite
    2=crache
    3=neutre
    4==home
  */

  switch (GouDouCouN) {
    case 0:
      servoG_M(servoG_repos);
      servoD_M(servoD_sol);

      break;
    case 1:
      servoG_M(servoG_sol);
      servoD_M(servoD_repos);
      break;
    case 2:
      servoG_M(servoG_sol);
      servoD_M(servoD_sol);
      break;
    case 3:
      servoG_M(servoG_repos);
      servoD_M(servoD_repos);
      break;
    case 4:
      servoG_M(servoG_home);
      servoD_M(servoD_home);
      break;
    default:
      servoG_M(servoG_home);
      servoD_M(servoD_home);
      break;
  }
}

void servoD_M(int servoD_etat_wanted) {
  // servo == le servo que je veux bouger : servoD ou servoG

  if (servoD_etat < servoD_etat_wanted) {
    for (int i = servoD_etat; i < servoD_etat_wanted; i++) {
      servoD_etat = i;
      servoD.write(i);
      delay(vitesse_servo);
    };
  }
  if (servoD_etat > servoD_etat_wanted) {
    for (int i = servoD_etat; i > servoD_etat_wanted; i--) {
      servoD_etat = i;
      servoD.write(i);
      delay(vitesse_servo);
    };
  }
}

void servoG_M(int servoG_etat_wanted) {
  // servo == le servo que je veux bouger : servoD ou servoG

  if (servoG_etat < servoG_etat_wanted) {
    for (int i = servoG_etat; i < servoG_etat_wanted; i++) {
      servoG_etat = i;
      servoG.write(i);
      delay(vitesse_servo);
    };
  }
  if (servoG_etat > servoG_etat_wanted) {
    for (int i = servoG_etat; i > servoG_etat_wanted; i--) {
      servoG_etat = i;
      servoG.write(i);
      delay(vitesse_servo);
    };
  }
}
void modeFin() {
  clack();
  lc.clearDisplay(0);
  delay(10);
  pieds(4);

  // metttre retour ICI

  delay(500);
  printByte(Bisou1);
  delay(500);
  printByte(Bisou2);
  delay(1000);
  lc.clearDisplay(0);
  delay(10);
  while (fin) {

  };
}
void randHOME() {
  int randa1 = analogRead(0);
  int randa2 = (randa1 - (((int) (randa1 / 10))) * 10);
  R = map(randa2, 0, 9, 0, 5);
  ;
}

void bootlc() {
  lc.shutdown(0, false);
  delay(50);  //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 10);     // Set the brightness to maximum value
  delay(50);
  lc.clearDisplay(0);         // and clear the display
  // printByte(Point);
  delay(50);
};
