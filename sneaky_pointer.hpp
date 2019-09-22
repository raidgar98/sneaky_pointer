#include <iostream>
#include <stdexcept>
#include <bitset>
#include <array>
#include <memory>
#include <limits>

using ulli = unsigned long long int;

template<typename T, ulli total_mem = 2ull * std::numeric_limits<size_t>::max(), bool __debug = false, std::ostream* __log_destination = nullptr >
class sneaky_pointer final
{
    #define out (*__log_destination)
    #define loggable __debug  && __log_destination != nullptr
    #define log(msg) if(loggable) out << std::endl << msg << std::endl
    #define mov_num 5

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
            // log("[LOG] Pointer secured");
        }
    }

    bool get_flag(const unsigned int num) const
    {
        if(num == 0 || num >= mov_num || __pointer == nullptr)
            try{ throw std::invalid_argument("has to be in range <1; " +
                std::to_string(mov_num) + ">"); }catch(...){ throw; }
        // log("[LOG] Getting flag: " + std::to_string(num));
        int64_t mask = 1;
        mask <<= (sizeof(T*) * 8) - num;
        return reinterpret_cast<int64_t>(__pointer) & mask;
    }

    void set_flag(const unsigned int num, const bool flag)
    {
        if(num == 0 || num >= mov_num || __pointer == nullptr)
            try{ throw std::invalid_argument("has to be in range <1; " +
                std::to_string(mov_num) + ">"); }catch(...){ throw; }
        int64_t mask = 1;
        mask <<= (sizeof(T*) * 8) - num;
        __pointer = reinterpret_cast<T*>(reinterpret_cast<int64_t>(__pointer) ^ mask);
        log("[LOG] Setted flag: "+std::to_string(num) + ", to: " + std::to_string(flag));
        log("[LOG] Actual bits: " + std::bitset<sizeof(T*)*8>(reinterpret_cast<int64_t>(__pointer)).to_string());
    }
    
    T * get_pointer() const noexcept
    {
        int64_t temp = reinterpret_cast<int64_t>(__pointer);
        temp <<= mov_num;
        temp >>= mov_num;
        // log("[LOG] Getting pointer");
        return reinterpret_cast<T*>(temp);
    }

    void set_pointer(T * ptr) noexcept
    {
        static_assert(sizeof(T*) == 8, "x64 architecture required.");
        int64_t mask = reinterpret_cast<int64_t>(__pointer);
        mask >>= (sizeof(T*) * 8) - mov_num;
        mask <<= (sizeof(T*) * 8) - mov_num;
        this->~sneaky_pointer();
        __pointer = reinterpret_cast<T*>(reinterpret_cast<int64_t>(ptr) ^ mask);
        log("[LOG] Setted pointer");
        log("[LOG] Actual bits: " + std::bitset<sizeof(T*)*8>(reinterpret_cast<int64_t>(__pointer)).to_string());
    }

};

template<typename T, ulli total_mem, bool __debug = false, std::ostream * __log_destination = nullptr >
std::ostream& operator<<(std::ostream& output, const sneaky_pointer<T, total_mem, __debug, __log_destination>& src)
{
    // DEV
    // output << src.get_pointer() << " = " << (src.get_pointer() == nullptr ? NULL : *src.get_pointer());
    // for(int i = 1; i < mov_num; i++)
    //     output << ";\t" << i <<": " << (src.get_flag(i) ? "True" : "False");
    // output << std::endl;
    // RELEASE
    output << *(src.get_pointer());
    return output;
}

//SRC: https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-output-of-command-within-c-using-posix
inline std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}