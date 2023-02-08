/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:08:25 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/09 17:58:19 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#	define VECTOR_HPP

# include<memory>
# include<__split_buffer>

# include"iterator.hpp"
# include"utility.hpp"

namespace ft {


template <typename _T>
	void swap (_T& a, _T&b);

/*************************************************************************************************************
*	@category Sequence Containers
*	@brief	dynamic contiguous arrays
*	@param 	T value type
*	@param	Allocator 	typename allocation
*************************************************************************************************************/
template <class T, class Allocator = std::allocator<T> >
	struct vector {

			typedef Allocator									allocator_type;
			typedef typename allocator_type::value_type			value_type;

			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef ft::normal_iterator< pointer>				iterator;
			typedef ft::normal_iterator< const_pointer>			const_iterator;
			typedef ft::reverse_iterator< iterator>				reverse_iterator;
			typedef	ft::reverse_iterator< const_iterator>		const_reverse_iterator;

		private:

			/** @brief attribute of allocator */
			allocator_type	_Alloc ;
			/**
				@brief pointer to the first vector element
			*/
			pointer					_Frst ;
			/*
				@brief pointer to the last vector element,
					in case of empty vecot it is equal to @a _Frst
			*/
			pointer					_Last ;
			/** 
				@brief pointer to the next-last case alloceted capacity
					at that moment, no capacity so @a nullptr is here
			*/
			pointer					_End_Capacity ;

		public:

			/** 
				@category	Constructor
				@brief Default constracter that initialize the Allocator 
					with default @a template Allocator or other i case of argement find,
					and inisialize the _End_Capacity with nulptr.
				@param alloc allocator which the vector use it.
			*/
			explicit vector (const Allocator& alloc = allocator_type())
				: _Alloc(alloc) { _replace (NULL); }

			/**
				@category copy Counstructor
				@brief	Needless to define غني عن تعريف
				@param	other vector to copie from it
			*/
			vector (const vector& other)
				: _Alloc(other.get_allocator()) { _replace (NULL); *this = other; }

			/**
				@category	Constructor
				@brief		constructs the container with count copies of elements with giting value
				@param		count number of copies
				@param		value	value to constructs
				@param		giving allocator if find, else = default (optional)
			*/
			explicit vector (size_type count, const_reference value = value_type(),
								const Allocator& alloc = allocator_type())
			: _Alloc(alloc) {

				_replace (NULL);
				assign(count, value);
			}

			/**
				@category	Constructor
				@brief	constructs the container with range contents 
				@param	first iterator #input of range
				@param	end of range -> inputiterator
				@param	alloc	giving allocator if find, else = default => (optional)
			*/
			template < typename InputIt>
				vector (InputIt first, typename ft::enable_if < ft::__is_input_iter <
					typename InputIt::iterator_category>::value, InputIt>::type last,
					const Allocator& alloc = allocator_type())
						: _Alloc(alloc) {

						_replace (NULL);
						assign (first, last);
				}

			/**
				@brief assign the vector with new value of range
				@param	first	first iterator to the range
				@param	last	end of range
			*/
			template < class InputIt>
				void assign (InputIt first, typename ft::enable_if < ft::__is_input_iter <
					typename InputIt::iterator_category>::value, InputIt>::type last) {

					clear();
					difference_type	count 	= ft::distance (first, last);
					_logical_reserve(count);

					while (first not_eq last)
						_Alloc.construct(_Last++, *(first++));
				}

			/**
				@brief assign the vector with count of value 
				@param	count	number of copies
				@param	value	value indecate 
			*/
			void assign (size_type count, const_reference value) {

				clear();
				_logical_reserve(count);
				insert (begin(), count, value);
			}


			allocator_type	get_allocator() const { return _Alloc; }


		/* ********************   OPERATOR  ******************** */
			vector& operator= (const vector& other) {

				if (*this == other) return *this;

				assign(other.begin(), other.end());

				return *this;
			}

