void applyForce(struct Particle * particleA, struct Particle * particleB) {
  struct Vector AB = {
    particleB->position.x - particleA->position.x,
    particleB->position.y - particleA->position.y
  };

  float distance = sqrt(pow(AB.x, 2) + pow(AB.y, 2));

  if (distance < PARTICLE_DIAMETER) return;

  float relForce = ELECTROMAG_CONST * -particleA->charge * particleB->charge / distance;

  if (relForce > MAX_FORCE) relForce = MAX_FORCE;

  particleA->velocity.x += AB.x / relForce;
  particleA->velocity.y += AB.y / relForce;
}