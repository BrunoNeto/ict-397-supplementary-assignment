#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

//	@brief	Class to handle custom exceptions
//	@author Michael Bell
//	@date	16/07/2019
//	version 1.0

class CException : public std::exception
{
public:
	/**
	*	@brief 
	*   @see
	*	@param
	*	@return Error messase as a string
	*	@pre
	*	@post
	*/
	const char* what() const { return m_strMessage.c_str(); }
	/**
	*	@brief Takes in a custom error string and outputs the message
	*   @see
	*	@param Custom error string
	*	@return void
	*	@pre
	*	@post
	*/
	CException(const std::string& strMessage = "") : m_strMessage(strMessage) { }
	/**
	*	@brief Deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	virtual ~CException() { }

	// Message string to be output
	std::string m_strMessage;
};

#endif 