/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:08:25 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/06 12:10:39 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	@brief dynamic contiguous array
*/
#ifndef VECTOR_HPP
#	define VECTOR_HPP

# include<unistd.h>

# include<memory>
# include"iterator.hpp"
# include<iterator>
# include<algorithm>
# include<cstdlib>

# include"utility.hpp"

namespace ft {

	template <typename T>
		void swap (T& a, T& b) {

			T c = a;
			a = b;
			b = c;
		}

	/*
		@brief dynamic contiguous arrays, encapsulated by sequence container
	*/
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

				typedef ft::iterator<pointer>				iterator;
				typedef ft::iterator<const_pointer>			const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			private:

				/* @brief attribute of allocator */
				allocator_type	_Alloc ;
				/*
					@brief pointer to the first vector element
					indefine if the vector was not initialized
				*/
				pointer					_Frst ;
				/*
					@brief pointer to the last vector element,
					in case of empty vecot it is equal to @a _Frst
				*/
				pointer					_Last ;
				/* 
					@brief pointer to the last case alloceted capacity
					at that moment, no capacity so @a nullptr is here
				*/
				pointer					_End_Capacity ;

			public:

				/* 
					@category constracter.
					@brief Default constracter that initialize the Allocator 
					with default @a template Allocator or other i case of argement find,
					and inisialize the _End_Capacity with nulptr.
					@param alloc allocator which the vector use it.
				*/
				explicit vector ( const Allocator& alloc = allocator_type() ): _Alloc(alloc){

					_End_Capacity = 0;
				}
				// vector( const vector& other ): _Alloc(other._Alloc){

				// 	_Frst	= other._Frst;
				// 	_End	= other._Last;

				// 	_End_Capacity = std::nullptr_t();
				// };

				// explicit vector ( size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator())
				// : _Alloc(alloc) {

				// 	_Frst = _Alloc.allocate(count, _Frst);
				// 	_Last = _Frst + count * sizeof(pointer);
				// 	_End_Capacity = _Last;
				// 	fill(_Frst, _End, value);
				// };
				// // template <class InputIt>
				// // 	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator()){ };

				// template< class InputIt >
				// 	void assign( InputIt first, InputIt last ) {

				// 		pointer old_start	= _Frst;
				// 		pointer old_end		= _Last;
				// 		_Frst	= &first;
				// 		_End	= &last;
				// 		try {

				// 			out_capacity(first - last);
				// 			if ((size_type) (first - last) * 2 > max_size())
				// 				this->reserve(max_size());
				// 			else
				// 				this->reserve((first - last) * 2);
				// 		}
				// 		catch (const std::exception& exc) {


							

				// 			_Frst	= old_start;
				// 			_End	= old_Last;
				// 			throw exc;
				// 		}
				// };
				// void assign( size_type count, const T& value ){

				// 	erase();
				// 	this->reserve(count);
				// };
				allocator_type	get_allocator() const { return _Alloc; };
			/* ********************   OPERATOR  ******************** */
				vector& operator=( const vector& other ){

					// assign(other.begin(), other.end());
					
					write(1, "operator= s\n",12 );
					_Last = other._Last;
					_End_Capacity = other._End_Capacity;
					_Frst = other._Frst;
					_Alloc = other,_Alloc;
					write(1, "operator= f\n",12 );
					return *this;
				};

			/* *******************   __Capacity__    ******************* */
				size_type		size (void) const			{ return _End_Capacity ? _Last - _Frst + 1 : 0; }
				bool			empty (void) const			{ return size() ? false : true; }
				size_type		max_size (void) const		{ return _Alloc.max_size(); }
				void			reserve (size_type new_cap)	{

					out_capacity(new_cap);

					if (new_cap == capacity())
						return ;
					if (empty()) {

						if (capacity())
							_Alloc.deallocate(_Frst, capacity());
						_Frst = _Alloc.allocate(new_cap);
						_Last = _Frst - 1;
						_End_Capacity = _Frst + new_cap;
						return ;
					}

					pointer old_start = _Frst;
					pointer old_end = _Last + 1;
					pointer	curs = _Frst - 1;
					_Frst = _Alloc.allocate(new_cap);
					_Last = _Frst - 1;
					while (++curs != old_end && new_cap--)
						_Alloc.construct(++_Last, *curs);

					_Alloc.deallocate(old_start, _End_Capacity - old_start);
					_End_Capacity = _Frst + new_cap;
				}
				size_type		capacity (void) const		{ return _End_Capacity ? _End_Capacity - _Frst : 0; }

			/* *******************  ITERATOR  ******************* */
				iterator		begin()			{ return iterator(_Frst); }
				const_iterator	begin() const	{  return const_iterator(_Frst); }

				iterator		end ()			{ return iterator(_Last + 1); }
				const_iterator	end () const	{ return const_iterator(_Last + 1); }

