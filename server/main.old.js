const path = require('path');

const express = require('express');
const app = express();

const server = require('http').createServer(app);
const io = require('socket.io')(server);

const { program } = require('commander');
const http = require('http2').createServer(app);

program
  .option('--testing', null, false)
  .option('--dir <path>')
  .option('--results-file <path>')
  .option('--port <port>')
  .parse();

const options = program.opts();
const dir = path.join(process.cwd(), options.dir);

app.use(express.static(dir), express.json());

if (options.testing) {
  app.post('/data', (req, res) => {
    console.log(req.body);
    res.sendStatus(200);
  });
}

// http.listen(3000, () => {
  // console.log('Listening...');

// })

app.listen(options.port, () => {
  console.log('Listening ...')
});