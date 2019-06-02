/*
     File:    eparsing.cpp
     Created: 27 December 2018.
     Author:  Федотов Николай Алексеевич
     E-mail: nick1999fedotov@gmail.com
*/

#include <cstdio>
#include <map>
#include "../include/file_contents.h"
#include "../include/parsing_result_t.h"

  std::vector<std::uint8_t> init_testing(const char* name){
    auto empty = std::vector<std::uint8_t>(0);
    auto contents = get_contents(name);
    auto content = contents.second;
    switch(contents.first){
        case Get_contents_return_code::Normal:
            if(content.size() == 0){
                puts("File length is equal to zero.");
                return empty;
            }else{
                return contents.second;
            }

        case Get_contents_return_code::Impossible_open:
            puts("Unable to open file.");
            return empty;

        case Get_contents_return_code::Read_error:
            puts("Error reading file.");
            return empty;
    }
    return empty;
}


static const char* help_str =
    R"~(Usage: myauka [option] file
Options:
    --help    Display this text.
    --version Display version information)~";

static const char* version_str =
    R"~(Myauka, lexical analyzer generator, v.1.1.0
(c) Fedotov Nikolay Alekseevich 2018)~";

typedef void (*FuncForKey)();  
void version(){
    puts(version_str);
}

void help(){
    puts(help_str);
}

std::map<std::string, FuncForKey> option_func = {
    {"--version", version}, {"--help", help}
};


int main(int argc, char* argv[]){
    if(argc == 1){
        puts("Not enough arguments!");
        puts("Use --help to print available arguments");
        return 0;
    }

    auto it = option_func.find(argv[1]);
    if(it != option_func.end()){
        (it->second)();
        return 0;
    }
    
    auto t = init_testing(argv[1]);
    
        
    parsing_result_t pr = parse(t);
    print(pr);
    return 0;
}
