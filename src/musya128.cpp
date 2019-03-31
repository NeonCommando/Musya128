/*
     File:    musya128.cpp
     Created: 26 March 2019.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/

#include "../include/musya128.h"
#include "../include/machine_model.h"

struct Musya128::Impl{
public:
    Musya128()=default;
    Musya128(const Musya128&)=default;
    ~Musya128()=default;
    Musya128(const ssrsif& image):
        image_{image}{}
    void set_image(const ssrsif& image)
    {
        image_=image;
    }
    ssrsif get_image()const
    {
        return image_;
    }
    void run();
    
private:
    ssrsif image_;
    Machine_model model;
    void convert_image_to_model();
};

Musya128::Musya128(): pimpl_{std::make_shared<Impl>()}{}
Musya128::Musya128(const ssrsif& image):pimpl_{
    std::make_shared<Impl>(image)}{}
Musya128::~Musya128()=default;
void Musya128::set_image(const ssrsif& image)
{
    pimpl_->set_image(image);
}
ssrsif Musya128::get_image()const
{
    return pimpl_->get_image();
}
void Musya128::run()
{
    pimpl_->run();
}
