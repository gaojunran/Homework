// in c code, all `anyhow` errors should be simply eprintf and exit(1)

use std::{
    env, fs,
    io::{self, Read, Write},
    path::{Path, PathBuf},
};

use anyhow::{anyhow, Context, Ok, Result};

const BUFSIZ: usize = 8192; // in c code we have this macro, include it

fn copy_file(src: &Path, dest: &Path) -> anyhow::Result<()> {
    dbg!(src, dest);
    // check if file exists
    // in c code, is_file and is_dir should be encapsulated in functions
    if !fs::metadata(src)?.is_file() {
        return Err(anyhow!("File {} does not exist", src.display()));
    }
    // check if the file is tried to be copied to itself
    // in c code, you need to encapsulate a function "to_abs_path"
    // and check if the abs paths are the same
    if src == dest {
        return Err(anyhow!(
            "File {} is tried to be copied to itself",
            src.display()
        ));
    }
    // check if file already exists in destination
    if dest.is_file() {
        println!(
            "File {} already exists in destination. Overwrite? [y/n] ",
            src.display()
        );
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        if input.trim() != "y" {
            println!("Skipping file {}.", src.display());
            return Ok(());
        }
    }
    // in c code, file_name should be encapsulated in a function
    let mut src_file = fs::File::open(src)?;
    let mut dest_file = fs::File::create(dest)?;
    let mut dest_writer = fs::OpenOptions::new()
        .write(true)
        .create(true)
        .truncate(true)
        .open(dest)?;
    let mut buffer = [0u8; BUFSIZ];
    loop {
        let bytes_read = src_file.read(&mut buffer)?;
        if bytes_read == 0 {
            break;
        }
        dest_file.write_all(&buffer[..bytes_read])?;
    }
    dest_writer.flush()?;
    Ok(())
}

fn copy_files(files: &[String], destination: &String) -> anyhow::Result<()> {
    dbg!(files, destination);
    // i'm not sure if c code has this kind of abstraction like `PathBuf`,
    // if no, choose another way to implement this
    let files = files.to_vec().iter().map(PathBuf::from).collect::<Vec<_>>();
    // check if destination is a directory
    if !(fs::metadata(destination)?.is_dir()) {
        return Err(anyhow!("Destination is not a directory"));
    }
    fs::create_dir_all(destination)
        .with_context(|| format!("Failed to create destination directory: {}", destination))?;
    for file in &files {
        copy_file(
            file,
            &Path::new(destination).join(file.file_name().unwrap_or_default()),
        )?;
    }
    println!(
        "{} successfully copied to {}",
        files
            .iter()
            .map(|f| f.display().to_string())
            .collect::<Vec<_>>()
            .join(" "),
        destination,
    );
    Ok(())
}

fn move_files(files: &[String], destination: &String) -> anyhow::Result<()> {
    dbg!(files, destination);
    let files = files.to_vec().iter().map(PathBuf::from).collect::<Vec<_>>();
    // check if destination is a directory
    if !(fs::metadata(destination)?.is_dir()) {
        return Err(anyhow!("Destination is not a directory"));
    }
    fs::create_dir_all(destination)
        .with_context(|| format!("Failed to create destination directory: {}", destination))?;
    for file in &files {
        let dest_path = Path::new(destination).join(file.file_name().unwrap_or_default());
        // first try: hard link
        // in c code you might need link()
        println!("Creating hard link for {}...", file.display());
        if let Err(e) = fs::hard_link(file, &dest_path) {
            println!(
                "Failed to create hard link for {}: {}\nCopy and remove original file instead.",
                file.display(),
                e
            );
            // if hard link fails, try copy
            copy_file(file, &dest_path)?;
            // then remove the original file
            // in c code use unlink()
            fs::remove_file(file)?;
        }
    }
    println!(
        "{} successfully moved to {}",
        files
            .iter()
            .map(|f| f.display().to_string())
            .collect::<Vec<_>>()
            .join(" "),
        destination,
    );
    Ok(())
}

fn main() -> Result<()> {
    let args = env::args().collect::<Vec<_>>();
    if args[0].contains("copy") {
        if args.len() < 3 {
            println!("Usage: copy source1 [source2 ...] destination");
        } else {
            copy_files(&args[1..args.len() - 1], &args[args.len() - 1])?;
        }
    } else if args[0].contains("move") {
        if args.len() < 3 {
            println!("Usage: move source1 [source2 ...] destination");
        } else {
            move_files(&args[1..args.len() - 1], &args[args.len() - 1])?;
        }
    } else {
        panic!("Unreachable code here!");
    }
    Ok(())
}
