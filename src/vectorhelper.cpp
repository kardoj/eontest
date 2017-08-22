#include "vectorhelper.h"

using namespace std;

string VectorHelper::at(vector<string> vector, int position)
{
    if (vector.size() > position) return vector.at(position);
    return "Vector does not have that many members";
}
