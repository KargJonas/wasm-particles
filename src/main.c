#include <math.h>
#include <stdio.h>

#include "lib.c"
#include "config.h"

// This array contains detailed information of each particle
Particle particles[PARTICLE_COUNT];
float timeScale = DEFAULT_TIMESCALE;
time_t lastUpdate;
time_t timeStep;

// typedef struct Particle Particle;

int main(int argc, char ** argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

void applyForce(Particle * particleA, Particle * particleB) {
  Vector AB = {
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
  timeStep = (clock() - lastUpdate) * timeScale;
  
  for (int i = 0; i < PARTICLE_COUNT - 1; i++) {
#define particle particles[i]

    particle.velocity.x *= (FRICTION * timeStep);
    particle.velocity.y *= (FRICTION * timeStep);

    for (int j = i + 1; j < PARTICLE_COUNT; j++) {
      applyForce(&particles[i], &particles[j]);
    }
  }

  for (int i = 0; i < PARTICLE_COUNT; i++) {
    // Basic wall collision detection

    // ToDo:
    // - Introduce timesteps

    particle.position.x += particle.velocity.x * timeStep;

    if (particle.position.x < 0 || particle.position.x > BOUNDS_X) {
      particle.position.x -= particle.velocity.x  * timeStep * 10;
      particle.velocity.x *= -ELASTICITY;
    }

    particle.position.y += particle.velocity.y * timeStep;

    if (particle.position.y < 0 || particle.position.y > BOUNDS_Y) {
      particle.position.y -= particle.velocity.y * timeStep * 10;
      particle.velocity.y *= -ELASTICITY;
    }
  }

  lastUpdate = clock();
}
