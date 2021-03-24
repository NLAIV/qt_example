const express = require('express');
const router = express.Router();
const example_sql = require('../models/example_model');

router.get('/allPersons',
    function(request,response){
        example_sql.getAllPersons(function(err, dbResult){
            if(err){
                response.json(err);
            }
            else{
                response.json(dbResult);
            }
        }
        )
    }
);

module.exports = router;