// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_EXCEPTIONS_HPP
#define BOOST_OBJECT_MODEL_EXCEPTIONS_HPP

#include <boost/object_model/detail/prefix.hpp>

BOOST_OM_BEGIN

struct empty_object
{
};

struct const_error
{
};

struct unknown_type
{
};

struct unknown_handle
{
};

struct type_mismatch
{
};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_EXCEPTIONS_HPP

//EOF
