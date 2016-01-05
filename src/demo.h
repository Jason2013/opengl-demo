#ifndef __DEMO_H__
#define __DEMO_H__

class Demo
{
public:
	virtual void Time(double time) {}
	virtual void Active() {}
	virtual void Key(int key) {}
	virtual void Prepare() {};
	virtual void Draw() {};
	virtual void Finalize() {};
	virtual ~Demo() {};
};

#endif
