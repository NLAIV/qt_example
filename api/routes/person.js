const express = require('express');
const router = express.Router();
const person = require('../models/person_model');

router.get('/:id?',
 function(request, response) {
  if (request.params.id) {
    person.getById(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        // [0] = palautetaan json objekti, eli ainoa alkio, ei koko arrayta!
        response.json(dbResult[0]);
      }
    });
  } else {
    person.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
});
router.post('/', 
function(request, response) {
  person.add(request.body, function(err, count) {
    if (err) {
      response.json(err);
    } else {
      //  tietokannan tietueen sijaan (dbResult) voidaan antaa myös tekstivastaus ("teksti").
      response.json("Person added."); 
    }
  });
});

//  Proseduurin "money_action" lisäys.
router.post('/money_action', 
function(request, response) {
  person.moneyAction(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      //  tietokannan tietueen sijaan (dbResult) voidaan antaa myös tekstivastaus ("teksti").
      response.json(dbResult); 
    }
  });
});

router.delete('/:id', 
function(request, response) {
  person.delete(request.params.id, function(err, count) {
    if (err) {
      response.json(err);
    } else {
      response.json(count);
    }
  });
});


router.put('/:id', 
function(request, response) {
  person.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      //  Lisätään virhetila jos KO tietuetta ei ole.
      console.log(dbResult);
      if(dbResult.affectedRows==1){
        //  tietokannan tietueen sijaan (dbResult) voidaan antaa myös tekstivastaus ("teksti").
        response.json("Person updated");
      }
      else{
        response.json("Does not exist!");
      }
      
    }
  });
});

module.exports = router;