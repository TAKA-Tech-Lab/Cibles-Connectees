/*
 * Taka Tech Lab - Système de Ciblerie Connectée (Nœud Émetteur)
 * Description : Détection d'impact balistique et transmission ESP-NOW.
 * Licence : MIT (Copyright 2026 Taka Tech Lab)
 * Vidéo de présentation : https://youtu.be/XkP-xxUsRR8
 */

#include <ESP8266WiFi.h>
#include <espnow.h>

#define SHOCK_PIN D5
#define BOARD_ID 1  // 1 pour Alpha, 2 pour Bravo, 3 pour Charlie, ...

// Structure pour envoyer les données
typedef struct struct_message {
    int id;
    bool shock;
} struct_message;

struct_message myData;
unsigned long lastShockTime = 0;
bool shockActive = false;

void setup() {
    Serial.begin(115200);
    pinMode(SHOCK_PIN, INPUT_PULLUP);

    WiFi.mode(WIFI_STA); // Obligatoire pour ESP-NOW
    if (esp_now_init() != 0) return;

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    
    // Adresse MAC de broadcast (envoie à tout le monde autour)
    uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
    int val = digitalRead(SHOCK_PIN);

    if (val == LOW && !shockActive) {
        shockActive = true;
        lastShockTime = millis();
        
        myData.id = BOARD_ID;
        myData.shock = true;
        
        uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
        Serial.println("Choc envoyé !");
    }

    if (shockActive && (millis() - lastShockTime > 1000)) {
        shockActive = false;
        myData.id = BOARD_ID;
        myData.shock = false;
        uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    }
}
