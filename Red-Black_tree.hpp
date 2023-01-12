/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Red-Black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/13 12:20:07 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

# include<iostream>
#include <cstdlib>
# include<climits>
# include<memory>

# include"utility.hpp"
# include"iterator.hpp"



/*************************************************************************************************************
*	@brief	base Red _ Black _ tree
*	@param	T_SHIP	Shipment to stor
*************************************************************************************************************/	
template < class T_SHIP>
	class RBT {

			# define	RED		1
			# define	BLACK	0
			# define	NIL		NULL
			# define	SE		37/* SE_NIOR */
			# define	JU		13/* JU_NIOR */
			# define	ROOT	33
			# define	NOTHING	7331

			typedef		std::allocator<RBT>	 Allocator;
			typedef 	typename Allocator::size_type size_type;

		protected:
			typedef		typename T_SHIP::first_type		key_type;
			typedef		typename T_SHIP::second_type 	v_map;

			T_SHIP*			Ship;/* load */
			bool			Color;
			bool			Empty;
			size_type		Size;
			RBT*			P;/* root of subtree(parent), NIL if node has root */
			RBT*			L_ch;/* left subtree, youngest son */
			RBT*			R_ch;/* right subtree, eldest son */

			Allocator		_Alloc;

		public:
/***************************  @category	 __  constructor  __  ***********************************************/


			RBT (): Ship(NIL), Size(0) {

				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;

				Empty	= true;

				_Alloc	= Allocator();
			}
			RBT (const RBT& tree) { *this = tree; }
			RBT (const T_SHIP& ship): Ship(&ship), Size(1) {

				/* case 0 */
				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Empty	= false;

				_Alloc	= Allocator();
			};



/***************************  @category	 __  encapsulation getters  __  *************************************/


	/*********************************************************************************************************
	*	@return		pointer parent node
	*********************************************************************************************************/
			RBT*	get_P()	const		{ return P;    }

	/*********************************************************************************************************
	*	@return		pointer left child node
	*********************************************************************************************************/
			RBT*	get_Lch() const		{ return L_ch; }

	/*********************************************************************************************************
	*	@return		pointer rigth child node
	*********************************************************************************************************/
			RBT*	get_Rch() const		{ return R_ch; }

	/*********************************************************************************************************
	*	@return		shipment reference
	*********************************************************************************************************/		
			T_SHIP&		get_Ship() const { return Ship ? *Ship : throw std::logic_error("Ship geter") , *Ship ; }




			short	WhoIm() const {

				if (P == NIL)
					return ROOT;
				if (P->L_ch == this)
					return JU;
				if (P->R_ch == this)
					return SE;
				throw std::logic_error("key ");
				return NOTHING;
			}
			short	WhoIm(const RBT* node) const {

				if (node == NIL)
					return NOTHING;
				return node->WhoIm();
			}


			bool	operator== (const RBT& tree) const {

				if (Ship && Ship->first == tree.Ship->first)
					return true;
				return false;
			}



/***************************  @category	 __  BST # tree intertion  __  **************************************/


	/*********************************************************************************************************
	*	@brief insert Ship (pair) inside the tree, exacption in case of duplicate key in tree
	*	@param ship shipment to insert
 	*********************************************************************************************************/
		void		insert (T_SHIP& ship) {

				if (not(Empty))
					return insertion(ship, this);

				Ship	= &ship;
				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Empty = false;

				++Size;
			}

	/*********************************************************************************************************
	*	@brief insert  node inside the tree, exacption in case of duplicate key in tree
	*	@param ship shipment to insert
 	*********************************************************************************************************/
		void		insert (RBT& _node) {

				if (not(Empty))
					return insertion(_node, this);

				Ship	= _node.Ship;
				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Empty = false;

				++Size;
			}


/***************************  @category	 __  BST # binary search tree  __  **********************************/

	/*********************************************************************************************************
	*	@return  node of the key, NIL if not find
 	*********************************************************************************************************/
		RBT*	search (key_type& key) const throw() {

			if (Empty)
				return NIL;
			return searching(key, const_cast<RBT*> (this));
		}

	/*********************************************************************************************************
	*	@return  node of the key, NIL if not find
	*	@param flag exeception or insirtion if not find
 	*********************************************************************************************************/
		v_map&		search (key_type& key, bool ex) {

			RBT* find = NIL;

			if (not(Empty))
				find = searching(key, const_cast<RBT*> (this));

			if (find)
				return find->Ship->second;
			if (ex)
				throw std::out_of_range ("key search");

			T_SHIP pair = ft::make_pair <key_type, v_map>(key, v_map());
			return  insert(pair), search(key, not(__EXCEPTIONS));
		}



/***************************  @category	 __  BST #  node deletion tree  __  *********************************/

	/*********************************************************************************************************
	*	@param 	key
	*	@return exictence true/false
	*********************************************************************************************************/
		bool		del (key_type& key) throw() {

			RBT* indecated = const_cast<RBT<T_SHIP>*> (search(key));

			if (indecated)
				_delete(*indecated);
			else
				return false;
			return true;
		}

	/*********************************************************************************************************
	*	@overload (2)
	*	@param 	Shipment (pair)
	*********************************************************************************************************/
		void		del (T_SHIP& ship) throw() { del (ship.first); }	



		private:
			RBT (const RBT& tree,  bool): Ship(tree.Ship) {

				/* the copy assignment constructor here is dangerous, because the 
					destroying of an object have a role in killing all his child */
				Color	= tree.Color;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Empty	= false;

				_Alloc	= tree._Alloc;
			}
			RBT (T_SHIP& ship, const RBT& parent): Ship(&ship), _Alloc(Allocator()) {

				Color	= RED;
				*P		= parent;
				L_ch	= NIL;
				R_ch	= NIL;
			}
			RBT&	operator= (const RBT& tree)/*  half copy , inside */ {

				Ship	= tree.Ship;
				if (WhoIm() != ROOT)
					Color	= tree.Color;
				return *this;
			}

			void	swap (RBT& subtree) {

				RBT tmp (*this, false);
				*this = subtree;
				subtree = tmp;
			}
			void	recolor() {

				if (WhoIm() == ROOT)
					return ;
				if (Color == RED)
					Color = BLACK;
				else
					Color = RED;
			}

		protected:
			RBT&	get_S() const/* Sibling */ {

				if (WhoIm() == ROOT || not(P->R_ch) || not(P->L_ch))
					throw std::logic_error("spiling doesn't");
				
				if (WhoIm() == JU)
					return *P->R_ch;
				//else if (WhoIm() == SE)
				return *P->L_ch;
			}
			RBT&	get_G() const/* GrandParent */ {

				if (P == NIL || P->P == NIL)
					throw std::logic_error("Grand P doesn't");
				return *P->P;
			}
			RBT&	get_U() const/* Uncle */ {

				if (WhoIm(P) == ROOT || WhoIm(P) == NOTHING)
					throw std::logic_error("Uncle doesn't");
				if (P->P->R_ch == NIL || P->P->L_ch == NIL)/* no Uncle */
					throw std::logic_error("Uncle doesn't");
				if (WhoIm(P) == JU)
					return *P->P->R_ch;
				//else if (WhoIm(P) == SE)
				return *P->P->L_ch;
			}

			RBT* 	this_RBT() { return this; }

		private:
			void	lr()/* Left  Rotation */ {

				if (not(this->R_ch))
					return ;
				RBT*	y = this->R_ch;

				swap(*R_ch);
				this->R_ch = this->R_ch->R_ch;
				if (this->R_ch)
					this->R_ch->P = this;
				y->R_ch = y->L_ch;

				y->L_ch = this->L_ch;
				if (this->L_ch)
					y->L_ch->P = y;

				this->L_ch = y;
			}
			void	rr()/* Rigth Rotation */ {

				if (not(this->L_ch))
					return ;
				RBT*	x = this->L_ch;

				swap(*L_ch);

				this->L_ch = this->L_ch->L_ch;
				if (this->L_ch)
					this->L_ch->P = this;

				x->L_ch = x->R_ch;

				x->R_ch = this->R_ch;
				if (this->R_ch)
					x->R_ch->P = x;

				this->R_ch = x;
			}

			void		adjustment(){

				if (P->Color == BLACK)
					return ;

				try {/* violate the properties of RBT */

					if (get_U().Color == BLACK)/* throw in case no uncle */
						throw "goto internal catch";

					{/* ( uncle exiicte and has RED color )*/ /* case 3.1 */

						P->Color = BLACK;
						get_U().Color = BLACK;
						P->P->recolor();

						if (P->P->Color == RED)
							P->P->adjustment();
					}
				}
				catch(...){

					if (WhoIm() == JU && WhoIm(P) == SE)/* case 3.2.2 */{

						P->rr();/* I'M ju to SE */
						goto C321;/* case 3.2.1 */
					}
					else if(WhoIm() == SE && WhoIm(P) == JU)/* case 3.2.4 */{

						P->lr();/* I'M SU to ju */
						goto C323;/* case 3.2.3 */
					}
					else if (WhoIm() == SE && WhoIm(P) == SE)/* case 3.2.1 */
		C321:			P->P->lr();
					else if (WhoIm() == JU && WhoIm(P) == JU)/* case 3.2.3 */
		C323:			P->P->rr();

					try{ get_S().Color = RED;}
						catch(...){};

					P->recolor();
					if (P->Color == RED)
						P->adjustment();
				}
			}
			void		insertion(T_SHIP& ship, RBT* subtree)/* BST_i # binary search tree insertion # */{
			
				if (subtree == NIL)/* It will never come true */
					return ;
				if (ship.first < subtree->Ship->first) {

					if (subtree->L_ch)
						subtree = subtree->L_ch;
					else {

						subtree->L_ch = _Alloc.allocate( 1);
						_Alloc.construct(subtree->L_ch, RBT(ship, *subtree));


						++Size;
						return subtree->L_ch->adjustment();
					}
				}
				else if (ship.first > subtree->Ship->first){

					if (subtree->R_ch)
						subtree = subtree->R_ch;
					else {

						subtree->R_ch = _Alloc.allocate( 1);
						_Alloc.construct(subtree->R_ch, RBT(ship, *subtree));


						++Size;
						return subtree->R_ch->adjustment();
					}
				}
				else
					throw "similar shipment violates the property of red-black tree" ;
				return insertion(ship, subtree);
			}
			void		insertion(RBT& _node, RBT* subtree) {
			
				if (subtree == NIL)/* It will never come true */
					return ;
				if (_node.ship.first < subtree->Ship->first) {

					if (subtree->L_ch)
						subtree = subtree->L_ch;
					else {

						subtree->L_ch = &_node;
						_node.P = subtree;

						return subtree->L_ch->adjustment();
					}
				}
				else if (_node.ship.first > subtree->Ship->first){

					if (subtree->R_ch)
						subtree = subtree->R_ch;
					else {

						subtree->R_ch = &_node;
						_node.P = subtree;

						return subtree->R_ch->adjustment();
					}
				}
				else
					throw "similar shipment violates the property of red-black tree" ;
				return insertion(_node, subtree);
			}

			RBT*	searching(key_type& key, RBT* subtree) const/* BST # binary search tree searching # */{
			
				if (not(subtree))
					return NIL;
				if (key < subtree->Ship->first)
						subtree = subtree->L_ch;
				else if (key > subtree->Ship->first)
						subtree = subtree->R_ch;
				else
					return  subtree;
				return searching(key, subtree);
			}

			RBT&		best_child() {

				RBT*	rch = this->R_ch;
				RBT*	lch = this->L_ch;
				int		l_path = 0;

				/* this function return the best child can replace this G^k
					without violate the the rule of BST (su(left), ju(rigth))*/
				if (not(lch) && not(rch))
					return *this;
				while (rch && rch->L_ch){

					rch = rch->L_ch;
					l_path++;
				}

				if (rch && rch->Color == RED)/*  */
					return *rch;
				
				while (lch && lch->R_ch) {

					l_path--;
					lch = lch->R_ch;
				}

				if (lch && lch->Color == RED)
					return *lch;

				if (not(lch) || l_path > 0)
					return *rch;
				return *lch;
			}
			void		delete_fixup(RBT* vctm) {

				if (vctm->get_S().Color == RED) {

					vctm->get_S().Color = BLACK;
					vctm->P->Color		 = RED;
					if (WhoIm(vctm) == JU)
						vctm->P->lr();
					else
						vctm->P->rr();
				}
				if (	vctm->get_S().L_ch && vctm->get_S().L_ch->Color == BLACK
					&&	vctm->get_S().R_ch && vctm->get_S().R_ch->Color == BLACK) {

					vctm->get_S().Color = RED;
					if (vctm->P->Color == BLACK)
						return delete_fixup(vctm->P);
					vctm->P->Color = BLACK;
					return ;
				}
				if (	vctm->get_S().L_ch && vctm->get_S().R_ch &&
						vctm->get_S().L_ch->Color != vctm->get_S().R_ch->Color) {

					vctm->get_S().L_ch->Color = BLACK;
					if (WhoIm(vctm) == JU){

						vctm->get_S().Color = RED;
						vctm->get_S().rr();
					}
					else {

						vctm->get_S().Color = RED;
						vctm->get_S().lr();
					}
				}
				if (vctm->get_S().R_ch && RED == vctm->get_S().R_ch->Color && WhoIm(vctm) == JU){

					vctm->get_S().R_ch->Color = BLACK;
					vctm->P->Color = BLACK;
					vctm->P->lr();
				}
				else if (vctm->get_S().L_ch && RED == vctm->get_S().L_ch->Color && WhoIm(vctm) == SE){

					vctm->get_S().L_ch->Color = BLACK;
					vctm->P->Color = BLACK;
					vctm->P->rr();
				}
			}
			void		_delete(RBT& criminal) {

				bool coler ;

				RBT& victim = criminal.best_child();

				Empty = (this->Ship->first == victim.Ship->first);
				if (Empty && (Ship = NIL))
					return ;

				RBT* ch = victim.L_ch ?  victim.L_ch :  victim.R_ch;

				if (victim.Color == BLACK)
					try {

						if (ch && ch->Color == RED)
							ch->recolor();
						else
							delete_fixup(&victim);
					}
					catch (...) { }

				criminal.swap(victim);
				coler			= criminal.Color;
				criminal.Color	= victim.Color;
				victim.Color	= coler;

				/* replace link to victim by who yastahik, ma ya3arfo hta had*/
				{
					if (ch)
						ch->P = victim.P;
					if (victim.WhoIm() == JU)
						victim.P->L_ch = ch;
					else if (victim.WhoIm() == SE)
						victim.P->R_ch = ch;
				}
				/* unlink the victim , mayaraf raso fin*/
				victim.L_ch	= NIL;
				victim.R_ch	= NIL;
				victim.P	= NIL;

				// _Alloc.deallocate (&victim, 1);

				delete &victim;
				--Size;
				/* end of history */
			}

		public:
			~RBT(){
				_Alloc.deallocate (R_ch, 1);
				_Alloc.deallocate (L_ch, 1);
			}
	};


