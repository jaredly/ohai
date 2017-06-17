
let info_for args => {
  open Args.Init;
  let default = Info.default args;
  if (args.interactive) {
    default
  } else {
    default /* TODO interactive */
  };
};

let fail message => {
  print_endline message;
  exit 1;
};

let will_overwrite info => {
  open Info.T;
  if (info.new_directory) {
    Sys.file_exists info.name
  } else {
    let contents = Sys.readdir ".";
    contents != [||] && contents != [|".git"|]
  }
};

let validate_info args info => {
  open Args.Init;
  open Info.T;
  if (will_overwrite info) {
    if (args.overwrite) {
      print_endline "Overwriting existing files";
    } else {
      fail "Would overwrite existing files. Pass --overwrite to do it anyway"
    }
  };
  /* TODO more validation? */
};

let mkdirs name => {
  let parts = CCString.split_on_char '/' name;
  let rec loop parts parent => switch parts {
  | [] | [_] => ()
  | [part, ...rest] => {
    let full = (parent ^ "/" ^ part);
    if (not (CCIO.File.exists full)) {
      Unix.mkdir full 0o755;
    };
    loop rest full
  }
  };

  loop parts ".";
};

let write_file (name, contents) => {
  mkdirs name;
  let file = CCIO.File.make name;
  CCIO.File.write_exn file contents;
};

let run () => {
  let cmd = Args.parse (Sys.argv);
  switch cmd {
  | NoCmd
  | Help => {
    print_endline Args.help;
    exit 1
  }
  | Init args => {
    let info = info_for args;
    validate_info args info;
    Printf.printf "Creating new %s project %S in %s/\n"
      (info.executable ? "executable" : "library")
      info.name
      (info.new_directory ? info.name : ".");
    let files = Files.generate info;
    List.iter write_file files;
  }
  }
  /*print_endline (Opam.build info)*/
};
