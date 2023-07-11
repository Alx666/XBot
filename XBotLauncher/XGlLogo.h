#pragma once

#include <qgl.h>
#include <stdio.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <windows.h>
#include <qsound.h> 

#define NUM_FX_START 2
#define NUM_FX_END	 30

struct Vector3f
{
	float x;
	float y;
	float z;
};

class XGlLogo : public QGLWidget
{
	Q_OBJECT

public:


	XGlLogo(QWidget *parent = 0, const char *name = 0, const QGLWidget *shareWidget = 0, WFlags f = 0);
	~XGlLogo();

	void startAnim();
	void stopAnim();

protected:

    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );
	void timerEvent( QTimerEvent * );
	void hideEvent( QHideEvent * );
	void showEvent( QShowEvent * );

private:
	//Variabili relative alla X
	GLint logoList;								//Display list della X
	GLuint texLogo[1];							//Texture della X
	float logoRot;								//Angolo di rotazione della X
	float fAccel;								//accelerazione (RAFFINARE)

	//Variabili relative alle Tildes
	GLint tildeList1, tildeList2, tildeList3;	//Display list delle Tildes
	GLuint texTildes[1];						//texture della punta
	GLuint texTildesBody[1];					//texture centrale
	GLuint texTildesBack[1];					//texture posteriore
	float fTildeRotX;							//Rotazione su asse x
	float fTildeRotY;
	float fTildeAccel;							//Accelerazione

	//Gestione delle animazioni
	bool spawnInLogo, connectTildes;
	short animPhase;
	int logoTimer;								//timer per gli FPS
	int animTimer;								//timer per eventuale animazione
	int spawnInTimer;
	bool inProgress;							//RAFFINARE						
	float fLogoZig;
	float fZdist;
	float fXtildeDist;
	float fRed, fGreen, fBlue;					//colori per le material (RAFFINARE)
	void randomLightningGroup(int n);
	Vector3f fxStartPoint[NUM_FX_START];		//Array dei punti dove iniziare Fulmini
	Vector3f fxEndPoint[NUM_FX_END];			//Array dei punti dove finire i Fulmini


	//Suoni
	struct XSOUND {
					void*			data;
					unsigned int	size;
	} soundSpawnIn,soundConnect,soundLoop;


	Vector3f RotateY(float angle, Vector3f v1);
	Vector3f TranslateX(float distance, Vector3f v1);
	void initDisplayLists();
	void initFX();
	void drawTilde(float xPos, float tildeRotX = 0, float tildeRotY = 0);
	void drawLogo();							//Disegna il Logo in cemento
	void LightningX();							//Disegna il Logo com fulmini
	void LightningXRand(int percent);			//Randomizza il draw di ogni singolo fulmine
	void adjustFxStart();
	bool spawnLightning(Vector3f v1, Vector3f v2, int nFrag, float nZig, float maxDistance, bool lights = false);
	bool loadTexture(char *Filename, char* ext, int width, int height, GLuint texArraY[]);

	//Test
	float evaluateDistance(Vector3f p1, Vector3f p2);
	
	bool loopPlayed, connectPlayed;
	
};

