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
