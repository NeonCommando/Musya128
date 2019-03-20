#ifndef MUSYA128_H
#define MUSA128_H
#include <memory> //...

class MUSYA128{
public:
    MUSYA128();
    MUSYA128(const MUSYA128&);
    ~MUSYA128();
    MUSYA128(const ssrsif& image);
    //ssrsif = структура_с_разобранным_содержимым_исп_файла
    void set_image(const ssrsif& image);
    void run();
    ssrsif get_image()const;
    
private:
    struct Impl;
    std::shared_ptr<Ipl>pimpl_;
};
#endif
