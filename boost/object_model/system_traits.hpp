// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_SYSTEM_TRAITS_HPP
#define BOOST_OBJECT_MODEL_SYSTEM_TRAITS_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/string.hpp>
#include <boost/object_model/label.hpp>
#include <boost/object_model/class.hpp>

BOOST_OM_BEGIN

///
template <class Alloc
    , class Char
    , class ChTr
    , class Str
    , class Label
    , class Ident
>
struct system_traits
{
    typedef Char char_type;
    typedef Alloc allocator_type;
    typedef Str string_type;
    typedef ChTr char_traits;
    typedef Label label_type;
    typedef Ident identifier_type;
    typedef system_traits<Alloc, Char, ChTr, Str, Label, Ident> this_type;
};

template <class Label, class Al = default_allocator, class Ch = char >
struct set_label : system_traits<Al, Ch>
{
    typedef Label label_type;
};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_SYSTEM_TRAITS_HPP

//EOF
