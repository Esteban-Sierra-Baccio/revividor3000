const mysql = require('../database/db')

class MainController {

async logSegLinea(req , res){
    console.log(req.params.device_id)
    console.log(req.params.dato_linea)
    if(req.params.device_id != null && req.params.dato_linea != null) {
        let device_id = req.params.device_id
        let dato_linea = req.params.dato_linea;
        var sql1 = `insert into log_seg1 (log_date, device_id, dato_linea) values (now(), ${device_id}, ${dato_linea});`
        mysql.query(sql1, (error,data,fields) => {
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

async getLogsSeg(req,res){
    console.log("Get Logs")
    console.log(req.params.device_id)
    if(req.params.device_id!=null){
        let device_id = req.params.device_id;
        var sql = `SELECT * FROM log_seg1 where device_id='${device_id}'`
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

}

const segController = new MainController()
module.exports = segController;