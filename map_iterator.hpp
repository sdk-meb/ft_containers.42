/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:47:28 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/22 00:13:38 by sdk-meb          ###   ########.fr       */
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
				explicit map_iterator(const treeiter& _x): Super(_x) { }
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

/*************************************************************************************************************
*	@brief	class that manage map iterator in reverse order
*	@param	_Iter iterator 
*************************************************************************************************************/
template <class _Iter>
	struct reverse_map_iterator {

			typedef _Iter									iterator_type;
			typedef typename _Iter::difference_type			difference_type;
			typedef typename _Iter::pointer					pointer;
			typedef typename _Iter::reference				reference;
			typedef typename _Iter::iterator_category		iterator_category;

		private:
			iterator_type Super;

		public:
			reverse_map_iterator() : Super() { };
			explicit reverse_map_iterator (iterator_type x): Super(x) { };
			template< class U >
				reverse_map_iterator (const reverse_map_iterator<U>& other)
					: Super(other.Super) { };


			reverse_map_iterator&	operator=( const reverse_map_iterator& rIt ){ Super = rIt.base();}

			reverse_map_iterator&	operator--() { ++Super; return *this; }
			reverse_map_iterator&	operator++() { --Super; return *this; }
			reverse_map_iterator	operator-- (int) { reverse_map_iterator old(Super); ++Super; return old; }
			reverse_map_iterator	operator++ (int) { reverse_map_iterator old(Super); --Super; return old; }

			reference		operator*() const { return *Super; }
			pointer			operator->() const { return &(*Super); }
	};


	template < typename Iter>
		typename ft::enable_if <
			ft::__is_bidirectional_iter<typename Iter::iterator_category>::value and 
			not	ft::__is_random_access_iter<typename Iter::iterator_category>::value,
			bool >::type 
				operator== (const Iter& a, const Iter& b)	{ return a->first == b->first; }
	template < typename Iter> 
		typename ft::enable_if <
			ft::__is_bidirectional_iter<typename Iter::iterator_category>::value and 
			not	ft::__is_random_access_iter<typename Iter::iterator_category>::value,
			bool >::type 
				operator!= (const Iter& a, const Iter& b)	{ return not (a == b); }


}

#endif
