#include "event.hpp"

SpeedEvent::SpeedEvent(const unsigned score_trigger, const float speed, Snake & snake) :
    BaseEvent{score_trigger, Color{0, 204, 0}},
    speed_{speed},
    snake_{snake}
{
}

void SpeedEvent::operator()()
{
    // Protection to the negative speed.
    if((snake_.speed + speed_) > 0.f)
    {
        snake_.speed += speed_;
    }
    else
    {
        snake_.speed = 0.1f;
    }   
}

ScoreEvent::ScoreEvent(const unsigned score_strigger, 
                       const int score_bonus) :
                        BaseEvent{score_strigger, Color{255, 0, 0}},
                        score_bonus_{score_bonus}
{
}

KeyboardEvent::KeyboardEvent(const unsigned score_trigger) :
    BaseEvent{score_trigger, Color{102, 0, 102}}
{
}