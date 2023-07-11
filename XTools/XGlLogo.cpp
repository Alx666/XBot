#include "XGlLogo.h"
#include "..\\XBotDll\XFileFormat.h"
#include <windows.h>

#define RADIFACT  0.0174533
/* TODO
 * 1) AGGIUNGERE ALTRI ENDPOINT
 * 2) PARAMETRIZZARE ORIGINE DEI FULMINI
 */

XGlLogo::XGlLogo(QWidget *parent, const char *name, const QGLWidget *shareWidget, WFlags f)
	: QGLWidget(parent, name, shareWidget, f)
{
	fRed        =     1.0f;
	fGreen      =     1.0f;
	fBlue       =     1.0f;
	fAccel      =     0.0f;
	fZdist      =   -15.0f;
	fXtildeDist =     1.8f;
	fTildeRotX  =     0.0f;
	fTildeRotY  =     0.0f;
	fTildeAccel =     0.0f;
	fLogoZig    =	  5.0f;

	inProgress    = false;
	spawnInLogo   = true;
	connectTildes = false;
	loopPlayed    = false;
	connectPlayed = false;


	//inizializzazione dello spawnIn
	spawnInTimer = startTimer(10);
	animPhase = 0;

	initFX();

	//loop = new QSound("data/loop.wav");
	//loop->setLoops(-1);
	CXFileFormat* xffReader = new CXFileFormat();
	xffReader->Open("data.xff");
	soundSpawnIn.size = xffReader->GetFile("XBot_spawnin","wav",&soundSpawnIn.data);
	soundConnect.size = xffReader->GetFile("XBot_connect","wav",&soundConnect.data);
	xffReader->Close();
	
	delete xffReader;
	xffReader = NULL;

	
}

XGlLogo::~XGlLogo()
{
	delete [] soundSpawnIn.data;
	delete [] soundConnect.data;

}

void XGlLogo::resizeGL( int width, int height )
{
 	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void XGlLogo::initializeGL()
{
	logoRot = 0;

	initDisplayLists();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	//Texturing
	glEnable(GL_TEXTURE_2D);
	loadTexture("XBot_tildeback","bmp",256,256, texTildesBack);
	loadTexture("XBot_conductor","bmp",256,256, texTildes);	
	loadTexture("XBot_tildebody","bmp",256,256, texTildesBody);
	

	//Light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	GLfloat LightAmbient[]=		{ 1.0f, 1.0f, 1.0f, 1.0f }; //Ambient Light 100%
	GLfloat LightDiffuse[]=		{ 0.0f, 0.0f, 0.0f, 1.0f }; //Diffuse at 100%
	GLfloat LightPosition[]=	{ 0.0f, 0.0f, -8.0f, 1.0f }; //source near in front of object

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
}


void XGlLogo::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();


	glTranslatef(0.0f, 0.0f, fZdist);

	if(!spawnInLogo)
		randomLightningGroup(2);
	else if(connectTildes)
	{
		adjustFxStart();
		spawnLightning(fxStartPoint[1], fxStartPoint[0], 5, fTildeAccel/10, 12.0f);
		spawnLightning(fxStartPoint[0], fxStartPoint[1], 5, fTildeAccel/10, 12.0f);
		LightningXRand(fTildeAccel);
	}

	drawTilde( fXtildeDist, fTildeRotX, fTildeRotY);
	drawTilde(-fXtildeDist, fTildeRotX, fTildeRotY - 180);

	if(!spawnInLogo)
	{
		glRotatef(logoRot, 0.0f, 1.0f, 0.0f);
		//drawLogo();
		LightningX();
	}
}

void XGlLogo::drawTilde(float xPos, float tildeRotX, float tildeRotY)
{
	glPushMatrix();
	glLoadIdentity();
		GLfloat color[4] = {fRed, fGreen, fBlue, 1.0f };
		glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color );

		glTranslatef(xPos, 0.0f, fZdist);
		glRotatef(tildeRotY, 0.0f, 1.0f, 0.0f);
		glRotatef(tildeRotX, 1.0f, 0.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, texTildes[0]);
		glCallList(tildeList1);
		glBindTexture(GL_TEXTURE_2D, texTildesBody[0]);
		glCallList(tildeList2);
		glBindTexture(GL_TEXTURE_2D, texTildesBack[0]);
		glCallList(tildeList3);

	glPopMatrix();
}

void XGlLogo::drawLogo()
{
	glPushMatrix();
	glLoadIdentity();
		glTranslatef(0.0f, 0.0f, fZdist);
		glRotatef(logoRot, 0.0f, 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texLogo[0]);
		GLfloat color[4] = {fRed, fGreen, fBlue, 1.0f };
		glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color );
		glCallList(logoList);

	glPopMatrix();
}

