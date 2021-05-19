

/* 
Tcl
TclClass
TclObject
*/


#include <stdio.h>
#include <string.h>
#include "agent.h"
#include <random.h>  // added later foR RANDOM

class NHDFAgent : public Agent {
public:
	NHDFAgent(); //constructor 
protected:
	int command (int argc, const char*const* argv);
private:
	double setValue;
	void ShowValue();
		
};

//The following class connects between Otcl and C++
static class NHDFAgentClass : public TclClass {
public:
	NHDFAgentClass(): TclClass("Agent/NHDF") {}
	TclObject* create(int, const char*const*) {
		return (new NHDFAgent());
	}
}class_NHDF_agent;

//Shadow object
/*
when a TCL object is been called, the C++ class will return an agent, if the agent is not present, it shows a FAILED SHADOW OBJECT Error.
*/

//Now we have to implement all the function of the main class

NHDFAgent::NHDFAgent():Agent(PT_UDP) {
	bind("SetValue",&setValue);
	//bind("Magnetometer",&magneto);
//binding is between the Otcl and C++ variables
}

int NHDFAgent::command(int argc, const char*const* argv) {
	if (argc==2) {
		if(strcmp(argv[1],"getValue")==0) {
			ShowValue();
			return (TCL_OK);
		}
	
	}
	return(Agent::command(argc,argv));
}

void NHDFAgent::ShowValue() {
 	setValue = rand()%10+1;
	Tcl& tcl = Tcl::instance();
	//tcl.eval("puts \"The random Value is: \" ");
	tcl.evalf("puts \"The random Value is %f\" ",setValue);
}


