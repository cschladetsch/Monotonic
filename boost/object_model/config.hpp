// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_CONFIG_HPP
#define BOOST_OBJECT_MODEL_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/functional/hash_fwd.hpp>

#define BOOST_OBJECT_MODEL_NAMESPACE_NAME object_model

#define BOOST_BEGIN namespace boost {
#define BOOST_END }

#define BOOST_OM_BEGIN BOOST_BEGIN namespace BOOST_OBJECT_MODEL_NAMESPACE_NAME {
#define BOOST_OM_END } BOOST_END
#define BOOST_OBJECT_MODEL_NAMESPACE(name) ::boost::BOOST_OBJECT_MODEL_NAMESPACE_NAME::name

BOOST_OM_BEGIN

typedef std::allocator<char> default_allocator;

BOOST_OM_END

#endif // BOOST_OBJECT_MODEL_CONFIG_HPP

//EOF
