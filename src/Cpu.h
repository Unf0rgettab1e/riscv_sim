
#ifndef RISCV_SIM_CPU_H
#define RISCV_SIM_CPU_H

#include "Memory.h"
#include "Decoder.h"
#include "RegisterFile.h"
#include "CsrFile.h"
#include "Executor.h"

class Cpu
{
public:
    Cpu(Memory& mem) : _mem(mem)
    {

    }

    void ProcessInstruction()
    {
        // Fetch
        Word word = _mem.Request(_ip);

        // Decode
        InstructionPtr instruction = _decoder.Decode(word);
        _csrf.Read(instruction);
        _rf.Read(instruction);

        // Execute
        _exe.Execute(instruction, _ip);
        _mem.Request(instruction);

        // Write back
        _csrf.Write(instruction);
        _rf.Write(instruction);

        // Advance PC
        _csrf.InstructionExecuted();
        _ip = instruction->_nextIp;
    }

    void Reset(Word ip)
    {
        _csrf.Reset();
        _ip = ip;
    }

    std::optional<CpuToHostData> GetMessage()
    {
        return _csrf.GetMessage();
    }

private:
    Reg32 _ip;              // the same as PC and IAR
    Decoder _decoder;
    RegisterFile _rf;
    CsrFile _csrf;          // used as storage devices for information about instructions received from machines
    Executor _exe;
    Memory& _mem;
};


#endif //RISCV_SIM_CPU_H
