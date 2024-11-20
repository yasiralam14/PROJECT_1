#include <iostream>

#include "homework_4.h"

namespace ipb {

template <typename T>
int count(named_vector<T>& namedVector) {
    return namedVector.vector_data.size();
}
template <typename T>
T accumulate(named_vector<T>& namedVector) {
    T sum{};
    for (const auto& element : namedVector.vector_data) {
        sum = sum + element;
    }
    return sum;
};

}  // namespace ipb