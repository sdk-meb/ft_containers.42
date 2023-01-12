
# include<map>
# include"map.hpp"
# include<ostream>

using namespace std;

#define Nice std::cerr << "\e[0;32m[ Nice ]" << "\e[0;0" << std::endl

int main(){

    /* member access */
    /* at */
    map<int, int>       m0;
    ft::map<int, int>   m1;
     ft::map<int, int>   m3;
int i = 43;
    m1[i] = 21;
    m0[i] = 6;
    m0[42] = 6;
    try {m1.at(0); exit(1); } catch(...){ Nice; };
    try {m0.at(0); exit(2); } catch(...){ Nice; };
    m0.at(43) = m1.at(43);
    m1.rbegin()++; ++m1.rbegin();m1.rbegin()--; --m1.rbegin();
    m1.rend()++; ++m1.rend(); m1.rend()--; --m1.rend();
    m1.begin()++; ++m1.begin();m1.begin()--; --m1.begin();
    m1.end()++; ++m1.end(); m1.end()--; --m1.end();
    m1.erase(m1.begin());
    m1.erase(m1.begin(), m1.end());
    m1.erase(i);
    m3.swap(m1);
    std::cout << m1.empty() << std::endl;
    std::cout << m1.size() << std::endl;
    m1.clear();

    return 0;
}

/*  c++ main_map.cpp -Wall -Wextra -Werror -fsanitize=address 2> re && ./a.out > out */


// template <class T>
//     class u {

//     public:
//         u( T& d): p(&d) {}
//         T* p;
//         u operator++() {p++; return u(*(--p));}
//         u& operator++(int) {p++; return *this;}
//         void operator=(u&& y){ p = y.p;}
//     };

// int main(){

// int i = 6;
//     u<int> l(i);
//     u<int> l2(++i);

//     // l2 = l++;
//       l2 = ++l;

// }