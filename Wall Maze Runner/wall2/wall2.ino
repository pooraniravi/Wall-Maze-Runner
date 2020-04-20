//initial maze solving logic...has bugs..
//left hand rule
int trig1 = 2;
int echo1= 3;
int trig2 = 4;
int echo2 = 5;
int trig3 = 6;
int echo3 = 7;
int dur1, dist1;
int dur2, dist2;
int dur3, dist3;
int tdelay = 750;
int i = 0;
int fdelay = 500;
int crit = 10;
int critm=10;
int lm1 = 10;
int lm2 = 11;
int rm1 = 8;
int rm2 = 9;
char directions[30];
void inch()
{
  Stop();
  delay(100);
  front();
  delay(500);
  ultrasonic1();
  ultrasonic2();
  ultrasonic3();
  delay(100);
}
void reverseinch()
{
  back();
  delay(500);
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
  digitalWrite(lm1, HIGH);
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
  digitalWrite(rm1, HIGH);
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

void setup()
{
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
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
  
  delay(200);
  //straight
  if ((dist1 < crit) && (dist2 > critm) && (dist3 < crit))
  {
    Serial.println("straight");
    Serial.println("");
    front();
//    if ((dist1 == (7 || 8 || 9)) && (dist2 > crit) && (dist3 == (7 || 8 || 9)))
//  {
//        Serial.println("forward");
//        front();
//        }
//      if ((dist1 > 9) && (dist2 > crit) && (dist3 < 7))
//      {
//        Serial.println("s-left");
//        smallleft();
//      }
//       if ((dist1 <7) && (dist2 > crit) && (dist3 >9))
//      {
//        Serial.println("s-right.");
//        smallright();
//      }
  }
  //left
  else if ((dist1 > crit) && (dist2 < critm) && (dist3 < crit))
  {
    Serial.println("left");
    Serial.println("");
    left();
  }
  //right
  else if ((dist1 < crit) && (dist2 < critm) && (dist3 > crit))
  {
    Serial.println("right");
    Serial.println("");
    right();
    delay(150);
  }
  //deadend
  else if ((dist1 < crit) && (dist2 < critm) && (dist3 < crit))
  {
    Serial.println("uturn");
    Serial.println("");
    right();
    delay(tdelay);
    directions[i] = 'U';
    i++;
  }
  //straight and right
  else if ((dist1 < crit) && (dist2 > critm) && (dist3 > crit))
  {
    Serial.println("straight");
    Serial.println("");
    front();
    directions[i] = 'S';
    i++;
  }
  //straight and left
  else if ((dist1 > crit) && (dist2 > critm) && (dist3 < crit))
  {
    Serial.println("left");
    Serial.println("");
    left();
    directions[i] = 'L';
    i++;
  }
  //t-intersection
  else if ((dist1 > crit) && (dist2 < critm) && (dist3 > crit))
  {
    Serial.println("left");
    Serial.println("");
    left();
    directions[i] = 'L';
    i++;
  }
  //four-way or end
  else if ((dist1 > crit) && (dist2 > critm) && (dist3 > crit))
  {
    inch();
    if ((dist1 < crit) && (dist2 > critm) && (dist3 < crit))
    {
      reverseinch();
      Serial.println("left");
      Serial.println("");
      left();
      directions[i] = 'L';
      i++;
    }
    else
    {
      Serial.println("stop");
      Serial.println("");
      directions[i] = 'E';
      i++;
      while (1)
      {
        Stop();
      }
    }
  }
}



