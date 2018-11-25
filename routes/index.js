var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', {
    title: 'Melo Kava!!',
    default_text_for_input: 'sample.json'
  });
});

module.exports = router;
