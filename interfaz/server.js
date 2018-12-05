var express = require("express");
var app = express();
var upload = require('express-fileupload');
const http = require('http');
http.Server(app).listen(3000); // make server listen on port 80

app.use(upload()); // configure middleware
app.use(express.static('src'));
console.log("Server Started at port 3000");

app.get('/', function (req, res) {
  res.sendFile(__dirname + 'src/index.html');
})
app.post('/upload', function (req, res) {
  console.log('Numero de palabras ', req.body.nwords);
  if (req.files.file) {
    var file = req.files.file,
    name = file.name,
    type = file.mimetype;
    console.log('Archivo: ', name);
    var uploadpath = __dirname + '/uploads/' + name;
    file.mv(uploadpath, function (err) {
      if (err) {
        console.log("File Upload Failed", name, err);
        res.send("Error Occured!")
      }
      else {
        console.log("File Uploaded", name);
        res.send('Done! Uploading files');
      }
    });
  }else {
    res.send("No File selected !");
    res.end();
  };
})
