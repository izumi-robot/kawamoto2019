#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cassert>


namespace brainf_ck {
    using inttype = std::int32_t;
    using Memory = std::vector<inttype>;

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

    class ProgramExecutor : public ExecutorBase {
    private:
        Memory _memory;
        int _ptr;
        std::istream &_istr;
        std::ostream &_ostr;

    public:
        ProgramExecutor(std::istream &istr = std::cin, std::ostream &ostr = std::cout)
            : _memory(256, 0), _ptr(0), _istr(istr), _ostr(ostr) {}

        inttype get_value() override
        {
            return _memory[_ptr];
        }

        void eval_cmd(const Command &cmd) override
        {
            switch (cmd)
            {
            case Command::add: _memory[_ptr]++; return;
            case Command::sub: _memory[_ptr]--; return;
            case Command::shift_l:
                assert (--_ptr >= 0);
                return;
            case Command::shift_r:
                assert(++_ptr < _memory.size());
                return;
            case Command::char_in:
                char buff;
                _istr >> buff;
                _memory[_ptr] = inttype(buff);
                return;
            case Command::char_out:
                _ostr << char(_memory[_ptr]);
                return;
            default: return;
            }
        }
    };

    class ProgramNode
    {
    public:
        virtual operator std::string () = 0;
        virtual void execute(ExecutorBase *) = 0;
    };

    using ProgramNodes = std::vector<ProgramNode*>;

    class ProgramLeaf final : public ProgramNode
    {
    public:
        const Command value;

        ProgramLeaf() = delete;
        ProgramLeaf(const Command &cmd) : value(cmd) {}
        ProgramLeaf(const char &chr) : value(static_cast<Command>(chr)) {}

        operator std::string () override
        {
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

        void execute(ExecutorBase *exe_p) override
        {
            if (exe_p == nullptr) return;
            exe_p->eval_cmd(value);
        }
    };

    class ProgramTree final : public ProgramNode
    {
    private:
        ProgramNodes *values;

    public:
        ProgramTree() : values(new ProgramNodes()) {}
        ProgramTree(ProgramNodes *nodes) : values(nodes) {}

        operator std::string () override
        {
            std::string res = "[";
            for (ProgramNode *node : *values) {
                res += std::string(*node);
            }
            return res + "]";
        }

        void execute(ExecutorBase *exe_p) override
        {
            if (exe_p == nullptr) return;
            while (exe_p->get_value() != 0) {
                for (ProgramNode *node : *values) {
                    node->execute(exe_p);
                }
            }
        }

        void add_node(ProgramNode *node)
        {
            values->push_back(node);
        }

        ProgramNodes *get_values()
        {
            return values;
        }
    };

    ProgramNodes* parse_program(const std::string &src) {
        ProgramNodes *result = new ProgramNodes();
        int nest_count = 0, nest_in_index = 0;
        for (int i = 0; i < src.size(); i++) {
            Command cmd = static_cast<Command>(src[i]);
            switch (cmd)
            {
            case Command::nest_in:
                if (nest_count == 0) nest_in_index = i;
                nest_count++;
                break;
            case Command::nest_out:
                if (nest_count == 1) {
                    std::string new_src = src.substr(nest_in_index + 1, i - nest_in_index - 1);
                    ProgramTree *new_tree = new ProgramTree(parse_program(new_src));
                    result->push_back(new_tree);
                }
                nest_count--;
                break;
            case Command::add:
            case Command::sub:
            case Command::shift_l:
            case Command::shift_r:
            case Command::char_in:
            case Command::char_out:
                if (nest_count == 0) result->push_back(new ProgramLeaf(cmd));
            default:
                break;
            }
        }
        return result;
    }
}

int main(int argc, char* argv[])
{
    // argument check
    if (argc < 2) {
        std::cerr << "error: not enough arguments" << std::endl;
        return 1;
    }

    // read source
    std::ifstream ifs(argv[1], std::ios::in);
    if (!ifs) {
        std::cerr
            << "error: could not open file "
            << '"' << argv[1] << '"'
            << std::endl;
        return 1;
    }

    std::string source, buffer;
    while (ifs >> buffer) {
        source += buffer;
    }
    ifs.close();

    brainf_ck::ProgramNodes *nodes = brainf_ck::parse_program(source);
    brainf_ck::ProgramExecutor *executor = new brainf_ck::ProgramExecutor();;
    for (brainf_ck::ProgramNode *node : *nodes) {
        node->execute(executor);
    }
    std::cout << std::endl;
}