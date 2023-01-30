/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:47:28 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/31 00:48:08 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITER_HPP
#define MAP_ITER_HPP

#include "iterator.hpp"

namespace ft {


	template <class treeiter>
		class map_iterator {


				typedef	iterator<ft::bidirectional_iterator_tag, typename treeiter::value_type>	INTERFACE;

			public:
				typedef typename INTERFACE::difference_type			difference_type;
				typedef typename treeiter::value_type				value_type;
				typedef typename INTERFACE::pointer					pointer;
				typedef typename INTERFACE::reference				reference;
				typedef typename INTERFACE::iterator_category		iterator_category;

				map_iterator() : Super (typename treeiter::key_compare()) { }
				explicit map_iterator(const treeiter& _x):Super(_x)  { }

				map_iterator&	operator++ ()  { ++Super; return *this; }
				map_iterator&	operator-- ()  { --Super; return *this; }
				map_iterator	operator++ (int)  { map_iterator old(Super); ++Super; return old; }
				map_iterator	operator-- (int)  { map_iterator old(Super); --Super; return old; }

				reference	operator*() const	{ return *Super.ItR->Ship; }
				pointer		operator->() const	{ return Super.ItR->Ship; }

				template <typename, typename, typename, typename>
					friend class map;
				template <typename, typename, typename>
					friend class set;
			public:
				treeiter	Super;
		};


		template <class treeiter>
		class const_map_iterator : public map_iterator<treeiter> {

			
				typedef	iterator<ft::bidirectional_iterator_tag, typename treeiter::value_type>	INTERFACE;
			public:
				typedef typename INTERFACE::difference_type			difference_type;
				typedef typename treeiter::value_type				value_type;
				typedef typename INTERFACE::pointer					pointer;
				typedef typename INTERFACE::reference				reference;
				typedef typename INTERFACE::iterator_category		iterator_category;

				const_map_iterator(){}
				explicit const_map_iterator(const treeiter& _x): map_iterator<treeiter>(_x) { }
				template< class U >
					const_map_iterator (map_iterator<U> other)
						{ this->Super = other.Super; }

		};


}

#endif
