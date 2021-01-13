# Pixy メモ

```Arduino
#include <Pixy2.h>

// This is the main Pixy object
Pixy2 pixy;

void setup() {
    Serial.begin(9600);
    Serial.println("Starting...");

    // initialize
    pixy.init();
}

void loop() {
    int i; 
    // grab blocks
    pixy.ccc.getBlocks();

    // If there are detect blocks, print them
    if (pixy.ccc.numBlocks) {
        Serial.print("Detected ");
        Serial.println(pixy.ccc.numBlocks);
        for (int i = 0; i < pixy.ccc.numBlocks; i++) {
            Serial.print(" block ");
            Serial.print(i);
            Serial.print(": ");
            pixy.ccc.blocks[i].print();
        }
    }
}
```

## Pixy.ccc Attributes

* `m_signature` -- シグネチャの番号
* `m_x` -- 検知したオブジェクトのx座標(1-316)
* `m_y` -- 検知したオブジェクトのy座標(1-316)
* `m_width` -- 検知したオブジェクトの横幅(0-316)
* `m_height` -- 検知したオブジェクトの高さ(0-208)
* `m_angle` -- https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:using_color_codes
* `m_index` -- オブジェクトのインデックス番号(多分使わない)
* `m_age` -- オブジェクトがトラックされているフレーム数


```C++
//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//

// Uncomment one of these to enable another type of serial interface
#define I2C
//#define UART
//#define SPI_SS
   
#ifdef I2C

#include <Pixy2I2C.h>
Pixy2I2C pixy;

#else 
#ifdef UART

#include <Pixy2UART.h>
Pixy2UART pixy;

#else 
#ifdef SPI_SS

#include <Pixy2SPI_SS.h>
Pixy2SPI_SS pixy;

#else

#include <Pixy2.h>
Pixy2 pixy;

#endif
#endif
#endif

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  pixy.init();
}

void loop()
{ 
  int i; 
  // grab blocks!
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }
  }  
}
```