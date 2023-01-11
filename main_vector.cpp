/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:00:13 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/11 14:46:00 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

# include"vector.hpp"
#include <vector>


using namespace std;

int test(1);

#define ko  std::cerr << "\e[0;32m[ OK ]("<<  test++ <<")\e[0;0" << std::endl
#define ok  std::cerr << "\e[0;32m[ KO ]("<<  test++ <<")\e[0;0" << std::endl


int main( )
{

   ft::vector<string> vft;
   vector<string> vstd;

   // vft.assign(3,"sdk-meb");
   // vft.assign(vft.begin(), vft.end());
   vft.data();

   vft.size() == vstd.size() ? ok : ko ;
   vft.capacity() == vstd.capacity() ? ok : ko ;
 
   try { std::cout << vft.at(0) << std::endl; std::cout << vstd.at(0) << std::endl; ok; }
   catch (...) { 
      try {  std::cout << vstd.at(0) << std::endl; ko; }
      catch (...) {
         try {  std::cout << vft.at(0) << std::endl; ko; }
         catch (...) { ok; }
      }  }
   

}

