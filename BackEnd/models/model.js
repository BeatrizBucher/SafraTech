const executeQuery = require('../database/query')

const HistoricosModel = {
    listaHitoricoCompleto: async () => {
        const result = await executeQuery('SELECT eventos.informacao, eventos.horario, dispositivos.nome, dispositivos.tipo FROM eventos INNER JOIN dispositivos ON eventos.dispositivo_id = dispositivos.id')
            .catch(erro => { throw erro })
    },
    listaHitorico: async (id) => {
        const result = await executeQuery('SELECT eventos.informacao, eventos.horario, dispositivos.nome, dispositivos.tipo FROM eventos INNER JOIN dispositivos ON eventos.dispositivo_id = dispositivos.id INNER JOIN AREAS ON dispositivos.area_id = areas.id WHERE areas.id = ?',[id])
            .catch(erro => { throw erro })
    }
}

module.exports = HistoricosModel