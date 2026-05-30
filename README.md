# Cibles-Connectees

## 🤖 À propos de ce projet
**Organisation :** Taka Tech Lab
**Catégorie :** Internet of Things (IoT), Tir Sportif, Maker
**Description :** Ce dépôt contient le code source pour la création d'un nœud de détection d'impact pour cibles sportives. Ce module (Node) capte les chocs balistiques et transmet l'information au boîtier central. Ce projet a été spécifiquement codé et optimisé pour des microcontrôleurs ESP8266 / NodeMCU 1.0 en raison de leur grande disponibilité matérielle. 

## 🛠️ Matériel Requis (Hardware)
*   1x Microcontrôleur : NodeMCU ESP8266 / NodeMCU 1.0 
*   1x Capteur de choc / vibration (ex: module piezoélectrique type KY-031)
*   Fils Dupont (Rouge, Noir, Jaune)
*   Alimentation (Batterie Lipo ou Powerbank)

## 🔌 Schéma de Câblage (Pinout & Fritzing)
Pour assurer une lecture correcte et instantanée des impacts, le câblage du capteur vers la carte doit suivre ce schéma précis :

*   **VCC (Capteur)** ➔ Broche **3V3** de l'ESP8266 *(Fil rouge)*
*   **GND (Capteur)** ➔ Broche **GND** de l'ESP8266 *(Fil noir)*
*   **DO (Digital Out Capteur)** ➔ Broche **D5** de l'ESP8266 *(Fil jaune)*

## 💻 Architecture du Code (ESP-NOW)
Ce projet fonctionne sur un modèle Master/Slave via le protocole sans fil **ESP-NOW**. Le code est divisé en deux parties distinctes :
* **[Code de la Cible (Node)](./target_node/target_node.ino) :** Installé sur chaque cible (Alpha, Bravo, Charlie). Il lit les vibrations du capteur piézoélectrique sur la broche `D5` et envoie un signal flash via ESP-NOW lors d'un impact.
* **[Code du Serveur (Master)](./master_server/master_server.ino) :** Installé sur le boîtier central. Il reçoit les signaux des cibles, incrémente les scores et génère un point d'accès WiFi (`Master_Cibles`) hébergeant une interface web de scoring en temps réel (accessible sur `192.168.4.1`).

## 🔗 Écosystème du Projet
*   **Boîtier Central (Master) :** [Ajouter le lien vers le dépôt du récepteur quand il sera créé]
*   **Boîtiers 3D :** Les fichiers STL pour imprimer les coques de protection des composants électroniques sont disponibles sur [Lien vers Printables/Thingiverse].

## 🎥 Démonstration et Tutoriel
Retrouvez les explications de montage, l'analyse du code et les tests de tir en conditions réelles sur notre chaîne YouTube **Taka Tech Lab** : https://youtu.be/XkP-xxUsRR8 

---
*Maintenu par [Taka Tech Lab]
