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

    class ProgramNode {
    public:
        virtual std::string to_string() = 0;
    };

    class ProgramLeaf : ProgramNode {
    public:
        const Command value;

        ProgramLeaf() = delete;
        ProgramLeaf(const Command &cmd) : value(cmd) {}
        ProgramLeaf(const char &chr) : value(static_cast<Command>(chr)) {}

        std::string to_string() override {
            switch (value)
            {
            case Command::add: return "+";
            case Command::sub: return "-";
            case Command::shift_l: return "<";
            case Command::shift_r: return ">";
            case Command::char_in:  return ",";
            case Command::char_out: return ".";
            default:
                break;
            }
        }
    };

}