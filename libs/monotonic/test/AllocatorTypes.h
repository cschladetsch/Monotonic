// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

#pragma once

#include <memory>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#undef max
#undef min
#include <boost/monotonic/allocator.hpp>
#include <boost/monotonic/local.hpp>

#ifdef BOOST_MONOTONIC_TBB
#include <tbb/tbb_allocator.h>
#endif

struct Type
{
    enum Value
    {
        None = 0,
        Standard = 1,
        FastPool = 2,
        Pool = 4,
        Monotonic = 8,
        Tbb = 16,
        Google = 32,
        All = 0xffffffff,
    };
    unsigned flags;
    Type(unsigned bits = All) : flags(bits) { }
    bool Includes(unsigned bit) const { return (flags & bit) != 0; }
    void Exclude(unsigned bit) { flags &= ~bit; }
    void Include(unsigned bit) { flags |= bit; }
    std::string ToString() const;
};

struct Location
{
    enum { Heap, Stack };
};

template <size_t Num, class Ty>
struct Allocator;

template <class Ty>
struct Allocator<Type::Standard, Ty> : std::allocator<Ty> { };

template <class Ty>
struct Allocator<Type::FastPool, Ty> : boost::fast_pool_allocator<Ty
    , boost::default_user_allocator_new_delete
    , boost::details::pool::null_mutex> { };

template <class Ty>
struct Allocator<Type::Pool, Ty> : boost::pool_allocator<Ty
    , boost::default_user_allocator_new_delete
    , boost::details::pool::null_mutex> { };

template <class Ty>
struct Allocator<Type::Monotonic, Ty> : boost::monotonic::allocator<Ty> { };

#ifdef BOOST_MONOTONIC_TBB
template <class Ty>
struct Allocator<Type::Tbb, Ty> : tbb::tbb_allocator<Ty> { };
#endif

template <class Alloc, class T>
struct Rebind
{
    typedef typename Alloc::template rebind<T>::other type;
};

struct Unaligned
{
    char c[5];
    Unaligned() { }
    Unaligned(char C) 
    {
        c[2] = C;
    }
};

inline bool operator<(Unaligned const &A, Unaligned const &B)
{
    return A.c[2] < B.c[2];
}

//EOF
