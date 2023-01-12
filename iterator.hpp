/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:13:41 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/11 19:11:12 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include<cstddef>
#include<unistd.h>

# include"utility.hpp"
# include"type_traits.hpp"

/*
	@attention just an exception meaning 
		it refer to the operations which are ability to change the local address,
			so after applying it the iterators are invalidated
*/
#define __Iterator_invalidation

namespace ft {


	struct input_iterator_tag { };/* LagacyInputIterator */
	struct output_iterator_tag { };/* LagacyOutputIterator */
	struct forward_iterator_tag : public input_iterator_tag { };/* LagacyForwardIterator */
	struct bidirectional_iterator_tag : public forward_iterator_tag { };/* LagcyBiderectionalIterator */
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };/* LagacyRondamAccessIter */

	template <class _Category, class _Tp, class _Distance = ptrdiff_t,
			class _Pointer = _Tp*, class _Reference = _Tp&>
		struct iterator {

				typedef _Distance				difference_type;
				typedef _Tp						value_type;
				typedef _Pointer				pointer;
				typedef _Reference				reference;
				typedef _Category				iterator_category;
		};

	template< class _Tp>
		struct iterator_traits {

			typedef ptrdiff_t					difference_type;
			typedef _Tp							value_type;
			typedef _Tp*						pointer;
			typedef _Tp&						reference;
			typedef random_access_iterator_tag	iterator_category;
		};

	template< class _Tp>
		struct iterator_traits < _Tp*> {

			typedef ptrdiff_t					difference_type;
			typedef _Tp							value_type;
			typedef _Tp*						pointer;
			typedef _Tp&						reference;
			typedef random_access_iterator_tag	iterator_category;
		};

	template< class _Tp>
		struct iterator_traits < const _Tp*> {

			typedef ptrdiff_t					difference_type;
			typedef _Tp							value_type;
			typedef const _Tp*					pointer;
			typedef const _Tp&					reference;
			typedef random_access_iterator_tag	iterator_category;
		};

	template< class _Tp, class Iter_traits = iterator_traits<_Tp> >
		class normal_iterator {

			public:
				typedef typename Iter_traits::difference_type	difference_type;
				typedef typename Iter_traits::value_type		value_type;
				typedef typename Iter_traits::pointer			pointer;
				typedef typename Iter_traits::reference			reference;
				typedef typename Iter_traits::iterator_category			iterator_category;

			protected:
				_Tp	Super;

			public:
				normal_iterator() : Super(_Tp()) { };
				explicit normal_iterator (const _Tp& _x): Super(_x) { };
				template< class U >
					normal_iterator (const normal_iterator<U>& other)
						: Super (const_cast< pointer> (other.base())) { };
				_Tp			base() const { return Super; }

				normal_iterator&	operator=( const normal_iterator& rIt ){ Super = rIt.base(); return *this; }

				normal_iterator&	operator++ ()  { ++Super; return *this; }
				normal_iterator&	operator-- ()  { --Super; return *this; }
				normal_iterator		operator++ (int)  { normal_iterator old(Super); ++Super; return old; }
				normal_iterator		operator-- (int)  { normal_iterator old(Super); --Super; return old; }
				normal_iterator		operator+  (ptrdiff_t n) const	{ return normal_iterator(Super + n); }
				normal_iterator		operator-  (ptrdiff_t n) const	{ return normal_iterator(Super - n); }
				normal_iterator&	operator+= (ptrdiff_t n) { Super += n; return *this; }
				normal_iterator&	operator-= (ptrdiff_t n) { Super -= n; return *this; }

				reference	operator*() const	{ return *Super; }
				pointer		operator->() const	{ return Super; }
				reference	operator[] (difference_type n) const { return Super[n]; }
		};

	template <class _Iter>
		struct reverse_iterator {

			typedef _Iter							iterator_type;
			typedef typename _Iter::difference_type		difference_type;
			typedef typename _Iter::pointer			pointer;
			typedef typename _Iter::reference			reference;
			typedef input_iterator_tag				iterator_category;

			private:
				iterator_type Super;

			public:
				// reverse_iterator() : Super() { };
				explicit reverse_iterator (iterator_type x): Super(x) { };
				template< class U >
					reverse_iterator (const reverse_iterator<U>& other)
						: Super(other.base()) { };

				iterator_type	base() const { return Super; };

				reverse_iterator&	operator=( const reverse_iterator& rIt ){ Super = rIt.base();}

				reverse_iterator&	operator--() { ++Super; return *this; }
				reverse_iterator&	operator++() { --Super; return *this; }
				reverse_iterator	operator-- (int) { reverse_iterator old(Super); ++Super; return old; }
				reverse_iterator	operator++ (int) { reverse_iterator old(Super); --Super; return old; }
				reverse_iterator	operator- (ptrdiff_t n) const { return reverse_iterator (Super + n); }
				reverse_iterator	operator+ (ptrdiff_t n) const { return reverse_iterator (Super - n); }
				reverse_iterator&	operator-= (ptrdiff_t n) { Super += n; return *this; }
				reverse_iterator&	operator+= (ptrdiff_t n) { Super -= n; return *this; }

				reference	operator*() const { iterator_type It = Super ; return *(--It); }
				// pointer		operator->() const { return &operattor*(); }
				reference	operator[] (difference_type n) const { return *(*this + n); }
		};

