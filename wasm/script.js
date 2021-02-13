const mspfCounter = document.querySelector('#mspf-counter');
const fpsCounter = document.querySelector('#fps-counter');
const realFpsCounter = document.querySelector('#real-fps-counter');
const cnv = document.querySelector('canvas');
const ctx = cnv.getContext('2d');

const PARTICLE_SIZE = 3;

const socket = io.connect('http://localhost:5500');

socket.on('connect', (data) => {
  socket.emit('join', 'Hello World from client');
});

socket.on('reload', () => {
  console.log('reload')
  window.location.reload();
});

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

    for (let particle of particles) {
      ctx.beginPath();
      ctx.fillStyle = particle[2] > 0 ? 'red' : 'blue';
      ctx.arc(particle[0], particle[1], PARTICLE_SIZE, 0, 7);
      ctx.fill();
    }
  }

  function truncate(number) {
    return (number * 100 | 0) / 100
  }

  let lastUpdate = 0;
  let updates = 0;
  let total = 0;
  let dataCollectionStart = Date.now();

  function update() {
    if (updates >= 1) {
      storeData();
      return;
    }

    requestAnimationFrame(update);
    updates++;

    getParticlePositions();

    const performance = getPerformance(updateParticles);
    // const now = Date.now();
    // const realPerformance = now - lastUpdate;
    // lastUpdate = now;

    total += performance;

    // mspfCounter.innerHTML = Math.round(performance * 100, 4) / 100;
    // fpsCounter.innerHTML = Math.round(1000 / performance);
    // realFpsCounter.innerHTML = Math.round(1000 / realPerformance);

    // draw();
  }

  update();

  function storeData() {
    const average = total / updates;

    const data = {
      total: truncate(total),
      average: truncate(average),
      updates
    };

    socket.emit('get-data', data);
  }
};