
build:
	jbuilder build @install

run: build
	jbuilder exec ohai
