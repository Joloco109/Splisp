use parser::SplispParser;
use parser::Rule;

#[test]
fn identifier() {
    pest::parses_to! {
        parser:SplispParser,
        input : "ab6_lq",
        rule : Rule::identifier,
        tokens: [ identifier(0, 6, []) ]
    }
    pest::parses_to! {
        parser:SplispParser,
        input : "ab(6_lq",
        rule : Rule::identifier,
        tokens: [ identifier(0, 2, []) ]
    }
}

#[test]
fn identifier_fail() {
    pest::fails_with! {
        parser:SplispParser,
        input : "0ab6_lq",
        rule : Rule::identifier,
        positives: vec![Rule::identifier],
        negatives: vec![],
        pos: 0
    }
    pest::fails_with! {
        parser:SplispParser,
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
        parser:SplispParser,
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

#[test]
fn function_def() {
    pest::parses_to! {
        parser:SplispParser,
        input : "func ( x : X, y:Y ) -> Z\n\t= (g(x),y)",
        rule : Rule::function_def,
        tokens: [
            function_def(0, 36, [
                identifier( 0, 4, []),
                function_sig( 5, 24, [
                    parameter_list(5, 19, [
                        identifier( 7, 8, [] ),
                        identifier( 11, 12, [] ),
                        identifier( 14, 15, [] ),
                        identifier( 16, 17, [] ),
                    ]),
                    identifier(23, 24, [])
                ]),
                list( 28, 36, [
                    function_call( 29, 33, [
                        identifier( 29, 30 ),
                        list( 30, 33, [
                        identifier( 31, 32, [])
                        ] )
                    ]),
                    identifier( 34, 35, [] )
                ] )
            ]) ]
    }
}

#[test]
fn expression() {
    let text = "let x:X = 0;\nlet y:= ();\nx";
    println!("{}",text);
    pest::parses_to! {
        parser:SplispParser,
        input : text,
        rule : Rule::expression,
        tokens: [
            let_var(0, 12, [
                identifier( 4, 5, [] ),
                identifier( 6, 7, [] ),
                integer( 10, 11, [] )
            ]),
            let_var(13, 24, [
                identifier( 17, 18, [] ),
                list( 21, 23, [] )
            ]),
            identifier(25,26,[] )
        ]
    }
    let text = "( x, 0, () )";
    println!("{}",text);
    pest::parses_to! {
        parser:SplispParser,
        input : text,
        rule : Rule::expression,
        tokens: [
            list( 0, 12, [
                  identifier(2,3),
                  integer(5,6),
                  list(8,10)
            ] )
        ]
    }
    let text = "0.1";
    println!("{}",text);
    pest::parses_to! {
        parser:SplispParser,
        input : text,
        rule : Rule::expression,
        tokens: [
            float( 0, 3, [] )
        ]
    }
    let text = "\"Hello \\\"World\\\"\"";
    println!("{}",text);
    pest::parses_to! {
        parser:SplispParser,
        input : text,
        rule : Rule::expression,
        tokens: [
            string( 0, 17, [] )
        ]
    }
}
