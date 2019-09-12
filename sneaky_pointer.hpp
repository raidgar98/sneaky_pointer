#include <iostream>
#include <stdexcept>

template<typename T>
class sneaky_pointer final
{
    T * __pointer = nullptr;

public:
    
    sneaky_pointer() { set_pointer(nullptr); }
    sneaky_pointer(const sneaky_pointer&) = delete;
    sneaky_pointer(sneaky_pointer&& src) { set_pointer(src.__pointer); src.__pointer = nullptr; }

    explicit sneaky_pointer(T * src) { set_pointer(src); }

    ~sneaky_pointer()
    {
        if(__pointer != nullptr)
        {
            __pointer = get_pointer();
            delete __pointer;
            __pointer = nullptr;
        }
    }

    bool get_flag(const unsigned int num) const
    {
        if(num == 0 || num >= 4 || __pointer == nullptr)
            try{ throw std::invalid_argument("has to be in range <1; 3>"); }catch(...){ throw; }
        int64_t mask = 1;
        mask <<= (sizeof(T*) * 8) - num;
        return reinterpret_cast<int64_t>(__pointer) & mask;
    }

    void set_flag(const unsigned int num, const bool flag)
    {
        if(num == 0 || num >= 4 || __pointer == nullptr)
            try{ throw std::invalid_argument("has to be in range <1; 3>"); }catch(...){ throw; }
        int64_t mask = 1;
        mask <<= (sizeof(T*) * 8) - num;
        __pointer = reinterpret_cast<T*>(reinterpret_cast<int64_t>(__pointer) ^ mask);
    }
    
    T * get_pointer() const noexcept
    {
        int64_t temp = reinterpret_cast<int64_t>(__pointer);
        temp <<= 4;
        temp >>= 4;
        return reinterpret_cast<T*>(temp);
    }

    void set_pointer(int * ptr) noexcept
    {
        static_assert(sizeof(T*) == 8, "x64 architecture required.");
        int64_t mask = reinterpret_cast<int64_t>(__pointer);
        mask >>= (sizeof(T*) * 8) - 4;
        mask <<= (sizeof(T*) * 8) - 4;
        this->~sneaky_pointer();
        __pointer = reinterpret_cast<T*>(reinterpret_cast<int64_t>(ptr) ^ mask);
    }

};

template<typename T>
std::ostream& operator<<(std::ostream& output, const sneaky_pointer<T>& src)
{
    output << src.get_pointer() << " = " << (src.get_pointer() == nullptr ? NULL : *src.get_pointer());
    for(int i = 1; i < 4; i++)
        output << ";\t" << i <<": " << (src.get_flag(i) ? "True" : "False");
    output << std::endl;
    return output;
}