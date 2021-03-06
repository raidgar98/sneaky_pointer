#include <iostream>
#include <stdexcept>
#include <bitset>
#include <array>
#include <memory>
#include <cmath>
#include <limits>
#include <map>

// This is not a smart pointer, you have to take care about memory managment!
template <typename T, uint8_t empty_bits = 4>
class sneaky_pointer
{
	T *__pointer = nullptr;
public:

	sneaky_pointer() { set_pointer(nullptr); }

	template<uint8_t _bits>
	sneaky_pointer(const sneaky_pointer<T, _bits> &src)
	{
		set_pointer(nullptr);
		set_pointer(src.get_pointer());
		sync_bits(src);
	}

	template<uint8_t _bits>
	sneaky_pointer(sneaky_pointer<T, _bits> &&src)
	{
		set_pointer(nullptr);
		__pointer = src.__pointer;
		sync_bits(src);
	}

	explicit sneaky_pointer(T *src)
	{
		set_pointer(nullptr);
		set_pointer(src);
	}

	~sneaky_pointer()
	{
		set_pointer(nullptr);
	}

	bool get_flag(const unsigned int num) const
	{
		if (num == 0 || num >= (empty_bits + 1) || __pointer == nullptr)
			try
			{
				throw std::invalid_argument("has to be in range <1; " +
											std::to_string((empty_bits)) + ">");
			}
			catch (...)
			{
				throw;
			}
		int64_t mask = 1;
		mask <<= (sizeof(T *) * 8) - num;
		return (reinterpret_cast<int64_t>(__pointer) & mask);
	}

	void set_flag(const unsigned int num, const bool flag)
	{
		if(get_flag(num) == flag) return;
		if (num == 0 || num >= (empty_bits + 1) || __pointer == nullptr)
			try
			{
				throw std::invalid_argument("has to be in range <1; " +
											std::to_string((empty_bits)) + ">");
			}
			catch (...)
			{
				throw;
			}
		int64_t mask = 1;
		mask <<= (sizeof(T *) * 8) - num;
		__pointer = reinterpret_cast<T *>(reinterpret_cast<int64_t>(__pointer) ^ mask);
	}

	T *get_pointer() const noexcept
	{
		int64_t temp = reinterpret_cast<int64_t>(__pointer);
		temp <<= (empty_bits + 1);
		temp >>= (empty_bits + 1);
		return reinterpret_cast<T *>(temp);
	}

	void set_pointer(T *ptr) noexcept
	{
		static_assert(sizeof(T *) == 8, "x64 architecture required.");
		static_assert(empty_bits < 31, "too many empty bits.");
		int64_t mask = reinterpret_cast<int64_t>(__pointer);
		mask >>= (sizeof(T *) * 8) - (empty_bits + 1);
		mask <<= (sizeof(T *) * 8) - (empty_bits + 1);
		__pointer = reinterpret_cast<T *>(reinterpret_cast<int64_t>(ptr) ^ mask);
	}

	template <typename num_type = uint64_t>
	num_type get_number() const noexcept
	{
		int64_t mask = reinterpret_cast<int64_t>(__pointer);
		mask >>= (sizeof(T *) * 8) - (empty_bits + 1);
		return static_cast<num_type>(mask);
	}

	template <typename num_type = uint64_t>
	void set_number(num_type num) noexcept
	{
		int64_t ptr = reinterpret_cast<uint64_t>(get_pointer());
		uint64_t mask = static_cast<uint64_t>(num);
		mask <<= (sizeof(T *) * 8) - (empty_bits + 1);
		__pointer = reinterpret_cast<T *>(ptr ^ mask);
	}

	T *const operator->() const noexcept
	{
		return static_cast<T *const>(get_pointer());
	}

	T &operator*()
	{
		return *get_pointer();
	}

	T &operator[](const size_t idx)
	{
		return get_pointer()[idx];
	}


	// template <typename T, uint8_t empty_bits, bool val>
	inline friend std::ostream &operator<<(std::ostream &output, const sneaky_pointer&src)
	{
		union{
			uint64_t out;
			T* in;
		} conv;

		conv.in = src.__pointer;

		std::bitset< sizeof(T) * 8 > bs{ conv.out };
		output << bs.to_string();
		return output;
	}

private:

	template<uint8_t _bits>
	void sync_bits(const sneaky_pointer<T, _bits>& ext )
	{
		uint8_t i = 0;
		while( i <= _bits && i <= empty_bits )
		{
			set_flag(i, ext.get_flag(i));
			i++;
		}
	}

};