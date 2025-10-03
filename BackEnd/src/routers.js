const express = require('express')
const controller = require('../controller/controller')
const router = express.Router()

//Historicos
router.get('listaHistoricoCompleto', controller.HistoricosController.listaHitoricoCompleto);
router.get('listaHistorico/:id', controller.HistoricosController.listaHitorico);
//Eventos
router.post('cadastrarEventos', controller.EventosController.cadastrarEventos);

module.exports = router;