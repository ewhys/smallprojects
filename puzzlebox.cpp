unsigned long previousMillis = 0;
const long interval = 1000;
bool lights [6] = {};
bool set [6] = {};
int button = 7;
int needed = 0;
bool pressed = 0;
int total = 0;
const int xpin = 5;
const int ypin = 3;
bool t = 0;
#include <Servo.h>
Servo s; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (button, INPUT);
  pinMode (13, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (xpin, INPUT);
  pinMode (ypin, INPUT);
  s.attach (6, 500, 2500);

}

void loop() {
 s.write (0);
  puzzle1 ();
  puzzle2 ();
  puzzle3 ();
  set [0] = 0;
  set [1] = 0;
  set [2] = 0;
  set [3] = 0;
  set [4] = 0;
  set [5] = 0;
  lights [0] = 0;
  lights [1] = 0;
  lights [2] = 0;
  lights [3] = 0;
  lights [4] = 0;
  lights [5] = 0;
}

void printlist ()
{
  int number = 0;
  Serial.println ();
  for (int i = 0; i < 6; i++)
  {
    number = lights [i] + set [i];
    if ( number == 2 )
    {
      number = 1;
    }
    Serial.print (number);
    digitalWrite (i + 8, number);
    
    
  }
  Serial.println ();
}

void b (int i)
{
printlist ();
    previousMillis = millis ();
    while ((millis () - previousMillis) < 200)
    {
      
      if (digitalRead (button) == 1)
      {
        pressed = 1;
        
      }
    }
    
    if ((pressed == 1) && (needed == i))
    {
      Serial.print (needed);
      Serial.println ("button clicked");
      
      needed++;
      set [i] = 1;

    }
    while (pressed == 1)
    {
      if (digitalRead (button) == 0)
      {
        pressed = 0;
      }
    }
  
}

void yay ()
{
  for (int i = 0; i < 6; i++)
  {
    for (int i = 0; i < 6; i ++)
    {
      digitalWrite (i + 8, 1);
    }
    delay (100);
    for (int i = 0; i < 6; i ++)
    {
      digitalWrite (i + 8, 0);
    }
    delay (100);
  }
}

void puzzle1 ()
{
  digitalWrite (13, 1);
  digitalWrite (12, 1);
  digitalWrite (11, 1);
  int ya;
  int yp;
  yp =pulseIn(ypin, HIGH);
  ya = ((yp)/10-500) * 8;
  for (int i = 0; i < 3; i++)
  {
    Serial.println ("looped");
    
    bool state = 0;
    //wait until y is more than 850
  while (ya<850)
    {
      yp =pulseIn(ypin, HIGH);
      ya = ((yp)/10-500) * 8;
      Serial.println (ya);
    }
    Serial.println ("more");
  // wait until y is less than -100
  while (ya>-100)
  {
    yp =pulseIn(ypin, HIGH);
      ya = ((yp)/10-500) * 8;
      Serial.println (ya);
  }
  Serial.println ("less");
  }
  Serial.println ("puzzle 1 done");
  yay ();
  s.write (180);
}

void puzzle2 ()
{
  int ya;
  int yp;
  digitalWrite (13, 0);
  digitalWrite (12, 1);
  digitalWrite (11, 1);
  //F
  
  
  // put your main code here, to run repeatedly:
  yp =pulseIn(ypin, HIGH);
  ya = ((yp)/10-500) * 8;
  while ((ya > -1000) || (digitalRead (button) == 0))
  {
    yp =pulseIn(ypin, HIGH);
    ya = ((yp)/10-500) * 8;
    Serial.println (ya);
  }
  yay ();
  Serial.println ("puzzle 2 done");
  

}

void puzzle3 ()
{
  //BALANCE GAME


  while (total < 6)
  {
    total = 0;
      for (int i = 0; i < 6; i++)
    {
    
      lights [i] = 1;
    
        if (i > 0)
      {
        lights [i-1] = 0;
      }
        else
      {
        lights [5] = 0;
      }
      b (i);
    }
  
  for (int j = 5; j > -1; j--)
  {
    lights [j] = 1;
    if (j < 5)
    {
      lights [j+1] = 0;
    }
    else
    {
      lights [0] = 0;
    }
    b (j);
  }
    for (int i = 0; i < 6; i ++)
    {
      if (set[i] == 1)
      {
        total ++;
      }
    }
    Serial.println (total);
  }
Serial.println ("puzzle 3 complete"); 
yay ();
}