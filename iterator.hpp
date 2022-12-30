/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:13:41 by mes-sadk          #+#    #+#             */
/*   Updated: 2022/12/31 12:07:46 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include<cstddef>
#include<unistd.h>

namespace ft {

	

	template< class _Tp>
		struct iterator_traits {

			typedef ptrdiff_t					difference_type;
			typedef _Tp							value_type;
			typedef _Tp*						pointer;
			typedef _Tp&						reference;
			// typedef random_access_iterator_tag	iterator_category;

			private:
				value_type	Super;

			public:
				iterator_traits() : Super(nullptr) { };
				explicit iterator_traits (value_type _x): Super(_x) { };
				template< class U >
					iterator_traits (const iterator_traits<U>& other)
						: Super(other.base()) { };
				value_type	base() const { return Super; }

				iterator_traits&	operator=( const iterator_traits& rIt ){ Super = rIt.base(); return *this; }

				iterator_traits&	operator++() { ++Super; return *this; }
				iterator_traits&	operator--() { --Super; return *this; }
				iterator_traits		operator++ (int) { return iterator_traits(Super++); }/* * 2 ????????? */ 
				iterator_traits		operator-- (int) { return  iterator_traits(Super--); }/* * 2 ????????? */ 
				iterator_traits		operator+ (ptrdiff_t n) const { return iterator_traits(Super + n); }
				iterator_traits		operator- (ptrdiff_t n) const { return iterator_traits(Super - n); }
				iterator_traits&	operator+= (ptrdiff_t n) { Super += n; return *this; }
				iterator_traits&	operator-= (ptrdiff_t n) { Super -= n; return *this; }

				reference	operator*() const { value_type tmp = (Super - 1); return *tmp; };
				pointer		operator->() const { return *Super; }
				reference	operator[] (difference_type n) const { return base()[-n -1]; }
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
				reverse_iterator() : Super(nullptr) { };
				explicit reverse_iterator (iterator_type x): Super(x) { };
				template< class U >
					reverse_iterator (const reverse_iterator<U>& other)
						: Super(other.base()) { };
				iterator_type	base() const { return iterator_traits<iterator_type>(Super).base(); };

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

	template <typename T>
		bool	operator > (T& a, T& b){ return a.base() > b.base(); }
	template <typename T>
		bool	operator >= (T& a, T& b){ return a.base() >= b.base(); }
	template <typename T>
		bool	operator < (T& a, T& b){ return a.base() > b.base(); }
	template <typename T>
		bool	operator <= (T& a, T& b){ return a.base() <= b.base(); }
	template <typename T>
		bool	operator == (T& a, T& b){ return a.base() == b.base(); }
	template <typename T>
		bool	operator != (T& a, T& b){ return a.base() != b.base(); }

} /* name space end [ ft ]*/

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

