/*
     File:    file_contents.cpp
     Created: 27 December 2018.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/

#include "../include/file_contents.h"
#include "../include/fsize.h"
#include <cstdio>
#include <memory>

class Binary_file{
public:
    Binary_file() = default;
    Binary_file(const char* name) : fptr(fopen(name, "rb")) {};
    ~Binary_file() {fclose(fptr);};
    Binary_file& operator=(const Binary_file&) = delete;
    Binary_file(const Binary_file&) = delete;

    FILE* get() const {return fptr;};
private:
    FILE* fptr = 0;
};

Contents get_contents(const char* name){
    Contents result;
    Binary_file f(name);

    FILE* fptr = f.get();
    if(!fptr){
        result.first = Get_contents_return_code::Impossible_open;
        return result;
    }

    long file_size = fsize(fptr);
    if(!file_size){
        result.first = Get_contents_return_code::Impossible_open;
        return result;
    }
    
    auto s = std::vector<std::uint8_t>(file_size);
    unsigned char* data_ptr = s.data();
    size_t read_count = fread(data_ptr, 1, file_size, fptr);
    if(read_count != (unsigned long)file_size){
        result.first = Get_contents_return_code::Read_error;
        return result;
    }
    
    result.first = Get_contents_return_code::Normal;
    result.second = s;
    return result;
}
