
# include<istream>
#include"Red-Black_tree.hpp"

int	main(){

	struct RBT<int> t;
	try{

		size_t size_k = 19;
		
		int k0[] = {16, -6, -17, 7, 8, 9, -3, 3, -63, -9, -8, -29, -5, 13, 12, 2, -4, 20, -2};
		int k1[] = {160, -60, -100, 70, 80, 90, -30, 30, -630, -90, -80, -290, -50, 130, 120, 230, -40, 200, -20};
		int k2[] = {161, -61, -101, 71, 81, 91, -31, 31, -631, -91, -81, -291, -51, 131, 121, 231, -41, 201, -28};
		int k3[] = {167, -67, -107, 77, 87, 97, -37, 37, -637, -97, -87, -297, -57, 137, 127, 237, -47, 207, 50};
	
		for (size_t i = 0; i < size_k ; i++)
			t.insert(k0[i]);
		for (size_t i = 0; i < size_k ; i++)
			t.del(k0[i]);

		for (size_t i = 0; i < size_k ; i++)
			t.del(k3[i]);

		for (size_t i = 0; i < size_k ; i++)
			{t.insert(k0[i]);t.insert(k1[i]);}
		for (size_t i = 0; i < size_k ; i++)
			t.del(k1[i]);

		for (size_t i = 0; i < size_k ; i++)
			{t.insert(k2[i]);t.insert(k3[i]);t.del(k0[i]);t.insert(k0[i]);}
	
		for (size_t i = 0; i < size_k ; i++)
			{t.del(k2[i]);t.del(k3[i]);t.del(k0[i]);t.del(k1[i]);}

		for (size_t i = 0; i < size_k ; i++)
			{t.insert(k2[i]);t.insert(k3[i]);t.insert(k0[i]);t.insert(k1[i]);}
		
		for (size_t i = 0; i < size_k ; i++)
			{t.del(k3[i]);t.del(k2[i]);t.del(k0[i]);t.del(k1[i]);}

		for (size_t i = 0; i < size_k ; i++){

			t.insert(k2[i]);;t.insert(k1[i]);
			t.del(k2[i]);
			t.insert(k3[i]);t.insert(k0[i]);
			t.del(k0[i]);
			
			t.insert(k2[i]);
		}
		for (size_t i = 0; i < size_k ; i++)
			t.insert(k0[i]);

	
		for (size_t i = 0; i < size_k; i++){

			struct RBT<int> * tptr = const_cast< RBT<int>*>(t.search(k0[i]));
			if (not(tptr))
				continue;
			std::cout	<< "["
						<< (tptr->P ? tptr->P->Ship : 0)		<< " P] ["
						<< (tptr->L_ch ? tptr->L_ch->Ship : 0)	<< " L] ["
						<< (tptr->R_ch ? tptr->R_ch->Ship : 0)	<< " R] ("
						<< tptr->Ship << ") " << (tptr->Color ? "R " : "B ")
						<< std::endl;
		}
		for (size_t i = 0; i < size_k; i++){

			struct RBT<int> * tptr = const_cast< RBT<int>*>(t.search(k1[i]));
			if (not(tptr))
				continue;
			std::cout	<< "["
						<< (tptr->P ? tptr->P->Ship : 0)		<< " P] ["
						<< (tptr->L_ch ? tptr->L_ch->Ship : 0)	<< " L] ["
						<< (tptr->R_ch ? tptr->R_ch->Ship : 0)	<< " R] ("
						<< tptr->Ship << ") " << (tptr->Color ? "R " : "B ")
						<< std::endl;
		}
		for (size_t i = 0; i < size_k; i++){

			struct RBT<int> * tptr = const_cast< RBT<int>*>(t.search(k2[i]));
			if (not(tptr))
				continue;
			std::cout	<< "["
						<< (tptr->P ? tptr->P->Ship : 0)		<< " P] ["
						<< (tptr->L_ch ? tptr->L_ch->Ship : 0)	<< " L] ["
						<< (tptr->R_ch ? tptr->R_ch->Ship : 0)	<< " R] ("
						<< tptr->Ship << ") " << (tptr->Color ? "R " : "B ")
						<< std::endl;
		}
		for (size_t i = 0; i < size_k; i++){

			struct RBT<int> * tptr = const_cast< RBT<int>*>(t.search(k3[i]));
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

	}	catch(const char *i){ std::cerr << i << std::endl ; };

	return 0;
}

/*  c++ RBT.cpp -std=c++98 -Wall -Wextra -Werror -fsanitize=address  */