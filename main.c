#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PARTICLE_COUNT 100
#define BOUNDS_X 500
#define BOUNDS_Y 500

struct Vector {
  float x;
  float y;
};

struct Particle {
  struct Vector position;
  struct Vector velocity;
};

// This array contains detailed information of each particle
struct Particle particles[PARTICLE_COUNT];

// This array contains only the position of each particle.
// The first half of the values are the x-Positions, the next half are y-Positions.
// float particlePositions[PARTICLE_COUNT << 1];

int main(int argc, char ** argv) {
  time_t current_time;
  srand((unsigned)time(&current_time));
}

void initializeParticleSystem() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {    
    // struct Vector initialPosition = {
    //   rand() % BOUNDS_X,
    //   rand() % BOUNDS_Y
    // };

    // struct Vector initialVelocity = {
    //   (rand() % 100 - 50) / 25.0,
    //   (rand() % 100 - 50) / 25.0
    // };
    
    struct Vector initialPosition = {
      1,
      234234.234234
    };

    struct Vector initialVelocity = {
      0,
      0
    };

    struct Particle newParticle = {
      initialPosition,
      initialVelocity
    };

    particles[i] = newParticle;
  }
}

// Returns the location of the particle array
struct Particle * getParticleArrayPointer() {
  return particles;
}

// Returns the size of the struct.
int * getParticleArraySize() {
  return (int*)sizeof(particles);
}

// Returns the size of the struct.
int * getParticleStructSize() {
  return (int*)sizeof(particles[0]);
}