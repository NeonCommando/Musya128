/*
     File:    machine_model.h
     Created: 26 March 2019.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/


#ifndef MACHINE_MODEL_H
#define MACHINE_MODEL_H

#include "../include/memory_info.h"

constexpr unsigned num_of_float_regs=32;
constexpr unsigned num_of_int_regs=32;
struct Float_context{
__float128 f[num_of_float_regs]=0;
};
struct Int_context{
    __int128 r[num_of_int_regs]=0;
    __int128 ip=0;
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
    Register regs[num_of_regs]=0;
    unsigned __int128 spr;
    unsigned __int128 spm;
    unsigned __int128 ip;
};

enum class Instr_code{
    ADD,     SUB,      MUL,       DIV,       MOD,      POWER,     NEG,      OR,      NOR,      XOR,     AND,     NAND,   LSH,    RSH,    NOT,     XOR1,             LT,      GT,       LEQ,       GEQ,       EQ,       NEQ,       LDC,      LDV,     LDVR,     LD0,     LD1,     LDm1,   LDSPM,  LDSF,   LDSFR,   ST,          ST_ADD,  ST_SUB,   ST_MUL,    ST_DIV,    ST_MOD,   ST_POWER,  ST_OR,    ST_NOR,  ST_XOR,   ST_AND,  ST_NAND, ST_LSH, ST_RSH, STR,    STR_ADD, STR_SUB,   STR_MUL, STR_DIV,  STR_MOD,   STR_POWER, STR_OR,   STR_NOR,   STR_XOR,  STR_AND, STR_NAND, STR_LSH, STR_RSH, STSPM,  STSF,   STSFR,  JMP,     JZ,         JNZ,     CALL,     CALLZ,     CALLNZ,    RET,      OUT_INT,   OUT_STR,  IN_INT,  INR_INT,  HLT,     DUP,     SWAP,   SPMADD, SPMSUB, POP,     ENTER,     LEAVE
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
    
   typedef bool(Machine_model::*Com_func)();  /*Изменения от 23.04.2019*/
   static Com_func funcs_[];
   void add_func();     void sub_func();    void mul_func();      void div_func();   void mod_func();    void power_func();  void neg_func();                    void or_func();      void nor_func();    void xor_func();      void and_func();   void nand_func();   void lsh_func();    void rsh_func();                  void not_func();     void xor1_func();   void lt_func();       void gt_func();    void leq_func();    void geq_func();    void eq_func();                   void neq_func();     void ldc_func();    void ldv_func();      void ldvr_func();  void ld0_func();    void ld1_func();    void ldm1_func();                void ldspm_func();   void ldsf_func();   void ldsfr_func();    void st_func();    void stadd_func();  void stsub_func();  void stmul_func();               void stdiv_func();   void stmod_func();  void stpower_func();  void stor_func();  void stnor_func();  void stxor_func();  void stand_func();                void stnand_func();  void stlsh_func();  void strsh_func();    void str_func();   void stradd_func(); void strsub_func(); void strmul_func();               void strdiv_func();  void strmod_func(); void strpower_func(); void stror_func(); void strnor_func(); void strxor_func(); void strand_func();               void strnand_func(); void strlsh_func(); void strrsh_func();   void stspm_func(); void stsf_func();   void stsfr_func();  void jmp_func();                 void jz_func();      void jnz_func();    void call_func();     void callz_func(); void callnz_func(); void ret_func();    void outint_func();              void outstr_func();  void inint_func();  void inrint_func();   void hlt_func();   void dup_func();    void swap_func();   void spmadd_func();              void spmsub_func();  void pop_func();    void enter_func();    void leave_func();
    
private:
    Context ctx_;
Memory_info mi_;
};
#endif
