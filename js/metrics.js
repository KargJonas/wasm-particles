// This method returns the average function execution time
function getPerformance(fn) {
  const t0 = performance.now();
  fn();
  return (performance.now() - t0);
}

// This method returns the average function execution time for n runs.
function getAveragePerformance(fn, runs = 1) {
  let total = 0;

  for (let i = 0; i < runs; i++) {
    const t0 = performance.now();
    fn();
    total += (performance.now() - t0);
  }

  return total / runs;
}