const int soundPin = 22;
const int BTN = 26;
const int solenoidPin = 27;
const int TimeWaiting = 5000;
const int rumblePin = 23;
unsigned long LooptimeElasped;
unsigned long LooptimeLast;
unsigned long LooptimeCurrent;
int cycle = 15000;
int result;
int SAMPLE_TIME = 200;
int clapInx = 0;
int clapChecked[6];
int ADDRESS;
int SumUpValue = 0;
bool allowTrig = false;
bool solenoidOpen = false;
//bool knockAllow = false;
int averageValue = 0;
volatile unsigned long TRUE;
volatile unsigned long TEST;
unsigned long timer = 0;
unsigned long timer4 = 0;
unsigned long timeCurrent;
unsigned long timeLast = 0;
unsigned long timer5 = 0;
unsigned long timer6 = 0;
unsigned long averageCounting = 0;
unsigned long timeElapsed;
unsigned long LooptimeLastPass = 0;
unsigned long realTimeCurrent = 0;
unsigned long realTimeLast = 0;
unsigned long realTimeElasped = 0;
unsigned long REAL_TIME = 200;
unsigned long durationLast = 0;
unsigned long durationCurrent;
unsigned long durationElapsed = 0;
int accecptableTime = 2000;
int averageTestVal = 0;
bool passEqually = false;
int Number_Of_Claps = 0;
int TimingArray[6];
int TimingTestArray[6];
int realbuffer;
int realValueSelf;
int realClapCount = 0;
unsigned long duration;
const int MIN_SENS = 350;
const int MAX_SENS = 900;
const int MIN_SENS_B = 901;
const int MAX_SENS_B = 1100;
const int KNOCK_MIN = 500;
const int KNOCK_MAX = 800;

int accecptableVal = 250;
int NewArray[0];
int clapCount = 0;
int clapArray[6];
int distance;
int SumUpTestVal = 0;
int samplebuffer;
int rumblebuffer;
int rumbleValue = 0;
int valueCheck;
const int echo = 18;
int valueSelf;
volatile int realvalue;
const int trig = 25;
int indexCompared = 0;
int MEASURE;
int TEST_MEASURE;

