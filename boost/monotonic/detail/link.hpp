// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_ALLOCATOR_DETAIL_LINK_HPP
#define BOOST_MONOTONIC_ALLOCATOR_DETAIL_LINK_HPP

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            /// a link in the chain of heap-based memory buffers used by a storage<> structure
            template <class Al>
            struct Link// : storage_base
            {
                typedef Al CharAllocator;

            private:
                size_t capacity, cursor;
                char *buffer;
                CharAllocator alloc;

            public:
                Link() : capacity(0), cursor(0), buffer(0)
                {
                }
                template <class Al2>
                Link(Al2 const &al, size_t cap)
                    : capacity(cap), cursor(0), buffer(0)
                    , alloc(typename Al2::template rebind<char>::other(al))
                {
                    buffer = alloc.allocate(capacity);
                    if (buffer == 0)
                        capacity = 0;
                }
                size_t max_size() const
                {
                    return capacity;
                }
                size_t remaining() const
                {
                    return capacity - cursor;
                }
                size_t get_cursor() const
                {
                    return cursor;
                }
                void set_cursor(size_t C)
                {
                    cursor = C;
                }
                void reset()
                {
                    cursor = 0;
                }
                void release()
                {
                    alloc.deallocate(buffer, 1);
                }
                size_t used() const
                {
                    return cursor;
                }
                inline void *allocate(size_t num_bytes, size_t alignment)
                {
                    size_t extra = cursor & (alignment - 1);
                    if (extra > 0)
                        extra = alignment - extra;
                    size_t required = num_bytes + extra;
                    if (capacity - cursor < required)
                        return 0;
                    char *ptr = buffer + cursor;
                    cursor += required;
                    return ptr + extra;
                }
                friend bool operator<(Link const &A, Link const &B)
                {
                    return A.remaining() < B.remaining();
                }
            };

        } // namespace detail

    } // namespace monotonic

} // namespace boost

#endif // BOOST_MONOTONIC_ALLOCATOR_DETAIL_LINK_HPP

//EOF
