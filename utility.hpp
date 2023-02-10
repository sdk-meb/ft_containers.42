/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:29:08 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/10 16:19:08 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP


namespace   ft {

	/**
		@brief struct holding tow object of arbitrary type

		@param T1 type of first object 
		@param T2 second object type
	*/
	template < class T1, class T2>
		struct pair {

				typedef  T1	first_type;
				typedef	 T2	second_type;

				pair() : first ( first_type()), second (second_type()) { }
				pair (const first_type& _x, const second_type& _y) : first (_x), second (_y) { }
				template < class U1, class U2>
					pair( const pair<U1, U2>& p ) : first (p.first), second (p.second) { }

				pair&	operator= (const pair& p)  {

					second = p.second;
					first = p.first;
					return *this;
				}

				first_type	first;
				second_type	second;

		};
	
	/**
		@brief template function create pair of objects
	*/
	template < class T1, class T2>	
		ft::pair< T1, T2>	make_pair (T1 t, T2 u) {

			return ft::pair< T1, T2>(t, u);
		}



	template <class InputIt1, class InputIt2>
		bool	equal (InputIt1 frst1, InputIt1 last1, InputIt2 frst2){

			for (; frst1 not_eq last1; ++frst1, ++frst2)
				if (frst1.operator*() not_eq frst2.operator*())
					return false;
			return true;
		}


	template < class InputIt1, class InputIt2>
		bool	lexicographical_compare (InputIt1 frst1, InputIt1 last1, InputIt2 frst2, InputIt2 last2 ) {

			for (; frst1 not_eq last1 and frst2 not_eq last2; ++frst1, ++frst2) {

				if (frst1.operator*() < frst2.operator*())
					return true;
				if (frst2.operator*() < frst1.operator*())
					return false;
			}

			return (frst1 == last1) and (frst2 not_eq last2);
		}
	template < class InputIt1, class InputIt2, class Compare>
		bool lexicographical_compare (InputIt1 frst1, InputIt1 last1, InputIt2 frst2, InputIt2 last2, Compare comp ) {

			for (; frst1 not_eq last1 and frst2 not_eq last2; ++frst1, ++frst2) {

				if (comp (*frst1, *frst2))
					return true;
				if (comp (*frst2, *frst1))
						return false;
			}
			return (frst1 == last1) and (frst2 not_eq last2);
		}

		template <typename T>
			struct remove_c { typedef T type; };
		template <typename T>
			struct remove_c <const T>{ typedef T type; };

};

template <class T>
    struct is_pair { static const bool value = false; };

template <class T1, class T2>
    struct is_pair< ft::pair<T1, T2> > { static const bool value = true; };



# endif
