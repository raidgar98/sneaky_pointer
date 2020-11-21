#include <iostream>

#include <sneaky_pointer/sneaky_pointer.hpp>

int main()
{
	//On my 10GB laptop, 15 is best i can get
	const uint8_t bits = 15;
	sneaky_pointer<int, bits> a{ new int(777ull) };
	std::cout << a << std::endl;
	a.set_pointer( new int(100ull) );
	std::cout << a << std::endl;
	a.set_flag(1, true);
	std::cout << a << std::endl;
	a.set_flag(1, false);
	std::cout << a << std::endl;
	a.set_flag(1, true);
	a.set_flag(2, true);
	a.set_flag(3, true);
	a.set_flag(4, true);
	std::cout << a << std::endl;
	a.set_pointer(new int(2000));
	std::cout << a << std::endl;
	try{ a.set_flag(bits + 1, true); }catch(const std::invalid_argument& e) { std::cout << "ERROR: " << e.what() << std::endl; }
	std::cout << a << std::endl;
	a.set_pointer(nullptr);
	std::cout << a << std::endl;

	a.set_pointer( new int(10ull) );
	a.set_number<int>(std::pow(2, bits)-1);
	std::cout << *(a.get_pointer()) << std::endl;
	std::cout << a.get_number() << std::endl;

	a.set_pointer( new int(20ull) );
	std::cout << *(a.get_pointer()) << std::endl;
	std::cout << a.get_number<int>() << std::endl;

	sneaky_pointer<std::string, bits> b{ new std::string{"sneaky peaky"} };
	std::cout << *b << std::endl;
	*b = "peaky sneaky";
	std::cout << *b << std::endl;

	sneaky_pointer<double, bits> c{ new double[20] };
	for(int i = 0; i < 20; i++)
		c[i] = i;

	for(int i = 0; i < 20; i++)
		std::cout << c[i] << std::endl;

	return 0;
}
