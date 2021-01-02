// pow(6, 1/3)
#define MIN_DIST 1.817

void applyForce(struct Particle * particleA, struct Particle * particleB) {
  float ABx = particleB->position.x - particleA->position.x;
  float ABy = particleB->position.y - particleA->position.y;

  float distance = pow(ABx * ABx + ABy * ABy, 1.5);

  // No force applied if too close
  if (distance < MIN_DIST) return;

  // Electromagnetic force:
  // F = k * (Qa * Qb) / r ^ 2

  float chr = ELECTROMAG_CONST * -particleA->charge * particleB->charge;
  float force = chr / distance;

  if (force > MAX_FORCE) force = MAX_FORCE;

  float Nx = ABx * force;
  float Ny = ABy * force;

  // This is a simplified implementation
  particleA->velocity.x += Nx;
  particleA->velocity.y += Ny;
}