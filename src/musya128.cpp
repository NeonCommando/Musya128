/*
File:    musya128.cpp
Created: 26 March 2019.

Author:  Федотов Николай Алексеевич
E-mail: nick1999fedotov@gmail.com
*/

#include "../include/musya128.h"
#include "../include/machine_model.h"

#include "../include/parsing_result_t.h"

#include <locale>
#include <cmath>

//Функции

bool Machine_model::add_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x+y);
    return t;}

bool Machine_model::sub_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = push_value(y-x);
    return t;}

bool Machine_model::mul_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x*y);
    return t;}

bool Machine_model::div_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = x != 0;
    if(!t){cout<<"Деление на нуль. Аварийный останов машины."<<endl;}
    else{push_value(y/x);}
    return t;}

bool Machine_model::mod_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = x != 0;
    if(!t){cout<<"Деление на нуль. Аварийный останов машины."<<endl;}
    else{push_value(y%x);}
    return t;}

bool Machine_model::power_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = is_power_args_correct(y, x);
    if(t){t = push_value(pow(y, x));}
    return t;}

bool Machine_model::neg_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = push_value(-x);
    return t;}

bool Machine_model::or_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x|y);
    return t;}

bool Machine_model::nor_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value((~y)|x);
    return t;}

bool Machine_model::xor_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x^y);
    return t;}

bool Machine_model::xor1_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = push_value(x^1);
    return t;}

bool Machine_model::and_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x&y);
    return t;}

bool Machine_model::nand_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value((~y)&x);
    return t;}

bool Machine_model::lsh_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(y<<x);
    return t;}

bool Machine_model::rsh_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(y>>x);
    return t;}

bool Machine_model::not_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = push_value(~x);
    return t;}

bool Machine_model::lt_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(y<x);
    return t;}

bool Machine_model::gt_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(y>x);
    return t;}

bool Machine_model::leq_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(y<=x);
    return t;}

bool Machine_model::geq_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(y>=x);
    return t;}

bool Machine_model::eq_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x==y);
    return t;}

bool Machine_model::neq_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x!=y);
    return t;}

bool Machine_model::ldc_func()
    {bool t = push_value(registers.offset_register);
    return t;}

bool Machine_model::ldv_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    y = get_word_from_data_memory(x, &t);
    if(t){t = push_value(y);}
    return t;}

bool Machine_model::ldvr_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    x += registers.SF;
    y = get_word_from_data_memory(x, &t);
    if(t){t = push_value(y);}
    return t;}

bool Machine_model::ld0_func()
    {bool t;
        t = push_value(0);
    return t;}

bool Machine_model::ld1_func()
    {bool t = push_value(1);
    return t;}

bool Machine_model::ldm1_func()
    {bool t = push_value(-1);
    return t;}

bool Machine_model::ldspm_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    registers.SPM = get_word_from_data_memory(x, &t);
    return t;}

bool Machine_model::ldsf_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    registers.SF = get_word_from_data_memory(x, &t);}

bool Machine_model::ldsfr_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    x += registers.SF;
    registers.SF = get_word_from_data_memory(x, &t);
    return t;}

bool Machine_model::st_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = set_word_in_data_memory(y, x);
    return t;}

bool Machine_model::stadd_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z += x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stsub_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z -= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stmul_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z *= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stdiv_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    t = x != 0;
    if(!t){cout<<"Деление на нуль. Аварийный останов машины."<<endl;}
    else
        {z = get_word_from_data_memory(y, &t);
        if(t)
            {z /= x;
            t = set_word_in_data_memory(y, z);}
        }
    return t;}

bool Machine_model::stmod_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    t = x != 0;
    if(!t){cout<<"Деление на нуль. Аварийный останов машины."<<endl;}
    else
        {z = get_word_from_data_memory(y, &t);
        if(t)
            {z %= x;
            t = set_word_in_data_memory(y, z);}
        }
    return t;}

bool Machine_model::stpower_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {t = is_power_args_correct(z, x);
        if(t){t = set_word_in_data_memory(y, pow(z, x));}
        }
    return t;}

bool Machine_model::stor_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z |= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stnor_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z = (~z) | x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stxor_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z ^= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stand_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z &= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stnand_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z = (~z) & x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stlsh_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z <<= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strsh_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z >>= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::str_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    t = set_word_in_data_memory(y, x);
    return t;}

