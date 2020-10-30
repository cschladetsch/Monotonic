// Copyright (C) 2009-2020 Christian@Schladetsch.com
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <boost/heterogenous/detail/prefix.hpp>
#include <boost/heterogenous/forward_declarations.hpp>

namespace boost::heterogenous {
/// base class for (wrapped) allocators to be used with heterogenous::cloneable<>
/// by heterogenous containers
struct abstract_allocator
{
    typedef char *pointer;

    virtual pointer allocate_bytes(size_t num_bytes, size_t alignment) = 0;

    virtual void deallocate_bytes(pointer, size_t alignment) = 0;

    static size_t calc_padding(pointer ptr, size_t alignment)
    {
        ptrdiff_t index = ptr - pointer(0);
        size_t extra = index & (alignment - 1);    // assumes 2^n alignment!
        if (extra > 0)
            extra = alignment - extra;
        return extra;
    }
};

}  // namespace boost::heterogenous

#include <boost/heterogenous/detail/suffix.hpp>