template < class Pr>
	class IterTree { 


			typedef		RBT<Pr>			__node;
			typedef		__node&				ref_node;
			typedef		__node*					ptr_node;
			typedef	typename Pr::first_type		key_type;

			ptr_node		ItR;
			/** @brief indecate the (de/in)_crementation address of the node which not have (Left/Rigth) (-/+)*/
			ptrdiff_t		Out;

			ref_node	next() {

				ptr_node	rch = ItR->get_Rch();

				if (Out && Out + 1)
					return Out++, throw "std::error_condition()", *rch;
				if (not(rch)) {

					rch = ItR->get_P();
					while (ItR->WhoIm(rch) == SE)
						rch = rch->get_P();
					if (not(rch) or not(rch->get_P()))
						return Out++, throw "std::error_condition()", *rch;
					return *rch->get_P();
				}
				while (rch->get_Lch())
					rch = rch->get_Lch();
				return *rch;
			}
			ref_node	prev() {

				ptr_node	lch = ItR->get_Lch();

				if (Out && Out - 1)
					return Out--, throw "std::error_condition()", *lch;
				if (not(lch)) {

					lch = ItR->get_P();
					while (ItR->WhoIm(lch) == JU)
						lch = lch->get_P();
					if (not(lch) or not(lch->get_P()))
						return Out--, throw "std::error_condition()", *lch;
					return *lch->get_P();
				}
				while (lch->get_Rch())
					lch = lch->get_Rch();
				return *lch;
			}

		public:
			IterTree() { }

			IterTree (ref_node tree): ItR(&tree) { }
			IterTree (ptr_node tree): ItR(tree) { }
			IterTree (const IterTree& tree) { *this = tree; }

			Pr&	get_pair()  { return ItR->get_Ship(); }

			IterTree&	operator++() {

				try { ItR = &next(); } catch(...) {};
				return *this;
			}
			IterTree	operator++(int) {

				IterTree old = *this;
				try { ItR = &next(); } catch(...) {};
				return old;
			}
			IterTree&	operator--() {

				try { ItR = &prev(); } catch(...) {};
				return *this;
			}
			IterTree	operator--(int) {

				IterTree old = *this;
				try { ItR = &prev(); } catch(...) {};
				return old;
			}

			IterTree&		operator<< (key_type& key) {

				// if (Out > 0)
				// 	Out = 1;
				// while (Out < 0)
				// 	++Out;

				if (ItR->get_Ship().first < key)
					while (ItR->get_P() && ItR->get_P()->get_Ship().first < key)
						ItR = ItR->get_P();
				if (ItR->get_P() && ItR->get_P()->get_Ship().first == key)
					return ItR = ItR->get_P(), *this;

				if (not(ItR->get_Rch()))
					goto CEND;

				while (1) {
					while (ItR->get_Rch() && ItR->get_Rch()->get_Ship().first < key)
						ItR = ItR->get_Rch();
					if (ItR->get_Lch()) {

						ItR = ItR->get_Lch();
						continue ;
					}
					if (ItR->get_Rch())
						return ItR = ItR->get_Rch(), *this;
					goto CEND;
				}
				if (0) {

/* convention end () */	
			CEND:	while (ItR->get_P())
						ItR = ItR->get_P();
					while (ItR->get_Rch())
						ItR = ItR->get_Rch();
					Out = 1;
					++ItR;/* must be the next address after last node ( last key )*/
				}
				return *this;
			}
			IterTree&		operator>> (key_type& key) {

				// if (Out > 0)
				// 	Out = 1;
				// while (Out < 0)
				// 	++Out;

				if (ItR->get_Ship().first < key)
					while (ItR->get_P() && ItR->get_P()->get_Ship().first < key)
						ItR = ItR->get_P();
				if (ItR->get_P() && ItR->get_P()->get_Ship().first == key)
					return ItR = ItR->get_P(), *this;

				if (not(ItR->get_Rch()))
					goto CEND;

				while (1) {
					while (ItR->get_Rch() && ItR->get_Rch()->get_Ship().first < key)
						ItR = ItR->get_Rch();
					if (ItR->get_Lch()) {

						ItR = ItR->get_Lch();
						continue ;
					}
					if (ItR->get_Rch())
						return ItR = ItR->get_Rch(), *this;
					goto CEND;
				}
				if (0) {

/* convention end () */	
			CEND:	while (ItR->get_P())
						ItR = ItR->get_P();
					while (ItR->get_Rch())
						ItR = ItR->get_Rch();
					Out = 1;
					++ItR;/* must be the next address after last node ( last key )*/
				}
				return *this;
			}
			bool	operator!= (const IterTree& pIt) { return pIt.ItR == ItR ? false : true; }
			bool	operator== (const IterTree& pIt) { return not(*this == pIt); }
	};


