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
GLBatch cylinder_t;
GLBatch quarder_t;
GLBatch ball_t;



// Definition der Kreiszahl 
#define GL_PI 3.1415f

// Rotationsgroessen
static float rotation[] = { 0, 0, 0, 0 };

// Flags fuer Schalter
bool bCull = false;
bool bOutline = false;
bool bDepth = true;

unsigned int tesselation = 10;

unsigned int dimension = 0;


M3DVector3f* calculateQuarder(float x, float y, float z, unsigned int* step) {
	M3DVector3f* Vertices = new M3DVector3f[14];


	int x_t1[] = { -1, 1, -1, 1, 1, 1, 1, -1, -1, -1, -1, 1, -1, 1 };
	int y_t1[] = { 1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,1 };
	int z_t1[] = { 1,1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1 };


	for (int i = 0; i < 14; i++) {
		Vertices[i][0] = x_t1[i] * x + 10;
		Vertices[i][1] = y_t1[i] * y + 10;
		Vertices[i][2] = z_t1[i] * z + 10;
	}
	*step = 14;
	return Vertices;
}
M3DVector3f* calculateCylinder(float r, float h, unsigned int* step) {
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

void drawBall() {
	ball_t.Free();
	unsigned	int number = tesselation + 3;
	unsigned int size = dimension;

	M3DVector3f* a = calculateBall(18 + dimension, &number);

	ball_t.Begin(GL_TRIANGLE_STRIP, number);
	for (int i = 0; i < number; i++) {
		switch (i % 4) {
		case 0:
			ball_t.Color4f(1, 0.8, 0.2, 1);
			break;
		case 1:
			ball_t.Color4f(1, 0.8, 0.2, 1);
			break;
		case 2:
			ball_t.Color4f(0, 0.8, 0, 1);

			break;
		case 3:
			ball_t.Color4f(0, 0.8, 0, 1);

			break;
		}


		ball_t.Vertex3fv(a[i]);
	}
	ball_t.End();
}

void drawCube() {
	quarder_t.Free();
	unsigned	int number = tesselation + 3;
	unsigned int size = dimension;

	M3DVector3f* a = calculateQuarder(3 + dimension, 3 + dimension, 2 + dimension, &number);

	quarder_t.Begin(GL_TRIANGLE_STRIP, number);
	for (int i = 0; i < number; i++) {
		switch (i % 4) {
		case 0:
			quarder_t.Color4f(1, 0.8, 0.2, 1);
			break;
		case 1:
			quarder_t.Color4f(1, 0.8, 0.2, 1);
			break;
		case 2:
			quarder_t.Color4f(0, 0.8, 0, 1);

			break;
		case 3:
			quarder_t.Color4f(0, 0.8, 0, 1);

			break;
		}


		quarder_t.Vertex3fv(a[i]);
	}
	quarder_t.End();
}

void drawCylinder() {
	cylinder_t.Free();
	unsigned	int number = tesselation + 3;
	unsigned int size = dimension;

	M3DVector3f* a = calculateCylinder(17 + dimension, 27 + dimension, &number);

	cylinder_t.Begin(GL_TRIANGLE_STRIP, number);
	for (int i = 0; i < number; i++) {
		switch (i % 4) {
		case 0:
			cylinder_t.Color4f(1, 0.8, 0.2, 1);
			break;
		case 1:
			cylinder_t.Color4f(1, 0.8, 0.2, 1);
			break;
		case 2:
			cylinder_t.Color4f(0, 0.8, 0, 1);

			break;
		case 3:
			cylinder_t.Color4f(0, 0.8, 0, 1);

			break;
		}


		cylinder_t.Vertex3fv(a[i]);
	}
	cylinder_t.End();
}


//Set Funktion für GUI, wird aufgerufen wenn Variable im GUI geändert wird
void TW_CALL SetTesselation(const void* value, void* clientData)
{
	//Pointer auf gesetzten Typ casten (der Typ der bei TwAddVarCB angegeben wurde)
	const unsigned int* uintptr = static_cast<const unsigned int*>(value);

	//Setzen der Variable auf neuen Wert
	tesselation = *uintptr;

	//Hier kann nun der Aufruf gemacht werden um die Geometrie mit neuem Tesselationsfaktor zu erzeugen

	
	drawCube();
	drawCylinder();
	drawBall();


}

//Get Funktion für GUI, damit GUI Variablen Wert zum anzeigen erhält
void TW_CALL GetTesselation(void* value, void* clientData)
{
	//Pointer auf gesetzten Typ casten (der Typ der bei TwAddVarCB angegeben wurde)
	unsigned int* uintptr = static_cast<unsigned int*>(value);

	//Variablen Wert and GUI weiterreichen
	*uintptr = tesselation;
}

// Set Funtion for Gui, is called when the variable is changed in GUI
void TW_CALL SetDimension(const void* value, void* clientData) {
	const unsigned int* uintptr = static_cast<const unsigned int*>(value);

	dimension = *uintptr;

	//call all draw methods to make objects bigger
	drawCube();
	drawCylinder();
	drawBall();

}

//Get function for Scale in GUI
void TW_CALL GetDimension(void* value, void* clientData) {
	unsigned int* uintptr = static_cast<unsigned int*>(value);

	*uintptr = dimension;
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
	
	//Hier weitere GUI Variablen anlegen. Für Farbe z.B. den Typ TW_TYPE_COLOR4F benutzen

	//Tesselation Faktor als unsigned 32 bit integer definiert
	TwAddVarCB(bar, "Tesselation", TW_TYPE_UINT32, SetTesselation, GetTesselation, NULL, "");
	TwAddVarCB(bar, "Dimension", TW_TYPE_UINT32, SetDimension, GetDimension, NULL, "");
}


void CreateGeometry() {

	//modelViewMatrix.PushMatrix();
	//shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	//ball_t.Draw();
	//modelViewMatrix.PopMatrix();

//	modelViewMatrix.PushMatrix();
	//shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	//quarder_t.Draw();
	//modelViewMatrix.PopMatrix();

	//modelViewMatrix.PushMatrix();
	//shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	//cylinder_t.Draw();
	//modelViewMatrix.PopMatrix();

	




}

void move() {
	GLfloat i, j;

	//Lower Arm
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(45, 0, 0);
	modelViewMatrix.Rotate(270, -1, 1, 0);
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	cylinder_t.Draw();
	modelViewMatrix.PopMatrix();
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	//Upper Arm
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(-20, 0, 0);
	modelViewMatrix.Rotate(90, 1, 1, 0);
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	cylinder_t.Draw();
	modelViewMatrix.PopMatrix();
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	//Elbow
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(13, -30, 0);
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	ball_t.Draw();
	modelViewMatrix.PopMatrix();
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	//wrist
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(78, 30, 0);
	modelViewMatrix.Scale(1, 1, .5);
	//modelViewMatrix.Rotate(45, 45, 1, 0);
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	ball_t.Draw();
	modelViewMatrix.PopMatrix();
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

	//Fingers
	for (i = 0; i < 17; i += 9.0) {
		for (j = 0; j < 17; j += 6.0) {
			modelViewMatrix.PushMatrix();

			modelViewMatrix.Translate(76 + j + i, 39 + j - i, -10);
			shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

			quarder_t.Draw();
			modelViewMatrix.PopMatrix();
			shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
		}
}
	//small finger
		modelViewMatrix.PushMatrix();
		modelViewMatrix.Translate(85, 27, -10);
		modelViewMatrix.Rotate(30, 0, 0, -1);
		shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

		quarder_t.Draw();
		modelViewMatrix.PopMatrix();
		shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

		modelViewMatrix.PushMatrix();
		modelViewMatrix.Translate(93, 29, -10);
		modelViewMatrix.Rotate(30, 0, 0, -1);
		shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

		quarder_t.Draw();
		modelViewMatrix.PopMatrix();
		shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	

	//thumb
	for (i = 0; i > -11; i -= 6) {
		modelViewMatrix.PushMatrix();

		modelViewMatrix.Translate(55 + i, 37 - i, -10);
		shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());

		quarder_t.Draw();
		modelViewMatrix.PopMatrix();
		shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	}


}

