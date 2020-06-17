// Ausgangssoftware des 3. Praktikumsversuchs 
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
#include <GL/freeglut.h>
#include <AntTweakBar.h>

GLMatrixStack modelViewMatrix;
GLMatrixStack projectionMatrix;
GLGeometryTransform transformPipeline;
GLFrustum viewFrustum;
GLBatch geometryBatch;
GLuint shaders;

GLBatch zylinderBoden;
GLBatch normBoden;

GLBatch zylinderMantel;
GLBatch normMantel;

GLBatch zylinderDeckel;
GLBatch normDeckel;

/// View space light position
float light_pos[4] = { 0.5f,0.1f,-5.0f,1.0f };
/// Lichtfarben
float light_ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
float light_diffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
float light_specular[4] = { 1.0f,1.0f,1.0f,1.0f };

//Materialeigenschaften
float mat_emissive[4] = { 0.0, 0.0, 0.0, 1.0 };
float mat_ambient[4] = { 0.1, 0.1, 0.0, 1.0 };
float mat_diffuse[4] = { 0.6, 0.0, 0.0, 1.0 };
float mat_specular[4] = { 0.8, 0.8, 0.8, 1.0 };
float specular_power = 10;
// Rotationsgroessen
float rotation[] = { 0, 0, 0, 0 };
//GUI
TwBar* bar;

void InitGUI()
{
	bar = TwNewBar("TweakBar");
	TwDefine(" TweakBar size='200 400'");
	TwAddVarRW(bar, "Model Rotation", TW_TYPE_QUAT4F, &rotation, "");
	TwAddVarRW(bar, "Light Position", TW_TYPE_DIR3F, &light_pos, "group=Light axisx=-x axisy=-y axisz=-z");
	//Hier weitere GUI Variablen anlegen. Für Farbe z.B. den Typ TW_TYPE_COLOR4F benutzen
}

void createCircle(boolean direction, float z) {
	const int a = 8;
	M3DVector3f triaVertices[a * 3];
	M3DVector4f triaColors[a * 3];
	M3DVector3f triaNorm[a * 3];

	M3DVector3f normLineVertices[a * 2 * 3];
	M3DVector4f normLineColors[a * 2 * 3];

	float abc = M3D_2PI / a;

	for (int i = 0; i < a; i++) {
		float x = cos(abc * i);
		float x1 = cos(abc * (i + 1));
		float y = sin(abc * i);
		float y1 = sin(abc * (i + 1));
		if (!direction) {
			y = -y;
			y1 = -y1;
		}


		m3dLoadVector4(triaColors[i * 3 + 0], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 3 + 0], 0, 0, z);


		m3dLoadVector4(triaColors[i * 3 + 1], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 3 + 1], x, y, z);

		m3dLoadVector4(triaColors[i * 3 + 2], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 3 + 2], x1, y1, z);
		//eigentlich muss das Cross nur einmal berechnet werden

		//calc norm
		M3DVector3f ab;
		m3dSubtractVectors3(ab, triaVertices[i * 3 + 2], triaVertices[i * 3 + 0]);

		M3DVector3f ac;
		m3dSubtractVectors3(ac, triaVertices[i * 3 + 1], triaVertices[i * 3 + 0]);


		M3DVector3f cross;
		m3dCrossProduct3(cross, ab, ac);
		m3dNormalizeVector3(cross);
		//m3dScaleVector3(cross, 10);

		for (int j = 0; j < 3; j++) {
			int normPostition = i * 3 + j;

			m3dCopyVector3(triaNorm[normPostition], cross);

			m3dCopyVector3(normLineVertices[2 * normPostition + 0], triaVertices[normPostition]);
			m3dLoadVector4(normLineColors[2 * normPostition + 0], 0, 0.6, 1, 1);

			M3DVector3f res;
			m3dAddVectors3(res, triaVertices[normPostition], cross);

			m3dCopyVector3(normLineVertices[2 * normPostition + 1], res);
			m3dLoadVector4(normLineColors[2 * normPostition + 1], 0, 0.6, 1, 1);
		}
		/*

		m3dLoadVector3(lineVertices[i * 2 + 0], x, y, 0);
		m3dLoadVector4(lineColors[i * 2 + 0], 0, 0.6, 1, 1);

		m3dLoadVector3(lineVertices[i * 2 + 1], x + x, y + y, 0);
		m3dLoadVector4(lineColors[i * 2 + 1], 0, 0.6, 1, 1);

		*/
	}
	if (direction) {
		zylinderBoden.Begin(GL_TRIANGLES, a * 3);
		zylinderBoden.CopyVertexData3f(triaVertices);
		zylinderBoden.CopyColorData4f(triaColors);
		zylinderBoden.CopyNormalDataf(triaNorm);
		zylinderBoden.End();

		normBoden.Begin(GL_LINES, a * 6);
		normBoden.CopyVertexData3f(normLineVertices);
		normBoden.CopyColorData4f(normLineColors);
		normBoden.End();
	}
	else {
		zylinderDeckel.Begin(GL_TRIANGLES, a * 3);
		zylinderDeckel.CopyVertexData3f(triaVertices);
		zylinderDeckel.CopyColorData4f(triaColors);
		zylinderDeckel.CopyNormalDataf(triaNorm);
		zylinderDeckel.End();

		normDeckel.Begin(GL_LINES, a * 6);
		normDeckel.CopyVertexData3f(normLineVertices);
		normDeckel.CopyColorData4f(normLineColors);
		normDeckel.End();
	}

}

