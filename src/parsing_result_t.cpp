/*
     File:    parsing_result_t.cpp
     Created: 27 December 2018.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/

#include "../include/parsing_result_t.h"

parsing_result_t parse(const std::vector<std::uint8_t>& source) {
    parsing_result_t result;
    result.header_ = *((header_t*)(source.data()));
    auto& content = result.content_;
    content.insert(content.end(), source.begin() + sizeof(header_t), source.end());
    return result;
}

char int_to_hex_digit(int x) {
    char result = '0';
    switch (x) {
        case 0 ... 9:
        result = '0' + x;
        break;
        case 10 ... 15:
        result = 'A' + x - 10;
        break;
    }
    return result;
}

std::string uint128tostr(unsigned __int128 x){
    unsigned __int128 y = x;
    int i = 32;
    char digits[33];
    std::string result;
    digits[i] = '\0';
    i--;
    do {
        digits[i] = int_to_hex_digit(y & 0xF);
        y>>=4;
        i--;
    } while(y!=0);
    if(i>=0) {
        while(i>=0) {
            digits[i]='0';
            i--;
        }
    }
    result = std::string(digits);
    return result;
}

void print(parsing_result_t pr) {
    std::cout << "Header:\n"; 
    std::cout << "00-07 file_type: " << uint128tostr(pr.header_.file_type) << "\n";
    std::cout << "08-17 begin_addr_: " << uint128tostr(pr.header_.begin_addr_) << "\n";
    std::cout << "18-27 ram_size_: " << uint128tostr(pr.header_.ram_size_) << "\n";
    std::cout << "28-37 entry_offset_: " << uint128tostr(pr.header_.entry_offset_) << "\n";
    std::cout << "38-47 volume_constants_: " << uint128tostr(pr.header_.volume_constants_) << "\n";
    std::cout << "48-57 variable_offset_: " << uint128tostr(pr.header_.variable_offset_) << "\n";
    std::cout << "58-67 variable_size_: " << uint128tostr(pr.header_.variable_size_) << "\n";
    std::cout << "68-77 code_offset_: " << uint128tostr(pr.header_.code_offset_) << "\n";
    std::cout << "78-87 size_code_: " << uint128tostr(pr.header_.size_code_) << "\n";
    std::cout << "88-97 initial_stack_value_: " << uint128tostr(pr.header_.initial_stack_value_) << "\n";
    printf("content:\n");
    
    auto& v=pr.content_;
size_t num_elems=v.size();
for(size_t i=0; i<num_elems; i+=16){
printf("%s:␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X␣%02X\n", uint128tostr(i).c_str(), v[i], v[i+1], v[i+2], v[i+3], v[i+4], v[i+5], v[i+6], v[i+7], v[i+8], v[i+9], v[i+10], v[i+11], v[i+12], v[i+13], v[i+14], v[i+15]);
}
}

