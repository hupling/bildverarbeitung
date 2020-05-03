// Versuch1b.cpp
// Ausgangssoftware des 1. Praktikumsversuchs 
// zur Vorlesung Echtzeit-3D-Computergrahpik
// von Prof. Dr. Alfred Nischwitz
// Programm umgesetzt mit der GLTools Library
#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif
#include <GLTools.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <GLFrustum.h>
#include <math.h>
#include <math3d.h>
#include <GL/glut.h>
#include <AntTweakBar.h>

GLShaderManager shaderManager;
GLMatrixStack modelViewMatrix;
GLMatrixStack projectionMatrix;
GLGeometryTransform transformPipeline;
GLFrustum viewFrustum;
GLBatch konus;
GLBatch boden;
GLBatch quarder;
GLBatch quader1;
GLBatch quarder2;
GLBatch kreis;
GLBatch kreis2;
GLBatch kreis3;
GLBatch kugel;



// Definition der Kreiszahl 
#define GL_PI 3.1415f

// Rotationsgroessen
static float rotation[] = {0, 0, 0, 0};

// Flags fuer Schalter
bool bCull = false;
bool bOutline = false;
bool bDepth = true;

unsigned int tesselation = 0;

//Set Funktion für GUI, wird aufgerufen wenn Variable im GUI geändert wird
void TW_CALL SetTesselation(const void *value, void *clientData)
{
	//Pointer auf gesetzten Typ casten (der Typ der bei TwAddVarCB angegeben wurde)
	const unsigned int* uintptr = static_cast<const unsigned int*>(value);

	//Setzen der Variable auf neuen Wert
	tesselation = *uintptr;

	//Hier kann nun der Aufruf gemacht werden um die Geometrie mit neuem Tesselationsfaktor zu erzeugen


}

//Get Funktion für GUI, damit GUI Variablen Wert zum anzeigen erhält
void TW_CALL GetTesselation(void *value, void *clientData)
{
	//Pointer auf gesetzten Typ casten (der Typ der bei TwAddVarCB angegeben wurde)
	unsigned int* uintptr = static_cast<unsigned int*>(value);

	//Variablen Wert and GUI weiterreichen
	*uintptr = tesselation;
}

//GUI
TwBar *bar;
void InitGUI()
{
	bar = TwNewBar("TweakBar");
	TwDefine(" TweakBar size='200 400'");
	TwAddVarRW(bar,"Model Rotation",TW_TYPE_QUAT4F, &rotation, "");
	TwAddVarRW(bar, "Depth Test?", TW_TYPE_BOOLCPP, &bDepth, "");
	TwAddVarRW(bar, "Culling?", TW_TYPE_BOOLCPP, &bCull, "");
	TwAddVarRW(bar, "Backface Wireframe?", TW_TYPE_BOOLCPP, &bOutline, "");
	//Hier weitere GUI Variablen anlegen. Für Farbe z.B. den Typ TW_TYPE_COLOR4F benutzen

	//Tesselation Faktor als unsigned 32 bit integer definiert
	TwAddVarCB(bar, "Tesselation", TW_TYPE_UINT32, SetTesselation, GetTesselation, NULL, "");
}

