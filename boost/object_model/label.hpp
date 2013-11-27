// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_LABEL_HPP
#define BOOST_OBJECT_MODEL_LABEL_HPP

#include <string>
#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/forward_declarations.hpp>
#include <boost/object_model/string.hpp>
#include <boost/object_model/string_stream.hpp>

BOOST_OM_BEGIN

template <class String>
struct label
{
    typedef String string_type;
    typedef typename String::allocator_type allocator_type;
    typedef typename string_type::value_type char_type;

private:
    string_type value;

public:
    label() { }
    label(const char_type *text)
    {
        from_string(text);
    }
    label(const string_type &text)
    {
        from_string(text);
    }

    const string_type &to_string() const { return value; }

    friend bool operator==(label const &a, label const &b) { return a.value == b.value; }
    friend bool operator<(label const &a, label const &b) { return a.value < b.value; }

private:
    void from_string(const string_type &text)
    {
        from_string(text.c_str());
    }
    void from_string(const char_type *text)
    {
        value = text;
    }
};

template <class Al, class Ch, class Tr, class String>
string_stream<Al,Ch,Tr> &operator<<(string_stream<Al,Ch,Tr> &stream, const label<String> &val)
{
    return stream << val.to_string();
}

BOOST_OM_END

BOOST_BEGIN

template <class Str>
struct hash<boost::BOOST_OBJECT_MODEL_NAMESPACE_NAME::label<Str> >
{
    size_t operator()(const boost::BOOST_OBJECT_MODEL_NAMESPACE_NAME::label<Str>  &ident) const
    {
        return hash<const typename Str::char_type *>(ident.to_string().c_str());
    }
};

BOOST_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_LABEL_HPP

//EOF
