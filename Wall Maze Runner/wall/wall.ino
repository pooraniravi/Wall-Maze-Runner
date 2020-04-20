//wall following logic.... may have bugs....
//right hand rule based if first turn is right or left hand rule based if first turn is left
int trig1 = 2;
int echo1= 3;
int trig2 = 4;
int echo2 = 5;
int trig3 = 8;
int echo3 = 7;
int dur1, dist1;
int dur2, dist2;
int dur3, dist3;
int tdelay = 800;
int i = 0;
int fdelay = 1450;
int crit = 15;
//int critm= 15;
int lm1 = 10;
int lm2 = 11;
int rm1 = 6;
int rm2 = 9;
char directions[30];
void printing(char prtdirection[])
{
  for (i = 0; prtdirection[i] != 'E'; i++)
  {
    Serial.print(prtdirection[i]);
  }
  delay(2000);
}
void ultrasonic1()
{

  digitalWrite(trig1, 0);
  delayMicroseconds(2);
  digitalWrite(trig1, 1);
  delayMicroseconds(10);
  digitalWrite(trig1, 0);
  dur1= pulseIn(echo1, 1);
  dist1 = (dur1 * (0.034 / 2));
}
void ultrasonic2()
{

  digitalWrite(trig2, 0);
  delayMicroseconds(2);
  digitalWrite(trig2, 1);
  delayMicroseconds(10);
  digitalWrite(trig2, 0);
  dur2 = pulseIn(echo2, 1);
  dist2 = (dur2 * (0.034 / 2));
}
void ultrasonic3()
{

  digitalWrite(trig3, 0);
  delayMicroseconds(2);
  digitalWrite(trig3, 1);
  delayMicroseconds(10);
  digitalWrite(trig3, 0);
  dur3 = pulseIn(echo3, 1);
  dist3 = (dur3 * (0.034 / 2));
}


void left()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW );
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}
void smallright()
{
  analogWrite(lm1, 127);
  digitalWrite(lm2, LOW );
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}

void right()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH );
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}
void smallleft()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW );
  analogWrite(rm1, 127);
  digitalWrite(rm2, LOW);
}

void front()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW );
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

void back()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}
void Stop()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}
void readsens()
{
  ultrasonic1();
  Serial.print("left sensor    ");
  Serial.println(dist1);
  ultrasonic2();
  Serial.print("middle sensor    ");
  Serial.println(dist2);
  ultrasonic3();
  Serial.print("right sensor    ");
  Serial.println(dist3);
 // Serial.println("");
  delay(200);
}

void setup()
{
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() 
{
readsens();
//if(dist2>crit && dist1>crit && dist3>crit) //end
//{
//  Stop();
//  Serial.print("stop");
//}
if(dist3<crit)
{
  if(dist2>crit)
  {front();
  delay(500);
   Serial.println("front");}
  else
  {
    Serial.println("left");
    front();
    delay(550);
    left();
    delay(tdelay);
    front();
    delay(fdelay);
    }
}
else if(dist3>crit) //ie break in wall and not dead end
{
  Serial.println("right");
  front();
    delay(550);
    right();
    delay(tdelay);
    front();
    delay(fdelay);
}
}



