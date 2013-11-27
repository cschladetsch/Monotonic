// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_CLASS_HPP
#define BOOST_OBJECT_MODEL_CLASS_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/detail/allocator.hpp>
#include <boost/object_model/generic/class.hpp>
#include <boost/object_model/detail/class_base.hpp>

BOOST_OM_BEGIN

template <class T, class Registry>
struct klass : detail::klass_base<typename Registry>
{
    typedef typename Registry::traits_type system_traits;
    typedef detail::klass_base<Registry> klass_base_type;
    typedef typename system_traits::label_type label_type;
    typedef typename Registry::rebind_storage<T>::type storage_type;
    typedef typename system_traits::allocator_type::template rebind<storage_type>::other allocator_type;
    typedef type::traits<T> traits;

private:
    Registry &factory;
    mutable allocator_type allocator;

public:
    klass(Registry &reg)
        : klass_base_type(reg, traits::name, traits::type_number), factory(reg), allocator(reg.get_allocator()) { }

    generic::object &create() const
    {
        storage_type *store = allocator.allocate(1);
        //allocator.construct(store);
        new (store) storage_type();
        store->construct(factory, *this, factory.get_next_handle());
        return *store;
    }

    storage_type &create(typename traits::const_reference_type init) const
    {
        storage_type *store = allocator.allocate(1);
        //allocator.construct(store);
        new (store) storage_type(init);
        store->construct(factory, *this, factory.get_next_handle());
        return *store;
    }

    void destroy(generic::object &obj) const
    {
        storage_type *store = &static_cast<storage_type &>(obj);
        allocator.destroy(store);
        allocator.deallocate(store, 1);
    }

};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_CLASS_HPP

//EOF
