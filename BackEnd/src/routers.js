const express = require('express')
const controller = require('../controller/controller')
const router = express.Router()

//Historicos
router.get('/listaHistoricoCompleto', controller.HistoricosController.listaHitoricoCompleto);
router.get('/listaHistorico/:id', controller.HistoricosController.listaHitorico);
//Eventos
router.post('/cadastrarEventos', controller.EventosController.cadastrarEventos);

//Info Meteorologicas
router.post('/cadastrarInfoMeteorologicas', controller.InfoMeteorologicasController.cadastrarInfoMeteorologicas);
router.get('/listarInfoMeteorologicasCompleta', controller.InfoMeteorologicasController.listarInformacoesMeteorologicas);
module.exports = router;