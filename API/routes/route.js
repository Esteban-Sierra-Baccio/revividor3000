const express = require('express');
const tempController = require('../controllers/tempController');
const humController = require('../controllers/humController');
const segController = require('../controllers/segController');
const segController2 = require('../controllers/segController2')
const router = express.Router();

// Ruta 1: temperatura digital
// Ruta 2: Temperatura ambiental
router.get('/api/getLogs/:deviceID', tempController.getLogs);
router.post('/api/logTemp/:deviceID/:temperature', tempController.logTemp);
router.get('/api/getLogs/:deviceID', humController.getLogs);
router.post('/api/logHum/:deviceID/:humedad', humController.logHum);
// Ruta 3: seguidor 1
router.get('/api/getLogsSeg/:device_id', segController.getLogsSeg);
router.post('/api/logSegLinea/:device_id/:dato_linea', segController.logSegLinea);
// Ruta 4: seguidor 2
router.get('/api/getLogsSeg2/:device_id', segController2.getLogsSeg2);
router.post('/api/logSegLinea2/:device_id/:dato_linea', segController2.logSegLinea2);
// Ruta 5: RFID
router.get('/api/getLogs/:device_id', rfidController.getLogs);
router.post('/api/logtag/:device_id/:dato_linea', rfidController.logtag);
// Ruta 6: color


module.exports = router;