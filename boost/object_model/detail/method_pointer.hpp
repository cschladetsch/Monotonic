// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_DETAIL_METHOD_POINTER_HPP
#define BOOST_OBJECT_MODEL_DETAIL_METHOD_POINTER_HPP

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/generic/object.hpp>
#include <boost/object_model/type/specifier.hpp>
#include <boost/object_model/object.hpp>
#include <boost/object_model/detail/base_type.hpp>

BOOST_OM_BEGIN

namespace detail
{
    template <class Reg, bool IsKonst, bool IsVoid, int Arity, class Return, class Klass, class Args>
    struct method_pointer;


    //----------------------------------------------------------- arity = 0
    struct method_pointerBase0
    {
        template <class OI>
        void AddArgs(OI)
        {
        }
    };
    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, false, false, 0, Return, Klass, Args> : method_pointerBase0
    {
        typedef Return (Klass::*method_type)();
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            stack.push_back(reg.create((reg.deref<Klass>(object).*method)()));
        }
    };

    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, true, false, 0, Return, Klass, Args> : method_pointerBase0
    {
        typedef Return (Klass::*method_type)() const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::const_object object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            stack.push_back(reg.create((reg.const_deref<Klass>(object).*method)()));
        }
    };
    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, false, true, 0, Return, Klass, Args> : method_pointerBase0
    {
        typedef Return (Klass::*method_type)();
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::mutable_object object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            (reg.const_deref<Klass>(object).*method)();
        }
    };

    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, true, true, 0, Return, Klass, Args> : method_pointerBase0
    {
        typedef Return (Klass::*method_type)() const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::const_object object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            (reg.const_deref<Klass>(object).*method)();
        }
    };

    //----------------------------------------------------------- arity = 1
    template <class Args>
    struct method_pointerBase1 : method_pointerBase0
    {
        typedef typename boost::mpl::at_c<Args, 0>::type A0;
        typedef typename detail::base_type<A0>::type P0;
        //typedef Pointer<B0> P0;
        template <class OI>
        void AddArgs(OI P)
        {
            method_pointerBase0::AddArgs(P);
            *P++ = type::make_specifier<A0>();
        }
    };
    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, false, false, 1, Return, Klass, Args> : method_pointerBase1<Args>
    {
        typedef Return (Klass::*method_type)(A0);
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::mutable_object object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            generic::object a0 = stack.pop();
            stack.push_back(reg.create((reg.deref<Klass>(object).*method)(reg.deref<P0>(a0))));
        }
    };
    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, true, false, 1, Return, Klass, Args> : method_pointerBase1<Args>
    {
        typedef Return (Klass::*method_type)(A0) const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::const_object const object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            generic::object a0 = stack.pop();
            stack.push_back(reg.create((reg.const_deref<Klass>(object).*method)(reg.deref<P0>(a0))));
        }
    };
    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, false, true, 1, Return, Klass, Args> : method_pointerBase1<Args>
    {
        typedef Return (Klass::*method_type)(A0);
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            generic::object a0 = stack.pop();
            (reg.const_deref<Klass>(object).*method)(reg.deref<P0>(a0))
        }
    };
    template <class Registry, class Return, class Klass, class Args>
    struct method_pointer<Registry, true, true, 1, Return, Klass, Args> : method_pointerBase1<Args>
    {
        typedef Return (Klass::*method_type)(A0) const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::const_object const object, typename Registry::vector_type &stack) const
        {
            Registry &reg = static_cast<Registry &>(object.get_registry());
            generic::object a0 = stack.pop();
            (reg.const_deref<Klass>(object).*method)(reg.deref<P0>(a0))
        }
    };

    /*
    //----------------------------------------------------------- arity = 2
    template <class Args>
    struct method_pointerBase2 : method_pointerBase1<Args>
    {
        typedef typename boost::mpl::at_c<Args, 1>::type A1;
        typedef typename BaseType<A1>::Type B1;
        typedef Pointer<B1> P1;
        template <class OI>
        void AddArgs(OI P)
        {
            method_pointerBase1<Args>::AddArgs(P);
            *P++ = Type::MakeType<A1>::Create();
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<false, false, 2, Return, Klass, Args> : method_pointerBase2<Args>
    {
        typedef Return (Klass::*method_type)(A0,A1);
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object &object, typename Registry::vector_type &stack) const
        {
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            stack.push_back(object.New((Deref<Klass>(object).*method)(*a0, *a1)));
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<true, false, 2, Return, Klass, Args> : method_pointerBase2<Args>
    {
        typedef Return (Klass::*method_type)(A0,A1) const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object const &object, typename Registry::vector_type &stack) const
        {
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            stack.push_back(object.New((Deref<Klass>(object).*method)(*a0, *a1)));
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<false, true, 2, Return, Klass, Args> : method_pointerBase2<Args>
    {
        typedef Return (Klass::*method_type)(A0,A1);
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object &object, typename Registry::vector_type &stack) const
        {
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            (Deref<Klass>(object).*method)(*a0, *a1);
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<true, true, 2, Return, Klass, Args> : method_pointerBase2<Args>
    {
        typedef Return (Klass::*method_type)(A0, A1) const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object const &object, typename Registry::vector_type &stack) const
        {
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            (Deref<Klass>(object).*method)(*a0, *a1);
        }
    };
    //----------------------------------------------------------- arity = 3
    template <class Args>
    struct method_pointerBase3 : method_pointerBase2<Args>
    {
        typedef typename boost::mpl::at_c<Args, 2>::type A2;
        typedef typename BaseType<A2>::Type B2;
        typedef Pointer<B2> P2;
        template <class OI>
        void AddArgs(OI P)
        {
            method_pointerBase2<Args>::AddArgs(P);
            *P++ = Type::MakeType<A2>::Create();
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<false, false, 3, Return, Klass, Args> : method_pointerBase3<Args>
    {
        typedef Return (Klass::*method_type)(A0,A1,A2);
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object &object, typename Registry::vector_type &stack) const
        {
            P2 a2 = stack.pop();
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            stack.push_back(object.New((Deref<Klass>(object).*method)(*a0, *a1, *a2)));
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<true, false, 3, Return, Klass, Args> : method_pointerBase3<Args>
    {
        typedef Return (Klass::*method_type)(A0,A1,A2) const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object const &object, typename Registry::vector_type &stack) const
        {
            P2 a2 = stack.pop();
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            stack.push_back(object.New((Deref<Klass>(object).*method)(*a0, *a1, *a2)));
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<false, true, 3, Return, Klass, Args> : method_pointerBase3<Args>
    {
        typedef Return (Klass::*method_type)(A0,A1,A2);
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object &object, typename Registry::vector_type &stack) const
        {
            P2 a2 = stack.pop();
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            (Deref<Klass>(object).*method)(*a0, *a1, *a2);
        }
    };
    template <class Return, class Klass, class Args>
    struct method_pointer<true, true, 3, Return, Klass, Args> : method_pointerBase3<Args>
    {
        typedef Return (Klass::*method_type)(A0, A1,A2) const;
        method_type method;
        method_pointer(method_type M) : method(M) { }
        void operator()(generic::object const &object, typename Registry::vector_type &stack) const
        {
            P2 a2 = stack.pop();
            P1 a1 = stack.pop();
            P0 a0 = stack.pop();
            (Deref<Klass>(object).*method)(*a0, *a1, *a2);
        }
    };

    */
    template <class Reg, class Rty, class Klass, class Args, bool Konst>
    struct make_method_pointer
    {
        typedef method_pointer<Reg, Konst, boost::is_same<void, Rty>::value, boost::mpl::size<Args>::value, Rty, Klass, Args> type;
    };
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_DETAIL_METHOD_POINTER_HPP

//EOF