//Riolvere prima illuminazione a parte
bool XGlLogo::spawnLightning(Vector3f v1, Vector3f v2, int nFrag, float nZig, float maxDistance, bool lights)
{	
	float nLength = sqrt( (v2.x-v1.x) * (v2.x-v1.x) + (v2.y-v1.y) * (v2.y-v1.y) + (v2.z-v1.z) * (v2.z-v1.z));

	if(nLength > maxDistance && maxDistance != 0)
		return false;

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT1);
	glDisable(GL_TEXTURE_2D);

	Vector3f vn;
	float fFragLength;
	
	
	//Calcolo della normale
	vn.x = (v2.x - v1.x) / nLength;
	vn.y = (v2.y - v1.y) / nLength;
	vn.z = (v2.z - v1.z) / nLength;


	fFragLength = nLength/nFrag;		//Lunghezza di ogni segmento del fulmine
	nZig  = (fFragLength*nZig)/4.24;	//fattore zig-zag, + e' grande + il fulmine e' random

	if(nZig > fFragLength)
		nZig = fFragLength;


	float RG = 0.3 + float(rand()%8)/10; //Componenti Red and Green in aggiunta ad una base Blu x ottenere un fulmine di colore azzurrastro
	int iZig = 100 * (nZig*2);

		if(iZig==0)
			iZig =1;

/*
	glPointSize(6);
	glBegin(GL_POINTS);
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
	glEnd();
*/

	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
		glColor3f(RG, RG, 1.0f);
		glVertex3f(v1.x, v1.y, v1.z);

		for(int i = 0; i<nFrag-1; i++)
		{
			float offX = float(nZig - ((rand()%iZig)/100.0f));
			float offY = float(nZig - ((rand()%iZig)/100.0f));
			float offZ = float(nZig - ((rand()%iZig)/100.0f));

			v1.x += (vn.x*fFragLength);
			v1.y += (vn.y*fFragLength);
			v1.z += (vn.z*fFragLength);

			glVertex3f(v1.x + offX, v1.y + offY, v1.z + offZ);
		}
		glVertex3f(v2.x, v2.y, v2.z);

	glEnd();


	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);


	if(lights)
	{
		glEnable(GL_LIGHT2);

		GLfloat LightAmbient[]=		{ 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat LightDiffuse[]=		{ 0.3f, 0.3f, 1.0f, 1.0f };
		GLfloat LightPosition[]=	{ v2.x, v2.y, v2.z, 0.0};

		glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
		glLightfv(GL_LIGHT2, GL_POSITION,LightPosition);
	}
	else
		glEnable(GL_LIGHT1);

	return true;
}

//PARTONO MAX N FULMINI CONTEMPORANEAMENTE CON FREQUENZA SPECIFICATA maggiore e' la frequenza tanto e' + facile che si raggiunga il limite n
void XGlLogo::randomLightningGroup(int n)
{
	/*
	if(rand()%1000 > 20)
	{
		glDisable(GL_LIGHT2); //disabilita la luce del fulmine 
		glEnable(GL_LIGHT1); //abilita la luce default
		return;
	}*/
	
	adjustFxStart();

	short sIndex, eIndex;
	
		for(int i = 0; i < n; i++)
		{
			sIndex = rand()%NUM_FX_START;
			eIndex = rand()%NUM_FX_END;

			spawnLightning(fxStartPoint[sIndex], RotateY(logoRot, fxEndPoint[eIndex]), 3, 1.0f, fXtildeDist+2);
		}
}

void XGlLogo::timerEvent( QTimerEvent *e )
{
	if(e->timerId() == logoTimer) 
	{
  		logoRot    += 1.0f;
		fTildeRotX += 6.0f + fTildeAccel; 

			if((int)logoRot%90 == 0)
			{
				logoRot    += 1.0f;
			}

		updateGL();
		return;
    }
	else if(e->timerId() == animTimer)
	{
		fTildeAccel += 0.1f;
		fTildeRotY += 3.0f;
	}
	else if(e->timerId() == spawnInTimer)
	{
		if(fTildeRotY < 180.0f)			//gira le Tildes
		{
			fTildeRotY += 4.0f;
			animPhase = 1;
		}
		else if(fXtildeDist < 4.0f)		//allarga le Tildes
		{
			fXtildeDist += 0.04f;
			connectTildes = true;
			animPhase = 2;

				if(!connectPlayed)
				{
					PlaySoundA((const char*)soundConnect.data,NULL,SND_MEMORY | SND_ASYNC);
					connectPlayed = true;
				}
		}
		else if(fXtildeDist >= 4.0f && fTildeAccel < 50.0f && animPhase <= 3)	//accelera le Tildes fino a 50.0f
		{
			fTildeAccel += 0.4f;
			animPhase = 3;
		}
		else if(fTildeAccel >= 50.0f && animPhase < 4)	//spawna la X e azzera accelerazione
		{
			connectTildes = false;
			spawnInLogo = false;
			animPhase = 4;
			//spawnIn->play();
			PlaySoundA((const char*)soundSpawnIn.data,NULL,SND_MEMORY | SND_ASYNC );
		}
		else if((fTildeAccel > 0.0 || fLogoZig > 1.5f) && animPhase <= 5) //Sistemare decelerazione then OK!
		{
			if(fTildeAccel > 0.0)
				fTildeAccel -= 0.80f;

			if(fLogoZig > 0.8f)
				fLogoZig -= 0.08f;

			animPhase = 5;
		}
		else
		{
			animPhase = 0;
			fTildeAccel = 0.0f;
			killTimer(spawnInTimer);
		}
	}
}


