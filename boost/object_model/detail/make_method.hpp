// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_DETAIL_MAKE_METHOD_HPP
#define BOOST_OBJECT_MODEL_DETAIL_MAKE_METHOD_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/detail/method_pointer.hpp>
#include <boost/object_model/detail/base_type.hpp>

BOOST_OM_BEGIN

namespace detail
{
    // TODO: move these to be methods of detail::class_base<Reg>

    template <class Klass, class Reg>
    generic::method<Reg> *make_method(void (Klass::*M)(), Reg &reg)
    {
        return reg.allocator_create<method<Reg, void, Klass, boost::mpl::vector<>, false> >(M);
    }

    template <class Ret, class Klass, class Reg>
    generic::method<Reg> *make_method(Ret (Klass::*M)(), Reg &reg)
    {
        return reg.allocator_create<method<Reg, Ret, Klass, boost::mpl::vector<>, false> >(M);
    }

    template <class Klass, class Reg>
    generic::method<Reg> *make_method(void (Klass::*M)() const, Reg &reg)
    {
        return reg.allocator_create<method<Reg, void, Klass, boost::mpl::vector<>, true> >(M);
    }

    template <class Ret, class Klass, class Reg>
    generic::method<Reg> *make_method(Ret (Klass::*M)() const, Reg &reg)
    {
        return reg.allocator_create<method<Reg, Ret, Klass, boost::mpl::vector<>, true> >(M);
    }

    // ---------------------------------- arity = 1

    template <class Klass, class Reg, class A0>
    generic::method<Reg> *make_method(void (Klass::*M)(A0), Reg &reg)
    {
        return reg.allocator_create<method<Reg, void, Klass, boost::mpl::vector<A0>, false> >(M);
    }

    template <class Ret, class Klass, class Reg, class A0>
    generic::method<Reg> *make_method(Ret (Klass::*M)(A0), Reg &reg)
    {
        return reg.allocator_create<method<Reg, Ret, Klass, boost::mpl::vector<A0>, false> >(M);
    }

    template <class Klass, class Reg, class A0>
    generic::method<Reg> *make_method(void (Klass::*M)(A0) const, Reg &reg)
    {
        return reg.allocator_create<method<Reg, void, Klass, boost::mpl::vector<A0>, true> >(M);
    }

    template <class Ret, class Klass, class Reg, class A0>
    generic::method<Reg> *make_method(Ret (Klass::*M)(A0) const, Reg &reg)
    {
        return reg.allocator_create<method<Reg, Ret, Klass, boost::mpl::vector<A0>, true> >(M);
    }

    /*

    // ---------------------------------- arity = 2

    template <class Klass, class R, class A0, class A1>
    generic::method<Reg> *MakeMethod(R (Klass::*M)(A0,A1))
    {
        return new Method<R, Klass, boost::mpl::vector<A0,A1>, false>(M);
    }

    template <class Klass, class R, class A0, class A1>
    generic::method<Reg> *MakeMethod(R (Klass::*M)(A0,A1) const)
    {
        return new Method<R, Klass, boost::mpl::vector<A0,A1>, true>(M);
    }

    // ---------------------------------- arity = 3

    template <class Klass, class R, class A0, class A1, class A2>
    generic::method<Reg> *MakeMethod(R (Klass::*M)(A0,A1,A2))
    {
        return new Method<R, Klass, boost::mpl::vector<A0,A1,A2>, false>(M);
    }

    template <class Klass, class R, class A0, class A1, class A2>
    generic::method<Reg> *MakeMethod(R (Klass::*M)(A0,A1,A2) const)
    {
        return new Method<R, Klass, boost::mpl::vector<A0,A1,A2>, true>(M);
    }
*/

}
BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_DETAIL_MAKE_METHOD_HPP

//EOF
