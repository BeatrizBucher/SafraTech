const Models = require('../models/model');

const HistoricosController = {
    listaHitoricoCompleto: async (req, res) => {
        try {
            const histCompleto = await Models.HistoricosModel.listaHitoricoCompleto();

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

            const listaHistID = await Models.HistoricosModel.listaHitorico(id);

            if (!listaHistID) {
                return res.status(404).json({ mensagem: 'Histórico não encontrado' });
            }

            res.status(200).json(listaHistID);
        } catch (error) {
            console.log(error);
            res.status(500).json({ mensagem: error.message });
        }
    }
}

const EventosController = {
    cadastrarEventos: async (req, res) => {
        const { informacao, dispositivo_id } = req.body;

        try {
            if (!informacao || !dispositivo_id) {
                return res.status(400).json({ mensagem: "O campo da informação é obrigatório" });
            }

            const novoEvento = await Models.EventosModel.CadastrarEventos({
                informacao,
                dispositivo_id
            });

            console.log(novoEvento);

            if (novoEvento.affectedRows > 0) {
                return res.status(201).json({
                    success: true,
                    data: novoEvento
                });
            }
            else {
                res.status(401).json({ msg: "Falha ao cadastrar um novo evento" })
            }
        } catch (error) {
            console.log(error);
            return res.status(500).json({
                success: false,
                mensagem: error.message
            });
        }
    },
}

module.exports = {
    HistoricosController,
    EventosController
}