// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

#pragma once

#include <boost/timer.hpp>

struct PoolResult 
{
    //boost::array<double, Type:: elapsed[;
    double pool_elapsed;
    double fast_pool_elapsed;
    double mono_elapsed;
    double local_mono_elapsed;
    double std_elapsed;
    double tbb_elapsed;
    PoolResult(double D = 0)
    {
        tbb_elapsed = pool_elapsed = fast_pool_elapsed = mono_elapsed = local_mono_elapsed = std_elapsed = D;
    }

    PoolResult& operator+=(PoolResult const &A)
    {
        pool_elapsed += A.pool_elapsed;
        fast_pool_elapsed += A.fast_pool_elapsed;
        mono_elapsed += A.mono_elapsed;
        local_mono_elapsed += A.local_mono_elapsed;
        std_elapsed += A.std_elapsed;
        tbb_elapsed += A.tbb_elapsed;
        return *this;
    }
    PoolResult& operator-=(PoolResult const &A)
    {
        pool_elapsed -= A.pool_elapsed;
        fast_pool_elapsed -= A.fast_pool_elapsed;
        mono_elapsed -= A.mono_elapsed;
        local_mono_elapsed -= A.local_mono_elapsed;
        std_elapsed -= A.std_elapsed;
        tbb_elapsed -= A.tbb_elapsed;
        return *this;
    }
    PoolResult& operator*=(PoolResult const &A)
    {
        pool_elapsed *= A.pool_elapsed;
        fast_pool_elapsed *= A.fast_pool_elapsed;
        mono_elapsed *= A.mono_elapsed;
        local_mono_elapsed *= A.local_mono_elapsed;
        std_elapsed *= A.std_elapsed;
        tbb_elapsed *= A.tbb_elapsed;
        return *this;
    }
    PoolResult& operator*=(double A)
    {
        pool_elapsed *= A;
        fast_pool_elapsed *= A;
        mono_elapsed *= A;
        local_mono_elapsed *= A;
        std_elapsed *= A;
        tbb_elapsed *= A;
        return *this;
    }

    void update_min(PoolResult const &other)
    {
        // reject very small mins as we sometimes have 0-element tests
        if (other.fast_pool_elapsed > 0.01)
            fast_pool_elapsed = std::min(fast_pool_elapsed, other.fast_pool_elapsed);
        if (other.pool_elapsed > 0.01)
            pool_elapsed = std::min(pool_elapsed, other.pool_elapsed);
        if (other.tbb_elapsed > 0.01)
            tbb_elapsed = std::min(tbb_elapsed, other.tbb_elapsed);
        if (other.std_elapsed > 0.01)
            std_elapsed = std::min(std_elapsed, other.std_elapsed);
    }
    void update_max(PoolResult const &other)
    {
        fast_pool_elapsed = std::max(fast_pool_elapsed, other.fast_pool_elapsed);
        pool_elapsed = std::max(pool_elapsed, other.pool_elapsed);
        tbb_elapsed = std::max(tbb_elapsed, other.tbb_elapsed);
        std_elapsed = std::max(std_elapsed, other.std_elapsed);
    }
};

inline PoolResult sqrt(PoolResult const &A)
{
    PoolResult R(A);
    R.fast_pool_elapsed = sqrt(R.fast_pool_elapsed); 
    R.mono_elapsed = sqrt(R.mono_elapsed); 
    R.local_mono_elapsed = sqrt(R.local_mono_elapsed); 
    R.std_elapsed = sqrt(R.std_elapsed); 
    R.tbb_elapsed = sqrt(R.tbb_elapsed); 
    return R;
}

inline PoolResult operator*(PoolResult const &A, PoolResult const &B)
{
    PoolResult R(A);
    R *= B;
    return R;
}

inline PoolResult operator+(PoolResult const &A, PoolResult const &B)
{
    PoolResult R(A);
    R += B;
    return R;
}

inline PoolResult operator-(PoolResult const &A, PoolResult const &B)
{
    PoolResult R(A);
    R -= B;
    return R;
}

typedef std::map<size_t /*count*/, PoolResult> PoolResults;


//EOF
