// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_GENERIC_STORAGE_HPP
#define BOOST_OBJECT_MODEL_GENERIC_STORAGE_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/dictionary.hpp>

BOOST_OM_BEGIN

namespace generic
{
    template <class Traits>
    struct const_storage : object
    {
        typedef dictionary<Traits> dictionary_type;
        typedef typename dictionary_type::label_type label_type;

    protected:
        dictionary_type dict;

    public:
        void set(label_type const &name, generic::object const &obj)
        {
            dict.set(name, obj);
        }
        generic::object get(label_type const &name) const
        {
            return dict.get(name);
        }
        bool has(label_type const &name) const
        {
            return dict.has(name);
        }
    };

    template <class Traits>
    struct storage : const_storage<Traits>
    {

    };
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_GENERIC_STORAGE_HPP

//EOF
