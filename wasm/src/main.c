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
  float abx, aby, nx, ny, powXY, distance, force;
  unsigned int i, j;

  for (i = 0; i < PARTICLE_COUNT - 1; i++) {
    particleA.vx *= FRICTION;
    particleA.vy *= FRICTION;

    for (j = i + 1; j < PARTICLE_COUNT; j++) {
      abx = -particleA.px + particleB.px;
      aby = -particleA.py + particleB.py;

      // float powXY = pow(AB.x, 2) + pow(AB.y, 2); // This little line cost 30
      // ms and 3h to find
      powXY = abx * abx + aby * aby;
      distance = sqrt(powXY);
      // distance = powXY / 7.0; // This is an "approximation" of the squareroot
  
      // No force applied if too close
      if (distance < PARTICLE_DIAMETER || distance > MAX_DIST)
        continue;

      // Electromagnetic force:
      // F = k * (Qa * Qb) / r ^ 2
      force = ELECTROMAG_CONST * -particleA.charge * particleB.charge /
              (powXY * distance);

      if (force > MAX_FORCE)
        force = MAX_FORCE;

      nx = abx * force;
      ny = aby * force;

      particleA.vx += nx;
      particleA.vy += ny;

      particleB.vx -= nx;
      particleB.vy -= ny;
    }
  }

  for (i = 0; i < PARTICLE_COUNT; i++) {
    // Basic wall collision detection

    particleA.px += particleA.vx;

    if (particleA.px < 0 || particleA.px > BOUNDS_X) {
      particleA.px -= particleA.vx;
      particleA.vx *= -ELASTICITY;
    }

    particleA.py += particleA.vy;

    if (particleA.py < 0 || particleA.py > BOUNDS_Y) {
      particleA.py -= particleA.vy;
      particleA.vy *= -ELASTICITY;
    }
  }
}