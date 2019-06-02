/*
     File:    file_contents.h
     Created: 27 December 2018.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/

#ifndef FILE_CONTENTS_H
#define FILE_CONTENTS_H
#include <utility>
#include <vector>
#include <cstdint>

enum class Get_contents_return_code{
    Normal,
    Impossible_open,
    Read_error
};

using Contents = std::pair<Get_contents_return_code, std::vector<std::uint8_t>>;

Contents get_contents(const char* name);
#endif
