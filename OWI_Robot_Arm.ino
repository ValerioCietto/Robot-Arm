/*
pin layout
0 tx
1 rx
2 direzione primo motore
3 pwm primo motore
4 direzione secondo motore
5 pwm secondo motore
6 pwm mano
7 direzione mao
8 direzione terzo motore
9 pwm terzo motore
10
11
12 luce
13
A0
A1
A2
A3
A4
A5

pin L9110
aia --> 4 arduino
ab --> 5 arduino
bia --> 2 arduino
bb --> 3 arduino
wcc --> 5v arduino
gnd --> ground arduino

pin L9110 secondo
aia --> 8 arduino
ab --> 9 arduino
bia --> 7 arduino
bb --> 6 arduino
wcc --> 5v arduino
gnd --> ground arduino
*/

const int trigPin = 11;
const int echoPin = 12;
boolean executing = false; //stops reading if the robot is moving to prevent long queues

void setup()
{
  Serial.begin(9600); // Start bluetooth serial at 9600
  Serial.print("------");
  digitalWrite(13, HIGH);
  delay(400); // Short delay, wait for the Mate to send back CMD
  digitalWrite(13, LOW);
  pinMode(2, OUTPUT); //Initiates left Motor dir pin
  pinMode(3, OUTPUT); //Initiates left Motor pwm pin
  pinMode(4, OUTPUT); //Initiates right Motor dir pin
  pinMode(5, OUTPUT); //Initiates right Motor pwm pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  if(Serial.available()){//bluetooth.available()
    char msg = (char)Serial.read(); //read next character, and removes it from the queue
    char next = (char)Serial.peek(); //looks for next character, but doesn't eliminate it from the queue
    if(msg == next){
        Serial.read();
      }
      if(executing==false)
      {
        if(msg=='d'){
          Serial.println(msg);
          muoviBaseDx(200);
        }
        else if(msg=='a'){
          Serial.println(msg);
          muoviBaseSx(200);
        }
        else if(msg=='w'){
          Serial.println(msg);
          muoviSecondoSx(200);
        }
        else if(msg=='s'){
          Serial.println(msg);
          muoviSecondoDx(200);
        }
        else if(msg=='f'){
          Serial.println(msg);
          muoviTerzoDx(200);
          muoviTerzoSx(2);
        }
        else if(msg=='h'){
          Serial.println(msg);
          muoviTerzoSx(200);
          muoviTerzoDx(2);
        }
        else if(msg=='g'){
          Serial.println(msg);
          muoviQuartoSx(200);
          muoviQuartoDx(2);
        }
        else if(msg=='t'){
          Serial.println(msg);
          muoviQuartoDx(200);
          muoviQuartoSx(2);
        }
    }
  }
}
//--------------------------------------------------------------------------------- PRIMO MOTORE (COMANDI D-A)----------------------------------------------------------------------------- FUNZIONA
void muoviBaseSx(int time)
{
  executing = true;
  digitalWrite(2, HIGH);
  analogWrite(3, 120);
  delay(time);
  executing=false;
  digitalWrite(2, LOW);
  analogWrite(3, 0);
  
}
void muoviBaseDx(int time)
{
  executing = true;
  digitalWrite(2, LOW);
  analogWrite(3, 200);
  delay(time);
  executing=false;
  digitalWrite(2, HIGH);
  analogWrite(3, 0);
}
//--------------------------------------------------------------------------------- SECONDO MOTORE (COMANDI W-S)----------------------------------------------------------------------------- FUNZIONA
void muoviSecondoSx(int time)
{
  executing = true;
  digitalWrite(4, HIGH);
  analogWrite(5, 120);
  delay(time);
  executing=false;
  digitalWrite(4, LOW);
  analogWrite(5, 0);
}
void muoviSecondoDx(int time)
{
  executing = true;
  digitalWrite(4, LOW);
  analogWrite(5, 120);
  delay(time);
  executing=false;
  analogWrite(5, 0);
}

//--------------------------------------------------------------------------------- TERZO MOTORE (COMANDI F-H)-----------------------------------------------------------------------------
void muoviTerzoSx(int time)
{
  executing = true;
  digitalWrite(7, LOW);
  analogWrite(6, 120);
  delay(time);
  executing=false;
  digitalWrite(7, LOW);
  analogWrite(6, 0);
}
void muoviTerzoDx(int time)
{
  executing = true;
  digitalWrite(7, LOW);
  analogWrite(6, 200);
  delay(time);
  executing=false;
  analogWrite(6, 0);
}

//--------------------------------------------------------------------------------- QUARTO MOTORE (COMANDI T-G)-----------------------------------------------------------------------------
void muoviQuartoSx(int time)
{
  executing = true;
  digitalWrite(8, HIGH);
  analogWrite(9, 120);
  delay(time);
  executing=false;
  digitalWrite(8, LOW);
  analogWrite(9, 0);
}
void muoviQuartoDx(int time)
{
  executing = true;
  digitalWrite(8, LOW);
  analogWrite(9, 120);
  delay(time);
  executing=false;
  digitalWrite(8, HIGH);
  analogWrite(9, 0);
}
