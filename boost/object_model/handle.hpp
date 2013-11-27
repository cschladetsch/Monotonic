// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_HANDLE_HPP
#define BOOST_OBJECT_MODEL_HANDLE_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/functional/hash_fwd.hpp>

BOOST_OM_BEGIN

/// a handle is a numeric identifier for a system object
struct handle
{
    typedef unsigned value_type;

private:
    value_type value;

public:
    handle() : value(0) {}
    handle(value_type val) : value(val) { }
    value_type get_value() const { return value; }

    friend bool operator==(handle a, handle b) { return a.value == b.value; }
    friend bool operator<(handle a, handle b) { return a.value < b.value; }
};

BOOST_OM_END

BOOST_BEGIN

template <>
struct hash<BOOST_OBJECT_MODEL_NAMESPACE(handle)>
{
    size_t operator()(BOOST_OBJECT_MODEL_NAMESPACE(handle) num) const
    {
        return num.get_value();
    }
};

BOOST_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_HANDLE_HPP

//EOF
