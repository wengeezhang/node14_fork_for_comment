const net = require('net');
// 2.创建一个服务
const server = net.createServer((c) => {
  // 'connection' listener.
  console.log('client connected');
  c.on('end', () => {
    console.log('end');
  });
  c.on('data', () => {
      console.log('data event');
      setTimeout(() => {
        console.log('timer1,....');
        setTimeout(() => {
          console.log('timer2....');
        }, 1000 * 3)
      }, 1000 * 5)
      setTimeout(() => {
        console.log('timer0000,....');
      }, 1000 * 2)
      c.write('HTTP/1.1 200 OK\r\n');
        c.write('Connection: keep-alive\r\n');
        c.write('Content-Length: 12\r\n');
        c.write('\r\n');
        c.write('hello world!');
  })
});
server.on('error', (err) => {
  throw err;
});
// 3.监听端口
server.listen(9090, () => {
  console.log('server bound');
});


/*const http = require('http');
// 2.创建一个服务
const server = http.createServer((req,res) => {
  // 'connection' listener.
  console.log('req received');
  req.on('data', (data) => {
    console.log('req on data');
  }).on('end', () => {
    console.log('req on end');
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/plain');
    res.end('Hello World on end');
  })
});
server.on('error', (err) => {
  throw err;
});
// 3.监听端口
server.listen(9090, () => {
  console.log('server bound');
});*/