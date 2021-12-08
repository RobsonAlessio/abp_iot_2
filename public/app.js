

(function(){
    
  // Inicia o Firebase
  var config = {
    apiKey: "J8OtwuqbzP6yJzlaXwCxp2MFRNiSkulSFx59UhQn",
    authDomain: "abp-iot-2.com",
    databaseURL: "https://abp-iot-2-mauricio-robson-default-rtdb.firebaseio.com/",
    storageBucket: "sensoriamento-iot-bootcamp.appspot.com",
    messagingSenderId: "1055433905603"
  };
  
  firebase.initializeApp(config);

  var db = firebase.database();

  // Cria os listeners dos dados no firebase
  var distRob = db.ref('distanciaRob');
  var lumiRob = db.ref('luminosidadeRob');
  var distMauricio = db.ref('distanciaMauricio');
  var lumiMauricio = db.ref('luminosidadeMauricio');

  // Registra as funções que atualizam os gráficos e dados atuais da telemetria
  distRob.on('value',function (snapshot) {
    document.getElementById("distanciaRob").innerText = parseFloat(snapshot.val().toFixed(2)) + ' m';
  });
  lumiRob.on('value',function (snapshot) {
    document.getElementById("luminosidadeRob").innerText = snapshot.val();
  });
  distMauricio.on('value',function (snapshot) {
    document.getElementById("distanciaMauricio").innerText = parseFloat(snapshot.val().toFixed(2)) + ' m';
  });
  lumiMauricio.on('value',function (snapshot) {
    document.getElementById("luminosidadeMauricio").innerText = snapshot.val();
  });

})();