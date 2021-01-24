#ifndef ROBO_UTIL_H
#define ROBO_UTIL_H

#ifdef ARDUINO

namespace robo {

namespace string {

    String rjust(const String &target, uint8_t width, const char &padding)
    {
        String rjusted_str = target;
        for (uint8_t i = rjusted_str.length(); i < width; ++i) {
            rjusted_str = padding + rjusted_str;
        }
        return rjusted_str;
    }

    void rjust(String *dst, const String &target, uint8_t width, const char &padding)
    {
        *dst = target;
        for (uint8_t i = target.length(); i < width; ++i)
        {
            *dst = padding + (*dst);
        }
    }

    void rjust(String *target, uint8_t width, const char &padding)
    {
        for (uint8_t i = target->length(); i < width; ++i)
        {
            *target = padding + (*target);
        }
    }

} // namespace string

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_UTIL_H */