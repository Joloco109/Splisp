#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <boost/spirit/home/x3.hpp>

/*namespace pegtl = tao::pegtl;

namespace splgrammar {
    struct ignored : pegtl::sor<pegtl::space>{};

    struct str_func : pegtl::string<'f','u','n','c'>{};
    struct str_type : pegtl::string<'t','y','p','e'>{};
    struct str_trait : pegtl::string<'t','r','a','i','t'>{};
    struct str_thorp : pegtl::string<'#'>{};

    template<typename T>
    struct inst : pegtl::pad<T, ignored>{};

    struct reserved :
            pegtl::sor<
            str_func,
            str_type,
            str_trait
            >{};

    // (A-Za-z_) ~ (UTF8-ICU-ALPHA | c-style-nonfirst-id)*
    struct identifier :
            pegtl::seq<
                pegtl::ascii::identifier_first,
                pegtl::star< pegtl::sor<
                    pegtl::utf8::icu::alphabetic,
                    pegtl::identifier_other
                >>
            >{};

    // (*|:*|*:*)
    struct atomic_pattern{};
};*/

namespace splgrammar {
    namespace x3 = boost::spirit::x3;

    auto spl_escape = x3::char_('#');

    auto sl_comment_terminal = (x3::eoi | x3::eol);
    auto sl_comment = spl_escape >> spl_escape >> *( x3::char_ - sl_comment_terminal) >> sl_comment_terminal;
    auto ml_comment_terminal = x3::lit("*#");
    auto ml_comment = x3::lit("#*") >> *(x3::char_ - ml_comment_terminal) >> ml_comment_terminal;

    //Build a parser that parses what we want to skip
    auto skip = (x3::space | sl_comment | ml_comment);
}

#endif // GRAMMAR_H
