const executeQuery = require('../database/query')

const HistoricosModel = {
    listaHitoricoCompleto: async () => {
        return await executeQuery('SELECT eventos.informacao, eventos.horario, dispositivos.nome, dispositivos.tipo FROM eventos INNER JOIN dispositivos ON eventos.dispositivo_id = dispositivos.id')
            .catch(erro => { throw erro })
    },
    listaHitorico: async (id) => {
        return await executeQuery('SELECT eventos.informacao, eventos.horario, dispositivos.nome, dispositivos.tipo FROM eventos INNER JOIN dispositivos ON eventos.dispositivo_id = dispositivos.id INNER JOIN AREAS ON dispositivos.area_id = areas.id WHERE areas.id = ?', [id])
            .catch(erro => { throw erro })
    }
}
// const AreasModel = {
//     CadastrarAreas: async (areas) => {
//         const { nome, latitude, longitude } = areas;
//         return await executeQuery('INSERT INTO areas (nome, latitude, longitude) VALUES (?,?,?)', [nome, latitude, longitude])
//             .catch(erro => { throw erro })
//     }
// }
// const DispositivosModel = {
//     CadastrarDispositivos: async (dispositivos) => {
//         const { nome, tipo, area_id } = dispositivos;
//         return await executeQuery('INSERT INTO dispositivos (nome, tipo, area_id) VALUES (?,?,?)', [nome, tipo, area_id])
//             .catch(erro => { throw erro })
//     }
// }
//O dispositivo id provavelmente vira do dispositivo em si
const EventosModel = {
    CadastrarEventos: async (eventos) => {
        const { informacao, horario, dispositivo_id } = eventos;
        return await executeQuery('INSERT INTO eventos (informacao, horario, dispositivo_id) VALUES (?,?,?)', [informacao, horario, dispositivo_id])
            .catch(erro => { throw erro })
    }
}
const InfoMeteorologicasModel = {
    CadastrarInfoMetereologicas: async (infoMeteorologica) => {
        const { temperatura, umidade, condicao, velocidade_vento, sensacao, maxima, minima, indice_uv, horario, precipitacao } = infoMeteorologica;
        return await executeQuery('INSERT INTO informacoes_meteorologicas (	temperatura,umidade,condicao,velocidade_vento,sensacao,maxima,minima,indice_uv,horario,precipitacao ) VALUES (?,?,?,?,?,?,?,?,?,?)', [temperatura, umidade, condicao, velocidade_vento, sensacao, maxima, minima, indice_uv, horario || new Date(), precipitacao])
            .catch(erro => { throw erro })
    },
    ListarInfoMetereologicasCompleta: async () => {
        return await executeQuery('SELECT * FROM informacoes_meteorologicas')
            .catch(erro => { throw erro })
    }
}

module.exports = { HistoricosModel, /*AreasModel, DispositivosModel*/ EventosModel, InfoMeteorologicasModel }