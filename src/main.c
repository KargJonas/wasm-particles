#include "lib.h"
#include <math.h>
#include <stdio.h>

#define ELECTROMAG_CONST 10   // Electromagnetic constant
#define MAX_FORCE .1          // Strongest force allowed in the system
#define ELASTICITY 0.8        // Energy retained after rebound
#define PARTICLE_DIAMETER 6   // Particle diameter
#define FRICTION 0.99          // Amount of velocity retained after each simulation step
#define MAX_DIST 200          // Max effective force distance (performance)

int main(int argc, char ** argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

void applyForce(struct Particle * particleA, struct Particle * particleB) {
  struct Vector AB = {
    particleB->position.x - particleA->position.x,
    particleB->position.y - particleA->position.y
  };

  float distance = sqrt(
    pow(AB.x, 2) +
    pow(AB.y, 2)
  );

  // No force applied if too close
  if (distance < PARTICLE_DIAMETER || distance > MAX_DIST) return;

  // Electromagnetic force:
  // F = k * (Qa * Qb) / r ^ 2
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

  particleB->velocity.x -= normalizedAB.x;
  particleB->velocity.y -= normalizedAB.y;
}

void updateParticles() {
  for (int i = 0; i < PARTICLE_COUNT - 1; i++) {
#define particle particles[i]

    particle.velocity.x *= FRICTION;
    particle.velocity.y *= FRICTION;

    for (int j = i + 1; j < PARTICLE_COUNT; j++) {
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