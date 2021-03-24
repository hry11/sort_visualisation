# sort_visualisation
Program that allows the visualisation of different sorting algorithms using the SFML library.  
Nothing Very fancy or user-friendly, the code isn't mind-blowingly efficient (some variable gets passed as an argument in a function solely to be used as an argument when calling another function, which I reckon takes some space on the stack), but it gets the job done.  
**ON LINUX**  
Install SFML, then compile the code with the following:  
`g++ -c sort.cpp && g++ sort.o -o sort -lsfml-graphics -lsfml-window -lsfml-system`  
the program takes two command line arguments:  
-An integer for the size of the list to sort  
-An integer between 1 and 5 for the algorithm to apply:  
1: Bubble sort  
2: Selection sort  
3: Insertion sort  
4: Merge sort  
5: Quicksort  
`./sort [SIZE] [ALGORITHM]`  
