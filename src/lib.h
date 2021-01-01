#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define PARTICLE_COUNT 500
#define BOUNDS_X 800
#define BOUNDS_Y 800

struct Vector {
  float x;
  float y;
};

struct Particle {
  struct Vector position;
  struct Vector velocity;
  float charge;
};

// This array contains detailed information of each particle
struct Particle particles[PARTICLE_COUNT];

void initializeParticleSystem() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {    
    struct Vector initialPosition = {
      (float)(rand() % BOUNDS_X),
      (float)(rand() % BOUNDS_Y)
    };

    // struct Vector initialVelocity = {
    //   (float)((rand() % 100 - 50) / 70.0),
    //   (float)((rand() % 100 - 50) / 70.0)
    // };

    struct Vector initialVelocity = { 0, 0 };

    float charge = (rand() % 2) ? -1 : 1;
    // float charge = 1.0;

    struct Particle newParticle = {
      initialPosition,
      initialVelocity,
      charge
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