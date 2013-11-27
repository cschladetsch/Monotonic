// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_FORWARD_DECLARATIONS_HPP
#define BOOST_OBJECT_MODEL_FORWARD_DECLARATIONS_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/exceptions.hpp>

BOOST_OM_BEGIN

namespace type
{
    /// traits for a given type
    template <class T>
    struct traits;

    /// a type number
    struct number;

    struct any;
}

/// a unique identifier of an object
struct handle;

/// a name for an object
template <class Text>
struct label;

/// a mapping of label to object
template <class Label>
struct dictionary;

/// generic bases for type-specific derived types
namespace generic
{
    struct base;

    struct object_base;

    struct const_object;

    struct mutable_object;

    struct object;

    /// common for all const storage for an instance
    template <class Traits>
    struct const_storage;

    /// common for all storage for an instance
    template <class Traits>
    struct storage;

    /// common for types that have a `self` pointer
    struct reflected;

    /// common for a all methods
    template <class Traits>
    struct method;

    /// common for all class properties
    struct property;

    /// common for all classes
    //template <class Label>
    struct klass;

    //template <class Label>
    struct registry;
}

template <class T = type::any>
struct const_object;

template <class T = type::any>
struct const_reference;

template <class T = type::any>
struct const_pointer;

template <class T = type::any>
struct mutable_object;

template <class T = type::any>
struct mutable_reference;

template <class T = type::any>
struct mutable_pointer;

template <class T = type::any>
struct object;

template <class T = type::any>
struct pointer;

template <class T = type::any>
struct reference;

/// storage for a specific type
template <class T, class Traits>
struct storage;

/// const storage for a specific type
template <class T, class Traits>
struct const_storage;

template <class T>
struct reflected;

template <class Al = default_allocator, class Ch = char, class Tr = std::char_traits<Ch> >
struct string;

template <class Str = string<> >
struct label;

/// a specific method of class type, with given signature
template <class Reg, class Rty, class Klass, class Args, bool Konst>
struct method;

/// a specific property
template <class T, class Val>
struct property;

/// class of a given type
template <class T, class Traits>
struct klass;

/// helper structure to assist with reflecting a C++ type
template <class T, class Traits>
struct builder;

/// traits type to control how the system works, and what data-types to use for various 
/// key components
template <
    class Alloc = default_allocator                // allocator to use for everything
    , class Char = char                            // default char type
    , class ChTr = std::char_traits<Char>        // char traits
    , class Str = string<Alloc, Char, ChTr>        // string type to use
    , class Label = label<Str>                    // label type. used to name sub-objects
    , class Ident = label<Str>                    // identifier. used to access fields and methods
>
struct system_traits;

/// an object type factory, and registery of instances
template <class Traits = system_traits<> >
struct registry;

namespace containers
{
    /// an array of objects given an allocator
    template <class Al>
    struct vector;

    /// an list of objects given an allocator
    template <class Al>
    struct list;

    /// an map of objects to objects given an allocator
    template <class Al>
    struct map;

    /// an set of objects given an allocator
    template <class Al>
    struct set;

}

/// a sequence of executable objects
struct continuation;

/// executes continuations
struct exectutor;

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_FORWARD_DECLARATIONS_HPP

//EOF
