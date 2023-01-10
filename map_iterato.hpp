/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterato.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:47:28 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/10 11:37:16 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITER_HPP
# define MAP_ITER_HPP

# include"iterator.hpp"

namespace   ft {


    template < class treeiter>
        class map_iterator
        : ft::normal_iterator<treeiter, ft::iterator<ft::bidirectional_iterator_tag, treeiter> > {

            
        };



}

# endif
