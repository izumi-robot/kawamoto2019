#ifndef ROBO_UTIL_H
#define ROBO_UTIL_H

#ifdef ARDUINO

namespace robo {

void str_rjust(String &s, int len, const String &pad) {
    for (int i = s.length(); i < len; i++) {
        s = pad + s;
    }
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_UTIL_H */