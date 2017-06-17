
/**
 * CLI argument parsing!
 */

module Init = {
  type t = {
    interactive: bool,
    name: option string,
    reason: bool,
    overwrite: bool,
    bin: bool,
  };

  let default = {
    interactive: false,
    name: None,
    overwrite: false,
    bin: false,
    reason: true,
  };
};

module Cmds = {
  type t =
    | Init Init.t
    | NoCmd
    | Help;
    /* TODO more commands? */
};

let valid_name_rx = Str.regexp "^[a-z0-9_]+$";
let is_valid_name name => Str.string_match valid_name_rx name 0;

let help = {|Usage: ohai [cmd] [opts]

Options:
  -h --help         show this info

Commands:

> help

show this help

> init [?name] [opts]

If you provide a package name, a directory of that name
will be created with the generated files. If you do not,
the current directory (if empty) will be used.

  -i --interactive  ask for information interactively
  --overwrite       write files even if directory is not empty
  --bin             use template for an executable
  --lib             use template for a library [default]
  --ml              don't use reason syntax
|};

let cmd_init opts arg => {
  open Init;
  switch arg {
  | "-i"
  | "--interactive" => {...opts, interactive: true}
  | "--overwrite" => {...opts, overwrite: true}
  | "--bin" => {...opts, bin: true}
  | "--lib" => {...opts, bin: false}
  | "--ml" => {...opts, reason: false}
  | "-h" | "--help" => {
    print_endline help;
    exit 1;
  }
  | "." => {...opts, name: None}
  | name when (is_valid_name name) => {...opts, name: Some name}
  | _ => {
    Printf.printf "!! Unexpected parameter %s\n\n" arg;
    print_endline help;
    exit 1;
  }
  };
};

let pick_cmd arg => {
  switch arg {
  | "-h" | "--help" | "help" => {
    Cmds.Help
  }
  | "init" => Cmds.Init Init.default
  /* If the first argument isn't a command, we default
   * to the "init" command. */
  | _ => Cmds.Init (cmd_init Init.default arg)
  }
};

let consume (first, opts) arg => {
  open Cmds;
  if (first) {
    (false, opts);
  } else {
    let opts = switch opts {
    | NoCmd => pick_cmd arg
    | Init opts => Init (cmd_init opts arg)
    | Help => Help
    };
    (false, opts)
  }
};

let parse args => snd (Array.fold_left consume (true, Cmds.NoCmd) args);
