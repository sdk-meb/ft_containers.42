/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:47:28 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/25 21:25:13 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITER_HPP
#define MAP_ITER_HPP

#include "iterator.hpp"

namespace ft {


	template <class treeiter>
		struct map_iterator {

				typedef	iterator<ft::bidirectional_iterator_tag, typename treeiter::value_type>	INTERFACE;

				typedef typename INTERFACE::difference_type			difference_type;
				typedef typename treeiter::value_type				value_type;
				typedef typename INTERFACE::pointer					pointer;
				typedef typename INTERFACE::reference				reference;
				typedef typename INTERFACE::iterator_category		iterator_category;

				map_iterator() {}
				explicit map_iterator(const treeiter& _x):Super(_x)  { }
				template< class U >
					map_iterator (map_iterator<U> other)
						: Super (other.Super) { };

				map_iterator&	operator++ ()  { ++Super; return *this; }
				map_iterator&	operator-- ()  { --Super; return *this; }
				map_iterator	operator++ (int)  { map_iterator old(Super); ++Super; return old; }
				map_iterator	operator-- (int)  { map_iterator old(Super); --Super; return old; }

				reference	operator*() const	{ return *Super.ItR->Ship; }
				pointer		operator->() const	{ return Super.ItR->Ship; }

				template <typename, typename, typename, typename>
					friend class map;
			private:
				treeiter	Super;
		};


	template < typename Iter>
		bool operator== (const Iter& a, const Iter& b)	{ return not (a not_eq b); }
	template < typename Iter> 
		typename ft::enable_if <
			ft::__is_bidirectional_iter<typename Iter::iterator_category>::value and 
			not	ft::__is_random_access_iter<typename Iter::iterator_category>::value,
			bool >::type 
				operator!= (const Iter& a, const Iter& b)	{ return &(*a) not_eq &(*b); }


}

#endif
