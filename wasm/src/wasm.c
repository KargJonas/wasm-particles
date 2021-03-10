#include <stdio.h>
#include <time.h>
#include <math.h>

#include "lib.c"

#define PARTICLE_COUNT 1      // Number of particles
#define BOUNDS_X 800          // Height of canvas
#define BOUNDS_Y 800          // Width of canvas

#define ELECTROMAG_CONST 15   // Electromagnetic constant
#define MAX_FORCE 0.1         // Strongest force allowed in the system
#define ELASTICITY 0.8        // Energy retained after rebound
#define PARTICLE_DIAMETER 6   // Particle diameter
#define FRICTION 0.9          // Amount of velocity retained after each simulation step
#define MAX_DIST 200          // Max effective force distance (performance)

#define particleA particles[i]
#define particleB particles[j]

struct _Particle {
  float px, py;
  float vx, vy;
  int charge;
};

typedef struct _Particle Particle;

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

      powXY = abx * abx + aby * aby;
      distance = sqrt(powXY);
  
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
