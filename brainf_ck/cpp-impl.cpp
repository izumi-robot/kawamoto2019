#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdint>

namespace brainf_ck {
    using inttype = std::int32_t;

    enum class Command : char
    {
        add     = '+', sub      = '-',
        shift_l = '<', shift_r  = '>',
        char_in = ',', char_out = '.',
        nest_in = '[', nest_out = ']'
    };

    class ExecutorBase
    {
    public:
        virtual inttype get_value() = 0;
        virtual void eval_cmd(const Command &) = 0;
    };

    class ProgramNode
    {
    public:
        virtual operator std::string () = 0;
        virtual void execute(Executor *) = 0;
    };

    class ProgramLeaf : ProgramNode
    {
    public:
        const Command value;

        ProgramLeaf() = delete;
        ProgramLeaf(const Command &cmd) : value(cmd) {}
        ProgramLeaf(const char &chr) : value(static_cast<Command>(chr)) {}

        operator std::string () override {
            switch (value)
            {
            case Command::add: return "+";
            case Command::sub: return "-";
            case Command::shift_l: return "<";
            case Command::shift_r: return ">";
            case Command::char_in:  return ",";
            case Command::char_out: return ".";
            default: return "";
            }
        }

        void execute(ExecutorBase *exe_p) override {
            exe_p->eval_cmd(value);
        }
    };

    class ProgramTree : ProgramNode
    {
    public:
        using Nodes = std::vector<ProgramNode>;
    private:
        Nodes values;
    public:

        ProgramTree() {}
        ProgramTree(const ProgramNode *nodes) : values(nodes) {}
        ProgramTree(const Nodes &nodes) : values(nodes) {}
    };

}