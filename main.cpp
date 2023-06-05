#include <iostream>

#include "tests.hpp"

using namespace std;

int main() {
    cout << "generating vectors" << endl;
    Setup();
    
    cout << "Test,Imp 1,Time (ms),Imp 2,Time (ms),Speedup %" << endl;
    RunTests();
}
