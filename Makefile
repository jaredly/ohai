
build:
	jbuilder build @install

# This is essentially the `npm install .`, for installing a local development version of a package
pin:
	opam pin add .

# Once it's pinned, this is what it takes to update the installation
repin: build
	opam upgrade ohai

# This will run all of the `runtest` aliases in our project -- currently just in test/jbuild
test:
	jbuilder runtest

# Cross-version testing! These rules will build & run the tests across multiple ocaml versions
build-all:
	jbuilder build --workspace jbuild-workspace.dev @install

test-all:
	jbuilder runtest --workspace jbuild-workspace.dev

# build & try running our executable
run: build
	jbuilder exec ohai

# A test run w/ some arguments
hello: build
	jbuilder exec ohai -- --bin hello

.PHONY: test build pin repin