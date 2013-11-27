// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_DETAIL_POOL_HPP
#define BOOST_MONOTONIC_DETAIL_POOL_HPP

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            /// a pool of same-sized chunks in a storage block
            struct Pool
            {
                char *first, *next, *last;
                size_t bucket_size;
                Pool() : first(0), next(0), last(0), bucket_size(0)
                {
                }
                Pool(size_t bs) : first(0), next(0), last(0), bucket_size(bs)
                {
                }
                template <class Storage>
                void *allocate(Storage &storage)
                {
                    if (next == last && !expand(storage))
                        return 0;
                    void *ptr = next;
                    next += bucket_size;
                    return ptr;
                }
                void pop()
                {
                    next -= bucket_size;
                }
                template <class Storage>
                bool expand(Storage &storage)
                {
                    size_t capacity = (std::max)(DefaultSizes::MinPoolSize*bucket_size, (last - first)*bucket_size*2);
                    void *ptr = storage.from_fixed(capacity, 16);
                    if (ptr == 0)
                    {
                        ptr = storage.from_heap(capacity, 16);
                        if (ptr == 0)
                            return false;
                    }
                    first = next = (char *)ptr;
                    last = first + capacity;
                    return true;
                }
                void reset()
                {
                    first = next = last = 0;
                }
            };

        } // namespace detail

    } // namespace monotonic

} // namespace boost
            
#endif // BOOST_MONOTONIC_DETAIL_POOL_HPP

//EOF
