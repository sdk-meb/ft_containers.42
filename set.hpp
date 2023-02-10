/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:18:15 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/10 17:34:41 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP 

# include"./map_iterator.hpp"
# include"./ab__tree.hpp"

namespace ft {

/*************************************************************************************************************
*	@category Associative containers
*	@brief	 key-value storted by itself (key), evrey key should unique
*	@param	key	indicator  eq value type
*	@param	Compare  relational operator or function to use it as comparison method (less = default)
*	@param	Allocator 	typename allocation
*************************************************************************************************************/
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
				typedef	__tree_ <set, value_type>					_tree;

	/*********************************************************************************************************
	*	@brief	is a class  with hir income pointer of tree node
	*********************************************************************************************************/
				typedef	typename _tree::IterTree		Itree;

		public:
	/*********************************************************************************************************
	*	@param	Itree tree iterator
	*********************************************************************************************************/
				typedef ft::map_iterator <Itree>			iterator;
				typedef	ft::const_map_iterator <Itree>		const_iterator;

	/*********************************************************************************************************
	*	@param	iterator 
	*********************************************************************************************************/
				typedef	ft::reverse_iterator <iterator>			reverse_iterator;
				typedef	ft::reverse_iterator <const_iterator>	const_reverse_iterator;



        private :

            value_compare	_v_cmp ;
            allocator_type	_Alloc ;
            _tree			tree;

        public:

            set&			operator= (const set& other) {

				if (this == &other) return *this;

				tree .destroy();

				if (other.size())
					tree	= const_cast<set&> (other).tree;

				return *this;
			}



/***************************  @category	 __  Constuctors  __  ***********************************************/

			~set () { tree .destroy(); };
			set() : _v_cmp(Compare()), _Alloc(Allocator()), tree(_v_cmp, _Alloc) { }

			explicit set (const Compare& comp, const Allocator& alloc = Allocator())
				: _v_cmp(comp), _Alloc(alloc), tree(_v_cmp, _Alloc) { }

			template< class InputIt >
				set ( InputIt first, InputIt last,
					const Compare& comp = Compare(), const Allocator& alloc = Allocator())
					: _v_cmp(comp), _Alloc(alloc), tree(_v_cmp, _Alloc) { insert (first, last); }

			set (const set& other): _v_cmp(other._v_cmp), _Alloc(other._Alloc), tree(_v_cmp, _Alloc)
				{ *this = other; }

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

				return tree.search(key) ? true : false ;
			}

	/*********************************************************************************************************
	*	@brief		searching tree
	*	@return		(const) iterator	
	*	@param		key		key which checks the existence
	*********************************************************************************************************/
			iterator		find (const key_type& key) {

				typename _tree::__road* tmp = tree.search(key);

				return tmp ? iterator(Itree(*tmp, _v_cmp)) : end();
			}
			const_iterator	find (const key_type& key) const {

				typename _tree::__road* tmp = tree.search(key);
	
				return tmp ? const_iterator(Itree(*tmp, _v_cmp)) : end();
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
					iterator (Itree (&tree.insert (value), _v_cmp)), true); }
			catch (const std::overflow_error&) { tmpr = ft::make_pair (
					iterator (Itree(tree.search (value), _v_cmp)), false); }

			return tmpr;
		}

	/*********************************************************************************************************
	*	@overload (2)
	*	@brief 		value type insertion in @a posistion
	*	@param		pos hint position
	*	@param		value	value to insert
	*********************************************************************************************************/
		iterator	insert (iterator pos, const value_type& value) {

			if (*pos not_eq value)
				return insert (value).first;
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

	friend bool	operator!= (const set& lhs, const set& rhs)	{
		
			return lhs.size() not_eq rhs.size() or not ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend bool	operator< (const set& lhs, const set& rhs) {
	
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	friend bool	operator> (const set& lhs, const set& rhs) {
	
			return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

};



}

# endif
