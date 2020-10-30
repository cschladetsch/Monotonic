// Copyright (C) 2009-2020 Christian@Schladetsch.com
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_STACK_HPP
#define BOOST_MONOTONIC_STACK_HPP

#include <typeinfo>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/utility/iter_range.hpp>

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/storage.hpp>
#include <boost/monotonic/containers/vector.hpp>

// warning C4345: behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
#pragma warning(disable:4345)

namespace boost
{
    namespace monotonic
    {
        struct null_pointer {};

        /// a first-class fixed-size stack object
        template <size_t InlineSize>
        struct fixed_stack
        {
            typedef fixed_stack<InlineSize> this_type;

        private:
            fixed_storage<InlineSize> store;

            template <class>
            struct element;

            /// an entry on the stack
            struct element_base
            {
                element_base *previous;
                size_t cursor;
                bool is_pod;
                element_base(bool ip = false) 
                    : is_pod(ip) { }
                template <class T>
                bool is_type() const
                {
                    return get_type() == typeid(T);
                }
                template <class T>
                T &get()
                {
                    if (get_type() != typeid(T))
                        throw std::bad_get();
                    return *static_get<element<T> &>(*this).get_pointer();
                }
                template <class T>
                const T &get() const
                {
                    if (get_type() != typeid(T))
                        throw std::bad_get();
                    return *static_get<const element<T> &>(*this).get_pointer();
                }

                virtual void destroy() {}
                virtual const std::type_info &get_type() const = 0;
            };
            struct impl
            {
                /// a class-type element
                template <class T, bool>
                struct element : element_base
                {
                    typedef T type;
                    typedef type *pointer;

                private:
                    pointer ptr;
                    char value[sizeof(T)];
                
                public:
                    element()
                        : ptr(reinterpret_cast<T *>(value))
                    {
                    }
                    const std::type_info &get_type() const
                    {
                        return typeid(T);
                    }
                    pointer get_pointer()
                    {
                        return ptr;
                    }
                    void destroy()
                    {
                        destroy(ptr, boost::has_trivial_destructor<type>());
                    }
                    void destroy(pointer ptr, const boost::false_type& )
                    {
                        (*ptr).~type();
                    }

                    void destroy(pointer, const boost::true_type& )
                    { 
                    }
                };

                /// a pod-type element
                template <class T>
                struct element<T, true> : element_base
                {
                    typedef T type;
                    type val;
                    element()
                        : element_base(true)
                    {
                    }
                    type *get_pointer()
                    {
                        return &val;
                    }
                    const std::type_info &get_type() const
                    {
                        return typeid(T);
                    }
                };
            };

            /// an element of a given type on the stack
            template <class T>
            struct element 
                : impl::element<T, boost::is_pod<T>::value>
            {
            };

            element_base *previous;

        public:
            typedef element_base value_type;
            typedef element_base &reference;
            typedef element_base const &const_reference;
            typedef size_t size_type;

            struct const_iterator : boost::iterator<forward_traversal_tag, element_base>
            {
                typedef element_base value_type;
                element_base *current;

                const_iterator(element_base *elem = 0) 
                    : current(elem) { }

                const value_type &operator*() const
                {
                    return *current;
                }
                const value_type *operator->() const
                {
                    return current;
                }
                const_iterator &operator++()
                {
                    current = current->previous;
                    return *this;
                }
                const_iterator operator++(int)
                {
                    const_iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }
                friend bool operator==(const_iterator left, const_iterator right)
                {
                    return left.current == right.current;
                }
                friend bool operator!=(const_iterator left, const_iterator right)
                {
                    return left.current != right.current;
                }
            };

            struct iterator : const_iterator
            {
                iterator(element_base *elem = 0) 
                    : const_iterator(elem) { }

                value_type &operator*()
                {
                    return *current;
                }
                value_type *operator->()
                {
                    return current;
                }
                iterator &operator++()
                {
                    const_iterator::operator++(0);
                    return *this;
                }
                iterator operator++(int)
                {
                    iterator tmp = *this;
                    const_iterator::operator++(0);
                    return tmp;
                }
            };

        public:
            fixed_stack() 
                : previous(0)
            {
            }
            ~fixed_stack()
            {
                clear();
            }

            size_t size() const
            {
                size_t len = 0;
                const_iterator F = begin(), L = end();
                for (; F != L; ++F)
                    ++len;
                return len;
            }
            const_iterator begin() const
            {
                return const_iterator(previous);
            }
            const_iterator end() const
            {
                return const_iterator(0);
            }
            iterator begin()
            {
                return iterator(previous);
            }
            iterator end()
            {
                return iterator(0);
            }

            template <class T>
            T &push()
            {
                element<T> &elem = push_element<T>();
                if (!is_pod<T>::value)
                    new (elem.get_pointer()) T();
                return *elem.get_pointer();
            }

            template <class T, class A0>
            T &push(A0 a0)
            {
                element<T> &elem = push_element<T>();
                new (elem.get_pointer()) T(a0);
                return *elem.get_pointer();
            }

            template <class T, class A0, class A1>
            T &push(A0 a0, A1 a1)
            {
                element<T> &elem = push_element<T>();
                new (elem.get_pointer()) T(a0, a1);
                return *elem.get_pointer();
            }

            template <class T, size_t N>
            array<T, N> &push_array()
            {
                return push<array<T, N> >();
            }

            void pop()
            {
                BOOST_ASSERT(previous);
                element_base *elem = previous;
                previous = elem->previous;
                size_t cursor = elem->cursor;
                if (!elem->is_pod)    // avoid empty virtual call for pods
                    elem->destroy();
                store.set_cursor(cursor);
            }

            size_t top() const
            {
                return store.get_cursor();
            }

            void clear()
            {
                while (previous != 0)
                {
                    pop();
                }
            }

        private:
            template <class T>
            element<T> &push_element()
            {
                size_t cursor = store.get_cursor();
                element<T> &elem = store.create<element<T> >();
                elem.previous = previous;
                elem.cursor = cursor;
                previous = &elem;
                return elem;
            }
        };

        /// a growable stack
        template <size_t Size, size_t Inc, class Al>
        struct stack
        {
            fixed_stack<Size> fixed;

        private:
            storage<Size, Inc, Al> storage;

        public:
            stack()
            {
            }
            ~stack()
            {
                clear();
            }

            void clear()
            {

            }
            size_t top() const
            {
                return 0;
            }
            size_t size() const
            {
                return 0;
            }
            template <class T>
            T &push()
            {
                return fixed.push<T>();
            }
        };
    
    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_STACK_HPP

//EOF
