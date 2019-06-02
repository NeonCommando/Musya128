/*
     File:    memory_info.h
     Created: 26 March 2019.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/


#ifndef MEMORY_INFO_H
#define MEMORY_INFO_H
#include <vector>
#include <cstdint>
#include <cstddef>

struct Mem_block{
bool filled;
unsigned __int128 begin_addr;
unsigned __int128 block_size;
std::vector<std::uint8_t>content;
bool executed;
};

struct Memory_info{
std::vector<Mem_block> blocks;
};

#endif
