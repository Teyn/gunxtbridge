/* MiPAL 2010
Author: Tyrone Trevorrow
Purpose: Provides a more generic mechanism for function callbacks.
		 Feel free to extend this to support any function's parameter lists.
*/
#ifndef WBFUNCTOR_H
#define WBFUNCTOR_H

#include "WBMsg.h"
#define WB_BIND( x ) createWBFunctor(this, &x)

class WBFunctorBase
{
public:
	virtual void call(std::string s, WBMsg* m) = 0;
	virtual ~WBFunctorBase(){}
};

template <typename C>
class WBFunctor: public WBFunctorBase
{
public:
	WBFunctor(C* obj, void (C::*pFunc) (std::string, WBMsg*)):
		fObject(obj), fFunction(pFunc) { };
	
	void call(std::string s, WBMsg* m)
	{
		(fObject->*fFunction)(s,m);
	};
private:
	C* fObject;
	typedef void (C::*func) (std::string, WBMsg*);
	func fFunction;
};

template <typename C>
WBFunctorBase* createWBFunctor(C *obj, void (C::*f) (std::string, WBMsg*))
{
	return new WBFunctor<C>(obj, f);
}

#endif
