// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_FORWARD_DECLARATIONS_HPP
#define BOOST_HETEROGENOUS_FORWARD_DECLARATIONS_HPP

#include <functional>
// including monotonic/allocator.hpp is temporary; not needed after make_clone_allocator works properly
#define BOOST_HETEROGENOUS
#include <boost/monotonic/allocator.hpp>
#include <boost/heterogenous/detail/prefix.hpp>

namespace boost
{
	namespace heterogenous
	{
		/// an abstract interface for an allocator that can allocate and de-allocate
		/// byte sequences
		struct abstract_allocator;

		/// empty structure with a virtual destructor used if the user does not
		/// wish to use a custom base type
		struct default_base_type;

		/// provides a set of pure-virtual methods for allocation, de-allocation, and cloning
		template <class Base>
		struct abstract_cloneable;

		/// a structure derived from this, with type Derived, is correctly
		/// cloneable from a base pointer, given an abstract_allocator.
		template <
			class Derived
			, class Base = default_base_type
			>// this is too much uncessary customisation:, class AbstractBase = abstract_cloneable<Base> >
		struct cloneable;

		/// an adaptor for an existing class.
		///
		/// this is a type that can be used correctly in an homogenous container,
		/// of effective type T, where T does not inherit from heterogenous::base.
		template <
			class T
			, class Base = default_base_type
			>//, class AbstractBase = abstract_cloneable<Base> >
		struct adaptor;

		/// a heterogenous vector of objects
		template <
			class Base = default_base_type
			, class Alloc = monotonic::allocator<int>
			>//, class AbstractBase = abstract_cloneable<Base> >
		struct vector;

		/// a mapping of heterogenous objects to heterogenous objects
		template <
			class Base = default_base_type
			, class Pred = std::less<Base>
			, class Alloc = monotonic::allocator<int>
			>//, class AbstractBase = abstract_cloneable<Base> >
		struct map;

	} // namespace heterogenous

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_FORWARD_DECLARATIONS_HPP

//EOF
