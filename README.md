# 🛡️ IPV4Evasion

## **encode.cpp**

Ce programme en C++ lit une séquence d'octets (shellcode généré par **msfvenom**) et la convertit en une liste d'adresses IP. Il utilise la fonction `bytesToIPAddresses` pour regrouper des groupes de 4 octets à partir du shellcode et les formater sous forme d'adresses IP.

### 🔍 **Détails :**
- Le programme commence par définir une fonction `bytesToIPAddresses` qui divise un tableau d'octets en groupes de 4 et les convertit en chaînes de caractères représentant des adresses IP.
- Le shellcode est généré par la commande **msfvenom** avec la charge utile `windows/x64/exec` qui exécute "calc.exe".
- Les adresses IP générées sont affichées sous la forme d'un vecteur de chaînes de caractères (`std::vector<std::string>`).

➡️ **Les adresses IP générées seront utilisées dans le programme "inject.cpp".**

<br>

![encode example](https://github.com/user-attachments/assets/9178ad6f-427e-4863-ab0c-b61fbc66961d)

---

## **inject.cpp**

Ce programme en C++ convertit la liste d'adresses IP en un tableau d'octets, puis injecte ce tableau dans une région de mémoire allouée et exécute le shellcode.

### 🔍 **Détails :**
- Le programme commence par la fonction `ipAddressesToBytes`, qui prend une liste d'adresses IP sous forme de chaînes de caractères et les convertit en octets.
- Une liste d'adresses IP est utilisée pour générer un tableau d'octets, qui est ensuite copié dans une région de mémoire nouvellement allouée à l'aide de la fonction **VirtualAlloc**.
- La fonction **memcpy** est utilisée pour déplacer le contenu de ce tableau d'octets (shellcode) dans la mémoire allouée.
- Le programme exécute ensuite le shellcode en appelant cette mémoire allouée comme une fonction.

💻 **Exemple de test :** Le test ici consiste à ouvrir "calc.exe" via un payload généré par **msfvenom**. (On peut imaginer remplacer ceci par un reverse shell.)

<br>

![inject example](https://github.com/user-attachments/assets/a48505f9-23a8-485f-bbf8-035a6f27a56a)

---
