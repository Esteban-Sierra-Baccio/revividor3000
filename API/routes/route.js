const express = require('express');
const router = express.Router();

// Ruta 1: temperatura digital
const tempDigController = require('../controllers/tempDigController');

router.get('/api/getLogs/:deviceID', tempDigController.getLogs);
router.post('/api/logTemp/:deviceID/:temperature', tempDigController.logTemp);

// Ruta 2: Temperatura ambiental
const tempController = require('../controllers/tempController');
const humController = require('../controllers/humController');

router.get('/api/getLogs/:deviceID', tempController.getLogs);
router.post('/api/logTemp/:deviceID/:temperature', tempController.logTemp);
router.get('/api/getLogs/:deviceID', humController.getLogs);
router.post('/api/logHum/:deviceID/:humedad', humController.logHum);

// Ruta 3: seguidor 1
const segController = require('../controllers/segController');

router.get('/api/getLogsSeg/:device_id', segController.getLogsSeg);
router.post('/api/logSegLinea/:device_id/:dato_linea', segController.logSegLinea);

// Ruta 4: seguidor 2
const segController2 = require('../controllers/segController2');

router.get('/api/getLogsSeg2/:device_id', segController2.getLogsSeg2);
router.post('/api/logSegLinea2/:device_id/:dato_linea', segController2.logSegLinea2);

// Ruta 5: RFID
const rfidController = require('../controllers/rfidController')

router.get('/api/getLogs/:deviceID', rfidController.getLogs);
router.post('/api/logtag/:deviceID/:tag', rfidController.logtag);

// Ruta 6: color
// const colorController = require('../controllers/colorController')

// router.get('/api/getLogs/:deviceID', colorController.getLogs);
// router.post('/api/logTemp/:deviceID/:temperature', colorController.logTemp);

module.exports = router;
