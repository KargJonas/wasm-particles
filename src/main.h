#include "config.h"
#include <time.h>

struct _Particle {
  float px, py;
  float vx, vy;
  int charge;
};

// typedef struct _Vector Vector;
typedef struct _Particle Particle;

extern Particle particles[PARTICLE_COUNT];
