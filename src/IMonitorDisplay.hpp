#ifndef IMONITORDISPLAY_HPP
# define IMONITORDISPLAY_HPP

# include "IMonitorModule.hpp"

enum UIEventType {
    kEventTypeNone = 0,
    kEventSwitch,
    kEventQuit
};

struct UIEvent {
    UIEventType type;
};

class IMonitorDisplay {
public:
	virtual ~IMonitorDisplay() {}
    virtual void Update(std::vector<IMonitorModule*>& modules) = 0;
    virtual bool PollEvent(UIEvent &event) = 0;
    virtual void Render() = 0;
};

#endif
