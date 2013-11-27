// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_DETAIL_BASE_TYPE_HPP
#define BOOST_OBJECT_MODEL_DETAIL_BASE_TYPE_HPP

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/forward_declarations.hpp>

BOOST_OM_BEGIN

namespace detail
{
    template <class T>
    struct remove_const_and_reference
    {
        typedef typename boost::remove_reference<T>::type T0;
        typedef typename boost::remove_const<T0>::type type;
    };

    template <class T>
    struct remove_object_wrap
    {
        typedef T type;
    };

    template <class T>
    struct remove_object_wrap<object<T> >
    {
        typedef T type;
    };

    /// remove any reference-ness or const-ness from a C++ type, and also strip object<> from it
    template <class T>
    struct base_type
    {
        typedef typename remove_const_and_reference<T>::type T0;
        typedef typename remove_object_wrap<T0>::type type;
    };

} // namespace detail


BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_DETAIL_BASE_TYPE_HPP

//EOF
