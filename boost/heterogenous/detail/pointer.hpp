// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_DETAIL_POINTER_HPP
#define BOOST_HETEROGENOUS_DETAIL_POINTER_HPP

#include <boost/heterogenous/detail/prefix.hpp>
#include <boost/heterogenous/cloneable.hpp>

namespace boost
{
	namespace heterogenous
	{
		namespace detail
		{
			
			template <class U, class B>
			struct pointer
			{
				typedef U derived_type;
				typedef B base_type;
				typedef cloneable<derived_type, base_type> ptr_type;
				typedef typename cloneable<derived_type, base_type>::this_type cloneable_type;
				typedef typename cloneable_type::abstract_base_type abstract_base_type;

			private:
				ptr_type *ptr;

			public:
				pointer(U *p = 0) : ptr(dynamic_cast<cloneable_type *>(p))
				{
				}
				abstract_base_type *to_abstract() const
				{
					return ptr;
				}
				base_type *to_base() const
				{
					return ptr;
				}
				cloneable_type *to_cloneable() const
				{
					return ptr;
				}
				derived_type *to_derived() const
				{
					return ptr->cloneable_type::self_ptr;
				}
			};

		} // namespace detail

	} // namespace heterogenous

} // namespace boost

#endif // BOOST_HETEROGENOUS_DETAIL_POINTER_HPP

//EOF
