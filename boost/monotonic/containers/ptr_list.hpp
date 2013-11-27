// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_PTR_LIST_HPP
#define BOOST_MONOTONIC_PTR_LIST_HPP

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/monotonic/allocator.hpp>
#include <boost/monotonic/inline_clone_allocator.hpp>

namespace boost
{
    namespace monotonic
    {
        /// A boost::ptr_list<T> that uses a monotonic allocator, and a custom clone allocator
        /// TODO: not use inheritance
        template <class T, class Region, class Access>
        struct ptr_list : boost::ptr_list<T, inline_clone_allocator, allocator<T,Region,Access> >
        {
            typedef allocator<T,Region,Access> Allocator;
            typedef boost::ptr_list<T, inline_clone_allocator, Allocator> List;

            ptr_list() 
            { 
            }
            ptr_list(Allocator const &A) 
                : List(A) 
            { 
            }    
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_PTR_LIST_HPP

//EOF
