// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_GENERIC_BASE_HPP
#define BOOST_OBJECT_MODEL_GENERIC_BASE_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/noncopyable.hpp>

BOOST_OM_BEGIN

namespace generic
{
    /// common to all other base structures in namespace generic
    struct base
    {
        virtual ~base() { }
    };

    /// common to all other base structures in namespace generic
    struct noncopyable_base : noncopyable
    {
        virtual ~noncopyable_base() { }
    };
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_GENERIC_BASE_HPP

//EOF
