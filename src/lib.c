#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "main.h"
#include "config.h"

void initializeParticleSystem() {
  for (int i = 0; i < PARTICLE_COUNT; i++) {    
    Vector initialPosition = {
      (float)(rand() % BOUNDS_X),
      (float)(rand() % BOUNDS_Y)
    };

    // Vector initialVelocity = {
    //   (float)((rand() % 100 - 50) / 70.0),
    //   (float)((rand() % 100 - 50) / 70.0)
    // };

    Vector initialVelocity = { 0, 0 };

    float charge = (rand() % 2) ? -1 : 1;
    // float charge = 1.0;

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