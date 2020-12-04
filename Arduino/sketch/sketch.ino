
// https://musashinodenpa.com/arduinok/ref/index.php?f=0&pos=1462
String motor_str(int m_num, int power) {
    String d = power < 0 ? "R" : "F";
    String p = String(abs(power));
    String tmp = "000";
    p = tmp.substring(0, 3 - p.length()) + p;
    String ans = String(m_num) + d + p;
    return ans;
}

void setup() {
    Serial.begin(9600);
}
/*
モーターの動かし方
F -- 正転
R -- 逆転
複数動かす場合は:で繋げる
*/
void loop() {
    Serial.println(motor_str(1, 100));
    delay(500);
    Serial.println(motor_str(1, -50));
    delay(1000);
}