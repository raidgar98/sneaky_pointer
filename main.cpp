#include <iostream>

#include "sneaky_pointer.hpp"

int main()
{
    sneaky_pointer<ulli, 9429102592ull> a{ new ulli(777ull) };
    std::cout << a;
    a.set_pointer( new ulli(100ull) );
    std::cout << a;
    a.set_flag(1, true);
    std::cout << a;
    a.set_flag(1, false);
    std::cout << a;
    a.set_flag(1, true);
    a.set_flag(2, true);
    a.set_flag(3, true);
    a.set_flag(4, true);
    std::cout << a;
    a.set_pointer(new ulli(2000));
    std::cout << a;
    try{ a.set_flag(5, true); }catch(const std::invalid_argument& e) { std::cout << "ERROR: " << e.what() << std::endl; }
    std::cout << a;
    a.set_pointer(nullptr);
    std::cout << a;
    return 0;
}
