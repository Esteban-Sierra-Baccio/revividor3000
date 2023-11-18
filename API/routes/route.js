const express = require('express');
const router = express.Router();

// Todas las rutas se basarán en la siguiente:
// http://x.x.x.x:x/api/getLogs/x
// http://x.x.x.x:x/api/log/x/y

// Ruta 1: temperatura digital
const tempDigController = require('../controllers/tempDigController');

router.get('/api/getLogs/1', tempDigController.getLogs);
router.post('/api/logTemp/1/:temperature', tempDigController.logTemp);

// Ruta 2: Temperatura ambiental
const tempController = require('../controllers/tempController');
const humController = require('../controllers/humController');

router.get('/api/getLogs/2', tempController.getLogs);
router.post('/api/logTemp/2/:temperature', tempController.logTemp);
router.get('/api/getLogs/2', humController.getLogs);
router.post('/api/logHum/2/:humedad', humController.logHum);

// Ruta 5: RFID
const rfidController = require('../controllers/rfidController')

router.get('/api/getLogs/5', rfidController.getLogs);
router.post('/api/logtag/5/:tag', rfidController.logtag);

// Ruta 6: color
const colorController = require('../controllers/colorController');

router.get('/api/getLogs/6', colorController.getLogs);
router.post('/api/logColor/6/:color', colorController.logColor);

module.exports = router;