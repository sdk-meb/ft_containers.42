/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:05:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/31 02:01:48 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

# include"./ab__tree.hpp"
# include"./base_tree.hpp"



/*************************************************************************************************************
*	@brief	base Red _ Black _ tree
*	@param	T_SHIP	Shipment to stor
*************************************************************************************************************/
template < class Container >
	class RBT : protected ___abase <Container> {

	public :
        typedef 	typename Container::allocator_type		Allocator;
        typedef 	typename Container::size_type			size_type;

        typedef 	typename Container::value_type			T_SHIP;
        typedef const typename Container::key_type			key_type;
        typedef 	typename Container::key_compare			key_compare;

        typedef		__road_<T_SHIP, Allocator>				__road;

        typedef typename Allocator::template rebind<__road>::other	SAllocator;

		public:
/***************************  @category	 __  constructor  __  ***********************************************/

		RBT (const key_compare& cmp, Allocator alloc = Allocator()) : ___abase <Container> (cmp, alloc) { }


/***************************  @category	 __  BST # tree intertion  __  **************************************/

	/*********************************************************************************************************
	*	@brief insert  node inside the tree, exacption in case of duplicate key in tree
	*	@param ship shipment to insert
	*	@param	ex exeption true = default
	*	@exception permitted by order
 	*********************************************************************************************************/
		__road&		insert (const __road& _node, bool ex=true) {

			if (this->seed) return insertion(const_cast<__road&>(_node), this->seed, ex);

			this->seed = this->_SAlloc.allocate ( 1);

			this->_SAlloc.construct (this->seed, _node);
			this->seed->Color	= BLACK;
			this->seed->copy_ship = false;

			++this->Size;
			return *this->seed;
		}

	/*********************************************************************************************************
	*	@brief insert  pair  inside the tree, exacption in case of duplicate key in tree
	*			, and thas not dealocated in destruction
	*	@param ship shipment to insert
 	*********************************************************************************************************/
		__road&		insert (const T_SHIP& pair) { return insert (__road (pair, this->_SAlloc)); }



/***************************  @category	 __  BST # binary search tree  __  **********************************/

	/*********************************************************************************************************
	*	@return  node indecated by the key, NIL if not find
 	*********************************************************************************************************/
		__road*		search (key_type& key) const throw() {

			return not this->seed ? NIL : this->searching(key, this->seed);
		}

	/*********************************************************************************************************
	*	@return content(value) idecated by the key
	*	@param flag exeception or insirtion in case of non-existence
 	*********************************************************************************************************/
		T_SHIP&		search (key_type& key, bool ex) {

			if (not ex) return  *insert(key).Ship;

			__road* find = search(key);

			if (not find) std::__throw_range_error ("key search");
			return *find->Ship;
		}



/***************************  @category	 __  BST #  node deletion tree  __  *********************************/

	/*********************************************************************************************************
	*	@param 	key
	*	@return result of deletion true/false
	*********************************************************************************************************/
		bool		del (key_type& key) throw() {

			__road* indecated = search(key);

			return indecated ? _delete(indecated), true : false;
		}

	/*********************************************************************************************************
	*	@overload (2)
	*	@param 	Shipment (pair)
	*********************************************************************************************************/
		void		del (__road& _node) throw() { _delete (&_node); }
		void		del (__road* _node) throw() { _delete (_node); }


	private:

	/*********************************************************************************************************
	*	@brief	binary tree insertion, that call @a adjustment that remove the violated rules of rb-tree
	*	@param	_node	indicator to being rotated
	*	@param	sub	indicator in last after recursions, the parent of the new child
	*	@param	ex exeption true = default
	*	@exception permitted by order
	*********************************************************************************************************/
		__road&		insertion(__road& _node, __road* sub, bool ex=true) {

			if (*_node.Ship < *sub->Ship) {

				if (sub->L_ch) sub = sub->L_ch;
				else {

					sub->L_ch = this->_SAlloc.allocate(1);

					this->_SAlloc.construct (sub->L_ch, _node);
					if (_node.Color == BLACK) throw "fddf";
					sub->L_ch->P = sub;

					sub->L_ch->copy_ship = false;
					sub->L_ch->adjustment();

					++this->Size;
					return *sub->L_ch;
				}
			}
			else if (*_node.Ship > *sub->Ship) {

				if (sub->R_ch) sub = sub->R_ch;
				else {

					sub->R_ch = this->_SAlloc.allocate(1);

					this->_SAlloc.construct (sub->R_ch, _node);
					if (_node.Color == BLACK) throw "fddf";
					sub->R_ch->P = sub;

					sub->R_ch->copy_ship = false;
					sub->R_ch->adjustment();
 
					++this->Size;
					return *sub->R_ch;
				}
			}
			else if (ex) { _node.copy_ship = false;
				std::__throw_overflow_error ("similar shipment violates the property of map rules") ;}
			else
				return  _node.copy_ship = false, *sub;
			return insertion(_node, sub, ex);
		}


	/*********************************************************************************************************
	*	@brief	binary tree deletion, that call @a delete_fixup rb-tree in case of violated rules
	*	@param	criminal	the node who has the shipment  referred by the key
	*********************************************************************************************************/
		void		_delete(__road* criminal) {

			if (not criminal) return ;

			__road* victim = &criminal->redemption();

			if (this->seed == victim) this->seed = victim->R_ch;

			std::swap (victim->Ship, criminal->Ship);

			__road* ch = victim->L_ch ?  victim->L_ch :  victim->R_ch;
			if (victim->Color == BLACK) {

				if (ch and ch->Color == RED) ch->recolor();
				else victim->delete_fixup();
			}

			/* replace link to victim by who yastahik, ma ya3arfo hta had*/
			{
				if (ch) ch->P = victim->P;
				if (victim->WhoIm() == JU)	victim->P->L_ch = ch;
				else if (victim->WhoIm() == SE) victim->P->R_ch = ch;
			}
			/* unlink the victim , mayaraf raso fin*/
			victim->L_ch	= NIL;
			victim->R_ch	= NIL;
			victim->P	= NIL;

			this->_SAlloc.destroy(victim);
			this->_SAlloc.deallocate (victim, 1);

			--this->Size;
			/* end of history */
		}


};





# endif
