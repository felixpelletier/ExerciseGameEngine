#include "Plugin.h"

namespace Rule { namespace Strategie { 

class StrategiePlugin : public Rule::Plugin {
	private:
	
	public:
		explicit StrategiePlugin();

    		virtual void install() override;
    		virtual void initialize() override;
    		virtual void shutdown() override;
    		virtual void uninstall() override;

		StrategiePlugin();
		~StrategiePlugin();
};

} }
