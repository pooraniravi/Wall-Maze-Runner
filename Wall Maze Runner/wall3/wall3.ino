//maze solving logic and spa.... has bugs.........
//right hand rule based if first turn is right or left hand rule based if first turn is left
int trig1 = 2;
int echo1 = 3;
int trig2 = 4;
int echo2 = 5;
int trig3 = 8;
int echo3 = 7;
int dur1, dist1;
int dur2, dist2;
int dur3, dist3;
int i = 0;
int k=0;
int fdelay = 1450;
int tdelay=800;
char reshortn[30];
char directions[30];
char shortn[30];
int crit = 18;
int critm=35;
//int critm2 = 30;
int lm1 = 10;
int lm2 = 11;
int rm1 = 6;
int rm2 = 9;
//void printing(char prtdirection[])
//{
//  for (i = 0; prtdirection[i] != 'E'; i++)
//  {
//    Serial.print(prtdirection[i]);
//  }
//  delay(2000);
//}
void ultrasonic1()
{

  digitalWrite(trig1, 0);
  delayMicroseconds(2);
  digitalWrite(trig1, 1);
  delayMicroseconds(10);
  digitalWrite(trig1, 0);
  dur1 = pulseIn(echo1, 1);
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
  analogWrite(lm2, 0);
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
void replacement(char shortn[])
{
  for(i=0;shortn[i]!='E';i++)
   {
     if(shortn[i]=='U')
      {
        if((shortn[i-1]=='S')&&(shortn[i+1]=='R'))
        {
          shortn[i-1]='X';
          shortn[i]='X';
          shortn[i+1]='L';
        }
        else if((shortn[i-1]=='R')&&(shortn[i+1]=='R'))
        {
          shortn[i-1]='X';
          shortn[i]='X';
          shortn[i+1]='S';
        }
        else if((shortn[i-1]=='R')&&(shortn[i+1]=='S'))
        {
          shortn[i-1]='X';
          shortn[i]='X';
          shortn[i+1]='L';
        }
        else if((shortn[i-1]=='R')&&(shortn[i+1]=='L'))
        {
          shortn[i-1]='X';
          shortn[i]='X';
          shortn[i+1]='U';
        }
        else if((shortn[i-1]=='L')&&(shortn[i+1]=='R'))
        {
          shortn[i-1]='X';
          shortn[i]='X';
          shortn[i+1]='U';
        }
        else if((shortn[i-1]=='S')&&(shortn[i+1]=='S'))
        {
          shortn[i-1]='X';
          shortn[i]='X';
          shortn[i+1]='U';
        }
      }
   }
   int j=0;
   for(i=0;shortn[i]!='E';i++)
   {
     if(shortn[i]!='X')
     {
       reshortn[j]=shortn[i];
       j++;
     }
   }
   reshortn[j]='E';
  for(i=0;reshortn[i]!='E';i++)
   {
     if(reshortn[i]=='U')
     {
       replacement(reshortn);
     }
   }
   final();
}
void decisions()
{
  if(reshortn[k]=='S')
  {
    front();
    delay(500);
  }
  else if(reshortn[k]=='L')
  {
    front();
    delay(550);
    left();
    delay(tdelay);
    front();
    delay(fdelay);
  }
  else if(reshortn[k]=='R')
  { 
   front();
    delay(550);
    right();
    delay(tdelay);
    front();
    delay(fdelay);
  }
 k++;
}
void final()
{
while(1)
{
  readsens();
  if (dist1 < crit && dist2 > crit && dist3 < crit) //forward
  {
      Serial.print("front only");
      front();
      delay(500);
      Serial.print('f');
      Serial.println("");
  }
  else if (dist1 < crit && dist2 < crit && dist3 > critm) //right only
  {
    Serial.print("right only");
    front();
    delay(550);
    right();
    delay(tdelay);
    front();
    delay(fdelay);
    Serial.print('r');
    Serial.println("");
  }
  else if (dist1 > critm && dist2 < crit && dist3 < crit) //left only
  {
    Serial.print("left only");
    front();
    delay(550);
    left();
    delay(tdelay);
    front();
    delay(fdelay);
    Serial.print('r');
    Serial.println("");
  }
  else if (dist1 < crit && dist2 > critm && dist3 > critm) //straight and right only
  {
    decisions();
  }
  else if (dist1 > critm && dist2 > critm && dist3 < crit) //straight and left only
  {
    decisions();
  }
  else if (dist1 > critm && dist2 < critm && dist2 > crit && dist3 > critm) //T-way
  {
    decisions();
  }
  else  if (dist1 < crit && dist2 < crit && dist3 < crit) //deadend
  {
    
    delay(200);
    readsens();
    if (dist1 < crit && dist2 < crit && dist3 < crit)
    {
      Serial.print("deadend");
      left();
    delay(1600);
    Serial.print("u-turn");
    Stop();
    delay(500);
    readsens();
    directions[i]='U';
    i++;
    Serial.println("");}
  }
  if (dist2 > 50 && dist1 > 50 && dist3 > 50) //end of maze
  {

    directions[i]='E';
      while (1)
      {
        Serial.print('s');
        Stop();
        delay(100);
        Serial.println("");
      }
    }
  
}}




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
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void loop()
{
  readsens();
  if (dist1 < crit && dist2 > crit && dist3 < crit) //forward
  {
    if (((dist1==2)||(dist1==3)||(dist1==4)))
    {
      smallleft();
      Serial.print("s-right");
      Serial.println("");
    }
    else if (((dist3==2)||(dist3==3)||(dist3==4)))
    {
      smallright();
      Serial.print("s-left");
      Serial.println("");
    }
    else
    {
      Serial.print("front only");
      front();
      delay(500);
      Serial.print('f');
      Serial.println("");
    }
  }
  else if (dist1 < crit && dist2 < crit && dist3 > critm) //right only
  {
    Serial.print("right only");
    front();
    delay(550);
    right();
    delay(tdelay);
    front();
    delay(fdelay);
    Serial.print('r');
    Serial.println("");
  }
  else if (dist1 > critm && dist2 < crit && dist3 < crit) //left only
  {
    Serial.print("left only");
    front();
    delay(550);
    left();
    delay(tdelay);
    front();
    delay(fdelay);
    Serial.print('r');
    Serial.println("");
  }
  else if (dist1 < crit && dist2 > critm && dist3 > critm) //straight and right only
  {
    Serial.print("straight and right");
    front();
    delay(550);
    right();
    delay(800);
    front();
    delay(fdelay);
    directions[i]='R';
    i++;
    Serial.print('r');
    Serial.println("");
  }
  else if (dist1 > critm && dist2 > critm && dist3 < crit) //straight and left only
  {
    Serial.print("straight and left");
    front();
    delay(3000);
    directions[i]='S';
    i++;
    Serial.print('s');
    Serial.println("");
  }
  else if (dist1 > critm && dist2 < critm && dist2 > crit && dist3 > critm) //T-way
  {
    Serial.print("T-way");
    front();
    delay(550);
    right();
    delay(800);
    front();
    delay(fdelay);
    directions[i]='R';
    i++;
    Serial.print('r');
    Serial.println("");
  }
  else  if (dist1 < crit && dist2 < crit && dist3 < crit) //deadend
  {
    
    delay(200);
    readsens();
    if (dist1 < crit && dist2 < crit && dist3 < crit)
    {
      Serial.print("deadend");
      left();
    delay(1600);
    Serial.print("u-turn");
    Stop();
    delay(500);
    readsens();
    directions[i]='U';
    i++;
    Serial.println("");}
  }
  if (dist2 > 50 && dist1 > 50 && dist3 > 50) //end of maze
  {
   directions[i]='E';
        Serial.print('s');
        Stop();
        delay(6000);
        replacement(directions);
        Serial.println("");
      }
    }




