#pragma once

#include "ScriptingEvent.h"

class ScriptingEventListener{

	public:
		virtual void receiveScriptingEvent(ScriptingEvent event) = 0;

};
