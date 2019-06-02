/*
     File:    parsing_result.h
     Created: 27 December 2018.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/

#ifndef PARSING_RESULT_T_H
#define PARSING_RESULT_T_H
#include <vector>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>

struct header_t{
  size_t                    file_type=0x383231DFD1D3CC;
  unsigned __int128         begin_addr_;
  unsigned __int128         ram_size_;
  unsigned __int128         sp_begin_;
  unsigned __int128         const_begin_addr_;
  unsigned __int128         const_size_;
  unsigned __int128         var_begin_addr_;
  unsigned __int128         var_size_;
  unsigned __int128         code_begin_addr_;
  unsigned __int128         code_size_; 
};

struct parsing_result_t {
    header_t                  header_;
    
std::vector<std::uint8_t> content_;
    std::vector<uint8_t> mem_bytes_;
};

parsing_result_t parse(const std::vector<std::uint8_t>& source);
void print(parsing_result_t pr);
#endif
