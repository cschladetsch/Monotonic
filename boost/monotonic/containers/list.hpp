// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
/*
* This file is derived from software bearing the following
* restrictions:
*
* Copyright (c) 1994
* Hewlett-Packard Company
*
* Permission to use, copy, modify, distribute and sell this
* software and its documentation for any purpose is hereby
* granted without fee, provided that the above copyright notice
* appear in all copies and that both that copyright notice and
* this permission notice appear in supporting documentation.
* Hewlett-Packard Company makes no representations about the
* suitability of this software for any purpose. It is provided
* "as is" without express or implied warranty.
*/

/*
* Copyright (c) 1992-2007 by P.J. Plauger.  ALL RIGHTS RESERVED.
* Consult your license regarding permissions and restrictions.
V5.03:0009 */

#ifndef BOOST_MONOTONIC_LIST_HPP
#define BOOST_MONOTONIC_LIST_HPP

#include <list>
#include <boost/interprocess/containers/list.hpp>
#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/detail/container.hpp>

namespace boost
{
    namespace monotonic
    {
        /// A list that uses a monotonic allocator with the given region and access
        template <class T, class Region = default_region_tag, class Access = default_access_tag>
        struct list : detail::container<list<T,Region,Access> >
        {
            typedef allocator<T,Region,Access> Allocator;
            //typedef interprocess::list<T, Allocator> List, Implementation;
            typedef std::list<T, Allocator> List, Implementation;
            typedef detail::container<list<T, Allocator> > Parent;

            typedef typename List::iterator iterator;
            typedef typename List::const_iterator const_iterator;
            typedef typename List::size_type size_type;
            typedef typename List::value_type value_type;
            typedef typename List::reference reference;
            typedef typename List::const_reference const_reference;
            typedef list<T,Region,Access> This;

        private:
            Implementation impl;

        public:
            list() { }
            list(Allocator A) 
                : impl(A) { }

            template <class II>
            list(II F, II L, Allocator A = Allocator())
                : impl(F,L,A) { }
        
            Allocator get_allocator()
            {
                return impl.get_allocator();
            }
            bool empty() const
            {
                return impl.empty();
            }
            size_type size() const
            {
                return impl.size();
            }
            void push_back(value_type const &value)
            {
                impl.push_back(value);
            }
            void pop_back()
            {
                impl.pop_back();
            }
            void push_front(value_type const &value)
            {
                impl.push_front(value);
            }
            void pop_front()
            {
                impl.pop_front();
            }
            iterator begin()
            {
                return impl.begin();
            }
            iterator end()
            {
                return impl.end();
            }
            const_iterator begin() const
            {
                return impl.begin();
            }
            const_iterator end() const
            {
                return impl.end();
            }
            value_type const &front() const
            {
                return impl.front();
            }
            value_type &front()
            {
                return impl.front();
            }
            value_type const &back() const
            {
                return impl.back();
            }
            value_type &back()
            {
                return impl.back();
            }

            void erase(iterator A)
            {
                impl.erase(A);
            }

            template <class Pred2>
            void sort(Pred2 pred)
            {    
                impl.sort(pred);
            }

            void sort()
            {
                sort(std::less<T>());
            }

            template <class Pred3>
            void merge(This& other, Pred3 pred)
            {
                impl.merge(other.impl, pred);
            }

            void splice(const_iterator where, This& other)
            {
                impl.splice(where, other.impl);
            }

            void swap(This &other)
            {
                impl.swap(other.impl);
            }
        };

        template <class Ty,class R,class Acc,class Ty2,class R2,class Acc2>
        bool operator==(list<Ty,R,Acc> const &A, list<Ty2,R2,Acc2> const &B)
        {
            return A.size() == B.size() && std::equal(A.begin(), A.end(), B.begin());
        }
        template <class Ty,class R,class Acc,class Ty2,class R2,class Acc2>
        bool operator!=(list<Ty,R,Acc> const &A, list<Ty2,R2,Acc2> const &B)
        {
            return !(A == B);
        }
        template <class Ty,class R,class Acc,class Ty2,class R2,class Acc2>
        bool operator<(list<Ty,R,Acc> const &A, list<Ty2,R2,Acc2> const &B)
        {
            return std::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end());
        }
        template <class Ty,class R,class Acc,class Ty2,class R2,class Acc2>
        bool operator>(list<Ty,R,Acc> const &A, list<Ty2,R2,Acc2> const &B)
        {
            return std::lexicographical_compare(B.begin(), B.end(), A.begin(), A.end());
        }
        template <class Ty,class R,class Acc,class Ty2,class R2,class Acc2>
        bool operator<=(list<Ty,R,Acc> const &A, list<Ty2,R2,Acc2> const &B)
        {
            return !(A > B);
        }
        template <class Ty,class R,class Acc,class Ty2,class R2,class Acc2>
        bool operator>=(list<Ty,R,Acc> const &A, list<Ty2,R2,Acc2> const &B)
        {
            return !(A < B);
        }

    } // namespace monotonic

} // namespace boost

#endif // BOOST_MONOTONIC_LIST_HPP

//EOF
