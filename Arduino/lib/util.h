#ifndef ROBO_UTIL_H
#define ROBO_UTIL_H

namespace robo {

void str_rjust(String &s, int len, const String &pad) {
    for (int i = s.length(); i < len; i++) {
        s = pad + s;
    }
}

}

#endif /* ROBO_UTIL_H */