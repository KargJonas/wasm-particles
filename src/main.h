#include "config.h"
#include <sys/types.h>
#include <time.h>

struct _Vector {
  float x;
  float y;
};

struct _Particle {
  struct _Vector position;
  struct _Vector velocity;
  float charge;
};

typedef struct _Vector Vector;
typedef struct _Particle Particle;

extern Particle particles[PARTICLE_COUNT];
