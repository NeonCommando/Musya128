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
  unsigned __int128         entry_offset_;
  unsigned __int128         volume_constants_;
  unsigned __int128         variable_offset_;
  unsigned __int128         variable_size_;
  unsigned __int128         code_offset_;
  unsigned __int128         size_code_;
  unsigned __int128         initial_stack_value_; 
};

struct parsing_result_t {
    header_t                  header_;    
    std::vector<std::uint8_t> content_;
};

parsing_result_t parse(const std::vector<std::uint8_t>& source);
void print(parsing_result_t pr);
#endif
