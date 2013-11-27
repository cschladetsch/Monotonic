// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_CONFIG_HPP
#include <boost/monotonic/config.hpp>
#endif

#ifdef BOOST_MSVC
#    pragma warning(push)
#    pragma warning(disable:4127) // conditional expression is constant
#    pragma warning(disable:4702) // unreachable code
#    pragma warning(disable:4996) // Function call with parameters that may be unsafe
#endif

//EOF
