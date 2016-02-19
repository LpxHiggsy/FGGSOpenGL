#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;


HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));

	InitGL(argc, argv);	
	InitObjects();
	glutMainLoop();

}


HelloGL::~HelloGL()
{
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = -200.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	
	_rotation = 1.0f;

	ObjMesh* player = MeshLoader::LoadObj("ship.obj");
	Texture2D* playerTex = new Texture2D();
	playerTex->Load("red.raw", 512, 512);

	ObjMesh* banana = MeshLoader::LoadObj("banana.obj");
	Texture2D* texture = new Texture2D();
	texture->Load("banana.raw", 512, 512);
	bananaList = new Linkedlist();
	listnode* bNode;

	TexturedMesh* cube = MeshLoader::LoadTextured("cube.txt");
	Texture2D* cubeTex = new Texture2D();
	cubeTex->Load("stars.raw", 512, 512);
	cubeList = new Linkedlist();
	listnode* cNode;

	ObjMesh* rock = MeshLoader::LoadObj("rocks.obj");
	Texture2D* rockTex = new Texture2D();
	rockTex->Load("brown2048x1024.raw", 2048, 1024);
	rockList = new Linkedlist();
	listnode* rNode;

	ObjMesh* rocket = MeshLoader::LoadObj("Rocket.obj");
	Texture2D* rocketTex = new Texture2D();
	rocketTex->Load("green.raw", 512, 512);
	rocketList = new Linkedlist();
	listnode* roNode;
	
	ObjMesh* planet1 = MeshLoader::LoadObj("planet.obj");
	Texture2D* planetTex = new Texture2D();
	planetTex->Load("blue2048x1024.raw", 2048, 1024);

	ObjMesh* planet2 = MeshLoader::LoadObj("planet2.obj");
	Texture2D* planetTex2 = new Texture2D();
	planetTex2->Load("brown2048x1024.raw", 2048, 1024);
	
	ObjMesh* planet3 = MeshLoader::LoadObj("planet3.obj");
	Texture2D* planetTex3 = new Texture2D();
	planetTex3->Load("red640x640.raw", 640, 640);

	ObjMesh* planet4 = MeshLoader::LoadObj("planet4.obj");
	Texture2D* planetTex4 = new Texture2D();
	planetTex4->Load("white256x256.raw", 256, 256);

	ObjMesh* planet5 = MeshLoader::LoadObj("planet5.obj");
	Texture2D* planetTex5 = new Texture2D();
	planetTex5->Load("pink960x960.raw", 960, 960);

	ObjMesh* enemy = MeshLoader::LoadObj("EnemyShip.obj");
	Texture2D* enemyTex = new Texture2D();
	enemyTex->Load("green.raw", 512, 512);
	enemyList = new Linkedlist();
	listnode* eNode;
	

	playerObj = new Player(player, playerTex);	
	
	planetObj3 = new Planets(planet1, planetTex, -50, 0, 150);
	planetObj2 = new Planets(planet2, planetTex2, 75, 0, 300);
	planetObj = new Planets(planet3, planetTex3, 0, 0, 300);
	planetObj4 = new Planets(planet4, planetTex4, -175, 0, 400);
	planetObj5 = new Planets(planet5, planetTex5, 175, 0, 500);

	for (int i = 0; i < ENEMYCOUNT; i++)
	{
		eNode = enemyList->makeNode(new EnemyShip(enemy, enemyTex, rand() % 50 - 25, rand() % 50 - 25, 75));
		enemyList->insertFirst(eNode);
	}

	for (int i = 0; i < ROCKS; i++)
	{
		rNode = rockList->makeNode(new Rocks(rock, rockTex, rand() % 100 - 50, rand() % 100 - 50, rand() % 800 - 400));
		rockList->insertFirst(rNode);
	}

	for (int i = 0; i < ROCKETCOUNT; i++)
	{
		roNode = rocketList->makeNode(new RocketObj(rocket, rocketTex, rand() % 100 - 50, rand() % 100 - 50, rand() % 800 - 400));
		rocketList->insertFirst(roNode);
	}

	for (int i = 0; i < BANANACOUNT; i++)
	{
		bNode = bananaList->makeNode(new Object(banana, texture, rand() % 100 - 50, rand() % 100 - 50, rand() % 800 - 400));
		bananaList->insertFirst(bNode);
	}
	for (int j = 0; j < CUBECOUNT; j++)
	{
		cNode = cubeList->makeNode(new objectcube(cube, rand() % 700 - 400, rand() % 700 - 400, 800, cubeTex));
		cubeList->insertFirst(cNode);
	}

	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->ambient.x = 0.2;
	_lightData->ambient.y = 0.2;
	_lightData->ambient.z = 0.2;
	_lightData->ambient.w = 1.0;
	_lightData->diffuse.x = 0.8;
	_lightData->diffuse.y = 0.8;
	_lightData->diffuse.z = 0.8;
	_lightData->diffuse.w = 1.0;
	_lightData->specular.x = 0.2;
	_lightData->specular.y = 0.2;
	_lightData->specular.z = 0.2;
	_lightData->specular.w = 1.0;


}


