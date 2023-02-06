#include <iostream>
#include <string>
#include <deque>
# include <stdlib.h>

# include "test.hpp"

#define VEC false
#define MAP false
#define SET false

// MAX_RAM 4 294 967 296 ( 4294967296 )

#define MAX_RAM    4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public CCLIB::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename CCLIB::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	CCLIB::vector<std::string> vector_str;
	CCLIB::vector<int> vector_int;
	CCLIB::stack<int> stack_int;
	CCLIB::vector<Buffer> vector_buffer;
	CCLIB::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	CCLIB::map<int, int> map_int;
	CCLIB::set<int> set_int;

	for (int i = 0; VEC and i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; VEC and i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	if (VEC)
	CCLIB::vector<Buffer>().swap(vector_buffer);

	if (VEC)
	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}

	for (int i = 0; MAP and i < COUNT; ++i)
	{
		map_int.insert(CCLIB::make_pair(rand(), rand()));
	}
	int sum = 0;
	for (int i = 0; MAP and i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	if (1)
	{
		CCLIB::map<int, int> copy = map_int;
	}

	for (int i = 0; SET and i < COUNT; ++i)
	{
		set_int.insert(rand());
	}

	sum = 0;
	for (int i = 0; SET and i < COUNT; i++)
	{
		int access = rand();
		set_int.insert(access);
	}
	if (SET)
	{
		CCLIB::set<int> copy = set_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
}
	std::cout << std::endl;

	{
		vec_test();
		map_test();
		stk_test();
		set_test();
	}
	std::cout << std::endl;

	#if  defined(__has_feature)
	# if not __has_feature(address_sanitizer)
	#if LEET ==  1337
    	system ("leaks rec_cs");
	#else
		system ("leaks org_cs");
	#endif
    #endif
	#endif
}
