#ifndef _GAMEFONT_H_
#define _GAMEFONT_H_

//	@brief	Class to handle custom exceptions
//	@author Michael Bell
//	@date	16/07/2019
//	version 1.0

#include "Rectangle.h"
#include <string>
#include <Windows.h>
#include <GL\gl.h>

// Utility class used to draw text on the screen using a 
// specific font.
class CGameFont
{
public:
	/**
	*	@brief Default Constructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	CGameFont();
	/**
	*	@brief Default Destructor
	*   @see
	*	@param
	*	@return 
	*	@pre
	*	@post
	*/
	~CGameFont();

	/**
	*	@brief Create the font with a specific height and weight.
	*   @see
	*	@param Typeface, height and weight of the font
	*	@return void
	*	@pre
	*	@post
	*/
	void CreateFont(const std::string& strTypeface,
		int iFontHeight,
		int iFontWeight);

	/**
	*	@brief	Draw text on the screen at the specified location with
	*			the specified colour.
	*   @see
	*	@param Text to draw, X position, Y position, Red amount, green amount, blue amount
	*	@return void
	*	@pre
	*	@post
	*/
	void DrawText(const std::string& strText, int XPos,
		int YPos, GLfloat iRed = 1.0,
		GLfloat iGreen = 1.0, GLfloat iBlue = 1.0);

	/**
	*	@brief	Returns the size of the text. The top and right fields
	*			of the returned rectangle are set to 0.
	*   @see
	*	@param String text
	*	@return Rectangle bounding text
	*	@pre
	*	@post
	*/
	TRectanglei GetTextSize(const std::string& strText);

	/**
	*	@brief Set the device used to create the font
	*   @see
	*	@param HDC
	*	@return void
	*	@pre
	*	@post
	*/
	static void SetDeviceContext(HDC hDevContext)
	{
		m_hDeviceContext = hDevContext;
	}

private:
	static HDC m_hDeviceContext; // The device context used to create the font.
	GLuint m_uiListBase; // The index of the base of the list.
	HFONT m_hFont; // The win32 font
};

#endif