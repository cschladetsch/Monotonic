// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_TYPE_NUMBER_HPP
#define BOOST_OBJECT_MODEL_TYPE_NUMBER_HPP

#include <boost/object_model/detail/prefix.hpp>

BOOST_OM_BEGIN

namespace type
{
    struct number
    {
        enum builtins
        {
            None,
            Any,
            Void,
            
            Object,
            
            Method,
            Property,
            Class,

            Bool,
            Int,
            Float,
            String,

            List,
            Vector,
            Map,
            Set,
        };

        typedef unsigned short value_type;
        value_type value;

        number() : value(0) { }
        number(value_type val) : value(val) { }

        friend bool operator==(number a, number b) { return a.value == b.value; }
        friend bool operator<(number a, number b) { return a.value < b.value; }
    };

}

BOOST_OM_END

BOOST_BEGIN

template <>
struct hash<BOOST_OBJECT_MODEL_NAMESPACE(type::number)>
{
    size_t operator()(BOOST_OBJECT_MODEL_NAMESPACE(type::number) num) const
    {
        return num.value;
    }
};

BOOST_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_TYPE_NUMBER_HPP

//EOF
