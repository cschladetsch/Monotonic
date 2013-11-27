// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_FIXED_STORAGE_HPP
#define BOOST_MONOTONIC_FIXED_STORAGE_HPP

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/assert.hpp>
#include <boost/array.hpp>
#include <boost/monotonic/forward_declarations.hpp>
#include <boost/monotonic/exceptions.hpp>
#include <boost/monotonic/storage_base.hpp>
#include <boost/type_traits/is_unsigned.hpp>

//#define BOOST_MONOTONIC_STORAGE_EARLY_OUT

namespace boost
{
    namespace monotonic
    {
        /// storage for an allocator that is on the stack or heap
        template <size_t InlineSize>
        struct fixed_storage : storage_base
        {
            typedef boost::array<char, InlineSize> Buffer;

        private:
            Buffer buffer;            ///< the storage
#ifdef BOOST_MONOTONIC_STORAGE_EARLY_OUT
            /// if `full` is true, buffer has reached its capacity; used for early-out on allocation. 
            /// this maybe should be removed, because although it may speed up allocation
            /// a little when the buffer is full, it also slows it down a little when it is not
            bool full;                
#endif
            size_t cursor;            ///< pointer to current index within storage for next allocation
#ifndef NDEBUG
            size_t num_allocations;
#endif
        public:
            fixed_storage() 
                : cursor(0)
#ifdef BOOST_MONOTONIC_STORAGE_EARLY_OUT
                , full(false)
#endif
#ifndef NDEBUG
                , num_allocations(0)
#endif
            {
            }

            Buffer const &get_buffer()  const
            {
                return buffer;
            }
            const char *begin() const
            {
                return &buffer[0];
            }
            const char *end() const
            {
                return &buffer[InlineSize - 1];
            }
            void reset()
            {
                cursor = 0;
#ifdef BOOST_MONOTONIC_STORAGE_EARLY_OUT
                full = false;
#endif
#ifndef NDEBUG
                num_allocations = 0;
#endif
            }
            void release()
            {
                reset();
            }

            size_t get_cursor() const
            {
                return cursor;
            }

            void set_cursor(size_t c)
            {
                cursor = c;
            }

            // testing performance against a fixed-size alignment
            BOOST_STATIC_CONSTANT(size_t, alignment = 64);

            struct AllocationAttempt
            {
                bool able;
                size_t required;
                size_t extra;
                AllocationAttempt() : able(false) { }
                AllocationAttempt(size_t R, size_t E) : able(true), required(R), extra(E) { }
            };

            AllocationAttempt TryAllocation(size_t num_bytes, size_t alignment)
            {
                size_t extra = cursor & (alignment - 1);    // assumes alignment is a power of 2!
                if (extra > 0)
                    extra = alignment - extra;
                size_t required = num_bytes + extra;
                if (cursor + required > InlineSize)
                    return AllocationAttempt();
                return AllocationAttempt(required, extra);
            }

            void *MakeAllocation(AllocationAttempt const &ad)
            {
                char *ptr = &buffer[cursor];
                cursor += ad.required;
                return ptr + ad.extra;
            }
            
        public:
            /// allocate storage, given alignment requirement
            void *allocate(size_t num_bytes, size_t alignment)
            {
#ifdef BOOST_MONOTONIC_STORAGE_EARLY_OUT
                if (full)
                    return 0;
#endif

                size_t extra = cursor & (alignment - 1);
                if (extra > 0)
                    extra = alignment - extra;
                size_t required = num_bytes + extra;
                if (cursor + required > InlineSize)
                {
#ifdef BOOST_MONOTONIC_STORAGE_EARLY_OUT
                    full = InlineSize - cursor < 16;
#endif
                    return 0;
                }
#ifndef NDEBUG
                ++num_allocations;
#endif
                char *ptr = &buffer[cursor];
                cursor += required;
                return ptr + extra;
            }

            void deallocate(void *ptr)
            {
                // do nothing
            }

            size_t max_size() const
            {
                return InlineSize;
            }

            size_t remaining() const
            {
                return InlineSize - cursor;
            }

            size_t used() const
            {
                return cursor;
            }

#ifndef NDEBUG
            size_t get_num_allocs() const
            {
                return num_allocations;
            }
#endif
            //-----------------------------------------------------------------


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

        };
    
    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_FIXED_STORAGE_HPP

//EOF