void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(25, 50);
	glutCreateWindow("Stuff");
	glutDisplayFunc(GLUTCallbacks::Display);
	//glutReshapeFunc(GLUTCallbacks::Reshape);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);


	// Use the Projection Matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, 500, 500);
	// Set the correct perspective.
	gluPerspective(45, 1, 0.1, 1000);
	// Get Back to the Modelview 
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//This clears the scene so we start a fresh each time 
	
	
	Vector3 v = { 500.0f, 1.8f, 0.0f };
	Color c = { 255.0f, 255.0f, 255.0f };
	DrawString("Planets Stars ships rocks missles oh and bananas", &v, &c);

	playerObj->Draw();

	planetObj->Draw();
	planetObj2->Draw();
	planetObj3->Draw();
	planetObj4->Draw();
	planetObj5->Draw();

	listnode* en = enemyList->head;
	while (en != nullptr)
	{
		en->data->Draw();
		en= en->next;
	}

	listnode* p = bananaList->head;
	while (p != nullptr)
	{
		p->data->Draw();
		p = p->next;
	}
	listnode* r = rockList->head;
	while (r != nullptr)
	{
		r->data->Draw();
		r = r->next;
	}
	listnode* ro = rocketList->head;
	while (ro != nullptr)
	{
		ro->data->Draw();
		ro = ro->next;
	}
	listnode* cube = cubeList->head;
	while (cube != nullptr)
	{
		cube->data->Draw();
		cube = cube->next;
	}
	
	glFlush(); //Flushes the scene we just drew to the graphics card
	
	glutSwapBuffers();
	
}


void HelloGL::Update()
{
	glLoadIdentity();
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
		camera->center.x, camera->center.y, camera->center.z,
		camera->up.x, camera->up.y, camera->up.z);

	playerObj->Update();
	planetObj->Update();
	planetObj2->Update();
	planetObj3->Update();
	planetObj4->Update();
	planetObj5->Update();

	listnode* enemy = enemyList->head;
	while (enemy != nullptr)
	{
		enemy->data->Update();
		enemy = enemy->next;
	}
	
	listnode* rock = rockList->head;
	while (rock != nullptr)
	{
		rock->data->Update();
		rock = rock->next;
	}
	listnode* rocket = rocketList->head;
	while (rocket != nullptr)
	{
		rocket->data->Update();
		rocket = rocket->next;
	}
	listnode* b = bananaList->head;
	while (b != nullptr)
	{
		b->data->Update();
		b = b->next;
	}
	listnode* c = cubeList->head;
	while (c != nullptr)
	{
		c->data->Update();
		c = c->next;
	}
	
	glutPostRedisplay();

}


void HelloGL::DrawString(const char* text, const Vector3* position, const Color* color)
{
	glPushMatrix();
	glDisable(GL_TEXTURE);
	glDisable(GL_LIGHTING);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE);
	glPopMatrix();
}


void HelloGL::Keyboard(unsigned char key, int x, int y)
{

	if (key == 'w')
	{
		camera->eye.y += 2.0f;
		camera->center.y += 2.0f;
	}

	if (key == 'a')
	{
		camera->center.x += 2.0f;
		camera->eye.x += 2.0f;
	}

	if (key == 'd')
	{
		camera->center.x -= 2.0f;
		camera->eye.x -= 2.0f;
	}

	if (key == 's')
	{
		camera->eye.y -= 2.0f;
		camera->center.y -= 2.0f;
	}

	if (key == 'f')
	{
		camera->eye.z += 2.0f;
		camera->center.z += 2.0f;
	}

	if (key == 'b')
	{
		camera->eye.z -= 2.0f;
		camera->center.z -= 2.0f;
	}
	if (key == 'x')
	{
		camera->eye.y = 0.0f; 
		camera->eye.z = -200.0f;
	}

	if (key == 'c')
	{
		camera->eye.y = 500.0f; 
		camera->eye.z = 950.0f;
	}
	if (key == 'v')
	{
		camera->eye.y = 0.0f;
		camera->eye.z = 5.0f;
	}
}

//void HelloGL::Reshape(int width, int height)
//{
//	if (height == 0)
//	{
//		height = 1;
//	}
//	float ratio = 1.0f *width / width;
//
//	glMatrixMode(GL_PROJECTION);
//
//	glLoadIdentity();
//
//	glViewport(0, 0, width, height);
//
//	gluPerspective(45, ratio, 0.1, 100);
//
//	glMatrixMode(GL_MODELVIEW);
//}




