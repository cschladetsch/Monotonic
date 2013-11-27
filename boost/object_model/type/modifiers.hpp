// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_TYPE_MODIFIER_HPP
#define BOOST_OBJECT_MODEL_TYPE_MODIFIER_HPP

#include <bitset>
#include <boost/object_model/detail/prefix.hpp>

BOOST_OM_BEGIN

namespace type
{
    struct modifiers
    {
        typedef std::bitset<3> flags_type;
        typedef unsigned long flags_value;
        enum
        {
            None = 0,
            Const = 1,
            Reference = 2,
        };
    private:
        flags_type flags;

    public:
        modifiers() : flags((flags_value)0) { }
        modifiers(flags_value N) : flags(N) { }

        bool is_const() const { return flags[Const]; }
        bool is_reference() const { return flags[Reference]; }
        void set_const(bool B = true) { flags[Const] = B; }
        void set_reference(bool B = true) { flags[Reference] = B; } 
        void set_const_reference(bool B = true) { set_const(B); set_reference(B); }    
    };
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_TYPE_MODIFIER_HPP

//EOF
