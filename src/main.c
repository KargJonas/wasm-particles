#include <math.h>
#include <stdio.h>

#include "lib.c"
#include "config.h"

// This array contains detailed information of each particle
Particle particles[PARTICLE_COUNT];

// typedef struct Particle Particle;

int main(int argc, char ** argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

void applyForce(Particle * particleA, Particle * particleB) {
  // No force applied if one of the particles is part of a neutron.
  if (particleA->charge < -1 || particleB->charge < -1) return;
  if (particleA->charge == 0 && particleB->charge == 0) return;

  Vector AB = {
    particleB->position.x - particleA->position.x,
    particleB->position.y - particleA->position.y
  };

  float distance = sqrt(
    pow(AB.x, 2) +
    pow(AB.y, 2)
  );

  // No force applied if too far away
  if (distance > MAX_DIST) return;

  // Merge to neutron if close enough
  if (distance < PARTICLE_DIAMETER) {
    particleB->charge = -2;
    particleA->charge = 0;
  }

  float force = STRONG_CONST / pow(distance, 2);

  // Only apply electromagnetic force when no  
  if (particleA->charge && particleB->charge) {
    // "Electromagnetic force"
    // F = k * (Qa * Qb) / r ^ 2
    force *= (ELECTROMAG_CONST * -particleA->charge * particleB->charge * 2);
  }
  
  if (force > MAX_FORCE) force = MAX_FORCE;

  // This can be simplified
  Vector normalizedAB = {
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

    particle.velocity.x *= (FRICTION);
    particle.velocity.y *= (FRICTION);

    for (int j = i + 1; j < PARTICLE_COUNT; j++) {
      applyForce(&particles[i], &particles[j]);
    }
  }

  for (int i = 0; i < PARTICLE_COUNT; i++) {
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
