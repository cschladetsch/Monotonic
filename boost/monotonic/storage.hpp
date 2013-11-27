// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_STORAGE_HPP
#define BOOST_MONOTONIC_STORAGE_HPP

#include <boost/foreach.hpp>
#include <algorithm>
#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/fixed_storage.hpp>
#include <boost/monotonic/detail/pool.hpp>
#include <boost/monotonic/detail/link.hpp>

namespace boost
{
    namespace monotonic
    {
        /// storage that spans the stack/heap boundary.
        ///
        /// allocation requests first use inline fixed_storage of InlineSize bytes.
        /// once that is exhausted, later requests are serviced from the heap.
        ///
        /// all allocations remain valid at all times.
        template <size_t InlineSize, size_t MinHeapIncrement, class Alloc>
        struct storage : storage_base
        {
            BOOST_STATIC_CONSTANT(size_t, NumPools = 8);
            BOOST_STATIC_CONSTANT(size_t, ChunkShift = 4);
            BOOST_STATIC_CONSTANT(size_t, ChunkSize = 1 << ChunkShift);

            typedef storage<InlineSize, MinHeapIncrement, Alloc> This;
            typedef Alloc Allocator;
            typedef typename Allocator::template rebind<char>::other CharAllocator;
            typedef detail::Link<CharAllocator> Link;
            typedef detail::Pool Pool;
            // allocations are always made from the stack, or from a pool the first link in the chain
            typedef std::vector<Link, Alloc> Chain;                    
            typedef boost::array<Pool, NumPools> Pools;
            typedef fixed_storage<InlineSize> FixedStorage;    // the inline fixed-sized storage which may be on the stack

        private:
            FixedStorage fixed;    // the inline fixed-sized storage which may be on the stack
            Chain chain;                        // heap-based storage
            Allocator alloc;                    // allocator for heap-based storage
            Pools pools;                        // pools of same-sized chunks

            void create_pools()
            {
                for (size_t n = 0; n < NumPools; ++n)
                {
                    pools[n] = Pool(n*ChunkSize);
                }
            }
        protected:
            template <size_t,size_t,class> friend struct stack;

        public:
            storage()
            {
                create_pools();
            }
            storage(Allocator const &A)
                : alloc(A)
            {
                create_pools();
            }
            ~storage()
            {
                release();
            }

            void reset()
            {
                fixed.reset();
                BOOST_FOREACH(Pool&pool, pools)
                {
                    pool.reset();
                }
                BOOST_FOREACH(Link &link, chain)
                {
                    link.reset();
                }
            }

            void release()
            {
                reset();
                BOOST_FOREACH(Link &link, chain)
                {
                    link.release();
                }
                chain.clear();
            }
        public:
            void *allocate(size_t num_bytes, size_t alignment = 1)
            {
                size_t pool = (ChunkSize + num_bytes) >> ChunkShift;
                if (pool < NumPools)
                {
                    if (void *ptr = from_pool(pool, num_bytes, alignment))
                        return ptr;
                }
                if (void *ptr = from_fixed(num_bytes, alignment))
                    return ptr;
                return from_heap(num_bytes, alignment);
            }

        private:
            friend struct detail::Pool;

            void *from_pool(size_t bucket, size_t num_bytes, size_t alignment)
            {
                return pools[bucket].allocate(*this);
            }
            
            void *from_fixed(size_t num_bytes, size_t alignment)
            {
                return fixed.allocate(num_bytes, alignment);
            }
            
            void *from_heap(size_t num_bytes, size_t alignment)
            {
                if (MinHeapIncrement == 0)
                    return 0;
                if (!chain.empty())
                {
                    if (void *ptr = chain.front().allocate(num_bytes, alignment))
                    {
                        return ptr;
                    }
                    std::make_heap(chain.begin(), chain.end());
                    if (void *ptr = chain.front().allocate(num_bytes, alignment))
                    {
                        return ptr;
                    }
                }
                AddLink((std::max)(MinHeapIncrement, num_bytes*2));
                void *ptr = chain.front().allocate(num_bytes, alignment);
                if (ptr == 0)
                    throw std::bad_alloc();
                return ptr;
            }

        public:
            void deallocate(void *ptr)
            {
                // do nothing
            }

            size_t max_size() const
            {
                return (std::numeric_limits<size_t>::max)();
            }

            size_t fixed_remaining() const
            {
                return fixed.remaining();
            }

            size_t remaining() const
            {
                return max_size();
            }

            size_t fixed_used() const
            {
                return fixed.used();
            }

            size_t heap_used() const
            {
                size_t count = 0;
                BOOST_FOREACH(Link const &link, chain)
                    count += link.used();
                return count;
            }

            size_t used() const
            {
                return fixed_used() + heap_used();
            }

            size_t num_links() const
            {
                return chain.size();
            }

            // ------------------------------------------------------------------------

            template <class Ty>
            Ty *uninitialised_create()
            {
                return reinterpret_cast<Ty *>(allocate_bytes<sizeof(Ty)>());
            }

            template <class Ty>
            void construct(Ty *ptr, const boost::true_type& /*is_pod*/)
            {
                // do nothing
            }

            template <class Ty>
            void construct(Ty *ptr, const boost::false_type&)
            {
                new (ptr) Ty();
            }

            template <class Ty>
            Ty &create()
            {
                Ty *ptr = uninitialised_create<Ty>();
                construct(ptr, boost::is_pod<Ty>());
                return *ptr;
            }

            template <class Ty, class A0>
            Ty &create(A0 a0)
            {
                Ty *ptr = uninitialised_create<Ty>();
                new (ptr) Ty(a0);
                return *ptr;
            }

            template <class Ty, class A0, class A1>
            Ty &create(A0 a0, A1 a1)
            {
                Ty *ptr = uninitialised_create<Ty>();
                new (ptr) Ty(a0, a1);
                return *ptr;
            }

            template <class Ty>
            void destroy(Ty &object)
            {
                object.~Ty();
            }

            template <class Ty>
            void destroy(Ty const &object)
            {
                destroy(const_cast<Ty &>(object));
            }

            template <size_t N>
            char *allocate_bytes()
            {
                return allocate_bytes(N, boost::aligned_storage<N>::alignment);
            }

            char *allocate_bytes(size_t num_bytes, size_t alignment = 1)
            {
                return reinterpret_cast<char *>(allocate(num_bytes, alignment));
            }

            size_t get_cursor() const
            {
                return fixed.get_cursor();
            }
            void set_cursor(size_t n)
            {
                fixed.set_cursor(n);
            }

        private:
            void AddLink(size_t size)
            {
                chain.push_back(Link(alloc, size));
                std::make_heap(chain.begin(), chain.end());
            }
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_STORAGE_HPP

//EOF
