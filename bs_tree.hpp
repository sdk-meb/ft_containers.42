/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/30 17:11:21 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

# include<iostream>
# include<algorithm>
# include<climits>
# include<memory>

#ifdef __linux
	class error_condition {};
	#include <cstdlib>
#else
	using std::error_condition;
#endif

# include"type_traits.hpp"
# include"utility.hpp"
# include"iterator.hpp"

			# define	NIL		NULL
			# define	SE		37/* SE_NIOR */
			# define	JU		13/* JU_NIOR */
			# define	ROOT	33
			# define	NOTHING	7331


/*************************************************************************************************************
*	@brief	data base of tree shipment
*	@param	T_SHIP	Shipment to stor
*************************************************************************************************************/
template < class T_SHIP, class Allocator = std::allocator <T_SHIP> >
	class __road_ {

		public:
			/** @brief the original allocator for this instance */	
			typedef typename Allocator::template rebind<__road_>::other	SAllocator;
			typedef	T_SHIP		value_type;

			SAllocator*			_SAlloc;
			Allocator			_Alloc;
			static	T_SHIP		nul_;

		__road_ (const __road_& other) { *this = other; }
		__road_ (__road_* const _P=NIL) { init_(); P = _P; }
		__road_	(T_SHIP ship, SAllocator& _salloc)
			: _SAlloc(&_salloc), _Alloc(Allocator()) {

			init_();
			Ship =  _Alloc.allocate(1);
			_Alloc.construct(Ship, ship);

		}

	private:
		void	init_ () {

			Ship		= &nul_;
			copy_ship	= true;

			P		= NIL;
			L_ch	= NIL;
			R_ch	= NIL;
		}

	public:
		T_SHIP*			Ship;/* load */
		bool			copy_ship;

		__road_*			P;/* root of subtree(parent), NIL if node has root */
		__road_*			L_ch;/* left subtree, youngest son */
		__road_*			R_ch;/* right subtree, eldest son */


	/*********************************************************************************************************
	*	@return		JUNIOR in case of the node is left child of his parent
	*	@return		SENIOR in case of the node is the rigth child of his parent
	*	@return		otherwise ROOT
	*	@exception	If and only if the bind logic that return NOTHING
	*********************************************************************************************************/
		short	WhoIm() const {

			if (P == NIL) return ROOT;
			if (P->L_ch == this) return JU;
			if (P->R_ch == this) return SE;

			return throw std::logic_error("tree bind unqualified"), NOTHING;
		}


/***************************  @category	 __   getters alogo __  *********************************************/


	/*********************************************************************************************************
	*	@return		Sibling (reference)
	*********************************************************************************************************/
		__road_&	get_S() const {

			if (WhoIm() == ROOT || not(P->R_ch) || not(P->L_ch))
				throw std::logic_error("spiling doesn't");

			if (WhoIm() == JU)
				return *P->R_ch;
			return *P->L_ch;
		}

	/*********************************************************************************************************
	*	@return		GrandParent (reference)
	*********************************************************************************************************/
		__road_&	get_G() const {

			if (WhoIm() == ROOT  || P->WhoIm() == ROOT)
				throw std::logic_error("Grand P doesn't");
			return *P->P;
		}

	/*********************************************************************************************************
	*	@return			Uncle (reference)
	*********************************************************************************************************/
		__road_&	get_U() const {

			if (WhoIm() == ROOT || P->WhoIm() == ROOT)
				throw std::logic_error("Uncle doesn't");

			if (get_G().R_ch == NIL || get_G().L_ch == NIL)
				throw std::logic_error("Uncle doesn't");

			if (P->WhoIm() == JU)
				return *get_G().R_ch;
			return *get_G().L_ch;
		}

	/*********************************************************************************************************
	*	@return	a node which can replace the caller node, without violating the binary search tree rules
	*********************************************************************************************************/
		__road_&	redemption() throw() {

			return this->L_ch ? this->L_ch->eldest() : *this;
		}


	/*********************************************************************************************************
	*	@return	 youngest of this subtree
	*********************************************************************************************************/	
		__road_&	youngest()  throw() {

			__road_* tmp = this;

			while (tmp->L_ch) tmp = tmp->L_ch;
					
			return *tmp;
		}

	/*********************************************************************************************************
	*	@return	eldest of this subtree
	*********************************************************************************************************/	
		__road_&	eldest()  throw() {

			__road_* tmp = this;

			while (tmp->R_ch) tmp = tmp->R_ch;

			return *tmp;
		}


	public:

	/********************************************************************************************************* 
	* (1) ref param (save the copyrigth)
	* @brief copy assignment operator, shallow copy type, that make @a original( @a other) unthreatened by this
	* @param other  reference
	* @attention destroctor that deallocate the shipment and all branche of node, so (!)
	*********************************************************************************************************/
		void	operator= (const __road_& other) {

			this->Ship	= other.Ship;
			this->_Alloc	= other._Alloc;
			this->_SAlloc	= other._SAlloc;
			this->L_ch	= other.L_ch;
			this->R_ch	= other.R_ch;
			this->P		= other.P;

			this->copy_ship = true;
		}

		~__road_ () {

			if (copy_ship) return;

			if (Ship) {

				_Alloc.destroy (Ship);
				_Alloc.deallocate (Ship, 1);
			}
			if (L_ch) {

				_SAlloc->destroy(L_ch);
				_SAlloc->deallocate (L_ch, 1);
			}
			if (R_ch) {

				_SAlloc->destroy(R_ch);
				_SAlloc->deallocate (R_ch, 1);
			}
		}

};

