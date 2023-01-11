/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/11 11:14:31 by mes-sadk         ###   ########.fr       */
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
				class __key, class T,
				class Compare = std::less<__key>,
				class Allocator = std::allocator<ft::pair<const __key, T> >
				>
		class map {

			public:

				typedef	__key									key_type;
				typedef	T										mapped_type;
				typedef	ft::pair< key_type, mapped_type>		value_type;

				typedef	typename Allocator::size_type				size_type;
				typedef	typename Allocator::difference_type			differance_type;

				typedef	Compare						key_compare;
				typedef	Allocator					allocator_type;
		
				typedef	value_type&						  	  reference;
				typedef	const value_type&				const_reference;
				typedef	typename Allocator::pointer					  pointer;
				typedef	typename Allocator::const_pointer		const_pointer;

				typedef	_RBtree<value_type>			__tree_;
				typedef	IterTree<value_type>			Itree;

				typedef ft::map_iterator< Itree>			iterator;
				typedef	ft::map_iterator<const Itree>			const_iterator;
				typedef	ft::reverse_iterator<iterator>			reverse_iterator;
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
				@category __  Element access  __
			*/
			/*
				@brief get mapped value by key scershing
				@param	key	the descriptor of the shipment
			*/
				T&			at (const key_type& key)		{ return tree.search(key); }
				const T&	at (const key_type& key) const	{ return tree.search(key); }
				T&	operator[] (const key_type& key)		{ return tree.search(key, _noexcept); }

			/*
				@category	__  Capacity  __
			*/
				bool		empty() const		{ return tree.empty(); }
				size_type	size() const		{ return tree.size(); }
				size_type	max_size() const	{ return _Alloc.max_size(); }

			/*
				@category	__  Modifiers  __
			*/
				void	clear() { tree.destroy(); }

			/*
				@category	__  Iterators  __
			*/
				iterator		begin() 		{ return iterator 		(tree.get_first()); }
				const_iterator	begin() const	{ return const_iterator (tree.Frst); }
				iterator		end()			{ return iterator		(++tree.get_last()); }
				const_iterator	end() const		{ return const_iterator (++tree.get_last()); }
				reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
				const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }
				reverse_iterator		rend()			{ return reverse_iterator(begin()); }
				const_reverse_iterator	rend() const	{ return onst_reverse_iterator(begin()); }

			/*
				@category	__  Lookup  __
			*/
			
		
			private:
				value_compare	_v_cmp (Compare());
				__tree_		tree;
				allocator_type	_Alloc;
		};


}
	

# endif
