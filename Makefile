EF		= ['_main', '_initializeParticleSystem', '_getParticleArraySize', '_getParticleArrayPointer', '_getParticleStructSize', '_updateParticles']
EERM	= ['ccall', 'cwrap', 'getValue']

OUT_DIR = ./build
SRC_DIR = ./src

clean: $(OUT_DIR)/compiled.js $(OUT_DIR)/compiled.wasm
	-rm $(OUT_DIR)/compiled.js $(OUT_DIR)/compiled.wasm

all: $(SRC_DIR)/main.c
	emcc 	-s "EXTRA_EXPORTED_RUNTIME_METHODS=$(EERM)" \
				-s "EXPORTED_FUNCTIONS=$(EF)" \
				-s WASM=1 \
				$(SRC_DIR)/main.c -o $(OUT_DIR)/compiled.js