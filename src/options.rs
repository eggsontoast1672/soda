use std::path::PathBuf;

struct Options {
    dump_options: bool,
    output_path: Option<PathBuf>,
    files: Vec<String>,
}

impl Default for Options {
    fn default() -> Self {
        Self {
            dump_options: false,
            output_path: None,
            files: Vec::new(),
        }
    }
}

fn print_usage_and_exit(program: &str) -> ! {
    eprintln!("Usage: {} [OPTIONS] INPUT\n", program);
    eprintln!("Options:");
    eprintln!("    -o <FILENAME>        Write output to FILENAME");
    eprintln!("    --tokens             Dump the tokens of a file");
    std::process::exit(1);
}


fn parse_options(argc: i32, argv: &[&str]) -> Options {
    let options = Options::default();
    let mut args = std::env::args();
    let program = args.next().unwrap();

    while let Some(arg) = args.next() {
    }


    for arg in std::env::args() {
        if (std::strcmp(argv[i], "--tokens") == 0) {
            options.dump_tokens = true;
        } else if (std::strcmp(argv[i], "-o") == 0) {
            i++;
            if (i < argc) {
                options.output_path = argv[i];
            } else {
                print_usage_and_exit(argv[0]);
            }
        } else {
            options.files.push_back(argv[i]);
        }
    }

    if (options.files.empty()) {
      print_usage_and_exit(argv[0]);
    }

    return options;
}

