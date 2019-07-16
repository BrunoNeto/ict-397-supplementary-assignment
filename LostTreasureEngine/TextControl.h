#ifndef _TEXTCONTROL_H_
#define _TEXTCONTROL_H_

#include <string>
#include "Rectangle.h"
#include "GameFont.h"

//	@brief	Utility class that display text with an alignment
//			in a specified region
//	@author Michael Bell
//	@date	16/07/2019
//	version 1.0
class CTextControl
{
public:
	/**
	*	@brief Default Constructor
	*   @see
	*	@param Font to be used, Rectangle
	*	@return
	*	@pre
	*	@post
	*/
	CTextControl(CGameFont* pFont, const TRectanglei& rectPosition);
	/**
	*	@brief Default Destructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~CTextControl();

	/**
	*	@brief Enum for the text alignment
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	enum ETextAlignement
	{
		TALeft,
		TACenter,
		TARight
	};

	/**
	*	@brief Set text function
	*   @see
	*	@param Text to set
	*	@return void
	*	@pre
	*	@post
	*/
	void SetText(const std::string& strText) { m_strText = strText; }
	/**
	*	@brief Set alignment function
	*   @see
	*	@param Enum text alignment
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAlignement(ETextAlignement Alignement) { m_Alignement = Alignement; }
	/**
	*	@brief Text control draw function
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void Draw();
	/**
	*	@brief Sets the text colour
	*   @see
	*	@param Red level, Green level, Blue level
	*	@return void
	*	@pre
	*	@post
	*/
	void SetTextColor(GLfloat fRed, GLfloat fGreen, GLfloat fBlue);

private:
	CGameFont* m_pFont; // The font used for the text.
	TRectanglei m_rectPosition; // The rectangle in which the text is diplayed.
	std::string m_strText; // The text to display.
	ETextAlignement m_Alignement; // The alignment of the text.

	// The color of the text.
	GLfloat m_fRed;
	GLfloat m_fGreen;
	GLfloat m_fBlue;
};

#endif