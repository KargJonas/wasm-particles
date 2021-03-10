const cnv = document.querySelector('canvas');
const ctx = cnv.getContext('2d');

const PARTICLE_SIZE = 3;

Module.onRuntimeInitialized = () => {
  const initializeParticleSystem = Module.cwrap('initializeParticleSystem', null, [null]);
  const getParticleArrayPointer = Module.cwrap('getParticleArrayPointer', 'number', [null]);
  const getParticleArraySize = Module.cwrap('getParticleArraySize', 'number', [null]);
  const getParticleStructSize = Module.cwrap('getParticleStructSize', 'number', [null]);
  const updateParticles = Module.cwrap('updateParticles', null, [null]);

  initializeParticleSystem();

  const particleArrayPointer = getParticleArrayPointer();
  const particleArraySize = getParticleArraySize();
  const particleStructSize = getParticleStructSize();

  const particleCount = particleArraySize / particleStructSize;
  const particles = [];

  function getParticlePositions() {
    for (let i = 0; i < particleCount; i++) {
      const pointer = particleArrayPointer + i * particleStructSize;

      particles[i] = [
        Module.getValue(pointer, 'float'),
        Module.getValue(pointer + 4, 'float'),
        Module.getValue(pointer + 16, 'float')
      ];
    }
  }

  function draw() {
    ctx.clearRect(0, 0, cnv.width, cnv.height);

    for (let particle of particles) {
      ctx.beginPath();
      ctx.fillStyle = particle[2] > 0 ? 'red' : 'blue';
      ctx.arc(particle[0], particle[1], PARTICLE_SIZE, 0, 7);
      ctx.fill();
    }
  }

  function update() {
    requestAnimationFrame(update);

    getParticlePositions();
    updateParticles();
    draw();
  }

  update();
};