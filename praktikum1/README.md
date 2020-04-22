# Praktikum1

## Aufgabe1
![orginal](docs/orginal.PNG)
*Passthroughfilter*

Gibt das Bild unverändert aus.

![bewmit](docs/BewMit.PNG)
*Bew Mit Filter*

Bei dem Filter "Bew Mit" wird der Durchschnittsfarbwert von einem Pixel und die acht Nachbarn gebildet, dabei wird im bild eine leichte Unschärfe erzeugt.


## Aufgabe2

1. Brightness_Contrast: 
* param1.x -> Helligkeit, Bei negativen Werten dunkler, positve Werte heller.
* param1.y -> Kontrast: nur positive Werte. Kontrast steigt. 

Filter ändert Kontrast und Helligkeit. 

![bright](docs/Brightness_Contrast.PNG)
*Brightness Contrast Filter: Helligkeit auf 4*

![contrast](docs/Brightness_0_Contrast_3.PNG)
*Brightness Contrast Filter: Kontrast auf 3*
   
2. Gauss3x3: 
* param1.x -> Glättungs-Faktor nur postive Werte

Glätttet die Kanten --> kleiner Stukturen gehen verloren, gröberer bleiben erhalten, vermeidet Bildrauschen

![3gauss](docs/3x3.PNG)
   
3. Gauss5x5:  
* param1.x -> Glättungs-Faktor nur postive Werte
* param1.y --> muss auf !=0 eingestellt sein

Glätttet die Kanten --> kleiner Stukturen gehen verloren, gröberer bleiben erhalten, vermeidet Bildrauschen

![5gauss](docs/5x5.PNG)
   
4. Gauss7x7: 

HX-Teil (Gauss7x7)
* param1.x -> Glättungs-Faktor nur postive Werte

HY-Teil (Gauss 5x5)
* param1.x -> Glättungs-Faktor nur postive Werte
* param1.y ->muss auf 0 eingestellt werden

Glätttet die Kanten --> kleiner Stukturen gehen verloren, gröberer bleiben erhalten, vermeidet Bildrauschen

FpS haben sich halbiert. 49 Multiplikation + Addition --> 14 Multiplikation + Addition

![7gauss](docs/7x7.PNG)

   
5. Laplace:
* param1.x --> Heligkeit 
* param1.y --> Kontrast nur positive Werte

Kantenerkennung 2. diskrete Ableitung

![laplacex](docs/Laplace_X.PNG)
*Laplace Filter mit param.x Faktor*

![laplacey](docs/Laplace_Y.PNG)
*Laplace Filter mit param.y Faktor*

6. Sobel:
* param1.x --> Heligkeit 
* param1.y --> Kontrast nur positive Werte

 1. Ableitung Kantenerkennung

![sobelx](docs/Sobel_X.PNG)
*Sobel Filter mit param.x Faktor*

![sobely](docs/Sobel_Y.PNG)
*Sobel Filter mit param.y Faktor*
   
7. Sharben:
* param1.x: parameter für die Schärfe

Stellt die Schärfe eines Bildes ein

![sharpenPos](docs/Sharpen_Pos.PNG)
*Sharpen Filter mit einem positiven param.x Faktor*

![sharpenNeg](docs/Sharpen_Neg.PNG)
*Sharpen Filter mit einem negitiven param.x Faktor*
   
8. Dilatation:
* param1.x -> Einstellen der Distanz

Erweitert den Weißbereich, dunklere Bereiche werden überschrieben. Der horiontale und vertikale Anteil kann nicht aufgespalte, weil der Filter nicht aus einer symetrischen Matrix besteht. Diagonalpixel würden nicht betrachtet werden.


![dilatation](docs/dilatation.PNG)
   
9. Erosion:
* param1.x -> Einstellen der Distanz

Erweiterung der dunklen Bereiche auf Kosten der Weißbereiche. Der horiontale und vertikale Anteil kann nicht aufgespalte, weil der Filter nicht aus einer symetrischen Matrix besteht. Diagonalpixel würden nicht betrachtet werden.

![errosion](docs/errosion.PNG)


## Aufgabe3

![aufgabe3](docs/aufgabe3.PNG)


