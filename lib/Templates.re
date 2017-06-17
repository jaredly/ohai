
let gitignore = {|
.merlin
_build
|};

let jbuild_lib name => Printf.sprintf {|
(jbuild_version 1)

(library (
  (name %s)
  (public_name %s)
  (libraries ())))
|} name name;

let jbuild_bin name => Printf.sprintf {|
(jbuild_version 1)

(executable (
  (name %s)
  (public_name %s)
  (libraries (lib))))
|} name name;

let jbuild_bin_lib = {|
(jbuild_version 1)

(library (
  (name lib)
  (libraries ())))
|};