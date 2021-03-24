const database=require('../database');

const example_sql={

    getAllPersons: function(callback){
        return database.query('select * from person', callback);
    }
}

module.exports = example_sql;