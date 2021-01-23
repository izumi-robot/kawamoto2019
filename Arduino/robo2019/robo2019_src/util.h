#ifndef ROBO_UTIL_H
#define ROBO_UTIL_H

#ifdef ARDUINO

namespace robo {

namespace string {

    String rjust(const String &target, uint8_t width, const char &padding) {
        String rjusted_str = target;
        for (uint8_t i = rjusted_str.length(); i < width; ++i) {
            rjusted_str = padding + rjusted_str;
        }
        return rjusted_str;
    }

} // namespace string

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_UTIL_H */