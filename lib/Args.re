
module T = {
  type t = {
    yes: bool,
    name: option string,
    reason: bool,
    overwrite: bool,
    bin: bool,
  };
};

let default = T.{
  yes: false,
  name: None,
  overwrite: false,
  bin: false,
  reason: true,
};

let valid_name_rx = Str.regexp "^[a-z0-9_]+$";
let is_valid_name name => Str.string_match valid_name_rx name 0;

let consume (first, opts) arg => {
  open T;
  if (first) {
    (false, opts);
  } else {
    let res = switch arg {
    | "-y"
    | "--no-input" => {...opts, yes: true}
    | "--overwrite" => {...opts, overwrite: true}
    | "--bin" => {...opts, bin: true}
    | "--lib" => {...opts, bin: false}
    | "--ml" => {...opts, reason: false}
    | name when (is_valid_name name) => {...opts, name: Some name}
    | _ => {
      Printf.printf "!! Ignoring unexpected parameter %s\n" arg;
      opts
    }
    };
    (false, res)
  };
};

let parse args => snd (Array.fold_left consume (true, default) args);
