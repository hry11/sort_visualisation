# sort_visualisation
Program that allows the visualisation of different sorting algorithms using the SFML library.
Nothing Very fancy or user-friendly, the code isn't mind-blowingly efficient (some variable gets passed as an argument in a function solely to be used as an argument when calling another function, which I reckon takes some space on the stack), but it gets the job done.
**ON LINUX**
Install SFML, then compile the code with the following:
`g++ -c sort.cpp && g++ sort.o -o sort -lsfml-graphics -lsfml-window -lsfml-system`
the program takes one command line argument for the size of the list to sort.
`./sort [SIZE]`
