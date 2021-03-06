const { program } = require('commander');
const path = require('path');
const express = require('express');
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);
const util = require('util');
const exec = util.promisify(require('child_process').exec);
var fs = require("fs");

const getConfigWASM = (particleCount) => `
#define PARTICLE_COUNT ${particleCount}   // Number of particles
#define BOUNDS_X 800          // Height of canvas
#define BOUNDS_Y 800          // Width of canvas

#define ELECTROMAG_CONST 8    // Electromagnetic constant
#define MAX_FORCE .02         // Strongest force allowed in the system
#define ELASTICITY 0.8        // Energy retained after rebound
#define PARTICLE_DIAMETER 6   // Particle diameter
#define FRICTION 0.9          // Amount of velocity retained after each simulation step
#define MAX_DIST 200          // Max effective force distance (performance)
`;

const getConfigJS = (particleCount) => `
const PARTICLE_COUNT = ${particleCount}   // Number of particles
const BOUNDS_X = 800          // Height of canvas
const BOUNDS_Y = 800          // Width of canvas

const ELECTROMAG_CONST = 15   // Electromagnetic constant
const MAX_FORCE = 0.1         // Strongest force allowed in the system
const ELASTICITY = 0.8        // Energy retained after rebound
const PARTICLE_DIAMETER = 6   // Particle diameter
const FRICTION = 0.9          // Amount of velocity retained after each simulation step
const MAX_DIST = 200          // Max effective force distance (performance)
`

program
  .option('--testing', null, false)
  .option('--dir <path>')
  .option('--results-file <path>')
  .option('--port <port>')
  .option('--config-file <path>')
  .option('--js', null, false)
  .parse();

const options = program.opts();
const dir = path.join(process.cwd(), options.dir);

const particleAmounts = [1, 10, 50, 100, 200, 300, 500, 1000, 2000, 5000, 6000, 7000, 8000];
let iteration = 0;

app.use(express.static(dir), express.json());

const getConfig = options.js ? getConfigJS : getConfigWASM;

if (options.testing) {
  let data = [];

  async function dataCollectionComplete() {
    data.shift();
    console.log('Data Collection Complete.');
    fs.writeFileSync(options.resultsFile, JSON.stringify(data), "utf8");
    console.log('Data saved to results file.');
    await modifyAndRebuild(particleAmounts[0]);
  }

  async function modifyAndRebuild(particleAmount) {
    // Modify config
    fs.writeFileSync(path.join(process.cwd(), options.configFile), getConfig(particleAmount), "utf8");

    // No need to rebuild for JS
    if (options.js) return;

    // Trigger recompile
    console.log('Triggerning rebuild')
    await runCommand('make main');
  }

  // Run command
  async function runCommand(command) {
    try {
      const { stdout, stderr } = await exec(command);
      console.log('stdout:', stdout);
      console.log('stderr:', stderr);
    } catch (err) {
      console.error(err);
    };
  };

  io.on('connection', (socket) => {
    console.log('Connection established.');

    socket.on('disconnect', () => {
      console.log('Connection closed.');
      iteration++;
    });

    socket.on('get-data', async (dataPoint) => {
      console.log('Received data.');
      console.log(dataPoint);
      data.push(dataPoint);

      if (iteration >= particleAmounts.length) {
        dataCollectionComplete();
        return;
      }

      const particleAmount = particleAmounts[iteration];
      console.log(`Running tests with ${particleAmount} particles.`);

      await modifyAndRebuild(particleAmount);

      // Reload webpage
      socket.emit('reload');
    })
  });
}

http.listen(options.port, () => {
  console.log('Listening ...');
});