/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterato.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:47:28 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/11 11:24:07 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITER_HPP
#define MAP_ITER_HPP

#include "iterator.hpp"

namespace ft
{

	template <class treeiter>
		class map_iterator
		: virtual public ft::normal_iterator<treeiter, ft::iterator<ft::bidirectional_iterator_tag, treeiter> >
		{

				typedef ft::normal_iterator<treeiter, ft::iterator<ft::bidirectional_iterator_tag, treeiter> > nor_iter;

			public:

				map_iterator() : nor_iter() {}
				explicit map_iterator(const treeiter &_x) : nor_iter(_x) { }
				template <class U>
					map_iterator(const map_iterator<U> &other)
					: nor_iter(dynamic_cast<
							ft::normal_iterator<U, ft::iterator<ft::bidirectional_iterator_tag, U> > >(other)) { };
		};

}

#endif
