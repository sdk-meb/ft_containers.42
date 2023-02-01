/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_tree.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:30:56 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/01 19:39:45 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BASE_TREE_HPP
# define __BASE_TREE_HPP


# include"utility.hpp"
# include"./ab__tree.hpp"

template < class Container >
    class ___abase {

        typedef 	typename Container::allocator_type		Allocator;
        typedef 	typename Container::size_type			size_type;
        typedef const typename Container::key_type			key_type;

        typedef 	typename Container::key_compare			key_compare;

        typedef		__road_<typename Container::value_type>		__road;

        typedef typename Allocator::template rebind<__road>::other	SAllocator;

		protected:
			const key_compare&		k_comp;
			Allocator&			_Alloc;
			size_type			Size;
			__road*				seed;
			SAllocator			_SAlloc;
        
    /*********************************************************************************************************
	*	@brief	binary tree searching, NULL in case of non existence
	*	@param	key	 searching indicator 
	*	@param	sub	indicator for start recursion place
	*********************************************************************************************************/
		__road*		searching (key_type& key, __road* sub=NULL) const throw() {

			if (not sub) sub = const_cast<__road*> (seed);
			while (sub) {

				if (t_comp (key, *sub->Ship, this->k_comp))
						sub = sub->L_ch;
				else if (t_comp (*sub->Ship, key, this->k_comp))
						sub = sub->R_ch;
				else break ;
			}
			return  sub;
		}
	/*********************************************************************************************************
	*	@brief	find palce of new key
	*	@param	key	 searching indicator 
	*	@return	parent who can accept new node withe the new key
	*********************************************************************************************************/
		__road&		find_place (key_type& key) const throw() {

			__road* sub = const_cast<__road*> (seed);
			while (sub) {

				if (t_comp (key, *sub->Ship, this->k_comp) and sub->L_ch)
						sub = sub->L_ch;
				else if (t_comp (*sub->Ship, key, this->k_comp) and sub->R_ch)
						sub = sub->R_ch;
				else break ;
			}
			return *sub;
		}


		public:
/***************************  @category	 __  constructor  __  ***********************************************/

		___abase (const key_compare& cmp, Allocator& alloc)
			: k_comp(cmp), _Alloc (alloc), Size(0), seed(NULL), _SAlloc(SAllocator()) { }

		~___abase() {

			if (seed) {

				seed->destroy (_Alloc, _SAlloc);
				_SAlloc.destroy(seed);
				_SAlloc.deallocate (seed, 1);
			}
		}


};


# endif
