/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:13:41 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/28 19:52:26 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#	define ITERATOR_HPP

# include<cstddef>

# include"utility.hpp"
# include"type_traits.hpp"



namespace ft {



/*********************************************************************************************************
*	@brief	just an interface, that manipulates the permission of the iterator
*	@note	iterator category
*********************************************************************************************************/
struct input_iterator_tag { };/* LagacyInputIterator */
struct output_iterator_tag { };/* LagacyOutputIterator */
struct forward_iterator_tag : public input_iterator_tag { };/* LagacyForwardIterator */
struct bidirectional_iterator_tag : public forward_iterator_tag { };/* LagcyBiderectionalIterator */
struct random_access_iterator_tag : public bidirectional_iterator_tag { };/* LagacyRondamAccessIter */



/*********************************************************************************************************
*	@brief	check if is a random access iterator,, else false value
*********************************************************************************************************/
	template < typename Iter_Category>
		class __is_random_access_iter : public false_type { };
	template < >
		class __is_random_access_iter <random_access_iterator_tag> : public true_type { };

/*********************************************************************************************************
*	@brief	check if bidirectional iterator here, else false value
*********************************************************************************************************/
	template < typename Iter_Category>
		class __is_bidirectional_iter : public __is_random_access_iter <Iter_Category> { };
	template < >
		class __is_bidirectional_iter <bidirectional_iterator_tag> : public true_type { };

/*********************************************************************************************************
*	@brief	check if forward iterator here, else false value
*********************************************************************************************************/
	template < typename Iter_Category>
		class __is_forward_iter : public __is_bidirectional_iter <Iter_Category> { };
	template < >
		class __is_forward_iter <forward_iterator_tag> : public true_type { };

/*********************************************************************************************************
*	@brief	check if input iterator here, else false value 
*********************************************************************************************************/
	template < typename Iter_Category>
		class __is_input_iter : public __is_forward_iter <Iter_Category> { };
	template < >
		class __is_input_iter <input_iterator_tag> : public true_type { };



/*************************************************************************************************************
*	@brief	prepare the interface of iterator
*	@param	_Category	category of iterator
*	@param	_Tp			type to mange it
*	@param	_Distance	ptrdiff_t = default
*	@param	_Pointer	( _TP * ) default and mostly usage
*	@param	_Reference	( _TP & ) default and mostly usage
*************************************************************************************************************/
	template <class _Category, class _Tp, class _Distance = ptrdiff_t,
			class _Pointer = _Tp*, class _Reference = _Tp&>
		struct iterator {

				typedef _Distance								difference_type;
				typedef typename ft::remove_c<_Tp>::type		value_type;
				typedef _Pointer								pointer;
				typedef _Reference								reference;
				typedef _Category								iterator_category;
		};

	template< class _Tp>
		struct iterator_traits : public iterator <random_access_iterator_tag, _Tp > { };

/*********************************************************************************************************
*	@brief	that remove the pointer of type
*********************************************************************************************************/
	template< class _Tp>
		struct iterator_traits < _Tp*> : public iterator <random_access_iterator_tag, _Tp> { };



/*************************************************************************************************************
*	@brief	class of terator managments
*	@param	_TP	type to mange it
*	@param	Iter_traits iterator interface
*************************************************************************************************************/
template< class _Tp, class Iter_traits = iterator_traits<_Tp> >
	struct normal_iterator {

			typedef typename Iter_traits::difference_type	difference_type;
			typedef typename Iter_traits::value_type		value_type;
			typedef typename Iter_traits::pointer			pointer;
			typedef typename Iter_traits::reference			reference;
			typedef typename Iter_traits::iterator_category			iterator_category;

		private:
			_Tp	Super;

		public:
			normal_iterator() : Super(_Tp()) { };
			explicit normal_iterator (const _Tp& _x): Super(_x) { };
			template< class U >
				normal_iterator (const normal_iterator<U>& other)
					: Super (const_cast< pointer> (other.base())) { };

			_Tp			base() const { return Super; }

			normal_iterator&	operator= ( normal_iterator rIt ) { Super = rIt.base(); return *this; }

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



/*************************************************************************************************************
*	@brief	class that manage normal iterator in reverse order
*	@param	_Iter iterator 
*************************************************************************************************************/
template <class _Iter>
	struct reverse_iterator {

			typedef _Iter									iterator_type;
			typedef typename _Iter::difference_type			difference_type;
			typedef typename _Iter::pointer					pointer;
			typedef typename _Iter::reference				reference;
			typedef typename _Iter::iterator_category		iterator_category;

		private:
			iterator_type Super;

		public:
			reverse_iterator() : Super() { };
			explicit reverse_iterator (iterator_type x): Super(x) { };
			template< class U >
				reverse_iterator (const reverse_iterator<U>& other)
					: Super(other.Super) { };

			iterator_type	base() const { return Super; };

			reverse_iterator&	operator=( const reverse_iterator& rIt ){ Super = rIt.Super;}

			reverse_iterator&	operator--() { ++Super; return *this; }
			reverse_iterator&	operator++() { --Super; return *this; }
			reverse_iterator	operator-- (int) { reverse_iterator old(Super); ++Super; return old; }
			reverse_iterator	operator++ (int) { reverse_iterator old(Super); --Super; return old; }
			reverse_iterator	operator- (ptrdiff_t n) const { return reverse_iterator (Super + n); }
			reverse_iterator	operator+ (ptrdiff_t n) const { return reverse_iterator (Super - n); }
			reverse_iterator&	operator-= (ptrdiff_t n) { Super += n; return *this; }
			reverse_iterator&	operator+= (ptrdiff_t n) { Super -= n; return *this; }

			reference	operator*() const { iterator_type org (Super); return *(--org); }
			pointer		operator->() const { iterator_type org (Super); return (--org).operator->(); }
			reference	operator[] (difference_type n) const { return *(*this + n); }
	};



	template < typename Iter>
		typename ft::enable_if < 
			ft::__is_input_iter<typename Iter::iterator_category>::value,
			bool >::type  operator== (const Iter& a, const Iter& b)	{ return &(*a) == &(*b); }
	template < typename Iter> 
		typename ft::enable_if < 
			ft::__is_input_iter<typename Iter::iterator_category>::value,
			bool >::type 
				operator< (const Iter& a, const Iter& b)	{ return &(*a) < &(*b); }


	template<typename Iter>
		bool operator!= (const Iter& a, const Iter& b) { return not (a == b); }

	template<typename Iter>
		bool operator> (const Iter& a, const Iter& b) { return  b < a; }

	template<typename Iter>
		bool operator<= (const Iter& a, const Iter& b) { return not (b < a); }

	template<typename Iter>
		bool operator>= (const Iter& a, const Iter& b) { return not (a <  b); }


	template < class _InputIter>
	typename _InputIter::difference_type
		distance (_InputIter first, _InputIter last) {

		typename _InputIter::difference_type length(0);
		for (; first != last; ++first)
			++length;
		return length;
	}
	template < class _InputIter>
	typename ft::enable_if <
		__is_random_access_iter< typename _InputIter::_InputIterator_category>::value, typename _InputIter::difference_type >::type 
			distance (_InputIter first, _InputIter last) { return abs(last.operator->() - first.operator->()); }


} /* namespace ft */

#endif
 



