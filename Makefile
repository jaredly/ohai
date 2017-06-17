
build:
	jbuilder build @install

pin:
	opam pin add .

run: build
	jbuilder exec ohai

hello: build
	jbuilder exec ohai -- --bin hello