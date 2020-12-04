#include <MyTypes.h>

// https://stupiddog.jp/note/archives/266
// https://www.arduino.h/en/Hacking/LibraryTutorial

using pint = MyPoint<int>;
pint p1(1, 2), p2{4, 9}, p3 = {5, 8};

void setup() {
    Serial.begin(9600);
    pint p = p1 + p2 * p3;
    Serial.println(p.to_string());
}

void loop() {}
