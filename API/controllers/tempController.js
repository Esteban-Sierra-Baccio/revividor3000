const mysql = require('../database/db')

class MainController {

    async logTemp(req , res){
        console.log(req.params.temperature)

if(req.params.temperature) {
    let temperature = req.params.temperature;
    var sql1 = `insert into log_temp (log_date, device_id, temp) values (now(), 2, ${temperature})`;
    mysql.query(sql1,(error,data,fields) => {
        if(error) {
            res.status(500)
            res.send(error.message)
            return;
        } else {
            console.log(data)
            res.json({
                status: 200,
                message: "Log uploaded successfully",
                affectedRows: data.affectedRows
            }) 
        } 
    });

    } else {
    res.send('Por favor llena todos los datos!')
  }
}

async getLogs(req,res){
  console.log("Get Logs")
    let deviceID = req.params.deviceID;
    var sql = 'SELECT * FROM log_temp where device_id=2';
    mysql.query(sql, (error, data, fields) => {
        if(error) {
            res.status(500)
            res.send(error.message)
        } else {
            console.log(data)
            res.json({
                data
            })
        }
    })

}
}

const tempController = new MainController()
module.exports = tempController;