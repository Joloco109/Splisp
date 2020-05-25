#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <boost/spirit/home/x3.hpp>

namespace splgrammar {

namespace x3 = boost::spirit::x3;

auto const lex = x3::lexeme;
using x3::char_;
using x3::lit;

//We ain't gonna have an octotorpe, sorry
auto const spl_escape = char_('#');
auto const spl_ellipsis = lit("...");

auto const sl_comment_terminal = (x3::eoi | x3::eol);
auto const sl_comment = spl_escape >> spl_escape >> *( char_ - sl_comment_terminal) >> sl_comment_terminal;
auto const ml_comment_terminal = lit("*#");
auto const ml_comment = lit("#*") >> *(char_ - ml_comment_terminal) >> ml_comment_terminal;

//Build a parser that parses what we want to skip
auto const skip = (x3::space | sl_comment | ml_comment);

auto const identifier = x3::alpha >> *x3::alnum;

//literals
auto const lit_string = lex['"' >> *(char_ - ('"' - lit("\\\""))) >> '"'];
auto const lit_any = lex[(lit_string
                          | x3::long_
                          | x3::double_) >> ('_' >> +x3::alnum)];

auto const atomic_pattern_expandable = identifier >> -spl_ellipsis;
auto const atomic_pattern_nonexpandable = identifier;

auto const inner_pattern = (atomic_pattern_nonexpandable
                            | ':' >> atomic_pattern_expandable
                            | atomic_pattern_nonexpandable >> ':' >> atomic_pattern_expandable);

auto const pattern = '(' >> inner_pattern >> ')';
auto const metapattern = '<' >> inner_pattern >> '>';






} // namespace splgrammar

#endif // GRAMMAR_H
