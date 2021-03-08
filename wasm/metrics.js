// This method returns the average function execution time
function getPerformance(fn) {
  const t0 = performance.now();
  fn();
  return (performance.now() - t0);
}