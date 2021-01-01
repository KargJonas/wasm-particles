EF		= ['_main', '_initializeParticleSystem', '_getParticleArraySize', '_getParticleArrayPointer', '_getParticleStructSize']
EERM	= ['ccall', 'cwrap', 'getValue']

clean: compiled.js compiled.wasm
	-rm compiled.js compiled.wasm

all: main.c
	emcc 	-s "EXTRA_EXPORTED_RUNTIME_METHODS=$(EERM)" \
				-s "EXPORTED_FUNCTIONS=$(EF)" \
				-s WASM=1 \
				main.c -o compiled.js