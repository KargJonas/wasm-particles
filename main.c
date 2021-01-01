#include "lib.h"

int main(int argc, char ** argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

void updateParticles() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {
    #define particle particles[i]

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