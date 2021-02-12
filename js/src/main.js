function applyForce(particleA, particleB) {
  const AB = {
    x: particleB.position.x - particleA.position.x,
    y: particleB.position.y - particleA.position.y
  };

  const distance = Math.sqrt(Math.pow(AB.x, 2) + Math.pow(AB.y, 2));

  // No force applied if too close
  if (distance < PARTICLE_DIAMETER || distance > MAX_DIST) return;

  // Electromagnetic force:
  // F = k * (Qa * Qb) / r ^ 2
  let force = ELECTROMAG_CONST * -particleA.charge * particleB.charge / Math.pow(distance, 2);

  if (force > MAX_FORCE) force = MAX_FORCE;

  force /= distance;

  const normalizedAB = {
    x: AB.x * force,
    y: AB.y * force
  };

  particleA.velocity.x += normalizedAB.x;
  particleA.velocity.y += normalizedAB.y;

  particleB.velocity.x -= normalizedAB.x;
  particleB.velocity.y -= normalizedAB.y;
}

function updateParticles() {
  for (let i = 0; i < PARTICLE_COUNT - 1; i++) {
    particles[i].velocity.x *= FRICTION;
    particles[i].velocity.y *= FRICTION;

    for (let j = i + 1; j < PARTICLE_COUNT; j++) {
      applyForce(particles[i], particles[j]);
    }
  }

  for (let i = 0; i < PARTICLE_COUNT; i++) {
    // Basic wall collision detection

    particles[i].position.x += particles[i].velocity.x;

    if (particles[i].position.x < 0 || particles[i].position.x > BOUNDS_X) {
      particles[i].position.x -= particles[i].velocity.x;
      particles[i].velocity.x *= -ELASTICITY;
    }

    particles[i].position.y += particles[i].velocity.y;

    if (particles[i].position.y < 0 || particles[i].position.y > BOUNDS_Y) {
      particles[i].position.y -= particles[i].velocity.y;
      particles[i].velocity.y *= -ELASTICITY;
    }
  }
}