// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_SHARED_ALLOCATOR_HPP
#define BOOST_MONOTONIC_SHARED_ALLOCATOR_HPP

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/shared_storage.hpp>

namespace boost
{
    namespace monotonic
    {
        template <class Region> 
        struct shared_allocator<void, Region>
        {
            typedef void* pointer;
            typedef const void* const_pointer;

            typedef void value_type;
            template <class U> 
            struct rebind 
            { 
                typedef shared_allocator<U, Region> other; 
            };
        };

        template <class T, class Region>
        struct shared_allocator : allocator<T, Region, shared_access_tag>
        {
            typedef allocator<T, Region, shared_access_tag> Parent;
            using typename Parent::size_type;
            using typename Parent::difference_type;
            using typename Parent::pointer;
            using typename Parent::const_pointer;
            using typename Parent::reference;
            using typename Parent::const_reference;
            using typename Parent::value_type;

            template <class U> 
            struct rebind 
            { 
                typedef shared_allocator<U, Region> other; 
            };

            shared_allocator() throw() 
                : Parent(boost::monotonic::static_storage<Region,shared_access_tag>::get_storage()) { }

        public:
            shared_allocator(storage_base &store) throw() 
                : Parent(store) { }

        public:
            shared_allocator(const shared_allocator& alloc) throw() 
                : Parent(alloc) { }

            template <class U> 
            shared_allocator(const shared_allocator<U, Region> &alloc) throw()
                : Parent(alloc) { }

            friend bool operator==(shared_allocator<T,Region> const &A, shared_allocator<T,Region> const &B) 
            { 
                return static_cast<Parent const &>(A) == static_cast<Parent const &>(B);
            }

            friend bool operator!=(shared_allocator<T,Region> const &A, shared_allocator<T,Region> const &B) 
            { 
                return static_cast<Parent const &>(A) != static_cast<Parent const &>(B);
            }
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_SHARED_ALLOCATOR_HPP

//EOF

