## Bump Memory Allocator 

**Tools** : CLion and C++ libraries

## RO

Acest cod este un prototip pentru un alocator de memorie. Este foarte simplu si este destul de bugguit. 

Principiul de functionare este unul simplu :

- Userul initializeaza buffer-ul cu dimensiunea maxima pe care acesta o doreste (nu este obligatoriu sa fie o dimensiune fixa)
  
- Alocatorul de memorie este alcatuit din
  1) **memory** -> pointer la buffer-ul mare din memorie 
  2) **size** -> dimensiunea totala pe care alocatorul o aloca  
  3) **offset** -> pozitia din buffer la care se afla pointerul
     
- functia allign8() are rolul de a rotunji la urmatorul multiplu de 8 dimensiunea trimisa
- avem functie de delete si de reset (important info: de preferat ar fi ca inainte sa fie dezalocat trebuie sa fie resetat bufferul la 0)

**Principiu de functionare** 

I) Bufferul initializat 

memory -> [................................................]
offset = 0

II) Luam exemplul din cod, int x = 10. Deci facem alocare cu sizeof(int), deci 8 bytes (deoarece facem aliniere la 8)

memory -> [XXXXXXXX........................................]
offset = 8

III) Apoi facem alocarea variabilei double. sizeof(double) este 8, deci se aduna cu 8. 

memory -> [XXXXXXXXXXXXXXXX...........................]
offset = 16


## EN 
