#include "event.hpp"

/*BaseEvent::BaseEvent(BaseEvent && rhs) :
    score_trigger_{rhs.score_trigger_}
{    
}

BaseEvent & BaseEvent::operator=(BaseEvent && rhs)
{
    if(&rhs != this)
    {
        score_trigger_ = rhs.score_trigger_;
    }   
    return *this; 
}*/

SpeedEvent::SpeedEvent(const unsigned score_trigger, const float speed) :
    BaseEvent{score_trigger},
    speed_{speed}
{
}

ScoreEvent::ScoreEvent(const unsigned score_strigger, 
                       const int score_bonus) :
                        BaseEvent{score_strigger},
                        score_bonus_{score_bonus}
{
}

KeyboardEvent::KeyboardEvent(const unsigned score_trigger) :
    BaseEvent{score_trigger}
{
}