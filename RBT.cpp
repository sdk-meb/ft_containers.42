
# include<iostream>


# define	RED		1
# define	BLACK	0
# define	NIL		NULL
# define	SE		37/* SE_NIOR */
# define	JU		13/* JU_NIOR */
# define	ROOT	1337

template <class T_SHIP>
	struct RBT {

			RBT(T_SHIP ship): Ship(ship){

				/* case 0 */
				Color	= BLACK;
				P		= NIL;
				L_ch	= NIL;
				R_ch	= NIL;
				Dirty	= NIL;
			};
			RBT(RBT& tree){

				*this = tree;
			}

			bool	operator==(RBT& tree) const {

				if (this->Ship == tree.Ship)
					return true;
				return false;
			}
			RBT&	operator=(RBT& tree){

				this->Color = tree.Color;
				this->Ship	= tree.Ship;
				this->Dirty	= tree.Dirty;
				this->R_ch	= tree.R_ch;
				this->L_ch	= tree.L_ch;
				this->P		= tree.P;
				return *this;
			}

			void	swap(RBT& tr1, RBT& tr2){

				RBT tmp = tr1;
				tr1 = tr2;
				tr2 = tr1;
			}
			void	swap(RBT& tr1){
				
				swap(tr1, *this);
			}

			void	insert(T_SHIP ship) {

				insertion(ship, this);
			}

			~RBT(){

				try { delete this->R_ch; }
				catch(...){ }//std::cerr << "right 1\n";};
				try { delete this->L_ch; }
				catch(...){ }//std::cerr << "left 1\n";};
				try { delete this->Dirty; }
				catch(...){ }//std::cerr << "dirty 1\n";};
			}

		private :
			RBT(T_SHIP ship, RBT* parent): Ship(ship){

				Color	= RED;
				P		= parent;
				L_ch	= NIL;
				R_ch	= NIL;
				Dirty	= NIL;
				if (P->Color == RED)
					adjustment();
			};
			void	make_black(){

				Color = BLACK;
			}
			void	make_red(){

				Color = RED;
			}
			void	recolor(){

				if (Color == RED)
					Color = BLACK;
				else
					Color = RED;
			}


			short	WhoIm(const RBT* node=NIL) const {

				if (node == NIL)
					node = this;
				if (node->P == NIL)
					return ROOT;
				if (node->P->L_ch == node->P)
					return JU;
				return SE;
			}

			RBT&	get_S() const/* Sibling */{

				if (WhoIm() == ROOT)
					throw ;
				if (WhoIm() == JU)
					return *this->P->R_ch;
				//else if (WhoIm() == SE)
				return *this->P->L_ch;
			}
			RBT&	get_G() const/* GrandParent */{

				if (this->P == NIL)
					throw ;
				return *this->P->P;
			}
			RBT&	get_U() const/* Uncle */{

				if (WhoIm(this->P) == ROOT)
					throw ;
				if (WhoIm(this->P) == JU)
					return *this->P->P->R_ch;
				//else if (WhoIm(this->P) == SE)
				return *this->P->P->L_ch;
			}

			void	lr(RBT& subtree)/* left rotation */{

				RBT&	bita	= *subtree.R_ch->L_ch;
				RBT&	P		= *subtree.P;
				RBT&	y		= *subtree.R_ch;

				if (WhoIm(&subtree) == ROOT)
					return ; /* subtree well be the original instince */
				else if (WhoIm(&subtree) == SE)
					P.L_ch	= &y;
				else
					P.R_ch	= &y;
				subtree.R_ch	= &bita;
				y.L_ch			= &subtree;
				subtree.P		= &y;
			}
		
			void	adjustment(){

				lr(*this);
				// RBT& uncle = get_uncle();

			}
			void	insertion(T_SHIP ship, RBT* subtree)/* BST_i # binary search tree insertion # */{
			
				if (subtree == NIL)
					return ;
				if (ship < subtree->Ship){

					if (subtree->L_ch)
						subtree = subtree->L_ch;
					else { subtree->L_ch = new RBT(ship, subtree); return ;}
				}
				else if (ship > subtree->Ship){

					if (subtree->R_ch)
						subtree = subtree->R_ch;
					else { subtree->R_ch = new RBT(ship, subtree); return ;}
				}
				else
					throw "similar shipment not allow to store in the same red-black tree" ;
				return insertion(ship, subtree);
			}

			const T_SHIP	Ship;/* load */
			bool			Color;
			RBT*			P;
			RBT*			L_ch;/* left subtree, youngest son*/
			RBT*			R_ch;/* right subtree, eldest son*/
			RBT*			Dirty;/* when load find in tree his similar */
	};


int	main(){

	struct RBT<int> tree1(4);

	tree1.insert(3);
	tree1.insert(5);
	tree1.insert(2);

	return 0;
}
