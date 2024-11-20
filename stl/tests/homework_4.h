#include <string>
#include <vector>

namespace ipb {
template <typename T>
struct named_vector {
    std ::vector<T> vector_data;
    std::string vector_name;
    named_vector<T>(const std::string& name, std::vector<T> vector)
        : vector_name(name), vector_data(vector) {}
    std::vector<T> vector() { return vector_data; }
    std::string name() { return vector_name; }
    std::size_t size() { return vector_data.size() + 1; }
    void resize(int n) { vector_data.resize(n); }
    void resize(int n, T value) { vector_data.resize(n, value); }
    int capacity() { return vector_data.capacity(); }
    void reserve(int n) { vector_data.reserve(n); }
    T& at(size_t index) { return vector_data.at(index); }
    T& operator[](size_t index) { return vector_data[index]; }
    T& front() { return vector_data.front(); }
    T& back() { return vector_data.back(); }
    T* data() { return vector_data.data(); }
    bool empty() { return vector_data.empty() && vector_name.empty(); }
    void push_back(T value) { vector_data.push_back(value); }
    T pop_back() { return vector_data.pop_back(); }
};
template <typename T>
int count(named_vector<T>& namedVector);
template <typename T>
T accumulate(named_vector<T>& namedVector);
}  // namespace ipb