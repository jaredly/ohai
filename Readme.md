
# Ohai - easy setup for ocaml/reason native projects

```bash
~$ ohai --bin testing
Creating new executable project "testing" in testing/
~$ cd testing
~$ tree
.
├── Makefile
├── bin
│   ├── jbuild
│   └── testing.re
├── jbuild-workspace.dev
├── lib
│   ├── Main.re
│   └── jbuild
├── test
│   ├── jbuild
│   └── test.re
└── testing.opam

3 directories, 9 files
~$ make run
jbuilder build @install
       refmt bin/testing.re.ml
    ocamldep bin/testing.depends.ocamldep-output
      ocamlc lib/lib.{cmi,cmo,cmt}
       refmt lib/Main.re.ml
    ocamldep lib/lib.depends.ocamldep-output
      ocamlc lib/lib__Main.{cmi,cmo,cmt}
      ocamlc bin/testing.{cmi,cmo,cmt}
    ocamlopt lib/lib.{cmx,o}
    ocamlopt lib/lib__Main.{cmx,o}
    ocamlopt lib/lib.{a,cmxa}
    ocamlopt bin/testing.{cmx,o}
    ocamlopt bin/testing.exe
jbuilder exec testing
Hello world
```

## Installation

Here's how to install from `master`
```
opam pin ohai git+https://github.com/jaredly/ohai
```

## Usage

```
~$ ohai
Usage: ohai [cmd] [opts]

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
```
