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

void initializeParticleSystem() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {    
    struct Vector initialPosition = {
      (float)(rand() % BOUNDS_X),
      (float)(rand() % BOUNDS_Y)
    };

    struct Vector initialVelocity = {
      (float)(rand() % 100 - 50) / 70.0,
      (float)(rand() % 100 - 50) / 70.0
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

// Returns the size of the array
int * getParticleArraySize() {
  return (int*)sizeof(particles);
}

// Returns the size of the individual structs within the array.
int * getParticleStructSize() {
  return (int*)sizeof(particles[0]);
}