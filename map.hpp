/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/04 09:25:32 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MAP_HPP
# define MAP_HPP

# include<functional>
# include<memory>
# include<cstddef>
# include<map>

# include"Red-Black_tree.hpp"
# include"iterator.hpp"
# include"utility.hpp"

namespace	ft {

	template	< 
				class key, class T,
				class Compare = std::less<key>,
				class Allocator = std::allocator<ft::pair<const key, T> >
				>
		class map {

			public:

							/* member types */
				typedef key							key_type;
				typedef	T							mapped_type;
				typedef	ft::pair<const key, T>		value_type;

				typedef	std::size_t				size_type;
				typedef	std::ptrdiff_t			differance_type;

				typedef	Compare						key_compare;
				typedef	Allocator					allocator_type;
		
				typedef	value_type&						  	  reference;
				typedef	const value_type&				const_reference;
				typedef	typename Allocator::pointer					  pointer;
				typedef	typename Allocator::const_pointer		const_pointer;

				typedef	iterator_traits<pointer>					  iterator;
				typedef	iterator_traits<const_pointer>			const_iterator;
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


				map(){};
				explicit map (const Compare& comp,
								const Allocator& alloc = Allocator()) : _alloc(alloc) { }
				map (const map& other);
				template< class InputIt >

				map (InputIt first, InputIt last,
					const Compare& comp = Compare(),
					const Allocator& alloc = Allocator()) {

						
				}












			private:
				value_compare	_v_cmp(Compare());
				allocator_type	_alloc;
		};


}
	

# endif
