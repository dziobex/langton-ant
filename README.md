# langton-ant
Mrówka Langtona, automat komórkowy

## Czym jest?
<p align="justify">
Mrówka Langtona to jest automat komórkowy, oryginalnie opisany w 1986 r. przez Chrisa Langtona. 
Automat działa na dwuwymiarowej planszy z określonymi komórkami, w czym jedna jest Mrówką.
Komórka może być czarna lub biała. Jeśli mrówka znajdzie się na białej komórce, zamienia jej kolor, obraca się w prawo o 90° i idzie na kolejną komórkę.
Jeśli znajdzie się na czarnej komórce, zamienia ją na białą, obraca się w lewo o 90° i idzie na kolejną komórkę.
To repozytorium jest implementacją Mrówki Langtona w języku C.
</p>

## Kompilacja i wywołanie
Kod można skompilować używając komendy `make` w konsoli. Po kompilacji można go wywołać dzięki:
```
./symulacja [-m] [-n] [-i] [-d] [-s] [-o] [-p] 
-m -- Ilość rzędów na planszy. Liczba całkowita w przedziale <5;1000>.
-n -- Ilość kolumn na planszy. Liczba całkowita w przedziale <5;1000>.
-i -- Ilość iteracji. Liczba całkowita w przedziale <1;2000>.
-d -- Początkowy kierunek mrówki. Liczba całkowita w przedziale <0;3>, przy czym 0 = góra, 1 = prawo, 2 = dół, 3 = lewo.
-s -- Pierwszy człon nazwy plików, do których będą zapisywane poszczególne etapy iteracji.
-o -- Plik, z którego wczytany jest stan początkowy planszy i mrówki.
-p -- Procent planszy, który będzie losowo zapełniony czarnymi komórkami. Liczba całkowita w przedziale <0;100>.
```

### Przykładowe wywołania:
`./symulacja -m 40 -n 40 -i 100 -s out/out -p 10` - Plansza 40x40, 100 iteracji, 10% komórek czarne.<br>
Pliki od `out_1` do `out_150` zostaną zapisane w folderze out.<br>
`./symulacja -i 300 -s out/out -o in.txt` - Plansza wczytana z pliku in.txt, 300 iteracji.<br>
Pliki od `out_1` do `out_300` zostaną zapisane w folderze out.<br>

## Autorzy
Oliwia Pawelec <br />
Jakub Żebrowski