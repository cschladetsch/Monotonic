// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_GENERIC_REGISTRY_HPP
#define BOOST_OBJECT_MODEL_GENERIC_REGISTRY_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/forward_declarations.hpp>
#include <boost/object_model/handle.hpp>
//#include <boost/object_model/storage.hpp>

BOOST_OM_BEGIN

namespace generic
{
    struct registry : base
    {
    public:

        virtual handle get_next_handle() = 0;
        virtual klass const *get_class(type::number) const = 0;
        virtual bool exists(handle) const = 0;

        virtual object_base &get_storage(handle) const = 0;

    };
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_GENERIC_REGISTRY_HPP

//EOF
