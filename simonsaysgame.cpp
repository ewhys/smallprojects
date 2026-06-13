#include <stdlib.h>
//#include <iostream> needed for tostring ()?
int b0 = 2;
int b1 = 3;
int b2 = 4;
int b3 = 5;
bool b0state = 0;

bool b1state = 0;
bool b2state = 0;
bool b3state = 0;
int l0 = 6;
int l1 = 7;
int l2 = 8;
int l3 = 9;
int correct [50];
int high = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode (b0, INPUT);
  pinMode (b1, INPUT);
  pinMode (b2, INPUT);
  pinMode (b3, INPUT);
  pinMode (l0, OUTPUT);
  pinMode (l1, OUTPUT);
  pinMode (l2, OUTPUT);
  pinMode (l3, OUTPUT);
  Serial.begin (9600);
  randomSeed (analogRead (0));
  makesequence ();
}

void loop () 
{
  
  bool right = 1;
  int roundnum = 1;
  while (right == 1 && roundnum < 50)
  {
    right = oneround (roundnum);

    if (right)
    {
      roundnum ++;
    }

    if (right && roundnum > high)
    {
      high ++;
    }

    if (!right)
    {
      Serial.println ("not correct");
      roundnum = 1;
      makesequence (); 
    }

    
    
    Serial.print ("High score:");
    Serial.print (high);
    Serial.println (" ");
  }
 
}

void makesequence ()
{
 for (int i = 0; i<51; i++)
  {
  long rand = random (4);
    correct [i] = rand;
  }
}

void showsequence (int length)
{
  
  for (int i = 0; i<length; i++)
  {
  Serial.println (correct[i]);
  digitalWrite (correct [i] + 6, HIGH);
  delay (500);
  digitalWrite (correct [i] + 6, LOW);
  delay (500);
  }
  
  
}

bool readsequence (int index)
{
  int state = 0;
  while (state == 0)
  {
  //cycle through buttons
  for (int i = 2; i < 6; i++)
    {
    
      if (digitalRead (i))
      {
        if (correct [index] == (i-2))
        {
          Serial.println ("correct");
          tone (10, 3000, 500);
          while (digitalRead (i))
          {

          }
          state = 1;
          delay (300);
          return 1;
        }
        else
        {
          Serial.println ("incorrect");
          //tone (pin, frequency 31 to 6553, duration)
          tone (10, 200, 500);
          state = 1;
          delay (500);
          while (digitalRead (i))
          {
          
          }
          return 0;
        
        }

      }
    
    }
  }
  return;
}

bool oneround (int length)
{
  showsequence (length);
  
  bool correct = 1;
  int index = 0;
  while (index < length)
  {
    correct = readsequence (index);
    if (!correct)
    {
      return 0;
    }
    index ++;
  }
  Serial.println ("congrats");
  
  tone (10, 1500, 1000);
  delay (500);
  tone (10, 1000, 1000);
  delay (500);
  tone (10, 500, 1000);
  
  return 1; 
}
