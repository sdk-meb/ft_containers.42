/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 03:34:08 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/14 04:08:58 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

#ifdef CSTD
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
#endif


#define Nice std::cerr << "\e[0;32m[ Nice ]" \
					   << "\e[0;0" << std::endl

int main()
{

	ft::map<int, int> 	_m0;
	ft::map<int, int> 	_m1;
	ft::map<int, int> 	_m2;
	// _m0.insert(std::make_pair(1,3));

	// _m0.insert(std::make_pair(1,5));

	// _m1.insert(_m0.end(), 7);

	for (long i = (INT_MAX * -1) ; i < INT_MAX  ; i+=12300 ) {

		try { std::cout << _m1[++i] << " " << std::endl; std::cout << "XE1"; }
		catch (...) { std::cout << "EX1"; }
		try { std::cout << _m1.at(i + 1) << " " << std::endl; std::cout << "XE2"; }
		catch (...) { std::cout << "EX2"; }
		try { std::cout << _m1[i + 2] << " " << std::endl; std::cout << "XE2"; }
		catch (...) { std::cout << "EX2"; }
		try { std::cout << _m1.at(i + 4) << " " << std::endl; std::cout << "XE3"; }
		catch (...) { std::cout << "EX3"; }
		try { std::cout << _m1[i + 5] << " " << std::endl; std::cout << "XE4"; }
		catch (...) { std::cout << "EX4"; }
		try { std::cout << _m1.at(i + 7) << " " << std::endl; std::cout << "XE5"; }
		catch (...) { std::cout << "EX5"; }
		
		break;
	}

	long g = 0;

	while ()
	_m1.rbegin()++;
	++_m1.rbegin();

	_m1.rbegin()--;
	--_m1.rbegin();
	_m1.rend()++;
	++_m1.rend();
	_m1.rend()--;
	--_m1.rend();
	_m1.begin()++;
	++_m1.begin();
	_m1.begin()--;
	--_m1.begin();
	_m1.end()++;
	++_m1.end();
	_m1.end()--;
	--_m1.end();
	_m1.erase(_m1.begin());
	_m1.erase(_m1.begin(), _m1.end());
	_m1.erase(g);
	_m1.swap(_m1);
	_m1.count(g);
	_m1.find(g);
	_m1.lower_bound(g);
	_m1.equal_range(g);
	std::cout << _m1.empty() << std::endl;
	std::cout << _m1.size() << std::endl;
	_m1.clear();
	exit(100);

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