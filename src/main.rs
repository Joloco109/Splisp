extern crate pest;
#[macro_use]
extern crate pest_derive;

pub mod parser;

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    mod parser_tests;
}
