var express = require('express');
var router = express.Router();

router.get('/:uid', function(req, res, next) {
  res.json(
    {
      "title": "DEEP to DEEP",
      "file_name": "sounds/AI_generated_deep_music.mp3"
    }
  );
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
