/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab__tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:46:23 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/08 15:57:48 by mes-sadk         ###   ########.fr       */
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
		__road_&		adjustment (__road_*& root) {

			/* this is the new node which has red color */
			try { get_G(); } catch (const std::logic_error&) { return *this; }

			__road_* u;
			__road_* k = this;
			while (k->P->Color == __RED) {

			if (k->P->WhoIm() == SE) {

				try { u = &k->get_U();
					if (u->Color not_eq __RED) std::__throw_logic_error ("internal catch");

					u->Color = BLACK;
					k->P->Color = BLACK;
					k->get_G().Color = __RED;
					k = &k->get_G();
				}
				catch (const std::logic_error&) { /* no uncel or uncel is black */

					if (k->WhoIm() == JU) {

						k = k->P;
						k->rr (root);
					}
					k->P->Color = BLACK;
					k->get_G().Color = __RED;
					k->get_G().lr (root);
				}
			}
			else if (k->P->WhoIm() == JU) {

				try { u = &k->get_U();
					if (u->Color not_eq __RED) std::__throw_logic_error ("internal catch");

					u->Color = BLACK;
					k->P->Color = BLACK;
					k->get_G().Color = __RED;
					k = &k->get_G();
				}
				catch (const std::logic_error&) { /* no uncel or uncel is black */

					if (k->WhoIm() == SE) {

						k = k->P;
						k->lr (root);
					}
					k->P->Color = BLACK;
					k->get_G().Color = __RED;
					k->get_G().rr (root);
				}
			}
			else break;
			if (k->WhoIm() == ROOT) break;
		}
		return *this;
	}

	/*********************************************************************************************************
	*	@brief	 rb-tree rules fixing
	*********************************************************************************************************/
		void		delete_fixup (__road_*& root) {

			/* here the node which in the progress of deletion (this),
				in case of Right that meant no Left and vice versa,
					no Left no Right means nothing */
			if (Color not_eq BLACK) return;

			__road_* ch = R_ch ? R_ch : L_ch;
			if (ch and ch->Color == __RED) return ch->recolor();

			try { if (get_S().Color == __RED) {

				get_S().recolor();
				P->recolor();
				if (WhoIm() == JU)
					P->lr (root);
				else
					P->rr (root);
			}	}
			catch (const std::logic_error&) { }
			try { if (get_S().L_ch and get_S().L_ch->Color == BLACK
				and	get_S().R_ch and get_S().R_ch->Color == BLACK) {

				get_S().Color = __RED;
				if (P->Color == BLACK)
					return P->delete_fixup (root);
				P->Color = BLACK;
				return ;
			}	}
			catch (const std::logic_error&) { }
			try { if (get_S().L_ch and get_S().R_ch
				and	get_S().L_ch->Color != get_S().R_ch->Color) {

				get_S().L_ch->Color = BLACK;
				if (WhoIm() == JU){

					get_S().Color = __RED;
					get_S().rr (root);
				}
				else {

					get_S().Color = __RED;
					get_S().lr (root);
				}
			}	}
			catch (const std::logic_error&) { }
			try { if (get_S().R_ch and __RED == get_S().R_ch->Color and WhoIm() == JU) {

				get_S().R_ch->Color = BLACK;
				P->Color = BLACK;
				P->lr (root);
			}
			else if (get_S().L_ch and __RED == get_S().L_ch->Color and WhoIm() == SE) {

				get_S().L_ch->Color = BLACK;
				P->Color = BLACK;
				P->rr (root);
			}	}
			catch (const std::logic_error&) { };
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
		void	lr (__road_*& root, __road_* _node=NULL) const {

			if (not _node) _node = const_cast<__road_*>(this);;
			if (not _node->R_ch) std::__throw_logic_error ("unqualified left rotation!");
			return _node->unsaf_left_retate (root);
		}

		void	unsaf_left_retate (__road_*& root) throw() {

			__road_*	y = R_ch;

			R_ch = y->L_ch;
			if (R_ch) R_ch->P = this;

			y->P = P;
			if (WhoIm() == ROOT) root = y;
			else if (WhoIm() == SE) P->R_ch = y;
			else P->L_ch = y;

			y->L_ch = this;
			P = y;
		}


	/*********************************************************************************************************
	*	@brief	Rigth  Rotation
	*	@param	_node	indicator to being rotated 
	*********************************************************************************************************/
		void	rr (__road_*& root, __road_* _node=NULL) const {

			if (not _node) _node = const_cast<__road_*>(this);; 
			if (not _node->L_ch) std::__throw_logic_error ("unqualified left rotation!");
			return _node->unsaf_rigth_retate (root);
		}

		void	unsaf_rigth_retate (__road_*& root) throw() {

			__road_* y = L_ch;
			L_ch = y->R_ch;
			if (y->R_ch)
				y->R_ch->P = this;

			y->P = P;
			if (WhoIm() == ROOT)
				root = y;
			else if (WhoIm() == JU)
				P->L_ch = y;
			else
				P->R_ch = y;

			y->R_ch = this;
			P = y;
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
		__road&		insert (const T_SHIP& ship, bool ex=true) { return insert (__road (ship, this->_Alloc), ex); }


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

			if (not ex) return  *insert(ft::make_pair (key, v_map()), false).Ship;

			__road* find = search(key);
			if (not find) std::__throw_range_error ("key search");
			return *find->Ship;
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

			__road*&	child = t_comp (*_node.Ship, *sub->Ship, this->k_comp)
							? sub->L_ch : sub->R_ch;
		
			child = this->_SAlloc.allocate(1),

			this->_SAlloc.construct (child, _node);
			child->P = sub;
			++this->Size;
			return child->adjustment (this->seed);
		}


	/*********************************************************************************************************
	*	@brief	binary tree deletion, that call @a delete_fixup rb-tree in case of violated rules
	*	@param	criminal	the node who has the shipment  refer__red by the key
	*********************************************************************************************************/
		void		_delete(__road* criminal) {

			if (not criminal) return ;

			__road* victim = &criminal->__redemption();

			if (size() == 1) return destroy();
			if (victim->WhoIm() == ROOT) this->seed = victim->R_ch;
			else victim->delete_fixup (this->seed);

			this->seed->recolor();
			__road* ch = NULL;
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
