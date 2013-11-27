// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_BUILDER_HPP
#define BOOST_OBJECT_MODEL_BUILDER_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/class.hpp>
#include <boost/object_model/method.hpp>

BOOST_OM_BEGIN

template <class T, class Reg>
struct builder
{
    typedef Reg registry_type;
    typedef type::traits<T> type_traits;
    typedef typename Reg::traits_type system_traits;
    typedef typename registry_type::template rebind_klass<T>::type class_type;

private:
    class_type *my_klass;

public:
    builder(registry_type &reg)
    {
        methods.my_klass = methods.fields.my_klass = my_klass = reg.register_class<T>();
        methods.factory = methods.fields.factory = &reg;
    }
    struct methods_type
    {
        struct fields_type
        {
            template <class Field>
            fields_type &operator()(const char *name, Field field)
            {
                return *this;
            }
            registry_type *factory;
            class_type *my_klass;
        } fields;

        template <class Method>
        methods_type &operator()(const char *name, Method method)
        {
            my_klass->add_method(name, detail::make_method(method, *factory));
            return *this;
        }
        registry_type *factory;
        class_type *my_klass;
    } methods;
};

template <class T, class Registry>
builder<T,Registry> class_builder(Registry &reg)
{
    return builder<T,Registry>(reg);
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_BUILDER_HPP

//EOF
