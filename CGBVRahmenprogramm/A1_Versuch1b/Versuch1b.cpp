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
GLBatch kreis_t;
GLBatch kugel_t;
GLBatch quarder_t;
GLBatch quarder_t1;



// Definition der Kreiszahl 
#define GL_PI 3.1415f

// Rotationsgroessen
static float rotation[] = { 0, 0, 0, 0 };

// Flags fuer Schalter
bool bCull = false;
bool bOutline = false;
bool bDepth = true;

unsigned int tesselation = 0;


M3DVector3f* calculateQuarder(float x, float y, float z, int* step) {
	M3DVector3f* Vertices = new M3DVector3f[14];


	int x_t1[] = { -1, 1, -1, 1, 1, 1, 1, -1, -1, -1, -1, 1, -1, 1 };
	int y_t1[] = { 1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,1 };
	int z_t1[] = { 1,1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1 };


	for (int i = 0; i < 14; i++) {
		Vertices[i][0] = x_t1[i] * x;
		Vertices[i][1] = y_t1[i] * y;
		Vertices[i][2] = z_t1[i] * z;
	}
	*step = 14;
	return Vertices;
}
M3DVector3f* calculateCylinder(float r, float h, int* step) {
	int count = *step;

	M3DVector3f* Vertices = new M3DVector3f[count * 6];

	int ho[4] = { -1, -1,1,1 };
	int ra[4] = { 0,1,1,0 };
	int counter = 0;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < count; i++) {
			float angle = i * 2.0f * GL_PI / count;
			float x = r * cos(angle);
			float y = r * sin(angle);

			for (int c = 0; c < 2; c++) {

				Vertices[counter][0] = ra[j + c] * x;
				Vertices[counter][1] = ra[j + c] * y;
				Vertices[counter][2] = ho[j + c] * h;

				counter++;
			}
		}
	}
	*step = count * 6;
	return Vertices;
}
M3DVector3f* calculateBall(float r, unsigned int* step) {
	int count = *step;
	
	M3DVector3f* Vertices = new M3DVector3f[count * count * 2];
	int counter = 0;

	for (int j = 0; j < count; j++) {
		for (int i = 0; i < count; i++) {
			for (int c = 0; c < 2; c++) {
				float angle_horizontal = i * 2.0f * GL_PI / count;
				float angle_vertical = (j + c) * GL_PI / count;

				Vertices[counter][0] = r * sin(angle_vertical) * cos(angle_horizontal);
				Vertices[counter][1] = r * sin(angle_vertical) * sin(angle_horizontal);
				Vertices[counter][2] = -r * cos(angle_vertical);

				counter++;
			}
		}
	}

	*step = count * count * 2;

	return Vertices;
}




//Set Funktion f�r GUI, wird aufgerufen wenn Variable im GUI ge�ndert wird
void TW_CALL SetTesselation(const void* value, void* clientData)
{
	//Pointer auf gesetzten Typ casten (der Typ der bei TwAddVarCB angegeben wurde)
	const unsigned int* uintptr = static_cast<const unsigned int*>(value);

	//Setzen der Variable auf neuen Wert
	tesselation = *uintptr;

	//Hier kann nun der Aufruf gemacht werden um die Geometrie mit neuem Tesselationsfaktor zu erzeugen

	quarder_t1.Free();
unsigned	int number = tesselation;
	
	M3DVector3f* a = calculateBall( 40, &number);

	quarder_t1.Begin(GL_TRIANGLE_STRIP, number);
	for (int i = 0; i < number; i++) {
		switch (i % 4) {
		case 0:
			quarder_t1.Color4f(1, 0.8, 0.2, 1);
			break;
		case 1:
			quarder_t1.Color4f(1, 0.8, 0.2, 1);
			break;
		case 2:
			quarder_t1.Color4f(0, 0.8, 0, 1);

			break;
		case 3:
			quarder_t1.Color4f(0, 0.8, 0, 1);

			break;
		}


		quarder_t1.Vertex3fv(a[i]);
	}
	quarder_t1.End();


}

//Get Funktion f�r GUI, damit GUI Variablen Wert zum anzeigen erh�lt
void TW_CALL GetTesselation(void* value, void* clientData)
{
	//Pointer auf gesetzten Typ casten (der Typ der bei TwAddVarCB angegeben wurde)
	unsigned int* uintptr = static_cast<unsigned int*>(value);

	//Variablen Wert and GUI weiterreichen
	*uintptr = tesselation;
}

