#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <AudioToolbox/AudioToolbox.h>

#include "glm.h"
#include "mtxlib.h"
#include "trackball.h"
#include "pca.h"

using namespace std;

_GLMmodel *mesh;
int WindWidth, WindHeight;

int last_x, last_y;

const float epsilon = 1e-6;

static bool LoadWAVFile(const char* filename, ALenum* format, ALvoid** data, ALsizei* size, ALsizei* freq, Float64* estimatedDurationOut)
{
	CFStringRef filenameStr = CFStringCreateWithCString( NULL, filename, kCFStringEncodingUTF8 );
	CFURLRef url = CFURLCreateWithFileSystemPath( NULL, filenameStr, kCFURLPOSIXPathStyle, false );
	CFRelease( filenameStr );

	AudioFileID audioFile;
	OSStatus error = AudioFileOpenURL( url, kAudioFileReadPermission, kAudioFileWAVEType, &audioFile );
	CFRelease( url );

	if ( error != noErr )
	{
		fprintf( stderr, "Error opening audio file. %d\n", error );
		return false;
	}

	AudioStreamBasicDescription basicDescription;
	UInt32 propertySize = sizeof(basicDescription);
	error = AudioFileGetProperty( audioFile, kAudioFilePropertyDataFormat, &propertySize, &basicDescription );

	if ( error != noErr )
	{
		fprintf( stderr, "Error reading audio file basic description. %d\n", error );
		AudioFileClose( audioFile );
		return false;
	}

	if ( basicDescription.mFormatID != kAudioFormatLinearPCM )
	{
		// Need PCM for Open AL. WAVs are (I believe) by definition PCM, so this check isn't necessary. It's just here
		// in case I ever use this with another audio format.
		fprintf( stderr, "Audio file is not linear-PCM. %d\n", basicDescription.mFormatID );
		AudioFileClose( audioFile );
		return false;
	}

	UInt64 audioDataByteCount = 0;
	propertySize = sizeof(audioDataByteCount);
	error = AudioFileGetProperty( audioFile, kAudioFilePropertyAudioDataByteCount, &propertySize, &audioDataByteCount );
	if ( error != noErr )
	{
		fprintf( stderr, "Error reading audio file byte count. %d\n", error );
		AudioFileClose( audioFile );
		return false;
	}

	Float64 estimatedDuration = 0;
	propertySize = sizeof(estimatedDuration);
	error = AudioFileGetProperty( audioFile, kAudioFilePropertyEstimatedDuration, &propertySize, &estimatedDuration );
	if ( error != noErr )
	{
		fprintf( stderr, "Error reading estimated duration of audio file. %d\n", error );
		AudioFileClose( audioFile );
		return false;
	}

	ALenum alFormat = 0;

	if ( basicDescription.mChannelsPerFrame == 1 )
	{
		if ( basicDescription.mBitsPerChannel == 8 )
			alFormat = AL_FORMAT_MONO8;
		else if ( basicDescription.mBitsPerChannel == 16 )
			alFormat = AL_FORMAT_MONO16;
		else
		{
			fprintf( stderr, "Expected 8 or 16 bits for the mono channel but got %d\n", basicDescription.mBitsPerChannel );
			AudioFileClose( audioFile );
			return false;
		}

	}
	else if ( basicDescription.mChannelsPerFrame == 2 )
	{
		if ( basicDescription.mBitsPerChannel == 8 )
			alFormat = AL_FORMAT_STEREO8;
		else if ( basicDescription.mBitsPerChannel == 16 )
			alFormat = AL_FORMAT_STEREO16;
		else
		{
			fprintf( stderr, "Expected 8 or 16 bits per channel but got %d\n", basicDescription.mBitsPerChannel );
			AudioFileClose( audioFile );
			return false;
		}
	}
	else
	{
		fprintf( stderr, "Expected 1 or 2 channels in audio file but got %d\n", basicDescription.mChannelsPerFrame );
		AudioFileClose( audioFile );
		return false;
	}

	UInt32 numBytesToRead = audioDataByteCount;
	void* buffer = malloc( numBytesToRead );

	if ( buffer == NULL )
	{
		fprintf( stderr, "Error allocating buffer for audio data of size %u\n", numBytesToRead );
		return false;
	}

	error = AudioFileReadBytes( audioFile, false, 0, &numBytesToRead, buffer );
	AudioFileClose( audioFile );

	if ( error != noErr )
	{
		fprintf( stderr, "Error reading audio bytes. %d\n", error );
		free(buffer);
		return false;
	}

	if ( numBytesToRead != audioDataByteCount )
	{
		fprintf( stderr, "Tried to read %lld bytes from the audio file but only got %d bytes\n", audioDataByteCount, numBytesToRead );
		free(buffer);
		return false;
	}

	*freq = basicDescription.mSampleRate;
	*size = audioDataByteCount;
	*format = alFormat;
	*data = buffer;
	*estimatedDurationOut = estimatedDuration;

	return true;
}
ALuint audio_source = 0;
void audio_init() {

	//
	// Initialization
	//
	ALCdevice* device = alcOpenDevice( NULL );

	if ( device == NULL )
	{
		fputs( "Couldn't open device", stderr );
		exit(1);
	}

	ALCcontext* context = alcCreateContext( device, NULL );

	if ( context == NULL )
	{
		fputs( "Error creating context", stderr );
		exit(1);
	}

	alcMakeContextCurrent( context );


	//
	// Generate buffers
	//
	alGetError(); // clear error code

	ALuint buffer;
	alGenBuffers( 1, &buffer );

	ALenum error = alGetError();

	if ( error != AL_NO_ERROR )
	{
		fprintf( stderr, "Couldn't generate buffer. %d\n", error );
		exit(1);
	}

	ALenum format = 0;
	ALvoid* data = NULL;
	ALsizei size = 0, freq = 0;
	Float64 estimatedDurationInSeconds = 0;

	if ( !LoadWAVFile( "input_voice/microphone-result.wav", &format, &data, &size, &freq, &estimatedDurationInSeconds ) )
	{
		fputs( "Wouldn't load wav", stderr );
		exit(1);
	}

	// copy the wav into AL buffer 0
	alBufferData( buffer, format, data, size, freq );
	free(data);
	error = alGetError();
	if ( error != AL_NO_ERROR )
	{
		fprintf( stderr, "Error copying helloworld wav. %d\n", error );
		exit(1);
	}

	//
	// Generate sources
	//

	alGenSources( 1, &audio_source );
	error = alGetError();
	if ( error != AL_NO_ERROR )
	{
		fprintf( stderr, "Error generating source. %d\n", error );
		exit(1);
	}

	//
	// Attach buffer to source
	//
	alSourcei( audio_source, AL_BUFFER, buffer );
	error = alGetError();
	if ( error != AL_NO_ERROR )
	{
		fprintf( stderr, "Error attaching buffer to source. %d\n", error );
		exit(1);
	}



	/*int sleepDuration = ceil( estimatedDurationInSeconds );
	printf( "sleeping for %d seconds while the file plays\n", sleepDuration );
	sleep(sleepDuration);

	alcMakeContextCurrent( NULL );
	alcDestroyContext( context );
	alcCloseDevice( device );

	puts( "OK" );

    return 0;*/
}



