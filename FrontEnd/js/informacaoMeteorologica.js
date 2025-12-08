const ApiKeyOpen = '811ea33449c14eff99871cd400ffc6f1';
const ApiKeyWeathe = '0eae4cec843c9af36a7c58ab3417009c';

async function buscarClima() {
    let municipio = document.getElementById('cidade');
    let lat = document.getElementById('latitude');
    let long = document.getElementById('longitude');
    let cidade = "";
    let estado = "";
    let longitude = "";
    let latitude = "";

    try {
        const cep = '17402026';
        const viaCep = await fetch(`https://viaCep.com.br/ws/${cep}/json/`);
        const dadosCep = await viaCep.json();
        cidade = dadosCep.localidade;
        estado = dadosCep.uf;
        municipio.innerText = `${cidade}/${estado}`;
        console.log(dadosCep);
    }
    catch (error) {
        console.log(`Erro em buscar o cep: ${error}`);
        return;
    }
    try {
        const dadosGeoLocalizacao = await fetch(`https://api.opencagedata.com/geocode/v1/json?q=${cidade},${estado}&key=811ea33449c14eff99871cd400ffc6f1`);
        const dadosGeo = await dadosGeoLocalizacao.json();
        latitude = dadosGeo.results[0].geometry.lat;
        longitude = dadosGeo.results[0].geometry.lng;
        lat.innerText = `Latitude: ${latitude}`;
        long.innerText = `Longitude: ${longitude}`;
        console.log(`Latitude: ${latitude} longitude: ${longitude}`)
    }
    catch (error) {
        console.log(`Erro em buscar o cep: ${error}`);
        return;

    }
    try {
        const key = 'b83855c9726230c218dc60e5e7fc4c3c';
        const dadosClimatologia = await fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${latitude}&lon=${longitude}&units=metric&lang=pt_br&appid=${key}`);
        const dadosClima = await dadosClimatologia.json();
        temperatura = dadosClima.main.temp;
        umidade = dadosClima.main.humidity;
        condicao = dadosClima.weather[0].description;
        cond.innerText = `Condição: ${condicao}`;
        temp.innerText = `Temperatura: ${temperatura}°`;
        umid.innerText = `Umidade: ${umidade}%`;
        localStorage.setItem("temperaturaAgora", temperatura);
        localStorage.setItem("umidadeAgora", umidade);
        localStorage.setItem("condicaoAgora", condicao);

        console.log(`temperatura: ${temperatura} condicao: ${condicao} umidade: ${umidade}`);
    }
    catch (error) {
        console.log(`Erro ao buscar: ${error}`);
        return;

    }
}
buscarClima()