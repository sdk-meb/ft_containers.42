
# include<iostream>
#include <cstdlib>
# include<climits>
#include<unistd.h>

# define	RED		1
# define	BLACK	0
# define	NIL		NULL
# define	SE		37/* SE_NIOR */
# define	JU		13/* JU_NIOR */
# define	ROOT	1337
# define	NOTHING	33

template <class T_SHIP>
	class RBT {

		// private:
		public:
				T_SHIP			Ship;/* load */
				bool			Color;
				bool			Empty;
				RBT*			P;/* root of subtree(parent), NIL if node has root*/
				RBT*			L_ch;/* left subtree, youngest son*/
				RBT*			R_ch;/* right subtree, eldest son*/

			RBT(){

				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Empty	= true;
			}
			RBT(const T_SHIP& ship): Ship(ship){

				/* case 0 */
				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Empty	= false;
			};
			RBT(const RBT& tree){

				/* the copy assignment constructor here is dangerous, because the 
					destroying of an object have a role in killing all his child */
				Color	= tree.Color;
				Ship	= tree.Ship;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Empty	= false;
			}
		
			void		insert(T_SHIP ship) {

				if (Empty){

					Ship = ship;
					Color	= BLACK;
					P		= NIL;
					L_ch	= NIL;
					R_ch	= NIL;
					Empty = false;
					return ;
				}
				insertion(ship, this);
			}
			const RBT*	search(T_SHIP& ship) const/* BST # binary search tree sherching # */{

				/* ????????????   return pointer must be much be dangerous */
				if (Empty)
					return NIL;
				return searching(ship, const_cast<RBT*> (this));
			}
			void		del(T_SHIP ship){

				RBT* indecated = const_cast<RBT<T_SHIP>*> (search(ship));

				if (indecated)
					_delete(*indecated);
			}

			~RBT(){
				try { delete R_ch; }
				catch(...){ }
				try { delete L_ch; }
				catch(...){ }
			}
		// private :
			RBT(const T_SHIP& ship, RBT& parent): Ship(ship){

				Color	= RED;
				P		= &parent;
				L_ch	= NIL;
				R_ch	= NIL;
			}

			void	recolor(){

				if (WhoIm() == ROOT)
					return ;
				if (Color == RED)
					Color = BLACK;
				else
					Color = RED;
			}

			short	WhoIm() const {

				if (P == NIL)
					return ROOT;
				if (P->L_ch == this)
					return JU;
				if (P->R_ch == this)
					return SE;
				return NOTHING;
			}
			short	WhoIs(const RBT* node) const {

				if (node == NIL)
					return NOTHING;
				return node->WhoIm();
			}

			RBT&	get_S() const/* Sibling */{

				if (WhoIm() == ROOT || not(P->R_ch) || not(P->L_ch))
					throw std::logic_error("spiling doesn't");
				
				if (WhoIm() == JU)
					return *P->R_ch;
				//else if (WhoIm() == SE)
				return *P->L_ch;
			}
			RBT&	get_G() const/* GrandParent */{

				if (P == NIL || P->P == NIL)
					throw std::logic_error("Grand P doesn't");
				return *P->P;
			}
			RBT&	get_U() const/* Uncle */{

				if (WhoIs(P) == ROOT || WhoIs(P) == NOTHING)
					throw std::logic_error("Uncle doesn't");
				if (P->P->R_ch == NIL || P->P->L_ch == NIL)/* no Uncle */
					throw std::logic_error("Uncle doesn't");
				if (WhoIs(P) == JU)
					return *P->P->R_ch;
				//else if (WhoIs(P) == SE)
				return *P->P->L_ch;
			}

			void	lr()/* Left Rotation */ {

				if (not(this->R_ch))
					return ;
				RBT*	y = this->R_ch;

				std::swap(Ship, R_ch->Ship);
				this->R_ch = this->R_ch->R_ch;
				if (this->R_ch)
					this->R_ch->P = this;
				y->R_ch = y->L_ch;

				y->L_ch = this->L_ch;
				if (this->L_ch)
					y->L_ch->P = y;

				this->L_ch = y;
			}
			void	rr()/* Rigth Rotation */{

				if (not(this->L_ch))
					return ;
				RBT*	x = this->L_ch;

				std::swap(Ship, L_ch->Ship);
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
						throw "";

					{/* ( uncle exiicte and has RED color )*/ /* case 3.1 */

						P->Color = BLACK;
						get_U().Color = BLACK;
						P->P->recolor();
						if (P->P->Color == RED)
							P->P->adjustment();
					}
				}
				catch(...){

					if (WhoIm() == JU && WhoIs(P) == SE)/* case 3.2.2 */{

						P->rr();/* I'M ju to SE */
						goto C321;/* case 3.2.1 */
					}
					else if(WhoIm() == SE && WhoIs(P) == JU)/* case 3.2.4 */{

						P->lr();/* I'M SU to ju */
						goto C323;/* case 3.2.3 */
					}
					else if (WhoIm() == SE && WhoIs(P) == SE)/* case 3.2.1 */
		C321:			P->P->lr();
					else if (WhoIm() == JU && WhoIs(P) == JU)/* case 3.2.3 */
		C323:			P->P->rr();
					else
						exit(3456);
					try{ get_S().Color = RED;}
						catch(...){};

					P->recolor();
					if (P->Color == RED)
						P->adjustment();
				}
			}
			void		insertion(const T_SHIP& ship, RBT* subtree)/* BST_i # binary search tree insertion # */{
			
				if (subtree == NIL)/* It will never come true */
					return ;
				if (ship < subtree->Ship){

					if (subtree->L_ch)
						subtree = subtree->L_ch;
					else {

						subtree->L_ch = new RBT(ship, *subtree);
						return subtree->L_ch->adjustment();
					}
				}
				else if (ship > subtree->Ship){

					if (subtree->R_ch)
						subtree = subtree->R_ch;
					else {

						subtree->R_ch = new RBT(ship, *subtree);
						return subtree->R_ch->adjustment();
					}
				}
				else
					throw "similar shipment violates the property of red-black tree" ;
				return insertion(ship, subtree);
			}
			const RBT*	searching(T_SHIP ship, RBT* subtree) const/* BST # binary search tree searching # */{
			
				if (subtree == NIL)
					return NIL;
				if (ship < subtree->Ship)
						subtree = subtree->L_ch;
				else if (ship > subtree->Ship)
						subtree = subtree->R_ch;
				else
					return  subtree;
				return searching(ship, subtree);
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
			
			void		delete_fixup(RBT* vctm){

				if (vctm->get_S().Color == RED) {

					vctm->get_S().Color = BLACK;
					vctm->P->Color		 = RED;
					if (WhoIs(vctm) == JU)
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
						vctm->get_S().L_ch->Color != vctm->get_S().R_ch->Color){

					vctm->get_S().L_ch->Color = BLACK;
					if (WhoIs(vctm) == JU){

						vctm->get_S().Color = RED;
						vctm->get_S().rr();
					}
					else {

						vctm->get_S().Color = RED;
						vctm->get_S().lr();
					}
				}
				if (vctm->get_S().R_ch && RED == vctm->get_S().R_ch->Color && WhoIs(vctm) == JU){

					vctm->get_S().R_ch->Color = BLACK;
					vctm->P->Color = BLACK;
					vctm->P->lr();
				}
				else if (vctm->get_S().L_ch && RED == vctm->get_S().L_ch->Color && WhoIs(vctm) == SE){

					vctm->get_S().L_ch->Color = BLACK;
					vctm->P->Color = BLACK;
					vctm->P->rr();
				}
			}

			void		_delete(RBT& criminal){


				RBT& victim = criminal.best_child();

				Empty = (*this == victim);
				if (Empty)
					return ;

				RBT* ch = victim.L_ch ?  victim.L_ch :  victim.R_ch;

				if (victim.Color == BLACK)
					try {

							if (ch && ch->Color == RED)
								ch->recolor();
							else
								delete_fixup(&victim);
					}
					catch (...) {}

				std::swap(criminal->Ship, victim->Ship);

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

				delete &victim; /* end of history */
			}

		RBT&	youngest() const throw() {

			RBT* tmp = const_cast<RBT*>(this);

			while (tmp->L_ch) tmp = tmp->L_ch;
					
			return *tmp;
		}

		RBT&	eldest() const throw() {

			RBT* tmp = const_cast<RBT*>(this);

			while (tmp->R_ch) tmp = tmp->R_ch;

			return *tmp;
		}

		RBT&	next()  {

			if (R_ch) return R_ch->youngest();

			RBT*	tmp = this;

			while (tmp->WhoIm() == SE) tmp = tmp->P;
			if (tmp->WhoIm() == ROOT)
                throw std::range_error ("no next");/* this is the eldest in tree*/
			return *tmp->P;
		}

		RBT&	prev()  {

			if (L_ch) return L_ch->eldest();

			RBT*	tmp = this;

			while (tmp->WhoIm() == JU) tmp = tmp->P;
			if (tmp->WhoIm() == ROOT)
                throw std::range_error ("no prev");/* this is the young in tree*/
			return *tmp->P;
		}
	};


int	main(){

	 RBT<int> t;

	int count = 699;

	srand (count);

		try {
		for (size_t i = count; i ; --i)
			t.insert (rand());
		}catch (const char* e) { std::cerr << e << std::endl; }
		// for (size_t i = count / 7; i; --i)
		// 	t.del (rand());
		
		try {
		for ( RBT<int> *o = &t.eldest(); ; o = &o->prev())
			std::cout << o->Ship << std::endl;
		}catch (const std::range_error& ) { }
		try {
		for ( RBT<int> *o = &t.youngest(); ; o = &o->next())
			std::cerr << o->Ship << std::endl;
		}catch (const std::range_error& ) { }

	return 0;
}

/*  c++ RBT.cpp -std=c++98 -Wall -Wextra -Werror -fsanitize=address  */