/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterato.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:47:28 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/14 20:50:20 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITER_HPP
#define MAP_ITER_HPP

#include "iterator.hpp"

namespace ft
{

	template <class treeiter>
		struct map_iterator {

				typedef	iterator<ft::bidirectional_iterator_tag, treeiter>	INTERFACE;

				typedef typename INTERFACE::difference_type			difference_type;
				typedef typename INTERFACE::value_type				value_type;
				typedef typename treeiter::value_type*				pointer;
				typedef typename treeiter::value_type&				reference;
				typedef typename INTERFACE::iterator_category		iterator_category;

				map_iterator() {}
				explicit map_iterator(const treeiter &_x): Super(_x) { }
				template< class U >
					map_iterator (map_iterator<U> other)
						: Super (other.Super) { };

				map_iterator&	operator++ ()  { --Super; return *this; }
				map_iterator&	operator-- ()  { --Super; return *this; }
				map_iterator	operator++ (int)  { map_iterator old(Super); ++Super; return old; }
				map_iterator	operator-- (int)  { map_iterator old(Super); --Super; return old; }

				reference	operator*() const	{ return *Super.ItR->Ship; }
				pointer		operator->() const	{ return Super.ItR->Ship; }

				template <typename, typename, typename, typename>
					friend class map;
			protected:
				treeiter	Super;
		};

}

#endif
