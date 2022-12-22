
# include<iostream>
#include <cstdlib>
# include<climits>


# define	RED		1
# define	BLACK	0
# define	NIL		NULL
# define	SE		37/* SE_NIOR */
# define	JU		13/* JU_NIOR */
# define	ROOT	1337
# define	NOTHING	33

template <class T_SHIP>
	struct RBT {

		// private:
				T_SHIP			Ship;/* load */
				bool			Color;
				RBT*			P;/* root of subtree(parent), NIL if node has root*/
				RBT*			L_ch;/* left subtree, youngest son*/
				RBT*			R_ch;/* right subtree, eldest son*/
				RBT*			Dirty;/* when load find in tree his similar */

		public:
			RBT(const T_SHIP& ship): Ship(ship){

				/* case 0 */
				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Dirty	= NIL;
			};
			RBT(const RBT& tree){

				/* the copy assignment constructor here is dangerous, because the 
					destroying of an object have a role in killing all his child */
				Color	= tree.Color;
				Ship	= tree.Ship;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Dirty	= NIL;
			}

			bool	operator==(RBT& tree) const {

				if (Ship == tree.Ship)
					return true;
				return false;
			}
			bool	operator>(RBT& tree) const {

				if (Ship > tree.Ship)
					return true;
				return false;
			}
			bool	operator<(RBT& tree) const {

				if (Ship < tree.Ship)
					return true;
				return false;
			}

			void		insert(const T_SHIP& ship) {

				insertion(ship, this);
			}
			const RBT*	search(T_SHIP ship) const/* BST # binary search tree sherching # */{

				/* ????????????   return pointer must be much be dangerous */
				return searching(ship, const_cast<RBT*> (this));
			}
			~RBT(){
				try { delete R_ch; }
				catch(...){ }//std::cerr << "right 1\n";};
				try { delete L_ch; }
				catch(...){ }//std::cerr << "left 1\n";};
				try { delete Dirty; }
				catch(...){ }//std::cerr << "dirty 1\n";};
			}

		// private :
			RBT(const T_SHIP& ship, RBT& parent): Ship(ship){

				Color	= RED;
				P		= &parent;
				L_ch	= NIL;
				R_ch	= NIL;
				Dirty	= NIL;
			}
			RBT&	operator=(const RBT& tree)/*  half copy , inside */{

				Ship	= tree.Ship;
				if (WhoIm() != ROOT)
					Color	= tree.Color;
				return *this;
			}

			void	swap(RBT& subtree){

				RBT tmp = *this;
				*this = subtree;
				subtree = tmp;
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
					throw "";
				
				if (WhoIm() == JU)
					return *P->R_ch;
				//else if (WhoIm() == SE)
				return *P->L_ch;
			}
			RBT&	get_G() const/* GrandParent */{

				if (P == NIL || P->P == NIL)
					throw "";
				return *P->P;
			}
			RBT&	get_U() const/* Uncle */{

				if (WhoIs(P) == ROOT || WhoIs(P) == NOTHING)
					throw "";
				if (P->P->R_ch == NIL || P->P->L_ch == NIL)/* no Uncle */
					throw "";
				if (WhoIs(P) == JU)
					return *P->P->R_ch;
				//else if (WhoIs(P) == SE)
				return *P->P->L_ch;
			}

			void	lr()/* Left Rotation */ {

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
			void	rr()/* Rigth Rotation */{

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
	};

int	main(){

	struct RBT<int> t(__INT_MAX__);
	try{

		size_t size_k = 12;
		int k[] = {__INT_MAX__, -6, -10, 7, 8, 9, -3, 3, -63, -9, -8, -29,};
		for (size_t i = 1; i < size_k ; i++)
			t.insert(k[i]);
		
		for (size_t i = 0; i <= size_k; i++){

			struct RBT<int> * tptr = const_cast< RBT<int>*>(t.search(k[i]));
			if (not(tptr))
				continue;
			std::cout	<< "["
						<< (tptr->P ? tptr->P->Ship : 0)		<< " P] ["
						<< (tptr->L_ch ? tptr->L_ch->Ship : 0)	<< " L] ["
						<< (tptr->R_ch ? tptr->R_ch->Ship : 0)	<< " R] ("
						<< tptr->Ship << ") " << (tptr->Color ? "R " : "B ")
						<< std::endl;
		}

		std::cout << std::endl;

	}	catch(const char *f){ std::cerr << f << std::endl ; };

	return 0;
}

/*  c++ RBT.cpp -std=c++98 -Wall -Wextra -Werror -fsanitize=address  */