#include <dirent.h>
#include <iostream>
#include "testcase.h"

using namespace std;

TestCase::TestCase() {}
TestCase::~TestCase() {}

void TestCase::assert_dir_exists(const string path)
{
    DIR *d = opendir(path.c_str());
    if (d != NULL)
    {
        closedir(d);
    }
    else
    {
        cout << " FAIL Expected directory [" << path << "] does not exist." << endl;
    }
}

void TestCase::assert_file_exists(const string path)
{
    FILE *fp = fopen(path.c_str(), "r");
    if (fp != NULL)
    {
        fclose(fp);
    }
    else
    {
        cout << " FAIL Expected file [" << path << "] does not exist." << endl;
    }
}
