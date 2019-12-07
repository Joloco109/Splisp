use parser::SlispParser;
use parser::Rule;

#[test]
fn identifier() {
    pest::parses_to! {
        parser:SlispParser,
        input : "ab6_lq",
        rule : Rule::identifier,
        tokens: [ identifier(0, 6, []) ]
    }
    pest::parses_to! {
        parser:SlispParser,
        input : "ab(6_lq",
        rule : Rule::identifier,
        tokens: [ identifier(0, 2, []) ]
    }
}

#[test]
fn identifier_fail() {
    pest::fails_with! {
        parser:SlispParser,
        input : "0ab6_lq",
        rule : Rule::identifier,
        positives: vec![Rule::identifier],
        negatives: vec![],
        pos: 0
    }
    pest::fails_with! {
        parser:SlispParser,
        input : "!ab6_lq",
        rule : Rule::identifier,
        positives: vec![Rule::identifier],
        negatives: vec![],
        pos: 0
    }
}

#[test]
fn function_dcl() {
    pest::parses_to! {
        parser:SlispParser,
        input : "func ( x : X, y:Y ) -> Z;",
        rule : Rule::function_dcl,
        tokens: [
            function_dcl(0, 25, [
                identifier( 0, 4, []),
                function_sig( 5, 24, [
                    parameter_list(5, 19, [
                        identifier( 7, 8, [] ),
                        identifier( 11, 12, [] ),
                        identifier( 14, 15, [] ),
                        identifier( 16, 17, [] ),
                    ]),
                    identifier(23, 24, [])
                ])
            ]) ]
    }
}
