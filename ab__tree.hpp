/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab__tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:46:23 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/07 23:47:02 by mes-sadk         ###   ########.fr       */
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

			# define	__RED	1
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

		typedef typename Allocator::template rebind<__road_>::other SAlloc;

	public:

		static	T_SHIP		nul_;

		__road_ (__road_* const _P=NULL) { init_(); Color = BLACK; P = _P; }
		__road_	(T_SHIP ship, Allocator& _alloc) {

			init_();
			Ship =  _alloc.allocate(1);
			_alloc.construct(Ship, ship);
		}

	private:

		void	init_ () {

			Ship		= &nul_;
			Color		= __RED;

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

		void	recolor() { Color = (Color not_eq __RED and WhoIm() not_eq ROOT) ? __RED : BLACK; }
		bool	violate_rule () { return Color not_eq BLACK and P and P->Color not_eq BLACK; }

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
	*	@brief		__red black tree adjustment, for for violating the properties(rules)
	*********************************************************************************************************/
		void		adjustment() {

			/* this is the new node which has red color */
		}

	/*********************************************************************************************************
	*	@brief	 rb-tree rules fixing
	*********************************************************************************************************/
		void		delete_fixup() {

			/* a node which  in the progress of deletion (this),
				in case of Right that meant no Left and vice versa,
					no Left no Right means nothing */
		}

	/*********************************************************************************************************
	*	@return	a node which can replace the caller node, without violating the binary search tree rules
	*********************************************************************************************************/
		__road_&	__redemption() throw() {

			return	this->L_ch ? this->L_ch->eldest() : *this;
		}

	private:
	/*********************************************************************************************************
	*	@brief	Left  Rotation
	*	@param	_node	indicator to being rotated
	*********************************************************************************************************/
		void	lr (__road_* _node=NULL) const {

			if (not _node) _node = const_cast<__road_*>(this);;
			if (not _node->R_ch) std::__throw_logic_error ("unqualified left rotation!");
			return _node->unsaf_left_retate();
		}

		void	unsaf_left_retate() throw() {

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
			return _node->unsaf_rigth_retate();
		}

		void	unsaf_rigth_retate() throw() {

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
	*	@brief	duplacate the tree, deep copy of it
	*	@param	other tree to dup-it
	*	@param	_alloc allocator to alocate a new shipment
	*	@param	_salloc allocator to alocate a new ndoe
	*********************************************************************************************************/	
		void	dup_  (const __road_& other, Allocator& _alloc, SAlloc& _salloc) {

			init_();

			Color = other.Color;
			Ship = _alloc.allocate(1);
			_alloc.construct (Ship, *other.Ship);
			if (other.L_ch) {

				L_ch = _salloc.allocate (1);
				L_ch->dup_ (*other.L_ch, _alloc, _salloc);
				L_ch->P = this;
			}
			if (other.R_ch) {

				R_ch = _salloc.allocate (1);
				R_ch->dup_ (*other.R_ch, _alloc, _salloc);
				R_ch->P = this;
			}
			
		}


	/*********************************************************************************************************
	*	@brief	destory
	*	@param	_alloc allocator to dealocate the shipments
	*	@param	_salloc allocator to dealocate the ndoes
	*********************************************************************************************************/	
		void	destroy (Allocator& _alloc, SAlloc& _salloc) {

				if (Ship and Ship not_eq &nul_) {

					_alloc.destroy (Ship);
					_alloc.deallocate (Ship, 1);
					Ship = NULL;
				}
				if (L_ch) {

					L_ch->destroy(_alloc, _salloc);
					_salloc.destroy(L_ch);
					_salloc.deallocate (L_ch, 1);
					L_ch = NULL;
				}
				if (R_ch) {

					R_ch->destroy(_alloc, _salloc);
					_salloc.destroy(R_ch);
					_salloc.deallocate (R_ch, 1);
					R_ch = NULL;
				}
				P = NULL;
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

		IterTree	get_Root() const 
			{ return IterTree(this->seed, this->k_comp); }

		IterTree	get_last() const  
			{ return this->seed ? IterTree(this->seed->eldest(), this->k_comp ,false): IterTree(this->k_comp); }

		IterTree	get_first() const 
			{ return this->seed ? IterTree(this->seed->youngest(), this->k_comp): IterTree(this->k_comp); }

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

		void operator= (__tree_& other) {

			if (not other.seed or &other == this) return;
			destroy();

			this->seed = this->_SAlloc.allocate (1);
			this->seed->dup_ (*other.seed, this->_Alloc, this->_SAlloc);

			this->Size = other.size();
		}

	private:

	/*********************************************************************************************************
	*	@brief	binary tree insertion, that call @a adjustment that remove the violated rules of rb-tree
	*	@param	_node	indicator to being inserted
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
			return t_comp (*_node.Ship, *sub->Ship, this->k_comp)
			?(
				sub->L_ch = this->_SAlloc.allocate(1), this->_SAlloc.construct (sub->L_ch, _node),
				sub->L_ch->P = sub, sub->L_ch->adjustment(),
				++this->Size, *sub->L_ch
			)
			:(
				sub->R_ch = this->_SAlloc.allocate(1), this->_SAlloc.construct (sub->R_ch, _node),
				sub->R_ch->P = sub, sub->R_ch->adjustment(),
				++this->Size, *sub->R_ch
			);
		}


	/*********************************************************************************************************
	*	@brief	binary tree deletion, that call @a delete_fixup rb-tree in case of violated rules
	*	@param	criminal	the node who has the shipment  refer__red by the key
	*********************************************************************************************************/
		void		_delete(__road* criminal) {

			if (not criminal) return ;

			__road* victim = &criminal->__redemption();

			if (victim->WhoIm() == ROOT) this->seed = victim->R_ch;

			__road* ch = NULL;
			victim->delete_fixup();
			if (victim not_eq criminal) {

				std::swap (victim->Ship, criminal->Ship);
				ch = victim->L_ch;
			}
			else ch = victim->R_ch;
	
			if (ch) ch->P = victim->P;
			if (victim->WhoIm() == JU)	victim->P->L_ch = ch;
			else if (victim->WhoIm() == SE) victim->P->R_ch = ch;

			/* unlink the victim , mayaraf raso fin*/
			victim->L_ch = victim->R_ch = victim->P = NULL;

			victim->destroy(this->_Alloc,this-> _SAlloc);
			this->_SAlloc.destroy(victim);
			this->_SAlloc.deallocate (victim, 1);

			--this->Size;
			/* end of history */
		}


};


# endif
