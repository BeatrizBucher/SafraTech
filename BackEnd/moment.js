const moment = require('moment')

function verificarData(data){

    const dataUSA = (data, 'YYYY-MM-DD', true)
    if(dataBR.isValid()){
        return dataBR.format('DD-MM-YYYY')
    }

    return null
}