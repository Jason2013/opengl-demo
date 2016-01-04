#ifndef __DEMO_H__
#define __DEMO_H__

class Demo
{
public:
	virtual void Prepare() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
	virtual ~Demo() {};
};

#endif
