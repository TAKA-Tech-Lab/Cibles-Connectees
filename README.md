# Cibles-Connectees

## 🤖 À propos de ce projet
**Organisation :** Taka Tech Lab
**Catégorie :** Internet of Things (IoT), Tir Sportif, Maker
**Description :** Ce dépôt contient le code source pour la création d'un nœud de détection d'impact pour cibles sportives. Ce module (Node) capte les chocs balistiques et transmet l'information au boîtier central. Ce projet a été spécifiquement codé et optimisé pour des microcontrôleurs ESP8266 en raison de leur grande disponibilité matérielle. 

## 🛠️ Matériel Requis (Hardware)
*   1x Microcontrôleur : NodeMCU ESP8266
*   1x Capteur de choc / vibration (ex: module piezoélectrique KY-031)
*   Fils Dupont (Rouge, Noir, Jaune)
*   Alimentation (Batterie Lipo ou Powerbank)

## 🔌 Schéma de Câblage (Pinout & Fritzing)
Pour assurer une lecture correcte et instantanée des impacts, le câblage du capteur vers la carte doit suivre ce schéma précis :

*   **VCC (Capteur)** ➔ Broche **3V3** de l'ESP8266 *(Fil rouge)*
*   **GND (Capteur)** ➔ Broche **GND** de l'ESP8266 *(Fil noir)*
*   **DO (Digital Out Capteur)** ➔ Broche **D5** de l'ESP8266 *(Fil jaune)*

## 💻 Installation (Arduino IDE)
1. Ouvrir le fichier `target_node_esp8266.ino` avec l'IDE Arduino.
2. S'assurer que le type de carte sélectionné est bien un "Generic ESP8266 Module".
3. Installer les bibliothèques requises pour le protocole réseau.
4. Flasher le code.

## 🔗 Écosystème du Projet
*   **Boîtier Central (Master) :** [Ajouter le lien vers le dépôt du récepteur quand il sera créé]
*   **Boîtiers 3D :** Les fichiers STL pour imprimer les coques de protection des composants électroniques sont disponibles sur [Lien vers Printables/Thingiverse].

## 🎥 Démonstration et Tutoriel
Retrouvez les explications de montage, l'analyse du code et les tests de tir en conditions réelles sur notre chaîne YouTube **Taka Tech Lab** : https://youtu.be/XkP-xxUsRR8?si=pvr8lxtIPj27w1AY

---
*Maintenu par [Taka Tech Lab]
