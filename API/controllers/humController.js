const mysql = require('../database/db')

class MainController {
async logHum(req , res){
    console.log(req.params.humedad)
    console.log(req.params.deviceID)

if(req.params.deviceID != null && req.params.humedad != null) {
let deviceID = req.params.deviceID;
let humedad = req.params.humedad;
var sql2 = `insert into log_hum (log_date, device_id, hum) values (now(), 2, ${humedad})`;
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
  console.log(req.params.deviceID)
  if(req.params.deviceID!=null){
      let deviceID = req.params.deviceID;
      var sql = 'SELECT * FROM log_hum where device_id=${2}';
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

const humedadController = new MainController()
module.exports = humedadController;