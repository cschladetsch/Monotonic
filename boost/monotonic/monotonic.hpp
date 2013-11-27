// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_MONOTONIC_HPP
#define BOOST_MONOTONIC_MONOTONIC_HPP

#include <boost/monotonic/detail/prefix.hpp>

#ifdef BOOST_MONOTONIC_THREADS
#    include <boost/monotonic/shared_allocator.hpp>
//TODO #    include <boost/monotonic/thread_local_allocator.hpp>
#endif

#include <boost/monotonic/containers/string.hpp>
#include <boost/monotonic/containers/vector.hpp>
#include <boost/monotonic/containers/list.hpp>
#include <boost/monotonic/containers/set.hpp>
#include <boost/monotonic/containers/map.hpp>
#include <boost/monotonic/containers/deque.hpp>
#include <boost/monotonic/containers/chain.hpp>

namespace boost
{
    namespace monotonic
    {

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_MONOTONIC_HPP

//EOF
