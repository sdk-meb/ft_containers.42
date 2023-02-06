
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
					_delete(indecated);
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

			
		void	recolor() { Color = (Color not_eq RED and WhoIm() not_eq ROOT) ? RED : BLACK; }
		bool	violate_rule () { return Color not_eq BLACK and P and P->Color not_eq BLACK; }

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

		void		adjustment() {

			if (not violate_rule()) return ;

			try {

				if (get_U().Color not_eq RED)/* throw in case no uncle */
					std::__throw_logic_error ("go to internal catch");

				/* ( uncle exiicte and has RED color )*/ /* case 3.1 */
				P->recolor();
				get_U().recolor();
				get_G().recolor();
				try { get_G().adjustment(); } catch (...) { abort(); }
			}
			catch (const std::logic_error&) {

				if (WhoIm() == JU and P->WhoIm() == SE)/* case 3.2.2 */
					P->rr();/* case 3.2.1 */
				else if (WhoIm() == SE and P->WhoIm() == JU)/* case 3.2.4 */
					P->lr();/* case 3.2.3 */
				if (WhoIm() == SE and P->WhoIm() == SE)/* case 3.2.1 */
					get_G().lr();
				else if (WhoIm() == JU and P->WhoIm() == JU)/* case 3.2.3 */
					get_G().rr();

				P->recolor();
				get_S().recolor();
				try { P->adjustment(); } catch (...) { abort(); }
			}
			catch (...) { abort(); }

		}
		
		
			void		insertion(const T_SHIP& ship, RBT* subtree)/* BST_i # binary search tree insertion # */{
			
				if (subtree == NIL)/* It will never come true */
					return ;
				while (1) {
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
				}
				return insertion(ship, subtree);
			}
			const RBT*	searching(T_SHIP ship, RBT* subtree) const/* BST # binary search tree searching # */{
			
				if (subtree == NIL)
					return NIL;
				while(1){
				if (ship < subtree->Ship)
						subtree = subtree->L_ch;
				else if (ship > subtree->Ship)
						subtree = subtree->R_ch;
				else
					return  subtree;
							}			return searching(ship, subtree);
			}

			RBT&		best_child() {

				return this->L_ch ? this->L_ch->eldest() : (this->R_ch ? this->R_ch->youngest() : *this );
			}
			
			void		delete_fixup(){

				if (Color not_eq BLACK) return;

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
RBT&	redemption() throw() {

			return this->L_ch ? this->L_ch->eldest() : *this;
		}


			void		_delete(RBT* criminal){


				if (not criminal) return ;

			RBT* victim = &criminal->redemption();

			if (this == victim and not R_ch) { 
			Empty = true; return;}


			std::swap (victim->Ship, criminal->Ship);

			RBT* ch = victim->L_ch ?  victim->L_ch :  victim->R_ch;

			if (ch and ch->Color == RED) ch->recolor();
			else victim->delete_fixup();

			/* replace link to victim by who yastahik, ma ya3arfo hta had*/
			{
				if (ch) ch->P = victim->P;
				if (victim->WhoIm() == JU)	victim->P->L_ch = ch;
				else if (victim->WhoIm() == SE) victim->P->R_ch = ch;
			}
			/* unlink the victim , mayaraf raso fin*/
			victim->L_ch = victim->R_ch = victim->P = NULL;

				delete victim; /* end of history */
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

	int count = 6365;


		for (size_t i = count; i ; --i)
			t.insert (i);
		for (size_t i = count; i ; --i){
			t.del (i);}
		for (size_t i = count; i ; --i)
			t.insert (i);
		for (size_t i = count; i ; --i)
			t.insert (i);
		for (size_t i = count; i ; --i)
			t.insert (i);
		
		try {
		for ( RBT<int> *o = &t.eldest(); ; o = &o->prev())
			std::cout << o->Ship << std::endl;
		}catch (const std::range_error& ) { }
		try {
		for ( RBT<int> *o = &t.youngest(); ; o = &o->next())
			std::cerr << o->Ship << std::endl;
		}catch (const std::range_error& ) { }
		// abort();

	return 0;
}

/*  c++ RBT.cpp -std=c++98 -Wall -Wextra -Werror -fsanitize=address  */