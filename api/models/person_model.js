const db = require('../database');

const person = {
  getById: function(id, callback) {
    return db.query('select * from person where id_person=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from person', callback);
  },
  add: function(person, callback) {
    return db.query(
      'insert into person (fname,lname,balance) values(?,?,?)',
      [person.fname, person.lname, person.balance],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from person where id_person=?', [id], callback);
  },
  update: function(id, person, callback) {
    return db.query(
      'update person set fname=?,lname=?, balance=? where id_person=?',
      [person.fname, person.lname, person.balance, id],
      callback
    );
  },
  moneyAction: function(procedureParams, callback) {
    return db.query(
      'call money_action (?,?)',
      [procedureParams.id, procedureParams.amount],
      callback
    );
  }
};
module.exports = person;