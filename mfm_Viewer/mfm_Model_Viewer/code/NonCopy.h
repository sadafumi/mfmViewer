#ifndef __NONCOPY_H__
#define __NONCOPY_H__

class NonCopy
{
public:
	NonCopy() {};
	~NonCopy() {};
private:
	NonCopy(const NonCopy&);
	NonCopy& operator=(const NonCopy) {};
};


#endif//__NONCOPY_H__