//TEST
Vector3f XGlLogo::TranslateX(float distance, Vector3f v1)
{
	Vector3f res;

	res.x = v1.x - (distance - 0.05) + distance; //(1.0 + 6.5) = 7.5
	res.y = v1.y;
	res.z = v1.z;

	return res;
}

























Vector3f XGlLogo::RotateY(float angle, Vector3f v1)
{
	Vector3f origin;
	origin.x = 0; origin.y = 0; origin.z = 0;

	float radius = v1.x;
	Vector3f res;

	res.x = -(radius * cos(logoRot * RADIFACT) + v1.z * cos( (logoRot - 90) * RADIFACT));
	res.y =   v1.y;
	res.z =   radius * sin(logoRot * RADIFACT) + v1.z * sin( (logoRot - 90) * RADIFACT);

	return res;
}

void XGlLogo::showEvent( QShowEvent * )
{
    logoTimer = startTimer(10);
}

void XGlLogo::hideEvent( QHideEvent * )
{
    killTimer(logoTimer);
}

void XGlLogo::startAnim()
{
	//animTimer = startTimer(100);
	fLogoZig += 0.1f;
}

void XGlLogo::stopAnim()
{
	fRed        =     1.0f;
	fGreen      =     1.0f;
	fBlue       =     1.0f;
	fAccel      =     0.0f;
	fXtildeDist =     4.0f;
	fTildeRotY  =   180.0f;
	fTildeAccel =     0.0f;
	fLogoZig    =	  1.0f;
	killTimer(spawnInTimer);
	animPhase = 0;	
	spawnInLogo = false;
	connectTildes = false;
}

bool XGlLogo::loadTexture(char *Filename, char* ext, int width, int height, GLuint texArraY[])
{
	CXFileFormat* xffReader = new CXFileFormat();
	xffReader->Open("data.xff");
	
	char* data;
	unsigned int fsize = xffReader->GetFile(Filename,ext,(void**)&data);
	
	xffReader->Close();
	
	delete xffReader;
	xffReader = NULL;
	
	if(fsize==0)
		return false;
	

	glGenTextures(1, &texArraY[0]);

	glBindTexture(GL_TEXTURE_2D, texArraY[0]);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, &data[55]);



	delete [] data;

	return true;
}

float XGlLogo::evaluateDistance(Vector3f p1, Vector3f p2)
{
	return sqrt( (p2.x-p1.x) * (p2.x-p1.x) + (p2.y-p1.y) * (p2.y-p1.y) + (p2.z-p1.z) * (p2.z-p1.z));
}


void XGlLogo::adjustFxStart()
{
	fxStartPoint[0].x = -1.5f + fXtildeDist;
	fxStartPoint[1].x = -fxStartPoint[0].x;
}

