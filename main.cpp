#include <iostream>
#include "date.h"
#include "eon.h"

using namespace std;

int main()
{
    // This can be used as a reference on how to pass params to the Eon object
    int argc = 1;
    char a1[] = { "eon " };
    char a2[] = { "" };
    char *argv[] = { a1, a2 };

    Eon eon = Eon(argc, argv);
    return 0;
}
