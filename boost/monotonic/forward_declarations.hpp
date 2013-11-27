// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_FORWARD_DECLARATIONS_HPP
#define BOOST_MONOTONIC_FORWARD_DECLARATIONS_HPP

#include <utility>
#include <limits>
#include <vector>
//#include <boost/foreach.hpp>

#include <boost/monotonic/detail/prefix.hpp>

namespace boost
{
    namespace monotonic
    {

        // fixed-sized storage for an allocator that is on the stack or heap
        template <size_t InlineSize = DefaultSizes::InlineSize>
        struct fixed_storage;

        // storage that can span the stack/heap boundary.
        //
        // allocation requests first use inline fixed_storage of InlineSize bytes.
        // once that is exhausted, later requests are serviced from the heap.
        //
        // all allocations remain valid until the storage goes out of scope.
        template <
            size_t InlineSize = DefaultSizes::InlineSize
            , size_t MinHeapIncrement = DefaultSizes::MinHeapIncrement
            , class Al = default_allocator >
        struct storage;

        // a fixed-size general stack
        template <
            size_t InlineSize = DefaultSizes::InlineSize>
        struct fixed_stack;

        // a growable stack-like object that starts on the stack and can grow to the heap
        template <
            size_t InlineSize = DefaultSizes::InlineSize
            , size_t MinHeapIncrement = DefaultSizes::MinHeapIncrement
            , class Al = default_allocator >
        struct stack;

        // tags for different storage regions
        struct default_region_tag { };
        struct heap_region_tag { };

        // tags for different access types
        struct default_access_tag { };
        struct shared_access_tag { };
        struct thread_local_access_tag { };

        // selector to create a storage type given accessor
        namespace detail
        {
            template <class Region, class Access>
            struct storage_type;
        }
    
        // a RIIA structure for accessing and releasing storage
        template <class Region = default_region_tag, class Access = default_access_tag>
        struct local;

        // conventional, reclaimable storage
        template <size_t InlineSize = 0, size_t MinHeapIncrement = 0, class Al = default_allocator>
        struct reclaimable_storage;
            
        // thread-safe storage
        template <class Storage>
        struct shared_storage;

        // thread-local storage
        template <size_t InlineSize = DefaultSizes::InlineSize
            , size_t MinHeapIncrement = DefaultSizes::MinHeapIncrement
            , class Al = default_allocator >
        struct thread_local_storage;

        // a globally available storage buffer
        template <class Region = default_region_tag
            , class Access = default_access_tag
            , size_t InlineSize = DefaultSizes::/*Static*/InlineSize
            , size_t MinHeapIncrement = DefaultSizes::/*Static*/MinHeapIncrement
            , class Al = default_allocator >
        struct static_storage;

        /// common to other monotonic allocators for type T of type Derived
        template <class T, class Derived>
        struct allocator_base;

        // a monotonic allocator has a storage buffer and a no-op deallocate() method
        //
        // each region uses independent storage
        //
        // each region is also factored over which access to use: global, shared, or thread-local storage
        template <class T, class Region = default_region_tag, class Access = default_access_tag> 
        struct allocator;

        // a monotonic shared_allocator has a shared storage buffer and a no-op deallocate() method
        // defaults to use static_storage_base<..., shared_storage>
        template <class T, class Region = default_region_tag> 
        struct shared_allocator;
    
        // a monotonic thread_local_allocator has a shared storage buffer and a no-op deallocate() method
        // defaults to use static_storage_base<..., thread_local_storage>
        template <class T, class Region = default_region_tag>
        struct thread_local_allocator;

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_FORWARD_DECLARATIONS_HPP

//EOF
