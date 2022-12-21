/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:08:25 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/12/19 05:50:29 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#	define VECTOR_HPP

# include<memory>
# include <Red_Black_tree.hpp>

namespace ft {

	template <class T, class Allocator = std::allocator<T> >
		class vector{

				typedef T				value_type;
				typedef T*				pointer;	
				typedef const T*		const_pointer;
				typedef T&				reference;
				typedef const T&		const_reference;
				typedef std::size_t		size_type;
				typedef std::ptrdiff_t	difference_type;
				
				
			public:
							vector () ;
				explicit	vector ( const Allocator& alloc );
				explicit	vector ( size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator() ) ;
				template <class InputIt>
					vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) ;
							vector( const vector& other ) ;
			
		};
};


# endif
