const { program } = require('commander');
const path = require('path');
const express = require('express');
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);
const util = require('util');
const exec = util.promisify(require('child_process').exec);

program
  .option('--testing', null, false)
  .option('--dir <path>')
  .option('--results-file <path>')
  .option('--port <port>')
  .parse();

const options = program.opts();
const dir = path.join(process.cwd(), options.dir);

app.use(express.static(dir), express.json());

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
  });

  socket.on('get-data', async (data) => {
    console.log('Received data.');
    console.log(data);

    // Trigger recompile
    console.log('Triggerning rebuild')
    await runCommand('make main');

    // Reload webpage
    socket.emit('reload');
  })
});

http.listen(options.port, () => {
  console.log('Listening ...');
});