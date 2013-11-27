// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_TYPE_TRAITS_HPP
#define BOOST_OBJECT_MODEL_TYPE_TRAITS_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/type/number.hpp>
#include <boost/preprocessor/stringize.hpp>

BOOST_OM_BEGIN

namespace type
{
    template <class T, size_t N, class S = T>
    struct traits_base
    {
        typedef S Storage;
        typedef Storage storage_type;
        typedef Storage *pointer_type;
        typedef Storage &reference_type;
        typedef Storage const &const_reference_type;
    };

    struct any { };
    struct none { };
}

#ifdef BOOST_OBJECT_MODEL_MAIN
#    define BOOST_OBJECT_MODEL_DEFINE_NAME(T, NAME) \
        const char * traits<T>::name = NAME;
#else
#    define BOOST_OBJECT_MODEL_DEFINE_NAME(T, NAME)
#endif

#define BOOST_OBJECT_MODEL_TRAITS_NUM_STORE_NAME(T,N,S,NAME) \
    BOOST_OM_BEGIN \
    namespace type \
    { \
        template <> \
        struct traits<T> : traits_base<T,N,S> \
        { \
            BOOST_STATIC_CONSTANT(number::value_type, type_number = N); \
            static const char *name; \
        }; \
        BOOST_OBJECT_MODEL_DEFINE_NAME(T,NAME); \
    } \
    BOOST_OM_END

#define BOOST_OBJECT_MODEL_TRAITS_NUM_STORE(T,N,S) \
    BOOST_OBJECT_MODEL_TRAITS_NUM_STORE_NAME(T,N,S,BOOST_PP_STRINGIZE(T))

#define BOOST_OBJECT_MODEL_TRAITS_NUM(T,N) \
    BOOST_OBJECT_MODEL_TRAITS_NUM_STORE(T,N,T)

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_TYPE_TRAITS_HPP

//EOF
