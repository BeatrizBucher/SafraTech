const express = require('express')
const controller = require('../controller/controller')
const router = express.Router()

router.get('listaHistoricoCompleto', controller.listaHitoricoCompleto)
router.get('listaHistorico/:id', controller.listaHitorico)

module.exports = router;