const mysql = require('../database/db')

class MainController {

    async logtag(req , res){
        console.log(req.params.temperature)
        console.log(req.params.deviceID)

if(req.params.deviceID != null && req.params.temperature) {
    let tag = req.params.tag;
    var sql1 = `insert into log_tag (log_date, status, device_id,tag) values (now(), "aceptado", 5,${tag})`;
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
  console.log(req.params.deviceID)
  if(req.params.deviceID!=null){
      let deviceID = req.params.deviceID;
      var sql = 'SELECT * FROM log_temp where device_id=${2}';
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

const tempController = new MainController()
module.exports = tempController;