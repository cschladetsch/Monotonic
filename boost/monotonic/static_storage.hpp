// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_STATIC_STORAGE_BASE_HPP
#define BOOST_MONOTONIC_STATIC_STORAGE_BASE_HPP

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/storage.hpp>

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            template <class Region>
            struct storage_type<Region, default_access_tag>
            {
                template <size_t N, size_t M, class Al>
                struct storage
                {
                    typedef monotonic::storage<N,M,Al> type;
                };
            };
        }

        template <class Region
            , class Access
            , size_t InlineSize
            , size_t MinHeapIncrement
            , class Al>
        struct static_storage
        {
            typedef Al HeapAllocator;
            typedef detail::storage_type<Region,Access> Selector;
            typedef typename Selector::template storage<InlineSize, MinHeapIncrement, HeapAllocator>::type StorageType;

        private:
            static StorageType global;

        public:
            static_storage()
            {
            }
            static StorageType &get_storage()
            {
                return global;
            }
            static void reset()
            {
                global.reset();
            }
            static void release()
            {
                global.release();
            }
            static void *allocate(size_t num_bytes, size_t alignment)
            {
                return global.allocate(num_bytes, alignment);
            }
            static size_t max_size()
            {
                return global.max_size();
            }
            static size_t used()
            {
                return global.used();
            }
            static size_t remaining()
            {
                return global.remaining();
            }
        };

        /// define the static storage member for all regions with all access types
        template <class Region
            , class Access
            , size_t InlineSize
            , size_t MinHeapIncrement
            , class Al>
        typename static_storage<Region, Access, InlineSize, MinHeapIncrement, Al>::StorageType 
            static_storage<Region, Access, InlineSize, MinHeapIncrement, Al>::global;

        //template <class Region
        //    , class Access = default_access_tag
        //    , size_t N = DefaultSizes::InlineSize
        //    , size_t M = DefaultSizes::MinHeapIncrement
        //    , class Al = std::allocator<void> >
        //struct get_storage
        //{
        //    typedef static_storage_base<Region,Access,N,M,Al> StaticStorage;

        //    static typename StaticStorage::StorageType &get()
        //    {
        //        return StaticStorage::get_storage();
        //    }
        //};

        inline void reset_storage()
        {
            static_storage<default_region_tag>::reset();
        }

        inline void release_storage()
        {
            static_storage<default_region_tag>::release();
        }

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_STATIC_STORAGE_BASE_HPP

//EOF
