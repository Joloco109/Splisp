#ifndef PARSER_H
#define PARSER_H

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/icu/utf8.hpp>

namespace pegtl = tao::pegtl;

namespace splgrammar {
    struct ignored : pegtl::sor<pegtl::space>{};
    struct str_func : pegtl::string<'f','u','n','c'>{};
    struct str_type : pegtl::string<'t','y','p','e'>{};
    struct str_trait : pegtl::string<'t','r','a','i','t'>{};
    struct thorperator : pegtl::string<'#'>{};

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
};

class Parser
{
public:
    Parser();
};

#endif // PARSER_H
