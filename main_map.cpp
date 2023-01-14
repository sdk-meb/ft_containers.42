/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 03:34:08 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/14 22:08:54 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

#ifndef CSTD
	#define CSTD 1
#endif

#if CSTD
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
	ft::map<int, std::string> 	_m1;
	ft::map<int, int> 	_m2;

	 _m1[1] = "root";
	 _m1[2] = "1left";
	 _m1[3] = "left rigth";
	 _m1[4] = "rigth left";
	
	std::cout << _m1[4] << " " << std::endl;
	std::cout << _m1[2] << " " << std::endl;
	std::cout << _m1[3] << " " << std::endl;
	std::cout << _m1[1] << " " << std::endl;


ft::pair<int, std::string> tmp = ft::make_pair(9, "dfgggg");
		std::cout << (*_m1.insert ( tmp).first).second << std::endl;

	tmp.second =  "dfghjhhgggg";
		_m1.insert (_m1.end() ,tmp);

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

	ft::map<int, std::string>::iterator It  = _m1.begin();

		std::cout << It->first << std::endl;
		exit(17);
	for ( long  i = (INT_MAX * -1) ; i < INT_MAX  ; i+=12300) {

		It-- ;
		// std::cout << It ;
	}
	// ++_m1.rbegin();

	_m1.swap(_m1);
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
