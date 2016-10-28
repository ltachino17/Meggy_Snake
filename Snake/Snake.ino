/*
  Snake.pde by Lauryn Tachino
 
 Example file using the The Meggy Jr Simplified Library (MJSL)
  from the Meggy Jr RGB library for Arduino
   
 Blink a damned LED.
   
   
 
 Version 1.25 - 12/2/2008
 Copyright (c) 2008 Windell H. Oskay.  All right reserved.
 http://www.evilmadscientist.com/
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this library.  If not, see <http://www.gnu.org/licenses/>.
 	  
 */

 
 
 
 

/*
 * Adapted from "Blink,"  The basic Arduino example.  
 * http://www.arduino.cc/en/Tutorial/Blink
 */

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.

struct Point
{
   int x;
   int y;
};

Point p1 = {2,4};
Point p2 = {3,4};
Point p3 = {3,4};
Point p4 = {3,4};
Point snakeArray[64] = {p1,p2,p3,p4};
int marker = 4;    // Index of first empty segement of the array
int direction = 0;
int xapple = random(8);
int yapple = random(8);
int binary = 0;
int speed = 200;

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
}

void loop()                     // run over and over again
{
  drawSnake();
  updateSnake();
  DrawPx(xapple,yapple,Red);  // Draws apple
  // Have we eaten apple?
  if (ReadPx(snakeArray[0].x,snakeArray[0].y) == Red) 
  {
    xapple = random(8);    // new random apple location if eaten
    yapple = random(8);
    Tone_Start(13100,50);   // Sound when apple is eaten
    marker++;
    binary = binary * 2 + 1;  // set aux leds
    if (binary > 255)      // restart aux leds if reaches 7
    {
      binary = 0;
      speed = speed - 50;
    }
  }
 
  Checkdeath();
  
  SetAuxLEDs(binary);         // Set aux leds when apple is eaten
  DisplaySlate();                  // Write the drawing to the screen.
  delay(speed);                  // waits for a second
  
  ClearSlate();                 // Erase drawing
}

// Checks the direction and updates the x or y value.

void updateSnake()
{
  // Move body
  for (int i = marker - 1; i > 0; i--)
  {
    // Copy the value at i-1 into i
    snakeArray[i] = snakeArray[i -1];
  }

  
  // Move head
  if (direction == 0)
  {
    // Updates y
    snakeArray[0].y = snakeArray[0].y + 1;

    // Corrects for out of bounds
    if (snakeArray[0].y > 7)
    {
      snakeArray[0].y = 0;
    }
  }
  

  if (direction == 90)
  {
    // Updates x
    snakeArray[0].x = snakeArray[0].x + 1;

    // Corrects for out of bounds
    if(snakeArray[0].x > 7)
    {
      snakeArray[0].x = 0;
    }
  }
  

  if (direction == 180)
  {
    snakeArray[0].y = snakeArray[0].y - 1;

    if (snakeArray[0].y < 0)
    {
      snakeArray[0].y = 7;
    }
  }


  if (direction == 270)
  {
    snakeArray[0].x = snakeArray[0].x - 1;

    if (snakeArray[0].x < 0)
    {
      snakeArray[0].x = 7;
    }
  }
  
  CheckButtonsPress();
  
  if (Button_Up)
   direction = 0;
  
  if (Button_Down)
    direction = 180;

  if (Button_Left)
    direction = 270;

  if (Button_Right)
    direction = 90;

}
    


void drawSnake()
{
  //Iterate through the entire array
  for (int i = 0; i < marker; i++)
  {
   DrawPx(snakeArray[i].x,snakeArray[i].y,Blue);        // Draw a dot at x=3, y=4, in yellow
  }
}

void Checkdeath()
{
  if (ReadPx(snakeArray[0].x,snakeArray[0].y) == Blue)  // If the head hits the body
  {
    ClearSlate();         // Clears screen
    Tone_Start(20000,50);   // Produce a sound
    CheckButtonsPress();

    // Creates violet line on screen
    for (int i = 0; i < 0; i++)
    {
      DrawPx(i,0,Violet);
      DrawPx(0,i,Violet);
    }
    for (int i = 0; i < 0; i++)
    {
      DrawPx(i,7,Violet);
      DrawPx(7,i,Violet);
    }
    for (int i = 2; i < 6; i++)
    {
      DrawPx(i,i,Violet);
    }
    for (int i = 6; i < 2; i++)
    {
      DrawPx(i,i,Violet);
    }
    DisplaySlate();
  }
}