void XGlLogo::initFX()
{
	//Init StartPoints
	for(int i = 0; i<NUM_FX_START; i++)
	{
		fxStartPoint[i].x =  0.0f;
		fxStartPoint[i].y =  0.0f;
		fxStartPoint[i].z =  0.0f;
	}
	for(i = 0; i<NUM_FX_END; i++)
	{
		fxEndPoint[i].x   =  0.0f;
		fxEndPoint[i].y   =  0.0f;
		fxEndPoint[i].z   =  0.0f;
	}

	//START POINT SETUP
	fxStartPoint[0].x = -1.5f + fXtildeDist;
	fxStartPoint[0].y =  0.0f;
	fxStartPoint[0].z =  0.0f;

	fxStartPoint[1].x = -fxStartPoint[0].x;
	fxStartPoint[1].y = -fxStartPoint[0].y;
	fxStartPoint[1].z = -fxStartPoint[0].z;

	//END POINT SETUP
	fxEndPoint[0].x   =  4.0f;
	fxEndPoint[0].y   =  2.0f;
	fxEndPoint[0].z   =  1.0f;
	fxEndPoint[1] = fxEndPoint[0];
	fxEndPoint[2] = fxEndPoint[0];
	fxEndPoint[3] = fxEndPoint[0];
	fxEndPoint[1].x = -fxEndPoint[1].x;
	fxEndPoint[2].y = -fxEndPoint[2].y;
	fxEndPoint[3].x = -fxEndPoint[3].x; fxEndPoint[3].y = -fxEndPoint[3].y;

	fxEndPoint[4].x   =  2.0f;
	fxEndPoint[4].y   =  1.0f;
	fxEndPoint[4].z   =  1.0f;
	fxEndPoint[5] = fxEndPoint[4];
	fxEndPoint[6] = fxEndPoint[4];
	fxEndPoint[7] = fxEndPoint[4];
	fxEndPoint[5].x = -fxEndPoint[5].x;
	fxEndPoint[6].y = -fxEndPoint[6].y;
	fxEndPoint[7].x = -fxEndPoint[7].x; fxEndPoint[7].y = -fxEndPoint[7].y;

	fxEndPoint[8].x   =  1.5f;
	fxEndPoint[8].y   =  2.5f;
	fxEndPoint[8].z   =  1.0f;
	fxEndPoint[9] = fxEndPoint[8];
	fxEndPoint[10] = fxEndPoint[8];
	fxEndPoint[11] = fxEndPoint[8];
	fxEndPoint[9].x = -fxEndPoint[9].x;
	fxEndPoint[10].y = -fxEndPoint[10].y;
	fxEndPoint[11].x = -fxEndPoint[11].x; fxEndPoint[11].y = -fxEndPoint[11].y;

	fxEndPoint[12].x   =  1.2f;
	fxEndPoint[12].y   =  0.2f;
	fxEndPoint[12].z   =  1.0f;
	fxEndPoint[13] = fxEndPoint[12];
	fxEndPoint[13].x = -fxEndPoint[13].x;
	fxEndPoint[13].y = -fxEndPoint[13].y;

	fxEndPoint[14].x   =  0.2f;
	fxEndPoint[14].y   =  1.2f;
	fxEndPoint[14].z   =  1.0f;
	fxEndPoint[15] = fxEndPoint[14];
	fxEndPoint[15].x = -fxEndPoint[15].x;
	fxEndPoint[15].y = -fxEndPoint[15].y;

	short halfArray = NUM_FX_END/2;
	short halfIndex;
	
	//Fixare reversione di Z
	for(i = 0; i < halfArray; i++)
	{
		halfIndex = i + halfArray;
		fxEndPoint[halfIndex] = fxEndPoint[i];
		fxEndPoint[halfIndex].z = -fxEndPoint[i].z;
	}


}

