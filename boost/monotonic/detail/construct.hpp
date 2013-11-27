// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_ALLOCATOR_DETAIL_CONSTRUCT_HPP
#define BOOST_MONOTONIC_ALLOCATOR_DETAIL_CONSTRUCT_HPP

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            template <bool is_mono_container>
            struct Construct
            {
                template <class T, class Alloc>
                static void Given(T *ptr, Alloc *allocator)
                {
                    new (ptr) T();
                }
                template <class T, class Alloc>
                static void Given(T *ptr, T const &val, Alloc *allocator)
                {
                    new (ptr) T(val);
                }
            };
            template <>
            struct Construct<true>
            {
                template <class T, class Alloc>
                static void Given(T *ptr, Alloc *allocator)
                {
                    new (ptr) T(*allocator);
                }
                template <class T, class Alloc>
                static void Given(T *ptr, T const &val, Alloc *allocator)
                {
                    // unfortunately, there is no requirement for a container to 
                    // have a copy-ctor that also passes an allocator.
                    new (ptr) T(*allocator);
                    *ptr = val;
                }
            };

            template <bool is_monotonic_container, class T>
            struct Create
            {
                template <class Storage>
                static T Given(Storage &)
                {
                    return T();
                }
                template <class Storage>
                static T Given(Storage &, T const &X)
                {
                    return T(X);
                }
            };
            template <class T>
            struct Create<true, T>
            {
                template <class Storage>
                static T Given(Storage &storage)
                {
                    return T(storage);
                }
                template <class Storage>
                static T Given(Storage &storage, T const &X)
                {
                    return T(X, storage);
                }
            };
        }
        namespace detail
        {
            template <size_t A, size_t B>
            struct miniumum
            {
                BOOST_STATIC_CONSTANT(size_t, value = A < B ? A : B);
            };
            template <size_t A, size_t B>
            struct maximum
            {
                BOOST_STATIC_CONSTANT(size_t, value = B < A ? A : B);
            };
        } // namespace detail

    } // namespace monotonic

} // namespace boost

#endif // BOOST_MONOTONIC_ALLOCATOR_DETAIL_CONSTRUCT_HPP

//EOF

