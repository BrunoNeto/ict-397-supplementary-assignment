#pragma once
#ifndef __SINGLETON_H
#define __SINGLETON_H

template <class T>

class singleton
{
public:
	static T& Instance()
	{
		static T _instance;
		return _instance;
	}
private:
	singleton();
	~singleton();
	singleton(singleton const&);
	singleton& operator=(singleton const&);
};
#endif
