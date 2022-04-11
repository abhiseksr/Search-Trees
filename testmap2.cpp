// testmap2.cpp

// using constant reference to the object
//for searching

#include "map.h"
#include <iostream>
using namespace std;

int main()
{

    // we will use "write" for write operation

    Map write;

    // creating a const reference to the object
    // "write".

    // "read" will be used for read-only operation.

    const Map& read = write;

    // insertion
    write[132] = 3;
    write[34] = 5;
    write[42] = 7;
    write[-83] = 4;
    write[66] = 9;
    write[197] = 8;
    write[-2] = -88;

    // updating
    write[42] = 55;

    int arr[] = { 132, -34, 34, 42, -83, 60,
                  66,  197, -2, 56, 1,   -3442 };
    cout << "key: value\n";
    for (int i = 0; i < sizeof(arr) / sizeof(int);
         i++) {
        // accessing value from its respective key

        // when we are searching for the key and if 
        //it is not found then a new key is not 
        //created instead 0 is returned without any 
        // affect on the map

        // if its found then its value is simply 
        //returned

        cout << '(' << arr[i] << ":" << read[arr[i]]
             << "),  ";
    }
    cout << endl;
    return 0;
}