var express = require("express");
var app = express();
var upload = require('express-fileupload');
const dgram = require('dgram');
const http = require('http');
var startTime;

http.Server(app).listen(3000); // make server listen on port 80
app.use(upload()); // configure middleware
app.use(express.static('src'));
app.set('view engine', 'pug');
const MasterPort = 7200, MasterAddress = '10.100.74.35';

console.log("Server Started at port 3000");

// INDEX
app.get('/', function (req, res) {
  res.sendFile(__dirname + 'src/index.html');
});

//Muestra la respuesta y el número de palíndromos encontrados
app.get('/response', function (req, res) {
  var list = ['Anita lava la tina', 'esto es otro ejemplo', 'tu gfa te odia'];
  res.render('response', { list: list, listlen: list.length });
});

// Subida de archivo y variable N
app.post('/upload', function (req, res) {
  if (req.files.file) {
    startTime = process.hrtime();
    var nwords = Number(req.body.nwords);
    console.log('Numero de palabras ', nwords);
    var file = req.files.file,
    name = file.name,
    type = file.mimetype;
    console.log('Archivo: ', name);
    var uploadpath = __dirname + '/uploads/' + name;
    file.mv(uploadpath, function (err) {
      if (err) {
        console.log("File Upload Failed", name, err);
        res.send("Error Occured!");
      }
      else {
        console.log("File Uploaded", name);
        sendUDP(name, nwords, res)
      }
    });
  }else {
    res.send("No File selected !");
    res.end();
  };
});


// *****************
// INICIO CÓDIGO UDP
// *****************

function sendUDP(fileName, nwords, resp) {
  const socket = dgram.createSocket('udp4');
  var mstr = String(nwords) + ',' + fileName;
  var buf=Buffer.from(mstr);
  console.log('buffer:', mstr);

  socket.on('error', (err) => {
    console.log(`socket error:\n${err.stack}`);
    socket.close();
  });
  socket.on('listening', () => {
    const address = socket.address();
    console.log(`socket listening ${address.address}:${address.port}`);
  });
  socket.on('message', (msg, rinfo) => {
    console.log(`socket got: ${msg} from ${rinfo.address}:${rinfo.port}`);
    var list = msg.toString().split('|');
    var elapsedSeconds = parseHrtimeToSeconds(process.hrtime(startTime));
    list.forEach(l=>{
      parseSpecialChars(l);
    });
    for (i = 0; i < list.length; i++) {
      list[i] = parseSpecialChars(list[i]);
    }
    resp.render('response', { list: list, listlen: list.length, time: elapsedSeconds });
    socket.close()
  });
  socket.bind(1234);

  socket.send(buf, MasterPort, MasterAddress, (err) => {
    if (err) {
      console.log('UDP Send failed', err);
      resp.send('Algo salió mal :(');
    }
  });
}

function parseHrtimeToSeconds(hrtime) {
  var seconds = (hrtime[0] + (hrtime[1] / 1e9)).toFixed(3);
  return seconds;
}

function parseSpecialChars(str){
  var diccionario = {
    '#':'Á','$':'É','%':'Í','&':'Ó',
    '(':'Ú',')':'á','=':'é','+':'í',
    '[':'ó','*':'ú','}':'ñ','{':'Ñ'
    };
  for (k in diccionario) {
    str = str.replace(k,diccionario[k])
    // console.log(k + diccionario[k]);
  }
  return str;
}