/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:49:41 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/12/31 10:15:06 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _TYPE_TRAITS_HPP
# define _TYPE_TRAITS_HPP

# include<iostream>

namespace ft {


	/* fundamental integral types */
	namespace fit {
	 
		template <class T, T v>
			struct integral_constant {

			static const T value = v;
			// operator T() { return v; }
		};
		typedef integral_constant<bool, true> true_type;
		typedef integral_constant<bool, false> false_type;
		template <typename>
			struct is_integral : public false_type{};
		template <>
			struct is_integral<bool> : public true_type{};
		template <>
			struct is_integral<char> : public true_type{};
		template <>
			struct is_integral<char16_t> : public true_type{};
		template <>
			struct is_integral<char32_t> : public true_type{};
		template <>
			struct is_integral<wchar_t> : public true_type{};
		template <>
			struct is_integral<signed char> : public true_type{};
		template <>
			struct is_integral<unsigned char> : public true_type{};
		template <>
			struct is_integral<short int> : public true_type{};
		template <>
			struct is_integral<int> : public true_type{};
		template <>
			struct is_integral<long int> : public true_type{};
		template <>
			struct is_integral<long long int> : public true_type{};
		template <>
			struct is_integral<unsigned short int> : public true_type{};
		template <>
			struct is_integral<unsigned int> : public true_type{};
		template <>
			struct is_integral<unsigned long int> : public true_type{};
		template <>
			struct is_integral<unsigned long long int> : public true_type{};
	}; /* END of namesp # fit # */

	/* https://cplusplus.com/reference/type_traits/enable_if */
	template <bool Cond, class T = void>
		struct enable_if{};

	template <class T>
		struct enable_if<true, T>{

			typedef T type;
		};

	using namespace fit;
};  /* END of namesp # ft # */


# endif
