// Versuch1b.cpp
// Ausgangssoftware des 1. Praktikumsversuchs 
// zur Vorlesung Echtzeit-3D-Computergrahpik
// von Prof. Dr. Alfred Nischwitz
// Programm umgesetzt mit der GLTools Library und Vertex-Arrays
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
#include <GL/freeglut.h>
#include <AntTweakBar.h>

GLShaderManager shaderManager;
GLMatrixStack modelViewMatrix;
GLMatrixStack projectionMatrix;
GLGeometryTransform transformPipeline;
GLFrustum viewFrustum;

GLBatch konus;
GLBatch boden;
GLBatch tria;
GLBatch line;




// Definition der Kreiszahl 
#define GL_PI 3.1415f

// Rotationsgroessen
static float rotation[] = { 0, 0, 0, 0 };

// Flags fuer Schalter
bool bCull = false;
bool bOutline = false;
bool bDepth = true;


//GUI
TwBar *bar;
void InitGUI()
{
	bar = TwNewBar("TweakBar");
	TwDefine(" TweakBar size='200 400'");
	TwAddVarRW(bar, "Model Rotation", TW_TYPE_QUAT4F, &rotation, "");
	TwAddVarRW(bar, "Depth Test?", TW_TYPE_BOOLCPP, &bDepth, "");
	TwAddVarRW(bar, "Culling?", TW_TYPE_BOOLCPP, &bCull, "");
	TwAddVarRW(bar, "Backface Wireframe?", TW_TYPE_BOOLCPP, &bOutline, "");
	//Hier weitere GUI Variablen anlegen. F�r Farbe z.B. den Typ TW_TYPE_COLOR4F benutzen
}
void triangele() {
	const int a = 6;
	M3DVector3f triaVertices[a*3];
	M3DVector4f konusColors[a*3];


	M3DVector3f lineVertices[a*2];
	M3DVector4f lineColors[a*2];


	float abc = (2.0f * GL_PI) / a;

	for (int i = 0; i < a; i++) {
		float x = 10*cos(abc* i);
		float y = 10*sin(abc * i);
		float x1 = 10*cos(abc * (i+1));
		float y1 = 10*sin(abc * (i+1));


		m3dLoadVector4(konusColors[i * 3 + 0], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 3 + 0], 0, 0, 0);

		m3dLoadVector4(konusColors[i * 3 + 1], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 3 + 1], x, y, 0);

		m3dLoadVector4(konusColors[i * 3 + 2], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 3 + 2], x1, y1, 0);


		m3dLoadVector3(lineVertices[i*2+0], x, y, 0);
		m3dLoadVector4(lineColors[i * 2 + 0], 0, 0.6, 1, 1);

		m3dLoadVector3(lineVertices[i * 2 + 1], x+x, y+y, 0);
		m3dLoadVector4(lineColors[i * 2 + 1], 0, 0.6, 1, 1);


	}

	tria.Begin(GL_TRIANGLES, a*3);
	tria.CopyVertexData3f(triaVertices);
	tria.CopyColorData4f(konusColors);
	tria.End();
	
	line.Begin(GL_LINES, a*2);
	line.CopyVertexData3f(lineVertices);
	line.CopyColorData4f(lineColors);
	line.End();

	//b


	//C
//	m3dLoadVector4(konusColors[2], 1, 0.8, 0.2, 1);
//	m3dLoadVector3(triaVertices[2], 075.68024953, 075.68024953, 0);


	/*
	M3DVector3f ab;
	m3dSubtractVectors3(ab, triaVertices[1], triaVertices[0]);
	M3DVector3f ac;
	m3dSubtractVectors3(ac, triaVertices[2], triaVertices[0]);

	
	M3DVector3f cross;
	m3dCrossProduct3(cross, ab, ac);

	M3DVector3f norm;
	m3dNormalizeVector3( cross);
	*/
	//tria.Normal3fv(cross);

	//18

	
	/*
	M3DVector3f lineVertices[2];
	M3DVector4f lineColors[2];
	//A
	m3dLoadVector3(lineVertices[0], 0, 0, 0);
	m3dLoadVector4(lineColors[0], 0, 0.6, 1, 1);

	//b
//	m3dLoadVector3(lineVertices[1], 10 *cross[0], 10*cross[1], 10*cross[2]);
	m3dLoadVector3(lineVertices[1], 10 * 10, 10 * 10, 10 * 10);
	m3dLoadVector4(lineColors[1], 0, 0.6, 1, 1);


	line.Begin(GL_LINES, 2);
	line.CopyVertexData3f(lineVertices);
	line.CopyColorData4f(lineColors);
	line.End();


	
	*/
}

