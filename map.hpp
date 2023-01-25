/** ************************************************************************** **/
/**                                                                            **/
/**                                                        :::      ::::::::   **/
/**   map.hpp                                            :+:      :+:    :+:   **/
/**                                                    +:+ +:+         +:+     **/
/**   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        **/
/**                                                +#+#+#+#+#+   +#+           **/
/**   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             **/
/**   Updated: 2023/01/12 13:05:55 by mes-sadk         ###   ########.fr       **/
/**                                                                            **/
/** ************************************************************************** **/

#ifndef	MAP_HPP
# define MAP_HPP

# include<functional>
# include<memory>
# include<algorithm>
# include<cstddef>

# include"rb_tree.hpp"
# include"map_iterator.hpp"
# include"utility.hpp"


namespace	ft {

/*************************************************************************************************************
*	@category Associative containers
*	@brief	collection of key-value pairs, storted by keys, evrey key should unique
*	@param	key	indicator
*	@param 	T value type
*	@param	Compare  relational operator or function to use it as comparison method (less = default)
*	@param	Allocator 	typename allocation
*************************************************************************************************************/
template	< 
			class __key, class _T,
			class Compare = std::less <__key>,
			class Allocator = std::allocator <ft::pair <const __key, _T> >
			>
	class map {


		public:
				typedef	__key									key_type;
				typedef	_T										mapped_type;
				typedef	ft::pair<const key_type, mapped_type>		value_type;

				typedef	typename Allocator::size_type				size_type;
				typedef	typename Allocator::difference_type			differance_type;

				typedef	Compare						key_compare;
				typedef	Allocator					allocator_type;
		
				typedef	value_type&						  	  reference;
				typedef	const value_type&				const_reference;
				typedef	typename Allocator::pointer					  pointer;
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
				typedef	ft::reverse_map_iterator <iterator>			reverse_iterator;
				typedef	ft::reverse_map_iterator <const_iterator>	const_reverse_iterator;


/***************************  @category	 __  Iterator Member Types __  **************************************/




	/*********************************************************************************************************
	*	@note	[functor] that compar the first components of the pairs (in map, the key of @a value_type)
	*	@param	key_compare that take in costruction
	*********************************************************************************************************/
				class	value_compare {

					friend class map;
					protected:
						key_compare comp;
					
						value_compare(key_compare c): comp(c) { }

					public:
						bool	operator() (const value_type& lhs, const value_type& rhs) {

							return comp(lhs.first, rhs.first);
						}
				};



/***************************  @category	 __  Constuctors  __  ***********************************************/

			map() : tree(__tree_()), _v_cmp(Compare()), _Alloc(Allocator()) { }

			explicit map (const Compare& comp, const Allocator& alloc = Allocator())
				: tree(__tree_()), _v_cmp(comp), _Alloc(alloc) { }

			template< class InputIt >
				map (InputIt first,
					typename ft::enable_if <
					__is_input_iter<typename InputIt::iterator_category>::value, InputIt>::type last,
					const Compare& comp = Compare(), const Allocator& alloc = Allocator())
					: tree(__tree_()), _v_cmp(comp), _Alloc(alloc) { insert (first, last); }

			map (const map& other): _v_cmp(other._v_cmp) {

				tree	= other.tree;
				_v_cmp	= other._v_cmp;
				_Alloc	= other._Alloc;
			}

			map&			operator= (const map& other) {

				tree	= other.tree;
				_Alloc	= other.get_allocator();
				_v_cmp	= other._v_cmp;
				return *this;
			}

			allocator_type	get_allocator() const { return _Alloc; }


/***************************  @category	 __  Element access  __  ********************************************/

	/*********************************************************************************************************
	*	@brief get mapped value by key scershing
	*	@exception out_of_range
	*	@param	key
	*********************************************************************************************************/
			mapped_type&			at (const key_type& key)		{ return tree.search(key, __EXCEPTIONS); }
			const mapped_type&		at (const key_type& key) const	{ return tree.search(key, __EXCEPTIONS); }
	
	/*********************************************************************************************************
	*	@brief	get mapped value by key scershing, ifnot endefined behavier
	*	@param	key
	*********************************************************************************************************/
			mapped_type&	operator[] (const key_type& key)   { return tree.search (key, not(__EXCEPTIONS)); }



/***************************  @category	 __  Capacity  __  **************************************************/

			bool		empty() const		{ return tree.empty(); }
			size_type	size() const		{ return tree.size(); }
			size_type	max_size() const	{ return _Alloc.max_size(); }




/***************************  @category	 __  Modifiers  __  *************************************************/

