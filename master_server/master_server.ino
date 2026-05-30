/*
 * Taka Tech Lab - Système de Ciblerie Connectée (Serveur Central Master)
 * Description : Réception ESP-NOW, gestion des scores et serveur Web de scoring.
 * Licence : MIT (Copyright 2026 Taka Tech Lab)
 * Vidéo de présentation : https://youtu.be/XkP-xxUsRR8
 */

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Structure pour stocker l'état des 3 cibles
struct Target {
  int count;
  bool active;
};
Target targets[4] = {{0, false}, {0, false}, {0, false}, {0, false}}; // Index 1 à 3

// Structure de réception (doit être identique à l'émetteur)
typedef struct struct_message {
  int id;
  bool shock;
} struct_message;

// Fonction de rappel (Callback) quand une donnée arrive
void onDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  struct_message myData;
  memcpy(&myData, incomingData, sizeof(myData));

  if (myData.id >= 1 && myData.id <= 3) {
    // Si c'est un nouveau choc (passage de false à true)
    if (myData.shock && !targets[myData.id].active) {
      targets[myData.id].count++;
    }
    targets[myData.id].active = myData.shock;
  }
}

// Page Web unique
const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<style>
  body { font-family: sans-serif; background: #2c3e50; color: white; text-align: center; margin:0; }
  .container { display: flex; flex-direction: column; height: 100vh; }
  .target { flex: 1; margin: 5px; border-radius: 10px; display: flex; flex-direction: column; justify-content: center; transition: 0.1s; border: 3px solid rgba(255,255,255,0.1); }
  .green { background: #2ecc71; }
  .red { background: #e74c3c; }
  .name { font-size: 8vw; font-weight: bold; }
  .count { font-size: 15vw; font-weight: bold; }
  #btn-reset { padding: 20px; font-size: 6vw; background: #34495e; color: white; border: 2px solid white; border-radius: 10px; margin: 10px; cursor: pointer; }
  #btn-reset:active { background: #e74c3c; }
</style></head>
<body>
  <div class="container">
    <div id="t1" class="target green"><div class="name">ALPHA</div><div id="c1" class="count">0</div></div>
    <div id="t2" class="target green"><div class="name">BRAVO</div><div id="c2" class="count">0</div></div>
    <div id="t3" class="target green"><div class="name">CHARLIE</div><div id="c3" class="count">0</div></div>
    <button id="btn-reset" onclick="reset()">REMETTRE À ZÉRO</button>
  </div>
<script>
  function reset() {
    fetch('/reset');
  }
  function update() {
    fetch('/data').then(r => r.json()).then(data => {
      for(let i=1; i<=3; i++) {
        document.getElementById('c'+i).innerText = data[i].c;
        document.getElementById('t'+i).className = data[i].s ? "target red" : "target green";
      }
      setTimeout(update, 150);
    }).catch(e => setTimeout(update, 500));
  }
  update();
</script></body></html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  // Configuration WiFi : Point d'Accès + Station (nécessaire pour ESP-NOW)
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Master_Cibles", "12345678");

  // Initialisation ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erreur ESP-NOW");
    return;
  }

  // Rôle esclave (reçoit les données)
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataRecv);

  // Routes Serveur Web
  server.on("/", []() { server.send_P(200, "text/html", PAGE); });
  
  server.on("/data", []() {
    String json = "{";
    for(int i=1; i<=3; i++) {
      json += "\"" + String(i) + "\":{\"s\":" + String(targets[i].active) + ",\"c\":" + String(targets[i].count) + "}";
      if(i<3) json += ",";
    }
    json += "}";
    server.send(200, "application/json", json);
  });

server.on("/reset", []() {
    for(int i=1; i<=3; i++) {
        targets[i].count = 0;
    }
    server.send(200, "text/plain", "OK");
});

  server.begin();
  Serial.println("Master prêt sur 192.168.4.1");
}

void loop() {
  server.handleClient();
}