void XGlLogo::initDisplayLists()
{
	logoList = glGenLists(1);

	glNewList(logoList,GL_COMPILE);

	//GLfloat ablue[4] = {0.2f, 0.2f, 1.0f, 1.0f };
	//glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ablue );


/////////////////PUNTE DELLA X/////////////////////
///////////////////////////////////////////////////

	///////////////////////////Upper Right
	glBegin(GL_TRIANGLES);		
		glNormal3f( 0.0f, 0.0f, 1.0f); //Front
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.5f, 2.5f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, 2.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 1.0f, 1.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f); //Rear
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.5f, 2.5f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, 2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( 0.196f, 0.98f, 0.0f); //Upper
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.5f, 2.5f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.5f, 2.5f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4.0f, 2.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 4.0f, 2.0f, 1.0f);

		glNormal3f( 0.447f, -0.89f, 0.0f); //Lower
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 4.0f, 2.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, 2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f, 1.0f, 1.0f);
	glEnd();


	///////////////////////////Upper Left
	glBegin(GL_TRIANGLES);
		glNormal3f( 0.0f, 0.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.5f, 2.5f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -4.0f, 2.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 1.0f, 1.0f);

		glNormal3f( 0.0f, 0.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.5f, 2.5f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -4.0f, 2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( -0.196f, 0.98f, 0.0f); //Upper
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.5f, 2.5f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.5f, 2.5f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -4.0f, 2.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -4.0f, 2.0f, 1.0f);

		glNormal3f( -0.447f, -0.89f, 0.0f); //Lower
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -4.0f, 2.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -4.0f, 2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -2.0f, 1.0f, 1.0f);
	glEnd();

	///////////////////////////Lower Right
	glBegin(GL_TRIANGLES);
		glNormal3f( 0.0f, 0.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, -2.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.5f, -2.5f, 1.0f);

		glNormal3f( 0.0f, 0.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, -2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.5f, -2.5f, -1.0f);
		
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( 0.447f, 0.89f, 0.0f); //Upper
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4.0f, -2.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 4.0f, -2.0f, 1.0f);

		glNormal3f( 0.196f, -0.98f, 0.0f); //Lower
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 4.0f, -2.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, -2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.5f, -2.5f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.5f, -2.5f, 1.0f);
	glEnd();


	///////////////////////////Lower Left
	glBegin(GL_TRIANGLES);
		glNormal3f( 0.0f, 0.0f,   1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -4.0f, -2.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5f, -2.5f, 1.0f);

		glNormal3f( 0.0f, 0.0f,   -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -4.0f, -2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5f, -2.5f, -1.0f);
		
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( -0.447f, 0.89f, 0.0f); //Upper
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -4.0f, -2.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -4.0f, -2.0f, 1.0f);

		glNormal3f( -0.196f, -0.98f, 0.0f); //Lower
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -4.0f, -2.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -4.0f, -2.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5f, -2.5f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.5f, -2.5f, 1.0f);
	glEnd();


		/////////////////Braccia DELLA X///////////////////
		///////////////////////////////////////////////////

	//Braccio SX->DX (Lungo)
	
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f); //Front
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.5f, 2.5f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.5f, -2.5f, 1.0f);
	
		glNormal3f( 0.0f, 0.0f, -1.0f); //Rear
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.5f, 2.5f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.5f, -2.5f, -1.0f);

		glNormal3f( -0.70f, 0.70f, 0.0f); //Upper
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.5f, 2.5f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.5f, 2.5f, 1.0f);

		glNormal3f( 0.70f, -0.70f, 0.0f); //Lower
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.5f, -2.5f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.5f, -2.5f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f, 1.0f, 1.0f);
	glEnd();


	//Braccio DX->SX (Basso)
	glBegin(GL_QUADS);
		glNormal3f( 0.0f,  0.0f, 1.0f); //Front
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.2f, -0.2f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.2f, -1.2f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.5f, -2.5f, 1.0f);

		glNormal3f( 0.0f,  0.0f, -1.0f); //Rear
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.2f, -0.2f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.2f, -1.2f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.5f, -2.5f, -1.0f);

		glNormal3f( -0.70f, 0.70f, 0.0f); //Upper left
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.2f, -0.2f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.2f, -1.2f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.2f, -1.2f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.2f, -0.2f, -1.0f);

		glNormal3f( 0.70f, 0.70f, 0.0f); //Upper right
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.2f, -0.2f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.2f, -0.2f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f, -1.0f, 1.0f);

		glNormal3f( -0.70f, -0.70f, 0.0f); //Lower left (Right is cover)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.2f, -1.2f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.2f, -1.2f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.5f, -2.5f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.5f, -2.5f, 1.0f);
	glEnd();

	//Braccio DX->SX (Alto)
	glBegin(GL_QUADS);
		glNormal3f( 0.0f,  0.0f, 1.0f); //Front
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.2f, 0.2f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -0.2f, 1.2f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.5f, 2.5f, 1.0f);

		glNormal3f( 0.0f,  0.0f, -1.0f); //Rear
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.2f, 0.2f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -0.2f, 1.2f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.5f, 2.5f, -1.0f);

		glNormal3f( 0.70f, -0.70f, 0.0f); //Lower Right
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.2f, 0.2f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -0.2f, 1.2f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -0.2f, 1.2f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.2f, 0.2f, -1.0f);

		glNormal3f( -0.70f, -0.70f, 0.0f); //Lower Left
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.2f, 0.2f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.2f, 0.2f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -2.0f, 1.0f, 1.0f);

		glNormal3f(  0.70f, 0.70f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -0.2f, 1.2f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -0.2f, 1.2f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5f, 2.5f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.5f, 2.5f, 1.0f);
	glEnd();
	glEndList();

	tildeList1 = glGenLists(3);
	glNewList(tildeList1,GL_COMPILE);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.5f,  0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, -0.5f,  0.5f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, -0.5f, -0.5f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.5f,  0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.5f, -0.5f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -0.5f,  0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, -0.5f, -0.5f);
	glEnd();
	glEndList();

	tildeList2 = tildeList1+1;
	glNewList(tildeList2, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.5f,  0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -0.5f,  0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f, -0.5f,  0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.7f,  0.5f,  0.5f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.5f,  0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.7f,  0.5f,  0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f,  0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.5f, -0.5f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.5f, -0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -0.5f, -0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f, -0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.7f,  0.5f, -0.5f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -0.5f,  0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.7f, -0.5f,  0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f, -0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, -0.5f, -0.5f);
		glEnd();
	glEndList();

	tildeList3 = tildeList2+1;
	glNewList(tildeList3, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.5f,  0.0f,  0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.7f,  0.5f,  0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f, -0.5f,  0.5f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.5f,  0.0f,  0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.7f,  0.5f, -0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f, -0.5f, -0.5f);
	
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.5f,  0.0f,  0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.7f,  0.5f,  0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f,  0.5f, -0.5f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.5f,  0.0f,  0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.7f, -0.5f,  0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.7f, -0.5f, -0.5f);
		glEnd();
	glEndList();
}

