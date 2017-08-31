#include <iostream>
#include "configurationtest.h"
#include "eon.h"
#include "projecttest.h"
#include "treetest.h"

using namespace std;

int main()
{
    int argc = 1;
    char a1[] = { "eon " };
    char a2[] = { "" };
    const char *argv[] = { a1, a2 };

    Eon eon = Eon(argc, argv);

    ProjectTest pt;
    pt.test();

    TreeTest tt;
    tt.test();

    ConfigurationTest ct;
    ct.test();

    return 0;
}
