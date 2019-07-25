//
//	md2.h - header file
//	@author Bruno Neto
//	@brief an md2 model class and the structures needed for loading rendering and animating
//	version 1.0


#pragma once
#include	<GL/glew.h>
#include	<GL/freeglut.h>
#include	<fstream>
#include	<iostream>
#include <glm/glm.hpp>
#include "BMPLoader.h"



// number of precalculated normals
#define NUMVERTEXNORMALS		162

// precalculated normal vectors
#define SHADEDOT_QUANT			16

// magic number "IDP2" or 844121161
#define MD2_IDENT				(('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define	MD2_VERSION				8

// maximum number of vertices for a MD2 model
#define MAX_MD2_VERTS			2048


//@brief array of 3 floats  
typedef float vec3_t[3];



//@brief md2 header
typedef struct
{
	int		ident;				// magic number. must be equal to "IPD2"
	int		version;			// md2 version. must be equal to 8

	int		skinwidth;			// width of the texture
	int		skinheight;			// height of the texture
	int		framesize;			// size of one frame in bytes

	int		num_skins;			// number of textures
	int		num_xyz;			// number of vertices
	int		num_st;				// number of texture coordinates
	int		num_tris;			// number of triangles
	int		num_glcmds;			// number of opengl commands
	int		num_frames;			// total number of frames

	int		ofs_skins;			// offset to skin names (64 bytes each)
	int		ofs_st;				// offset to s-t texture coordinates
	int		ofs_tris;			// offset to triangles
	int		ofs_frames;			// offset to frame data
	int		ofs_glcmds;			// offset to opengl commands
	int		ofs_end;			// offset to the end of file

} md2_t;



// @brief vertex
typedef struct
{
	unsigned char	v[3];				// compressed vertex' (x, y, z) coordinates
	unsigned char	lightnormalindex;	// index to a normal vector for the lighting

} vertex_t;



// @brief frame
typedef struct
{
	float		scale[3];		// scale values
	float		translate[3];	// translation vector
	char		name[16];		// frame name
	vertex_t	verts[1];		// first vertex of this frame

} frame_t;



//@ brief animation
typedef struct
{
	int		first_frame;			// first frame of the animation
	int		last_frame;				// number of frames
	int		fps;					// number of frames per second

} anim_t;



// @brief the status of animation
typedef struct
{
	int		startframe;				// first frame
	int		endframe;				// last frame
	int		fps;					// frame per second for this animation

	float	curr_time;				// current time
	float	old_time;				// old time
	float	interpol;				// percent of interpolation

	int		type;					// animation type

	int		curr_frame;				// current frame
	int		next_frame;				// next frame

} animState_t;



// @brief animation list for md2 models
typedef enum {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINTING,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH,
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,

	MAX_ANIMATIONS

} animType_t;




// CMD2Model - MD2 model class object.

//@brief an md2 model class and the structures needed for loading rendering and animating
class MD2Model
{
public:
	// constructor/destructor
	/**
	*	@brief constructor for md2 model initialises member variables to defaults 
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	MD2Model(void);
	/**
	*	@brief destructor for md2 object releases any pointer data
	*   @see
	*	@param void
	*	@return
	*	@pre
	*	@post
	*/
	~MD2Model(void);
	

	// functions
	/**
	*	@brief function for loading a md2 model from a md2 file
	*   @see
	*	@param filename the name/directory of the file
	*	@return returns true apon creation
	*	@pre
	*	@post
	*/
	bool	LoadModel(const char *filename);
	/**
	*	@brief function for loading a md2 models skin from a bitmap file
	*   @see
	*	@param filename the filename of the bitmap texture file to load
	*	@return returns true upon completion
	*	@pre filename must be a 24bit bitmap
	*	@post
	*/
	bool	LoadSkin(const char *filename);
	/**
	*	@brief loads a bmp into bmploader object and uses the bmploader object to create a texture of the bitmap and return it
	*   @see
	*	@param filename the filename/path of the file to load
	*	@return unsigned int the type used by gl to store texture data
	*	@pre
	*	@post
	*/
	unsigned int LoadTexture(const char* filename);
	/**
	*	@brief draws the model.
	*   @see
	*	@param time the time elapsed kept track in game with an object ctimer
	*	@return unsigned int
	*	@pre
	*	@post
	*/
	void	DrawModel(float time);
	/**
	*	@brief draw one frame of the model using gl commands.
	*   @see
	*	@param frame the frame to draw
	*	@return void
	*	@pre
	*	@post
	*/
	void	DrawFrame(int frame);
	/**
	*	@brief sets the animation by the enumeration or int given ,note this will likely not work on static md2 models without animation 
	*   @see
	*	@param type the enumeration or int that corresponds to the default animation types in an md2 model
	*	@return
	*	@pre
	*	@post
	*/
	void	SetAnim(int type);
	/**
	*	@brief scales the model by the float factor given 0.2 is 20% smaller etc
	*   @see
	*	@param s the amount to scale the model by
	*	@return void
	*	@pre
	*	@post
	*/
	void	ScaleModel(float s) { m_scale = s; }



