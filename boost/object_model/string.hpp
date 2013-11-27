// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_STRING_HPP
#define BOOST_OBJECT_MODEL_STRING_HPP

#include <string>
#include <boost/object_model/detail/prefix.hpp>

BOOST_OM_BEGIN

template <class Alloc, class Ch, class Tr>
struct string
{
    typedef std::basic_string<Ch, Tr, Alloc> implementation;
    typedef typename implementation::value_type value_type;
    typedef typename implementation::iterator iterator;
    typedef typename implementation::const_iterator const_iterator;
    typedef Alloc allocator_type;

private:
    implementation impl;

public:

    string() { }
    string(const value_type *text) : impl(text) { }
    string &operator=(const value_type *text)
    {
        impl = text;
        return *this;
    }
    const value_type *c_str() const
    {
        return impl.c_str();
    }

    friend bool operator==(string const &a, string const &b)
    {
        return a.impl == b.impl;
    }
    friend bool operator<(string const &a, string const &b)
    {
        return a.impl < b.impl;
    }
};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_STRING_HPP

//EOF
