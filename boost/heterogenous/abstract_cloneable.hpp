// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_COMMON_BASE_HPP
#define BOOST_HETEROGENOUS_COMMON_BASE_HPP

#include <string>
#include <boost/functional/hash_fwd.hpp>
#include <boost/heterogenous/detail/prefix.hpp>
#include <boost/heterogenous/abstract_allocator.hpp>

namespace boost
{
	namespace heterogenous
	{
		/// default base type used for object hierarchies to be stored in a given
		/// container or containers. the user can supply their own when using 
		/// cloneable<Derived, Base> this will be used by default.
		struct default_base_type
		{
			virtual ~default_base_type() { }
		};

		/// root structure for the heterogenous object system
		template <class Base>
		struct abstract_cloneable : virtual Base
		{
			typedef Base base_type;
			typedef abstract_cloneable<Base> this_type;

			/// make storage for a new instance, but do not invoke any constructor
			virtual this_type *allocate(abstract_allocator &) const = 0;

			/// free memory associated with the given instance
			virtual void deallocate(abstract_allocator &) = 0;

			/// create a new object of the derived type
			virtual this_type *create_new(abstract_allocator &) const = 0;

			/// create a clone using copy-constructor. this is implemented in cloneable<>, but can
			/// be overriden by the user in the derived type if required.
			virtual this_type *copy_construct(abstract_allocator &) const = 0;

			/// optional means to make a clone that does not use copy-construction.
			/// user can overload this in their derived type to provide custom clone implementation.
			virtual this_type *make_copy(abstract_allocator &) const { return 0; }

			/// make a copy of the given instance. try the custom clone method first, 
			/// then default to using the copy-constructor method
			this_type *clone(abstract_allocator &alloc) const
			{
				if (this_type *copy = make_copy(alloc))
					return copy;
				return copy_construct(alloc);
			}

			/// for use with types that use multiple inheritance - select which sub-object to clone
			template <class Ty>
			this_type *clone_as(abstract_allocator &alloc) const
			{
				const cloneable<Ty, Base> *ptr = dynamic_cast<const cloneable<Ty, Base> *>(this);
				if (ptr == 0)
					throw std::bad_cast();
				return ptr->clone(alloc);
			}

			/// make a copy of the given instance using the heap. caller should call delete
			this_type *clone() const
			{
				return 0;
				//if (this_type *copy = clone(original, alloc))
				//	return copy;
				//return copy_construct(original, alloc);
			}

			/// overridable hash function
			virtual size_t hash_value() const { return 0; }

			/// return a hash value for the object. try the virtual method first, otherwise just use pointer value
			size_t hash() const 
			{ 
				if (size_t value = hash_value())
					return value;
				return ptrdiff_t(reinterpret_cast<const char *>(this) - 0);
			}

			virtual std::string to_string() const { return "cloneable"; }
		};

	} // namespace heterogenous


	template <class B>
	struct hash<heterogenous::abstract_cloneable<B> >
	{
		size_t operator()(heterogenous::abstract_cloneable<B> const &base) const
		{
			return base.hash();
		}
	};

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_COMMON_BASE_HPP

//EOF