template < class T_SHIP, class Allocator>
	T_SHIP	__road_<T_SHIP, Allocator>::nul_;



/*************************************************************************************************************
*	@brief	base Red _ Black _ tree
*	@param	T_SHIP	Shipment to stor
*************************************************************************************************************/
template < class Container >
	class BST {


		public:
			typedef 	typename Container::allocator_type		Allocator;
			typedef 	typename Container::size_type			size_type;

			typedef 	typename Container::value_type			T_SHIP;
			typedef const typename Container::key_type			key_type;
			typedef 	typename Container::mapped_type			v_map;

			typedef		__road_<T_SHIP, Allocator>				__road;

			typedef typename Allocator::template rebind<__road>::other	SAllocator;

		protected:
			Allocator			_Alloc;
			size_type			Size;
			__road*				seed;
			SAllocator			_SAlloc;


		public:
/***************************  @category	 __  constructor  __  ***********************************************/

		BST (Allocator alloc = Allocator())
			: _Alloc (alloc), Size(0), seed(NIL), _SAlloc(SAllocator()) { }


/***************************  @category	 __  BST # tree intertion  __  **************************************/

	/*********************************************************************************************************
	*	@brief insert  node inside the tree, exacption in case of duplicate key in tree
	*	@param ship shipment to insert
	*	@param	ex exeption true = default
	*	@exception permitted by order
 	*********************************************************************************************************/
		__road&		insert (const __road& _node, bool ex=true) {

			if (seed) return insertion(_node, seed, ex);

			seed = _SAlloc.allocate ( 1);

			_SAlloc.construct (seed, _node);
			seed->copy_ship = false;

			++Size;
			return *seed;
		}

	/*********************************************************************************************************
	*	@brief insert  pair  inside the tree, exacption in case of duplicate key in tree
	*			, and thas not dealocated in destruction
	*	@param ship shipment to insert
 	*********************************************************************************************************/
		__road&		insert (const T_SHIP& pair) { return insert (__road (pair, _SAlloc)); }


/***************************  @category	 __  BST # binary search tree  __  **********************************/

	/*********************************************************************************************************
	*	@return  node indecated by the key, NIL if not find
 	*********************************************************************************************************/
		__road*		search (key_type& key) const throw() {

			return not seed ? NIL : searching(key, seed);
		}

	/*********************************************************************************************************
	*	@return content(value) idecated by the key
	*	@param flag exeception or insirtion in case of non-existence
 	*********************************************************************************************************/
		v_map&		search (key_type& key, bool ex) {

			if (not ex) return  insert(ft::make_pair (key, v_map())) .Ship->second;

			__road* find = search(key);

			if (not find) std::__throw_range_error ("key search");
			return find->Ship->second;
		}



/***************************  @category	 __  BST #  node deletion tree  __  *********************************/

	/*********************************************************************************************************
	*	@param 	key
	*	@return result of deletion true/false
	*********************************************************************************************************/
		bool		del (key_type& key) throw() {

			__road* indecated = search(key);

			return indecated ? _delete(indecated), true : false;
		}

	/*********************************************************************************************************
	*	@overload (2)
	*	@param 	Shipment (pair)
	*********************************************************************************************************/
		void		del (__road& _node) throw() { _delete (&_node); }
		void		del (__road* _node) throw() { _delete (_node); }


	private:

	/*********************************************************************************************************
	*	@brief	binary tree insertion, that call @a adjustment that remove the violated rules of rb-tree
	*	@param	_node	indicator to being rotated
	*	@param	sub	indicator in last after recursions, the parent of the new child
	*	@param	ex exeption true = default
	*	@exception permitted by order
	*********************************************************************************************************/
		__road&		insertion(const __road& _node, __road* sub, bool ex=true) {

			if (_node.Ship->first < sub->Ship->first) {

				if (sub->L_ch) sub = sub->L_ch;
				else {

					sub->L_ch = _SAlloc.allocate(1);

					_SAlloc.construct (sub->L_ch, _node);
					sub->L_ch->P = sub;

					sub->L_ch->copy_ship = false;

					++Size;
					return *sub->L_ch;
				}
			}
			else if (_node.Ship->first > sub->Ship->first) {

				if (sub->R_ch) sub = sub->R_ch;
				else {

					sub->R_ch = _SAlloc.allocate(1);

					_SAlloc.construct (sub->R_ch, _node);
					sub->R_ch->P = sub;

					sub->R_ch->copy_ship = false;
 
					++Size;
					return *sub->R_ch;
				}
			}
			else if (ex)
				std::__throw_overflow_error ("similar shipment violates the property of map rules") ;
			else
				return *sub;
			return insertion(_node, sub, ex);
		}

	/*********************************************************************************************************
	*	@brief	binary tree searching, NIL in case of non existence
	*	@param	key	 searching indicator 
	*	@param	sub	indicator for start recursion place
	*********************************************************************************************************/
		__road*		searching(key_type& key, __road* sub) const throw() {

			if (not(sub))
				return NIL;

			if (key < sub->Ship->first)
					sub = sub->L_ch;
			else if (key > sub->Ship->first)
					sub = sub->R_ch;
			else
				return  sub;
			return searching(key, sub);
		}

	/*********************************************************************************************************
	*	@brief	binary tree deletion, that call @a delete_fixup rb-tree in case of violated rules
	*	@param	criminal	the node who has the shipment  referred by the key
	*********************************************************************************************************/
		void		_delete(__road* criminal) {

			if (not criminal) return ;

			__road* victim = &criminal->redemption();

			if (seed == victim) seed = victim->R_ch;

			std::swap (victim->Ship, criminal->Ship);

			__road* ch = victim->L_ch ?  victim->L_ch :  victim->R_ch;

			/* replace link to victim by who yastahik, ma ya3arfo hta had*/
			{
				if (ch) ch->P = victim->P;
				if (victim->WhoIm() == JU)	victim->P->L_ch = ch;
				else if (victim->WhoIm() == SE) victim->P->R_ch = ch;
			}
			/* unlink the victim , mayaraf raso fin*/
			victim->L_ch	= NIL;
			victim->R_ch	= NIL;
			victim->P	= NIL;

			_SAlloc.destroy(victim);
			_SAlloc.deallocate (victim, 1);

			--Size;
			/* end of history */
		}

	public:

		~BST() {

			if (seed) {

				_SAlloc.destroy(seed);
				_SAlloc.deallocate (seed, 1);
			}
		}
};




