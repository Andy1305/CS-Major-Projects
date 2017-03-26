1. Clasa Tema_2 contine doar functia main, in care se citeste din fisier linie cu linie, pana la sfarsitul
   acestuia si se apeleaza functiile corespunzatoare fiecarei operatii.

2. Interfata GraphInterface contine operatiile (metodele) ce trebuie implementate.

3. Clasa Graph contine un ArrayList cu noduri si implementeaza metodele: - Insert, ce introduce un nod in graf, daca acesta nu exista.
				       					 - Delete, ce sterge un nod din graf.
				       					 - InsertM, ce introduce o muchie.
				       					 - DeleteM, ce sterge o muchie.
				       					 - findInfo, ce returneaza nodul cu informatia cautata.
				       					 - Serialize, ce serializeaza un nod, conform enuntului. Returneaza un string ce va fi scris in fisier.
									 - Deserialize, ce reface graful, conform noilor setari si face operatiile de cast.
									 - Display, ce afiseaza informatiile din graf.

4. Clasa Node reprezinta nodul generic ce contine metodele corespunzatoare fiecarei clase, A, B, sau C.

5. Clasele NodeA, NodeB si NodeC, extind clasa Node si contin metodele: - getName, ce returneaza informatia din nod.
				 					- getClassType, ce returneaza numele clasei.
				 					- getIteration, ce returneaza iteratia nodului.
				 					- getID, ce returneaza ID-ul nodului.
				 					- getNeighborsList, ce returneaza lista de noduri adiacente.
				 					- getNeighborsVector, ce returneaza vectorul de noduri adiacente.
				 					- getNeighborsSet, ce returneaza setul de noduri adiacente.
				 					- addNeighbors, ce adauga noduri adiacente, daca acestea nu exista deja.
				 					- deleteNeighbors, ce sterge noduri adiacente.

6. Interfata ItertionsInterface contine metodele specifice iteratiilor, ce trebuie implmentate.

7. Clasele List, Vector si Set, contine metodele: - add, ce adauga un nod in lista de vecini.
						  - delete, ce sterge un nod din lista de vecini.