void Reshape(int width, int height)
{
	int base = min(width, height);

	tbReshape(width, height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 1.0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3.5);

	WindWidth = width;
	WindHeight = height;
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	tbMatrix();

	// render solid model
	glEnable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glmDraw(mesh, GLM_SMOOTH);

	// render wire model
	/*glPolygonOffset(1.0, 1.0);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glLineWidth(1.0f);
	glColor3f(0.6, 0.0, 0.8);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glmDraw(mesh, GLM_SMOOTH);
	*/

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

vector3 Unprojection(vector2 _2Dpos)
{
	float Depth;
	int viewport[4];
	double ModelViewMatrix[16];				//Model_view matrix
	double ProjectionMatrix[16];			//Projection matrix

	glPushMatrix();
	tbMatrix();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);

	glPopMatrix();

	glReadPixels((int)_2Dpos.x, viewport[3] - (int)_2Dpos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Depth);

	double X = _2Dpos.x;
	double Y = _2Dpos.y;
	double wpos[3] = { 0.0 , 0.0 , 0.0 };

	gluUnProject(X, ((double)viewport[3] - Y), (double)Depth, ModelViewMatrix, ProjectionMatrix, viewport, &wpos[0], &wpos[1], &wpos[2]);

	return vector3(wpos[0], wpos[1], wpos[2]);
}

