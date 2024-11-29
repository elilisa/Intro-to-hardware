# Projet de Contrôle d'Accès avec Circuit Électronique et Raspberry Pi

Ce projet consiste à créer un système de contrôle d'accès électronique capable de :
- Lire un badge RFID.
- Vérifier les permissions via une base de données sécurisée sur un Raspberry Pi.
- Signifier l'état de l'accès (accordé ou refusé) à l'utilisateur via des LED.

## **Fonctionnalités**
1. **Lecture de badge** : Utilisation d'un module RFID pour lire les identifiants des badges.
2. **Vérification d'accès** : Communication avec une API hébergée sur un Raspberry Pi pour vérifier les autorisations.
3. **Indicateur visuel** : LED bleue pour un accès accordé, LED rouge pour un accès refusé.
4. **Connectivité WiFi** : Le circuit se connecte au réseau WiFi pour interagir avec le Raspberry Pi.

---

## **Architecture du Système**
1. **Composants Matériels** :
   - Microcontrôleur (ESP32/Arduino avec connectivité WiFi).
   - Module RFID (ex. : MFRC522).
   - Raspberry Pi (hébergeant la base de données et l'API).
   - LED (bleue et rouge) pour signalisation.

2. **Communication** :
   - Le circuit communique avec le Raspberry Pi via des requêtes HTTP.
   - Une réponse JSON est utilisée pour déterminer si l'accès est accordé ou refusé.

---

## **Configuration**
### **1. Code Principal**
Le fichier principal du projet (`main_code.ino`) :
- Configure les connexions au WiFi.
- Lit les badges via le module RFID.
- Effectue des requêtes HTTP pour vérifier l'accès.
- Contrôle les LED en fonction de la réponse.

### **2. Code de Test : Ping**
Un fichier de test (`ping_rasp.ino`) permet de vérifier si le Raspberry Pi est joignable via le réseau.

---

## **Installation**
1. **Pré-requis** :
   - Installez les bibliothèques nécessaires :
     ```arduino
     ArduinoJson
     MFRC522 : pour interagir avec le module RFID MFRC522, facilitant la lecture et l'écriture de cartes RFID avec des microcontrôleurs tels qu'Arduino
     WiFi : permet d'utiliser les fonctionnalités WiFi de l'ESP32
     HTTPClient
     SPI :  permet de gérer les échanges d'informations entre la carte Arduino et les circuits SPI connectés
     WiFiClientSecure : établir des connexions securisées en ssl/tls en assurant le chiffrement des données
     ```
   - Configurez le Raspberry Pi pour qu'il héberge une API REST exposant les données des badges.

2. **Connexion WiFi** :
   - Modifiez les variables `ssid` et `password` dans le code pour correspondre à votre réseau.

3. **Configuration de l'API** :
   - Déployez l'API sur le Raspberry Pi.
   - Exemple d'URL de l'API : `http://192.168.192.179/api/badges/{id_badge}`.

---

## **Utilisation**
1. **Lancer le Système** :
   - Chargez le code principal dans le microcontrôleur.
   - Allumez le Raspberry Pi et assurez-vous que l'API est opérationnelle.

2. **Lecture de Badge** :
   - Approchez un badge RFID du lecteur.
   - Observez les LED :
     - **Bleue** : Accès accordé.
     - **Rouge** : Accès refusé.

3. **Test de Connectivité** :
   - Utilisez le fichier `ping_raspberry.ino` pour vérifier si le Raspberry Pi est accessible via le réseau.

---

## **Code**
### **1. Code Principal**
Le fichier principal est disponible dans `main_code.ino`.

### **2. Code de Test**
Le fichier de ping est disponible dans `ping_raspberry.ino`.

---

## **Améliorations Futures**
- Ajout d'une interface utilisateur pour configurer le réseau WiFi sans reprogrammer le microcontrôleur.
- Sécurisation accrue des communications entre le microcontrôleur et le Raspberry Pi (HTTPS).
- Intégration avec d'autres systèmes (domotique, alarmes).

---

## **Contributeurs**
- Auteurs principaux : @elzie et @GlenChaigneau
- Contributions bienvenues via des pull requests.

---

## **Licence**
Ce projet est sous licence MIT. Consultez le fichier `LICENSE` pour plus d'informations.