		/* *******************   __Capacity__    ******************* */
			size_type		size (void) const			{ return _Last - _Frst; }
			bool			empty (void) const			{ return size() ? false : true; }
			size_type		max_size (void) const		{ return _Alloc.max_size(); }
			void			reserve (size_type new_cap)	{

				if (capacity() == new_cap or new_cap < size()) return ;
				if (new_cap > max_size()) std::__throw_length_error ("vector");

				if (true) {

					vector del(*this, true);
					_replace (_Alloc.allocate (new_cap), size(), new_cap);
					move_range (del.begin(), del.end(), begin());
				}
			}

			size_type		capacity (void) const		{ return _End_Capacity - _Frst; }


		/* ********************** Modefier  ********************** */

			/**
				@brief clear fun, destroy all content of container and make it empty
				@attention that not have any access to memory de/allocation
			*/
			void	clear (){

				for (size_type lenght = 0; lenght < size(); lenght++)
					_Alloc.destroy(_Frst + lenght);
				if (capacity())
					_Last = _Frst;
			}

			/**
				@brief insert @ value befor position
				@param	pos position to put in
				@param value value to put it
			*/
			iterator	insert (iterator pos, const_reference value) {

				return insert (pos, 1, value);
			}

			/**
				@brief insert @ count number of value befor position
				@param	pos position to put in
				@param	count number of the value insertion
				@param value value to put it
			*/
			iterator  insert (iterator pos, size_type count, const_reference value) {

				difference_type _offset = ft::distance(pos, end());

				_logical_reserve (size() + count);

				if (_offset) move_range (end() - _offset, end(), (end() - _offset) + count);

				while (count--)
					_Alloc.construct((_Last++) -_offset, value);

				return end() - _offset - (_offset ? 1 : 0);
			}

			/**
				@brief insert befor position from first_iter to last_iter
				@param	pos position to put in start
				@param	first iterator to start from the adapter values
				@param	is the emd iterator present the range of adapters
			*/
			template <class InputIt>
				typename enable_if<__is_input_iter<typename InputIt::iterator_category>::value, iterator>::type 
				insert (iterator pos, InputIt first, InputIt last) {

	  				difference_type _offset = ft::distance (pos, end());
					difference_type count =	ft::distance (first, last);

					vector del(*this, true or false);
					vector __save(*this, false);
					try {
						const size_type ndl =  _logical_reserve (size() + count, false);
						if (ndl not_eq capacity()) _replace (NULL);
						else del._replace (NULL);
						_logical_reserve (ndl);
					}
					catch (const std::length_error& lerr) {

						del._replace (NULL);
						if (__save.capacity() not_eq capacity())
							vector del(*this, true or false);
						_replace (__save);
						__save._replace (NULL); throw lerr;
						
					}

					if (del.capacity()) {

						move_range (del.begin(), del.end() - _offset, begin()); /* size() = del.size() - _offset */
						if (_offset) move_range (del.end() - _offset, del.end(), begin() + (del.size() - _offset) + count);
						_replace (_Frst, del.size(), capacity());
					}
					else if (_offset) move_range (end() - _offset, end(), (end() - _offset) + count);

					try { while (first not_eq last) _Alloc.construct((_Last++) -_offset, *(first++)); }
					catch (const char* ss) {

						del._replace (NULL);
						if (__save.capacity() not_eq capacity())
							vector del(*this, true or false);
						_replace (__save);
						__save._replace (NULL); throw ss;
					}
					__save._replace (NULL);
					return end() - _offset;
				}


			iterator	erase (iterator pos) {

				_Alloc.destroy (pos.base());
				if (pos not_eq end()) move_range (pos + 1, end(), pos);
				if (capacity()) _Last -= 1;
				return pos;
			}

			iterator	erase (iterator first, iterator last) {

				iterator curs = last;			
				while (curs not_eq first) _Alloc.destroy((--curs).base());

				move_range (last, end(), first);

				if (capacity()) _Last -= ft::distance (first, last);
				return first;
			}

			void		push_back (const_reference value) { insert (end(), 1, value); }

			void		pop_back() {

				if (not empty())
					_Alloc.destroy(--_Last);
			}

			void		resize (size_type count, value_type value = value_type()) {

				if (count > size()) insert (end(), count - size(), value);
				else if (count < size()) erase (begin() + count, end());
			}

