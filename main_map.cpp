
# include<map>
# include"map.hpp"
# include<ostream>

using namespace std;

#define Nice

int main(){

    /* member access */
    /* at */
    map<int, int>       m0;
    ft::map<int, int>   m1;

    m1[43] = 21;
    m0[43] = 6;
    m0[42] = 6;
    try {m1.at(0); exit(1); } catch(...){ Nice };
    try {m0.at(0); exit(2); } catch(...){ Nice };
    m0.at(43) = m1.at(43);
    m1.rbegin()++; ++m1.rbegin();m1.rbegin()--; --m1.rbegin();
    m1.rend()++; ++m1.rend(); m1.rend()--; --m1.rend();
    m1.begin()++; ++m1.begin();m1.begin()--; --m1.begin();
    m1.end()++; ++m1.end(); m1.end()--; --m1.end();

    std::cout << m1.empty() << std::endl;
    std::cout << m1.size() << std::endl;
    m1.clear();

    return 0;
}

/*  c++ main_map.cpp -Wall -Wextra -Werror -fsanitize=address 2> re && ./a.out > out */