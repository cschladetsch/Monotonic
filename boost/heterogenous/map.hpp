// Copyright (C) 2009-2020 Christian@Schladetsch.com
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_MAP_HPP
#define BOOST_HETEROGENOUS_MAP_HPP

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/foreach.hpp>

#include <boost/cloneable/detail/make_clone_allocator.hpp>

namespace boost 
{
    namespace heterogenous
    {
        /// a vector of heterogenous objects
        template <class Base, class Pred, class Alloc>//, class AbstractBase>
        struct map
        {
            typedef typename make_clone_allocator<Alloc>::type allocator_type;
            typedef Base base_type;
            //typedef ptr_map<Base, Base, Pred, allocator, allocator_type> implementation;
            typedef abstract_cloneable<Base> abstract_base_type;

            typedef std::map<Base *, Base *, Pred, allocator_type> implementation;

            typedef typename implementation::value_type value_type;
            typedef typename implementation::reference reference;
            typedef typename implementation::const_reference const_reference;
            typedef typename implementation::iterator iterator;
            typedef typename implementation::const_iterator const_iterator;
            typedef typename implementation::key_type key_type;
            typedef typename implementation::mapped_type mapped_type;
            typedef map<Base, Pred, Alloc/*, AbstractBase*/> this_type;

        private:
            implementation impl;

        public:
            map()
            {
            }
            map(allocator_type a) 
                : impl(a)
            {
            }

            /* purposefully elided
            template <class II>
            map(II F, II L, allocator_type a = allocator_type());
            */

        private:
            struct value_adder
            {
                this_type *parent;
                base_type *key_instance;

                value_adder(this_type &P, base_type &K) 
                    : parent(&P), key_instance(&K) { }

                template <class U>
                this_type &value()
                {
                    base_type *val = detail::construct<U,base_type>(parent->get_allocator()).to_base();
                    parent->insert(std::make_pair(key_instance, val));
                    return *parent;
                }

                // TODO: use variadic arguments or BOOST_PP to pass ctor args
                template <class U, class A0>
                this_type &value(A0 a0)
                {
                    base_type *val = detail::construct<U,base_type>(parent->get_allocator(), a0).to_base();
                    parent->insert(std::make_pair(key_instance, val));
                    return *parent;
                }
                template <class U, class A0, class A1>
                this_type &value(A0 a0, A1 a1)
                {
                    base_type *val = detail::construct<U,base_type>(parent->get_allocator(), a0, a1).to_base();
                    parent->insert(std::make_pair(key_instance, val));
                    return *parent;
                }
            };

        public:
            template <class U>
            value_adder key()
            {
                base_type *key_instance = detail::construct<U,base_type>(get_allocator()).to_base();
                return value_adder(*this, *key_instance);
            }

            // TODO: use variadic arguments or BOOST_PP to pass ctor args
            template <class U, class A0>
            value_adder key(A0 a0)
            {
                base_type *key_instance = detail::construct<U,base_type>(get_allocator(), a0).to_base();
                return value_adder(*this, *key_instance);
            }
            template <class U, class A0, class A1>
            value_adder key(A0 a0, A1 a1)
            {
                base_type *key_instance = detail::construct<U,base_type>(get_allocator(), a0, a1).to_base();
                return value_adder(*this, *key_instance);
            }
            template <class U, class A0, class A1, class A2>
            value_adder key(A0 a0, A1 a1, A2 a2)
            {
                base_type *key_instance = detail::construct<U,base_type>(get_allocator(), a0, a1, a2).to_base();
                return value_adder(*this, *key_instance);
            }

            // TODO: make this private
            void insert(value_type x)
            {
                impl.insert(x);
            }

            template <class Fun>
            Fun for_each(Fun fun)
            {
                BOOST_FOREACH(value_type &value, *this)
                {
                    fun(value);
                }
            }

            template <class Ty, class Fun>
            Fun for_each_key(Fun fun)
            {
                //BOOST_FOREACH(base_type &b, *this)
                //{
                //    if (Ty *ptr = dynamic_cast<Ty *>(&b))
                //    {
                //        fun(*ptr);
                //    }
                //}
                return fun;
            }

            template <class Ty, class Fun>
            Fun for_each_mapped(Fun fun) const
            {
                //BOOST_FOREACH(const common_base &base, *this)
                //{
                //    if (Ty *ptr = dynamic_cast<Ty *>(&base))
                //    {
                //        fun(*ptr);
                //    }
                //}
                return fun;
            }

            size_t size() const
            {
                return impl.size();
            }
            bool empty() const
            {
                return impl.empty();
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

            iterator find(key_type const &key)
            {
                return impl.find(key);
            }

            //reference operator[](key_type const &key)
            //{
            //    return impl[n];
            //}
            //const_reference operator[](key_type const &key) const
            //{
            //    return impl[n];
            //}

            typename implementation::allocator_type get_allocator()
            {
                return impl.get_allocator();
            }
        };
    
    } // namespace heterogenous

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_MAP_HPP

//EOF
