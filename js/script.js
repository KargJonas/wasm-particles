const cnv = document.querySelector('canvas');
const ctx = cnv.getContext('2d');
const particles = [];

initializeParticleSystem();

function fastDraw() {
  ctx.clearRect(0, 0, cnv.width, cnv.height);

  for (let particle of particles) {
    ctx.fillRect(particle[0], particle[1], PARTICLE_DIAMETER, PARTICLE_DIAMETER);
  }
}

function draw() {
  ctx.clearRect(0, 0, cnv.width, cnv.height);

  for (let particle of particles) {
    ctx.beginPath();
    ctx.fillStyle = particle.charge > 0 ? 'red' : 'blue';
    ctx.arc(particle.position.x, particle.position.y, PARTICLE_DIAMETER / 2, 0, 7);
    ctx.fill();
  }
}

let lastUpdate = 0;
let updates = 0;
let total = 0;
let dataCollectionStart = Date.now();

const updateCount = 100;

function update() {
  requestAnimationFrame(update);
  updateParticles();
  draw();
}

update();