void mouse(int button, int state, int x, int y)
{
	tbMouse(button, state, x, y);


	last_x = x;
	last_y = y;
}

void motion(int x, int y)
{
	tbMotion(x, y);
	last_x = x;
	last_y = y;
}

vector<vector<float> > source;
vector<float> source_sequece;
int all = 0;
float pca_ref1 = 10.0;
float pca_ref2 = 10.0;
float pca_ref3 = 10.0;
float pca_ref4 = 10.0;
float ref1 = 5;
float ref2 = 5;
float ref3 = 14;
float ref4 = 5;
bool animate = true;

void test()
{
	for (int i = 1; i <= mesh->numvertices; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mesh->vertices[3 * i + j] = (mean_shape[3 * (i - 1) + j] / 30
										+ ref1 * pca_ref1 * pca_str1[3 * (i - 1) + j] / 30
										+ ref2 * pca_ref2 * pca_str2[3 * (i - 1) + j] / 30
										+ ref3 * pca_ref3 * pca_str3[3 * (i - 1) + j] / 30
										+ (-1)*ref4 * pca_ref4 * pca_str4[3 * (i - 1) + j] / 30);
		}
	}
	glmUnitize(mesh);
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27: // ESC
		exit(0);
		break;
	case 'x':
		alSourcePlay( audio_source );
		break;
	case 'z':
		all = 0;
		animate = !animate;
		break;
	}
}


int timeline = 100000;
void timf(int value)
{
	int cur = glutGet(GLUT_ELAPSED_TIME);
	int elapsed = cur - value;
	timeline += elapsed;
	glutPostRedisplay();
	int time_window = 40/4;
	glutTimerFunc(time_window, timf, cur);
	if (animate) {
		all = timeline / time_window;
		if (all < source[0].size()) {
			pca_ref1 = source[source_sequece[0]][all];
			pca_ref2 = source[source_sequece[1]][all];
			pca_ref3 = source[source_sequece[2]][all];
			pca_ref4 = source[source_sequece[3]][all];
			test();
			glutSetWindowTitle((to_string(all) + "_f1=" + to_string(ref1) + "_f2=" + to_string(ref2) + "_f3=" + to_string(ref3) + "_f4=" + to_string(ref4)).c_str());
		} else if (timeline / time_window > source[0].size() + time_window) {
			// to fix
			// use openAL to align audio with video
			alSourcePlay( audio_source );
			timeline = 360; // offset
		}
	}
}

void readFile() {
	//read sequence
	FILE *in_seq;
	float f1;
	char str[20];
	char buffer[10], numbuf[10];
	for (int i = 0; i < 16; i++)
	{
		vector<float> temp_vec;
		sprintf(numbuf, "%d", i);
		strcpy(str, "sequence");
		strcat(str, numbuf);
		in_seq = fopen(str, "r");
		if (in_seq == NULL)
		{
			perror("Error opening file");
		}
		while (!feof(in_seq))
		{
			fscanf(in_seq, "%f\n",&f1);
			temp_vec.push_back(f1);
		}
		source.push_back(temp_vec);
		fclose(in_seq);
	}

	int d1;
	in_seq = fopen("correspond_sequence", "r");
	if (in_seq == NULL)
	{
		perror("Error opening file");
	}
	while (!feof(in_seq))
	{
		fscanf(in_seq, "%d\n", &d1);
		source_sequece.push_back(d1);
	}
	fclose(in_seq);
}

int main(int argc, char *argv[])
{
	readFile();
	WindWidth = 1024;
	WindHeight = 768;

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

	glutInit(&argc, argv);
	glutInitWindowSize(WindWidth, WindHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-WindWidth)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-WindHeight)/2);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Display Animation");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(Keyboard);
	glClearColor(0, 0, 0, 0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	tbInit(GLUT_LEFT_BUTTON);
	tbAnimate(GL_FALSE);

	glutTimerFunc(0, timf, 0); // Set up timer for 40ms, about 25 fps

	// load 3D model
	std::cout << "Loading model ... ";
	mesh = glmReadOBJ("./data/head.obj");
	std::cout << "done." << std::endl;

	glmUnitize(mesh);
	glmFacetNormals(mesh);
	glmVertexNormals(mesh, 90.0);

	audio_init();
	glutMainLoop();

	return 0;

}

