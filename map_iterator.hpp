/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:47:28 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/10 11:23:38 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if  not defined(MAP_ITER_HPP) or defined(COMPL_MITR)

#include "iterator.hpp"

#ifndef  MAP_ITER_HPP
# define MAP_ITER_HPP

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
				explicit map_iterator(const treeiter& _x) :Super(_x)  { }
				template <typename m_Iter>
					map_iterator (typename ft::enable_if < 
						ft::__is_bidirectional_iter < 
						typename  m_Iter::iterator_category >::value, const m_Iter&>::type other)
						: Super(other.Super) { }

				map_iterator&	operator++ ()  { ++Super; return *this; }
				map_iterator&	operator-- ()  { --Super; return *this; }
				map_iterator	operator++ (int)  { map_iterator old(Super); ++Super; return old; }
				map_iterator	operator-- (int)  { map_iterator old(Super); --Super; return old; }

				reference	operator*() const	{ return *Super.ItR->Ship; }
				pointer		operator->() const	{ return Super.ItR->Ship; }

				template <typename _Iter>
					void operator= (const _Iter& other) { Super = other.Super;}
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
#define COMPL_MITR

#endif
