#include<LiquidCrystal_I2C.h>
#include<Servo.h>

Servo mservo;
LiquidCrystal_I2C lcd (0x27, 16, 2);

int trigDepan = 2;//untuk servo sehinggga tidak crash
int echoDepan = 11;

int trigKiriDepan = 12;
int echoKiriDepan = 13;

int trigKiriBelakang = 9;
int echoKiriBelakang = 4;

int trigBelakang = 5;
int echoBelakang = 6;

//int pinBuz = 1;
int ledPinMerah = 13;
int ledPinHijau = 12;

int enA = 3;
int in1 = 8;
int in2 = 7;

int drsdp;
int drskirdep;
int drskirbel;
int drsbel;
float jrkdp;
float jrkkirdep;
float jrkkirbel;
float jrkbel;

//Rule Base
float min1r1, min2r1;
float min1r2, min2r2;
float min1r3, min2r3;
float min1r4, min2r4;
float min1r5, min2r5;
float min1r6, min2r6;
float min1r7, min2r7;
float min1r8, min2r8;
float min1r9, min2r9;
float min1r10, min2r10;
float min1r11, min2r11;
float min1r12, min2r12;
float min1r13, min2r13;
float min1r14, min2r14;
float min1r15, min2r15;
float min1r16, min2r16;
float min1r17, min2r17;
float min1r18, min2r18;
float min1r19, min2r19;
float min1r20, min2r20;
float min1r21, min2r21;
float min1r22, min2r22;
float min1r23, min2r23;
float min1r24, min2r24;
float min1r25, min2r25;
float min1r26, min2r26;
float min1r27, min2r27;
float min1r28, min2r28;
float min1r29, min2r29;
float min1r30, min2r30;
float min1r31, min2r31;
float min1r32, min2r32;
float min1r33, min2r33;
float min1r34, min2r34;

float defuzz;
float Mtot, Atot;



float jarakDepan[3];
float jarakBelakang[3];
float jarakKiriDepan[3];
float jarakKiriBelakang[3];


float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9, rule10,
      rule11, rule12, rule13, rule14, rule15, rule16, rule17, rule18, rule19, rule20,
      rule21, rule22, rule23, rule24, rule25, rule26, rule27, rule28, rule29, rule30,
      rule31, rule32, rule33, rule34, rule35;
bool parkirS = false;

