
/**
 * Here we just construct the list of files needed, based on the info
 * we've assembled.
 */

let bin_files info => {
  open Info.T;
  let ext = info.reason ? ".re" : ".ml";

  [
    ("Makefile", Templates.Bin.make info.name),
    ("bin/jbuild", Templates.Bin.jbuild info.name),
    ("bin/" ^ info.name ^ ext, (
      info.reason ? Templates.Bin.re : Templates.Bin.ml
    )),
    ("lib/jbuild", Templates.Bin.Lib.jbuild),
    ("lib/Main" ^ ext, (
      info.reason ? Templates.Bin.Lib.re : Templates.Bin.Lib.ml
    )),
    ("test/jbuild", Templates.Bin.Test.jbuild),
    ("test/test" ^ ext, (
      info.reason ? Templates.Bin.Test.re : Templates.Bin.Test.ml
    )),
  ]
};

let lib_files info => {
  open Info.T;
  let ext = info.reason ? ".re" : ".ml";
  let capName = CCString.capitalize_ascii info.name;

  [
    ("Makefile", Templates.Lib.make info.name),
    ("lib/jbuild", Templates.Lib.jbuild info.name),
    ("lib/" ^ info.name ^ ext, (
      info.reason ? Templates.Lib.re : Templates.Lib.ml
    )),
    ("test/jbuild", Templates.Lib.Test.jbuild info.name),
    ("test/test" ^ ext,
      (info.reason ? Templates.Lib.Test.re : Templates.Lib.Test.ml)
      capName),
  ]
};

let generate info => {
  open Info.T;
  let files = [
    (info.name ^ ".opam", Opam.build info),
    ("jbuild-workspace.dev", Templates.workspace),
    (".gitignore", Templates.gitignore),
    ...((info.executable ? bin_files : lib_files) info)
  ];
  if (info.new_directory) {
    List.map
    (fun (name, contents) => (info.name ^ "/" ^ name, contents))
    files
  } else {
    files
  }
};
