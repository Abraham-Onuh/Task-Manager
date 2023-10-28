#include <iostream>
#include "Task.h"
#include <fstream> 
#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 

using namespace std;

int main()
{

    Task trial;     //declaration of object that will be used in the running of the program

    trial.begin();     //we first load the contents of an existing file (if any)

    trial.startmenu();    //then we start the program;

    return 0;


}


