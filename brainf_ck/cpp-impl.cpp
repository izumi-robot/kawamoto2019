#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdint>

namespace brainf_ck {
    using inttype = std::int32_t;

    enum class Command : char {
        add     = '+', sub      = '-',
        shift_l = '<', shift_r  = '>',
        char_in = ',', char_out = '.',
        nest_in = '[', nest_out = ']'
    };

    class IExecutor {
    public:
        virtual inttype val() = 0;

        virtual void inc_val() = 0;
        virtual void dec_val() = 0;

        virtual void inc_ptr() = 0;
        virtual void dec_ptr() = 0;

        virtual void char_in()  = 0;
        virtual void char_out() = 0;
    };

    class ProgramTree {
    public:
        virtual std::string to_string() = 0;
    };

}