
let info_for args => {
  open Args.T;
  let default = Info.default args;
  if (args.yes) {
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
    Sys.readdir "." != [||]
  }
};

let validate_info args info => {
  open Args.T;
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

let run () => {
  let args = Args.parse (Sys.argv);
  let info = info_for args;
  validate_info args info;
  let files = Files.generate info;
  print_endline (Opam.build info)
};
