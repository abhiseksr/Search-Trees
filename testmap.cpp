// testmap.cpp

// without using constant reference 
// to the object of class Map

#include "map.h"
#include <iostream>
using namespace std;

int main()
{

    // here "map" is used for both
    // read-write operation

    Map map;

    // insertion
    map[132] = 3;
    map[34] = 5;
    map[42] = 7;
    map[-83] = 4;
    map[66] = 9;
    map[197] = 8;
    map[-2] = -88;

    // updation
    map[42] = 55;

    int arr[] = { 132, -34, 34, 42,
                 -83, 60, 66,  197,
                 -2, 56, 1,   -3442 };
    cout << "key: value\n";
    for (int i = 0; i < sizeof(arr) / 
         sizeof(int); i++) {
        // accessing value from its 
        // respective key

        // when we are searching for the
        // key and if it is not found then 
        //a new key is created with value 0
        // and then 0 is returned

        // if its found then its value is 
        //simply returned

        cout << '(' << arr[i] << ":"
             << map[arr[i]] << ") , ";
    }
    cout << endl;
    return 0;
}