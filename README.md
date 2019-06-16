pid_kontroler
=============

Projekt realizowany na początku studiów na przedmiocie którego nazwy nie pamiętam :) Był to program (kontroler PID) do sterowania prędkością silnika elektrycznego podłączanego do płytki prototypowej STM32.

piny GPIO:
  PC0 (opcjonalnie) mozna podlaczyc wyjscie CS ze sterownika (powinna byc wart zasilania ale nie ma)
  
  PA2 PA3- wejscie z enkodera, na tej podstawie obliczana jest predkosc
  
  PC6 - wyjscie PWM do sterownika silnika
  
  PA8 PA9 - piny podpiete pod INa oraz INb sterownika, sluza do ustalenia kierunku obrotow lub hamowania
  


najlepiej podlaczyc pod STM Studio tam mozna zmieniac zadana predkosc i wspolczynniki PID oraz obserwowac wykresy
