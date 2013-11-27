// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_OBJECT_HPP
#define BOOST_OBJECT_MODEL_OBJECT_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/generic/object.hpp>
#include <boost/object_model/dereference.hpp>

BOOST_OM_BEGIN

/// an object with a specific type
template <>
struct object<type::any> : generic::object
{
    object() 
    {
    }

    template <class Other>
    object(object<Other> const &other) : generic::object(other)
    {
    }
    object(const generic::object &obj) : generic::object(obj)
    {
    }
    object& operator=(object const &other)
    {
        generic::object::operator=(other);
        return *this;
    }
};

/// work in progress... would like (not need) some way to allow free-standing
/// object<T>'s to be able to dereference themselves without having the owning registry
struct impl
{
    struct abstract_object
    {
        // go through the registry to get to the storage base
        virtual generic::object_base &deref() = 0;
    };


    template <class Derived, class T, class Reg>
    struct object_base
    {

    };
};

template <class T>//, class Reg = type::none>
struct object : generic::object// : impl::object_base<object<T,Reg>, T, Reg>
{
    typedef type::traits<T> traits;
    //scoped_ptr<impl::abstract_object<Reg> > ptr;
    //impl::abstract_object<Reg> *ptr;

    typedef typename traits::reference_type (*deref_fun)(generic::object &);
    typedef typename traits::const_reference_type (*const_deref_fun)(const generic::object &);

private:
    deref_fun deref;
    const_deref_fun const_deref;

public:
    object() : deref(0), const_deref(0) {}

    object(const object<type::any> &obj)
    {
        *this = obj;
    }

    object(const generic::object &obj, deref_fun d, const_deref_fun c) 
        : deref(d), const_deref(c)
    {
        *this = obj;
    }

    object& operator=(object const &other)
    {
        generic::object::operator=(other);
        return *this;
    }

    object& operator=(object<type::any> const &other)
    {
        if (!other.is_type<T>())
            throw type_mismatch();
        generic::object::operator=(other);
        return *this;
    }

    typename traits::reference_type get_reference()
    {
        if (!deref)
            throw empty_object();
        return deref(*this);
    }

    typename traits::reference_type operator*()
    {
        return get_reference();
    }

    typename traits::pointer_type operator->()
    {
        return &get_reference();
    }

    template <class Label>
    void set(const Label &label, generic::object obj)
    {
        //impl->setter(*this, label, obj);
    }

};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_OBJECT_HPP

//EOF
