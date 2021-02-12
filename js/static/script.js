const mspfCounter = document.querySelector('#mspf-counter');
const fpsCounter = document.querySelector('#fps-counter');
const realFpsCounter = document.querySelector('#real-fps-counter');
const cnv = document.querySelector('canvas');
const ctx = cnv.getContext('2d');

// This array contains detailed information of each particle
const particles = [];

const PARTICLE_RADIUS = PARTICLE_DIAMETER / 2;

initializeParticleSystem();

function fastDraw() {
  ctx.clearRect(0, 0, cnv.width, cnv.height);

  for (let particle of particles) {
    ctx.fillRect(particle[0], particle[1], PARTICLE_DIAMETER, PARTICLE_DIAMETER);
  }
}

function draw() {
  ctx.clearRect(0, 0, cnv.width, cnv.height);
  // ctx.fillStyle = 'rgba(255, 255, 255, 0.015)';
  // ctx.fillRect(0, 0, cnv.width, cnv.height);
  // ctx.beginPath();

  for (let particle of particles) {
    ctx.beginPath();
    ctx.fillStyle = particle.charge > 0 ? 'red' : 'blue';
    // ctx.moveTo(particle[0], particle[1]);
    ctx.arc(particle.position.x, particle.position.y, PARTICLE_DIAMETER / 2, 0, 7);
    ctx.fill();
  }
}

let lastUpdate = 0;

function update() {
  requestAnimationFrame(update);

  const performance = getPerformance(updateParticles);
  const realPerformance = Date.now() - lastUpdate;

  mspfCounter.innerHTML = Math.round(performance * 100, 4) / 100;
  fpsCounter.innerHTML = 1000 / performance | 0;
  realFpsCounter.innerHTML = 1000 / realPerformance | 0;

  draw();
  lastUpdate = Date.now();
}

update();