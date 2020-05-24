# Praktikum 3
## David Haupenthal und Nicole Gertz

## Aufgabe 3.1 d)

Die Funktion _void glFrontFace(GLenum mode)_ kontrolliert, welche Seite des Objekts die "vorder" Seite ist, indem es definiert, welche Seiten des Polygons vorne und hinter sind. Die zwei "Modes" sind _GL_CW_ für Clockwise oder Uhrzeigersinn und _GL_CCW_ für Counter-Clockwise oder Gegenuhrzeigersinn.

Die Funktion _glCullFace_ bestimmt, ob die Vorderseite bzw. die Rückseite entfernt (culled) werden darf. Dazu muss "Cull Face" aktiviert  sein mit _glEnable(GL_CULL_FACE)_. 

Wenn das Programm weißt, welche Seite vorne ist, muss es nicht die Rückseite zeichnen, was der Zeichenvorgang enorm beschleunigt.

## Aufgabe 3.1 e)

## Aufgabe 3.2 a) Quader

## Aufgabe 3.2 a) Kugel

## Aufgabe 3.2 a) Zylinder

## Aufgabe 3.2 b) Komplexe Szene

