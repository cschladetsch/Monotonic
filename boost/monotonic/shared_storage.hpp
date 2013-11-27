// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_SHARED_STORAGE_HPP
#define BOOST_MONOTONIC_SHARED_STORAGE_HPP

#include <boost/monotonic/storage.hpp>
#include <boost/monotonic/static_storage.hpp>
#include <boost/thread/mutex.hpp>

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            template <class Region>
            struct storage_type<Region,shared_access_tag>
            {
                template <size_t N, size_t M, class Al>
                struct storage
                {
                    typedef shared_storage<storage<N,M,Al> > type;
                };
            };
        }

        /// thread-safe storage
        template <class Storage>
        struct shared_storage : storage_base
        {
        private:
            Storage store;
            mutable mutex guard;

        public:
            shared_storage()
            {
            }
            template <class Allocator>
            shared_storage(Allocator A)
                : store(A)
            {
            }
            size_t used() const
            {
                mutex::scoped_lock lock(guard);
                return store.used();
            }
            void reset()
            {
                mutex::scoped_lock lock(guard);
                store.reset();
            }
            void release()
            {
                mutex::scoped_lock lock(guard);
                store.release();
            }
            void *allocate(size_t num_bytes, size_t alignment)
            {
                mutex::scoped_lock lock(guard);
                return store.allocate(num_bytes, alignment);
            }
            void deallocate(void *ptr)
            {
                mutex::scoped_lock lock(guard);
                store.deallocate(ptr);
            }
            size_t remaining() const
            {
                mutex::scoped_lock lock(guard);
                return store.remaining();
            }
            size_t fixed_remaining() const
            {
                mutex::scoped_lock lock(guard);
                return store.fixed_remaining();
            }
            size_t max_size() const
            {
                mutex::scoped_lock lock(guard);
                return store.max_size();
            }

        };

    } // namespace monotonic

} // namespace boost

#endif // BOOST_MONOTONIC_SHARED_STORAGE_HPP

//EOF