	/*********************************************************************************************************
	*	@brief	value type insertion
	*	@return	pait of iterator and true if and only if 
	*********************************************************************************************************/
		ft::pair<iterator, bool> insert (const value_type& value) {

				ft::pair<iterator, bool> tmpr;
				try { tmpr = ft::make_pair (
						iterator (Itree (tree.insert (const_cast<value_type&>(value)))), true); }
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

			if (pos->first != value.first) 
				return insert (value).first;
			pos->second = value.second;
			return pos;
		}

	/*********************************************************************************************************
	*	@overload (3) template
	*	@param		InputIt  template parameter sfinae in case of not input iterator
	*	@param		first_last	range [F, L] to insert it value 
	*********************************************************************************************************/
		template< class InputIt >
			typename ft::enable_if<__is_input_iter<typename InputIt::iterator_category>::value, void>::type	
			insert (InputIt first, InputIt last) {

				while (first not_eq last) {

					insert(*first);
					++first;
				}
			}


	/*********************************************************************************************************
	*	@brief remove all contents in the map
	*********************************************************************************************************/
			void	clear() { tree.destroy(); }
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

				iterator del;
				while (first not_eq last) {

					del = first++;
					erase(del);
				}
			}

	/*********************************************************************************************************
	*	@attention swwwwwwwwwwap
	*********************************************************************************************************/		
			void		swap (map& other) {

				std::swap (_v_cmp, other._v_cmp);
				std::swap (tree, other.tree);
				std::swap (_Alloc, other._Alloc);
			}


/***************************  @category	 __  Iterators  __  *************************************************/

			iterator			begin() 		{ return iterator 		(tree.get_first()); }
			const_iterator		begin() const	{ return const_iterator (tree.get_first()); }
			iterator			end()			{ return iterator		(tree.get_last()); }
			const_iterator		end() const		{ return const_iterator (tree.get_last()); }
			reverse_iterator		rbegin()		{ return reverse_iterator 		(end()); }
			const_reverse_iterator	rbegin() const	{ return const_reverse_iterator (end()); }
			reverse_iterator		rend()			{ return reverse_iterator 		(begin()); }
			const_reverse_iterator	rend() const	{ return onst_reverse_iterator	(begin()); }




/***************************  @category	 __  Lookup  __  ****************************************************/
	
	/*********************************************************************************************************
	*	@brief		generally is a counter, but in map we have one unique key for ech element,
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

				return iterator (tree.get_first() << key);
			}

	/*********************************************************************************************************
	*	@return	as iterator shipment have the key or the first greater than it, if not then end() return
	*	@param	key
	*********************************************************************************************************/
			iterator	upper_bound (const key_type& key) {

				return iterator (tree.get_first() >> key);
			}



/***************************  @category	 __  Lookup  __  ****************************************************/

	/*********************************************************************************************************
	*	@return	 the function object that compares the keys
	*********************************************************************************************************/
			key_compare		key_comp() { return _v_cmp.comp; }

	/*********************************************************************************************************
	*	@return	 the object of the functor @a value_compare
	*********************************************************************************************************/
			value_compare	value_comp() {return _v_cmp; }


			private :

				__tree_			tree;
				value_compare	_v_cmp ;
				allocator_type	_Alloc ;

		};


template <class key, class T, class Comp, class Alloc>
	bool operator== (const ft::map<key, T, Comp, Alloc>& lhs, const ft::map<key, T, Comp, Alloc>& rhs) {

		return not (lhs not_eq rhs);
	}
template <class key, class T, class Comp, class Alloc>
	bool operator!= (const ft::map<key, T, Comp, Alloc>& lhs, const ft::map<key, T, Comp, Alloc>& rhs) {

		return (lhs.size() not_eq rhs.size()) or (not ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

template <class key, class T, class Comp, class Alloc>
	bool operator< (const ft::map<key, T, Comp, Alloc>& lhs, const ft::map<key, T, Comp, Alloc>& rhs) {

		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
template <class key, class T, class Comp, class Alloc>
	bool operator>= (const ft::map<key, T, Comp, Alloc>& lhs, const ft::map<key, T, Comp, Alloc>& rhs) {

		return not (lhs < rhs);
	}

template <class key, class T, class Comp, class Alloc>
	bool operator> (const ft::map<key, T, Comp, Alloc>& lhs, const ft::map<key, T, Comp, Alloc>& rhs) {

		return rhs < lhs;
	}
template <class key, class T, class Comp, class Alloc>
	bool operator<= (const ft::map<key, T, Comp, Alloc>& lhs, const ft::map<key, T, Comp, Alloc>& rhs) {

		return not (rhs < lhs);
	}



}
	

# endif
