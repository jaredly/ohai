# Ohai - easy setup for ocaml/reason native projects

Think of it as the `npm init` or the `cargo new` for jbuilder + opam.

- [jbuilder docs](https://jbuilder.readthedocs.io/en/latest/)
- [opam docs](https://opam.ocaml.org/doc/Usage.html)

```bash
~$ ohai --bin example
Creating new executable project "example" in example/
~$ cd example
~$ tree
.
├── Makefile
├── bin
│   ├── jbuild
│   └── example.re
├── jbuild-workspace.dev
├── lib
│   ├── Main.re
│   └── jbuild
├── test
│   ├── jbuild
│   └── test.re
└── example.opam

3 directories, 9 files
~$ make run
jbuilder build @install
       refmt bin/example.re.ml
    ocamldep bin/example.depends.ocamldep-output
      ocamlc lib/lib.{cmi,cmo,cmt}
       refmt lib/Main.re.ml
    ocamldep lib/lib.depends.ocamldep-output
      ocamlc lib/lib__Main.{cmi,cmo,cmt}
      ocamlc bin/example.{cmi,cmo,cmt}
    ocamlopt lib/lib.{cmx,o}
    ocamlopt lib/lib__Main.{cmx,o}
    ocamlopt lib/lib.{a,cmxa}
    ocamlopt bin/example.{cmx,o}
    ocamlopt bin/example.exe
jbuilder exec example
Hello world
```

Then take a look at the generated `Makefile` and source files for more info on
how to get started!

## Why do we need this?

If you haven't done it before, setting up all the `jbuild` and `opam` files
can be a bit confusing. If you have done it before, it can be tedious!

`ohai` gets the boilerplate out of the way so you can start building your
thing.

## Installation

Make sure you have [ocaml installed](https://opam.ocaml.org/doc/Install.html) (`brew install opam` on osx).

Then go ahead and pin to this repository.
```
opam pin add ohai git+https://github.com/jaredly/ohai
```

_The current version of ocaml installed by homebrew is `4.05.0`, but ohai expects ocaml verion `4.02.3`, `4.03.0`, or `4.04.0`.
Run `opam switch 4.04.0` if the opam pin command fails._ 


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

  -i --interactive  ask for information interactively (coming soon)
  --overwrite       write files even if directory is not empty
  --bin             use template for an executable
  --lib             use template for a library [default]
  --ml              don't use reason syntax
```

## Roadmap

- make a ppx for inlining static files (see `Templates.re`)
- have a template for ppxs
