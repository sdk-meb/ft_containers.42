/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:13:41 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/06 12:00:55 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include<cstddef>
#include<unistd.h>

# include"utility.hpp"
# include"type_traits.hpp"

namespace ft {

	template< class _Tp>
		struct iterator_traits { };

	template< class _Tp>
		struct iterator_traits < _Tp*> {

			typedef _Tp							value_type;
			typedef _Tp*						pointer;
			typedef _Tp&						reference;
			// typedef random_access_iterator_tag	iterator_category;
		};

	template< class _Tp>
		struct iterator_traits < const _Tp*> {

			typedef _Tp						value_type;
			typedef const _Tp*				pointer;
			typedef const _Tp&				reference;
			// typedef random_access_iterator_tag	iterator_category;
		};

	template< class _Tp>
		struct iterator {

			// typedef	iterator_base					iterator;
    		typedef ft::iterator_traits<_Tp>				traits_type;

			typedef ptrdiff_t								difference_type;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;

			protected:
				_Tp	Super;

			public:
				iterator() : Super(_Tp()) { };
				explicit iterator (const _Tp& _x): Super(_x) { };
				template< class U >
					iterator (const iterator<U>& other)
						: Super (const_cast< pointer> (other.base())) { };
				_Tp			base() const { return Super; }

				iterator&	operator=( const iterator& rIt ){ Super = rIt.base(); return *this; }

				iterator&	operator++() { ++Super; return *this; }
				iterator&	operator--() { --Super; return *this; }
				iterator	operator++ (int) { return iterator(Super++); }
				iterator	operator-- (int) { return  iterator(Super--); }
				iterator	operator+ (ptrdiff_t n) const { return iterator(Super + n); }
				iterator	operator- (ptrdiff_t n) const { return iterator(Super - n); }
				iterator&	operator+= (ptrdiff_t n) { Super += n; return *this; }
				iterator&	operator-= (ptrdiff_t n) { Super -= n; return *this; }

				reference	operator*() const	{ return *Super; }
				pointer		operator->() const	{ return Super; }
				reference	operator[] (difference_type n) const { return Super[n]; }
		};


	template <class _Iter>
		struct reverse_iterator {
														
			typedef _Iter						iterator_type;
			typedef ptrdiff_t					difference_type;
			typedef _Iter*						pointer;
			typedef _Iter&						reference;

			private:
				_Iter Super;

			public:
				reverse_iterator() : Super(0) { };
				explicit reverse_iterator (iterator_type x): Super(x) { };
				template< class U >
					reverse_iterator (const reverse_iterator<U>& other)
						: Super((other).base()) { };
				iterator_type	base() const { return iterator<iterator_type>(Super).base(); };

				reverse_iterator&	operator=( const reverse_iterator& rIt ){ Super = rIt.base();}

				reverse_iterator&	operator--() { ++Super; return *this; }
				reverse_iterator&	operator++() { --Super; return *this; }
				reverse_iterator	operator-- (int) { return reverse_iterator(Super++); }
				reverse_iterator	operator++ (int) { return reverse_iterator(Super--); }
				reverse_iterator	operator- (ptrdiff_t n) const { return reverse_iterator(base()+n); }
				reverse_iterator	operator+ (ptrdiff_t n) const { return reverse_iterator(base()-n); }
				reverse_iterator&	operator-= (ptrdiff_t n) { Super += n; return *this; }
				reverse_iterator&	operator+= (ptrdiff_t n) { Super -= n; return *this; }

				reference	operator*() const { iterator_type tmp = (Super - 1); return *tmp; };
				pointer		operator->() const { return *Super; }
				reference	operator[] (difference_type n) const { return base()[-n -1]; }
		};

	template < typename Iter>
		bool	operator > (Iter& a, Iter& b){ return a.base() > b.base(); }
	template < typename Iter>
		bool	operator >= (Iter& a, Iter& b){ return a.base() >= b.base(); }
	template < typename Iter>
		bool	operator < (Iter& a, Iter& b){ return a.base() > b.base(); }
	template < typename Iter>
		bool	operator <= (Iter& a, Iter& b){ return a.base() <= b.base(); }

	template < typename Iter >
		bool	operator == (Iter& a, Iter& b)
				{ return(a).base() == (b).base(); }

	template <typename Iter>
		bool	operator != (Iter& a, Iter& b){ return a.base() != b.base(); }


	/*
		@brief check type of typename is it iterator or not, 
		is a defined behaviour for the enable_if statement
	*/
	template < typename _TP, typename Iter>
		class __is_input_iterator : public false_type { };
	template < typename _TP >
		class __is_input_iterator <   _TP, iterator_traits < _TP > > : public true_type { };
	template <  typename _TP>
		class __is_input_iterator <   _TP, iterator < _TP > > : public true_type { };
	template <  typename _TP>
		class __is_input_iterator <   _TP, reverse_iterator < iterator < _TP > > >: public true_type { };

}/* name space end [ ft ]*/

#endif
 



	// struct input_iterator_tag { };/* LagacyInputIterator */
	// struct output_iterator_tag { };/* LagacyOutputIterator */
	// struct forward_iterator_tag : public input_iterator_tag { };/* LagacyForwardIterator */
	// struct bidirectional_iterator_tag : public forward_iterator_tag { };/* LagcyBiderectionalIterator */
	// struct random_access_iterator_tag : public bidirectional_iterator_tag { };/* LagacyRondamAccessIter */


	// template <class _Category, class _Tp, class _Distance = ptrdiff_t,
	// 		class _Pointer = _Tp*, class _Reference = _Tp&>
	// 	struct iterator {

	// 			typedef _Distance				difference_type;
	// 			typedef _Tp						value_type;
	// 			typedef _Pointer				pointer;
	// 			typedef _Reference				reference;
	// 			typedef _Category				iterator_category;
	// 	};

