// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_THREAD_LOCAL_STORAGE_HPP
#define BOOST_MONOTONIC_THREAD_LOCAL_STORAGE_HPP

#include <boost/thread.hpp>

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/storage.hpp>
#include <boost/monotonic/static_storage.hpp>

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            template <class Region>
            struct storage_type<Region, thread_local_access_tag>
            {
                template <size_t N, size_t M, class Al>
                struct storage
                {
                    typedef thread_local_storage<N,M,Al> type;
                };
            };
        }

        /// thread-local storage
        template <size_t InlineSize, size_t MinHeapSize, class Al>
        struct thread_local_storage : storage_base
        {
            typedef storage<InlineSize, MinHeapSize, Al> Storage;
            typedef boost::thread_specific_ptr<Storage> TLS_Storage;
            typedef thread_local_storage<InlineSize, MinHeapSize, Al> This;

        private:
            Storage store;
            TLS_Storage tls_store;
            static void no_delete(Storage *) { }

        public:
            thread_local_storage() 
                : tls_store(&This::no_delete)
            {
                tls_store.reset(&store);
            }
            size_t used() const
            {
                return tls_store->used();
            }
            void reset()
            {
                tls_store->reset();
            }
            void release()
            {
                tls_store->release();
            }
            void *allocate(size_t num_bytes, size_t alignment)
            {
                return tls_store->allocate(num_bytes, alignment);
            }
            size_t remaining() const
            {
                return tls_store->remaining();
            }
            size_t fixed_remaining() const
            {
                return tls_store->fixed_remaining();
            }
            size_t max_size() const
            {
                return tls_store->max_size();
            }
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_THREAD_LOCAL_STORAGE_HPP

//EOF

