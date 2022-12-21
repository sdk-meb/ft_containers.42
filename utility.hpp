/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:29:08 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/12/19 10:37:52 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include<utility>

namespace   ft {

	/*  https://cplusplus.com/reference/algorithm/equal */
	template <class T1, class T2>
		struct pair : public std::pair<T1, T2> {
			T1	first_type;
			T2	second_type;
		};
};




# endif
