# Prepravljač

**Prepravljač** je program koji služi za rešavanje markdown problema kod Olympicode tekstova zadataka.

Kako biste ga pokrenuli, samo ga pokrenite i nakon poziva upišite ime fajla koji želite prepraviti i output fajl, kao u primeru ispod.
```
python prepravljac.py 01_odbijanje.md 01_odbijanje_output.md
```
Izvorni fajl je, naravno, **01_odbijanje.md** a output programa je **01_odbijanje_output.md**.

Moguće je i da izvorni fajl i izlazni fajl budu isti, samo će izvorni fajl biti pregažen.

Drugi način korišćenja jeste da prebacite sve markdown fajlove u isti direktorijum kao i prepravljač i da onda pozovete
```
python prepravljac.py 1
```
što će sve Markdown fajlove u direktorijumu u kojem je prepravljač prepraviti.