/*************************************************************************************************************
*	@brief	drived Red _ Black _ tree 
*	@param	Pr	pair to stored it (Shipment)
*	@param	Allocator to allocate the @a Pr
*************************************************************************************************************/	
template < class Pr, class Allocator = std::allocator<Pr> >
	class _RBtree : public RBT<Pr> {


			typedef		RBT<Pr>				__Base;
			typedef	typename __Base::v_map			v_map;
			typedef	typename __Base::key_type			key_type;
			typedef	typename Allocator::size_type			size_type;

		public:
			typedef		RBT<Pr>				__base;

			_RBtree():__base() { }


			bool		empty() const { return this->Empty; }
			size_type	size() const { return  this->Size; }

			IterTree<Pr>	get_last() 	{

				__Base*  Last = this->this_RBT();
				
				while (Last->get_Lch())
					Last = Last->get_Lch();
				return size() ? IterTree<Pr>(Last) : IterTree<Pr>(NIL);
			}
			IterTree<Pr>	get_first() {

				__Base*  Frst = this->this_RBT();
				
				while (Frst->get_Rch())
					Frst = Frst->get_Rch();
				return size() ? IterTree<Pr>(Frst) : IterTree<Pr>(NIL);
			}
			IterTree<Pr>	get_Root() 	{ return size() ? IterTree<Pr>(this->this_RBT()) : IterTree<Pr>(NIL); }


			void		destroy() {

				this->_Alloc.deallocate(this->L_ch, 1);
				this->_Alloc.deallocate(this->R_ch, 1);
				this->Empty = true;
				this->Size = not(true);
			}

	};




# endif