bool Machine_model::stradd_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z += x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strsub_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z -= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strmul_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z *= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strdiv_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    t = x != 0;
    if(!t){cout<<"Деление на нуль. Аварийный останов машины."<<endl;}
    else
        {z = get_word_from_data_memory(y, &t);
        if(t)
            {z /= x;
            t = set_word_in_data_memory(y, z);}
        }
    return t;}

bool Machine_model::strmod_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    t = x != 0;
    if(!t){cout<<"Деление на нуль. Аварийный останов машины."<<endl;}
    else
        {z = get_word_from_data_memory(y, &t);
        if(t)
            {z %= x;
            t = set_word_in_data_memory(y, z);}
        }
    return t;}

bool Machine_model::strpower_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {
t = is_power_args_correct(z, x);
        if(t){t = set_word_in_data_memory(y, pow(z, x));}
        }
    return t;}

bool Machine_model::stror_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z |= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strnor_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z = (~z) | x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strxor_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z ^= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strand_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z &= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strnand_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z = (~z) & x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strlsh_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z <<= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::strrsh_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    y += registers.SF;
    z = get_word_from_data_memory(y, &t);
    if(t)
        {z >>= x;
        t = set_word_in_data_memory(y, z);}
    return t;}

bool Machine_model::stspm_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = set_word_in_data_memory(x, registers.SPM);
    return t;}

bool Machine_model::stsf_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = set_word_in_data_memory(x, registers.SF);
    return t;}

void Machine_model::stsfr_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    y = registers.SF;
    x += y;
    bool t = set_word_in_data_memory(x, y);
    return t;}

bool Machine_model::jmp_func()
    {int x = pop_func();
    bool t;
    registers.IP = x;
    return t;}

bool Machine_model::jz_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    if(y == 0)
        {registers.IP = x;}
    return t;}

bool Machine_model::jnz_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    if(y != 0)
        {registers.IP = x;}
    return t;}

bool Machine_model::call_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = push_value(registers.IP);
    registers.IP = x;
    return t;}

bool Machine_model::callz_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    if(y == 0)
        {t = push_value(registers.IP);
        registers.IP = x;}
    return t;}

bool Machine_model::callnz_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    if(y != 0)
        {t = push_value(registers.IP);
        registers.IP = x;}
    return t;}

bool Machine_model::ret_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    registers.SPM -= x*4;
    registers.IP = y;
    return t;}

bool Machine_model::outint_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    cout<<x;
    return t;}

bool Machine_model::outstr_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = check_address_in_data_memory(x);
    if(t)
        {char* pch = data_memory_begin + x;
        cout<<pch;}
    return t;}

bool Machine_model::inint_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t=check_address_in_data_memory(x+3);
    if(t)
        {int* pi = (int*)( data_memory_begin + x );
        cin>>pi;}
    return t;}

bool Machine_model::inrint_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    y = registers.SF;
    x += y;
    bool t=check_address_in_data_memory(x+3);
    if(t)
        {int* pi = (int*)( data_memory_begin + x );
        cin>>pi;}
    return t;}

bool Machine_model::hlt_func()
    {cout<<"Машина заканчивает работу."<<endl;
    bool t = false;
    return t;}

bool Machine_model::dup_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    t = push_value(x);
    t = push_value(x);
    return t;}

bool Machine_model::swap_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    t = push_value(x);
    t = push_value(y);
    return t;}

bool Machine_model::spmadd_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    registers.SPM += x;
    t = true;
    return t;}

bool Machine_model::spmsub_func()
    {int x = pop_func();
    bool t = get_arguments(&x);
    registers.SPM -= x;
    t = true;
    return t;}

bool Machine_model::enter_func()
    {int x = pop_func();
    int y = pop_func();
    int z;
    bool t = get_arguments(&x, &y);
    t = set_word_in_data_memory(registers.SPM, registers.SF);
    registers.SPM += 4;
    z = registers.SPM;
    if(y > 0)
        {int q;
        for(int i = 0; i < y -1; i++)
            {registers.SF += 4;
            q = get_word_from_data_memory(registers.SF, &t);
            if(!t){return false;};
            t = set_word_in_data_memory(registers.SPM, q);
            registers.SPM += 4;}
        t = set_word_in_data_memory(registers.SPM, z);
        if(!t){return false;};
        registers.SPM += 4;}
    registers.SF = z;
    registers.SPM += x;
    return t;}

