function initializeParticleSystem() {
  for (let i = 0; i < PARTICLE_COUNT; i++) {
    const position = {
      x: Math.random() * BOUNDS_X,
      y: Math.random() * BOUNDS_Y
    };

    const velocity = { x: 0, y: 0 };
    const charge = Math.random() * 2 < 1 ? -1 : 1;

    const newParticle = {
      position,
      velocity,
      charge
    };

    particles[i] = newParticle;
  }
}