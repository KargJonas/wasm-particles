const mspfCounter = document.querySelector('#mspf-counter');
const fpsCounter = document.querySelector('#fps-counter');
const realFpsCounter = document.querySelector('#real-fps-counter');
const cnv = document.querySelector('canvas');
const ctx = cnv.getContext('2d');

const PARTICLE_SIZE = 3;

Module.onRuntimeInitialized = () => {
  const initializeParticleSystem = Module.cwrap('initializeParticleSystem', null, [null]);
  const getParticleArrayPointer = Module.cwrap('getParticleArrayPointer', 'number', [null]);
  const getParticleArraySize = Module.cwrap('getParticleArraySize', 'number', [null]);
  const getParticleStructSize = Module.cwrap('getParticleStructSize', 'number', [null]);
  const updateParticles = Module.cwrap('updateParticles', null, [null]);
  const setTimeScale = Module.cwrap('setTimeScale', null, ['number']);

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
        Module.getValue(pointer + 4, 'float'),
        Module.getValue(pointer + 16, 'float')
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
    ctx.clearRect(0, 0, cnv.width, cnv.height);
    // ctx.fillStyle = 'rgba(255, 255, 255, 0.015)';
    // ctx.fillRect(0, 0, cnv.width, cnv.height);
    // ctx.beginPath();

    // ctx.fillStyle = 'rgb(0, 0, 0)';

    for (let particle of particles) {
      ctx.beginPath();
      ctx.fillStyle = particle[2] > 0 ? 'red' : 'blue';
      // ctx.moveTo(particle[0], particle[1]);
      ctx.arc(particle[0], particle[1], PARTICLE_SIZE, 0, 7);
      ctx.fill();
    }

    // ctx.fill();
  }

  setTimeScale(0.0004);

  let lastUpdate = 0;

  function update() {
    requestAnimationFrame(update);

    const performance = getPerformance(updateParticles);
    const realPerformance = Date.now() - lastUpdate;

    mspfCounter.innerHTML = Math.round(performance * 100, 4) / 100;
    fpsCounter.innerHTML = 1000 / performance | 0;
    realFpsCounter.innerHTML = 1000 / realPerformance | 0;

    getParticlePositions();
    draw();
    lastUpdate = Date.now();
  }

  update();
};