void XGlLogo::LightningX()
{
	Vector3f v1, v2;

	//PUNTA ALTO DX
	v1.x =  4.0f, v1.y =  2.0f, v1.z =  1.0f;
	v2.x =  4.0f, v2.y =  2.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y =  2.0f, v1.z =  1.0f;
	v2.x =  1.5f, v2.y =  2.5f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y =  2.0f, v1.z = -1.0f;
	v2.x =  1.5f, v2.y =  2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y =  2.0f, v1.z =  1.0f;
	v2.x =  2.0f, v2.y =  1.0f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y =  2.0f, v1.z = -1.0f;
	v2.x =  2.0f, v2.y =  1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  2.0f, v1.y =  1.0f, v1.z =  1.0f;
	v2.x =  2.0f, v2.y =  1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  1.5f, v1.y =  2.5f, v1.z =  1.0f;
	v2.x =  1.5f, v2.y =  2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	//PUNTA ALTO SX
	v1.x = -4.0f, v1.y =  2.0f, v1.z =  1.0f;
	v2.x = -4.0f, v2.y =  2.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y =  2.0f, v1.z =  1.0f;
	v2.x = -1.5f, v2.y =  2.5f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y =  2.0f, v1.z = -1.0f;
	v2.x = -1.5f, v2.y =  2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y =  2.0f, v1.z =  1.0f;
	v2.x = -2.0f, v2.y =  1.0f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y =  2.0f, v1.z = -1.0f;
	v2.x = -2.0f, v2.y =  1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -2.0f, v1.y =  1.0f, v1.z =  1.0f;
	v2.x = -2.0f, v2.y =  1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -1.5f, v1.y =  2.5f, v1.z =  1.0f;
	v2.x = -1.5f, v2.y =  2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	//PUNTA BASSO DX
	v1.x =  4.0f, v1.y = -2.0f, v1.z =  1.0f;
	v2.x =  4.0f, v2.y = -2.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y = -2.0f, v1.z =  1.0f;
	v2.x =  1.5f, v2.y = -2.5f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y = -2.0f, v1.z = -1.0f;
	v2.x =  1.5f, v2.y = -2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y = -2.0f, v1.z =  1.0f;
	v2.x =  2.0f, v2.y = -1.0f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  4.0f, v1.y = -2.0f, v1.z = -1.0f;
	v2.x =  2.0f, v2.y = -1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  2.0f, v1.y = -1.0f, v1.z =  1.0f;
	v2.x =  2.0f, v2.y = -1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x =  1.5f, v1.y = -2.5f, v1.z =  1.0f;
	v2.x =  1.5f, v2.y = -2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	//PUNTA BASSO SX
	v1.x = -4.0f, v1.y = -2.0f, v1.z =  1.0f;
	v2.x = -4.0f, v2.y = -2.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y = -2.0f, v1.z =  1.0f;
	v2.x = -1.5f, v2.y = -2.5f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y = -2.0f, v1.z = -1.0f;
	v2.x = -1.5f, v2.y = -2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y = -2.0f, v1.z =  1.0f;
	v2.x = -2.0f, v2.y = -1.0f, v2.z =  1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -4.0f, v1.y = -2.0f, v1.z = -1.0f;
	v2.x = -2.0f, v2.y = -1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -2.0f, v1.y = -1.0f, v1.z =  1.0f;
	v2.x = -2.0f, v2.y = -1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	v1.x = -1.5f, v1.y = -2.5f, v1.z =  1.0f;
	v2.x = -1.5f, v2.y = -2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 4, fLogoZig, 3.0);

	//Sezione diagonale lunga
	v1.x =  1.5f, v1.y =  2.5f, v1.z =  1.0f;
	v2.x = -2.0f, v2.y = -1.0f, v2.z =  1.0f;
	spawnLightning(v1, v2, 5, fLogoZig, 6.0);

	v1.x =  2.0f, v1.y =  1.0f, v1.z =  1.0f;
	v2.x = -1.5f, v2.y = -2.5f, v2.z =  1.0f;
	spawnLightning(v1, v2, 5, fLogoZig, 6.0);

	v1.x =  1.5f, v1.y =  2.5f, v1.z = -1.0f;
	v2.x = -2.0f, v2.y = -1.0f, v2.z = -1.0f;
	spawnLightning(v1, v2, 5, fLogoZig, 6.0);

	v1.x =  2.0f, v1.y =  1.0f, v1.z = -1.0f;
	v2.x = -1.5f, v2.y = -2.5f, v2.z = -1.0f;
	spawnLightning(v1, v2, 5, fLogoZig, 6.0);

	//Sezione diagonale corta bassa
	v1.x =  2.0f, v1.y = -1.0f, v1.z =  1.0f;
	v2.x =  1.2f, v2.y = -0.2f, v2.z =  1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x =  2.0f, v1.y = -1.0f, v1.z = -1.0f;
	v2.x =  1.2f, v2.y = -0.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x =  1.5f, v1.y = -2.5f, v1.z =  1.0f;
	v2.x =  0.2f, v2.y = -1.2f, v2.z =  1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x =  1.5f, v1.y = -2.5f, v1.z = -1.0f;
	v2.x =  0.2f, v2.y = -1.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x =  0.2f, v1.y = -1.2f, v1.z =  1.0f;
	v2.x =  1.2f, v2.y = -0.2f, v2.z =  1.0f;
	spawnLightning(v1, v2, 2, fLogoZig, 3.0);

	v1.x =  0.2f, v1.y = -1.2f, v1.z = -1.0f;
	v2.x =  1.2f, v2.y = -0.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 2, fLogoZig, 3.0);

	v1.x =  0.2f, v1.y = -1.2f, v1.z =  1.0f;
	v2.x =  0.2f, v2.y = -1.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x =  1.2f, v1.y = -0.2f, v1.z =  1.0f;
	v2.x =  1.2f, v2.y = -0.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	//Sezione diagonale corta Alta
	v1.x = -2.0f, v1.y =  1.0f, v1.z =  1.0f;
	v2.x = -1.2f, v2.y =  0.2f, v2.z =  1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x = -2.0f, v1.y =  1.0f, v1.z = -1.0f;
	v2.x = -1.2f, v2.y =  0.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x = -1.5f, v1.y =  2.5f, v1.z =  1.0f;
	v2.x = -0.2f, v2.y =  1.2f, v2.z =  1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x = -1.5f, v1.y =  2.5f, v1.z = -1.0f;
	v2.x = -0.2f, v2.y =  1.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x = -0.2f, v1.y =  1.2f, v1.z =  1.0f;
	v2.x = -1.2f, v2.y =  0.2f, v2.z =  1.0f;
	spawnLightning(v1, v2, 2, fLogoZig, 3.0);

	v1.x = -0.2f, v1.y =  1.2f, v1.z = -1.0f;
	v2.x = -1.2f, v2.y =  0.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 2, fLogoZig, 3.0);

	v1.x = -0.2f, v1.y =  1.2f, v1.z =  1.0f;
	v2.x = -0.2f, v2.y =  1.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);

	v1.x = -1.2f, v1.y =  0.2f, v1.z =  1.0f;
	v2.x = -1.2f, v2.y =  0.2f, v2.z = -1.0f;
	spawnLightning(v1, v2, 3, fLogoZig, 3.0);
}

