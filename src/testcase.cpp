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

void TestCase::assert_file_contents_equal(const string contents, const string path, const unsigned max_row_length)
{
    string file_contents = "";
    char row[max_row_length];
    FILE *fp = fopen(path.c_str(), "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {
            if (fgets(row, max_row_length, fp) == NULL) break;
            file_contents = file_contents + string(row);
        }
        fclose(fp);
        if (file_contents.compare(contents) != 0)
        {
            cout << " FAIL Expected [" << contents << "] to be equal to [" << file_contents << "]." << endl;
        }
    }
    else
    {
        cout << " FAIL Expected [" << contents << "] to be equal to [" << file_contents << "]." << endl;
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

void TestCase::assert_true(const bool value, const string what_is_it)
{
    if (!value)
    {
        cout << " FAIL Expected [" << what_is_it << "] to be true but was false." << endl;
    }
}
