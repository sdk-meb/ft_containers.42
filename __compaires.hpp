/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __compaires.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:14:29 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/10 18:33:47 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CMPAIR_HPP
#   define __CMPAIR_HPP

# include<functional>

# include"type_traits.hpp"
# include"utility.hpp"


namespace ft {


/**
 * @brief overloading comparing function, the compare pairs and/or integral  
 * @param TP type pair
 * @param TF not pair value
 * @param comp Function object for performing comparisons
*/
template <typename TP, typename TF, typename comp >
    typename ft::enable_if < is_pair<TP>::value and not is_pair<TF>::value , bool >::type
        t_comp (const TP& pr, const TF& frst, const comp& cmp) { return cmp (pr.first, frst); }

template <typename TF, typename TP, typename comp >
    typename ft::enable_if < is_pair<TP>::value and not is_pair<TF>::value , bool >::type
        t_comp (const TF& frst, const TP& pr, const comp& cmp) { return cmp (frst, pr.first); }

template <typename TP, typename comp>
    typename ft::enable_if < is_pair<TP>::value , bool >::type
        t_comp (const TP& pr1, const TP& pr2, const comp& cmp) { return cmp (pr1.first, pr2.first); }

template <typename TF, typename comp >
    typename ft::enable_if < not is_pair<TF>::value , bool >::type
		t_comp (const TF& f1, const TF& f2, const comp& cmp) { return cmp (f1, f2); }


/**
 * @brief comparing operators_
 * @a __V  value type
 * @param pr1 
 * @param pr2
*/
template <typename __V>
    typename ft::enable_if < is_pair<__V>::value , bool >::type
        operator!= (const __V& pr1, const __V& pr2) {

            return pr1.second not_eq pr2.second or pr1.first not_eq pr2.first;
        }

template <typename __V>
    typename ft::enable_if < is_pair<__V>::value , bool >::type
        operator< (const __V& _v1, const __V& _v2) {

            return _v1.first < _v2.first or (not (_v2.first < _v1.first) and _v1.second < _v2.second);
        }


template <typename __V>
    typename ft::enable_if < is_pair<__V>::value , bool >::type
        operator> (const __V& _v1, const __V& _v2) {

            return _v2 < _v1;
        }

template <typename __V>
        bool    operator>= (const __V& _v1, const __V& _v2) {

            return not (_v1 < _v2);
        }

template <typename __V>
        bool    operator<= (const __V& _v1, const __V& _v2) {

            return not (_v2 < _v1);
        }

template <typename __V>
        bool    operator== (const __V& _v1, const __V& _v2) {

            return  not (_v1 not_eq _v2);
        }

}

#endif
