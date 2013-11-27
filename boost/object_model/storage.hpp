// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_STORAGE_HPP
#define BOOST_OBJECT_MODEL_STORAGE_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/generic/storage.hpp>

BOOST_OM_BEGIN

template <class T, class Traits>
struct const_storage : generic::const_storage<Traits>
{
    typedef Traits system_traits;
    typedef type::traits<T> type_traits;
    typename type_traits::storage_type value;

    const_storage() {} 
    const_storage(typename type_traits::const_reference_type init) : value(init) { }
    typename type_traits::const_reference_type get_const_reference() const
    {
        return value;
    }
};

template <class T, class Traits>
struct storage : generic::storage<Traits>
{
    typedef Traits system_traits;
    typedef type::traits<T> type_traits;
    typename type_traits::storage_type value;
    mutable bool dirty;

    storage() : dirty(true) {} 
    storage(typename type_traits::const_reference_type init) : value(init), dirty(false) { }

    typename type_traits::const_reference_type get_const_reference() const
    {
        return value;
    }
    typename type_traits::reference_type get_reference()
    {
        dirty = true;
        return value;
    }
    bool is_dirty() const
    {
        return dirty;
    }
    void set_clean() const
    {
        dirty = false;
    }
};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_STORAGE_HPP

//EOF
