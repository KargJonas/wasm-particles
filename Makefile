EF		= ['_main', '_initializeParticleSystem', '_getParticleArraySize', '_getParticleArrayPointer', '_getParticleStructSize', '_updateParticles']
EERM	= ['ccall', 'cwrap', 'getValue']

STATIC_DIR 	= ./wasm
OUT_DIR 		= $(STATIC_DIR)/build
SRC_DIR 		= ./wasm/src

SERVER			= /home/jonas/code/testing-wasm/wasm-particles/server/main.js

clean: $(OUT_DIR)
	-rm -rf $(OUT_DIR)

main: $(SRC_DIR)/main.c $(SRC_DIR)/main.h $(SRC_DIR)/lib.c $(SRC_DIR)/config.h
	@echo Building WASM executables from $(SRC_DIR)
	-mkdir -p $(OUT_DIR)
	-emcc -s "EXTRA_EXPORTED_RUNTIME_METHODS=$(EERM)" \
				-s "EXPORTED_FUNCTIONS=$(EF)" \
				-s WASM=1 \
				$(SRC_DIR)/main.c -o $(OUT_DIR)/compiled.js