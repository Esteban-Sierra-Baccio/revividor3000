const mysql = require('../database/db')

class MainController {
async logButton(req , res){
    console.log(req.params.status)

if(req.params.status != null) {
let status = req.params.status;
var sql2 = `insert into log_button (log_date, device_id, status) values (now(), 7, ${status})`;
mysql.query(sql2,(error,data,fields) => {
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

    var sql = 'SELECT * FROM log_button where device_id=${7}';
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

const buttonController = new MainController()
module.exports = buttonController;