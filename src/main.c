#include "lib.h"
#include <math.h>

int main(int argc, char ** argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

// struct Vector * add(struct Vector * a, struct Vector * b) { }

struct Vector calculateForce(struct Particle particleA, struct Particle particleB) {
  // Electromagnetic force (k will be omitted):
  // F = k * (Qa * Qb) / r ^ 2

  struct Vector AB = {
    particleB.position.x - particleA.position.x,
    particleB.position.y - particleA.position.y
  };

  float distance = sqrt(
    pow(AB.x, 2) +
    pow(AB.y, 2)
  );

  float force = particleA.charge * particleB.charge / pow(distance, 2);

  // This can be simplified
  struct Vector normalizedAB = {
    AB.x / distance * force,
    AB.y / distance * force
  };
}

void updateParticles() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {
    #define particle particles[i]

    for (int j = 0; j < PARTICLE_COUNT; j++) {

    }

    // Basic wall collision detection

    particle.position.x += particle.velocity.x;

    if (particle.position.x < 0 || particle.position.x > BOUNDS_X) {
      particle.position.x -= particle.velocity.x;
      particle.velocity.x *= -1;
    }

    particle.position.y += particle.velocity.y;

    if (particle.position.y < 0 || particle.position.y > BOUNDS_Y) {
      particle.position.y -= particle.velocity.y;
      particle.velocity.y *= -1;
    }
  }
}