/*************************************************************************************************************
*	@brief	iterator helper, manage pointing tree
*	@param	Pr	pair(Shipment) to iterate it 
*************************************************************************************************************/	
template < class DS >
	struct __IterTree {


		typedef typename DS::value_type		value_type;
		typedef typename DS::key_type		key_type;
		typedef	__road_<value_type, typename DS::Allocator>	__node;
	
		typedef	__node&						ref_node;
		typedef	__node*						ptr_node;
	
		ptr_node		ItR;
		__node			nul_;

		__IterTree ( ) { ItR = &nul_; }
		__IterTree (ref_node _P, bool) { nul_.P = &_P; ItR = &nul_; }
		__IterTree (ref_node tree): ItR(&tree) { }
		__IterTree (ptr_node tree): ItR(tree) { }
		__IterTree (const __IterTree& tree) {

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
			if (tmp->WhoIm() == ROOT) throw std::range_error ("no next");/* ItR is the eldest in tree*/
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
			if (tmp->WhoIm() == ROOT) throw std::range_error ("no prev");/* ItR is the young in tree*/
			return *tmp->P;
		}


		__IterTree&	operator++() {

			try { ItR = &next(); }
			catch (const error_condition&) { }
			catch (const std::logic_error&) { nul_.P = NIL; }
			catch (const std::range_error&) {

				nul_.P = ItR;
				if (ItR == &nul_) nul_.P = NIL;
				else ItR = &nul_;
			}
			return *this;
		}
		__IterTree	operator++(int) {

			__IterTree old = *this;
			++(*this);
			return old;
		}

		__IterTree&	operator--() {

			if (ItR == &nul_) { ItR = (nul_.P ? nul_.P : &nul_); nul_.P = NIL; return *this; }
			try { ItR = &prev(); }
			catch (const error_condition&) { }
			catch (const std::range_error&) { nul_.P = NIL; }
			return *this;
		}
		__IterTree	operator--(int) {

			__IterTree old = *this;
			--(*this);
			return old;
		}

		__IterTree&		operator << (key_type& key) {

			try { while (ItR->Ship->first > key) ItR = &prev();}
			catch (const std::range_error&) { return *this; }
			try { while (ItR->Ship->first < key) ItR = &next(); }
			catch (const std::range_error&) { exit(9);ItR = &nul_; ItR->Ship = NIL; }
			return *this;
		}
		__IterTree&		operator >> (key_type& key) {

			try { while (ItR->Ship->first > key) ItR = &prev(); }
			catch (const std::range_error&) { return *this; }
			try { while (ItR->Ship->first <= key) ItR = &next(); }
			catch (const std::range_error&) { exit(8);ItR = &nul_; ItR->Ship = NIL; }
			return *this;
		}

		~__IterTree( ) { ItR = NULL; }
};


