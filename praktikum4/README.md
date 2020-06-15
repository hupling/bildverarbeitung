# Praktikum 4
## David Haupenthal und Nicole Gertz

## Aufgabe 4.1 a)

Um die Szene zu animieren, muss die RenderScene-Funktion regelmäßig mit neuen Werten aufgerufen werden. Dafür haben wir eine Timer-Funktion ausgewählt. Eine globale Variabel in der Timer-Funktion ist definiert, die in der RenderScene-Funktion zur Positionsänderung benutzt wird. Zwei Methoden sind in der Timer-Funktion enthalten: glutPostRedisplay() und glutTimerFunc(20, TimerFunc, 0). Durch die glutPostRedisplay-Methode wird eine Flag gesetzt, die in der Hauptprogramm-Schleife den Aufruf der Funktion RenderScene() auslöst. Der erste Parameter in der glutTimerFunc() bedeutet, nach wie vieler Millisekunden die rekursive TimerFunc-Method (zweite Parameter) erneut aufgerufen wird. Jeder Aufruf von der TimerFunc-Methode erhöht die globale Variabel *t* um eins.

## Aufgabe 4.1 b)

Die Bewegung des Augenpunktes ist durch die Augenpunkt-Transformation durchgefüht worden. Das bedeutet, dass die Position sich ändert und die Blickrichtung des Augenpunkts, von dem aus die Szene betrachtet wird. Wenn die Tasten "h" und "j" gedrückt werden, wird die Rotation um die x-Achse ausgeführt und bei den "k" und "l" wird die Rotation um die y-Achse ausgeführt. Die Tasten "n" und "m" bewegt die Kamera auf der z-Achse. Die Pfeil-Tasten bewegt die Kamera auf der x- und y-Achse. 

## Aufgabe 4.2

In der Perspektivischen Projektion ist das sichtbare Volumen ein Pyramidenstumpf, der quasi auf der Seite liegt. Das ist anders als die Orthographische Projektion, wo das sichtbare Volumen ein Kubus ist. Im Code muss das GLFrustum Objekt die SetPerspective-Methode statt der SetOrthographic-Methode aufrufen. Die Parameter in der SetPerspective-Methode bedeuten erstens ein vertikalen Blickwinkel, zweitens das Verhältnis zwischen horizontalem und vertikalem Blickwinkel, drittens die vordere Grenzfläche (near clipping plane) und viertens die hintere Grenzfläche (far clipping plane). Ein kleiner Wert von "near clipping plane" weitet das sichtbare Volumen stark auf (Weitwinkel-Effekt) und ein großer Wert von "near clipping plane" engt das sichtbare Volumen stark ein (Tele-Effekt).
