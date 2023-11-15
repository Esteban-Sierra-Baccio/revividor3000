const mysql = require('../database/db')

class MainController {

async logSegLinea2(req , res){
    console.log(req.params.dato_linea)
    if(req.params.dato_linea != null) {
        let dato_linea = req.params.dato_linea;
        var sql2 = `insert into log_seg2 (log_date, device_id, dato_linea) values (now(), 4, ${dato_linea});`
        mysql.query(sql2, (error,data,fields) => {
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

async getLogsSeg2(req,res){
    console.log("Get Logs")
    console.log(req.params.device_id)

    let device_id = req.params.device_id;
    var sql = `SELECT * FROM log_seg2 where device_id='${device_id}'`
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

const segController2 = new MainController()
module.exports = segController2;