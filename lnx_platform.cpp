#include "lnx_platform.h"
static Window* g_window;

int main(int argc, char** argv){

	// Get Display Port
	Display* xDisplay = XOpenDisplay(0);
	if(xDisplay == NULL)
	//TODO(MSK) logging needed here
		printf("Could not connect to X-Server\n");

	if(!glXQueryExtension(xDisplay, 0, 0))
		printf("GLX could not be found\n");
	
	//Check GLX Version
	int32 major_Version = 0;
	int32 minor_Version = 0;

	if(glXQueryVersion(xDisplay, &major_Version, &minor_Version))
	{
		if(GLX_MAJOR_VERSION < 1 || GLX_MINOR_VERSION < 3)
			//TODO(MSK) logging needed here
			printf("GLX Version %d. %d is insufficant, Version %d.%d requiered\n",
						major_Version, minor_Version, 
						GLX_MAJOR_VERSION, GLX_MINOR_VERSION);
	}
	else
	{
		printf("GLX did not respond to Version Query\n");
	}

    int32 glx_attributes[] = {
        GLX_X_RENDERABLE,   True,
        GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,    GLX_RGBA_BIT,
        GLX_RED_SIZE,       8,
        GLX_GREEN_SIZE,     8,
        GLX_BLUE_SIZE,      8,
        GLX_ALPHA_SIZE,     8,
        GLX_DEPTH_SIZE,     24,
        GLX_STENCIL_SIZE,   8,
        GLX_DOUBLEBUFFER,   True,
        None
    };

	int32 config_num = 0;

	GLXFBConfig* available_configs = glXChooseFBConfig(	xDisplay, 
																											DefaultScreen(xDisplay), 
																											glx_attributes, 
																											&config_num);
	if(Array_Count(available_configs) < 1)
		printf("No Available XFBConfig\n");

	GLXFBConfig config = available_configs[0];																										
	XFree(available_configs);

	XVisualInfo* visual_config = glXGetVisualFromFBConfig(xDisplay, config);

	if(!visual_config)
		printf("getXVisualInfo failed\n");
	
	
	Window window_root = XDefaultRootWindow(xDisplay);
	
	Colormap colormap = XCreateColormap(xDisplay, window_root, visual_config->visual, AllocNone);
	
	XSetWindowAttributes window_attributes;

	window_attributes.colormap = colormap;
	window_attributes.event_mask = 	KeyPressMask | 
																	KeyReleaseMask | 
																	PointerMotionMask |
																	StructureNotifyMask |
																	ButtonPressMask | 
																	ButtonReleaseMask;

	Window window = XCreateWindow(	xDisplay, 
																	window_root, 
																	0, 0,
																	PREFERED_WINDOW_WIDTH,
																	PREFERED_WINDOW_HEIGHT,
																	0,
																	visual_config->depth,
																	InputOutput,
																	visual_config->visual,
																	CWColormap | CWEventMask,
																	&window_attributes);

	g_window = &window;
	XFree(visual_config);

	XStoreName(xDisplay, window, WINDOW_NAME); 
	XMapWindow(xDisplay, window);

	GLXWindow glx_window = glXCreateWindow(xDisplay, config, window, 0);

	//NOTE(msk) temporary halt for debug purposes
	int retval = 0;
	scanf("%d", &retval);

	printf("process done\n");
}

