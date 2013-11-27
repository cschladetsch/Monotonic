// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_STRING_STREAM_HPP
#define BOOST_OBJECT_MODEL_STRING_STREAM_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/string.hpp>

BOOST_OM_BEGIN

template <class Alloc = default_allocator, class Ch = char, class Tr = std::char_traits<Ch> >
struct string_stream
{
    typedef string<Alloc,Ch,Tr> string_type;
    typedef std::basic_stringstream<Ch, Tr, Alloc> string_stream_type;

private:
    string_stream_type stream;

public:
    string_type str() const
    {
        return stream.str();
    }
};

template <class Al, class Ch, class Tr, class Ty>
string_stream<Al,Ch,Tr> &operator<<(string_stream<Al,Ch,Tr> &stream, const Ty &val)
{
    return stream << val;
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_STRING_STREAM_HPP

//EOF
