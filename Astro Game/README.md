Visual Studio game in C++ and OpenGL about an astronaut flying through space.

For info on how to run it, please email me.


1. Clasa ReflectinPlatform contine datele pentru platforma de reflexie.
2. Clasa LandingPlatform contine datele pentru platforma de aterizare.
3. Clasa FinalPlatform contine datele pentru platforma finala.
4. Clasa Astronaut contine datele pentru astronaut.
5. Clasa Asteroid contine datele pentru asteroizi.
6. Clasa Tema1 contine variabilele, obiectele si functiile necesare temei.
7. In fisierul Tema1.cpp:
	- Metoda Init() initializeaza datele si introduce meshele in hashmap. Tot aici se creeaza
	  si punctele pentru asteroid.
	- Metoda LandingPlatformCollision() calculeaza translatia initiala, 
	  pozitia varfului si unghiul de rotatie, in functie de latura.
	- Metoda ReflectionPlatformCollision() calculeaza translatia initiala, 
	  pozitia varfului unghiul de rotatie si noul cadran, dupa coliziune, 
	  in functie de latura.
	- Metoda AsteroidCollision() calculeaza translatia initiala, pozitia varfului 
          si unghiul de rotatie, in functie de latura, pentru asteroid.
	- Metoda GameOver() calculeaza coliziune cu platforma de final si reseteaza jocul.
	- Metoda Update() calculeaza, detecteaza coliziuni si aplica transformari la fiecare pas, 
	  in functie de cadran sau de latura, precum: calculare pozitie varf astronaut,
	  calculare translatie si rotatie astronaut, detectare coliziune cu LandingPlatform,
	  detectare coliziune cu ReflexionPlatform, detectare coliziune si calculare pozitii noi asteroizi.
	- Metoda OnMouseBtnPress() calculeaza viteza si unghiul de rotatie pana la pozitia mouse-ului.

8. Fisierul Main.cpp este cel din framework.


9. Observatii: Am sters: - /Visual Studio/obj
			 - /Visual Studio/Framework_EGC.VC
			 - /x64/
			 - /libs/
