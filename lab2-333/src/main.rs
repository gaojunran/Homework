/// For Task 1 ~ 3 of Lab2.
use rand::Rng;
use std::{
    fs::File,
    io::{self, Write},
    ptr,
};

static MAX_NUMBERS: u32 = 100;

fn generate_random() -> f32 {
    let mut rng = rand::rng();
    rng.random_range(-100.0..=100.0) as f32
}

unsafe fn insert_node(h: *mut *mut Node, t: *mut *mut Node, value: NodeValue) {
    // Creates a new node with value given by parameter value
    // and inserts that node at the beginning of the list whose
    // first and last nodes are pointed to by *h and *t
    // respectively.
    let temp = Box::into_raw(Box::new(Node {
        value,
        next: ptr::null_mut(),
    }));

    if (*h).is_null() {
        // List is currently empty.
        *h = temp;
        *t = temp;
    } else {
        // The list is not empty. Use *h to add the node
        // at the beginning.
        (*temp).next = *h;
        *h = temp;
    }
}

unsafe fn fprint_list(h: *mut Node, filename: Option<&str>) {
    // Prints the values stored in the nodes of the list pointed to by h.
    // If a filename is provided, writes the output to the file.
    // Otherwise, prints to stdout.

    let mut output: Box<dyn Write> = match filename {
        Some(name) => Box::new(File::create(name).expect("Failed to create file")),
        None => Box::new(io::stdout()),
    };

    if h.is_null() {
        writeln!(output, "The list is empty.").expect("Failed to write to output");
    } else {
        writeln!(output, "Values in the list are:").expect("Failed to write to output");
        let mut current = h;
        while !current.is_null() {
            writeln!(output, "[{:?}], ", (*current).value).expect("Failed to write to output");
            current = (*current).next;
        }
    }
}

#[derive(Debug)]
struct Node {
    value: NodeValue,
    next: *mut Node,
}

#[derive(Debug)]
struct NodeValue {
    value: f32,
}

fn main() {
    let args = std::env::args().collect::<Vec<String>>();
    // println!("Arguments: {:?}", args);
    if args.len() != 3 {
        eprintln!("Usage: {} <number_of_positive> <file_ext>", args[0]);
        std::process::exit(1);
    }
    let num_positive: u32 = args[1].parse().expect("Invalid number of positive values");
    let file_ext: String = args[2].clone();
    let mut count = 0;
    let mut pos: *mut Node = ptr::null_mut();
    let mut pos_tail: *mut Node = ptr::null_mut();
    let mut pos_frac: *mut Node = ptr::null_mut();
    let mut pos_frac_tail: *mut Node = ptr::null_mut();
    let mut neg: *mut Node = ptr::null_mut();
    let mut neg_tail: *mut Node = ptr::null_mut();
    let mut neg_frac: *mut Node = ptr::null_mut();
    let mut neg_frac_tail: *mut Node = ptr::null_mut();
    while count < num_positive {
        match generate_random() {
            n if n >= 1.0 => {
                let value = NodeValue { value: n };
                unsafe {
                    insert_node(&mut pos, &mut pos_tail, value);
                }
                count += 1;
            }
            n if (0.0..1.0).contains(&n) => {
                let value = NodeValue { value: n };
                unsafe {
                    insert_node(&mut pos_frac, &mut pos_frac_tail, value);
                }
            }
            n if (-1.0..0.0).contains(&n) => {
                let value = NodeValue { value: n };
                unsafe {
                    insert_node(&mut neg, &mut neg_tail, value);
                }
            }
            n if n <= -1.0 => {
                let value = NodeValue { value: n };
                unsafe {
                    insert_node(&mut neg_frac, &mut neg_frac_tail, value);
                }
            }
            _ => {
                panic!("Unexpected value generated");
            }
        }
    }
    unsafe { fprint_list(pos, Some(&format!("pos.{}", file_ext))) };
    unsafe { fprint_list(pos_frac, Some(&format!("pos_frac.{}", file_ext))) };
    unsafe { fprint_list(neg, Some(&format!("neg.{}", file_ext))) };
    unsafe { fprint_list(neg_frac, Some(&format!("neg_frac.{}", file_ext))) };
}
