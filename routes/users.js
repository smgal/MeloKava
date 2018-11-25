
var express = require('express');
var router = express.Router();
var path = require('path');
var process = require('process');


var PATH_DIR_APP = path.resolve(process.cwd(), 'app'); // not __dirname
var PATH_DIR_PUBLIC = path.resolve(process.cwd(), 'public');
var PATH_EMOSYNTH = path.resolve(PATH_DIR_APP, 'EmoSynth.exe');

var converting_result = -1;


router.get('/:user_uid', function(req, res, next) {
  var result = "";
  var user_uid = req.params.user_uid;
  var mp3_name = user_uid + '.mp3';
  var path_mp3 = path.resolve(PATH_DIR_PUBLIC, mp3_name);

  console.log("++ REQUESTED UID = " + user_uid);
  console.log("++ Emosynth path = " + PATH_EMOSYNTH);
  console.log("++ MP3 path      = " + path_mp3);
  console.log("++ path.cwd      = " + process.cwd());

  const spawn = require('child_process').spawn, emo_synth = spawn(PATH_EMOSYNTH, [ user_uid, path_mp3 ], { cwd: "app", checkCWD: true });

  emo_synth.stdout.on('data', data => { result += 'STDOUT: ' + data + '<br>'; });
  emo_synth.stderr.on('data', data => { result += 'ERROR: ' + data + '<br>'; });

  emo_synth.on('close', code => {
    error_code = code; // 3221225781 <- DLL error

    if (error_code != 0)
    {
      result += 'child process exited with code: ' + code;
      res.send(result);
      return;
    }

    res.json(
      {
        "title": user_uid,
        "file_name" : mp3_name,
        "ref_file_name": "sounds/AI_generated_deep_music.mp3"
      }
    );
  
    //res.download(path_mp3);
    //res.sendFile(path_mp3);
  });  
});

router.post('/register', function(req, res, next) {
  const crypto = require("crypto");
  const id = crypto.randomBytes(12).toString("hex");
  res.json(
    {
      "id" : id,
      "result" : true
    }
  );
});

module.exports = router;
