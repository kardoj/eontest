#ifndef EONTEST_VECTORHELPER_H
#define EONTEST_VECTORHELPER_H

#include <string>
#include <vector>

class VectorHelper {
    public:
        // The purpose of this is to handle out of bounds
        static std::string at(std::vector<std::string> vector, int position);
};


#endif //EONTEST_VECTORHELPER_H
