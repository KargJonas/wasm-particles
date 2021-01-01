Module.onRuntimeInitialized = () => {
  const initializeParticleSystem = Module.cwrap('initializeParticleSystem', null, [null]);
  const getParticles = Module.cwrap('getParticles', 'number', [null]);

  initializeParticleSystem();
  console.log(getParticles());
};

