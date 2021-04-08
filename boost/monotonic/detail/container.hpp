// Copyright (C) 2009-2020 Christian@Schladetsch.com
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <boost/monotonic/detail/prefix.hpp>
#include <type_traits>

//#include <boost/monotonic/allocator.hpp>

namespace boost
{
    namespace monotonic
    {
        namespace detail
        {
            struct container_base { virtual ~container_base() { } };

            template <class Impl>
            struct container;

            template <class T>
            struct is_monotonic : std::is_convertible<T *, container_base *>::value { };
            
            template <class Impl>
            struct is_monotonic<container<Impl> > : std::true_type { };

            template <class Impl>
            struct container : container_base
            {
                typedef Impl Derived;

                storage_base &get_storage() const
                {
                    Derived const &self = static_cast<Derived const &>(*this);
                    storage_base *store = self.get_allocator().get_storage();
                    if (store == 0)
                        //throw_exception(no_storage());
                        throw no_storage();
                    return *store;
                }
            };
        }
    }
}

#include <boost/monotonic/detail/postfix.hpp>

//EOF