void XGlLogo::LightningXRand(int percent)
{
	Vector3f v1, v2;

	//PUNTA ALTO DX
	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y =  2.0f, v1.z =  1.0f;
		v2.x =  4.0f, v2.y =  2.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y =  2.0f, v1.z =  1.0f;
		v2.x =  1.5f, v2.y =  2.5f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y =  2.0f, v1.z = -1.0f;
		v2.x =  1.5f, v2.y =  2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y =  2.0f, v1.z =  1.0f;
		v2.x =  2.0f, v2.y =  1.0f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y =  2.0f, v1.z = -1.0f;
		v2.x =  2.0f, v2.y =  1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}
	if(rand()%100 <= percent)
	{
		v1.x =  2.0f, v1.y =  1.0f, v1.z =  1.0f;
		v2.x =  2.0f, v2.y =  1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}
	if(rand()%100 <= percent)
	{
		v1.x =  1.5f, v1.y =  2.5f, v1.z =  1.0f;
		v2.x =  1.5f, v2.y =  2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	//PUNTA ALTO SX
	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y =  2.0f, v1.z =  1.0f;
		v2.x = -4.0f, v2.y =  2.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y =  2.0f, v1.z =  1.0f;
		v2.x = -1.5f, v2.y =  2.5f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y =  2.0f, v1.z = -1.0f;
		v2.x = -1.5f, v2.y =  2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y =  2.0f, v1.z =  1.0f;
		v2.x = -2.0f, v2.y =  1.0f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y =  2.0f, v1.z = -1.0f;
		v2.x = -2.0f, v2.y =  1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -2.0f, v1.y =  1.0f, v1.z =  1.0f;
		v2.x = -2.0f, v2.y =  1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -1.5f, v1.y =  2.5f, v1.z =  1.0f;
		v2.x = -1.5f, v2.y =  2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	//PUNTA BASSO DX
	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y = -2.0f, v1.z =  1.0f;
		v2.x =  4.0f, v2.y = -2.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}
	
	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y = -2.0f, v1.z =  1.0f;
		v2.x =  1.5f, v2.y = -2.5f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y = -2.0f, v1.z = -1.0f;
		v2.x =  1.5f, v2.y = -2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y = -2.0f, v1.z =  1.0f;
		v2.x =  2.0f, v2.y = -1.0f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  4.0f, v1.y = -2.0f, v1.z = -1.0f;
		v2.x =  2.0f, v2.y = -1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  2.0f, v1.y = -1.0f, v1.z =  1.0f;
		v2.x =  2.0f, v2.y = -1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  1.5f, v1.y = -2.5f, v1.z =  1.0f;
		v2.x =  1.5f, v2.y = -2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	//PUNTA BASSO SX
	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y = -2.0f, v1.z =  1.0f;
		v2.x = -4.0f, v2.y = -2.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y = -2.0f, v1.z =  1.0f;
		v2.x = -1.5f, v2.y = -2.5f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y = -2.0f, v1.z = -1.0f;
		v2.x = -1.5f, v2.y = -2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}
	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y = -2.0f, v1.z =  1.0f;
		v2.x = -2.0f, v2.y = -1.0f, v2.z =  1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}
	if(rand()%100 <= percent)
	{
		v1.x = -4.0f, v1.y = -2.0f, v1.z = -1.0f;
		v2.x = -2.0f, v2.y = -1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}
	if(rand()%100 <= percent)
	{
		v1.x = -2.0f, v1.y = -1.0f, v1.z =  1.0f;
		v2.x = -2.0f, v2.y = -1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}
	if(rand()%100 <= percent)
	{
		v1.x = -1.5f, v1.y = -2.5f, v1.z =  1.0f;
		v2.x = -1.5f, v2.y = -2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 4, fLogoZig, 3.0);
	}

	//Sezione diagonale lunga
	if(rand()%100 <= percent)
	{
		v1.x =  1.5f, v1.y =  2.5f, v1.z =  1.0f;
		v2.x = -2.0f, v2.y = -1.0f, v2.z =  1.0f;
		spawnLightning(v1, v2, 5, fLogoZig, 6.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  2.0f, v1.y =  1.0f, v1.z =  1.0f;
		v2.x = -1.5f, v2.y = -2.5f, v2.z =  1.0f;
		spawnLightning(v1, v2, 5, fLogoZig, 6.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  1.5f, v1.y =  2.5f, v1.z = -1.0f;
		v2.x = -2.0f, v2.y = -1.0f, v2.z = -1.0f;
		spawnLightning(v1, v2, 5, fLogoZig, 6.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  2.0f, v1.y =  1.0f, v1.z = -1.0f;
		v2.x = -1.5f, v2.y = -2.5f, v2.z = -1.0f;
		spawnLightning(v1, v2, 5, fLogoZig, 6.0);
	}

	//Sezione diagonale corta bassa
	if(rand()%100 <= percent)
	{	
		v1.x =  2.0f, v1.y = -1.0f, v1.z =  1.0f;
		v2.x =  1.2f, v2.y = -0.2f, v2.z =  1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  2.0f, v1.y = -1.0f, v1.z = -1.0f;
		v2.x =  1.2f, v2.y = -0.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  1.5f, v1.y = -2.5f, v1.z =  1.0f;
		v2.x =  0.2f, v2.y = -1.2f, v2.z =  1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  1.5f, v1.y = -2.5f, v1.z = -1.0f;
		v2.x =  0.2f, v2.y = -1.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  0.2f, v1.y = -1.2f, v1.z =  1.0f;
		v2.x =  1.2f, v2.y = -0.2f, v2.z =  1.0f;
		spawnLightning(v1, v2, 2, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  0.2f, v1.y = -1.2f, v1.z = -1.0f;
		v2.x =  1.2f, v2.y = -0.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 2, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  0.2f, v1.y = -1.2f, v1.z =  1.0f;
		v2.x =  0.2f, v2.y = -1.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x =  1.2f, v1.y = -0.2f, v1.z =  1.0f;
		v2.x =  1.2f, v2.y = -0.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	//Sezione diagonale corta Alta
	if(rand()%100 <= percent)
	{
		v1.x = -2.0f, v1.y =  1.0f, v1.z =  1.0f;
		v2.x = -1.2f, v2.y =  0.2f, v2.z =  1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -2.0f, v1.y =  1.0f, v1.z = -1.0f;
		v2.x = -1.2f, v2.y =  0.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -1.5f, v1.y =  2.5f, v1.z =  1.0f;
		v2.x = -0.2f, v2.y =  1.2f, v2.z =  1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -1.5f, v1.y =  2.5f, v1.z = -1.0f;
		v2.x = -0.2f, v2.y =  1.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -0.2f, v1.y =  1.2f, v1.z =  1.0f;
		v2.x = -1.2f, v2.y =  0.2f, v2.z =  1.0f;
		spawnLightning(v1, v2, 2, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -0.2f, v1.y =  1.2f, v1.z = -1.0f;
		v2.x = -1.2f, v2.y =  0.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 2, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -0.2f, v1.y =  1.2f, v1.z =  1.0f;
		v2.x = -0.2f, v2.y =  1.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}

	if(rand()%100 <= percent)
	{
		v1.x = -1.2f, v1.y =  0.2f, v1.z =  1.0f;
		v2.x = -1.2f, v2.y =  0.2f, v2.z = -1.0f;
		spawnLightning(v1, v2, 3, fLogoZig, 3.0);
	}
}