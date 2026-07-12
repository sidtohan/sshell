#include <iostream>
#include <sstream>
#include <string>


// TODOS;
// 1. simple input loop. (DONE)
// 2. call actual func via fork api.
// 3. redirection support.
// 4. pipe etc.
// 5. catching signals.
void inputLoop() {
    std::string buf;
    
    while (true) {
        std::stringstream inp_stream; // Must make new input stream every time.. Else we can have leftover data.
       
        std::cout << ">> ";
        getline(std::cin, buf);
        inp_stream << buf;

        // Now tokenize.
        while (inp_stream >> buf) {
            // Now we have access to token.
            std::cout << buf << '#';
        }
        std::cout << std::endl; // Flush
    }
}

// Simple Shell Implementation.
int main() {
    inputLoop(); 
}
