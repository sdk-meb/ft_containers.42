
# include<iostream>


# define	RED		1
# define	BLACK	0
# define	NIL		NULL
# define	SE		37/* SE_NIOR */
# define	JU		13/* JU_NIOR */
# define	ROOT	1337
# define	NOTHING	33

template <class T_SHIP>
	struct RBT {
	
		private:
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

				std::cout << "CAC\n";
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
				std::cout << "destroy\n";
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
			RBT&	operator=(RBT& tree)/*  half copy , inside */{

				std::cout << "CAO\n";
				Ship	= tree.Ship;
				Color	= tree.Color;
				P		= tree.P;
				L_ch	= tree.L_ch;
				R_ch	= tree.R_ch;
				Dirty	= tree.Dirty;
				return *this;
			}

			void	swap(RBT& tree)/* global copy , inside/outside */{

				std::cout << "SWAP\n";
				if (WhoIm() == JU)
					P->L_ch = &tree;
				else if (WhoIm() == SE)
					P->R_ch = &tree;
				if (tree.WhoIm() == JU)
					tree.P->L_ch = this;
				else if (tree.WhoIm() == SE)
					tree.P->R_ch = this;

				if (R_ch)
					R_ch->P = &tree;
				if (tree.R_ch)
					tree.R_ch->P = this;

				if (L_ch)
					L_ch->P = &tree;
				if (tree.L_ch)
					tree.L_ch->P = this;

				RBT& tmp = tree;
				tree = *this;
				*this = tmp;
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

				if (WhoIm() == ROOT)
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

				if (not(R_ch && R_ch->L_ch))
					throw "_____lr ???____";
				RBT&	_y	= *R_ch;
				RBT&	ß	= *_y.L_ch;

				{/* ß <⤶ _y to x ⤷> ß  */
					R_ch	= &ß;
					ß.P 	= this;
				}	

				{/*  p ⥮ x to p ⥮ _y */
					_y.P = P;
					if (WhoIm() == ROOT)
						swap(_y);			
					else if (WhoIm() == SE)
						P->R_ch	= &_y;
					else
						P->L_ch	= &_y;
				}

				{/* x ⤷> _y to x <⤶ _y */
					_y.L_ch	= this;
					P		= &_y;
				}
			}
			void	rr()/* Rigth Rotation */{

				if (not(L_ch && L_ch->R_ch))
					throw "_____rr ???____";
				RBT&	_x	= *L_ch;
				RBT&	ß	= *_x.R_ch;

				{/* _x ⤷> ß to ß <⤶ this  */
					L_ch	= &ß;
					ß.P 	= this;
				}

				{/*  p ⥮ this to p ⥮ _x */
					_x.P = P;
					if (WhoIm() == ROOT)
						swap(_x);
					else if (WhoIm() == SE)
						P->R_ch	= &_x;
					else if (WhoIm() == JU)
						P->L_ch	= &_x;
					else
						exit(NOTHING);
				}
				
				{/* _x <⤶ this to _x ⤷> this */
					_x.R_ch	= this;
					P		= &_x;
				}
			}

			void		adjustment(){

				if (P->Color == BLACK)
					return ;
				try {/* violate the properties of RBT */

					if (get_U().Color == BLACK)/* throw in case no uncle */
						throw "";

					{/* ( uncle is RED )*/ /* case 3.1 */

						P->recolor();
						get_U().recolor();
						if (P->P->WhoIm() != ROOT)
							P->P->recolor();
					}
				}
				catch(...){

					if ((WhoIm() == SE && WhoIs(P) == SE)/* case 3.2.1 */
						|| (WhoIm() == JU && WhoIs(P) == JU)/* case 3.2.3 */){

					std::cout << "here seq "<< P->P->Ship <<" \n";
						P->P->rr();
						get_S().Color = RED;
						P->Color = BLACK;
					}
					else if ((WhoIm() == JU && WhoIs(P) == SE)/* case 3.2.2 */
						|| (WhoIm() == SE && WhoIs(P) == JU)/* case 3.2.4 */){

					std::cout << "here opps \n";
						P->lr();
						P->P->rr();/* case 3.2.1 */
						get_S().Color = RED;
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

			public:void	print_tree( RBT& tree)
			{
					std::cout << tree.Ship << ' '\
					<< (tree.Color ? "R " : "B ");

					if (tree.L_ch)
						print_tree(*tree.L_ch);
					if (tree.R_ch){

						std::cout << std::endl;
						print_tree(*tree.R_ch);
					}
			}
	};


int	main(){

	struct RBT<int> tree1(7);
	try{

		tree1.insert(3);
		tree1.insert(1);
		tree1.print_tree(tree1);

	}
	catch(const char *f){ std::cerr << f << std::endl ; };
	return 0;
}

