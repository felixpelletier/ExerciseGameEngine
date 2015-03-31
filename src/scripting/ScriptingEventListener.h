#pragma once

#include "ScriptingEvent.h"

class ScriptingEventListener{

	public:
		virtual void fireEvent(ScriptingEvent event) = 0;

};
