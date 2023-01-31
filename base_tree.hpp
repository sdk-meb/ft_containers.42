
#ifndef __BASE_TREE_HPP
# define __BASE_TREE_HPP


# include"utility.hpp"

template < class Container >
    class ___abase {

        typedef 	typename Container::allocator_type		Allocator;
        typedef 	typename Container::size_type			size_type;
        typedef const typename Container::key_type			key_type;

        typedef 	typename Container::key_compare			key_compare;

        typedef		__road_<typename Container::value_type, Allocator>				__road;

        typedef typename Allocator::template rebind<__road>::other	SAllocator;

		protected:
			const key_compare&		k_comp;
			Allocator			_Alloc;
			size_type			Size;
			__road*				seed;
			SAllocator			_SAlloc;
        
    /*********************************************************************************************************
	*	@brief	binary tree searching, NIL in case of non existence
	*	@param	key	 searching indicator 
	*	@param	sub	indicator for start recursion place
	*********************************************************************************************************/
		__road*		searching(key_type& key, __road* sub) const throw() {

			if (not(sub))
				return NIL;

			if (t_comp (key, *sub->Ship, this->k_comp))
					sub = sub->L_ch;
			else if (t_comp (*sub->Ship, key, this->k_comp))
					sub = sub->R_ch;
			else
				return  sub;
			return searching(key, sub);
		}

		public:
/***************************  @category	 __  constructor  __  ***********************************************/

		___abase (const key_compare& cmp, Allocator alloc = Allocator())
			: k_comp(cmp), _Alloc (alloc), Size(0), seed(NIL), _SAlloc(SAllocator()) { }
        
		~___abase() {

			if (seed) {

				_SAlloc.destroy(seed);
				_SAlloc.deallocate (seed, 1);
			}
		}
    };


# endif