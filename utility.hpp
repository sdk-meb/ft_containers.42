/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:29:08 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/10 12:14:01 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace   ft {

	/*
		@brief struct holding tow object of arbitrary type

		@param T1 type of first object 
		@param T2 second object type
	*/
	template < class T1, class T2>
		struct pair {

				typedef T1	first_type;
				typedef	T2	second_type;

				pair() : first ( first_type()), second (second_type()) { }
				pair (const first_type& _x, const second_type& _y) : first (_x), second (_y) { }
				template < class U1, class U2>
					pair( const pair<U1, U2>& p ) : first (p.first), second (p.second) { }
				pair&	operator= (const pair& p) {

					second = p.second;
					first = p.first;
					return *this;
				}

				first_type	first;
				second_type	second;

		};
	
	/*
		@brief functor create pair of objects
	*/
	template < class T1, class T2>	
		ft::pair< T1, T2>	make_pair (T1 t, T2 u) {

			return ft::pair< T1, T2>(t, u);
		}

};




# endif
