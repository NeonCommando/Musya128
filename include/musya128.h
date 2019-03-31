/*
     File:    musya128.h
     Created: 26 March 2019.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/


#ifndef MUSYA128_H
#define MUSA128_H
#include <memory>

class MUSYA128{
public:
    MUSYA128();
    MUSYA128(const MUSYA128&);
    ~MUSYA128();
    MUSYA128(const ssrsif& image);
    //ssrsif = структура_с_разобранным_содержимым_исполняемого_файла
    void set_image(const ssrsif& image);
    void run();
    ssrsif get_image()const;
    
private:
    struct Impl;
    std::shared_ptr<Impl>pimpl_;
};
#endif
