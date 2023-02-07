/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_tree.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:30:56 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/07 22:42:07 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BASE_TREE_HPP
# define __BASE_TREE_HPP


# include"utility.hpp"


/*************************************************************************************************************
*	@brief	iterator helper, manage pointing tree
*	@param	DS data struct, rules to iterate it
*************************************************************************************************************/	
template < class DS >
	struct __IterTree_ {


		typedef typename DS::T_SHIP		value_type;
		typedef typename DS::key_type		key_type;
		typedef typename DS::key_compare		key_compare;
		typedef	__road_<value_type>	__node;
	
		typedef	__node&						ref_node;
		typedef	__node*						ptr_node;
	
        const key_compare&    k_comp;
		ptr_node		ItR;
		__node			nul_;

		__IterTree_ (const key_compare& cmp=key_compare()) : k_comp(cmp) { ItR = &nul_; }
		__IterTree_ (ref_node _P, const key_compare& cmp, bool) : k_comp(cmp) { nul_.P = &_P; ItR = &nul_; }
		__IterTree_ (ref_node tree, const key_compare& cmp): k_comp(cmp), ItR(&tree) { }
		__IterTree_ (ptr_node tree, const key_compare& cmp): k_comp(cmp), ItR(tree) { }
		__IterTree_ (const __IterTree_& tree) : k_comp(tree.k_comp)  { *this = tree; }
		void	operator= (const __IterTree_& tree) {

			if (tree.ItR and tree.ItR->Ship == nul_.Ship) { nul_.P = tree.ItR->P ; ItR = &nul_; }
			else ItR = tree.ItR;
		}

	/*********************************************************************************************************
	*	@return	next node in tree contine the next sequence key
	*********************************************************************************************************/	
		ref_node	next() const {

			if (not ItR) throw error_condition();
			if (ItR->R_ch) return ItR->R_ch->youngest();

			ptr_node	tmp = ItR;

			while (tmp->WhoIm() == SE) tmp = tmp->P;
			if (tmp->WhoIm() == ROOT)
                throw std::range_error ("no next");/* ItR is the eldest in tree*/
			return *tmp->P;
		}

	/*********************************************************************************************************
	*	@return	previous node in tree contine the first less of sequence key
	*********************************************************************************************************/	
		ref_node	prev() const {

			if (not ItR) throw error_condition();
			if (ItR->L_ch) return ItR->L_ch->eldest();

			ptr_node	tmp = ItR;

			while (tmp->WhoIm() == JU) tmp = tmp->P;
			if (tmp->WhoIm() == ROOT)
                throw std::range_error ("no prev");/* ItR is the young in tree*/
			return *tmp->P;
		}

		__IterTree_&	operator++() {

			try { ItR = &next(); }
			catch (const error_condition&) { }
			catch (const std::logic_error&) { nul_.P = NULL; }
			catch (const std::range_error&) {

				nul_.P = ItR;
				if (ItR == &nul_) nul_.P = NULL;
				else ItR = &nul_;
			}
			return *this;
		}

		__IterTree_&	operator--() {

			try { ItR = &prev(); }
			catch (const error_condition&) { }
			catch (const std::logic_error&) { ItR = (nul_.P ? nul_.P : &nul_); nul_.P = NULL; return *this; }
			catch (const std::range_error&) { ItR = &nul_; nul_.P = NULL; }
			return *this;
		}

		__IterTree_&		operator << (key_type& key) {

			try { while ( t_comp(key, *ItR->Ship, k_comp)) ItR = &prev();}
			catch (const std::range_error&) { return *this; }
			try { while ( t_comp(*ItR->Ship, key, k_comp)) ItR = &next(); }
			catch (const std::range_error&) { ItR = &nul_; ItR->Ship = NULL; }
			return *this;
		}
		__IterTree_&		operator >> (key_type& key) {

			try { while (t_comp(key, *ItR->Ship, k_comp)) ItR = &prev(); }
			catch (const std::range_error&) { return *this; }
			try { while (not t_comp(key, *ItR->Ship, k_comp)) ItR = &next(); }
			catch (const std::range_error&) { ItR = &nul_; ItR->Ship = NULL; }
			return *this;
		}

};


/*************************************************************************************************************
*	@brief	base class of tree 
*	@param	Container 
*************************************************************************************************************/	
template < class Container >
    class ___abase {

        typedef 	typename Container::allocator_type		Allocator;
        typedef 	typename Container::size_type			size_type;
        typedef const typename Container::key_type			key_type;
		typedef const typename Container::value_type		T_SHIP;


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
		__road&		find_place (T_SHIP& ship) const throw() {

			__road* sub = const_cast<__road*> (seed);
			while (sub) {

				if (t_comp (ship, *sub->Ship, this->k_comp) and sub->L_ch)
						sub = sub->L_ch;
				else if (t_comp (*sub->Ship, ship, this->k_comp) and sub->R_ch)
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
