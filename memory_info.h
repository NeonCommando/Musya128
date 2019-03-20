#ifndef MEMORY_INFO_H
#define MEMORY_INFO_H
#include <vector>, <cstdint>, <cstdddef>

struct Mem_block{
bool filled; //если true, то блок заполнен, иначе - не заполнен
unsigned __int128 begin_addr;
unsigned __int128 block_size;
std::vector<std::uint8_t>content;
bool executed;
};

struct Memory_info{
std::vector<Mem_block> blocks;
};
//точка входа - в блоке, имеющем индекс
#endif
