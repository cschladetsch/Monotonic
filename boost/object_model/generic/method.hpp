// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_GENERIC_METHOD_HPP
#define BOOST_OBJECT_MODEL_GENERIC_METHOD_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/label.hpp>
#include <boost/object_model/type/signature.hpp>
#include <boost/object_model/containers/vector.hpp>

BOOST_OM_BEGIN

namespace generic
{
    /// common base for all specific methods
    template <class Registry>
    struct method
    {
    private:
        typename Registry::label_type name;
        type::signature sig;

    public:

        virtual void invoke(object &servant, typename Registry::vector_type &args) const = 0;

        template <class Traits>
        typename Traits::string_type to_string(const Registry &reg) const
        {
            typename Traits::string_type s;
            return s;
        }
    };
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_GENERIC_METHOD_HPP

//EOF