void setup() {
  pinMode(soundPin, INPUT);
  pinMode(rumblePin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(BTN, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(soundPin), timeInterrupt, FALLING);
}
void runmysensor() {
  if (millis() - timer4 > 250) {
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    //Serial.println(distance);
    timer4 = millis();
  }
}

void setbackcounter() {
  if (digitalRead(BTN) == 0) {
    clapCount = 0;
  }
}
void loop() {

  runmysensor();
  setbackcounter();
  while (digitalRead(BTN) == 1) {
    LooptimeLast = 0;
    averageTestVal = 0;
    SumUpTestVal = 0;
    passEqually = false;
    realClapCount = 0;
    timeCurrent = millis();
    LooptimeCurrent = millis();
    durationCurrent = millis();
    timeElapsed = timeCurrent - timeLast;
    LooptimeElasped = LooptimeCurrent - LooptimeLastPass;
    runmysensor();
    if (LooptimeElasped > cycle) {
      for (int resets = 0; resets <= clapCount; resets++) {
        clapArray[resets] = 0;
        TimingArray[resets] = 0;
      }
      clapCount = 0;
      Number_Of_Claps = 0;
      //knockAllow = false;
      rumblebuffer = 0;
      SumUpValue = 0;
      MEASURE = 0;
      Serial.println("Pass lock resets");
      LooptimeLastPass = LooptimeCurrent;
    }
    // if (clapCount > 6) {
    //   for (int resets = 0; resets <= clapCount; resets++) {
    //     clapArray[resets] = 0;
    //     TimingArray[resets] = 0;
    //   }
    //   clapCount = 0;
    //   Number_Of_Claps = 0;
    //   SumUpValue = 0;
    //   MEASURE = 0;
    //   Serial.println("Pass lock resets");
    //   LooptimeLastPass = LooptimeCurrent;
    // }
    if (LooptimeElasped >= TimeWaiting && allowTrig == true) {
      averageValue = SumUpValue / Number_Of_Claps;
      for (int averageIndex = 0; averageIndex <= Number_Of_Claps; averageIndex++) {
        clapArray[averageIndex] = averageValue;
      }
      Serial.println(averageValue);
      Serial.println("mainIntensity");
      // Number_Of_Claps = 0;
      SumUpValue = 0;
      rumblebuffer = 0;
      samplebuffer = 0;
      allowTrig = false;
    }

    if (digitalRead(soundPin) == 0) {
      samplebuffer++;
    }
    // if (digitalRead(rumblePin) == 0) {
    //   rumblebuffer++;
    // }
    // if (rumblebuffer >= 400) {
    //   knockAllow = true;
    // }


    if (timeElapsed > SAMPLE_TIME) {
      if ((samplebuffer >= MIN_SENS && samplebuffer <= MAX_SENS && clapCount <= 5 ) || (samplebuffer >= MIN_SENS_B && samplebuffer <= MAX_SENS_B && clapCount <= 5 )) {
        if (samplebuffer >= MIN_SENS_B && samplebuffer <= MAX_SENS_B) {
          samplebuffer = 900;
        }
        Serial.println(rumblebuffer);
        valueCheck = samplebuffer;
        realvalue = valueCheck;
        allowTrig = true;
        SumUpValue += realvalue;
        LooptimeLastPass = millis();
        //Serial.println(valueCheck);
        //Serial.print(" ");
        //Serial.print(realvalue);
        //Serial.print(TRUE);
        Serial.print(realvalue);
        Serial.println(" intensity");
        if (clapCount == 0) {
          TRUE = 0;
          durationLast = millis();
        }
        TimingArray[clapCount] = TRUE;
        Serial.print(TimingArray[clapCount]);
        Serial.println(" duration");
        clapCount += 1;
        if (clapCount != 0) {
          Number_Of_Claps = clapCount;
          //Serial.println(Number_Of_Claps);
        }
        Serial.println(clapCount);
        MEASURE = clapCount;
        ADDRESS = 69;
        //Serial.println(clapCount);
      //  knockAllow = false;
      }
      samplebuffer = 0;
      rumblebuffer = 0;
      timeLast = timeCurrent;
    }
  }




  while (distance <= 25 && digitalRead(BTN) == 0) {
    LooptimeLastPass = 0;
    averageValue = 0;
    allowTrig = false;
    runmysensor();
    setbackcounter();
    durationCurrent = millis();
    realTimeCurrent = millis();
    LooptimeCurrent = millis();
    realTimeElasped = realTimeCurrent - realTimeLast;
    LooptimeElasped = LooptimeCurrent - LooptimeLast;
    if (LooptimeElasped > cycle) {
      for (int resets = 0; resets < realClapCount; resets++) {
        TimingTestArray[resets] = 0;
        clapChecked[resets] = 0;
      }
      Serial.println("resets Counter");
      realbuffer = 0;
      realClapCount = 0;
      SumUpTestVal = 0;
      TEST_MEASURE = 0;
      rumblebuffer = 0;
      LooptimeLast = LooptimeCurrent;
     // knockAllow = false;
    }
    if (digitalRead(soundPin) == 0) {
      realbuffer++;
    }
    // if (digitalRead(rumblePin) == 0) {
    //   rumblebuffer++;
    // }
    // if (rumblebuffer >= 400) {
    //   knockAllow = true;
    // }
    if (realTimeElasped >= REAL_TIME) {
      valueSelf = realbuffer;
      if ((valueSelf >= MIN_SENS && valueSelf <= MAX_SENS) || (valueSelf >= MIN_SENS_B && valueSelf <= MAX_SENS_B) && realClapCount >= 0) {
        // if (knockAllow == true) {
          if (valueSelf >= MIN_SENS_B && valueSelf <= MAX_SENS_B) {
            valueSelf = 900;
          }
          realValueSelf = valueSelf;
          SumUpTestVal += realValueSelf;
          //Serial.println(realValueSelf);
          LooptimeLast = millis();
          realClapCount += 1;
          TEST_MEASURE = realClapCount;
          if (realClapCount == 1) {
            TEST = 0;
            durationLast = millis();
          }
          if (TEST_MEASURE == MEASURE) {
            averageTestVal = SumUpTestVal / realClapCount;
            for (int indexTestVal = 0; indexTestVal <= realClapCount; indexTestVal++) {
              clapChecked[indexTestVal] = averageTestVal;
            }
            Serial.print(clapChecked[0]);
            Serial.println(" mainintensity");
          }
          TimingTestArray[realClapCount - 1] = TEST;
          Serial.print(realValueSelf);
          Serial.println(" intensity");
          Serial.print(TimingTestArray[realClapCount - 1]);
          Serial.println(" duration");

          ADDRESS = 68;
        }
      // }
     // knockAllow = false;
      realbuffer = 0;
      realTimeLast = realTimeCurrent;
    }
    if (realClapCount > 6) {
      for (int resets = 0; resets < realClapCount; resets++) {
        TimingTestArray[resets - 1] = 0;
        clapChecked[resets - 1] = 0;
      }
      Serial.println("resets Counter");
      SumUpTestVal = 0;
      realbuffer = 0;
      rumblebuffer = 0;
      realClapCount = 0;
      TEST_MEASURE = 0;
      LooptimeLast = LooptimeCurrent;
    }
   // knockAllow = false;
  }




  while (distance > 25 && digitalRead(BTN) == 0) {
    LooptimeLastPass = 0;
    averageTestVal = 0;
    averageValue = 0;
    allowTrig = false;
    SumUpTestVal = 0;
    LooptimeLast = 0;
    runmysensor();
    setbackcounter();
    durationCurrent = millis();
    if (MEASURE == TEST_MEASURE) {

      for (; indexCompared < realClapCount;) {
        if (abs(clapChecked[indexCompared] - clapArray[indexCompared]) <= accecptableVal) {
          passEqually = true;
        } else {
          passEqually = false;
          break;
        }
        indexCompared++;
      }
      indexCompared = 0;
      if (passEqually == true) {
        for (; indexCompared < realClapCount;) {
          if (abs(TimingTestArray[indexCompared] - TimingArray[indexCompared]) <= accecptableTime) {
            passEqually = true;
          } else {
            passEqually = false;
            break;
          }
          indexCompared++;
        }
      } else {
        passEqually = false;
      }

    } else {
      passEqually = false;
    }
    unsigned long solenoid = millis();
    if (passEqually == true) {
      durationCurrent = millis();
      if (millis() - timer6 > 1000) {
        Serial.println("Door unlocked");
        digitalWrite(solenoidPin, HIGH);
        realClapCount = 0;
        timer6 = millis();
      }

      //code for the servo to unlock da door
    } else if (passEqually == false) {
      durationCurrent = millis();
      if (millis() - timer6 > 1000) {
        digitalWrite(solenoidPin, LOW);
        Serial.println("Door locked");
        Serial.println(MEASURE);
        Serial.println(TEST_MEASURE);
        realClapCount = 0;
        timer6 = millis();
      }
      //code for the buzzer to send the wrong notification
    }
  }



  //clapArray[clapCount] = NewArray[0];
}
void timeInterrupt() {

  if (ADDRESS == 69) {
    durationElapsed = durationCurrent - durationLast;
    durationLast = durationCurrent;
    if (clapCount <= 5) {

      TRUE = durationElapsed;
    }
    ADDRESS = 67;
  }
  if (ADDRESS == 68) {
    durationElapsed = durationCurrent - durationLast;
    durationLast = durationCurrent;
    if (realClapCount <= 5) {

      TEST = durationElapsed;
    }
    ADDRESS = 67;
  }
}
