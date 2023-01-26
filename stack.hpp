/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:35:45 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/26 12:33:30 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#	define STACK_HPP

# include"vector.hpp"
#include <cstdlib>
namespace	ft {


/*************************************************************************************************************
*	@category adaptor Containers
*	@brief	adapt the container as an stack funconality, LIFO D-S
*	@param 	T value type
*	@param	Container 	Container to adapt it
*************************************************************************************************************/
template <class T, class Container = ft::vector<T> >
	class stack {

		public:

		typedef Container	container_type;
		typedef typename	container_type::value_type			value_type;	
		typedef typename	container_type::size_type			size_type;	
		typedef typename	container_type::reference			reference;	
		typedef typename	container_type::const_reference		const_reference;
		

    template<typename _T, typename con>
		friend bool
		operator== (const stack<_T, con>&, const stack<_T, con>&);

    template<typename _T, typename con>
		friend bool
		operator< (const stack<_T, con>&, const stack<_T, con>&);

		protected :
			container_type	c;

		public:

		/** 
			@category	Constructor
			@brief Default constracter that initialize the container 
				with default constructor  or copy assi-cons i case of argement find;
			@param cont container which the stack adapt it.
		*/
			explicit stack (const Container& cont=Container()): c(cont) { }

		/**
			@category copy Counstructor
			@brief	Needless to define غني عن تعريف
			@param	other vector to copie from it
		*/
			stack (const stack& other): c(other.Stack) { }

		/**
			@category operator
			@brief	Needless to define, equal to the same container operator
			@param	cont Container
		*/
			stack&	operator= (const Container& cont) { c = cont.c; return *this; }


	/** *******************  @category __Capacity__    ******************* */
			bool		empty() const { return c.empty(); }
			size_type	size() const { return c.size(); }
	
	/** *******************  @category __Modifiers__    ******************* */
			void		push (const value_type& value) { c.push_back(value); }
			void		pop() { c.pop_back(); }

	/** *******************  @category __Element_access__    ******************* */
			reference	top() { return c.back(); }


		~stack() { };
	};

template<typename _Tp, typename con>
    bool operator== (const stack<_Tp, con>& _x, const stack<_Tp, con>&  _y)
    { return _x.c ==  _y.c; }

template<typename _Tp, typename con>
    bool operator< (const stack<_Tp, con>& _x, const stack<_Tp, con>& _y)
    { return _x.c <  _y.c; }

template<typename _Tp, typename con>
    bool operator!= (const stack<_Tp, con>& _x, const stack<_Tp, con>& _y)
    { return not (_x ==  _y); }

template<typename _Tp, typename con>
    bool operator> (const stack<_Tp, con>& _x, const stack<_Tp, con>& _y)
    { return  _y < _x; }

template<typename _Tp, typename con>
    bool operator<= (const stack<_Tp, con>& _x, const stack<_Tp, con>& _y)
    { return not ( _y < _x); }

template<typename _Tp, typename con>
    bool operator>= (const stack<_Tp, con>& _x, const stack<_Tp, con>& _y)
    { return not (_x <  _y); }

};

# endif
