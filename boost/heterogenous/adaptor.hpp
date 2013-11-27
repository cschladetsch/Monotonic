// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_ADAPTOR_HPP
#define BOOST_HETEROGENOUS_ADAPTOR_HPP

#include <boost/heterogenous/detail/prefix.hpp>
#include <boost/heterogenous/cloneable.hpp>

namespace boost
{
	namespace heterogenous
	{
		/// an adaptor for an existing class
		///
		/// this is a type that can be used in an homogenous container
		///
		/// ...this may or may not be a good idea...
		template <class T, class Base>//, class AbstractBase>
		struct adaptor : T, cloneable<adaptor<T, Base/*, AbstractBase*/>, Base/*, AbstractBase*/>
		{
			adaptor() { }

			template <class A0>
			adaptor(A0 a0) : T(a0)
			{
			}
			template <class A0, class A1>
			adaptor(A0 a0, A1 a1) : T(a0, a1)
			{
			}
			template <class A0, class A1, class A2>
			adaptor(A0 a0, A1 a1, A2 a2) : T(a0, a1, a2)
			{
			}
		};

	} // namespace heterogenous

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_ADAPTOR_HPP

//EOF
