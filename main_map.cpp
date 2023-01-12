
# include<map>
# include"map.hpp"
# include<ostream>

using namespace std;

#define Nice std::cerr << "\e[0;32m[ Nice ]" << "\e[0;0" << std::endl

int main(){

    /* member access */
    /* at */
    // map<int, int>       m0;
    // m0.insert(std::make_pair(1,3));

    // m0.insert(std::make_pair(1,5));

    // m0.insert(m0.end(), 7);
    ft::map<int, int>   mm;
//    ft::map<int, int>   m1;

int i = 43;
    // m1[i] = 32;
    mm[i] = 21;
    mm[i] = 6;
    mm[i] = mm[2];
    mm[i];
    // mm[i] = 2;
try{
    std::cout << mm[i] << " "   << std::endl;
}catch(const char* e) {std::cout << e << std::endl;}
    // try {m1.at(0); exit(1); } catch(...){ Nice; }
    try {mm.at(0); exit(1); } catch(...){ Nice; }
    // try {mm.at(42) = m1.at(43); Nice; } catch(...){ exit(1); }
    
    // // // // m1.rbegin()++; ++m1.rbegin();m1.rbegin()--; --m1.rbegin();
    // // // // m1.rend()++; ++m1.rend(); m1.rend()--; --m1.rend();
    // // // // m1.begin()++; ++m1.begin();m1.begin()--; --m1.begin();
    // // // // m1.end()++; ++m1.end(); m1.end()--; --m1.end();
    // // m1.erase(m1.begin());
    // // // m1.erase(m1.begin(), m1.end());
    // m1.erase(i);
    // mm.swap(m1);
    // m1.count(i);
    // m1.find(i);
    // m1.lower_bound(i);
    // m1.equal_range(i);
    // std::cout << m1.empty() << std::endl;
    // std::cout << m1.size() << std::endl;
    // m1.clear();

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