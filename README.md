# IPV4Evasion

encode.cpp :

Programme en C++ qui lit une séquence d'octets (shellcode généré par msfvenom) et la convertit en une liste d'adresses IP. Il utilise la fonction bytesToIPAddresses pour prendre des groupes de 4 octets à partir du shellcode et les formater sous la forme d'adresses IP.

  Détails :
    - Le programme commence par définir une fonction bytesToIPAddresses qui divise un tableau d'octets en groupes de 4 et les convertit en chaînes de caractères représentant des        adresses IP.
    - Le shellcode est généré par la commande msfvenom avec la charge utile windows/x64/exec qui exécute "calc.exe".
    - Les adresses IP générées sont affichées sous la forme d'un vecteur de chaînes de caractères (std::vectorstd::string).

  Les adresses IP générées seront à entrer dans le programme "inject.cpp" : 
  ![image](https://github.com/user-attachments/assets/9178ad6f-427e-4863-ab0c-b61fbc66961d)


inject.cpp :