#define __binary_operator

#define __relational_operator __binary_operator

		template < typename Iter1, typename Iter2>
			__relational_operator
			bool	operator> (Iter1& a, Iter2& b)	{ return a.base() > b.base(); }
		template < typename Iter1, typename Iter2>
			__relational_operator
			bool	operator>= (Iter1& a, Iter2& b)	{ return a.base() >= b.base(); }
		template < typename Iter1, typename Iter2>
			__relational_operator
			bool	operator< (Iter1& a, Iter2& b)	{ return a.base() > b.base(); }
		template < typename Iter1, typename Iter2>
			__relational_operator
			bool	operator<= (Iter1& a, Iter2& b)	{ return a.base() <= b.base(); }
		template < typename Iter1, typename Iter2>
			__relational_operator
			bool	operator== (Iter1& a, Iter2& b)	{ return a.base() == b.base(); }
		template < typename Iter1, typename Iter2>
			__relational_operator
			bool	operator!= (Iter1& a, Iter2& b)	{ return a.base() != b.base(); }

#define __assignment_operator __binary_operator

		template < typename Iter1, typename Iter2>
			__assignment_operator
			typename Iter1::difference_type	operator- (Iter1 a, Iter2 b)	{ return a.base() - b.base(); }
		// template < typename Iter1, typename Iter2>
		// 	typename Iter1::difference_type	operator+ (Iter1& a, Iter2& b)	{ return *a + *b;}
		// template < typename Iter>
		// // 	Iter&	operator= (Iter& a, Iter& b)	{ *a = *b; return a; }
		// template < typename Iter>
		// 	Iter&	operator+= (Iter& a, Iter& b)	{ *a += *b; return a; }
		// template < typename Iter>
		// 	Iter&	operator-= (Iter& a, Iter& b)	{ *a -= *b; return a; }


	/*
		@brief check type of typename is it iterator or not, 
		is a defined behaviour for the enable_if statement
	*/
	template < typename _TP, typename Iter>
		class __is_input_iterator : public false_type { };
	template < typename _TP >
		class __is_input_iterator <   _TP, iterator_traits < _TP > > : public true_type { };
	template <  typename _TP>
		class __is_input_iterator <   _TP, normal_iterator < _TP > > : public true_type { };
	template <  typename _TP>
		class __is_input_iterator <   _TP, reverse_iterator < normal_iterator < _TP > > >: public true_type { };

	template < class _Tp>
		normal_iterator<_Tp> to_normal_iter (const normal_iterator<_Tp>& it) { return it; }
	template < class _Tp>
		normal_iterator<_Tp> to_normal_iter (const reverse_iterator<normal_iterator<_Tp> >& it) { return it.base(); }


	namespace ___distance {


		template <class _InputIter>
				typename iterator_traits<_InputIter>::difference_type
				__distance(_InputIter __first, _InputIter __last, input_iterator_tag) {

					typename iterator_traits<_InputIter>::difference_type __r(0);
						for (; __first != __last; ++__first)
							++__r;
					return __r;
				}

				template <class _RandIter>
					typename iterator_traits<_RandIter>::difference_type
				__distance(_RandIter __first, _RandIter __last, random_access_iterator_tag) {

					return __last - __first;
				}

				template <class _InputIter>
				typename iterator_traits<_InputIter>::difference_type
				distance(_InputIter __first, _InputIter __last) {

					return __distance(__first, __last, typename iterator_traits<_InputIter>::iterator_category());
				}
	}

	using namespace ___distance;
}/* name space end [ ft ]*/

#endif
 



