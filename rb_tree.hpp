/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/30 00:09:23 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

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

			# define	RED		1
			# define	BLACK	0
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
		__road_ (__road_* const _P=NIL) {

			init_();
			Color		= BLACK;
			P			= _P;
		}
		__road_	(T_SHIP ship, SAllocator& _salloc)
			: _SAlloc(&_salloc), _Alloc(Allocator()) {

			init_();
			Ship =  _Alloc.allocate(1);
			_Alloc.construct(Ship, ship);

		}
		__road_	(T_SHIP& ship, SAllocator& _salloc, Allocator& alloc)
			: _SAlloc(&_salloc), _Alloc(alloc) {

			init_();
			Ship = &ship;
		}
		__road_	(T_SHIP* ship, SAllocator& _salloc, Allocator& alloc)
			: _SAlloc(&_salloc), _Alloc(alloc) {

			init_();
			Ship = ship;
		}
		__road_	(typename T_SHIP::first_type& key, SAllocator& _salloc)
			: _SAlloc(&_salloc), _Alloc(Allocator()) {

			init_();
			Ship =  _Alloc.allocate(1);
			_Alloc.construct(Ship, ft::make_pair
				<typename T_SHIP::first_type, typename T_SHIP::second_type>
					(key, typename T_SHIP::second_type()));
		}

		void	init_ () {

			Ship		= &nul_;
			copy_ship	= true;
			Color		= RED;

			P		= NIL;
			L_ch	= NIL;
			R_ch	= NIL;
		}

		T_SHIP*			Ship;/* load */
		bool			Color;
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

		void	recolor() { Color = RED == Color ? BLACK : RED; }


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
	*	@brief		red black tree adjustment, for for violating the properties(rules)
	*********************************************************************************************************/
		void		adjustment() {

return;
			if (not P or P->Color == BLACK)
				return ;

			try {

				if (get_U().Color not_eq RED)/* throw in case no uncle */
					std::__throw_logic_error ("go to internal catch");

				/* ( uncle exiicte and has RED color )*/ /* case 3.1 */
				P->recolor();
				get_U().recolor();
				if (get_G().WhoIm() not_eq ROOT)
					get_G().recolor();
			}
			catch (const std::logic_error&) {

				if (WhoIm() == JU and P->WhoIm() == SE)/* case 3.2.2 */
					rr(P);/* case 3.2.1 */
				else if (WhoIm() == SE and P->WhoIm() == JU)/* case 3.2.4 */
					lr(P);/* case 3.2.3 */
				if (WhoIm() == SE and P->WhoIm() == SE)/* case 3.2.1 */{
		
					lr(&get_G());

					if (P->WhoIm() not_eq ROOT) P->recolor();
					try { get_S().Color = RED; }
					catch (const std::logic_error&) { };
					if (P->WhoIm() not_eq ROOT and P->Color == RED) P->adjustment();
				}
				else if (WhoIm() == JU and P->WhoIm() == JU)/* case 3.2.3 */{
		
					rr(&get_G());
					if (P->WhoIm() not_eq ROOT) P->recolor();
					try { get_S().Color = RED; }
					catch (const std::logic_error&) { };
					if (P->WhoIm() not_eq ROOT and P->Color == RED) P->adjustment();
				}
			}
		}

	/*********************************************************************************************************
	*	@brief	 rb-tree rules fixing
	*********************************************************************************************************/
		void		delete_fixup() {

	return;
				if (get_S().Color == RED) {

					get_S().recolor();
					P->recolor();
					if (WhoIm() == JU)
						P->lr();
					else
						P->rr();
				}
				if (get_S().L_ch and get_S().L_ch->Color == BLACK
					and	get_S().R_ch and get_S().R_ch->Color == BLACK) {

					get_S().Color = RED;
					if (P->Color == BLACK)
						return P->delete_fixup();
					P->Color = BLACK;
					return ;
				}
				if (get_S().L_ch and get_S().R_ch
					and	get_S().L_ch->Color != get_S().R_ch->Color) {

					get_S().L_ch->Color = BLACK;
					if (WhoIm() == JU){

						get_S().Color = RED;
						get_S().rr();
					}
					else {

						get_S().Color = RED;
						get_S().lr();
					}
				}
				if (get_S().R_ch and RED == get_S().R_ch->Color and WhoIm() == JU) {

					get_S().R_ch->Color = BLACK;
					P->Color = BLACK;
					P->lr();
				}
				else if (get_S().L_ch and RED == get_S().L_ch->Color and WhoIm() == SE) {

					get_S().L_ch->Color = BLACK;
					P->Color = BLACK;
					P->rr();
				}
			}

	/*********************************************************************************************************
	*	@return	a node which can replace the caller node, without violating the binary search tree rules
	*********************************************************************************************************/
		__road_&	redemption() throw() {

			return this->L_ch ? this->L_ch->eldest() : *this;
		}


	/*********************************************************************************************************
	*	@brief	Left  Rotation
	*	@param	_node	indicator to being rotated
	*********************************************************************************************************/
		void	lr (__road_* _node=NIL) {

			if (not(_node)) _node = this;
			if (not(_node->R_ch))
				throw std::logic_error("unqualified left rotation!");

			__road_*	_P	= _node->P;
			__road_*	y	= _node->R_ch;
			__road_*	_β	= y->L_ch;

			y->P	= _P;
			if 	(_node->WhoIm() == JU)	_P->L_ch = y;
			else if (_node->WhoIm() == SE)	_P->R_ch = y;

			_node->R_ch = _β;
			if (_β)	_β->P = _node;

			y->R_ch	= _node;
			_node->P = y;
		}

	/*********************************************************************************************************
	*	@brief	Rigth  Rotation
	*	@param	_node	indicator to being rotated 
	*********************************************************************************************************/
		void	rr (__road_* _node=NIL) {

			if (not _node) _node = this; 
			if (not _node->L_ch)
				throw std::logic_error("unqualified left rotation!");

			__road_*	_P	= _node->P;
			__road_*	x	= _node->L_ch;
			__road_*	_β	= x->R_ch;

			x->P	= _P;
			if 	(_node->WhoIm() == JU)	_P->L_ch = x;
			else if (_node->WhoIm() == SE)	_P->R_ch = x;

			_node->L_ch = _β;
			if (_β)	_β->P = _node;

			x->L_ch	= _node;
			_node->P = x;
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

			this->Color	= other.Color;
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
// template < class Container >
// 	class RBT {


// 		protected:
// 			typedef 	typename Container::allocator_type		Allocator;
// 			typedef 	typename Container::size_type			size_type;

// 			typedef 	typename Container::value_type			T_SHIP;
// 			typedef 	typename Container::key_type			key_type;
// 			typedef 	typename Container::mapped_type			v_map;

// 			typedef		__road_<T_SHIP, Allocator>				__road;

// 			typedef typename Allocator::template rebind<__road>::other	SAllocator;

template < class T_SHIP, class Allocator = std::allocator <T_SHIP> >
	class RBT {


		protected:
			typedef 	typename Allocator::size_type	size_type;
			typedef		typename T_SHIP::first_type		key_type;
			typedef		typename T_SHIP::second_type 	v_map;
			typedef		__road_<T_SHIP, Allocator>					__road;

			typedef typename Allocator::template rebind<__road>::other	SAllocator;

			Allocator			_Alloc;
			size_type			Size;
			__road*				seed;
			SAllocator			_SAlloc;


		public:
/***************************  @category	 __  constructor  __  ***********************************************/

		RBT (Allocator alloc = Allocator())
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
			seed->Color	= BLACK;
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

	/*********************************************************************************************************
	*	@brief insert key with default (pair) inside the tree, exacption in case of duplicate key in tree
	*	@param key indecator shipment to insert
	*	@overload	(2)
	*	@param	ex exeption true = default
	*	@exception permitted by order
 	*********************************************************************************************************/
		__road&		insert (const key_type& key, bool ex=true) { return insert (__road (key, _SAlloc), ex); }



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

			if (not ex) return  insert(key, false) .Ship->second;

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
					if (_node.Color == BLACK) throw "fddf";
					sub->L_ch->P = sub;

					sub->L_ch->copy_ship = false;
					sub->L_ch->adjustment();

					++Size;
					return *sub->L_ch;
				}
			}
			else if (_node.Ship->first > sub->Ship->first) {

				if (sub->R_ch) sub = sub->R_ch;
				else {

					sub->R_ch = _SAlloc.allocate(1);

					_SAlloc.construct (sub->R_ch, _node);
					if (_node.Color == BLACK) throw "fddf";
					sub->R_ch->P = sub;

					sub->R_ch->copy_ship = false;
					sub->R_ch->adjustment();
 
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
			if (victim->Color == BLACK) {

				if (ch and ch->Color == RED) ch->recolor();
				else victim->delete_fixup();
			}

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

		~RBT() {

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
// template < class Container >
// 	struct __IterTree {


// 		typedef typename Container::value_type		value_type;
// 		typedef	__road_<value_type, typename Container::allocator_type>	__node;
	
// 		typedef	__node&								ref_node;
// 		typedef	__node*								ptr_node;
// 		typedef typename Container::key_type		key_type;

template < class Pr, class Allocator >
	struct __IterTree {


		typedef	Pr							value_type;
		typedef	__road_<value_type, Allocator>		__node;
		typedef	__node&									ref_node;
		typedef	__node*								ptr_node;
		typedef	typename Pr::first_type			key_type;
	
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
// template < class Container >
// 	class _RBtree : public RBT<Container> {


// 		typedef	RBT< Container>					__Base;
// 		typedef	typename __Base::v_map			v_map;
// 		typedef	typename __Base::key_type		key_type;
// 		typedef	typename __Base::size_type		size_type;
// 		typedef	__IterTree< Container>			IterTree;

template < class Pr, class Allocator = std::allocator<Pr > >
	class _RBtree : public RBT<Pr, Allocator> {


		typedef	RBT<Pr, Allocator>					__Base;
		typedef	typename __Base::v_map				v_map;
		typedef	typename __Base::key_type			key_type;
		typedef	typename Allocator::size_type		size_type;
		typedef	__IterTree<Pr, Allocator>			IterTree;

	public:
		typedef	typename __Base::__road				__base;

	public:
		typedef	typename __Base::__road			__base;

		_RBtree():__Base() { }

		size_type	size() const { return  this->Size; }
		bool		empty() const { return size() ? false : true; }

		IterTree	get_Root() const  { return IterTree(this->seed); }
		IterTree	get_last() const  { return this->seed ? IterTree(this->seed->eldest(), false): IterTree(); }
		IterTree	get_first() const { return this->seed ? IterTree(this->seed->youngest()): IterTree(); }

		void		swap (_RBtree& other) {

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