bool Machine_model::leave_func()
    {int x = pop_func();
    int y = pop_func();
    bool t = get_arguments(&x, &y);
    x = registers.SF;
    registers.SPM = x;
    y = get_word_from_data_memory(x, &t);
    if(t)
        {registers.SF = y;
        registers.SPM -=4;}
    return t;}

struct MUSYA128::Impl{
public:
    Impl()=default;
    Impl(const Impl&)=default;
    ~Impl()=default;
    Impl(const parsing_result_t& image):
        image_{image}{}
    void set_image(const parsing_result_t& image)
    {
        image_=image;
    }
    parsing_result_t get_image()const
    {
        return image_;
    }
    void run()                                   //void run
    {
        void MUSYA128::run(){}
    };
    
private:
    parsing_result_t image_;
    Machine_model model;
    void convert_image_to_model(){};
};

MUSYA128::MUSYA128(): pimpl_{std::make_shared<Impl>()}{}
MUSYA128::MUSYA128(const parsing_result_t& image):pimpl_{
    std::make_shared<Impl>(image)}{}
MUSYA128::~MUSYA128()=default;
void MUSYA128::set_image(const parsing_result_t& image)
{
    pimpl_->set_image(image);
}
parsing_result_t MUSYA128::get_image()const
{
    return pimpl_->get_image();
}
void MUSYA128::run()
{
    pimpl_->run();
}

Machine_model::Com_func Machine_model::funcs_[]={
    &Machine_model::add_func,     &Machine_model::sub_func,     &Machine_model::mul_func,    &Machine_model::div_func,
    &Machine_model::mod_func,     &Machine_model::power_func,   &Machine_model::neg_func,    &Machine_model::or_func,
    &Machine_model::nor_func,     &Machine_model::xor_func,     &Machine_model::and_func,    &Machine_model::nand_func,
    &Machine_model::lsh_func,     &Machine_model::rsh_func,     &Machine_model::not_func,    &Machine_model::xor1_func,
    &Machine_model::lt_func,      &Machine_model::gt_func,      &Machine_model::leq_func,    &Machine_model::geq_func,
    &Machine_model::eq_func,      &Machine_model::neq_func,     &Machine_model::ldc_func,    &Machine_model::ldv_func,
    &Machine_model::ldvr_func,    &Machine_model::ld0_func,     &Machine_model::ld1_func,    &Machine_model::ldm1_func,
    &Machine_model::ldspm_func,   &Machine_model::ldsf_func,    &Machine_model::ldsfr_func,  &Machine_model::st_func,
    &Machine_model::stadd_func,   &Machine_model::stsub_func,   &Machine_model::stmul_func,  &Machine_model::stdiv_func,
    &Machine_model::stmod_func,   &Machine_model::stpower_func, &Machine_model::stor_func,   &Machine_model::stnor_func,
    &Machine_model::stxor_func,   &Machine_model::stand_func,   &Machine_model::stnand_func, &Machine_model::stlsh_func,
    &Machine_model::strsh_func,   &Machine_model::str_func,     &Machine_model::stradd_func, &Machine_model::strsub_func,
    &Machine_model::strmul_func,  &Machine_model::strdiv_func,  &Machine_model::strmod_func, &Machine_model::strpower_func,
    &Machine_model::stror_func,   &Machine_model::strnor_func,  &Machine_model::strxor_func, &Machine_model::strand_func,
    &Machine_model::strnand_func, &Machine_model::strlsh_func,  &Machine_model::strrsh_func, &Machine_model::stspm_func,
    &Machine_model::stsf_func,    &Machine_model::stsfr_func,   &Machine_model::jmp_func,    &Machine_model::jz_func,
    &Machine_model::jnz_func,     &Machine_model::call_func,    &Machine_model::callz_func,  &Machine_model::callnz_func,
    &Machine_model::ret_func,     &Machine_model::outint_func,  &Machine_model::outstr_func, &Machine_model::inint_func,
    &Machine_model::inrint_func,  &Machine_model::hlt_func,     &Machine_model::dup_func,    &Machine_model::swap_func,
    &Machine_model::spmadd_func,  &Machine_model::spmsub_func,  &Machine_model::pop_func,    &Machine_model::enter_func,
    &Machine_model::leave_func
};
void Machine_model::run()     //Здесь реализовать зануление регистров (как должно быть написано?)
    {//установить ip, ... (как должно быть написано?)
    for(;;){
        //читаем текущий байт по ip и записываем его в перем. uint8_t opcode; (как должно быть написано?)
        bool t=(this->*procs_[opcode])();
        if(!t){return false;}
        }
    }
