/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/24 12:23:33 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

# include<iostream>
# include<algorithm>
#include <cstdlib>
# include<climits>
# include<memory>

#ifdef __linux
	class error_condition {};
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

		/** @brief constructor for nul node */
		__road_ (__road_* const _P=NIL) {

			Ship = &nul_;

			Color = BLACK;
			P = _P;
			L_ch = NIL;
			R_ch = NIL;
			copy_ship = true;
			_SAlloc = NIL;
		}
		__road_	(T_SHIP ship, SAllocator& _salloc)
			: _SAlloc(&_salloc), _Alloc(Allocator()) {

			Ship =  _Alloc.allocate(1);
			_Alloc.construct(Ship, ship);

			Color	= RED;

			P		= NIL;
			L_ch	= NIL;
			R_ch	= NIL;
			copy_ship = false;
		}
		__road_	(T_SHIP& ship, SAllocator& _salloc, Allocator& alloc)
			: _SAlloc(&_salloc), Ship(&ship), _Alloc(alloc) {

			Color	= RED;

			P		= NIL;
			L_ch	= NIL;
			R_ch	= NIL;

			copy_ship = false;
		}
		__road_	(T_SHIP* ship, SAllocator& _salloc, Allocator& alloc)
			: _SAlloc(&_salloc), Ship(ship), _Alloc(alloc) {

			if (not(Ship))
				throw "null to ship";
			Color	= RED;

			P		= NIL;
			L_ch	= NIL;
			R_ch	= NIL;

			copy_ship = false;
		}
		__road_	(typename T_SHIP::first_type& key, SAllocator& _salloc)
			: _SAlloc(&_salloc), _Alloc(Allocator()) {

			Ship =  _Alloc.allocate(1);
			_Alloc.construct(Ship, ft::make_pair
				<typename T_SHIP::first_type, typename T_SHIP::second_type>
					(key, typename T_SHIP::second_type()));

			Color	= RED;

			P		= NIL;
			L_ch	= NIL;
			R_ch	= NIL;

			copy_ship = false;
		}

		T_SHIP*			Ship;/* load */
		bool			Color;
		bool			copy_ship;

		__road_*			P;/* root of subtree(parent), NIL if node has root */
		__road_*			L_ch;/* left subtree, youngest son */
		__road_*			R_ch;/* right subtree, eldest son */


	/*********************************************************************************************************
	*	@brief		swap any two ndoes, 
	*	@param		other	node in __road_
	*********************************************************************************************************/
		void	swap (__road_& other) {

			if (WhoIm() == JU)	P->L_ch = &other;
			else if (WhoIm() == SE)	P->R_ch = &other;

			if (other.WhoIm() == JU)	other.P->L_ch = this;
			else if (other.WhoIm() == SE)	other.P->R_ch = this;

			if (L_ch) L_ch->P = &other;
			if (R_ch) R_ch->P = &other;

			if (other.L_ch) other.L_ch->P = this;
			if (other.R_ch) other.R_ch->P = this;

			std::swap(*this, other);
		}

	/*********************************************************************************************************
	*	@return		JUNIOR in case of the node is left child of his parent
	*	@return		SENIOR in case of the node is the rigth child of his parent
	*	@return		otherwise	ROOT
	*	@exception	If and only	the logic that return NOTHING
	*********************************************************************************************************/
		short	WhoIm() const {

			if (P == NIL) return ROOT;
			if (P->L_ch == this) return JU;
			if (P->R_ch == this) return SE;

			return throw std::logic_error("tree bind unqualified"), NOTHING;
		}

		void	recolor() { Color = RED == Color ? BLACK : RED; }