/*************************************************************************************************************
*	@brief	drived Red _ Black _ tree 
*	@param	Pr	pair to stored it (Shipment)
*	@param	Allocator to allocate the @a Pr
*************************************************************************************************************/	
template < class Container >
	class _BSTree : public BST<Container> {


		typedef	BST< Container>					__Base;

	public:
		typedef	typename Container::value_type	value_type;

		typedef	typename __Base::key_type		key_type;
		typedef	typename __Base::size_type		size_type;

		typedef __IterTree<_BSTree>				IterTree;

		typedef	typename __Base::__road				__base;

		_BSTree():__Base() { }

		size_type	size() const { return  this->Size; }
		bool		empty() const { return size() ? false : true; }

		IterTree	get_Root() const  { return IterTree(this->seed); }
		IterTree	get_last() const  { return this->seed ? IterTree(this->seed->eldest(), false): IterTree(); }
		IterTree	get_first() const { return this->seed ? IterTree(this->seed->youngest()): IterTree(); }

		void		swap (_BSTree& other) {

			std::swap (this->seed, other.seed);
			std::swap (this->_Alloc, other._Alloc);
			std::swap (this->_SAlloc, other._SAlloc);
			std::swap (this->Size, other.Size);
			
		}
		void		destroy() {

			if (this->seed) {

				this->_SAlloc.destroy(this->seed);
				this->_SAlloc.deallocate(this->seed, 1);
			}
			this->seed = NIL;
			this->Size = 0;
		}

};




# endif