			void		swap (vector& other) {

				vector __swap(other, false);
				other._replace(_Frst, size(), capacity());
				_replace (__swap._Frst, __swap.size(), __swap.capacity());
				__swap._replace(NULL);
			}


		/* *******************  ITERATOR  ******************* */
			iterator		begin()			{ return iterator (_Frst); }
			const_iterator	begin() const	{  return const_iterator (_Frst); }

			iterator		end ()			{ return iterator (_Last); }
			const_iterator	end () const	{ return const_iterator (_Last); }

			reverse_iterator		rbegin()		{ return reverse_iterator (end()); }
			const_reverse_iterator	rbegin() const	{ return const_reverse_iterator (end()); }

			reverse_iterator		rend()			{ return reverse_iterator(begin()); }
			const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); }


		/* *******************  Element access ******************* */
			reference		operator[] (size_type idx)			{ return *(_Frst + idx);}
			const_reference	operator[] (size_type idx) const	{ return *(_Frst + idx);}

			reference		at (size_type idx)			{ out_range(idx); return (*this)[idx]; }
			const_reference	at (size_type idx) const	{ out_range(idx); return (*this)[idx]; }

			reference 		front()			{ return *_Frst; }
			const_reference	front() const	{ return *_Frst; }

			reference		back()			{ --_Last; return *_Last++; }
			const_reference	back() const	{ --_Last; return *_Last++; }

			pointer			data()			{ return _Frst; }
			const_pointer	data() const	{ return _Frst; }

		private :

		vector (const vector& other, bool)
			: _Alloc(other.get_allocator()) { _replace(other._Frst, other.size(), other.capacity()); }

		void	_del_capacity() {

			clear();
			if ( capacity() ) _Alloc.deallocate (_Frst, capacity());
			_replace (NULL);
		}

		void	_replace (pointer F, difference_type _size=0, difference_type _cap=0) {

			_Frst			= F;
			_Last			= _Frst + _size;
			_End_Capacity	= _Frst + _cap;
		}
		void	_replace (const vector& c) {

			this->_replace (c._Frst, c.size(), c.capacity());
		}

		/**
			@brief move range of contente form range address to start address.
			@attention most move it dongeer in overlapping case ! so here is a defined behiver 
			@param S ref to start range,
			@param L ref to end of range (last)
			@param to refere to the new start range
		*/
		template < class InputIt>
			typename enable_if <ft::__is_input_iter<typename InputIt::iterator_category>::value, void>::type
				move_range(InputIt S, InputIt L, InputIt to) {

					if (S == to) return ;
					if (to < S or L < to) {

						for (;S not_eq L; to++, S++)
							*(to.base()) = *S;
					}
					else {

						difference_type _offset1 = ft::distance (S, to);

						while (--L not_eq S)
							L[ _offset1] = *L;
						L[ _offset1] = *S;
					}
				}

			/**
				@brief throw exeption if indexe indec case outside vector size
				@param idx index
			*/
			void	out_range( size_type idx ) {

				if (idx >= size()) std::__throw_out_of_range( "vector");
			}

			size_type	_logical_reserve (size_type nedl, bool __set=true) {

				if (capacity() >= nedl) return capacity();
				if (nedl > max_size()) std::__throw_length_error ("vector");
				nedl =  std::min ( std::max (capacity() * 2, nedl), max_size());

				if (__set) {

					vector del(*this, true);
					_replace (_Alloc.allocate (nedl), size(), nedl);
					move_range (del.begin(), del.end(), begin());
				}
				return nedl;
			}

		public:
			~vector() { _del_capacity(); }
	};

template <typename _T>
	void swap (_T& a, _T&b) {
		
		_T c = a;
		a = b;
		b = c;
	}

template< class T, class Alloc >
	bool operator< (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {

		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

template< class T, class Alloc >
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {

		return not (lhs < rhs);
	}

template< class T, class Alloc >
	bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {

		return rhs < lhs;
	}
template< class T, class Alloc >
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {

		return not (rhs < lhs);
	}

template< class T, class Alloc >
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {

		return lhs < rhs or lhs > rhs;
	}

template< class T, class Alloc >
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {

		return not (lhs not_eq rhs);
	}




};

# endif

