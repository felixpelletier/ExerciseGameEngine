#include <Vector.h>
#include <GameState.h>
#include <StrategyState.h>
#include <boost/python.hpp>

//Creates the POC module in python containing various utilities (PLUGINS)
BOOST_PYTHON_MODULE(rule_python)
{
    using namespace boost::python;
    using namespace Rule;
    using namespace Rule::Strategie;

    class_<Vector>("Vector")
	    .def("set", &Vector::set)
    	    .def("getX", &Vector::getX)
    	    .def("getY", &Vector::getY);

    class_<GameState>("GameState")
	    .def("getPlayer", &GameState::getPlayer) 
	    .def("setPlayer", &GameState::setPlayer)
	    .def("getTime", &GameState::getTime);
    
    class_<StrategyState>("StrategyState")
	    .def("getPlayer", &StrategyState::getPlayer) 
	    .def("setPlayer", &StrategyState::setPlayer);

}

