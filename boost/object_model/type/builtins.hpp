// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_TYPE_BUILTINS_HPP
#define BOOST_OBJECT_MODEL_TYPE_BUILTINS_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/type/traits.hpp>

BOOST_OM_BEGIN

struct void_storage {};

BOOST_OM_END

BOOST_OBJECT_MODEL_TRAITS_NUM_STORE(void, boost::object_model::type::number::Void, void_storage);
BOOST_OBJECT_MODEL_TRAITS_NUM(int, boost::object_model::type::number::Int);
BOOST_OBJECT_MODEL_TRAITS_NUM(bool, boost::object_model::type::number::Bool);
BOOST_OBJECT_MODEL_TRAITS_NUM(float, boost::object_model::type::number::Float);
BOOST_OBJECT_MODEL_TRAITS_NUM(type::any, boost::object_model::type::number::Any);
BOOST_OBJECT_MODEL_TRAITS_NUM(type::none, boost::object_model::type::number::None);

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_TYPE_BUILTINS_HPP

//EOF