/***************************  @category	 __   getters alogo __  *********************************************/

	/**	@exception  all @fn return reference */

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

			if (P->P->R_ch == NIL || P->P->L_ch == NIL)
				throw std::logic_error("Uncle doesn't");

			if (P->WhoIm() == JU)
				return *P->P->R_ch;
			return *P->P->L_ch;
		}


	/*********************************************************************************************************
	*	@brief		red black tree adjustment, for for violating the properties(rules)
	*********************************************************************************************************/
		void		adjustment() {

			if (P->Color == BLACK)
				return ;

			try {

				if (get_U().Color == BLACK)/* throw in case no uncle */
					throw "go to internal catch";

				{/* ( uncle exiicte and has RED color )*/ /* case 3.1 */

					P->Color = BLACK;
					get_U().Color = BLACK;
					P->P->recolor();

					if (P->P->Color == RED)
						P->P->adjustment();
				}
			}
			catch(...) {

				if (WhoIm() == JU && P->WhoIm() == SE)/* case 3.2.2 */{

					rr(P);
					goto C321;/* case 3.2.1 */
				}
				else if (WhoIm() == SE && P->WhoIm() == JU)/* case 3.2.4 */{

					lr(P);
					goto C323;/* case 3.2.3 */
				}
				else if (WhoIm() == SE && P->WhoIm() == SE)/* case 3.2.1 */
	C321:			lr(P->P);
				else if (WhoIm() == JU && P->WhoIm() == JU)/* case 3.2.3 */
	C323:			rr(P->P);

				try { get_S().Color = RED;}
					catch(...){};

				P->recolor();
				if (P->Color == RED)
					P->adjustment();
			}
		}

	/*********************************************************************************************************
	*	@brief	 rb-tree rules fixing
	*********************************************************************************************************/
		void		delete_fixup() {

				if (get_S().Color == RED) {

					get_S().Color = BLACK;
					P->Color		 = RED;
					if (WhoIm() == JU)
						P->lr();
					else
						P->rr();
				}
				if (	get_S().L_ch && get_S().L_ch->Color == BLACK
					&&	get_S().R_ch && get_S().R_ch->Color == BLACK) {

					get_S().Color = RED;
					if (P->Color == BLACK)
						return P->delete_fixup();
					P->Color = BLACK;
					return ;
				}
				if (	get_S().L_ch && get_S().R_ch &&
						get_S().L_ch->Color != get_S().R_ch->Color) {

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
				if (get_S().R_ch && RED == get_S().R_ch->Color && WhoIm() == JU){

					get_S().R_ch->Color = BLACK;
					P->Color = BLACK;
					P->lr();
				}
				else if (get_S().L_ch && RED == get_S().L_ch->Color && WhoIm() == SE){

					get_S().L_ch->Color = BLACK;
					P->Color = BLACK;
					P->rr();
				}
			}

	/*********************************************************************************************************
	*	@return	a node which can replace the caller node, without violating the binary search tree rules
	*********************************************************************************************************/
		__road_&	redemption() {

			__road_*	rch = this->R_ch;
			__road_*	lch = this->L_ch;

			if (not(lch) && not(rch))
				return *this;

			while (rch && rch->L_ch) rch = rch->L_ch;
			if (rch) return *rch;
	
			while (lch && lch->R_ch) lch = lch->R_ch;
			return *lch;
		}


	/*********************************************************************************************************
	*	@brief	Left  Rotation
	*	@param	_node	indicator to being rotated
	*********************************************************************************************************/
		void	lr (__road_* _node=NIL) {

			if (not(_node))
				_node = this;
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

			if (not(_node))
				_node = this; 
			if (not(_node->L_ch))
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
		void	operator= (const __road_& other) {

				this->Color = other.Color;
				this->_Alloc = other._Alloc;
				this->Ship = other.Ship;
				this->L_ch = other.L_ch;
				this->R_ch = other.R_ch;
				this->P = other.P;

				this->_SAlloc = NIL;
				this->copy_ship = true;
			}
		bool	operator== (const __road_& other) {

			return 
					other.Color == this->Color
					and other.Ship == this->Ship;
		}
		~__road_ () {

			if (not copy_ship) _Alloc.deallocate (Ship, 1);
			if (not _SAlloc) return ;
			_SAlloc->deallocate (L_ch, 1);
			_SAlloc->deallocate (R_ch, 1);
		}

};
template < class T_SHIP, class Allocator>
	T_SHIP	__road_<T_SHIP, Allocator>::nul_ = T_SHIP();



/*************************************************************************************************************
*	@brief	base Red _ Black _ tree
*	@param	T_SHIP	Shipment to stor
*************************************************************************************************************/
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
		__road&		insert (__road _node, bool ex=true) {

				_node.copy_ship = true;
				if (seed) return insertion(_node, seed, ex);

				seed = _SAlloc.allocate ( 1);

				_SAlloc.construct (seed, _node);
				seed->Color	= BLACK;

				++Size;
				return *seed;
		}

	/*********************************************************************************************************
	*	@brief insert  pair  inside the tree, exacption in case of duplicate key in tree
	*			, and thas not dealocated in destruction
	*	@param ship shipment to insert
 	*********************************************************************************************************/
		__road&		insert (T_SHIP& pair) { return insert (__road (pair, _SAlloc)); }

	/*********************************************************************************************************
	*	@brief insert key with default (pair) inside the tree, exacption in case of duplicate key in tree
	*	@param key indecator shipment to insert
	*	@overload	(2)
	*	@param	ex exeption true = default
	*	@exception permitted by order
 	*********************************************************************************************************/
		__road&		insert (key_type& key, bool ex=true) { return insert (__road (key, _SAlloc), ex); }



/***************************  @category	 __  BST # binary search tree  __  **********************************/

	/*********************************************************************************************************
	*	@return  node indecated by the key, NIL if not find
 	*********************************************************************************************************/
		__road*	search (key_type& key) const throw() {

			if (not(seed)) return NIL;
			return searching(key, seed);
		}

	/*********************************************************************************************************
	*	@return content(value) idecated by the key
	*	@param flag exeception or insirtion in case of non-existence
 	*********************************************************************************************************/
		v_map&		search (key_type& key, bool ex) {

			__road* find = search(key);

			if (find) return find->Ship->second;
			if (ex) throw std::out_of_range ("key search");

			return  insert(key) .Ship->second;
		}



/***************************  @category	 __  BST #  node deletion tree  __  *********************************/

	/*********************************************************************************************************
	*	@param 	key
	*	@return result of deletion true/false
	*********************************************************************************************************/
		bool		del (key_type& key) throw() {

			__road* indecated = search(key);

			if (indecated) _delete(indecated);
			else return false;
			return true;
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
		__road&		insertion(__road& _node, __road* sub, bool ex=true) {

			if (_node.Ship->first < sub->Ship->first) {

				if (sub->L_ch) sub = sub->L_ch;
				else {

					sub->L_ch = _SAlloc.allocate(1);
					_SAlloc.construct (sub->L_ch, _node);
					sub->L_ch->P = sub;
					// sub->L_ch->adjustment();
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
					// sub->R_ch->adjustment();
					++Size;
					return *sub->R_ch;
				}
			}
			else if (ex)
				throw std::overflow_error ("similar shipment violates the property of map rules") ;
			else
				return _node;
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

			if (not(criminal))
				return ;
			__road* victim = &criminal->redemption();

			criminal->swap (*victim);
			std::swap (criminal->Color, victim->Color);

			__road* ch = victim->L_ch ?  victim->L_ch :  victim->R_ch;

			if (victim->Color == BLACK)
				try {

					if (ch && ch->Color == RED)
						ch->recolor();
					else
						victim->delete_fixup();
				}
				catch (...) { }

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

			_SAlloc.deallocate (victim, 1);

			--Size;
			/* end of history */
		}

	public:
		~RBT() { _SAlloc.deallocate (seed, 1); }
};




/*************************************************************************************************************
*	@brief	iterator helper, manage pointing tree
*	@param	Pr	pair(Shipment) to iterate it 
*************************************************************************************************************/	
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
		__IterTree (const __IterTree& tree) { ItR = tree.ItR; }

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
			catch (const std::logic_error&) { ItR = NULL; }
			catch (const std::range_error&) {

				nul_.P = ItR;
				if (ItR == &nul_) ItR = NULL;
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

			if (ItR == &nul_) { ItR = nul_.P; return *this; }
			try { ItR = &prev(); }
			catch (const error_condition&) { }
			catch (const std::range_error&) { ItR = NULL; }
			return *this;
		}
		__IterTree	operator--(int) {

			__IterTree old = *this;
			--(*this);
			return old;
		}

		__IterTree&		operator<< (key_type& key) {

			if (ItR->Ship->first < key)
				while (ItR->P && ItR->P->Ship->first < key)
					ItR = ItR->P;
			if (ItR->P && ItR->P->Ship->first == key)
				return ItR = ItR->P, *this;

			if (not(ItR->R_ch))
				goto CEND;

			while (1) {
				while (ItR->R_ch && ItR->R_ch->Ship->first < key)
					ItR = ItR->R_ch;
				if (ItR->L_ch) {

					ItR = ItR->L_ch;
					continue ;
				}
				if (ItR->R_ch)
					return ItR = ItR->R_ch, *this;
				goto CEND;
			}
			if (0) {

/* convention end () */	
		CEND:	while (ItR->P)
					ItR = ItR->P;
				while (ItR->R_ch)
					ItR = ItR->R_ch;
				// Out = 1;
				++ItR;/* must be the next address after last node ( last key )*/
			}
			return *this;
		}
		__IterTree&		operator>> (key_type& key) {

			if (ItR->Ship->first < key)
				while (ItR->P && ItR->P->Ship->first < key)
					ItR = ItR->P;
			if (ItR->P && ItR->P->Ship->first == key)
				return ItR = ItR->P, *this;

			if (not(ItR->R_ch))
				goto CEND;

			while (1) {
				while (ItR->R_ch && ItR->R_ch->Ship->first < key)
					ItR = ItR->R_ch;
				if (ItR->L_ch) {

					ItR = ItR->L_ch;
					continue ;
				}
				if (ItR->R_ch)
					return ItR = ItR->R_ch, *this;
				goto CEND;
			}
			if (0) {

		CEND:	while (ItR->P)
					ItR = ItR->P;
				while (ItR->R_ch)
					ItR = ItR->R_ch;
				// Out = 1;
				++ItR;/* must be the next address after last node ( last key )*/
			}
			return *this;
		}

};