// Aufruf draw scene
void RenderScene(void)
{
	// Clearbefehle für den color buffer und den depth buffer
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

	// Zeichne die Rückseite von Polygonen als Drahtgitter falls das Flag gesetzt ist
	if (bOutline)
		glPolygonMode(GL_BACK, GL_LINE);
	else
		glPolygonMode(GL_BACK, GL_FILL);

	// Speichere den matrix state und führe die Rotation durch
	modelViewMatrix.PushMatrix();
	M3DMatrix44f rot;
	m3dQuatToRotationMatrix(rot, rotation);
	modelViewMatrix.MultMatrix(rot);

	//setze den Shader für das Rendern und übergebe die Model-View-Projection Matrix
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());


	move();


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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// In Uhrzeigerrichtung zeigende Polygone sind die Vorderseiten.
	// Dies ist umgekehrt als bei der Default-Einstellung weil wir Triangle_Fans benützen
	glFrontFace(GL_CW);

	//initialisiert die standard shader
	shaderManager.InitializeStockShaders();
	//Matrix stacks für die Transformationspipeline setzen, damit werden dann automatisch die Matrizen multipliziert
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
	//erzeuge die geometrie
	//CreateGeometry();
	
	drawCube();
	drawCylinder();

	drawBall();
	move();

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
