#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "config.h"

void initializeParticleSystem() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {    
    Vector initialVelocity = { 0, 0 };

    Vector initialPosition = {
      (float)(rand() % BOUNDS_X),
      (float)(rand() % BOUNDS_Y)
    };

    float charge = (rand() % 2) ? -1 : 1;

    Particle newParticle = {
      initialPosition,
      initialVelocity,
      charge
    };

    particles[i] = newParticle;
  }
}

// Returns the location of the particle array
Particle *getParticleArrayPointer() {
  return particles;
}

// Returns the size of the array
int *getParticleArraySize() {
  return (int*)sizeof(particles);
}

// Returns the size of the individual structs within the array.
int *getParticleStructSize() {
  return (int*)sizeof(particles[0]);
}