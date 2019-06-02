/*
     File:    musya128.h
     Created: 26 March 2019.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/


#ifndef MUSYA128_H
#define MUSYA128_H
#include <memory>
#include "../include/parsing_result_t.h"

class MUSYA128{
public:
    MUSYA128();
    MUSYA128(const MUSYA128&);
    ~MUSYA128();
    MUSYA128(const parsing_result_t& image);
    void set_image(const parsing_result_t& image);
    void run();
    parsing_result_t get_image()const;
    
private:
    struct Impl;
    std::shared_ptr<Impl>pimpl_;
};
#endif
