const cnv = document.querySelector('canvas');
const ctx = cnv.getContext('2d');

const PARTICLE_SIZE = 3;

function checkPerformance(fn, runs = 1) {
  let total = 0;

  for (let i = 0; i < runs; i++) {
    const t0 = performance.now();
    fn();
    const t1 = performance.now();
    total += (t1 - t0);
  }

  console.log(total / runs);
}

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

  function fastDraw() {
    ctx.clearRect(0, 0, cnv.width, cnv.height);

    for (let particle of particles) {
      ctx.fillRect(particle[0], particle[1], PARTICLE_SIZE, PARTICLE_SIZE);
    }
  }

  function draw() {
    // ctx.clearRect(0, 0, cnv.width, cnv.height);
    ctx.fillStyle = 'rgba(255, 255, 255, 0.02)';
    ctx.fillRect(0, 0, cnv.width, cnv.height);
    ctx.beginPath();

    ctx.fillStyle = 'rgb(0, 0, 0)';

    for (let particle of particles) {
      ctx.moveTo(particle[0], particle[1]);
      ctx.arc(particle[0], particle[1], PARTICLE_SIZE, 0, 7);
    }

    ctx.fill();
  }

  function update() {
    requestAnimationFrame(update);
    updateParticles();
    getParticlePositions();
    draw();
    // fastDraw();
  }

  update();
};