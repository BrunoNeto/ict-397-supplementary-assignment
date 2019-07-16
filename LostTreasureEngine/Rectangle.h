#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

//	@brief	utility template class which contains information for
//			an axis-aligned rectangle.
//			This has mainly been used for aligning text elements on
//			the menu.
//	@author Michael Bell
//	@date	16/07/2019
//	version 1.0
template <class T>
class CRectangle
{
public:
	/**
	*	@brief Default Destructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	CRectangle() : m_Top(0), m_Bottom(0), m_Left(0), m_Right(0) { }
	/**
	*	@brief Constructor which takes the rectangle coordinates as argument
	*   @see
	*	@param Top Coordinate, Bottom coordinate, Left coordinate, Right Coordinate
	*	@return 
	*	@pre
	*	@post
	*/
	CRectangle(T top, T bottom, T left, T right)
		: m_Top(top), m_Bottom(bottom), m_Left(left), m_Right(right) { }
	/**
	*	@brief Default destructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~CRectangle() { }

	/**
	*	@brief Getter method for the width of the rectangle
	*   @see
	*	@param
	*	@return Width of the rectangle
	*	@pre
	*	@post
	*/
	T GetWidth()  const { return m_Right - m_Left; }
	/**
	*	@brief Getter method for the height of the rectangle
	*   @see
	*	@param
	*	@return Height of the rectangle
	*	@pre
	*	@post
	*/
	T GetHeight() const { return m_Bottom - m_Top; }

	/**
	*	@brief	Check if this rectangle intersects with the rectangle 
	*			passed as argument. Returns true if that's the case.
	*   @see
	*	@param Rectangle
	*	@return Boolean
	*	@pre
	*	@post
	*/
	bool Intersect(const CRectangle& rect) const
	{
		return ((m_Left < rect.m_Right) && (m_Right > rect.m_Left) &&
			(m_Bottom > rect.m_Top) && (m_Top < rect.m_Bottom));
	}

	/**
	*	@brief	Returns true if this is a valid rectangle (has a width and
	*			a height).
	*   @see
	*	@param
	*	@return Boolean
	*	@pre
	*	@post
	*/
	bool IsValid() const
	{
		if ((m_Top > m_Bottom) || (m_Left > m_Right))
			return false;
		return true;
	}

	/**
	*	@brief	Moved the rectangle in the x and y offsets
	*   @see
	*	@param x offset, y offset
	*	@return void
	*	@pre
	*	@post
	*/
	void OffsetRect(int xOffset, int yOffset)
	{
		m_Top += yOffset;
		m_Bottom += yOffset;
		m_Left += xOffset;
		m_Right += xOffset;
	}

	
	T  m_Top; // The position of the top side of the rectangle
	T  m_Bottom; // The position of the bottom side of the rectangle
	T  m_Left; // The position of the left side of the rectangle
	T  m_Right; // The position of the right side of the rectangle
};

// Typdefs for the most used types.
typedef CRectangle<int>    TRectanglei;
typedef CRectangle<float>  TRectanglef;
typedef CRectangle<double> TRectangled;

#endif