/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 22:13:00 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/04 12:25:56 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST___
#define TEST___

# include<iostream>
    # include<vector>

#ifndef LEET
    #define LEET 0
	#error LEET UNDEFINED
#endif

#if LEET != 1337
	# include<set>
    # include<map>
    # include<stack>
	namespace CCLIB = std;
#else
	# include<set.hpp>
    # include<map.hpp>
    # include<vector.hpp>
    # include<stack.hpp>
	namespace CCLIB = ft;
#endif

#define test(str) std::cout << std::endl << "\e[36********************* < " << str <<" > *********************\e[0m" << std::endl

void stk_test();
void vec_test();
void set_test();
void map_test();


# endif