void createMantel(float h) {


	const int a = 8;
	M3DVector3f triaVertices[a * 6];
	M3DVector4f triaColors[a * 6];
	M3DVector3f triaNorm[a * 6];


	M3DVector3f normLineVertices[a * 2 * 6];
	M3DVector4f normLineColors[a * 2 * 6];


	float abc = M3D_2PI / a;

	for (int i = 0; i < a; i++) {
		float x = cos(abc * i);
		float x1 = cos(abc * (i + 1));
		float y = sin(abc * i);
		float  y1 = sin(abc * (i + 1));



		m3dLoadVector4(triaColors[i * 6 + 0], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 6 + 0], x, y, -h);


		m3dLoadVector4(triaColors[i * 6 + 1], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 6 + 1], x, y, h);

		m3dLoadVector4(triaColors[i * 6 + 2], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 6 + 2], x1, y1, -h);


		m3dLoadVector4(triaColors[i * 6 + 3], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 6 + 3], x, y, h);

		m3dLoadVector4(triaColors[i * 6 + 4], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 6 + 4], x1, y1, h);

		m3dLoadVector4(triaColors[i * 6 + 5], 1, 0.8, 0.2, 1);
		m3dLoadVector3(triaVertices[i * 6 + 5], x1, y1, -h);


		//calc norm
		M3DVector3f ab;
		m3dSubtractVectors3(ab, triaVertices[i * 6 + 1], triaVertices[i * 6 + 0]);
		M3DVector3f ac;
		m3dSubtractVectors3(ac, triaVertices[i * 6 + 5], triaVertices[i * 6 + 0]);

		M3DVector3f cross;
		m3dCrossProduct3(cross, ac, ab);
		m3dNormalizeVector3(cross);
		//m3dScaleVector3(cross, 10);


		for (int j = 0; j < 6; j++) {
			int normPostition = i * 6 + j;
			m3dCopyVector3(triaNorm[normPostition], cross);

			m3dCopyVector3(normLineVertices[2 * normPostition + 0], triaVertices[normPostition]);
			m3dLoadVector4(normLineColors[2 * normPostition + 0], 0, 0.6, 1, 1);

			M3DVector3f res;
			m3dAddVectors3(res, triaVertices[normPostition], cross);

			m3dCopyVector3(normLineVertices[2 * normPostition + 1], res);
			m3dLoadVector4(normLineColors[2 * normPostition + 1], 0, 0.6, 1, 1);


		}

	}
	zylinderMantel.Begin(GL_TRIANGLES, a * 6);
	zylinderMantel.CopyVertexData3f(triaVertices);
	zylinderMantel.CopyColorData4f(triaColors);
	zylinderMantel.CopyNormalDataf(triaNorm);
	zylinderMantel.End();

	normMantel.Begin(GL_LINES, a * 12);
	normMantel.CopyVertexData3f(normLineVertices);
	normMantel.CopyColorData4f(normLineColors);
	normMantel.End();
}
void CreateGeometry()
{
	//Dreieck
	geometryBatch.Begin(GL_TRIANGLES, 2);

	geometryBatch.Normal3f(0, 0, 1);
	geometryBatch.Vertex3f(-1, -1, 0);

	geometryBatch.Normal3f(0, 0, 1);
	geometryBatch.Vertex3f(0, 1, 0);

	geometryBatch.Normal3f(0, 0, 1);
	geometryBatch.Vertex3f(1, -1, 0);

	geometryBatch.End();

	//Shader Programme laden. Die letzen Argumente geben die Shader-Attribute an. Hier wird Vertex und Normale gebraucht.
	shaders = gltLoadShaderPairWithAttributes("VertexShader.glsl", "FragmentShader.glsl", 2,
		GLT_ATTRIBUTE_VERTEX, "vVertex",
		GLT_ATTRIBUTE_NORMAL, "vNormal");

	gltCheckErrors(shaders);
}