//GUI
TwBar* bar;
void InitGUI()
{
	bar = TwNewBar("TweakBar");
	TwDefine(" TweakBar size='200 400'");
	TwAddVarRW(bar, "Model Rotation", TW_TYPE_QUAT4F, &rotation, "");
	TwAddVarRW(bar, "Depth Test?", TW_TYPE_BOOLCPP, &bDepth, "");
	TwAddVarRW(bar, "Culling?", TW_TYPE_BOOLCPP, &bCull, "");
	TwAddVarRW(bar, "Backface Wireframe?", TW_TYPE_BOOLCPP, &bOutline, "");
	//Hier weitere GUI Variablen anlegen. F�r Farbe z.B. den Typ TW_TYPE_COLOR4F benutzen

	//Tesselation Faktor als unsigned 32 bit integer definiert
	TwAddVarCB(bar, "Tesselation", TW_TYPE_UINT32, SetTesselation, GetTesselation, NULL, "");
}


void CreateGeometry()
{
	// Triangle Fan mit 18 Vertices anlegen
	konus.Begin(GL_TRIANGLE_FAN, 18);
	// Die Spitze des Konus ist ein Vertex, den alle Triangles gemeinsam haben;
	// um einen Konus anstatt einen Kreis zu produzieren muss der Vertex einen positiven z-Wert haben
	konus.Vertex3f(0, 0, 75);
	konus.Color4f(0, 1, 0, 1);
	// Kreise um den Mittelpunkt und spezifiziere Vertices entlang des Kreises
	// um einen Triangle_Fan zu erzeugen
	int iPivot = 1;
	for (float angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		// Berechne x und y Positionen des naechsten Vertex
		float x = 50.0f * sin(angle);
		float y = 50.0f * cos(angle);

		// Alterniere die Farbe zwischen Rot und Gruen
		if ((iPivot % 2) == 0)
			konus.Color4f(0.235, 0.235, 0.235, 1);
		else
			konus.Color4f(0, 0.6, 1, 1);

		// Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		iPivot++;

		// Spezifiziere den naechsten Vertex des Triangle_Fans
		konus.Vertex3f(x, y, 0);
	}

	// Fertig mit dem Konus
	konus.End();


	// Erzeuge einen weiteren Triangle_Fan um den Boden zu bedecken
	boden.Begin(GL_TRIANGLE_FAN, 18);
	// Das Zentrum des Triangle_Fans ist im Ursprung
	boden.Vertex3f(0.0f, 0.0f, 0.0f);
	for (float angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		// Berechne x und y Positionen des naechsten Vertex
		float x = 50.0f * sin(angle);
		float y = 50.0f * cos(angle);

		// Alterniere die Farbe zwischen Rot und Gruen
		if ((iPivot % 2) == 0)
			boden.Color4f(1, 0.8, 0.2, 1);
		else
			boden.Color4f(0, 0.8, 0, 1);

		// Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		iPivot++;

		// Spezifiziere den naechsten Vertex des Triangle_Fans
		boden.Vertex3f(x, y, 0);
	}

	// Fertig mit dem Bodens
	boden.End();

	




}

// Aufruf draw scene
void RenderScene(void)
{
	// Clearbefehle f�r den color buffer und den depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Schalte culling ein falls das Flag gesetzt ist
	if (bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Schalte depth testing ein falls das Flag gesetzt ist
	if (bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// Zeichne die R�ckseite von Polygonen als Drahtgitter falls das Flag gesetzt ist
	if (bOutline)
		glPolygonMode(GL_BACK, GL_LINE);
	else
		glPolygonMode(GL_BACK, GL_FILL);

	// Speichere den matrix state und f�hre die Rotation durch
	modelViewMatrix.PushMatrix();
	M3DMatrix44f rot;
	m3dQuatToRotationMatrix(rot, rotation);
	modelViewMatrix.MultMatrix(rot);

	//setze den Shader f�r das Rendern und �bergebe die Model-View-Projection Matrix
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	//Zeichne Konus und Boden
	//konus.Draw();
//	boden.Draw();

//	kreis_t.Draw();
	//	kugel_t.Draw();
	quarder_t1.Draw();

	//Auf fehler �berpr�fen
	gltCheckErrors(0);
	// Hole die im Stack gespeicherten Transformationsmatrizen wieder zur�ck
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// In Uhrzeigerrichtung zeigende Polygone sind die Vorderseiten.
	// Dies ist umgekehrt als bei der Default-Einstellung weil wir Triangle_Fans ben�tzen
	glFrontFace(GL_CW);

	//initialisiert die standard shader
	shaderManager.InitializeStockShaders();
	//Matrix stacks f�r die Transformationspipeline setzen, damit werden dann automatisch die Matrizen multipliziert
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
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
	if (h == 0)
		h = 1;
	// Setze den Viewport gemaess der Window-Groesse
	glViewport(0, 0, w, h);
	// Ruecksetzung des Projection matrix stack
	projectionMatrix.LoadIdentity();

	// Definiere das viewing volume (left, right, bottom, top, near, far)
	if (w <= h)
		viewFrustum.SetOrthographic(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		viewFrustum.SetOrthographic(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
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
	glutInitWindowSize(800, 600);
	glutCreateWindow("Versuch1");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Veralteter Treiber etc.
		std::cerr << "Error: " << glewGetErrorString(err) << "\n";
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
