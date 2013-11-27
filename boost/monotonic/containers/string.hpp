// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_STRING_HPP
#define BOOST_MONOTONIC_STRING_HPP

#include <string>
#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/allocator.hpp>

namespace boost
{
    namespace monotonic
    {
        /// a string that uses a monotonic allocator in the given region
        template <class Region = default_region_tag, class Access = default_access_tag>
        struct string : detail::container<string<Region,Access> >
        {
            typedef char Ch;
            typedef std::char_traits<Ch> Tr;
            typedef allocator<Ch, Region,Access> Allocator;
            typedef std::basic_string<Ch, Tr, Allocator> Impl;
            typedef size_t size_type;
            typedef typename Impl::iterator iterator;
            typedef typename Impl::const_iterator const_iterator;
            typedef typename Impl::value_type value_type;

        private:
            Impl impl;

        public:
            string()
            {
            }
            template <class Reg2, class Acc2>
            string(string<Reg2,Acc2> const &other)
                : impl(other.impl)
            {
            }
            string(Allocator alloc)
                : impl(alloc)
            {
            }
            string(const Ch *str)
                : impl(str)
            {
            }
            template <class U>
            string(const Ch *str, allocator<U,Region,Access> alloc)
                : impl(str, alloc)
            {
            }
            string(const Ch *str, storage_base &store)
                : impl(str, store)
            {
//                BOOST_STATIC_ASSERT((boost::same_type<default_region_tag, Region>::value));
            }
            template <class II>
            string(II F, II L)
                : impl(F, L)
            {
            }
            template <class II, class U>
            string(II F, II L, allocator<U,Region,Access> alloc)
                : impl(F, L, alloc)
            {
            }
            template <class II>
            string(II F, II L, storage_base &store)
                : impl(F, L, store)
            {
            }

            string &operator=(string const &other)
            {
                impl = other.get_impl();
                return *this;
            }

            Allocator get_allocator() const
            {
                return impl.get_allocator();
            }

            Impl const &get_impl() const
            {
                return impl;
            }
            Impl &get_impl()
            {
                return impl;
            }

            template <class Reg2, class Acc2>
            string &operator=(string<Reg2,Acc2> const &other)
            {
                impl = other.c_str();
                return *this;
            }

            string &operator+=(Ch const *str)
            {
                impl += str;
                return *this;
            }

            Ch const *c_str() const
            {
                return impl.c_str();
            }
        };

        template <class Reg, class Acc>
        bool operator==(string<Reg,Acc> const &A, string<Reg,Acc> const &B)
        {
            return A.get_impl() == B.get_impl();
        }
        template <class Reg, class Acc, class Reg2, class Acc2>
        bool operator==(string<Reg,Acc> const &A, string<Reg2,Acc2> const &B)
        {
            return A.get_impl() == B.c_str();
        }
        template <class Reg, class Acc>
        bool operator==(string<Reg,Acc> const &A, typename string<Reg,Acc>::value_type const *B)
        {
            return A.get_impl() == B;
        }
        template <class Reg, class Acc, class Reg2, class Acc2>
        bool operator<(string<Reg,Acc> const &A, string<Reg2,Acc2> const &B)
        {
            return A.get_impl() < B.get_impl();
        }

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_STRING_HPP

//EOF
