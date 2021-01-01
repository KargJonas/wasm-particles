
Module.onRuntimeInitialized = () => {
  const initializeParticleSystem = Module.cwrap('initializeParticleSystem', null, [null]);
  const getParticleArrayPointer = Module.cwrap('getParticleArrayPointer', 'number', [null]);
  const getParticleArraySize = Module.cwrap('getParticleArraySize', 'number', [null]);
  const getParticleStructSize = Module.cwrap('getParticleStructSize', 'number', [null]);

  initializeParticleSystem();
  console.log('Particle array at heap location: ' + getParticleArrayPointer());
  console.log('Particle array size: ' + getParticleArraySize());
  console.log('Particle struct size: ' + getParticleStructSize());

  const particleArrayPointer = getParticleArrayPointer();
  const particleArraySize = getParticleArraySize();
  const particleArrayEnd = particleArrayPointer + particleArraySize;
  const particleStructSize = getParticleStructSize();

  // Reads the particle positions from heap
  function getParticlePositions() {
    for (let i = particleArrayPointer; i < particleArrayEnd; i += particleStructSize) {
      console.log(Module.getValue(i + 4, 'float'));
    }
  }

  getParticlePositions();
};