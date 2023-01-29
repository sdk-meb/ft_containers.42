
# include"./rb_tree.hpp"
# include"./map_iterator.hpp"


namespace ft {


template <
    class _Key,
    class Compare = std::less<_Key>,
    class Allocator = std::allocator<_Key>
    > class set {


		public:
            typedef	_Key									key_type;
            typedef	key_type                           		value_type;

            typedef	typename Allocator::size_type				size_type;
            typedef	typename Allocator::difference_type			differance_type;

            typedef	Compare						key_compare;
            typedef	Compare						value_compare;
            typedef	Allocator					allocator_type;
    
            typedef	typename Allocator::reference               reference;
            typedef typename Allocator::const_reference			const_reference;
            typedef	typename Allocator::pointer	            pointer;
            typedef	typename Allocator::const_pointer		const_pointer;

		private:
				typedef	_RBtree <value_type, Allocator>			__tree_;

	/*********************************************************************************************************
	*	@brief	is a class  with hir income pointer of tree node
	*********************************************************************************************************/
				typedef	__IterTree <value_type, Allocator>			Itree;

		public:
	/*********************************************************************************************************
	*	@param	Itree tree iterator
	*********************************************************************************************************/
				typedef ft::map_iterator <Itree>			iterator;
				typedef	ft::map_iterator <const Itree>		const_iterator;

	/*********************************************************************************************************
	*	@param	iterator 
	*********************************************************************************************************/
				typedef	ft::reverse_iterator <iterator>			reverse_iterator;
				typedef	ft::reverse_iterator <const_iterator>	const_reverse_iterator;



        private :

            __tree_			tree;
            value_compare	_v_cmp ;
            allocator_type	_Alloc ;

        public:

            set&			operator= (const set& other) {

				tree .destroy();
				for (Itree it (other.tree.get_first().ItR); iterator(it) != end(); ++it)
					tree.insert(*it.ItR->Ship);

				_Alloc	= other.get_allocator();
				_v_cmp	= other._v_cmp;
				return *this;
			}



/***************************  @category	 __  Constuctors  __  ***********************************************/

			~set () { tree .destroy(); };
			set() : tree(__tree_()), _v_cmp(Compare()), _Alloc(Allocator()) { }

			explicit set (const Compare& comp, const Allocator& alloc = Allocator())
				: tree(__tree_()), _v_cmp(comp), _Alloc(alloc) { }

			template< class InputIt >
				set ( typename ft::enable_if < not
					__is_random_access_iter<typename InputIt::iterator_category>::value, InputIt>::type first,
					typename ft::enable_if <
					__is_input_iter<typename InputIt::iterator_category>::value, InputIt>::type last,
					const Compare& comp = Compare(), const Allocator& alloc = Allocator())
					: tree(__tree_()), _v_cmp(comp), _Alloc(alloc) { insert (first, last); }

			set (const set& other): _v_cmp(other._v_cmp) {

				*this = other;
			}

			allocator_type	get_allocator() const { return _Alloc; }

/***************************  @category	 __  Iterators  __  *************************************************/

			iterator			begin() 		{ return iterator 		(tree.get_first()); }
			const_iterator		begin() const	{ return const_iterator (tree.get_first()); }
			iterator			end()			{ return iterator		(tree.get_last()); }
			const_iterator		end() const		{ return const_iterator (tree.get_last()); }
			reverse_iterator		rbegin()		{ return reverse_iterator 		(end()); }
			const_reverse_iterator	rbegin() const	{ return const_reverse_iterator (end()); }
			reverse_iterator		rend()			{ return reverse_iterator 		(begin()); }
			const_reverse_iterator	rend() const	{ return onst_reverse_iterator	(begin()); }



/***************************  @category	 __  Capacity  __  **************************************************/

			bool		empty() const		{ return tree.empty(); }
			size_type	size() const		{ return tree.size(); }
			size_type	max_size() const	{ return _Alloc.max_size(); }





/***************************  @category	 __  Lookup  __  ****************************************************/
	
	/*********************************************************************************************************
	*	@brief		generally is a counter, but in set we have one unique key for ech element,
	*	@return			so it return implique the existence of key , 1 or 0 
	*	@param		key		key which checks the existence
	*********************************************************************************************************/
			size_type		count (const key_type& key) {

				try { tree.search(key, __EXCEPTIONS); }
				catch (...) { return false ; }

				return true;
			}

	/*********************************************************************************************************
	*	@brief		searching tree
	*	@return		(const) iterator	
	*	@param		key		key which checks the existence
	*********************************************************************************************************/
			iterator		find (const key_type& key) {

				typename __tree_::__base* tmp = tree.search(key);

				if (tmp) return iterator(Itree(*tmp));

				return end();
			}
			const_iterator	find (const key_type& key) const {

				typename __tree_::__base* tmp = tree.search(key);
	
				if (tmp) return const_iterator(Itree(*tmp));

				return end();
			}

	/*********************************************************************************************************
	*	@return	pair of iterator indecate the range of shipment  have same key
	*	@param	key
	*********************************************************************************************************/
			ft::pair<iterator,iterator>					equal_range (const key_type& key) {

				return ft::make_pair(lower_bound(key), upper_bound(key));
			}
			ft::pair<const_iterator,const_iterator>		equal_range (const key_type& key) const {

				return ft::make_pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key));
			}

	/*********************************************************************************************************
	*	@return	 as iterator shipment have the key or the first less than it, if not then end() return
	*	@param	key
	*********************************************************************************************************/	
			iterator	lower_bound (const key_type& key) {

				return iterator (tree.get_Root() << key);
			}
			const_iterator	lower_bound (const key_type& key) const {

				return const_iterator (tree.get_Root() << key);
			}

	/*********************************************************************************************************
	*	@return	as iterator shipment have the key or the first greater than it, if not then end() return
	*	@param	key
	*********************************************************************************************************/
			iterator		upper_bound (const key_type& key) {

				return iterator (tree.get_Root() >> key);
			}
			const_iterator	upper_bound (const key_type& key) const{

				return const_iterator (tree.get_Root() >> key);
			}





