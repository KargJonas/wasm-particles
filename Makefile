EF		= ['_main', '_initializeParticleSystem', '_getParticles']
EERM	= ['ccall','cwrap']

clean: compiled.js compiled.wasm
	-rm compiled.js compiled.wasm

all: main.c
	emcc 	-s "EXTRA_EXPORTED_RUNTIME_METHODS=$(EERM)" \
				-s "EXPORTED_FUNCTIONS=$(EF)" \
				-s WASM=1 \
				main.c -o compiled.js