	/**
	* @brief Gets the models position
	*
	* Returns the position of the model as a glm::vec3.
	*
	* @return glm::vec3&
	*/
	glm::vec3& GetPosition() { return m_position; }

	/**
	* @brief Sets the models position
	*
	* Sets the position of the model using the parameter given.
	*
	* @param glm::vec3 position
	* @return void
	*/
	void SetPosition(glm::vec3 position);

	/**
	* @brief Gets the models rotation
	*
	* Returns the rotation of the model as a glm::vec3.
	*
	* @return glm::vec3&
	*/
	glm::vec3& GetRotation() { return m_rotation; }

	/**
	* @brief Sets the models rotation
	*
	* Sets the rotation of the model using the parameter given.
	*
	* @param glm::vec3 rotation
	* @return void
	*/
	void SetRotation(glm::vec3 rotation);

	/**
	* @brief Gets the models scale
	*
	* Returns the scale of the model as a glm::vec3.
	*
	* @return glm::vec3&
	*/
	glm::vec3& GetScale() { return m_scaleVector; }

	/**
	* @brief Sets the models scale
	*
	* Sets the rotation of the model using the parameter given.
	*
	* @param glm::vec3 scale
	* @return void
	*/
	void SetScale(glm::vec3 scale);

	/**
	* @brief Gets the camera object
	*
	* Returns a pointer to the camera object to access the view and projection matrices.
	*
	* @return Camera*
	*/
	//CCamera GetCamera() { return m_camera; }

	/**
	* @brief Sets the camera object
	*
	* Sets the camera object to the world camera object to retrieve the view and projection
	* matrices.
	*
	* @return const void
	*/
	//const void SetCamera(CCamera camera) { m_camera = camera; }

	/**
	* @brief Gets the mesh batch
	*
	* Returns the vector of meshes of the model by reference.
	*
	* @return std::vector<Mesh>&
	*/


private:
	/**
	*	@brief calculate the current frame, next frame and interpolation percent.
	*   @see
	*	@param time the current time tracked with a ctime object at runtime
	*	@return void
	*	@pre
	*	@post
	*/
	void	Animate(float time);
	/**
	*	@brief process all lighting calculus.
	*   @see
	*	@param void
	*	@return void
	*	@pre
	*	@post
	*/
	void	ProcessLighting(void);
	/**
	*	@brief interpolate and scale vertices from the current and the next frame
	*   @see
	*	@param vertlist a pointer to the list of vertices of the model
	*	@return void
	*	@pre
	*	@post
	*/
	void	Interpolate(vec3_t *vertlist);
	/**
	*	@brief renders the current frame of the animation
	*   @see
	*	@param void
	*	@return void
	*	@pre
	*	@post
	*/
	void	RenderFrame(void);

public:
	// member variables
	static vec3_t	anorms[NUMVERTEXNORMALS];
	static float	anorms_dots[SHADEDOT_QUANT][256];
	unsigned int gl_texture_object;
	static anim_t	animlist[21];		// animation list

protected:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scaleVector;

		//CCamera m_camera;

private:
	int				num_frames;			// number of frames
	int				num_xyz;			// number of vertices
	int				num_glcmds;			// number of opengl commands

	vec3_t			*m_vertices;		// vertex array
	int				*m_glcmds;			// opengl command array
	int				*m_lightnormals;	// normal index array
	
	unsigned int	m_texid;			// texture id
	animState_t		m_anim;				// animation
	float			m_scale;			// scale value

};



