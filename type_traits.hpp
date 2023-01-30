/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:49:41 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/30 14:44:17 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _TYPE_TRAITS_HPP
# define _TYPE_TRAITS_HPP


namespace ft {


	namespace __Fundamental_Integral_Types {


		template < class T, T v>
			struct integral_constant { static const T value = v; };

		typedef integral_constant< bool, true>	true_type;
		typedef integral_constant< bool, false>	false_type;

		template <typename>
			struct is_integral : public false_type { };

		template < >
			struct is_integral< bool> : public true_type { };
		template < >
			struct is_integral< char> : public true_type { };
#ifdef	__APPLE__
		template < >
			struct is_integral< char16_t> : public true_type { };
		template < >
			struct is_integral< char32_t> : public true_type { };
# endif
		template < >
			struct is_integral< wchar_t> : public true_type { };
		template < >
			struct is_integral< signed char> : public true_type { };
		template < >
			struct is_integral< unsigned char> : public true_type { };
		template < >
			struct is_integral< short int> : public true_type { };
		template < >
			struct is_integral< int> : public true_type { };
		template < >
			struct is_integral< long int> : public true_type { };
		template < >
			struct is_integral< long long int> : public true_type { };
		template < >
			struct is_integral< unsigned short int> : public true_type { };
		template < >
			struct is_integral< unsigned int> : public true_type { };
		template < >
			struct is_integral< unsigned long int> : public true_type { };
		template < >
			struct is_integral< unsigned long long int> : public true_type { };
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



	using namespace __Fundamental_Integral_Types;
	using namespace __Enable_if;


}/* END of namesp ft */


# endif
