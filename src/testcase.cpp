#include <dirent.h>
#include <iostream>
#include <stdio.h>
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
void TestCase::assert_false(const bool value, const string what_is_it)
{
    if (value)
    {
        cout << " FAIL Expected [" << what_is_it << "] to be false but was true." << endl;
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

void TestCase::remove_dir_recursively(const string path)
{
    DIR *d = opendir(path.c_str());
    dirent *ent = 0;
    string ent_path, ent_name;
    if (d != NULL)
    {
        while((ent = readdir(d)) != NULL)
        {
            ent_name = string(ent->d_name);
            if (ent_name.compare(".") == 0 || ent_name.compare("..") == 0) continue;

            ent_path = path + "/" + ent_name;
            if (ent->d_type == DT_REG)
            {
                if (remove(ent_path.c_str()) != 0)
                {
                    cout << " ERROR TestCase::remove_dir_recursively could not remove a file: " << ent_path << endl;
                    break;
                }
            }
            else if (ent->d_type == DT_DIR)
            {
                remove_dir_recursively(ent_path);
            }
            else
            {
                cout << " ERROR TestCase::remove_dir_recursively received a path to an unknown entity: " << ent_path << endl;
                break;
            }
        }
        closedir(d);
        if (rmdir(path.c_str()) != 0)
        {
            cout << " ERROR TestCase::remove_dir_recursively could not remove a directory: " << ent_path << endl;
        }
    }
    // Not finding a given directory is intentionally left unhandled to allow for "just making sure" removals
}

void TestCase::assert_equal(const string one, const string two)
{
    if (one.compare(two) != 0)
    {
        cout << " FAIL Expected a string [" << one << "] to be equal to [" << two << "]." << endl;
    }
}
