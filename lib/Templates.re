
let gitignore = {|
.merlin
_build
*.install
|};

module Lib = {
  /* TODO add hooks for testing */
  let make name => "build:\n\tjbuilder build @install\n\n" ^
  "test:\n\tjbuilder runtest";

  let jbuild name => Printf.sprintf {|
(jbuild_version 1)

(library (
  (name %s)
  (public_name %s)
  (libraries ())))
|} name name;

  let re = {|
let rec fib n => {
  (fib (n - 1)) + (fib (n - 2))
};
|};

  let ml = {|
let rec fib n = (fib (n - 1)) + (fib (n - 2))
|};

  module Test = {
    let jbuild name => Printf.sprintf {|
(jbuild_version 1)

(executable (
  (name test)
  (libraries (%s))
))

(alias (
  (name runtest)
  (deps (test.exe))
  (action (run ${<}))
))
|} name;

    let re capName => Printf.sprintf {|
let test () => {
  assert (%s.fib 5 == 13);
};

test();
|} capName;

    let ml capName => Printf.sprintf {|
let test () =
  assert (%s.fib 5 == 13)

let _ = test()
|} capName;

  };
};

module Bin = {

  let make name => "build:\n\tjbuilder build @install\n\n" ^
  "run:build\n\tjbuilder exec" ^ name ^ "\n\n" ^
  "test:\n\tjbuilder runtest";

  let jbuild name => Printf.sprintf {|
(jbuild_version 1)

(executable (
  (name %s)
  (public_name %s)
  (libraries (lib))))
|} name name;

  let re = "Lib.Main.run();";
  let ml = "let _ = Lib.Main.run()";

  module Lib = {

    let jbuild = {|
(jbuild_version 1)

(library (
  (name lib)
  (libraries ())))
|};

    let re = {|
let main () => {
  print_endline "Hello world";
};

let add2 x => x + 2;
|};

    let ml = {|
let main () = print_endline "Hello world"

let add2 x = x + 2
|};

  };

  module Test = {
    let jbuild = {|
(jbuild_version 1)

(executable (
  (name test)
  (libraries (lib))
))

(alias (
  (name runtest)
  (deps (test.exe))
  (action (run ${<}))
))
|};

    let re = {|
let test () => {
  assert (Lib.add2 5 == 7);
};

test();
|};

    let ml = {|
let test () =
  assert (Lib.add2 5 == 7)

let _ = test()
|};

  };
};


