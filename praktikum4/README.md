# Praktikum 4
## David Haupenthal und Nicole Gertz

## Aufgabe 4.1 a)

Um die szene zu animieren, muss die RenderScene-Funktion regelmäßig mit neuen Werten aufgerufen. Dafür haben wir eine Timer-Funktion ausgewählt. Eine globale Variabel in der Timer-Funktion ist definiert, die in der RenderScene-Funktion zur Positionsänderung benützt wird. Zwei methode sind in der Timer-Funktion drin: glutPostRedisplay() und glutTimerFunc(20, TimerFunc, 0). Durch den glutPostRedisplay-Methode wird ein Flag gesetzt, das in der Hauptprogramm-Schleife den Aufruf der Funktion RenderScene() auslöst. Der erste Parameter in glutTimerFunc() bedeutet nach wie viele Millisekunden die rekursive TimerFunc-Method (zweite Parameter) erneut aufgerufen wird. Jedes Aufruf von der TimerFunc-Methode erhöht den globale Variabel t um eins.

## Aufgabe 4.1 b)


## Aufgabe 4.2
