/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/10 12:13:25 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MAP_HPP
# define MAP_HPP

# include<functional>
# include<memory>
# include<cstddef>

# include"Red-Black_tree.hpp"

# include"map_iterato.hpp"
# include"iterator.hpp"

# include"utility.hpp"

namespace	ft {

	/*
		@category Associative containers
		@brief	collection of key-value pairs, storted by keys, evrey key should unique
		@param	key	indicator
		@param 	T value type
		@param	Compare  relational operator or function to use it as comparison method (less = default)
		@param	Allocator 	typename allocation
	*/
	template	< 
				class key, class T,
				class Compare = std::less<key>,
				class Allocator = std::allocator<ft::pair<const key, T> >
				>
		class map {

			public:

				typedef	key									key_type;
				typedef	T										mapped_type;
				typedef	ft::pair<const key_type, mapped_type>		value_type;

				typedef	typename Allocator::size_type				size_type;
				typedef	typename Allocator::difference_type			differance_type;

				typedef	Compare						key_compare;
				typedef	Allocator					allocator_type;
		
				typedef	value_type&						  	  reference;
				typedef	const value_type&				const_reference;
				typedef	typename Allocator::pointer					  pointer;
				typedef	typename Allocator::const_pointer		const_pointer;

				typedef	_RBtree<value_type>			__tree_;

				typedef	ft::map_iterator<__tree_>					  iterator;
				typedef	ft::map_iterator<const __tree_>				const_iterator;
				typedef	ft::reverse_iterator<iterator>				  reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

				class	value_compare {

					protected:
						key_compare comp;
					
						value_compare(key_compare c): comp(c) { }

					public:
						bool	operator() (const value_type& lhs, const value_type& rhs) {

							return comp(lhs.first, rhs.first);
						}
				};

				map() : tree(__tree_()) { } ;

			/*
				@category Element access
			*/
			/*
				@brief get mapped value by key scershing
			*/
				T&	at (const key_type& key) {

					const tree* =  tree.search(ft::make_pair<>());
				}
				const T& at( const key_type& key ) const {

					
				}
			private:
				value_compare	_v_cmp (Compare());
				__tree_			tree;
				allocator_type	_alloc;
		};


}
	

# endif