void CreateGeometry()
{
	// Triangle Fan mit 18 Vertices anlegen
	konus.Begin(GL_TRIANGLE_FAN,18);
	// Die Spitze des Konus ist ein Vertex, den alle Triangles gemeinsam haben;
	// um einen Konus anstatt einen Kreis zu produzieren muss der Vertex einen positiven z-Wert haben
	konus.Vertex3f(0,0,75);
	konus.Color4f(0,1,0,1);
	// Kreise um den Mittelpunkt und spezifiziere Vertices entlang des Kreises
	// um einen Triangle_Fan zu erzeugen
	int iPivot = 1;
	for(float angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		// Berechne x und y Positionen des naechsten Vertex
		float x = 50.0f*sin(angle);
		float y = 50.0f*cos(angle);

		// Alterniere die Farbe zwischen Rot und Gruen
		if((iPivot %2) == 0)
			konus.Color4f(0.235,0.235,0.235,1);
		else
			konus.Color4f(0,0.6,1,1);

		// Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		iPivot++;

		// Spezifiziere den naechsten Vertex des Triangle_Fans
		konus.Vertex3f(x,y,0);
	}

	// Fertig mit dem Konus
	konus.End();
	

	// Erzeuge einen weiteren Triangle_Fan um den Boden zu bedecken
	boden.Begin(GL_TRIANGLE_FAN, 18);
	// Das Zentrum des Triangle_Fans ist im Ursprung
	boden.Vertex3f(0.0f, 0.0f,0.0f);
	for(float angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		// Berechne x und y Positionen des naechsten Vertex
		float x = 50.0f*sin(angle);
		float y = 50.0f*cos(angle);

		// Alterniere die Farbe zwischen Rot und Gruen
		if((iPivot %2) == 0)
			boden.Color4f(1,0.8,0.2,1);
		else
			boden.Color4f(0,0.8,0,1);

		// Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		iPivot++;

		// Spezifiziere den naechsten Vertex des Triangle_Fans
		boden.Vertex3f(x, y,0);
	}

	// Fertig mit dem Bodens
	boden.End();
	int x_q = 20;
	int y_q = 10;
	int z_q = 30;

	quarder.Begin(GL_QUAD_STRIP, 10);
	quarder.Color4f(1, 0, 0, 1);
	quarder.Vertex3f(-x_q, y_q, z_q);

	quarder.Vertex3f(x_q, y_q, z_q);

	quarder.Color4f(0, 1, 0, 1);
	quarder.Vertex3f(-x_q, -y_q, z_q);
	
	quarder.Color4f(1, 0.8, 0.2, 1);
	quarder.Vertex3f(x_q,-y_q, z_q);

	quarder.Color4f(1, 0.8, 0.2, 1);
	quarder.Vertex3f(-x_q, -y_q, -z_q);

	quarder.Color4f(1, 0.8, 0.2, 1);
	quarder.Vertex3f(x_q, -y_q, -z_q);

	quarder.Color4f(1, 0.8, 0.2, 1);
	quarder.Vertex3f(-x_q, y_q, -z_q);

	quarder.Color4f(1, 0.8, 0.2, 1);
	quarder.Vertex3f(x_q, y_q, -z_q);

	quarder.Color4f(0, 0.8, 0, 1);
	quarder.Vertex3f(-x_q, y_q, z_q);


	quarder.Color4f(1, 0.8, 0.2, 1);
	quarder.Vertex3f(x_q, y_q,z_q);

	quarder.End();

	quader1.Begin(GL_TRIANGLE_STRIP,4);
	quader1.Color4f(0, 0.8, 0, 1);

	quader1.Vertex3f(x_q, y_q, z_q);
	quader1.Color4f(0, 0.8, 0, 1);

	quader1.Vertex3f(x_q, y_q, -z_q);
	quader1.Color4f(0, 0.8, 0, 1);

	quader1.Vertex3f(x_q, -y_q, z_q);
	
	quader1.Color4f(0, 0.8, 0, 1);

	quader1.Vertex3f(x_q,-y_q, -z_q);

	quader1.End();

	quarder2.Begin(GL_TRIANGLE_STRIP, 4);
	quarder2.Color4f(0.8, 0, 0, 1);

	quarder2.Vertex3f(-x_q, y_q, -z_q);
	quarder2.Color4f(0.8, 0, 0, 1);

	quarder2.Vertex3f(-x_q, y_q, z_q);
	quarder2.Color4f(0.8, 0, 0, 1);

	quarder2.Vertex3f(-x_q, -y_q, -z_q);

	quarder2.Color4f(0.8, 0, 0, 1);

	quarder2.Vertex3f(-x_q, -y_q, z_q);

	quarder2.End();

	int test = 15;
	kreis.Begin(GL_TRIANGLE_FAN, test+2);
	// Das Zentrum des Triangle_Fans ist im Ursprung
	kreis.Vertex3f(0.0f, 0.0f, 0.0f);
	for (float angle = (2.0f * GL_PI); angle >= 0.0f; angle -= (2.0f * GL_PI / test))
	{
		// Berechne x und y Positionen des naechsten Vertex
		float x = 50.0f * sin(angle);
		float y = 50.0f * cos(angle);

		// Alterniere die Farbe zwischen Rot und Gruen
		if ((iPivot % 2) == 0)
			kreis.Color4f(1, 0.8, 0.2, 1);
		else
			kreis.Color4f(0, 0.8, 0, 1);

		// Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		iPivot++;

		// Spezifiziere den naechsten Vertex des Triangle_Fans
		kreis.Vertex3f(x, y, 0);
	}

	// Fertig mit dem Bodens
       kreis.End();

	   kreis2.Begin(GL_TRIANGLE_FAN, test + 2);
	   // Das Zentrum des Triangle_Fans ist im Ursprung
	   kreis2.Vertex3f(0.0f, 0.0f, 75);
	   for (float angle = 0.0f; angle <= (2.0f * GL_PI); angle += (2.0f * GL_PI / test))

	   {
		   // Berechne x und y Positionen des naechsten Vertex
		   float x = 50.0f * sin(angle);
		   float y = 50.0f * cos(angle);

		   // Alterniere die Farbe zwischen Rot und Gruen
		   if ((iPivot % 2) == 0)
			   kreis2.Color4f(1, 0.8, 0.2, 1);
		   else
			   kreis2.Color4f(0, 0.8, 0, 1);

		   // Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		   iPivot++;

		   // Spezifiziere den naechsten Vertex des Triangle_Fans
		   kreis2.Vertex3f(x, y, 75);
	   }

	   // Fertig mit dem Bodens
	   kreis2.End();


	   kreis3.Begin(GL_QUAD_STRIP, 2*test + 2);
	   // Das Zentrum des Triangle_Fans ist im Ursprung

	 //  for (float angle = 0.0f; angle <= (2.0f * GL_PI); angle += (2.0f * GL_PI / test)){
	 for (int angle1 = 0; angle1 <= test; angle1 ++){
	
		   float angle = angle1*2.0f * GL_PI / test;
		   // Berechne x und y Positionen des naechsten Vertex
		   float x = 50.0f * sin(angle);
		   float y = 50.0f * cos(angle);
		   kreis3.Vertex3f(x, y, 75);
		   // Alterniere die Farbe zwischen Rot und Gruen
		 
		   if ((iPivot % 2) == 0)
			   kreis3.Color4f(1, 0.8, 0.2, 1);
		   else
			   kreis3.Color4f(0, 0.8, 0, 1);

		   // Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		   iPivot++;
	
		   // Spezifiziere den naechsten Vertex des Triangle_Fans
		//   kreis3.Color4f(1, 0.8, 0.2, 1);
		  

		 //  kreis3.Color4f(1, 0.8, 0.2, 1);
		   kreis3.Vertex3f(x, y, 0);
	   }

	   // Fertig mit dem Bodens
	   kreis3.End();

	   int test1 =15;
	   kugel.Begin(GL_TRIANGLE_STRIP,test1*2);
	   //0/0/0
	   //0/0/100
	   kugel.Color4f(1, 0.8, 0.2, 1);
	   kugel.Vertex3f(0, 0, -50);

	   for (int angle1 = 0; angle1 <= test1; angle1++) {
		   if (angle1 != 0 && angle1 != test1) {
			    float angle = angle1 *  GL_PI / test1;
		// Berechne x und y Positionen des naechsten Vertex
			   float y = 50.0f * sin(angle);
			   float x = -50.0f * cos(angle);


			   kugel.Color4f(1, 0.8, 0.2, 1);
			   kugel.Vertex3f(y* cos(0), y*sin(0), x);

			   kugel.Color4f(1, 0.8, 0.2, 1);
			   kugel.Vertex3f(y*  cos(GL_PI / 4), y* sin(GL_PI / 4), x);
		   }
	   }
	 

	   kugel.Color4f(1, 0.8, 0.2, 1);
	  kugel.Vertex3f(0, 0, 50);
	  kugel.End();

}

