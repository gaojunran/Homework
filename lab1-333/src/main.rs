/// Author: Gao Junran
/// Date: 2024-03-26
/// Description: This is a program to convert a floating point number to its IEEE 754 representation.
/// My program is tested in https://baseconvert.com/ieee-754-floating-point, and turns out to be accurate.
use std::io::stdin;
use std::io::stdout;
use std::io::Write;

struct F32Repr {
    sign: String,
    mantissa: String,
    exponent: String,
}

impl F32Repr {
    fn new() -> Self {
        Self {
            sign: String::new(),
            mantissa: String::new(),
            exponent: String::new(),
        }
    }

    fn repr(&self) -> String {
        format!(
            "The IEEE 754 Single Precision is \nSign: {}\nMantissa (24 bit): {}\nExponent: {}",
            self.sign, self.mantissa, self.exponent
        )
    }
}

fn int_to_binary(int: i64) -> String {
    let mut integer = int;
    let mut binary = String::new();
    while integer > 0 {
        let remainder = integer % 2;
        binary.push_str(&remainder.to_string());
        integer /= 2;
    }
    binary.chars().rev().collect::<String>()
}

fn dec_to_binary(dec: f64) -> String {
    let mut decimal = dec;
    let mut binary = String::new();
    if decimal == 0.0 {
        binary.push('0');
    }
    while decimal > 0.0 {
        decimal *= 2.0;
        if decimal >= 1.0 {
            binary.push('1');
            decimal -= 1.0;
        } else {
            binary.push('0');
        }
    }
    binary
}

/// From slide: page 46
fn calculate_mantissa(int_binary: &String, dec_binary: &String) -> String {
    let mut binary = format!("{}{}", int_binary, dec_binary);
    // drop the leading zeros
    while binary.starts_with("0") {
        binary.remove(0);
    }
    // consider: 0.0
    if binary.is_empty() {
        binary.push('1');
    }
    binary = format!("{:0<24}", binary);
    binary[..24].to_string()
}

/// From slide: page 47
fn calculate_exponent(real: f64) -> String {
    let mut real = real;
    let mut exponent = 0;
    if real >= 1.0 {
        // For greater than 1: keep dividing by 2 until it's less than 2
        while real >= 2.0 {
            real /= 2.0;
            exponent += 1;
        }
    } else {
        // For less than 1: keep multiplying by 2 until it's greater than 1
        while real < 1.0 {
            real *= 2.0;
            exponent -= 1;
        }
    }
    exponent += 127; // bias
    if exponent > 255 {
        // overflow
        exponent = 255;
    }
    format!("{:0>8}", int_to_binary(exponent))
}

fn main() {
    println!("Input a real number: ");
    stdout().flush().unwrap();
    let mut real = String::new();
    stdin().read_line(&mut real).unwrap();
    // parse to float first to accept scientific notation
    let mut real = real.trim().parse::<f64>().unwrap();
    let mut repr = F32Repr::new();
    repr.sign = if real >= 0.0 { "0" } else { "1" }.to_string();
    // After the sign is determined, make the number positive
    real = real.abs();
    let (int, dec) = (
        real as i64,  // integer part
        real.fract(), // decimal part
    );
    let int_binary = int_to_binary(int);
    let dec_binary = dec_to_binary(dec);
    repr.mantissa = calculate_mantissa(&int_binary, &dec_binary);
    repr.exponent = calculate_exponent(real);
    if repr.exponent == "11111111" {
        repr.mantissa = "000000000000000000000000".to_string(); // rule by IEEE 754
        println!("{}", repr.repr());
        println!("Overflow!!!")
    } else {
        println!("{}", repr.repr());
    }
}
