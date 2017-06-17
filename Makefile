
build:
	jbuilder build @install

pin:
	opam pin add .

repin: build
	opam upgrade ohai

run: build
	jbuilder exec ohai

hello: build
	jbuilder exec ohai -- --bin hello