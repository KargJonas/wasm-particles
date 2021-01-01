Module.onRuntimeInitialized = () => {
  const test = Module.cwrap('test', 'number', ['number']);
  console.log(test(2));
}