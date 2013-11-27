// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_GENERIC_CLASS_HPP
#define BOOST_OBJECT_MODEL_GENERIC_CLASS_HPP

#include <map>
#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/forward_declarations.hpp>
#include <boost/object_model/type/number.hpp>
#include <boost/object_model/generic/base.hpp>
#include <boost/object_model/label.hpp>

BOOST_OM_BEGIN

namespace generic
{
    typedef const char *class_name;

    struct klass : base
    {
    private:
        type::number type_number;
        class_name name;

    public:
        klass(class_name ident, type::number num)
            : type_number(num), name(ident) { }

        type::number get_type_number() const { return type_number; }
        class_name get_name() const { return name; }

        virtual object &create() const = 0;
        virtual void destroy(object &) const = 0;

        //virtual bool has_method(object &) const = 0;

        //virtual const_object get_property(const label&, const_object &owner) const = 0;
        //virtual object get_property(const label&, object &owner) const = 0;
    };
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_GENERIC_CLASS_HPP

//EOF
