#define PARTICLE_COUNT 600    // Number of particles
#define BOUNDS_X 800          // Height of canvas
#define BOUNDS_Y 800          // Width of canvas

#define ELECTROMAG_CONST 10   // Electromagnetic constant
#define MAX_FORCE .1          // Strongest force allowed in the system
#define ELASTICITY 0.8        // Energy retained after rebound
#define PARTICLE_DIAMETER 6   // Particle diameter
#define FRICTION 0.90         // Amount of velocity retained after each simulation step
#define MAX_DIST 100           // Max effective force distance (performance)
#define DEFAULT_TIMESCALE 1   // Default timescale