void setup() {
  Serial.begin(9600);
  mservo.attach(10);
  lcd.begin();
  lcd.backlight();
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //  delay(2000);
  //  analogWrite(enA, 160);
  //  digitalWrite(in1, HIGH);
  //  digitalWrite(in2, LOW);
  //
  //  if (jrkdp <= 40) {
  lcd.setCursor(0, 0);
  lcd.print("Sistem Aktif.......");
  mservo.write(75);
  delay(2000);
  analogWrite(enA, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(2000);

  Defuzzy();


  analogWrite(enA, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  //  if (jrkdp <= 30) {
  //    analogWrite(enA, 0);
  //    digitalWrite(in1, LOW);
  //    digitalWrite(in2, LOW);
  //    mservo.write(defuzz);
  //  }

}

void loop() {

  ultraDepan();
  ultraKiriDepan();
  ultraBelakang();
  ultraKiriBelakang();
  Serial.print("JarakDepan :");
  Serial.println(jrkdp);
  Serial.print("JarakBelakang :");
  Serial.println(jrkbel);
  Serial.print("JarakKiriDepan :");
  Serial.println(jrkkirdep);
  Serial.print("JarakKiriBelakang :");
  Serial.println(jrkkirbel);
  Defuzzy();

  if (jrkdp <= 40) {
    analogWrite(enA, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(0.5);
    analogWrite(enA, 0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    mservo.write(defuzz);
  } else

    if (jrkkirdep >= 15 || jrkkirbel >= 15) {

      analogWrite(enA, 255);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      delay(0.5);

//      analogWrite(enA, 140);
//      digitalWrite(in1, HIGH);
//      digitalWrite(in2, LOW);
//      delay(10);



      analogWrite(enA, 0);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      delay(1000);
      mservo.write(70);
      delay(200);
      mservo.write(defuzz);
      delay(50);
      //mundur
      analogWrite(enA, 180);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      delay(50);

      
      if (jrkbel <= 25) {
        analogWrite(enA, 255);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        delay(0.5);
    
        analogWrite(enA, 0);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        delay(1000);
        mservo.write(120);
        delay(50);
//        mservo.write(defuzz);
        analogWrite(enA, 160);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        delay(300);
        if (jrkbel <= 10) {
          
          analogWrite(enA, 0);
          digitalWrite(in1, LOW);
          digitalWrite(in2, LOW);
          delay(1000);
          mservo.write(70);
//          mservo.write(defuzz);

          analogWrite(enA, 140);
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
          delay(50);

          if (jrkdp <= 15) {
            analogWrite(enA, 0);
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            delay(1000);
            mservo.write(70);
//            mservo.write(defuzz);
            analogWrite(enA, 140);
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);

          }
        }
      }
      //      //stop

      //
      //
      //      //kanan
      //      mservo.write(defuzz);
      //      Serial.print("KANAN :");
      //      Serial.println(defuzz);
      //      analogWrite(enA, 160);
      //      digitalWrite(in1, LOW);
      //      digitalWrite(in2, HIGH);
      //      delay(200);
      //
      //      //stop
      //      analogWrite(enA, 255);
      //      digitalWrite(in1, HIGH);
      //      digitalWrite(in2, LOW);
      //      delay(0.5);
      //      analogWrite(enA, 0);
      //      digitalWrite(in1, LOW);
      //      digitalWrite(in2, LOW);
      //      delay(1000);
      //
      //      //      lurus
      //      mservo.write(defuzz);
      //
      //      Serial.print("LURUS :");
      //      Serial.println(defuzz);
      //
      //      analogWrite(enA, 160);
      //      digitalWrite(in1, HIGH);
      //      digitalWrite(in2, LOW);
      //      delay(200);

      if (jrkdp <= jrkbel) {
        analogWrite(enA, 255);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        delay(0.5);

        analogWrite(enA, 0);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        mservo.write(70);
        lcd.print("Parkir Selesai .....");
      }

    }

  lcd.clear();
  lcd.print("Parkir Ditemukan");
  //  }
  //     fuzzyJarakDepan();
  //    fuzzyJarakBelakang();
  //    fuzzyJarakKiriDepan();
  //  fuzzyJarakKiriBelakang();
  //maju();
}

void fuzzyJarakDepan() {
  ultraDepan();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Jarak awal :");
  //  lcd.print(jrkdp);
  //dekat
  if (jrkdp <= 20)
  {
    jarakDepan[0] = 1;
  }
  else if (jrkdp >= 20 && jrkdp <= 30)
  {
    jarakDepan[0] = (30 - jrkdp) / (30 - 20);
  }
  else if (jrkdp >= 30) {
    jarakDepan[0] = 0;
  }

  //  sedang
  if (jrkdp <= 20 || jrkdp >= 40)
  {
    jarakDepan[1] = 0;
  }
  else if (jrkdp >= 20 && jrkdp <= 30)
  {
    jarakDepan[1] = (jrkdp - 20) / (30 - 20);
  }
  else if (jrkdp >= 30 && jrkdp <= 40)
  {
    jarakDepan[1] = (40 - jrkdp) / (40 - 20);
  }

  //  jauh
  if (jrkdp <= 30)
  {
    jarakDepan[2] = 0;
  }
  else if (jrkdp >= 30 && jrkdp <= 40)
  {
    jarakDepan[2] = (jrkdp - 30) / (40 - 30);
  }
  else if (jrkdp >= 40)
  {
    jarakDepan[2] = 1;
  }

  //  lcd.setCursor(0, 1);
  //  lcd.print("nilai fuzzy Dekat:");
  //  lcd.println(jarakDepan[0]);
  //  lcd.print("nilai fuzzy Sedang:");
  //  lcd.println(jarakDepan[1]);
  //  lcd.print("nilai fuzzy Jauh :");
  //  lcd.println(jarakDepan[1]);
}

void fuzzyJarakBelakang() {
  ultraBelakang();
  lcd.setCursor(0, 0);
  lcd.print("jarak  :");
  lcd.print(jrkbel);
  //dekat
  if (jrkbel <= 20)
  {
    jarakBelakang[0] = 1;
  }
  else if (jrkbel >= 20 && jrkbel <= 30)
  {
    jarakBelakang[0] = (30 - jrkbel) / (30 - 20);
  }
  else if (jrkbel >= 30) {
    jarakBelakang[0] = 0;
  }

  //  sedang
  if (jrkbel <= 20 || jrkbel >= 40)
  {
    jarakBelakang[1] = 0;
  }
  else if (jrkbel >= 20 && jrkbel <= 30)
  {
    jarakBelakang[1] = (jrkbel - 20) / (30 - 20);
  }
  else if (jrkbel >= 30 && jrkbel <= 40)
  {
    jarakBelakang[1] = (40 - jrkbel) / (40 - 20);
  }

  //  jauh
  if (jrkbel <= 30)
  {
    jarakBelakang[2] = 0;
  }
  else if (jrkbel >= 30 && jrkbel <= 40)
  {
    jarakBelakang[2] = (jrkbel - 30) / (40 - 30);
  }
  else if (jrkbel >= 40)
  {
    jarakBelakang[2] = 1;
  }
  lcd.setCursor(0, 1);
  lcd.print("Nilai Fuzzy Dekat:");
  lcd.println(jarakBelakang[0]);
  lcd.print("Nilai Fuzzy Sedang:");
  lcd.println(jarakBelakang[1]);
  lcd.print("Nilai Fuzzy Jauh:");
  lcd.println(jarakBelakang[2]);
}

void fuzzyJarakKiriDepan() {
  ultraKiriDepan();
  //lcd.setCursor(0, 0);
  //lcd.print("jarak");
  //lcd.print(jrkkirdep);
  //dekat
  if (jrkkirdep <= 10)
  {
    jarakKiriDepan[0] = 1;
  }
  else if (jrkkirdep >= 10 && jrkkirdep <= 15)
  {
    jarakKiriDepan[0] = (15 - jrkkirdep) / (15 - 10);
  }
  else if (jrkkirdep >= 15) {
    jarakKiriDepan[0] = 0;
  }

  //  sedang
  if (jrkkirdep <= 10 || jrkkirdep >= 20)
  {
    jarakKiriDepan[1] = 0;
  }
  else if (jrkkirdep >= 10 && jrkkirdep <= 15)
  {
    jarakKiriDepan[1] = (jrkkirdep - 10) / (15 - 10);
  }
  else if (jrkkirdep >= 15 && jrkkirdep <= 20)
  {
    jarakKiriDepan[1] = (20 - jrkkirdep) / (20 - 10);
  }

  //  jauh
  if (jrkkirdep <= 15)
  {
    jarakKiriDepan[2] = 0;
  }
  else if (jrkkirdep >= 15 && jrkkirdep <= 20)
  {
    jarakKiriDepan[2] = (jrkkirdep - 15) / (20 - 15);
  }
  else if (jrkkirdep >= 20)
  {
    jarakKiriDepan[2] = 1;
  }

  // lcd.setCursor(0, 1);
  //lcd.print("Nilai Fuzzy :");
  //lcd.println(jarakKiriDepan[1]);
  //Serial.println(jarakKiriDepan[2]);
}

void fuzzyJarakKiriBelakang() {
  ultraKiriBelakang();
  // lcd.setCursor(0, 0);
  // lcd.print("jarak");
  // lcd.print(jrkkirbel);
  //dekat
  if (jrkkirbel <= 10)
  {
    jarakKiriBelakang[0] = 1;
  }
  else if (jrkkirbel >= 10 && jrkkirbel <= 15)
  {
    jarakKiriBelakang[0] = (15 - jrkkirbel) / (15 - 10);
  }
  else if (jrkkirbel >= 15) {
    jarakKiriBelakang[0] = 0;
  }

  //  sedang
  if (jrkkirbel <= 10 || jrkkirbel >= 20)
  {
    jarakKiriBelakang[1] = 0;
  }
  else if (jrkkirbel >= 10 && jrkkirbel <= 15)
  {
    jarakKiriBelakang[1] = (jrkkirbel - 10) / (15 - 10);
  }
  else if (jrkkirbel >= 15 && jrkkirbel <= 20)
  {
    jarakKiriBelakang[1] = (20 - jrkkirbel) / (20 - 10);
  }

  //  jauh
  if (jrkkirbel <= 15)
  {
    jarakKiriBelakang[2] = 0;
  }
  else if (jrkkirbel >= 15 && jrkkirbel <= 20)
  {
    jarakKiriBelakang[2] = (jrkkirbel - 15) / (20 - 15);
  }
  else if (jrkkirbel >= 20)
  {
    jarakKiriBelakang[2] = 1;
  }

  //lcd.setCursor(0, 1);
  // lcd.print("Nilai Fuzzy :");
  // Serial.println(jarakKiriBelakang[1]);
  //lcd.print(jarakKiriBelakang[2]);
}

//Hitung Rule

//Hitung Rule
void RuleEva() {
  fuzzyJarakDepan();
  fuzzyJarakBelakang();
  fuzzyJarakKiriDepan();
  fuzzyJarakKiriBelakang();


  Serial.println("-- fuzzy Depan --");
  Serial.print("DEKAT :");
  Serial.println(jarakDepan[0]);
  Serial.print("SEDANG  :");
  Serial.println(jarakDepan[1]);
  Serial.print("JAUH  :");
  Serial.println(jarakDepan[2]);
  Serial.println("");


  Serial.println("-- fuzzy Belakang --");
  Serial.print("DEKAT :");
  Serial.println(jarakBelakang[0]);
  Serial.print("SEDANG  :");
  Serial.println(jarakBelakang[1]);
  Serial.print("JAUH  :");
  Serial.println(jarakBelakang[2]);
  Serial.println("");


  Serial.println("-- fuzzy Kiri Depan --");
  Serial.print("DEKAT :");
  Serial.println(jarakKiriDepan[0]);
  Serial.print("SEDANG  :");
  Serial.println(jarakKiriDepan[1]);
  Serial.print("JAUH  :");
  Serial.println(jarakKiriDepan[2]);
  Serial.println("");

  Serial.println("-- fuzzy Kiri Belakang --");
  Serial.print("DEKAT :");
  Serial.println(jarakKiriBelakang[0]);
  Serial.print("SEDANG  :");
  Serial.println(jarakKiriBelakang[1]);
  Serial.print("JAUH  :");
  Serial.println(jarakKiriBelakang[2]);
  Serial.println("");


  //fungsi implikasi

  //RULE1-->kiri
  min1r1 = min(jarakDepan[0], jarakBelakang[0]);
  min2r1 = min(jarakKiriDepan[0], jarakKiriBelakang[0]);
  rule1 = min(min1r1, min2r1);
  Serial.print("a1  :");
  Serial.println(rule1);

  //RULE2-->kiri
  min1r2 = min(jarakDepan[1], jarakBelakang[1]);
  min2r2 = min(jarakKiriDepan[0], jarakKiriBelakang[0]);
  rule2 = min(min1r2, min2r2);
  Serial.print("a2  :");
  Serial.println(rule2);

  //RULE3-->kanan
  min1r3 = min(jarakDepan[1], jarakBelakang[1]);
  min2r3 = min(jarakKiriDepan[1], jarakKiriBelakang[1]);
  rule3 = min(min1r3, min2r3);
  Serial.print("a3  :");
  Serial.println(rule3);

  //RULE4-->kanan
  min1r4 = min(jarakDepan[2], jarakBelakang[2]);
  min2r4 = min(jarakKiriDepan[2], jarakKiriBelakang[1]);
  rule4 = min(min1r4, min2r4);
  Serial.print("a4  :");
  Serial.println(rule4);

  //RULE5-->kanan
  min1r5 = min(jarakDepan[2], jarakBelakang[2]);
  min2r5 = min(jarakKiriDepan[2], jarakKiriBelakang[2]);
  rule5 = min(min1r5, min2r5);
  Serial.print("a5  :");
  Serial.println(rule5);

  //RULE6-->kiri
  min1r6 = min(jarakDepan[2], jarakBelakang[0]);
  min2r6 = min(jarakKiriDepan[1], jarakKiriBelakang[0]);
  rule6 = min(min1r6, min2r6);
  Serial.print("a6  :");
  Serial.println(rule6);

  //RULE7-->kanan
  min1r7 = min(jarakDepan[2], jarakBelakang[2]);
  min2r7 = min(jarakKiriDepan[2], jarakKiriBelakang[0]);
  rule7 = min(min1r7, min2r7);
  Serial.print("a7  :");
  Serial.println(rule7);

  //RULE8-->tetap
  min1r8 = min(jarakDepan[0], jarakBelakang[0]);
  min2r8 = min(jarakKiriDepan[1], jarakKiriBelakang[0]);
  rule8 = min(min1r8, min2r8);
  Serial.print("a8  :");
  Serial.println(rule8);

  //RULE9-->tetap
  min1r9 = min(jarakDepan[1], jarakBelakang[1]);
  min2r9 = min(jarakKiriDepan[1], jarakKiriBelakang[1]);
  rule9 = min(min1r9, min2r9);
  Serial.print("a9  :");
  Serial.println(rule9);

  //RULE10-->tetap
  min1r10 = min(jarakDepan[2], jarakBelakang[2]);
  min2r10 = min(jarakKiriDepan[0], jarakKiriBelakang[0]);
  rule10 = min(min1r10, min2r10);
  Serial.print("a10 :");
  Serial.println(rule10);

  //RULE11-->tetap
  min1r11 = min(jarakDepan[2], jarakBelakang[2]);
  min2r11 = min(jarakKiriDepan[0], jarakKiriBelakang[2]);
  rule11 = min(min1r11, min2r11);
  Serial.print("a11 :");
  Serial.println(rule11);

  //RULE12-->tetap
  min1r12 = min(jarakDepan[1], jarakBelakang[1]);
  min2r12 = min(jarakKiriDepan[1], jarakKiriBelakang[0]);
  rule12 = min(min1r12, min2r12);
  Serial.print("a12 :");
  Serial.println(rule12);

  //RULE13-->tetap
  min1r13 = min(jarakDepan[1], jarakBelakang[1]);
  min2r13 = min(jarakKiriDepan[2], jarakKiriBelakang[2]);
  rule13 = min(min1r13, min2r13);
  Serial.print("a13 :");
  Serial.println(rule13);

  //RULE14-->tetap
  min1r14 = min(jarakDepan[2], jarakBelakang[2]);
  min2r14 = min(jarakKiriDepan[1], jarakKiriBelakang[0]);
  rule14 = min(min1r14, min2r14);
  Serial.print("a14 :");
  Serial.println(rule14);

  //RULE15-->tetap
  min1r15 = min(jarakDepan[2], jarakBelakang[1]);
  min2r15 = min(jarakKiriDepan[2], jarakKiriBelakang[0]);
  rule15 = min(min1r15, min2r15);
  Serial.print("a15 :");
  Serial.println(rule15);

  //RULE16-->tetap
  min1r16 = min(jarakDepan[1], jarakBelakang[1]);
  min2r16 = min(jarakKiriDepan[0], jarakKiriBelakang[1]);
  rule16 = min(min1r16, min2r16);
  Serial.print("a16 :");
  Serial.println(rule16);

  //RULE17-->kanan
  min1r17 = min(jarakDepan[2], jarakBelakang[1]);
  min2r17 = min(jarakKiriDepan[2], jarakKiriBelakang[1]);
  rule17 = min(min1r17, min2r17);
  Serial.print("a17 :");
  Serial.println(rule17);

  //RULE18-->kanan
  min1r18 = min(jarakDepan[0], jarakBelakang[0]);
  min2r18 = min(jarakKiriDepan[2], jarakKiriBelakang[1]);
  rule18 = min(min1r18, min2r18);
  Serial.print("a18 :");
  Serial.println(rule18);

  //RULE19-->tetap
  min1r19 = min(jarakDepan[0], jarakBelakang[0]);
  min2r19 = min(jarakKiriDepan[2], jarakKiriBelakang[2]);
  rule19 = min(min1r19, min2r19);
  Serial.print("a19 :");
  Serial.println(rule19);


  //RULE20-->tetap
  min1r20 = min(jarakDepan[1], jarakBelakang[2]);
  min2r20 = min(jarakKiriDepan[2], jarakKiriBelakang[0]);
  rule20 = min(min1r20, min2r20);
  Serial.print("a20 :");
  Serial.println(rule20);

  //RULE21-->tetap
  min1r21 = min(jarakDepan[1], jarakBelakang[2]);
  min2r21 = min(jarakKiriDepan[1], jarakKiriBelakang[1]);
  rule21 = min(min1r21, min2r21);
  Serial.print("a21 :");
  Serial.println(rule21);

  //RULE22-->tetap
  min1r22 = min(jarakDepan[0], jarakBelakang[1]);
  min2r22 = min(jarakKiriDepan[1], jarakKiriBelakang[1]);
  rule22 = min(min1r22, min2r22);
  Serial.print("a22 :");
  Serial.println(rule22);

  //RULE23-->tetap
  min1r23 = min(jarakDepan[1], jarakBelakang[1]);
  min2r23 = min(jarakKiriDepan[2], jarakKiriBelakang[0]);
  rule23 = min(min1r23, min2r23);
  Serial.print("a23 :");
  Serial.println(rule23);

  //RULE24-->tetap
  min1r24 = min(jarakDepan[0], jarakBelakang[2]);
  min2r24 = min(jarakKiriDepan[2], jarakKiriBelakang[0]);
  rule24 = min(min1r24, min2r24);
  Serial.print("a24 :");
  Serial.println(rule24);

  //RULE24-->tetap
  min1r25 = min(jarakDepan[2], jarakBelakang[0]);
  min2r25 = min(jarakKiriDepan[0], jarakKiriBelakang[0]);
  rule25 = min(min1r25, min2r25);
  Serial.print("a25 :");
  Serial.println(rule25);

  min1r26 = min(jarakDepan[2], jarakBelakang[0]);
  min2r26 = min(jarakKiriDepan[2], jarakKiriBelakang[2]);
  rule26 = min(min1r26, min2r26);
  Serial.print("a26 :");
  Serial.println(rule26);

  min1r27 = min(jarakDepan[2], jarakBelakang[0]);
  min2r27 = min(jarakKiriDepan[0], jarakKiriBelakang[2]);
  rule27 = min(min1r27, min2r27);
  Serial.print("a27 :");
  Serial.println(rule27);

  min1r28 = min(jarakDepan[2], jarakBelakang[2]);
  min2r28 = min(jarakKiriDepan[1], jarakKiriBelakang[2]);
  rule28 = min(min1r28, min2r28);
  Serial.print("a28 :");
  Serial.println(rule28);

  min1r29 = min(jarakDepan[2], jarakBelakang[2]);
  min2r29 = min(jarakKiriDepan[0], jarakKiriBelakang[2]);
  rule29 = min(min1r29, min2r29);
  Serial.print("a29 :");
  Serial.println(rule29);

  min1r30 = min(jarakDepan[0], jarakBelakang[0]);
  min2r30 = min(jarakKiriDepan[0], jarakKiriBelakang[2]);
  rule30 = min(min1r30, min2r30);
  Serial.print("a30 :");
  Serial.println(rule30);

  min1r31 = min(jarakDepan[0], jarakBelakang[1]);
  min2r31 = min(jarakKiriDepan[0], jarakKiriBelakang[2]);
  rule31 = min(min1r31, min2r31);
  Serial.print("a31 :");
  Serial.println(rule31);

  min1r32 = min(jarakDepan[0], jarakBelakang[2]);
  min2r32 = min(jarakKiriDepan[0], jarakKiriBelakang[2]);
  rule32 = min(min1r32, min2r32);
  Serial.print("a32 :");
  Serial.println(rule32);

  min1r33 = min(jarakDepan[0], jarakBelakang[2]);
  min2r33 = min(jarakKiriDepan[0], jarakKiriBelakang[0]);
  rule33 = min(min1r33, min2r33);
  Serial.print("a33 :");
  Serial.println(rule33);

  min1r34 = min(jarakDepan[0], jarakBelakang[2]);
  min2r34 = min(jarakKiriDepan[2], jarakKiriBelakang[2]);
  rule34 = min(min1r34, min2r34);
  Serial.print("a34 :");
  Serial.println(rule34);
}


void Defuzzy() {
  RuleEva();
  float kiri = 20;
  //  lcd.setCursor(0,0);
  //  lcd.print("kiri :");
  //  lcd.print(kiri);
  float lurus = 70;
  // lcd.setCursor(0,0);
  //  lcd.print("kiri :");
  //  lcd.print(lurus);
  float kanan = 120;
  // lcd.setCursor(0,1);
  //  lcd.print("kiri :");
  // lcd.print(kanan);
  // metode sugeno (weighted average)
  Mtot = (rule1 * lurus)
         + (rule2 * lurus)
         + (rule3 * lurus)
         + (rule4 * kanan)
         + (rule5 * kiri)
         + (rule6 * kanan)
         + (rule7 * lurus)
         + (rule8 * kanan)
         + (rule9 * lurus)
         + (rule10 * kiri)
         + (rule11 * kiri)
         + (rule12 * lurus)
         + (rule13 * kiri)
         + (rule14 * kanan)
         + (rule15 * lurus)
         + (rule16 * kiri)
         + (rule17 * kanan)
         + (rule18 * kanan)
         + (rule19 * lurus)
         + (rule20 * kanan)
         + (rule21 * lurus)
         + (rule22 * lurus)
         + (rule23 * kanan)
         + (rule24 * kanan)
         + (rule25 * kanan)
         + (rule26 * kanan)
         + (rule27 * kanan)
         + (rule28 * kanan)
         + (rule29 * kiri)
         + (rule30 * lurus)
         + (rule31 * lurus)
         + (rule32 * kanan)
         + (rule33 * kiri)
         + (rule34 * lurus);

  Serial.print("Momen Total :");
  Serial.println(Mtot);

  Atot = (rule1 + rule2 + rule3 + rule4 + rule5 + rule6 + rule7 + rule8 + rule9 + rule10 +
          rule11 + rule12 + rule13 + rule14 + rule15 + rule16 + rule17 + rule18 + rule19 + rule20 + rule21 + rule22
          + rule23 + rule24 + rule25 + rule26 + rule27 + rule28 + rule29 + rule30 + rule31 + rule32 + rule33 + rule34);
  Serial.print("Luas Total  :");
  Serial.println(Atot);

  //inferensi fungsi keanggotaan output
  defuzz = Mtot / Atot;
  Serial.print("Hasil defuzzi :");
  Serial.println(defuzz);
  Serial.println("-------------");
  if (defuzz == 20) {
    Serial.println("KIRI");
  } else if (defuzz == 70) {
    Serial.println("LURUS");
  } else if (defuzz == 120) {
    Serial.println("KANAN");
  }
}

//ultrasonik
void ultraDepan() {
  pinMode(trigDepan, OUTPUT);
  digitalWrite(trigDepan, LOW);
  delayMicroseconds(2);
  digitalWrite(trigDepan, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigDepan, LOW);
  pinMode(echoDepan, INPUT);
  drsdp = pulseIn(echoDepan, HIGH);
  jrkdp = (drsdp / 2) / 29.1;
  //  lcd.setCursor(0, 0);
  //  lcd.print("Jarak: ");
  //  lcd.print(jrkdp);
  //  lcd.print("  cm");
  //  delay(10);
  //  lcd.setCursor(0, 1);
  //  lcd.print("Jarak: ");
  //  lcd.print(" ");
}

void ultraBelakang() {
  pinMode(trigBelakang, OUTPUT);
  digitalWrite(trigBelakang, LOW);
  delayMicroseconds(2);
  digitalWrite(trigBelakang, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigBelakang, LOW);
  pinMode(echoBelakang, INPUT);
  drsbel = pulseIn(echoBelakang, HIGH);
  jrkbel = (drsbel / 2) / 29.1;
  //  lcd.setCursor(0, 0);
  //  lcd.print("Jarak: ");
  //  lcd.print(jrkbel);
  //  lcd.print("  cm");
  //  delay(10);
  //  lcd.setCursor(0, 1);
  //  lcd.print("Jarak: ");
  //  lcd.print(" ");
}

void ultraKiriDepan() {
  pinMode(trigKiriDepan, OUTPUT);
  digitalWrite(trigKiriDepan, LOW);
  delayMicroseconds(2);
  digitalWrite(trigKiriDepan, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigKiriDepan, LOW);
  pinMode(echoKiriDepan, INPUT);
  drskirdep = pulseIn(echoKiriDepan, HIGH);
  jrkkirdep = (drskirdep / 2) / 29.1;
  //  lcd.setCursor(0, 0);
  //  lcd.print("Jarak: ");
  //  lcd.print(jrkkirdep);
  //  lcd.print("  cm");
  //  delay(10);
  //  lcd.setCursor(0, 1);
  //  lcd.print("Jarak: ");
  //  lcd.print(" ");
}

void ultraKiriBelakang() {
  pinMode(trigKiriBelakang, OUTPUT);
  digitalWrite(trigKiriBelakang, LOW);
  delayMicroseconds(2);
  digitalWrite(trigKiriBelakang, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigKiriBelakang, LOW);
  pinMode(echoKiriBelakang, INPUT);
  drskirbel = pulseIn(echoKiriBelakang, HIGH);
  jrkkirbel = (drskirbel / 2) / 29.1;
  //  lcd.setCursor(0, 0);
  //  lcd.print("Jarak: ");
  //  lcd.print(jrkkirbel);
  //  lcd.print("  cm");
  //  delay(10);
  //  lcd.setCursor(0, 1);
  //  lcd.print("Jarak: ");
  //  lcd.print(" ");
}

void maju() {
  analogWrite(enA, 160);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  parkirS = true;
}

void mundur() {
  analogWrite(enA, 180);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //  pushBuz();
}

void berhenti() {
  analogWrite(enA, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

//void pushBuz() {
//  tone(pinBuz,450);
//  delay(500);
//  noTone(pinBuz);
//  delay(500);
//}