// Aufruf draw scene
void RenderScene(void)
{
	// Clearbefehle für den color buffer und den depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	modelViewMatrix.LoadIdentity();
	modelViewMatrix.Translate(0, 0, -5);
	// Speichere den matrix state und führe die Rotation durch
	modelViewMatrix.PushMatrix();

	M3DMatrix44f rot;
	m3dQuatToRotationMatrix(rot, rotation);
	modelViewMatrix.MultMatrix(rot);

	//setze den Shader für das Rendern
	glUseProgram(shaders);
	// Matrizen an den Shader übergeben
	glUniformMatrix4fv(glGetUniformLocation(shaders, "mvpMatrix"), 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
	glUniformMatrix4fv(glGetUniformLocation(shaders, "mvMatrix"), 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
	glUniformMatrix3fv(glGetUniformLocation(shaders, "normalMatrix"), 1, GL_FALSE, transformPipeline.GetNormalMatrix(true));
	// Lichteigenschaften übergeben
	glUniform4fv(glGetUniformLocation(shaders, "light_pos_vs"), 1, light_pos);
	glUniform4fv(glGetUniformLocation(shaders, "light_ambient"), 1, light_ambient);
	glUniform4fv(glGetUniformLocation(shaders, "light_diffuse"), 1, light_diffuse);
	glUniform4fv(glGetUniformLocation(shaders, "light_specular"), 1, light_specular);
	glUniform1f(glGetUniformLocation(shaders, "spec_power"), specular_power);
	//Materialeigenschaften übergeben
	glUniform4fv(glGetUniformLocation(shaders, "mat_emissive"), 1, mat_emissive);
	glUniform4fv(glGetUniformLocation(shaders, "mat_ambient"), 1, mat_ambient);
	glUniform4fv(glGetUniformLocation(shaders, "mat_diffuse"), 1, mat_diffuse);
	glUniform4fv(glGetUniformLocation(shaders, "mat_specular"), 1, mat_specular);
	//Zeichne Model
	//geometryBatch.Draw();

	normBoden.Draw();
	zylinderBoden.Draw();

	normDeckel.Draw();
	zylinderDeckel.Draw();


	zylinderMantel.Draw();
	normMantel.Draw();


	// Hole die im Stack gespeicherten Transformationsmatrizen wieder zurück
	modelViewMatrix.PopMatrix();
	// Draw tweak bars
	TwDraw();
	gltCheckErrors(shaders);
	// Vertausche Front- und Backbuffer
	glutSwapBuffers();
	glutPostRedisplay();
}

// Initialisierung des Rendering Kontextes
void SetupRC()
{
	// Schwarzer Hintergrund
	glClearColor(0.12f, 0.35f, 0.674f, 0.0f);

	// In Uhrzeigerrichtung zeigende Polygone sind die Vorderseiten.
	// Dies ist umgekehrt als bei der Default-Einstellung weil wir Triangle_Fans benützen
	glFrontFace(GL_CCW);

	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
	//erzeuge die geometrie
	CreateGeometry();

	createCircle(true, -1);
	createCircle(false, 1);
	createMantel(1);
	InitGUI();
}

void ShutDownRC()
{
	//Aufräumen
	glDeleteProgram(shaders);

	//GUI aufräumen
	TwTerminate();
}



void ChangeSize(int w, int h)
{
	// Verhindere eine Division durch Null
	if (h == 0)
		h = 1;
	// Setze den Viewport gemaess der Window-Groesse
	glViewport(0, 0, w, h);
	// Ruecksetzung des Projection matrix stack
	projectionMatrix.LoadIdentity();
	viewFrustum.SetPerspective(45, float(w) / float(h), 1, 100);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	// Ruecksetzung des Model view matrix stack
	modelViewMatrix.LoadIdentity();

	// Send the new window size to AntTweakBar
	TwWindowSize(w, h);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("A3 Normalenvektoren");
	glutCloseFunc(ShutDownRC);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Veralteter Treiber etc.
		std::cerr << "Error: " << glewGetErrorString(err) << "\n";
		return 1;
	}
	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT); // same as MouseMotion
	glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventKeyboardGLUT);

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	TwInit(TW_OPENGL_CORE, NULL);
	SetupRC();
	glutMainLoop();

	return 0;
}
