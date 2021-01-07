#include <math.h>
#include <stdio.h>

#include "config.h"
#include "lib.c"

#define particleA particles[i]
#define particleB particles[j]

// This array contains detailed information of each particle
Particle particles[PARTICLE_COUNT];

int main(int argc, char **argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

void updateParticles() {
  for (int i = 0; i < PARTICLE_COUNT - 1; i++) {
// #define particle particleA

    float powXY, distance, force;

    particleA.velocity.x *= FRICTION;
    particleA.velocity.y *= FRICTION;

    for (int j = i + 1; j < PARTICLE_COUNT; j++) {
      Vector AB = {particleB.position.x - particleA.position.x,
                   particleB.position.y - particleA.position.y};

      // float powXY = pow(AB.x, 2) + pow(AB.y, 2); // This little line cost 30
      // ms and 3h to find
      powXY = AB.x * AB.x + AB.y * AB.y;
      distance = sqrt(powXY);

      // No force applied if too close
      if (distance < PARTICLE_DIAMETER || distance > MAX_DIST)
        continue;;

      // Electromagnetic force:
      // F = k * (Qa * Qb) / r ^ 2
      force = ELECTROMAG_CONST * -particleA.charge * particleB.charge /
                    (powXY * distance);

      // printf("%f\n", force);

      if (force > MAX_FORCE)
        force = MAX_FORCE;

      // This can be simplified
      Vector normalizedAB = {AB.x * force, AB.y * force};

      // This is a simplified implementation
      particleA.velocity.x += normalizedAB.x;
      particleA.velocity.y += normalizedAB.y;

      particleB.velocity.x -= normalizedAB.x;
      particleB.velocity.y -= normalizedAB.y;
    }
  }

  for (int i = 0; i < PARTICLE_COUNT; i++) {
    // Basic wall collision detection

    particleA.position.x += particleA.velocity.x;

    if (particleA.position.x < 0 || particleA.position.x > BOUNDS_X) {
      particleA.position.x -= particleA.velocity.x * 10;
      particleA.velocity.x *= -ELASTICITY;
    }

    particleA.position.y += particleA.velocity.y;

    if (particleA.position.y < 0 || particleA.position.y > BOUNDS_Y) {
      particleA.position.y -= particleA.velocity.y * 10;
      particleA.velocity.y *= -ELASTICITY;
    }
  }
}
