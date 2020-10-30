// Copyright (C) 2009-2020 Christian@Schladetsch.com
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_LOCAL_HPP
#define BOOST_MONOTONIC_LOCAL_HPP

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/storage.hpp>
#include <boost/monotonic/static_storage.hpp>

namespace boost
{
    namespace monotonic
    {
        // RIIA for storage
        template <class Region, class Access>
        struct local
        {
            typedef local<Region, Access> This;

            // the storage to use 
            typedef static_storage<
                Region
                , Access
                , DefaultSizes::InlineSize
                , DefaultSizes::MinHeapIncrement
                , default_allocator > StaticStorage;

            // create a rebounded allocator type
            template <class T>
            struct allocator
            {
                typedef monotonic::allocator<T, Region, Access> type;
            };

            local()
            {
            }
            ~local()
            {
                reset();
            }

            template <class T>
            static monotonic::allocator<T,Region,Access> make_allocator()
            {
                return monotonic::allocator<T,Region,Access>();
            }

            static typename StaticStorage::StorageType &get_storage()
            {
                return StaticStorage::get_storage();
            }
            static void reset()
            {
                get_storage().reset();
            }
            static void release()
            {
                get_storage().release();
            }

            template <class Ty>
            Ty &create()
            {
                return get_storage().template create<Ty>();
            }

            template <class Ty>
            Ty &create(Ty const &X)
            {
                return get_storage().template create<Ty>(X);
            }

            template <class Ty>
            void destroy(Ty &X)
            {
                get_storage().destroy(X);
            }

            static size_t fixed_used() 
            {
                return get_storage().fixed_used();
            }

            static size_t heap_used() 
            {
                return get_storage().heap_used();
            }

            static size_t used()
            {
                return get_storage().used();
            }

        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_LOCAL_HPP

//EOF
