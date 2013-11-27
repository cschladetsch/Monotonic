// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_METHOD_HPP
#define BOOST_OBJECT_MODEL_METHOD_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/generic/method.hpp>
#include <boost/object_model/detail/make_method.hpp>

BOOST_OM_BEGIN

template <
    class Reg        // the registry type
    , class Rty        // return type
    , class Klass    // servant type
    , class Args    // argument list
    , bool Konst    // constness
>
struct method : generic::method<Reg>, detail::make_method_pointer<Reg, Rty, Klass, Args, Konst>::type
{
    typedef typename detail::make_method_pointer<Reg, Rty, Klass, Args, Konst>::type Parent;
    method(typename Parent::method_type M) : Parent(M) 
    { 
        //signature.return_type = Type::MakeType<Rty>::Create();//Type::Traits<typename BaseType<Rty>::Type>::TypeNumber;
        //signature.class_type = Type::Traits<Klass>::TypeNumber;
        //signature.konst = Konst;
        //Parent::AddArgs(std::back_inserter(signature.arguments));

    }
    void invoke(generic::object &servant, typename Reg::vector_type &stack) const
    {
        (*this)(servant, stack);
    }
};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_METHOD_HPP

//EOF