				reverse_iterator		rbegin()		{ return reverse_iterator(iterator( _Last)); }
				const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(const_iterator(_Last)); }

				reverse_iterator		rend()			{ return reverse_iterator(iterator(_Frst - 1)); }
				const_reverse_iterator	rend() const	{ return const_reverse_iterator(const_iterator(_Frst - 1)); }

			/* *******************  Element access ******************* */
				reference		operator[] (size_type idx)			{ return *(_Frst + idx);}
				const_reference	operator[] (size_type idx) const	{ return *(_Frst + idx);}

				reference		at (size_type pos)			{ out_range(pos); return *this[pos]; }
				const_reference	at (size_type pos) const	{ out_range(pos); return *this[pos]; }

				reference 		front()			{ return *_Frst;}
				const_reference	front() const	{ return *_Frst;}

				reference		back()			{ return *_Last;}
				const_reference	back() const	{ return *_Last;}

				pointer			data()			{ return _Frst ;}
				const_pointer	data() const	{ return _Frst ;}

			/* ********************** Modefier  ********************** */
				/*
					@brief clear fun, destroy all content of container and make it empty
				*/
				void	clear (){

					for (size_type lenght = 0; lenght < size(); lenght++)
						_Alloc.destroy(_Frst + lenght);
					_Last = _Frst - 1;
				}
				/*
					@brief insert @ value befor position
					@param	pos position to put in
					@param value value to put it
				*/
				iterator	insert (const_iterator pos, const_reference value) {

					iterator it_pos (pos);

					if (not(empty()) && (it_pos.base() < begin().base() || end().base() < it_pos.base()))
						_Alloc.deallocate((pointer)1, 1);/* abort */

					difference_type _offset = end().base() - pos.base();

					push_back(value);/* IaR */

					if (_offset++) 
						move_range ( end().base() - _offset, (end().base() - 2), (end().base() - _offset) + 1);
					*(end().base() - _offset) = value;

					return pos;
				}
				/*
					@brief insert @ count number of value befor position
					@param	pos position to put in
					@param	count number of the value insertion
					@param value value to put it
				*/
				iterator	insert (const_iterator pos, size_type count, const_reference value) {

					iterator it_pos (pos);

					if (count == 0)
						return pos;

					if (not(empty()) && (it_pos.base() < begin().base() || end().base() < it_pos.base()))
						_Alloc.deallocate((pointer)1, 1);/* abort */

					difference_type _offset = end().base() - pos.base();

					if (capacity() < size() + count)
						reserve (size() + count);/* IaR */

					if (_offset)
						move_range ( end().base() - _offset, (end().base() - 1), (end().base() - _offset) + count);

					it_pos = end() - _offset;
					_Last += count;
					while (count--)
						*(it_pos + count) = value;
					return pos;
				}
				/*
					@brief insert befor position from first_iter to last_iter
					@param	pos position to put in start
					@param	first iterator to start from the adapter values
					@param	is the last iterator present the range of adapters
				*/
				template <class InputIt>
					typename enable_if<__is_input_iterator<pointer, InputIt>::value, iterator>::type 
					insert (const_iterator pos, InputIt first, InputIt last) {

						iterator it_pos (pos);

						if (not(empty()) && (it_pos.base() < begin().base() || end().base() < it_pos.base(git )))
							_Alloc.deallocate((pointer)1, 1);/* abort */

						difference_type _offset = end().base() - pos.base();
						difference_type count = last.base() - first.base() + 1;

						if (static_cast<difference_type> (capacity()) < count)
							reserve (count);/* IaR */

						if (_offset)
							move_range ( end().base() - _offset, (end().base() - 1), (end().base() - _offset) + count);

						it_pos = end() - _offset;
						_Last += count;
						while (count--)
							*(it_pos++) = *(first++);
						return pos;
					}

				iterator	erase (iterator pos) {

					pointer pois = pos.base();

					iterator It = pos;
					while( pois != _Last) {

						*pois = *(pois + 1);
						pois++;
					}
					_Alloc.destroy(_Last);
					_Last--;
					return It;/* Iterator following the last removed element */
				}
				iterator	erase (iterator first, iterator last) {

					pointer curs = first.base();

					if (first > last)
						_Alloc.deallocate((pointer)1, 1);/* abort */
					while( curs != last.base() + 1)
						_Alloc.destroy(curs++);
					while(curs != _Last + 1)
						_Alloc.construct ((first++).base(), *curs++);
					_Last = first.base() - 1;
					while( curs != last.base())
						_Alloc.destroy(--curs);

					return last;
				}
				void		push_back (const_reference value) {

					if (size() >= capacity())
						reserve((empty() ? 1 : (size() * 2)));

					_Alloc.construct(++_Last, value);
				}
				void		pop_back() {

					if (not(empty()))
						_Alloc.destroy(_Last--);
				}

				void		resize (size_type count, value_type value = value_type()) {

					out_capacity(count);

					if (count < size())
						while (count != size())
							pop_back();
					else if (count > size())
						while (count != size())
							push_back(value);
				}
				void		swap (vector& other) {

					ft::swap(_Frst, other._Frst);
					ft::swap(_Last, other._Last);
					ft::swap(_End_Capacity, other._End_Capacity);
					ft::swap(_Alloc, other._Alloc);
				}

			private :

				/*
					@brief move range of contente form range address to start address.
					@attention most move it dongeer in overlapping case ! so it checked here.
					@param S ref to start range,
					@param E ref to end of range (last)
					@param to refere to the new start range
				*/
			template < class Tp>
				void	move_range(Tp S, Tp L, Tp to) {

						if (S == to)
							return ;
						if (to < S || L < to)/* @a to outside the range*/{

							while(S != L)
								*to++ = *S++;
							*to = *S;
						}
						else {

							difference_type _offset1 = to - S;
							L += 1;
							while (--L != S)
								*(L + _offset1) = *L;
							*to = *S;
						}
					}
				/*
					@brief throw exeption @if indexe indec case outside vector size
					@param idx index
				*/
				void	out_range( size_type idx ) {

					if (idx >= this->size())
						throw std::out_of_range( "vector");
				}
				/*
					@brief throw exeption @if count grader than the capacity convenable by allocutor
					@param count capacity to check
				*/
				void	out_capacity( size_type count ) {

					if (count > this->max_size())
						throw std::length_error( "vector");
				}

			public:
				~vector() {

					if (_End_Capacity)
						_Alloc.deallocate(_Frst, _End_Capacity - _Frst);
				}
		};
};


# endif

/* IaR */ /* meaning @attention  iterators are rejected */
