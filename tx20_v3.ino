const byte DATAPIN=D2;
volatile boolean TX20IncomingData = false;

unsigned char chk;
unsigned char sa,sb,sd,se;
unsigned int sc,sf, pin;

String tx20RawDataS = "";


void isTX20Rising() {
  if (!TX20IncomingData) {
    TX20IncomingData = true;
  }  
}

/*
 * SETUP
 */
void setup() {
  pinMode(DATAPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(DATAPIN), isTX20Rising, RISING);
  Serial.begin(115200);
}

boolean readTX20() {
    int bitcount=0;
    
    sa=sb=sd=se=0;
    sc=0;sf=0;
    tx20RawDataS = "";

    for (bitcount=41; bitcount>0; bitcount--) {
      pin = (digitalRead(DATAPIN));
      if (!pin) {
        tx20RawDataS += "1";      
      } else {
        tx20RawDataS += "0";      
      }
      if ((bitcount==41-4) || (bitcount==41-8) || (bitcount==41-20)  || (bitcount==41-24)  || (bitcount==41-28)) {
        tx20RawDataS += " ";
      }      
      if (bitcount > 41-5){
        // start, inverted
        sa = (sa<<1)|(pin^1);
      } else
      if (bitcount > 41-5-4){
        // wind dir, inverted
        sb = sb>>1 | ((pin^1)<<3);
      } else
      if (bitcount > 41-5-4-12){
        // windspeed, inverted
        sc = sc>>1 | ((pin^1)<<11);
      } else
      if (bitcount > 41-5-4-12-4){
        // checksum, inverted
        sd = sd>>1 | ((pin^1)<<3);
      } else 
      if (bitcount > 41-5-4-12-4-4){
        // wind dir
        se = se>>1 | (pin<<3);
      } else {
        // windspeed
        sf = sf>>1 | (pin<<11);
      } 
          
      delayMicroseconds(1220);    
    }
    chk= ( sb + (sc&0xf) + ((sc>>4)&0xf) + ((sc>>8)&0xf) );chk&=0xf;
    delayMicroseconds(2000);  // just in case
    TX20IncomingData = false;  

    if (sa==4 && sb==se && sc==sf && sd==chk){      
      return true;
    } else {
      return false;      
    }
}

/*
 * LOOP
 */
void loop() {
  if (TX20IncomingData) {
    char a[90];
    boolean validData = readTX20();
    Serial.println(tx20RawDataS);
    sprintf(a, "ID: %d\t%d\n", sa, B00100);
    Serial.write (a);
    sprintf(a, "Wind direction: %d\t%d\n", sb, se);
    Serial.write (a);
    sprintf(a, "Wind speed: %d\t%d\n", sc, sf);
    Serial.write (a);
    sprintf(a, "Checksum: %d\t%d\n", sd, chk);
    Serial.write (a);
    if (validData){      
      Serial.println(" :) OK :) OK :) OK :) OK");
    } else {
      Serial.println(" !!! ERROR !!! ERROR !!!");
    }
    Serial.println("");
  }
}