/***************************  @category	 __  Lookup  __  ****************************************************/

	/*********************************************************************************************************
	*	@return	 the function object that compares the keys
	*********************************************************************************************************/
			key_compare		key_comp() const { return value_compare(); }

	/*********************************************************************************************************
	*	@return	 the object of the functor @a value_compare
	*********************************************************************************************************/
			value_compare	value_comp() const { return _v_cmp; }




/***************************  @category	 __  Modifiers  __  *************************************************/

	/*********************************************************************************************************
	*	@brief remove all contents in the set
	*********************************************************************************************************/
			void	clear() { tree.destroy(); }

	/*********************************************************************************************************
	*	@brief	value type insertion
	*	@return	pait of iterator and true if and only if 
	*********************************************************************************************************/
		ft::pair<iterator, bool> insert (const value_type& value) {

			ft::pair<iterator, bool> tmpr;
			try { tmpr = ft::make_pair (
					iterator (Itree (tree.insert (value))), true); }
			catch (const std::overflow_error&) { tmpr = ft::make_pair (
					iterator (Itree(tree.search (value.first))), false); }

			return tmpr;
		}

	/*********************************************************************************************************
	*	@overload (2)
	*	@brief 		value type insertion in @a posistion
	*	@param		pos hint position
	*	@param		value	value to insert
	*********************************************************************************************************/
		iterator	insert (iterator pos, const value_type& value) {

			if (pos->first not_eq value.first)
				return insert (value).first;
			pos->second = value.second;
			return pos;
		}

	/*********************************************************************************************************
	*	@overload  (3) template
	*	@param		InputIt  template parameter sfinae in case of not input iterator
	*	@param		first_last	range [F, L] to insert it value 
	*********************************************************************************************************/
		template< class InputIt >
			typename ft::enable_if<__is_input_iter<typename InputIt::iterator_category>::value, void>::type	
			insert (InputIt first, InputIt last) {

				while (first not_eq last) insert(*(first++));
			}


	/*********************************************************************************************************
	*	@brief remove element inside range 
	*	@overload (2)
	*	@param key key of the shipment (pair)
	*********************************************************************************************************/
			size_type	erase (const key_type& key) { return tree.del(key); }

	/*********************************************************************************************************
	*	@brief remove element in position 
	*	@param pos iterator position
	*********************************************************************************************************/
			void	erase (iterator pos) { tree.del(pos.Super.ItR); }

	/*********************************************************************************************************
	*	@brief remove element inside range 
	*	@overload (1)
	*	@param first start iterator position
	*	@param last end of range as iterator
	*********************************************************************************************************/
			void		erase (iterator first, iterator last) {

				while (first not_eq last) erase (first++);
			}

	/*********************************************************************************************************
	*	@attention swwwwwwwwwwap
	*********************************************************************************************************/		
			void		swap (set& other) {

				std::swap (_v_cmp, other._v_cmp);
				tree.swap (other.tree);
				std::swap (_Alloc, other._Alloc);
			}


    };

}