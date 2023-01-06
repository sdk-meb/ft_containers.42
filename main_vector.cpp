



#include <iostream>

# include"vector.hpp"
#include <vector>


// # define FT

#ifdef FT 
   using namespace ft;
#else
   using namespace std;
#endif

int main( )
{
   std::vector <int> v2;
   ft::vector <int> v3;


   v3.push_back(10);
   v3.push_back(20);
   v3.push_back(30);
   v3.push_back(40);
   v3.push_back(50);


   v2.push_back(20);
   v2.push_back(30);
   v2.push_back(40);
   v2.push_back(50);

   v2.insert(v2.end() , 99);
   v3.insert(v3.end() , 99);

   v2.insert(v2.end() ,v2.begin(), v2.end() -1);

   v3.insert(v3.end() ,v3.begin(), v3.end() -1);

   ft::vector<int>::iterator iter3 = v3.end() -= 1;
   std::vector<int>::iterator iter2 = v2.end() -= 1;

   std::cout <<  *iter3.base() << std::endl;
   std::cout <<  *iter2.base() << std::endl;


}