void CreateGeometry()
{
	//18 Vertices anlegen
	M3DVector3f konusVertices[18];
	M3DVector4f konusColors[18];
	// Die Spitze des Konus ist ein Vertex, den alle Triangles gemeinsam haben;
	// um einen Konus anstatt einen Kreis zu produzieren muss der Vertex einen positiven z-Wert haben
	m3dLoadVector3(konusVertices[0], 0, 0, 75);
	m3dLoadVector4(konusColors[0], 0, 1, 0, 1);
	// Kreise um den Mittelpunkt und spezifiziere Vertices entlang des Kreises
	// um einen Triangle_Fan zu erzeugen
	int iPivot = 1;
	int i = 1;
	for (float angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		// Berechne x und y Positionen des naechsten Vertex
		float x = 50.0f*sin(angle);
		float y = 50.0f*cos(angle);

		// Alterniere die Farbe zwischen Rot und Gruen
		if ((iPivot % 2) == 0)
			m3dLoadVector4(konusColors[i], 0.235, 0.235, 0.235, 1);
		else
			m3dLoadVector4(konusColors[i], 0, 0.6, 1, 1);

		// Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		iPivot++;

		// Spezifiziere den naechsten Vertex des Triangle_Fans
		m3dLoadVector3(konusVertices[i], x, y, 0);
		i++;
	}

	konus.Begin(GL_TRIANGLE_FAN, 18);
	konus.CopyVertexData3f(konusVertices);
	konus.CopyColorData4f(konusColors);
	konus.End();



	// Erzeuge einen weiteren Triangle_Fan um den Boden zu bedecken
	M3DVector3f bodenVertices[18];
	M3DVector4f bodenColors[18];
	// Das Zentrum des Triangle_Fans ist im Ursprung
	m3dLoadVector3(bodenVertices[0], 0, 0, 0);
	m3dLoadVector4(bodenColors[0], 1, 0, 0, 1);
	i = 1;
	for (float angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		// Berechne x und y Positionen des naechsten Vertex
		float x = 50.0f*sin(angle);
		float y = 50.0f*cos(angle);

		// Alterniere die Farbe zwischen Rot und Gruen
		if ((iPivot % 2) == 0)
			m3dLoadVector4(bodenColors[i], 1, 0.8, 0.2, 1);
		else
			m3dLoadVector4(bodenColors[i], 0, 0.8, 0, 1);

		// Inkrementiere iPivot um die Farbe beim naechsten mal zu wechseln
		iPivot++;

		// Spezifiziere den naechsten Vertex des Triangle_Fans
		m3dLoadVector3(bodenVertices[i], x, y, 0);
		i++;
	}

	boden.Begin(GL_TRIANGLE_FAN, 18);
	boden.CopyVertexData3f(bodenVertices);
	boden.CopyColorData4f(bodenColors);
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

	//setze den Shader f�r das Rendern
	shaderManager.UseStockShader(GLT_SHADER_FLAT_ATTRIBUTES, transformPipeline.GetModelViewProjectionMatrix());
	//Zeichne Konus
	line.Draw();
	tria.Draw();
	//	konus.Draw();
//	boden.Draw();
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
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
	//erzeuge die geometrie
	triangele();
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
		viewFrustum.SetOrthographic(-nRange, nRange, -nRange * float(h) / float(w), nRange * float(h) / float(w), -nRange, nRange);
	else
		viewFrustum.SetOrthographic(-nRange * float(w) / float(h), nRange * float(w) / float(h), -nRange, nRange, -nRange, nRange);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	// Ruecksetzung des Model view matrix stack
	modelViewMatrix.LoadIdentity();

	TwWindowSize(w, h);
}

void ShutDownRC()
{
	//GUI aufr�umen
	TwTerminate();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Versuch1");
	glutCloseFunc(ShutDownRC);

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

	TwInit(TW_OPENGL_CORE, NULL);
	SetupRC();
	glutMainLoop();

	return 0;
}
