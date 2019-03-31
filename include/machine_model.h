/*
     File:    machine_model.h
     Created: 26 March 2019.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/


#ifndef MACHINE_MODEL_H
#define MACHINE_MODEL_H

constexpr unsigned num_of_float_regs=32;
constexpr unsigned num_of_int_regs=32;
struct Float_context{
__float128 f[num_of_float_regs];
};
struct Int_context{
    __int128 r[num_of_int_regs];
    __int128 ip;
};
constexpr unsigned bp=30;
constexpr unsigned sp=31;

enum class Value_kind{
Float, Int
};

struct Register{
    Value_kind kind;
    union{
        __float128 float_val;
        __int128 int_val;
    };
};

constexpr unsigned num_of_regs=16384;

struct Context{
    Register regs[num_of_regs];
    unsigned __int128 spr;
    unsigned __int128 spm;
    unsigned __int128 ip;
};

class Machine_model{
public:
    Machine_model()=default;
    Machine_model(const Machine_model&)=default;
    ~Machine_model()=default;
    void set_context(const Context& ctx)
    {
        ctx_=ctx;
    }
    Context get_context()const
    {
        return ctx_;
    }
    void set_memory_info(const Memory_info& mi)
    {
        mi_=mi;
    }
    Memory_info get_memory_info()const
    {
        return mi_;
    }
    void run();
    Machine_model(const Context& ctx, const Memory_info& mi): ctx_{ctx}, mi_{mi}{}
    
private:
    Context ctx_;
Memory_info mi_;
};
#endif
