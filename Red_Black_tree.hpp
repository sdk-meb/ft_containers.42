/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Red_Black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 05:29:13 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/12/19 10:34:20 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#	define RED_BLACK_TREE_HPP

template <typename T>
	struct Red_Black_tree
		{
			Red_Black_tree();
			void	add_to(T& node) ;
			private :
				# define	DOWN	0/* left */
				# define	IN		1/* local */
				# define	UP		2/* right */

				T	node[3];
				T&	operator++(){ return node[UP];};
				T&	operator--(){ return node[DOWN];};
	
		};

struct C_rbt {
	
	
};


# endif
