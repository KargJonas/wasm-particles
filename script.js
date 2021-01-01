const cnv = document.querySelector('canvas');
const ctx = cnv.getContext('2d');

Module.onRuntimeInitialized = () => {
  const initializeParticleSystem = Module.cwrap('initializeParticleSystem', null, [null]);
  const getParticleArrayPointer = Module.cwrap('getParticleArrayPointer', 'number', [null]);
  const getParticleArraySize = Module.cwrap('getParticleArraySize', 'number', [null]);
  const getParticleStructSize = Module.cwrap('getParticleStructSize', 'number', [null]);

  initializeParticleSystem();

  const particleArrayPointer = getParticleArrayPointer();
  const particleArraySize = getParticleArraySize();
  const particleStructSize = getParticleStructSize();

  const particles = [];

  // Reads the particle positions from heap
  function getParticlePositions() {
    const particleCount = particleArraySize / particleStructSize;

    for (let i = 0; i < particleCount; i++) {
      const pointer = particleArrayPointer + i * particleStructSize;

      particles[i] = [
        Module.getValue(pointer, 'float'),
        Module.getValue(pointer + 4, 'float')
      ];
    }
  }

  function drawParticles() {
    ctx.beginPath();
    
    for (let particle of particles) {
      ctx.moveTo(...particle);
      ctx.arc(...particle, 8, 0, 7);
    }

    ctx.fill();
  }

  getParticlePositions();
  drawParticles();
};