/*************************************************************************************************************
*	@brief	drived Red _ Black _ tree 
*	@param	Pr	pair to stored it (Shipment)
*	@param	Allocator to allocate the @a Pr
*************************************************************************************************************/	
template < class Pr, class Allocator = std::allocator<Pr > >
	class _RBtree : public RBT<Pr, Allocator> {


		typedef	RBT<Pr, Allocator>					__Base;
		typedef	typename __Base::v_map				v_map;
		typedef	typename __Base::key_type			key_type;
		typedef	typename Allocator::size_type		size_type;
		typedef	__IterTree<Pr, Allocator>			IterTree;

	public:
		typedef	typename __Base::__road				__base;

		_RBtree():__Base() { }

		bool		empty() const { return size() ? false : true; }
		size_type	size() const { return  this->Size; }

		IterTree	get_Root() 	{ return this->seed ? IterTree(this->seed) : IterTree(); }
		IterTree	get_last() 	{ return this->seed ? IterTree(this->seed->eldest(), false): IterTree(); }
		IterTree	get_first() { return this->seed ? IterTree(this->seed->youngest()): IterTree(); }

		void		destroy() {

			this->_SAlloc.deallocate(this->seed, 1);
			this->seed = NIL;
			this->Size = 0;
		}

	};




# endif
