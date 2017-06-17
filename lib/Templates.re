
/**
 * Here are all the files we might create.
 * 
 * I probably want to make a ppx similar to
 * [babel-plugin-static-fs](https://www.npmjs.com/package/babel-plugin-static-fs)
 * or [babel-plugin-include](https://www.npmjs.com/package/babel-plugin-include)
 * or [babel-plugin-inline-import](https://www.npmjs.com/package/babel-plugin-inline-import)
 * so that I can put these contents in actual files but then have them inlined
 * at compile time. Something like `[%inline "./lib/jbuild"].
 */

let gitignore = {|
.merlin
_build
*.install
|};

let workspace = {|
(context ((switch 4.02.3)))
(context ((switch 4.03.0)))
(context ((switch 4.04.0)))
|};

module Lib = {
  let make name => "build:\n\tjbuilder build @install\n\n" ^
  "test:\n\tjbuilder runtest\n\n" ^
  "pin:\n\topam pin add .\n\n" ^
  "repin: build\n\topam upgrade " ^ name ^ "\n\n" ^
  "build-all:\n\tjbuilder build --workspace jbuild-workspace.dev @install\n\n" ^
  "test-all:\n\tjbuilder build --workspace jbuild-workspace.dev @runtest\n\n" ^
  ".PHONY: build test pin repin build-all test-all";

  let jbuild name => Printf.sprintf {|
(jbuild_version 1)

(library (
  (name %s)
  (public_name %s)
  (libraries ())))
|} name name;

  let re = {|
let rec fib n => {
  switch n {
  | 0 => 0
  | 1 => 1
  | _ when n < 0 => 0
  | _ => (fib (n - 1)) + (fib (n - 2))
  }
};
|};

  let ml = {|
let rec fib n = match n with
  | 0 => 0
  | 1 => 1
  | _ when n < 0 => 0
  | _ => (fib (n - 1)) + (fib (n - 2))
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
  assert (%s.fib 6 == 8);
};

test();
|} capName;

    let ml capName => Printf.sprintf {|
let test () =
  assert (%s.fib 6 == 8)

let _ = test()
|} capName;

  };
};

module Bin = {

  let make name => "build:\n\tjbuilder build @install\n\n" ^
  "run: build\n\tjbuilder exec " ^ name ^ "\n\n" ^
  "test:\n\tjbuilder runtest\n\n" ^
  "pin:\n\topam pin add .\n\n" ^
  "repin: build\n\topam upgrade " ^ name ^ "\n\n" ^
  "build-all:\n\tjbuilder build --workspace jbuild-workspace.dev @install\n\n" ^
  "test-all:\n\tjbuilder build --workspace jbuild-workspace.dev @runtest\n\n" ^
  ".PHONY: build test pin repin build-all test-all";

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
let run () => {
  print_endline "Hello world";
};

let add2 x => x + 2;
|};

    let ml = {|
let run () = print_endline "Hello world"

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
  assert (Lib.Main.add2 5 == 7);
};

test();
|};

    let ml = {|
let test () =
  assert (Lib.Main.add2 5 == 7)

let _ = test()
|};

  };
};
