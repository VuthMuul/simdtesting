# ARM Neon Testing

To run, it requires an arm64 processor. Compiling requires G++ and make. Run make main, then run the main executable. Edit the g++ flags to play around with compile optimisation levels. -O2 and above will auto vectorise code, otherwise use -O1; and run make clean run before building if changed. Edit values in consts.hpp for different vector sizes, tolerances, depth etc. Change evaluated tests in tests.cpp. Defaults to fastest of 10 for each implementation
