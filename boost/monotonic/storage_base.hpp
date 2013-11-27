// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_STORAGE_BASE_HPP
#define BOOST_MONOTONIC_STORAGE_BASE_HPP

#include <boost/monotonic/detail/prefix.hpp>

namespace boost
{
    namespace monotonic
    {
        /// base structure for different storage types
        struct storage_base
        {
            // reset the number of bytes used to zero
            virtual void reset() = 0;

            // reset(), and release all heap-based storage
            virtual void release() = 0;

            // the number of bytes to allocate, and the alignment to use
            virtual void *allocate(size_t num_bytes, size_t alignment) = 0;

            virtual void deallocate(void * ptr) = 0;
            
            virtual size_t max_size() const = 0;
            
            /// return the number of bytes used
            virtual size_t used() const = 0;

            /// return the number of bytes remaining
            virtual size_t remaining() const = 0;
        };
    
    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_STORAGE_BASE_HPP

//EOF
