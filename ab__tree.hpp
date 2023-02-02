/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab__tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:46:23 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/02 13:55:34 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef AB_TREE_HPP
# define AB_TREE_HPP


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
			# define	SE		37/* SE_NIOR */
			# define	JU		13/* JU_NIOR */
			# define	ROOT	33
			# define	NOTHING	7331


/*************************************************************************************************************
*	@brief	data base of tree shipment
*	@param	T_SHIP	Shipment to stor
*************************************************************************************************************/
template < class T_SHIP, class Allocator = std::allocator<T_SHIP> >
	class __road_ {

	public:

		static	T_SHIP		nul_;

		__road_ (const __road_& other) { *this = other; }
		__road_ (__road_* const _P=NULL) { init_(); Color = BLACK; P = _P; }
		__road_	(T_SHIP ship, Allocator& _alloc) {

			init_();
			Ship =  _alloc.allocate(1);
			_alloc.construct(Ship, ship);
		}

	private:

		void	init_ () {

			Ship		= &nul_;
			Color		= RED;

			P		= NULL;
			L_ch	= NULL;
			R_ch	= NULL;
		}

	public:
		T_SHIP*			Ship;/* load */
		bool			Color;

		__road_*		P;/* root of subtree(parent), NULL if node has root */
		__road_*		L_ch;/* left subtree, youngest son */
		__road_*		R_ch;/* right subtree, eldest son */


	/*********************************************************************************************************
	*	@return		JUNIOR in case of the node is left child of his parent
	*	@return		SENIOR in case of the node is the rigth child of his parent
	*	@return		otherwise ROOT
	*	@exception	If and only if the bind logic that return NOTHING
	*********************************************************************************************************/
		short	WhoIm() const {

			if (P == NULL) return ROOT;
			if (P->L_ch == this) return JU;
			if (P->R_ch == this) return SE;

			return std::__throw_logic_error ("tree bind unqualified"), NOTHING;
		}

		void	recolor() { Color = RED == Color ? BLACK : RED; }


/***************************  @category	 __   getters alogo __  *********************************************/


	/*********************************************************************************************************
	*	@return		Sibling (reference)
	*********************************************************************************************************/
		__road_&	get_S() const {

			if (WhoIm() == ROOT or not P->R_ch or not P->L_ch)
				std::__throw_logic_error ("spiling doesn't");

			if (WhoIm() == JU)
				return *P->R_ch;
			return *P->L_ch;
		}

	/*********************************************************************************************************
	*	@return		GrandParent (reference)
	*********************************************************************************************************/
		__road_&	get_G() const {

			if (WhoIm() == ROOT or P->WhoIm() == ROOT)
				std::__throw_logic_error ("Grand P doesn't");
			return *P->P;
		}

	/*********************************************************************************************************
	*	@return			Uncle (reference)
	*********************************************************************************************************/
		__road_&	get_U() const {

			if (WhoIm() == ROOT or P->WhoIm() == ROOT)
				std::__throw_logic_error ("Uncle doesn't");

			if (get_G().R_ch == NULL or get_G().L_ch == NULL)
				std::__throw_logic_error ("Uncle doesn't");

			if (P->WhoIm() == JU)
				return *get_G().R_ch;
			return *get_G().L_ch;
		}


	/*********************************************************************************************************
	*	@brief		red black tree adjustment, for for violating the properties(rules)
	*********************************************************************************************************/
		void		adjustment() {
return;
			if (Color not_eq RED or P->Color not_eq RED) return ;

			try {/* violate the properties of RBT */

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
			if (Color not_eq RED) return;

			try { if (get_S().Color == RED) {

				get_S().recolor();
				P->recolor();
				if (WhoIm() == JU)
					P->lr();
				else
					P->rr();
			}	}
			catch (const std::logic_error&) { }
			try { if (get_S().L_ch and get_S().L_ch->Color == BLACK
				and	get_S().R_ch and get_S().R_ch->Color == BLACK) {

				get_S().Color = RED;
				if (P->Color == BLACK)
					return P->delete_fixup();
				P->Color = BLACK;
				return ;
			}	}
			catch (const std::logic_error&) { }
			try { if (get_S().L_ch and get_S().R_ch
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
			}	}
			catch (const std::logic_error&) { }
			try { if (get_S().R_ch and RED == get_S().R_ch->Color and WhoIm() == JU) {

				get_S().R_ch->Color = BLACK;
				P->Color = BLACK;
				P->lr();
			}
			else if (get_S().L_ch and RED == get_S().L_ch->Color and WhoIm() == SE) {

				get_S().L_ch->Color = BLACK;
				P->Color = BLACK;
				P->rr();
			}	}
			catch (const std::logic_error&) { };
		}

	/*********************************************************************************************************
	*	@return	a node which can replace the caller node, without violating the binary search tree rules
	*********************************************************************************************************/
		__road_&	redemption() throw() {

			return this->L_ch ? this->L_ch->eldest() : *this;
		}

	private:
	/*********************************************************************************************************
	*	@brief	Left  Rotation
	*	@param	_node	indicator to being rotated
	*********************************************************************************************************/
		void	lr (__road_* _node=NULL) const {

			if (not _node) _node = const_cast<__road_*>(this);;
			if (not _node->R_ch) std::__throw_logic_error ("unqualified left rotation!");
			return _node->_lr();
		}

		void	_lr() throw() {

			__road_*	y = this->R_ch;

			
			std::swap(Ship, y->Ship);
			std::swap(Color, y->Color);

			this->R_ch = this->R_ch->R_ch;
			if (this->R_ch)
				this->R_ch->P = this;
			y->R_ch = y->L_ch;

			y->L_ch = this->L_ch;
			if (this->L_ch)
				y->L_ch->P = y;

			this->L_ch = y;
		}


	/*********************************************************************************************************
	*	@brief	Rigth  Rotation
	*	@param	_node	indicator to being rotated 
	*********************************************************************************************************/
		void	rr (__road_* _node=NULL) const {

			if (not _node) _node = const_cast<__road_*>(this);; 
			if (not _node->L_ch) std::__throw_logic_error ("unqualified left rotation!");
			return _node->_rr();
		}

		void	_rr() throw() {

			__road_*	x = this->L_ch;

			std::swap(Ship, x->Ship);
			std::swap(Color, x->Color);

			this->L_ch = this->L_ch->L_ch;
			if (this->L_ch)
				this->L_ch->P = this;

			x->L_ch = x->R_ch;

			x->R_ch = this->R_ch;
			if (this->R_ch)
				x->R_ch->P = x;

			this->R_ch = x;
		}


	public:
	/*********************************************************************************************************
	*	@return	 youngest of this subtree
	*********************************************************************************************************/	
		__road_&	youngest() const throw() {

			__road_* tmp = const_cast<__road_*>(this);

			while (tmp->L_ch) tmp = tmp->L_ch;
					
			return *tmp;
		}

	/*********************************************************************************************************
	*	@return	eldest of this subtree
	*********************************************************************************************************/	
		__road_&	eldest() const throw() {

			__road_* tmp = const_cast<__road_*>(this);

			while (tmp->R_ch) tmp = tmp->R_ch;

			return *tmp;
		}


	/********************************************************************************************************* 
	* (1) ref param (save the copyrigth)
	* @brief copy assignment operator, shallow copy type, that make @a original( @a other) unthreatened by this
	* @param other  reference
	* @attention destroctor that deallocate the shipment and all branche of node, so (!)
	*********************************************************************************************************/
		void	operator= (const __road_& other) {

			this->Color	= other.Color;
			this->Ship	= other.Ship;
			this->L_ch	= other.L_ch;
			this->R_ch	= other.R_ch;
			this->P		= other.P;
		}

	template <typename Al, typename SAl>
		void destroy (Al& _alloc, SAl& _salloc) {

				if (Ship) {

					_alloc.destroy (Ship);
					_alloc.deallocate (Ship, 1);
				}
				if (L_ch) {

					L_ch->destroy(_alloc, _salloc);
					_salloc.destroy(L_ch);
					_salloc.deallocate (L_ch, 1);
				}
				if (R_ch) {

					R_ch->destroy(_alloc, _salloc);
					_salloc.destroy(R_ch);
					_salloc.deallocate (R_ch, 1);
				}
			}

};

template < class T_SHIP, class Alloc>
	T_SHIP	__road_<T_SHIP, Alloc>::nul_;



template <typename TP, typename TF, typename comp >
    typename ft::enable_if < is_pair<TP>::value and not is_pair<TF>::value , bool >::type
        t_comp (const TP& pr, const TF& frst, const comp& cmp) { return cmp (pr.first, frst); }

template <typename TF, typename TP, typename comp >
    typename ft::enable_if < is_pair<TP>::value and not is_pair<TF>::value , bool >::type
        t_comp (const TF& frst, const TP& pr, const comp& cmp) { return cmp (frst, pr.first); }

template <typename TP, typename comp>
    typename ft::enable_if < is_pair<TP>::value , bool >::type
        t_comp (const TP& pr1, const TP& pr2, const comp& cmp) { return cmp (pr1.first, pr2.first); }

template <typename TF, typename comp >
    typename ft::enable_if < not is_pair<TF>::value , bool >::type
		t_comp (const TF& f1, const TF& f2, const comp& cmp) { return cmp (f1, f2); }


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

		__IterTree_ () : k_comp(key_compare()) { }
		__IterTree_ (const key_compare& cmp) : k_comp(cmp) { ItR = &nul_; }
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
			catch (const std::logic_error&) { ItR = &nul_; nul_.P = NULL; }
			catch (const std::range_error&) {

				nul_.P = ItR;
				if (ItR == &nul_) nul_.P = NULL;
				else ItR = &nul_;
			}
			return *this;
		}

		__IterTree_&	operator--() {

			try { ItR = &prev(); }
			catch (const std::logic_error&) { ItR = (nul_.P ? nul_.P : &nul_); nul_.P = NULL; return *this; }
			catch (const error_condition&) { }
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

# include"./base_tree.hpp"

/*************************************************************************************************************
*	@brief	drived  _ tree 
*	@param  Container that contain all typename genereited
*	@param	DS data struct used
*************************************************************************************************************/	
template < class Container, class v_map>
	class __tree_ : protected ___abase<Container> {


	public:
		typedef 	typename Container::allocator_type					Allocator;

		typedef 	typename Container::size_type			size_type;

		typedef typename Container::value_type			T_SHIP;

		typedef typename Allocator::template rebind<__road_<T_SHIP> >::other	SAllocator;
		typedef const typename Container::key_type			key_type;
		typedef typename Container::key_compare			key_compare;

		typedef		__road_<T_SHIP, Allocator>				__road;



		typedef __IterTree_<__tree_>				IterTree;


/***************************  @category	 __  constructor  __  ***********************************************/

		__tree_ (const key_compare& cmp, Allocator& alloc)
			: ___abase <Container> (cmp, alloc) { }


/***************************  @category	 __  BST # tree intertion  __  **************************************/

	/*********************************************************************************************************
	*	@brief insert  node inside the tree, exacption in case of duplicate key in tree
	*	@param ship shipment to insert
	*	@param	ex exeption true = default
	*	@exception permitted by order
 	*********************************************************************************************************/
		__road&		insert (const __road& _node, bool ex=true) {

			if (this->seed) return this->insertion(const_cast<__road&>(_node), ex);

			this->seed = this->_SAlloc.allocate ( 1);

			this->_SAlloc.construct (this->seed, _node);
			this->seed->Color		= BLACK;

			++this->Size;
			return *this->seed;
		}

	/*********************************************************************************************************
	*	@brief insert  pair  inside the tree, exacption in case of duplicate key in tree
	*			, and thas not dealocated in destruction
	*	@param ship shipment to insert
 	*********************************************************************************************************/
		__road&		insert (const T_SHIP& ship) { return insert (__road (ship, this->_Alloc)); }


/***************************  @category	 __  BST # binary search tree  __  **********************************/

	/*********************************************************************************************************
	*	@return  node indecated by the key, NULL if not find
 	*********************************************************************************************************/
		__road*		search (key_type& key) const throw() {

			return not this->seed ? NULL : this->searching(key);
		}

	/*********************************************************************************************************
	*	@return content(value) idecated by the key
	*	@param flag exeception or insirtion in case of non-existence
 	*********************************************************************************************************/
		T_SHIP& search (key_type& key, bool ex) {

			__road* find = search(key);
			if (find) return *find->Ship;
			if (ex) std::__throw_range_error ("key search");
			return  *insert(ft::make_pair (key, v_map())).Ship;
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
		void		del (__road* _node) throw() { _delete (_node); }


		size_type	size() const { return  this->Size; }
		bool		empty() const { return size() ? false : true; }

		IterTree	get_Root() const  { return IterTree(this->seed, this->k_comp); }
		IterTree	get_last() const  { return this->seed ? IterTree(this->seed->eldest(), this->k_comp ,false): IterTree(this->k_comp); }
		IterTree	get_first() const { return this->seed ? IterTree(this->seed->youngest(), this->k_comp): IterTree(this->k_comp); }

		void		swap (__tree_& other) {

			std::swap (this->seed, other.seed);
			std::swap (this->Size, other.Size);
		}

		void		destroy() {

			if (this->seed) {

				this->seed->destroy (this->_Alloc, this->_SAlloc);
				this->_SAlloc.destroy(this->seed);
				this->_SAlloc.deallocate(this->seed, 1);
			}
			this->seed = NULL;
			this->Size = 0;
		}

	private:

	/*********************************************************************************************************
	*	@brief	binary tree insertion, that call @a adjustment that remove the violated rules of rb-tree
	*	@param	_node	indicator to being rotated
	*	@param	sub	indicator in last after recursions, the parent of the new child
	*	@param	ex exeption true = default
	*	@exception permitted by order
	*********************************************************************************************************/
		__road&		insertion(__road& _node, bool ex=true) {

			__road*	sub = &this->find_place (*_node.Ship);

			if (not t_comp (*_node.Ship, *sub->Ship, this->k_comp) and
				not t_comp (*sub->Ship, *_node.Ship, this->k_comp)) {

				_node.destroy(this->_Alloc,this-> _SAlloc);
				if (not ex) return *sub;
				std::__throw_overflow_error ("similar shipment violates the property of map rules") ;
			}
			else if (t_comp (*_node.Ship, *sub->Ship, this->k_comp)) {

				sub->L_ch = this->_SAlloc.allocate(1);

				this->_SAlloc.construct (sub->L_ch, _node);
				sub->L_ch->P = sub;

				sub->L_ch->adjustment();

				return ++this->Size, *sub->L_ch;
			}
			{
				sub->R_ch = this->_SAlloc.allocate(1);
				this->_SAlloc.construct (sub->R_ch, _node);
				sub->R_ch->P = sub;

				sub->R_ch->adjustment();
			}
			return ++this->Size, *sub->R_ch;
		}


	/*********************************************************************************************************
	*	@brief	binary tree deletion, that call @a delete_fixup rb-tree in case of violated rules
	*	@param	criminal	the node who has the shipment  referred by the key
	*********************************************************************************************************/
		void		_delete(__road* criminal) {
abort();
			if (not criminal) return ;

			__road* victim = &criminal->redemption();

			if (this->seed == victim) this->seed = victim->R_ch;

			std::swap (victim->Ship, criminal->Ship);

			__road* ch = victim->L_ch ?  victim->L_ch :  victim->R_ch;

			if (ch and ch->Color == RED) ch->recolor();
			else victim->delete_fixup();

			/* replace link to victim by who yastahik, ma ya3arfo hta had*/
			{
				if (ch) ch->P = victim->P;
				if (victim->WhoIm() == JU)	victim->P->L_ch = ch;
				else if (victim->WhoIm() == SE) victim->P->R_ch = ch;
			}
			/* unlink the victim , mayaraf raso fin*/
			victim->L_ch	= NULL;
			victim->R_ch	= NULL;
			victim->P	= NULL;

			victim->destroy(this->_Alloc,this-> _SAlloc);
			this->_SAlloc.destroy(victim);
			this->_SAlloc.deallocate (victim, 1);

			--this->Size;
			/* end of history */
		}


};


# endif
