
(function(){
    
  // Inicia o firebase Firebase
  var config = {
    apiKey: "XmMpRoPvM0LHhQVEqx0DWGmneob13BuxeHiGOsrO",
    authDomain: "abp-iot-2.com",
    databaseURL: "https://abp-iot-2-default-rtdb.firebaseio.com",
    storageBucket: "sensoriamento-iot-bootcamp.appspot.com",
    messagingSenderId: "1055433905603"
  };
  firebase.initializeApp(config);

  var db = firebase.database();

  // Cria os listeners dos dados no firebase
  var tempRef = db.ref('temperature');
  var umidRef = db.ref('humidity');
  var presenceRef = db.ref('presence');



  // Registra as funções que atualizam os gráficos e dados atuais da telemetria
  tempRef.on('value',function (snapshot) {
    document.getElementById("currentTemp").innerText = snapshot.val() + 'm';
  });
  umidRef.on('value',function (snapshot) {
    document.getElementById("currentUmid").innerText = snapshot.val();
  });



  // Registrar função ao alterar valor de presença
  presenceRef.on('value', function(snapshot){
    var value = snapshot.val();
    var el = document.getElementById('currentPresence')
    if(value){
      el.classList.add('green-text');
    }else{
      el.classList.remove('green-text');
    }
  });

})();


// Retorna uma função que de acordo com as mudanças dos dados
// Atualiza o valor atual do elemento, com a metrica passada (currentValueEl e metric)
// e monta o gráfico com os dados e descrição do tipo de dados (chartEl, label)
function onNewData(currentValueEl, chartEl, label, metric){
  return function(snapshot){
    var readings = snapshot.val();
    if(readings){
        var currentValue;
        var data = [];
        for(var key in readings){
          currentValue = readings[key]
          data.push(currentValue);
        }
        document.getElementById(currentValueEl).innerText = currentValue + ' ' + metric;
        buildLineChart(chartEl, label, data);
    }
  }
}

// Constroi um gráfico de linha no elemento (el) com a descrição (label) e os
// dados passados (data)
function buildLineChart(el, label, data){
  var elNode = document.getElementById(el);
  new Chart(elNode, {
    type: 'line',
    data: {
        labels: new Array(data.length).fill(""),
        datasets: [{
            label: label,
            data: data,
            borderWidth: 1,
            fill: false,
            spanGaps: false,
            lineTension: 0.1,
            backgroundColor: "#F9A825",
            borderColor: "#F9A825"
        }]
    }
  });
}
