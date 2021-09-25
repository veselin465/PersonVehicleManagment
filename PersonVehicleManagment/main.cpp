#include <iostream>

#include "ControlCenter.h"
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"

using namespace std;

std::string stringToUpper(std::string str){
    for(size_t  i = 0; str[i]; i++){
        if('a' <= str[i] && str[i] <= 'z'){
            str[i] = str[i] + 'A' - 'a';
        }
    }
    return str;
}

int main(int argc, char* argv[])
{

    ControlCenter cc;

    if(argc >= 2){
        cc.loadFromFile(argv[1]);
        std::cout << "\n";
    }

    cc.loadFromFile("s.txt");

    std::string input = "";

    while(true){

        std::cout << "> ";

        getline(std::cin, input);

        if(input.size() == 0){
            continue;
        }

        if(stringToUpper(input) == "EXIT"){
            break;
        }

        try{
            const std::string output = cc.executeCommand(input);
            if(output != ""){
                std::cout << output;
            }else{
                std::cout << "    OK";
            }
        }catch(std::invalid_argument& e){
            std::cout << "  FAIL. " << e.what();
        }

        std::cout << std::endl;

    }

    return 0;
}
