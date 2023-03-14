# C_memory_management

 In main:
	- se initializeaza datele;
	- se citeste fiecare linie primita de la tastatura intr-un while;
	- pentru fiecare linie se aloca memorie si se retin datele in structura care va fi introdusa in vector conform cerintei;
	- se apeleaza functia aferente fiacarei linii;

 Functiile folosite sunt:
 
1) Functie pentru adaugarea unui element la finalul vectorului in care:
- daca vectorul arr e null:
	- se aloca memorie pentru noul element;
	- se adauga in vector cu ajutorul functiei memmove;
	- se creste lungimea in octeti vectorului de octeti;
- daca vectorul nu e null:
	- se realoca memorie pentru noul element;
	- se adauga in vector cu ajutorul functiei memmove;
	- se creste lungimea in octeti vectorului de octeti;

2) Functie pentru adaugarea unui element la un anumit index din vector in care:
- daca indexul e mai mic decat zero se returneaza eroarea -1;
- se calculeaza nr de elemente ale vectorului;
- daca indexul e mai mare decat nr de elemente se apeleaza functia add_last;
- se calculeaza lungimea in octeti a vectorului pana la index;
- se realoca memorie pentru noul element;
- se adauga in vector cu ajutorul functiei memmove;
- se creste lungimea in octeti vectorului de octeti;

3) Functie pentru gasirea si afisarea unui element din vector in care:
- daca vectorul de octeti e gol se termina functia;
- daca indexul e mai mic decat zero se termina functia;
- se calculeaza lungimea in octeti a vectorului pana la index;
- daca indexul e mai mare decat nr de elemente se termina functia;
- se parcurge vectorul de octeti pana la index si se retine header-ul in joey si data in valerie;
- se face afisarea pentru fiecare tip;

4) Functie pentru stergerea unui element din vector de la un index dat in care:
- daca lungimea vectorului e 0 se intoarce eroarea -1;
- se calculeaza lungimea in octeti a vectorului pana la index;
- se retine head-ul fiecarui element;
- se sterge elementul de la indexul dat cu ajutorul functiei memmove;

5) Functie pentru printarea vectorului in care:
- daca vectorul de octeti e gol se termina functia;
- se parcurge vectorul de octeti din element in element si se afiseaza pentru fiecare in functie de tip si de tipul datelor;

TASKS: https://ocw.cs.pub.ro/courses/iocla/teme/tema-1
