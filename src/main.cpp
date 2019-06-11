#include <iostream>
#include "Sistema.hpp"

int main() {
    Sistema sis;

    while(sis.is_running()){
        sis.ui_main();
    }

    return 0;
}

