const HistoricosModel = require('../models/model');

const HistoricosController = {
     listaHitoricoCompleto: async (req, res) =>{
        try {
            const histCompleto = await HistoricosModel.listaHitoricoCompleto();

            console.log(histCompleto);

            return res.status(200).json(histCompleto);

        }
        catch (error) {
            res.status(500).json({ mensagem: error.message });
        }
    },

    listaHitorico: async (req, res) => {
        try {
                const { id } = req.params;
                if (!id) {
                    return res.status(400).json({ mensagem: 'ID inválido' });
                }
    
                const listaHistID = await HistoricosModel.listaHitorico(id);
    
                if (!listaHistID) {
                    return res.status(404).json({ mensagem: 'Histórico não encontrado'});  
                }
    
                res.status(200).json(listaHistID);
            } catch (error) {
                console.log(error);
                res.status(500).json({ mensagem: error.message });
            }
    }
}

module.exports = HistoricosController