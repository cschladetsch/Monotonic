// Copyright (C) 2009-2020 Christian@Schladetsch.com
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_RECLAIMABLE_STORAGE_HPP
#define BOOST_MONOTONIC_RECLAIMABLE_STORAGE_HPP

#include <algorithm>

#include <boost/unordered/unordered_set.hpp>

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/forward_declarations.hpp>

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            template <>
            struct storage_type<heap_region_tag, default_access_tag>
            {
                template <size_t N, size_t M, class Al>
                struct storage
                {
                    typedef reclaimable_storage<N,M,Al> type;
                };
            };

        }

        /// conventional, reclaimable storage
        ///
        /// this is really a long way around to using new and delete, however it
        /// also keeps track of the allocations made so they can be released.
        template <size_t InlineSize, size_t MinHeapIncrement, class Al>
        struct reclaimable_storage : storage_base
        {
            typedef reclaimable_storage<InlineSize, MinHeapIncrement, Al> This;
            typedef Al Allocator;
            typedef typename Allocator::template rebind<char>::other CharAllocator;

            /* this has to go to an allocator
            struct AllocationBase
            {
                void *ptr;
                AllocationBase(void *P = 0) : ptr(P) { }
                virtual void destroy() = 0;
            };
            template <class T>
            struct Allocation : AllocationBase
            {
                Allocation(T *P) : AllocationBase(P) { }
                void destroy()
                {
                    static_cast<T *>(this->AllocationBase::ptr)->~T();
                }
            };
            template <class T, class Alloc>
            static Allocation<T> MakeAllocation(T *ptr, Alloc al)
            {
                typename Alloc::template rebind<Allocation<T> >::other(al) allocator;
                Allocation<T> *allocation = allocator.allocate(1);
                allocator.construct(allocation, ptr);
                return allocation;
            }*/

            /* this has to go to a tracking_allocator
            struct Allocation
            {
                void *ptr;
                size_t size;
                Allocation(void *P = 0, size_t N = 0) : ptr(P), size(N) { }
                void *get_pointer() const { return ptr; }
                size_t get_size() const { return size; }
            };
            struct AllocHash
            {
                size_t operator()(Allocation const &alloc) const
                {
                    return reinterpret_cast<size_t>(alloc.ptr);
                }
            };
            struct AllocLess
            {
                bool operator()(Allocation const &A, Allocation const &B) const
                {
                    return A.ptr < B.ptr;
                }
            };
            typedef boost::unordered_set<
                Allocation
                , AllocHash
                , AllocLess
                , Allocator> 
            Allocations;
            */

        private:
            CharAllocator alloc;

        public:
            reclaimable_storage()
            {
            }
            reclaimable_storage(Allocator const &A)
                : alloc(A)
            {
            }
            ~reclaimable_storage()
            {
                release();
            }

            void reset()
            {
            }

            void release()
            {
            }

            void *allocate(size_t num_bytes, size_t /*alignment*/ = 1)
            {
                return alloc.allocate(num_bytes);
            }

            void deallocate(void *ptr)
            {
                alloc.deallocate((char *)ptr, 1);
            }

            size_t max_size() const
            {
                return (std::numeric_limits<size_t>::max)();
            }

            size_t remaining() const
            {
                return max_size();
            }

            size_t used() const
            {
                BOOST_ASSERT(0);
                return 0;
            }

            // ------------------------------------------------------------------------

            template <class Ty>
            Ty *uninitialised_create()
            {
                return reinterpret_cast<Ty *>(allocate_bytes<sizeof(Ty)>());
            }

            template <class Ty>
            Ty &create()
            {
                Ty *ptr = uninitialised_create<Ty>();
                construct(ptr, boost::is_pod<Ty>());
                return *ptr;
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
            Ty &create(Ty const &X)
            {
                Ty *ptr = uninitialised_create<Ty>();
                new (ptr) Ty(X);
                return *ptr;
            }

            template <class Ty>
            void destroy(Ty &object)
            {
                object.~Ty();
                deallocate(&object, 1);
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
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_RECLAIMABLE_STORAGE_HPP

//EOF
