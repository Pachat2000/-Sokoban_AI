#include <iostream>

#include <SWI-Prolog.h>
#include <SWI-Stream.h>



int main(int argc, char** argv) {

    PL_initialise(argc, argv);

    PlTermv args(1);
    args[0] = "main.pl";
    PlQuery pq("consult", args);
    if (pq.next_solution()) {
        std::cout << "Command OK\n";
    } else {
        std::cout << "Command failed\n";
    }

    PlTermv inputs(3);
    inputs[0] = "sin(x)";
    inputs[1] = "x";
    inputs[2] = "R";


   
    try {
        PlQuery pq_sin("d", inputs);

        while (pq_sin.next_solution()) {
            std::cout << (char*) inputs[0] << std::endl;
        }
        std::cout << "Query OK\n";
    } catch (PlException& e) {
        std::cout << (char*) e << std::endl;
        std::cout << "Query error\n";
    }


    return 1;
}