// Aufruf draw scene
void RenderScene(void)
{
	// Clearbefehle für den color buffer und den depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Schalte culling ein falls das Flag gesetzt ist
	if(bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Schalte depth testing ein falls das Flag gesetzt ist
	if(bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// Zeichne die Rückseite von Polygonen als Drahtgitter falls das Flag gesetzt ist
	if(bOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);

	// Speichere den matrix state und führe die Rotation durch
	modelViewMatrix.PushMatrix();
	M3DMatrix44f rot;
	m3dQuatToRotationMatrix(rot,rotation);
	modelViewMatrix.MultMatrix(rot);

	//setze den Shader für das Rendern und übergebe die Model-View-Projection Matrix
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	//Zeichne Konus und Boden
	//konus.Draw();
//	boden.Draw();
	//quarder.Draw();
//	quader1.Draw();
	//quarder2.Draw();
	//kreis.Draw();
//	kreis2.Draw();
	//kreis3.Draw();
	kugel.Draw();

	//Auf fehler überprüfen
	gltCheckErrors(0);
	// Hole die im Stack gespeicherten Transformationsmatrizen wieder zurück
	modelViewMatrix.PopMatrix();

	TwDraw();
	// Vertausche Front- und Backbuffer
	glutSwapBuffers();
	glutPostRedisplay();
}

// Initialisierung des Rendering Kontextes
void SetupRC()
{
	// Schwarzer Hintergrund
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	// In Uhrzeigerrichtung zeigende Polygone sind die Vorderseiten.
	// Dies ist umgekehrt als bei der Default-Einstellung weil wir Triangle_Fans benützen
	glFrontFace(GL_CW);

	//initialisiert die standard shader
	shaderManager.InitializeStockShaders();
	//Matrix stacks für die Transformationspipeline setzen, damit werden dann automatisch die Matrizen multipliziert
	transformPipeline.SetMatrixStacks(modelViewMatrix,projectionMatrix);
	//erzeuge die geometrie
	CreateGeometry();
	InitGUI();
}

void SpecialKeys(int key, int x, int y)
{
	TwEventKeyboardGLUT(key, x, y);
	// Zeichne das Window neu
	glutPostRedisplay();
}


void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	// Verhindere eine Division durch Null
	if(h == 0)
		h = 1;
	// Setze den Viewport gemaess der Window-Groesse
	glViewport(0, 0, w, h);
	// Ruecksetzung des Projection matrix stack
	projectionMatrix.LoadIdentity();
	
	// Definiere das viewing volume (left, right, bottom, top, near, far)
	if (w <= h) 
		viewFrustum.SetOrthographic(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else 
		viewFrustum.SetOrthographic(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	// Ruecksetzung des Model view matrix stack
	modelViewMatrix.LoadIdentity();

	TwWindowSize(w, h);
}

void ShutDownRC()
{
	TwTerminate();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("Versuch1");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Veralteter Treiber etc.
		std::cerr <<"Error: "<< glewGetErrorString(err) << "\n";
		return 1;
	}

	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT); // same as MouseMotion
	glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);

	TwInit(TW_OPENGL, NULL);
	SetupRC();
	glutMainLoop();
	ShutDownRC();
	
	return 0;
}
