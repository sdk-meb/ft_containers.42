
# include<iostream>
#include <cstdlib>


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

		private :
			RBT(const T_SHIP& ship, RBT& parent): Ship(ship){

				Color	= RED;
				P		= &parent;
				L_ch	= NIL;
				R_ch	= NIL;
				Dirty	= NIL;
			}
			RBT&	operator=(const RBT& tree)/*  half copy , inside */{

				Ship	= tree.Ship;
				Color	= tree.Color;
				return *this;
			}

			void	swap(RBT& subtree){

				RBT tmp = *this;
				*this = subtree;
				subtree = tmp;
			}

			void	recolor(){

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

				RBT*	y = this->R_ch;

				if (not(y))
					return ;
				swap(*R_ch);
				this->R_ch = this->R_ch->R_ch;
				if (this->R_ch)
					this->R_ch->P = this;
				y->R_ch = y->L_ch;

				y->L_ch = this->L_ch;
				if (this->L_ch)
					this->L_ch->P = y;

				y->P = this;
				this->L_ch = y;
			}
			void	rr()/* Rigth Rotation */{

				RBT*	x = this->L_ch;

				if (not(x))
					return ;
				swap(*L_ch);
				this->L_ch = this->L_ch->L_ch;
				if (this->L_ch)
					this->L_ch->P = this;
				x->L_ch = this->R_ch;
				if (this->R_ch)
					this->R_ch->P = x;
				x->R_ch = this->R_ch;
				if (x->R_ch)
					x->R_ch->P = x;

				x->P = this;
				this->R_ch = x;
			}

			void		adjustment(){

				if (P->Color == BLACK)
					return ;
				try {/* violate the properties of RBT */

					if (get_U().Color == BLACK)/* throw in case no uncle */
						throw "";

					{/* ( uncle is RED )*/ /* case 3.1 */

						// std::cout << "uncle red__\n";
						P->recolor();
						get_U().recolor();
						if (P->P->WhoIm() != ROOT)
							P->P->recolor();
						// std::cout << "uncle red\n";
					}
				}
				catch(...){

					if ((WhoIm() == SE && WhoIs(P) == SE)/* case 3.2.1 */
						|| (WhoIm() == JU && WhoIs(P) == JU)/* case 3.2.3 */){

						// std::cout << "seq___\n ";
						P->P->rr();
						try{ get_S().Color = RED;}
						catch(...){};
						P->Color = BLACK;
						// std::cout << "seq \n";
					}
					else if ((WhoIm() == JU && WhoIs(P) == SE)/* case 3.2.2 */
						|| (WhoIm() == SE && WhoIs(P) == JU)/* case 3.2.4 */){

						// std::cout << "op__\n ";
						P->lr();
						P->P->rr();/* case 3.2.1 */
						try{ get_S().Color = RED;}
						catch(...){};
						// std::cout << "op \n";
						P->Color = BLACK;
					}
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

			public:void	print_tree( RBT* tree)
			{
					if (not(tree))
						return ;

					if (tree->L_ch)
						print_tree(tree->L_ch);
					std::cout << tree->Ship << ' '\
					<< (tree->Color ? "R " : "B ");
					if (tree->R_ch){

						std::cout << std::endl;
						print_tree(tree->R_ch);
					}
			}
	};


int	main(){

	struct RBT<int> t(INT_MAX);
	try{

		size_t size_k = 8;
		int k[] = {INT_MAX, 3, 10, 7, 8, 9, -3, -6, -6, -6};
		for (size_t i = 1; i < size_k ; i++ )
			t.insert(k[i]);

		for (size_t i = 0; i < size_k; i++){

			struct RBT<int> * tptr = const_cast< RBT<int>*>(t.search(k[i]));
			std::cout << tptr << "[" << tptr->P << " P] ["<< tptr->L_ch << " L]" 
			<< " ["<< tptr->R_ch << " R] ->" << tptr->Ship << ' ' << (tptr->Color ? "R " : "B ") << std::endl;
		}

		// t.print_tree(&t);
		std::cout << std::endl;

	}	catch(const char *f){ std::cerr << f << std::endl ; };

	return 0;
}