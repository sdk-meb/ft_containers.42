/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:08:25 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/12/31 15:08:45 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#	define VECTOR_HPP
/*         dynamic contiguous array    */
/*          */
# include<memory>
# include"iterator.hpp"
# include<iterator>
# include<algorithm>
# include<cstdlib>

// # undef  ptrdiff_t

namespace ft {

		template <typename T>
			void swap (T& a, T& b) {

				T c = a;
				a = b;
				b = c;
			}
	template <class T, class Allocator = std::allocator<T> >
		struct vector {
			/* https://en.cppreference.com/w/cpp/memory/allocator */
				typedef Allocator									allocator_type;
				typedef typename allocator_type::value_type			value_type;

				typedef typename allocator_type::size_type			size_type;
				typedef typename allocator_type::difference_type	difference_type;

				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;

				typedef ft::iterator_traits<pointer>				iterator;
				typedef ft::iterator_traits<const_pointer>			const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			private:

				allocator_type	_Alloc ;
				pointer					_Frst ;
				pointer					_Last ;
				pointer					_End_Capacity ;

			public:

				explicit vector ( const Allocator& alloc = allocator_type() ): _Alloc(alloc){

					// _Frst = std::nullptr_t();
					// _Last = std::nullptr_t();

					_End_Capacity = nullptr;
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
				// 		catch (const std::exception& exc){


							

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

			/* *******************   capacity    ******************* */
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

				reference		back() 			{ return *_Last;}
				const_reference	back() const	{ return *_Last;}

				pointer			data()			{ return _Frst ;}
				const_pointer	data() const	{ return _Frst ;}

			/* ********************** Modefier  ********************** */
				void	clear (){

					for (size_type lenght = 0; lenght < size(); lenght++)
						_Alloc.destroy(_Frst + lenght);
					_Last = _Frst - 1;
				}
				iterator	insert (const_iterator pos, const_reference value) {

					if (pos.base() > _Last || pos.base() < _Frst)
						_Alloc.deallocate((pointer)1, 1);
					push_back(value);
					for (pointer p = _Last; p != pos.base(); p--)
						ft::swap(p, p - 1);
				}
				// iterator	insert (const_iterator pos, size_type count, const_reference value) {

					
				// }
				// template <class InputIt>
				// 	iterator	insert (const_iterator pos, InputIt first, InputIt last) {

						
				// 	}
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
				void	swap (vector& other) {

					ft::swap(_Frst, other._Frst);
					ft::swap(_Last, other._Last);
					ft::swap(_End_Capacity, other._End_Capacity);
					ft::swap(_Alloc, other._Alloc);
				}

			private :

				void	out_range( size_type idx ) {

					if (idx >= this->size())
						throw std::out_of_range( "vector");
				}
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
