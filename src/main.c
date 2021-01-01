#include "lib.h"
#include <math.h>
#include <stdio.h>

// #define ELECTROMAG_CONST 1e2
// #define MAX_FORCE 3
// #define ELASTICITY 0.8

// Temporary values
#define ELECTROMAG_CONST 10
#define MAX_FORCE .1
#define ELASTICITY 0.3
#define PARTICLE_DIAMETER 6
#define FRICTION 0.90

int main(int argc, char ** argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

void applyForce(struct Particle * particleA, struct Particle * particleB) {
  // Electromagnetic force:
  // F = k * (Qa * Qb) / r ^ 2

  struct Vector AB = {
    particleB->position.x - particleA->position.x,
    particleB->position.y - particleA->position.y
  };

  float distance = sqrt(
    pow(AB.x, 2) +
    pow(AB.y, 2)
  );

  // No force applied if too close
  if (distance < PARTICLE_DIAMETER) return;

  float force = ELECTROMAG_CONST * -particleA->charge * particleB->charge / pow(distance, 2);
  
  if (force > MAX_FORCE) force = MAX_FORCE;

  // This can be simplified
  struct Vector normalizedAB = {
    AB.x / distance * force,
    AB.y / distance * force
  };

  // This is a simplified implementation
  particleA->velocity.x += normalizedAB.x;
  particleA->velocity.y += normalizedAB.y;
}

void updateParticles() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {
    #define particle particles[i]

    particle.velocity.x *= FRICTION;
    particle.velocity.y *= FRICTION;

    // ToDo:
    // - Reuse force for particle pairs (they experience the same force)
    // - Optimize using lattice?!?
    for (int j = 0; j < PARTICLE_COUNT; j++) {
      if (j == i) continue;
      applyForce(&particles[i], &particles[j]);
    }

    // Basic wall collision detection

    particle.position.x += particle.velocity.x;

    if (particle.position.x < 0 || particle.position.x > BOUNDS_X) {
      particle.position.x -= particle.velocity.x;
      particle.velocity.x *= -ELASTICITY;
    }

    particle.position.y += particle.velocity.y;

    if (particle.position.y < 0 || particle.position.y > BOUNDS_Y) {
      particle.position.y -= particle.velocity.y;
      particle.velocity.y *= -ELASTICITY;
    }
  }
}