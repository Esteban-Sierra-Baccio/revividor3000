const mysql = require('../database/db')

class MainController {

    async logColor(req , res){
        console.log(req.params.color)
        if(req.params.color != null) {
            let color = req.params.color;
            var sql = `insert into log_color (log_date, device_id, color) values (now(), 6, ${color});`
            mysql.query(sql, (error,data,fields) => {
                if(error) {
                    res.status(500)
                    res.send(error.message)
                } else {
                    console.log(data)
                    res.json({
                        status: 200,
                        message: "Log uploaded successfully",
                        affectedRows: data.affectedRows
                    })
                }
            })
        } else {
          res.send('Por favor llena todos los datos!')
        }
    }
    
    async getLogs(req,res){
        console.log("Get Logs")
        var sql = `SELECT * FROM log_color where device_id=6`
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

const colorController = new MainController()
module.exports = colorController;