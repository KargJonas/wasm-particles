#define MIN_DIST 300

void applyForce(struct Particle * particleA, struct Particle * particleB) {
  float ABx = particleB->position.x - particleA->position.x;
  float ABy = particleB->position.y - particleA->position.y;

  float distance = pow(ABx * ABx + ABy * ABy, 1.5);

  // No force applied if too close
  if (distance < MIN_DIST) return;

  float chr = ELECTROMAG_CONST * -particleA->charge * particleB->charge;
  float force = chr / distance;

  #define SPEC_MAX_FORCE .02

  if (force > SPEC_MAX_FORCE) force = SPEC_MAX_FORCE;

  float Nx = ABx * force;
  float Ny = ABy * force;

  // This is a simplified implementation
  particleA->velocity.x += Nx;
  particleA->velocity.y += Ny;
}