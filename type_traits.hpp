/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:49:41 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/09 10:03:50 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _TYPE_TRAITS_HPP
# define _TYPE_TRAITS_HPP
#include<iterator>

namespace ft {


	namespace __Fundamental_Integral_Types {

	 
		template < class T, T v>
			struct integral_constant { static const T value = v; };

		typedef integral_constant< bool, true>	true_type;
		typedef integral_constant< bool, false>	false_type;

		template <typename>
			struct is_integral
				: public false_type { };
		template < >
			struct is_integral< bool>
				: public true_type { };
		template < >
			struct is_integral< char>
				: public true_type { };
#ifdef	__APPLE__
		template < >
			struct is_integral< char16_t>
			: public true_type { };
		template < >
			struct is_integral< char32_t>
			: public true_type { };
# endif
		template < >
			struct is_integral< wchar_t>
				: public true_type { };
		template < >
			struct is_integral< signed char>
				: public true_type { };
		template < >
			struct is_integral< unsigned char>
				: public true_type { };
		template < >
			struct is_integral< short int>
				: public true_type { };
		template < >
			struct is_integral< int>
				: public true_type { };
		template < >
			struct is_integral< long int>
				: public true_type { };
		template < >
			struct is_integral< long long int>
				: public true_type { };
		template < >
			struct is_integral< unsigned short int>
				: public true_type { };
		template < >
			struct is_integral< unsigned int>
				: public true_type { };
		template < >
			struct is_integral< unsigned long int>
					: public true_type { };
		template < >
			struct is_integral< unsigned long long int>
					: public true_type { };
	}

	namespace __Enable_if {

		// Primary template.
		/*
			@brief if condition is false, enable_if has no public member typedef `type` of T
			so in case of using type, substitution failuer is not an error
			@param Cond flage was true or false
			@param T typename = void(default)
		*/
		template < bool Cond, class T = void>
			struct enable_if { };
		
  		// Partial specialization for true.
		template < class T>
			struct enable_if<true, T> { typedef T type; };
	}

	namespace equivalence {


		template <class InputIt1, class InputIt2>
			bool	equal(InputIt1 frst1, InputIt1 last1, InputIt2 frst2){

				for (; frst1 != last1; ++frst1, ++frst2)
        			if (*frst1 != *frst2)
            			return false;
    			return true;
			}
		
		template < class InputIt1, class InputIt2>
			bool	lexicographical_compare( InputIt1 frst1, InputIt1 last1, InputIt2 frst2, InputIt2 last2 ) {

				for (; (frst1 != last1) && (frst2 != last2); ++frst1, (void) ++frst2) {

					if (*frst1 < *frst2)
						return true;
					if (*frst2 < *frst1)
						return false;
				}
			
				return (frst1 == last1) && (frst2 != last2);
			}
		template < class InputIt1, class InputIt2, class Compare>
			bool lexicographical_compare( InputIt1 frst1, InputIt1 last1, InputIt2 frst2, InputIt2 last2, Compare comp ) {

			    for (; (frst1 != last1) && (frst2 != last2); ++frst1, (void) ++frst2) {

			        if (comp(*frst1, *frst2))
           		 		return true;
        			if (comp(*frst2, *frst1))
           				 return false;
    			}
    			return (frst1 == last1) && (frst2 != last2);
			}

	
	}

	using namespace __Fundamental_Integral_Types;
	using namespace __Enable_if;
	using namespace	equivalence;


}/* END of namesp ft */


# endif
