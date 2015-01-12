#include <ScriptEngine.h>
#include <sys/time.h>

//namespace Soul { namespace Script { 

using namespace boost::python;
using namespace boost::python::api;

StrategieEngine::StrategieEngine(){

    Py_Initialize();
    //PyEval_InitThreads(); 
    
    //Ajouter le dossier 'scripts' au path temporaire Python
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("./assets/scripts"));
    PyList_Append(path, PyUnicode_FromString("."));

    //Relacher l'exclusivité de l'interpreteur
    //pour pouvoir l'utiliser sur les autres threads
    PyEval_ReleaseLock(); 
   
}

StrategieEngine::~StrategieEngine(){
	Py_Finalize();	
}

void StrategieEngine::setGameState(struct GameState data){

	this->gameState = data;

}

//Le thread démarre sur cette fonction
void StrategieEngine::updatePosition(){
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure(); //Le thread aquérit l'interpreteur Python

	object pModule, pFunc;
	
	pModule = import("main");

	if (pModule != NULL) {
		pFunc = pModule.attr("getGameState");

		if (pFunc) {

			//Boucle principale du thread (infinie pour l'instant)
			while(1){

				struct StrategyState result;

				object pValue;
			
				pValue = pFunc(this->gameState); //Call Python function and get results back.

				if (pValue != NULL) {

					boost::python::extract<StrategyState> resultExtractor(pValue);
				
					if (resultExtractor.check()){ //Check if result is valid
						result = resultExtractor();//Convert python results from pyObject to GameState
					}
					else{
						printf("Python a retourné un type non valide");
					}
					
				}
				else {
					PyErr_Print();
					fprintf(stderr,"Call failed\n");
				}
				
				this->strategyState = result;//We made it safe

			}

		}
		else {
		    if (PyErr_Occurred())
			PyErr_Print();
		    fprintf(stderr, "Cannot find function");
		}
		
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load ");
	}

	PyGILState_Release (gstate); 

}

struct StrategyState StrategieEngine::getState()
{
	return this->strategyState;
}

//}}
